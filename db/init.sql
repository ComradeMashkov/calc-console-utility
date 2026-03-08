CREATE DATABASE calculator_db;

\c calculator_db

CREATE TABLE operations (
    id BIGSERIAL PRIMARY KEY,
    operand1 BIGINT NOT NULL,
    operand2 BIGINT,
    operation VARCHAR(16) NOT NULL,
    result_int BIGINT,
    result_double DOUBLE PRECISION,
    status INTEGER NOT NULL,
    error_msg TEXT,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);