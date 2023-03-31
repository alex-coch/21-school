-- Enter to session 1
SHOW TRANSACTION ISOLATION LEVEL;
START TRANSACTION;
UPDATE pizzeria SET rating = 5 WHERE name = 'Pizza Hut';  
SELECT * FROM pizzeria WHERE name  = 'Pizza Hut';  -- we've got rating = 5.0
-- Jump to session 2
COMMIT;
SELECT * FROM pizzeria WHERE name  = 'Pizza Hut';  -- we've got rating = 5.0
-- Jump to session 2 and repeat SELECT

-- Enter to session 2
SELECT * FROM pizzeria WHERE name  = 'Pizza Hut';  -- we've got rating = 4.6
-- Jump to session 1 and proceed from COMMIT command
SELECT * FROM pizzeria WHERE name  = 'Pizza Hut';  -- we've got rating = 5.0
