DROP TABLE student_unit;
DROP TABLE student;
DROP TABLE course;
DROP TABLE unit;
DROP TABLE department;

CREATE TABLE department(
	id INT AUTO_INCREMENT,
    name VARCHAR(128),
    dep_code VARCHAR(64) UNIQUE,
    creation_date DATE NOT NULL,
    PRIMARY KEY (id)
);

CREATE TABLE course(
	id INT AUTO_INCREMENT PRIMARY KEY,
	id_department INT,
	name VARCHAR(128),
    creation_date DATE,
    FOREIGN KEY (id_department) REFERENCES department(id)
);

CREATE TABLE student(
	id INT AUTO_INCREMENT PRIMARY KEY,
    id_course INT,
    name VARCHAR(128),
    number INT UNIQUE,
    address VARCHAR(255),
    city VARCHAR(64),
    enroll_date DATE,
    CONSTRAINT fk_st_id_course FOREIGN KEY (id_course) REFERENCES course(id)
);

CREATE TABLE unit(
	id INT PRIMARY KEY,
    department_id INT,
    name VARCHAR(127),
    credits INT NOT NULL,
    FOREIGN KEY (department_id) REFERENCES department(id)
);

CREATE TABLE student_unit(
	id INT PRIMARY KEY,
    student_id INT,
    unit_id INT,
    start_date DATE NOT NULL,
    end_date DATE,
    grade INTEGER,
    CHECK(grade >= 0 AND grade <= 20),
    FOREIGN KEY (student_id) REFERENCES student(id),
    FOREIGN KEY (unit_id) REFERENCES department(id)
);


#INSERT INTO department (name, dep_code, creation_date)
#VALUES
#("DEEC", "123ABC", "1998-01-01"),
#("DI", "123FGH", "1992-01-01"),
#("DM", "123IJK", "1990-01-01");
#SELECT * FROM department;
