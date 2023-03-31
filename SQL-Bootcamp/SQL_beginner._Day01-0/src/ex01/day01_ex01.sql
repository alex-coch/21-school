SELECT s.object_name
FROM 
(SELECT 
	2, m.pizza_name AS object_name 
FROM 
	menu AS m
UNION ALL
SELECT 
	1, p.name AS object_name
FROM
	person AS p 
ORDER BY 
	1, object_name) s
