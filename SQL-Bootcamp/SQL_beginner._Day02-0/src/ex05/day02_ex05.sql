SELECT 
	p."name" 
FROM 
	person p 
WHERE 
	p.age > 25 AND p.gender ='female'
ORDER BY
	p."name"
