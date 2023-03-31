WITH iq AS (
    SELECT 
    	m.pizza_name, 
    	p."name", 
    	m.price, 
    	m.pizzeria_id
    FROM 
    	menu m
    LEFT JOIN 
    	pizzeria p ON m.pizzeria_id = p.id
)
SELECT 
	iq.pizza_name, 
	iq.name AS pizzeria_name_1, 
	iq2.name AS pizzeria_name_2, 
	iq.price
FROM 
	iq
JOIN 
	iq AS iq2
ON 
	iq.pizza_name = iq2.pizza_name 
AND 
	iq.price = iq2.price 
AND 
	iq.pizzeria_id > iq2.pizzeria_id
ORDER BY 
	pizza_name;
