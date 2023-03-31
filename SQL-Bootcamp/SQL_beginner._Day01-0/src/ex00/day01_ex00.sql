SELECT 
	id AS object_id, pizza_name  AS object_name 
FROM 
	menu m 
UNION
SELECT 
	id AS object_id, name AS object_name
FROM
	person p 
ORDER BY 
	object_id, object_name
