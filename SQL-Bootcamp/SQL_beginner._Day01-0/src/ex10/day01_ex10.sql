SELECT 
	p."name" AS person_name,
	m.pizza_name AS pizza_name,
	p2."name" AS pizzeria_name
FROM 
	person p
JOIN
	person_order po ON p.id = po.person_id 
JOIN 
	menu m ON po.menu_id = m.id
JOIN 
	person_visits pv ON p.id = pv.person_id AND po.order_date = pv.visit_date 
JOIN 
	pizzeria p2 ON pv.pizzeria_id = p2.id 
ORDER BY 
	person_name, pizza_name, pizzeria_name
