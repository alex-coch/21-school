WITH pq AS (
SELECT 
	p.id 
FROM 
	person p 
WHERE 
	name = 'Andrey'
)
SELECT 
	p2.name AS pizzeria_name
FROM 
	person_visits pv
JOIN 
	pq p ON pv.person_id = p.id
JOIN 
	pizzeria p2 ON pv.pizzeria_id = p2.id
EXCEPT
SELECT 
	p2.name AS pizzeria_name
FROM 
	person_order po
JOIN 
	pq p ON po.person_id = p.id
JOIN 
	menu m ON po.menu_id = m.id
JOIN 
	pizzeria p2 ON p2.id = m.pizzeria_id
ORDER BY 
	pizzeria_name;
