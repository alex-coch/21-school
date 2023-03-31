SELECT 
	name
FROM 
	pizzeria p 
WHERE 
	id NOT IN 
(
SELECT 
	pizzeria_id
FROM 
	person_visits pv 
);

SELECT 
	p.name
FROM   
	pizzeria p 
LEFT JOIN
	person_visits pv 
ON p.id = pv.pizzeria_id 
WHERE  
	(pv.pizzeria_id is NULL) 
	AND EXISTS
(
SELECT 
	p."name" 
FROM 
	pizzeria p 
LEFT JOIN
	person_visits pv 
ON p.id = pv.pizzeria_id 
WHERE  
	pv.pizzeria_id is NULL
)  
