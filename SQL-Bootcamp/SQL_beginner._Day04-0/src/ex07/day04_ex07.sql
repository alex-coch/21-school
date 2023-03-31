INSERT INTO 
	person_visits
VALUES (
    (SELECT MAX(id)+1 FROM person_visits),
    (SELECT id FROM person WHERE name = 'Dmitriy'),
    (SELECT id FROM pizzeria WHERE name = 'Dominos'),
    '2022-01-08'
 	);
INSERT INTO 
	menu
VALUES (
	(SELECT MAX(id)+1 FROM menu), 
	(SELECT id FROM pizzeria WHERE name = 'Dominos'), 
	'italian pizza', 
	750);

SELECT * FROM mv_dmitriy_visits_and_eats;

REFRESH MATERIALIZED VIEW mv_dmitriy_visits_and_eats;

SELECT * FROM mv_dmitriy_visits_and_eats;

