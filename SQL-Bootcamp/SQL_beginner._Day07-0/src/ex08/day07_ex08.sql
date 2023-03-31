SELECT 
	p.address, 
	p2.name, 
	COUNT(m.pizzeria_id) AS count_of_orders
FROM 
	person_order po
JOIN 
	menu m ON m.id = po.menu_id
JOIN 
	pizzeria p2 ON p2.id = m.pizzeria_id
JOIN 
	person p ON p.id = po.person_id
GROUP BY 
	p.address, 
	p2.name
ORDER BY 
	p.address, 
	p2.name;
