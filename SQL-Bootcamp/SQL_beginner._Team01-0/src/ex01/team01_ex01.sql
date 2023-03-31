insert into currency values (100, 'EUR', 0.85, '2022-01-01 13:29');
insert into currency values (100, 'EUR', 0.79, '2022-01-08 13:29');
          
WITH c AS
(
         SELECT   c.id,
                  c.NAME
         FROM     currency c
         GROUP BY c.id,
                  c.NAME)
SELECT    COALESCE (u.NAME, 'not defined')    AS NAME,
          COALESCE(u.lastname, 'not defined') AS lastname,
          c.NAME                              AS currency_name,
          COALESCE(
                     (
                     SELECT   rate_to_usd
                     FROM     currency c
                     WHERE    b.currency_id = c.id
                     AND      c.updated < b.updated
                     ORDER BY c.updated DESC limit 1),
                   (
                            SELECT   rate_to_usd
                            FROM     currency c
                            WHERE    b.currency_id = c.id
                            AND      c.updated > b.updated
                            ORDER BY c.updated ASC limit 1))*money AS rate_to_usd
FROM      balance b
JOIN      c
ON        c.id = b.currency_id
LEFT JOIN "user" u
ON        u.id = b.user_id
ORDER BY  NAME DESC,
          lastname,
          currency_name;
