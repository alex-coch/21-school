SELECT 
	COALESCE(o.name, v.name) AS name, 
	(COALESCE(v.count, 0) + COALESCE(o.count, 0)) AS total_count
FROM 
	(SELECT pizzeria.name, pvc.count, 'v' AS action_type
      FROM (SELECT pizzeria_id, COUNT(pizzeria_id) AS count
            FROM person_visits
            GROUP BY pizzeria_id) AS pvc
      LEFT JOIN pizzeria ON pizzeria.id = pvc.pizzeria_id) as v
FULL JOIN
    (SELECT pizzeria.name, poc.count, 'order' AS action_type
    FROM(SELECT pizzeria_id, COUNT(pizzeria_id) AS count
         FROM person_order po LEFT JOIN menu ON menu.id = po.menu_id
         GROUP BY pizzeria_id) AS poc
    LEFT JOIN pizzeria ON pizzeria.id = poc.pizzeria_id) as o
ON o.name = v.name
ORDER BY 
	total_count DESC, 
	name ASC;
