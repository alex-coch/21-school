SELECT 
	p2.order_date, 
	CONCAT(p."name", ' (age:', p.age, ')') AS person_information
FROM 
	person p 
NATURAL JOIN
(SELECT 
	person_id AS id,
	order_date
FROM 
	person_order po 
) p2
ORDER BY 
	p2.order_date, person_information
