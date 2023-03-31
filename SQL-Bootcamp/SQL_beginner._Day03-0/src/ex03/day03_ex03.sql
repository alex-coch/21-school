WITH iq AS (
    SELECT 
    	p.gender, 
    	p2.name AS pizzeria_name
    FROM 
    	person_visits pv
    JOIN 
    	person p ON pv.person_id = p.id
    JOIN 
    	pizzeria p2 ON pv.pizzeria_id = p2.id
)
(SELECT 
	pizzeria_name 
FROM 
	iq 
WHERE 
	gender = 'female'
EXCEPT ALL
SELECT 
	pizzeria_name 
FROM 
	iq 
WHERE 
	gender = 'male')
UNION ALL
(SELECT 
	pizzeria_name 
FROM 
	iq
WHERE 
	gender = 'male'
EXCEPT ALL
SELECT 
	pizzeria_name 
FROM 
	iq 
WHERE 
	gender = 'female')
ORDER BY 
	pizzeria_name;
