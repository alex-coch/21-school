-- Session #1
BEGIN TRANSACTION;
SET TRANSACTION ISOLATION LEVEL SERIALIZABLE;
SHOW TRANSACTION ISOLATION LEVEL;
-- Session #2
BEGIN TRANSACTION;
SET TRANSACTION ISOLATION LEVEL SERIALIZABLE;
SHOW TRANSACTION ISOLATION LEVEL;
-- Session #1
SELECT * FROM pizzeria WHERE name  = 'Pizza Hut';
-- Session #2
UPDATE pizzeria SET rating = 3.0 WHERE name = 'Pizza Hut';
-- Session #2
COMMIT;
-- Session #1
SELECT * FROM pizzeria WHERE name  = 'Pizza Hut';
-- Session #1
COMMIT;
-- Session #1
SELECT * FROM pizzeria WHERE name  = 'Pizza Hut';
-- Session #2
SELECT * FROM pizzeria WHERE name  = 'Pizza Hut';
