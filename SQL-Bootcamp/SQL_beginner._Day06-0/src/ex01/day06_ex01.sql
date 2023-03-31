INSERT INTO  
	person_discounts
SELECT 
	ROW_NUMBER() OVER(ORDER BY po.person_id, m.pizzeria_id) AS id, 
	po.person_id AS person_id,
    m.pizzeria_id AS pizzeria_id,
    CASE
    	WHEN count(m.pizzeria_id) = 1 THEN 10.5
        WHEN count(m.pizzeria_id) = 2 THEN 22
        ELSE 30
    END AS discount
FROM 
	person_order po 
JOIN 
	menu m ON po.menu_id = m.id
GROUP BY 
	person_id, m.pizzeria_id;
