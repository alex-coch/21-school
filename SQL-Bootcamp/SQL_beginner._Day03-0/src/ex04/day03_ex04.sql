WITH iq AS (
    SELECT 
    	p2.name AS pizzeria_name,
    	p.gender
    FROM 
    	person_order po
    JOIN 
    	person p ON po.person_id = p.id
    JOIN 
    	menu m ON po.menu_id = m.id
    JOIN 
    	pizzeria p2 ON m.pizzeria_id = p2.id
)
(
SELECT 
	pizzeria_name 
FROM 
	iq 
EXCEPT
SELECT 
	pizzeria_name 
FROM 
	iq
WHERE 
	gender = 'male'
)
UNION 
(
SELECT 
	pizzeria_name 
FROM 
	iq  
EXCEPT
SELECT 
	pizzeria_name 
FROM 
	iq
WHERE 
	gender = 'female'
)
ORDER BY 
	pizzeria_name;
