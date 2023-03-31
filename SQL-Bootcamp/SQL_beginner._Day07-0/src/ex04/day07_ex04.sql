SELECT 
	p."name", 
	count(pv.person_id) AS count_of_visits
FROM 
	person_visits pv 
JOIN
	person p ON p.id = pv.person_id 
GROUP BY 
	p."name"
HAVING 
	count(pv.person_id) > 3
	