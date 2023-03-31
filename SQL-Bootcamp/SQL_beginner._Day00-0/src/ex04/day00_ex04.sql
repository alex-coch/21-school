SELECT 
	CONCAT(name, ' (age:', age, ',gender:''', gender, ''',address:''', address, ''')') AS person_information
FROM 
	person p 
ORDER BY 
	person_information
