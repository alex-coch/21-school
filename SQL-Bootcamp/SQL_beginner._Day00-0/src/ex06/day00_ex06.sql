SELECT 
	(SELECT CASE WHEN name = 'Denis' THEN  TRUE ELSE FALSE END AS check_name FROM person p WHERE id=a.po_id)
FROM 
	(SELECT person_id as po_id FROM person_order po WHERE (id = 13 OR id = 14 OR id = 18) AND order_date = '2022-01-07') a
