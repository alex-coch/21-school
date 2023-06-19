-- в func_group_margin можно передать 4 параметра
-- 	первый - это customer_id
-- 	второй - group_id
-- 	3 - 1 или 2
-- 	    1 - это подсчёт маржи через ограниченное кол-во последних транзакций
-- 	    2 - подсчёт маржи через кол-во дней перед date_of_analysis_formation
-- 	    default - подсчёт маржи через всё кол-во транзакций
-- 	4 - это кол-во дней, либо транзакций (default 0)
DROP FUNCTION if EXISTS func_group_margin;
CREATE
OR REPLACE FUNCTION func_group_margin(
    cust_id INT,
    gr_id INT,
    pick INT DEFAULT 0,
    amount INT DEFAULT 0
) RETURNS NUMERIC LANGUAGE plpgsql AS $ $ DECLARE ret NUMERIC;
BEGIN if pick = 1 THEN WITH pre AS (
    SELECT
        group_summ_paid - group_cost AS dif
    FROM
        purchases
    WHERE
        group_id = gr_id
        AND customer_id = cust_id
    ORDER BY
        transaction_datetime desc
    LIMIT
        amount
)
SELECT
    round(SUM(dif), 6) INTO ret
FROM
    pre;
ELSE if pick = 2 THEN WITH pre AS (
    SELECT
        group_summ_paid - group_cost AS dif
    FROM
        purchases p
        JOIN date_of_analysis_formation d ON p.transaction_datetime BETWEEN d.analysis_formation - INTERVAL '1 day' * amount
        AND d.analysis_formation
    WHERE
        p.group_id = gr_id
        AND p.customer_id = cust_id
    ORDER BY
        p.transaction_datetime desc
)
SELECT
    round(SUM(dif), 6) INTO ret
FROM
    pre;
ELSE WITH pre AS (
    SELECT
        group_summ_paid - group_cost AS dif
    FROM
        purchases
    WHERE
        group_id = gr_id
        AND customer_id = cust_id
    ORDER BY
        transaction_datetime desc
)
SELECT
    round(SUM(dif), 6) INTO ret
FROM
    pre;
END if;
END if;
RETURN ret;
END;
$ $;
DROP view if EXISTS cgroups;
CREATE
OR replace view cgroups AS (
    WITH churn2 AS (
        SELECT
            p.customer_id,
            p.group_id,
            p.group_purchase:: DOUBLE PRECISION / (
                SELECT
                    COUNT(*)
                FROM
                    (
                        SELECT
                            *
                        FROM
                            purchases
                        WHERE
                            customer_id = p.customer_id
                    ) AS pu
                WHERE
                    transaction_datetime BETWEEN p.first_group_purchase_date
                    AND p.last_group_purchase_date
            ):: DOUBLE PRECISION AS group_affinity_index,
            round(
                EXTRACT(
                    epoch
                    FROM
                        (
                            (
                                SELECT
                                    *
                                FROM
                                    date_of_analysis_formation
                            ) - p.last_group_purchase_date
                        ) / 3600 / 24
                ) / p.group_frequency,
                3
            ) AS group_churn_rate
        FROM
            periods p
    ),
    inte AS (
        SELECT
            ph.customer_id,
            ph.group_id,
            ABS(
                EXTRACT(
                    epoch
                    FROM
(
                            ph.transaction_datetime - lag(ph.transaction_datetime) OVER (
                                PARTITION BY ph.customer_id,
                                ph.group_id
                                ORDER BY
                                    ph.transaction_datetime
                            )
                        ) / 3600 / 24
                ) - p.group_frequency
            ) / p.group_frequency AS interim,
            p.group_frequency
        FROM
            purchases ph
            JOIN periods p USING(customer_id, group_id)
    ),
    stab AS (
        SELECT
            customer_id,
            group_id,
            round(COALESCE(AVG(interim), 0), 9) AS group_stability_index
        FROM
            inte
        GROUP BY
            1,
            2
    ),
    discount AS (
        SELECT
            p.customer_id,
            p.group_id,
            d.count:: FLOAT / p.group_purchase:: FLOAT AS group_discount_share,
            p.group_min_discount AS group_minimum_discount
        FROM
            (
                SELECT
                    customer_id,
                    group_id,
                    COUNT(sku_discount)
                FROM
                    checks
                    JOIN purchases USING(transaction_id)
                WHERE
                    sku_discount > 0
                GROUP BY
                    1,
                    2
                ORDER BY
                    1,
                    2
            ) AS d
            JOIN periods p USING(customer_id, group_id)
    ),
    averageDiscount AS (
        SELECT
            customer_id,
            group_id,
            round(SUM(group_summ_paid) / SUM(group_summ), 7) AS group_average_discount
        FROM
            purchases
        GROUP BY
            1,
            2
    )
    SELECT
        c.customer_id,
        c.group_id,
        c.group_affinity_index,
        c.group_churn_rate,
        s.Group_Stability_Index,
        -- 	в func_group_margin можно передать 4 параметра
        -- 	первый - это customer_id
        -- 	второй - group_id
        -- 	3 - 1 или 2
        -- 	    1 - это подсчёт маржи через ограниченное кол-во последних транзакций
        -- 	    2 - подсчёт маржи через кол-во дней перед date_of_analysis_formation
        -- 	    default - подсчёт маржи через всё кол-во транзакций
        -- 	4 - это кол-во дней, либо транзакций (default 0)
        func_group_margin(c.customer_id, c.group_id) AS group_margin,
        d.Group_Discount_Share,
        d.Group_Minimum_Discount,
        a.Group_Average_Discount
    FROM
        churn2 c
        JOIN stab s USING(customer_id, group_id)
        JOIN discount d USING(customer_id, group_id)
        JOIN averageDiscount a USING(customer_id, group_id)
);