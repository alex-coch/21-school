SELECT 
	m.pizza_name AS pizza_name,
	p2."name" AS pizzeria_name
FROM 
	menu m 
JOIN
	person_order po ON m.id =po.menu_id 
JOIN 
	person p ON po.person_id = p.id 
JOIN 
	person_visits pv ON p.id = pv.person_id AND pv.visit_date = po.order_date 
JOIN 
	pizzeria p2 ON pv.pizzeria_id = p2.id 
WHERE
	p."name" = 'Denis' OR p."name" = 'Anna'
ORDER BY 
	pizza_name, 
	pizzeria_name
