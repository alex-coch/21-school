COMMENT ON TABLE person_discounts IS 'Pizza discount regarding pizzeria by a person';
COMMENT ON COLUMN person_discounts.id IS 'Primary key';
COMMENT ON COLUMN person_discounts.person_id IS 'Foreign key person_id';
COMMENT ON COLUMN person_discounts.pizzeria_id IS 'Foreign key  pizzeria_id';
COMMENT ON COLUMN person_discounts.discount IS 'Discount in percents';
