SELECT 
	p."name",
	count(po.id) AS count_of_orders, 
	round(avg(m.price), 2) AS average_price,
	max(m.price) AS max_price,
	min(m.price) AS min_price
FROM 
	person_order po 
JOIN
	menu m ON po.menu_id = m.id 
JOIN 
	pizzeria p ON m.pizzeria_id = p.id 
GROUP BY 
	1
ORDER BY 
	1
