/* CREATE TABLE */
CREATE TABLE student(
	st_number 	INTEGER,
    st_name 	VARCHAR(127),
    address 	VARCHAR(255),
    postal_code 	VARCHAR(10),
    city 		VARCHAR(64),
    st_email 	VARCHAR(64)
);

/* 1 - SHOW TABLE (DESCRIPTION)*/
describe student;


/* 2 - INSERT SOME STUDENTS IN THE TABLE */
INSERT INTO student(st_number, st_name, city)
VALUES 
(8001, "Jose Pires", "Lisboa"),
(8002, "Giovanni Marcheta", "Rome"),
(8003, "Maria Duarte", "Porto"),
(8004, "Catarina Silva", "Porto"),
(8005, "Francico Mendes", "Beja");

/* 3 - Visualize the inserted students */
/* ALL students*/
SELECT * FROM student;

/* SOME students */
SELECT st_number, st_name, city FROM student;

/* FILTER RESULT */
SELECT * FROM student WHERE st_number = 8001;


/* 4 - UPDATE  */
/* 4.1 UPDATE ONE COLUMN*/
UPDATE student SET address = "Rua Sobe e desce, 31 2Esq" WHERE st_number = 8001;
UPDATE student SET postal_code = "1234-123" WHERE st_number = 8001;

UPDATE student SET postal_code = NULL WHERE st_number = 8001;

/* 5 - DELETE */
DELETE FROM student WHERE st_number = 8005;



/* 7 - COSTRANINT
	NOT NULL,
    UNIQUE,
    PRIMARY KEY,
    FOREIGN KEY,
    CHECK,
    DEFAULT,
    CREATE INDEX
 */


/* 7.1 */
ALTER TABLE student ADD CONSTRAINT st_number_null_ctrl CHECK(st_number IS NOT NULL);

INSERT INTO student (st_name, city) VALUE ("Juvenal Baera", "Barreiro");

ALTER TABLE student ADD CONSTRAINT st_numer_unique_ctrl UNIQUE(st_number);

SELECT * FROM student;
DESC student;


CREATE TABLE unit_student(
	st_number INTEGER NOT NULL UNIQUE,
	unit_name VARCHAR(50) NOT NULL,
    grade INTEGER,
    PRIMARY KEY (st_number),
    CHECK(grade >= 0 AND grade <= 20)
);

/* EXERCÍCIOS */
INSERT INTO unit_student (st_number, unit_name)
VALUES
(8001, "Analise Matemática 1");

SELECT * FROM unit_student;