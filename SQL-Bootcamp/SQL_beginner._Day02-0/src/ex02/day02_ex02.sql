SELECT 
	COALESCE(person_name, NULL, '-') AS person_name, 
	visit_date, 
	COALESCE(NULL, name, '-') AS pizzeria_name
FROM 
(SELECT person_visits.person_id, pizzeria_id, visit_date, name AS person_name
    FROM (SELECT *
          FROM 
          	person_visits
          WHERE 
          	visit_date BETWEEN '2022-01-01' AND '2022-01-03') as person_visits
    FULL JOIN person
    ON person.id =  person_visits.person_id) AS pt
FULL JOIN 
	pizzeria
ON 
	pizzeria.id =  pt.pizzeria_id
ORDER BY 
	person_name, visit_date, pizzeria_name
