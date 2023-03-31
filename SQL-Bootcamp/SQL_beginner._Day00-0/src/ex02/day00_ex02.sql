SELECT 
	name, rating  
FROM 
	pizzeria p
WHERE 
	rating >= 3.5 AND rating <= 5.0 
ORDER BY 
	rating;
	
SELECT 
	name, rating  
FROM 
	pizzeria p
WHERE 
	rating between 3.5 AND 5.0 
ORDER BY 
	rating;
