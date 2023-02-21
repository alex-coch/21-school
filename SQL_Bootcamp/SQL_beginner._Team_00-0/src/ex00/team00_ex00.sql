CREATE TABLE IF NOT EXISTS cities (
    point1 VARCHAR NOT NULL,
    point2 VARCHAR NOT NULL,
    cost INT8 NOT NULL
);

INSERT INTO cities (point1, point2, cost)
VALUES ('a', 'b', 10),
       ('b', 'a', 10),
       ('a', 'd', 20),
       ('d', 'a', 20),
       ('a', 'c', 15),
       ('c', 'a', 15),
       ('b', 'c', 35),
       ('c', 'b', 35),
       ('d', 'b', 25),
       ('b', 'd', 25),
       ('d', 'c', 30),
       ('c', 'd', 30);

WITH RECURSIVE tours AS (
    SELECT point1 AS tour, point1, point2, cost, cost AS total_cost
    FROM cities
    WHERE point1 = 'a'

    UNION ALL

    SELECT concat(t.tour, ',', c.point1) AS traces, c.point1, c.point2, c.cost, t.total_cost + c.cost AS total_cost
    FROM cities AS c
    JOIN tours AS t ON c.point1 = t.point2
    WHERE tour NOT LIKE '%' || c.point1 || '%'
    )

SELECT total_cost, concat('{', tour, ',', point2, '}') AS tour
FROM tours
WHERE length(tour) = 7 AND point2 = 'a' AND total_cost IN (SELECT min(total_cost)
                                                           FROM tours
                                                           WHERE length(tour) = 7 AND point2 = 'a')
ORDER BY total_cost, tour
