DROP FUNCTION if EXISTS Check_Measure;
CREATE
OR REPLACE FUNCTION Check_Measure(
    cust_id INT,
    variant INT,
    start_date TIMESTAMP,
    end_date TIMESTAMP,
    trans_count INT,
    rate_check_measure NUMERIC
) RETURNS FLOAT LANGUAGE plpgsql AS $ $ BEGIN if variant = 1 THEN -- by transactions
RETURN (
    SELECT
        round(
            SUM(transaction_summ) * rate_check_measure / COUNT(transaction_summ),
            2
        ) AS Required_Check_Measure
    FROM
        (
            SELECT
                t.transaction_summ
            FROM
                cards c
                JOIN transactions t USING(customer_card_id)
            WHERE
                c.customer_id = cust_id
            ORDER BY
                1,
                t.transaction_datetime desc
            LIMIT
                trans_count
        ) tr
);
ELSE -- by period
RETURN (
    SELECT
        round(
            SUM(transaction_summ) * rate_check_measure / COUNT(transaction_summ),
            2
        ) AS Required_Check_Measure
    FROM
        (
            SELECT
                t.transaction_summ
            FROM
                cards c
                JOIN transactions t USING(customer_card_id)
            WHERE
                c.customer_id = cust_id
                AND t.transaction_datetime BETWEEN start_date AND end_date
            ORDER BY
                1,
                t.transaction_datetime desc
        ) per
);
END if;
END;
$ $;
--select * from Check_Measure(1, 1, '2020-01-01', '2022-01-01', 5, 1.5);
--select Check_Measure from Check_Measure(1, 2, '2020-01-01', '2021-01-01', 5, 1.5);
DROP FUNCTION if EXISTS average_check_growth;
CREATE
OR REPLACE FUNCTION average_check_growth(
    variant INT,
    start_date TIMESTAMP,
    end_date TIMESTAMP,
    trans_count INT,
    rate_check_measure NUMERIC,
    max_churn_rate NUMERIC,
    max_discount_share NUMERIC,
    margin NUMERIC
) RETURNS TABLE(
    customer_id INT,
    required_check_measure NUMERIC,
    group_name VARCHAR,
    offer_discount_depth INT
) LANGUAGE plpgsql AS $ $ DECLARE Required_Check_Measure TIMESTAMP: = get_date_analysis();
BEGIN RETURN QUERY
SELECT
    c.customer_id,
    Check_Measure(
        c.customer_id,
        variant,
        '2020-01-01',
        '2022-01-01',
        5,
        1.5
    ):: NUMERIC,
    sg.group_name,
    (
        CASE
            WHEN Group_Margin * margin / 100 > Group_Minimum_Discount THEN Group_Minimum_Discount
            ELSE Group_Margin * margin / 100
        END
    ):: INT AS Offer_Discount_Depth -- Group_Affinity_Index, Group_Churn_Rate, Group_Discount_Share, Group_Margin * 80/100,
FROM
    cgroups c
    JOIN sku_group sg USING(group_id)
WHERE
    Group_Churn_Rate <= max_churn_rate
    AND Group_Discount_Share <= max_discount_share
ORDER BY
    Group_Affinity_Index desc;
END;
$ $;
SELECT
    *
FROM
    average_check_growth(1, '2020-01-01', '2022-01-01', 2, 1.5, 7, 3, 60);
SELECT
    *
FROM
    average_check_growth(2, '2020-01-01', '2022-01-01', 2, 1.5, 7, 3, 60);