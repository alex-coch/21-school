WITH t
     AS (SELECT COALESCE(u.NAME, 'not defined')     AS NAME,
                COALESCE(u.lastname, 'not defined') AS lastname,
                b.type,
                Sum(b.money)                        AS volume,
                currency_id
         FROM   balance b
                LEFT JOIN currency c
                       ON c.id = b.currency_id
                          AND c.updated = b.updated
                LEFT JOIN "user" u
                       ON u.id = b.user_id
         GROUP  BY u.id,
                   b.type,
                   b.currency_id),
     l
     AS (SELECT c.id,
                Max(c.updated) AS updated
         FROM   currency c
         GROUP  BY c.id),
     lc
     AS (SELECT c.*
         FROM   currency c
                RIGHT JOIN l
                        ON c.id = l.id
                           AND c.updated = l.updated)
SELECT t.NAME,
       t.lastname,
       t.type,
       t.volume,
       COALESCE(lc.NAME, 'not defined')       AS currency_name,
       COALESCE(lc.rate_to_usd, 1)            AS last_rate_to_usd,
       t.volume * COALESCE(lc.rate_to_usd, 1) AS total_volume_in_usd
FROM   t
       LEFT JOIN lc
              ON lc.id = t.currency_id
ORDER  BY NAME DESC,
          lastname ASC,
          type ASC;
