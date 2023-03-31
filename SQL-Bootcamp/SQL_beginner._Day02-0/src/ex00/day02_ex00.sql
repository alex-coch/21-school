SELECT 
	p."name",
	p.rating 
FROM 
	pizzeria p
LEFT JOIN 
	person_visits pv ON pv.pizzeria_id = p.id 
WHERE 
	pv.pizzeria_id IS NULL 
