SELECT 
	person_id 
FROM
	person_order po
WHERE 
	order_date  = '2022-01-07'
EXCEPT ALL
SELECT 
	person_id 
FROM 
	person_visits pv 
WHERE 
	visit_date = '2022-01-07'
