SELECT 
	p."name" 
FROM 
	pizzeria p
JOIN
	person_visits pv ON p.id = pv.pizzeria_id 
JOIN 
	person p2 ON pv.person_id = p2.id
JOIN 
	menu m ON p.id = m.pizzeria_id 
WHERE 
	p2."name" = 'Dmitriy' 
AND 
	pv.visit_date = '2022-01-08'
AND 
	m.price < 800
