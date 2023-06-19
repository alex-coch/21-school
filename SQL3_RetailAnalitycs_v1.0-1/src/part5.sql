DROP FUNCTION if EXISTS do_it_faster;
CREATE
OR REPLACE FUNCTION do_it_faster(
    date1 DATE,
    date2 DATE,
    transactions_amount INT,
    churn_rate NUMERIC,
    discount NUMERIC,
    percentage NUMERIC
) RETURNS TABLE (
    customer_id INT,
    start_date text,
    end_date text,
    required_transactions_count NUMERIC,
    group_name VARCHAR,
    offer_discount_depth NUMERIC
) LANGUAGE plpgsql AS $ $ BEGIN RETURN QUERY
SELECT
    c.customer_id,
    to_char(date1:: DATE, 'dd.mm.yyyy hh:mm:ss.US') AS Start_Date,
    to_char(date2:: DATE, 'dd.mm.yyyy hh:mm:ss.US') AS End_Date,
    round((date2:: DATE - date1:: DATE) / c.customer_frequency, 0) + transactions_amount AS Required_Transactions_Count,
    sg.group_name AS Group_Name,
    CASE
        WHEN g.Group_Minimum_Discount < g.Group_Margin * percentage / 100 THEN g.Group_Minimum_Discount
        ELSE g.Group_Margin * 60 / 100
    END AS Offer_Discount_Depth 
FROM
    cgroups g
    JOIN sku_group sg USING(group_id)
    JOIN customers c USING(customer_id)
WHERE
    g.customer_id = 1
    AND g.Group_Churn_Rate <= churn_rate
    AND g.Group_Discount_Share <= discount
ORDER BY
    g.Group_Affinity_Index desc;
END $ $;
SELECT
    *
FROM
    do_it_faster('2020-01-01', '2022-01-01', 2, 7, 3, 60);