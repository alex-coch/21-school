SELECT 
	DISTINCT p.id  
FROM 
	person p LEFT JOIN person_visits pv ON p.id = pv.person_id
WHERE 
	pv.visit_date BETWEEN '2022-01-06' AND '2022-01-09' 
	OR pv.pizzeria_id = 2
ORDER BY 
	p.id DESC;
