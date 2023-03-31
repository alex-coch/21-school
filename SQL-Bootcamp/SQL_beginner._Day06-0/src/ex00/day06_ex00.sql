DROP TABLE IF EXISTS person_discounts;

CREATE TABLE person_discounts(
    id INT8 PRIMARY KEY,
    person_id INT8 NOT NULL,
    pizzeria_id INT8 NOT NULL,
    discount NUMERIC NOT NULL DEFAULT 0,
    CONSTRAINT fk_person_discounts_person_id FOREIGN KEY (person_id) REFERENCES person(id),
    CONSTRAINT fk_person_discounts_pizzeria_id FOREIGN KEY (pizzeria_id) REFERENCES pizzeria(id)
    );
