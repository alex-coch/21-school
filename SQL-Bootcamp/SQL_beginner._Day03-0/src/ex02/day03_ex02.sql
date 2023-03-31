WITH iq AS (
    SELECT 
		m.id AS menu_id 
	FROM 
		menu m
	EXCEPT
	SELECT 
		po.menu_id 
	FROM 
		person_order po
	ORDER BY 
		menu_id
	)
SELECT 
	m.pizza_name, 
	m.price, 
	p.name AS pizzeria_name
FROM 
	iq
JOIN 
	menu m ON iq.menu_id = m.id
JOIN 
	pizzeria p on m.pizzeria_id = p.id
ORDER BY 
	pizza_name, 
	price;
