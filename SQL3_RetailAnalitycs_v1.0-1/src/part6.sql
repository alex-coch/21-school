DROP FUNCTION if EXISTS crosses;
CREATE
OR REPLACE FUNCTION crosses(
    group_amount INT,
    churn_rate NUMERIC,
    stability NUMERIC,
    share_sku NUMERIC,
    margin NUMERIC
) RETURNS TABLE(
    customer_id INT,
    sku_name VARCHAR,
    offer_discount_depth NUMERIC
) LANGUAGE plpgsql AS $ $ BEGIN RETURN QUERY WITH pre AS (
    SELECT
        c.customer_id,
        c.group_id,
        p.sku_name,
        SUM(s.SKU_Retail_Price - s.SKU_Purchase_Price) AS sku_sum
    FROM
        cgroups c
        JOIN product_grid p USING(group_id)
        JOIN stores s USING(sku_id)
    WHERE
        c.Group_Churn_Rate < churn_rate
        AND c.Group_Stability_Index < stability
    GROUP BY
        1,
        2,
        3
    HAVING
        COUNT(s.sku_id) / COUNT(c.group_id) * 100 <= share_sku
    ORDER BY
        4 desc
),
pre2 AS (
    SELECT
        p.customer_id,
        p.group_id,
        p.sku_name,
        p.sku_sum,
        SUM(
            (s.sku_retail_price - s.sku_purchase_price) / s.sku_retail_price
        ) AS divd
    FROM
        pre p
        JOIN product_grid pg USING(group_id)
        JOIN stores s USING(sku_id)
    GROUP BY
        1,
        2,
        3,
        4
    HAVING
        COUNT(p.group_id) < group_amount
)
SELECT
    DISTINCT p.customer_id,
    p.sku_name,
    CASE
        WHEN p.sku_sum / p.divd >= g.group_minimum_discount THEN g.group_minimum_discount
        ELSE p.sku_sum / p.divd * margin
    END AS Offer_Discount_Depth
FROM
    pre2 p
    JOIN cgroups g USING(group_id);
END $ $;
SELECT
    *
FROM
    crosses(2, 7, 3, 100, 90);