SELECT
	order_date AS action_date, p."name" AS person_name
FROM
	person_order po 
JOIN 
	person p ON person_id = p.id
INTERSECT
SELECT 
	visit_date AS action_date, p."name" AS person_name  
FROM 
	person_visits pv
JOIN 
	person p ON person_id = p.id
ORDER BY 
	action_date, person_name DESC
