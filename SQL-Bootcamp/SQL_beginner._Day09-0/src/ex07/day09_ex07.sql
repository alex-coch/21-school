CREATE OR REPLACE FUNCTION func_minimum(VARIADIC arr NUMERIC[]) RETURNS NUMERIC AS
$$
DECLARE
    x NUMERIC := arr[1];
BEGIN
    FOR counter IN 2..array_length(arr, 1)
    LOOP
        IF arr[counter] < x THEN x = arr[counter];
        END IF;
    end loop;
    return x;
END;
$$ LANGUAGE plpgsql;

SELECT func_minimum(VARIADIC arr => ARRAY[10.0, -1.0, 5.0, 4.4]);
