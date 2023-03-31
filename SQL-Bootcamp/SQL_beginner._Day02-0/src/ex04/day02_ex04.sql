SELECT 
	m.pizza_name AS pizza_name,
	p."name" AS pizzeria_name,
	m.price AS price
FROM 
	menu m 
FULL JOIN
	pizzeria p ON m.pizzeria_id = p.id 
WHERE 
	m.pizza_name = 'mushroom pizza' OR m.pizza_name = 'pepperoni pizza'
ORDER BY 
	pizza_name, 
	pizzeria_name
