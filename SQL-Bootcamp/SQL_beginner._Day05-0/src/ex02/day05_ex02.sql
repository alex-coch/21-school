CREATE INDEX idx_person_name ON person USING btree(UPPER(name));

SET enable_seqscan  = off;

EXPLAIN ANALYSE
    SELECT person.name FROM person ORDER BY UPPER(name);
