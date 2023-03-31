SELECT 
	p.name, 
	m.pizza_name, 
	m.price,
    (m.price * (1 - pd.discount/100)) AS discount_price, 
    p2.name AS pizzeria_name
FROM 
	person_order po
JOIN 
	person p ON po.person_id = p.id
JOIN 
	menu m ON m.id = po.menu_id
JOIN 
	pizzeria p2 ON p2.id = m.pizzeria_id
JOIN 
	person_discounts pd ON pd.person_id = po.person_id 
AND
    pd.pizzeria_id = m.pizzeria_id
ORDER BY 
	name, pizza_name;
