SELECT 
	m.pizza_name,
	m.price,
	p2."name" AS pizzeria_name,
	pv.visit_date 
FROM 
	menu m 
JOIN
	person_visits pv ON m.pizzeria_id = pv.pizzeria_id  
JOIN 
	person p ON pv.person_id = p.id 
JOIN 
	pizzeria p2 ON m.pizzeria_id = p2.id 
WHERE 
	p."name" = 'Kate'
AND 
	m.price BETWEEN 800 AND 1000
ORDER BY 
	pizza_name, price, pizzeria_name;
