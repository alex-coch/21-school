(
SELECT 
	p2.name, 
	pvc.count, 
	'visit' AS action_type
FROM 
	(SELECT pizzeria_id, COUNT(pizzeria_id) AS count
      FROM person_visits
      GROUP BY pizzeria_id) AS pvc
JOIN 
	pizzeria p2 ON p2.id = pvc.pizzeria_id
ORDER BY 
	count DESC
LIMIT 
	3
)
UNION ALL
(
SELECT 
	p2.name, 
	poc.count, 
	'order' AS action_type
FROM
	(SELECT pizzeria_id, COUNT(pizzeria_id) AS count
     FROM person_order LEFT JOIN menu ON menu.id = person_order.menu_id
     GROUP BY pizzeria_id) AS poc
JOIN 
	pizzeria p2 ON p2.id = poc.pizzeria_id
ORDER BY 
	count DESC
LIMIT 
	3
)
ORDER BY 
	action_type ASC, 
	count DESC;
