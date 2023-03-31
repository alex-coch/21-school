WITH my_cte AS (
	SELECT * FROM generate_series('2022-01-01'::timestamp,
                              '2022-01-10', '24 hours')
)
SELECT 
	DATE(pv.generate_series) AS missing_date
FROM 
	my_cte pv 
LEFT JOIN 
(
SELECT 
	DISTINCT pv2.visit_date 
FROM 
	person_visits pv2 
WHERE 
	person_id = 1 OR person_id = 2
) pr 
ON 
	pv.generate_series = pr.visit_date 
WHERE 
	pr.visit_date IS NULL 
ORDER BY 
	missing_date;

WITH my_cte AS (
	SELECT * FROM generate_series('2022-01-01'::timestamp,
                              '2022-01-10', '24 hours')
)
SELECT 
	DISTINCT pv.visit_date AS missing_date
FROM 
	person_visits pv 
LEFT JOIN 
(
SELECT 
	DISTINCT pv2.visit_date 
FROM 
	person_visits pv2 
WHERE 
	person_id = 1 OR person_id = 2
) pr 
ON 
	pv.visit_date = pr.visit_date 
JOIN 
	my_cte m ON pv.visit_date = DATE(m.generate_series) 
WHERE 
	pr.visit_date IS NULL 
	AND pv.visit_date BETWEEN '2022-01-01' AND '2022-01-10'
ORDER BY 
	missing_date;
