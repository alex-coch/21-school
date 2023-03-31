SELECT 
	(SELECT name FROM person p WHERE id=pv.person_id) AS person_name, 
	(SELECT name FROM pizzeria p2 WHERE id= pv.pizzeria_id) AS pizzeria_name 	
FROM 
	(SELECT person_id, pizzeria_id FROM person_visits) AS pv
