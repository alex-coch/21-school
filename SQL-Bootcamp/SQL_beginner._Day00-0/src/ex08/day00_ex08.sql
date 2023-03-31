SELECT 
	*
FROM 
	person_order po 
WHERE 
	id % 2 = 0
ORDER BY 
	id
