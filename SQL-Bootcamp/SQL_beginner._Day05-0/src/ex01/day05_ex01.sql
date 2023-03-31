SET enable_seqscan = off;

EXPLAIN ANALYZE
    SELECT 
    	m.pizza_name, 
    	p2.name AS pizzeria_name
    FROM 
    	pizzeria p2, 
    	menu m
    WHERE 
   		p2.id = m.pizzeria_id;

--   ->  Index Scan using pizzeria_pkey on pizzeria p2  (cost=0.15..2.57 rows=1 width=40) (actual time=0.002..0.002 rows=1 loops=20)
