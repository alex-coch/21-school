CREATE OR REPLACE FUNCTION fnc_person_visits_and_eats_on_date(IN pperson VARCHAR DEFAULT 'Dmitriy',
    IN pprice NUMERIC DEFAULT 500, IN pdate date DEFAULT '2022-01-08')
    RETURNS TABLE(
        pizzeria_name varchar
    ) AS
$$
BEGIN
    RETURN QUERY
    SELECT DISTINCT pizzeria.name AS pizzeria_name
    FROM person_order
    LEFT JOIN menu ON menu.id = person_order.menu_id
    INNER JOIN person_visits ON person_visits.person_id = person_order.person_id AND
                                person_visits.pizzeria_id = menu.pizzeria_id AND
                                person_visits.visit_date = person_order.order_date
    LEFT JOIN person ON person.id = person_visits.person_id
    LEFT JOIN pizzeria ON person_visits.pizzeria_id = pizzeria.id
    WHERE person.name = pperson AND menu.price <= pprice AND order_date = pdate;
END;
$$ LANGUAGE plpgsql;

select * 
from fnc_person_visits_and_eats_on_date(pprice := 800);

select * 
from fnc_person_visits_and_eats_on_date(pperson := 'Anna',pprice := 1300,pdate := '2022-01-01');
