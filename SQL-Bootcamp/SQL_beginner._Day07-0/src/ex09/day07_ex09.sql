SELECT 
	address, 
	formula, 
	average,
    CASE
    	WHEN formula > average THEN true
        ELSE false
    END AS comparison
FROM 
	(
	SELECT 
		address, 
		ROUND(MAX(age::NUMERIC) - MIN(age::NUMERIC)/MAX(age::NUMERIC), 2) AS formula,
        ROUND(AVG(age), 2) AS average
    FROM 
    	person
    GROUP BY 
    	address
    ) AS a
ORDER BY 
	address
