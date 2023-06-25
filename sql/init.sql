-- Active: 1672402019146@@127.0.0.1@3306@employee_manage
CREATE DATABASE employee_manage
    DEFAULT CHARACTER SET = 'utf8mb4'; 

USE employee_manage;


CREATE TABLE employee (
    employee_id INT PRIMARY KEY AUTO_INCREMENT,
    `name` VARCHAR(10),
    sex CHAR(1),
    age TINYINT,
    phone_number VARCHAR(15),
    hire_date DATE,
    education_backgroud VARCHAR(10),
    job_title VARCHAR(10),
    department_id INT,
    salary DECIMAL(10, 2)
) AUTO_INCREMENT = 20230001;

CREATE TABLE department (
    department_id INT PRIMARY KEY AUTO_INCREMENT,
    department_name VARCHAR(15),
    manager_id INT
) AUTO_INCREMENT = 1;
-- 插入部门经理
INSERT INTO department(department_name, manager_id)
VALUES('IT', 20220001),
('行政部', 20220002),
('人力资源部', 20220003),
('市场部', 20220004),
('会计部', 20220005);
CREATE TABLE user (
    `user_name` VARCHAR(20) PRIMARY KEY,
    `password` VARCHAR(40) NOT NULL -- SHA加密后为40个字符
);
INSERT INTO  VALUES('admin', SHA1("admin"));
-- 检查登录的存储函数
SET GLOBAL log_bin_trust_function_creators = 1;
DELIMITER $
CREATE FUNCTION check_login(uname VARCHAR(20) , pwd VARCHAR(40))
RETURNS BOOLEAN
BEGIN
    RETURN (
        SELECT TRUE FROM `user` 
        WHERE `user_name` = uname AND `password` = SHA1(pwd)
    );
END $
DELIMITER ;
DELIMITER $
CREATE PROCEDURE insert_employee(emp_name VARCHAR(10), emp_sex CHAR(1), 
    emp_age TINYINT, phNum VARCHAR(15), edubkg VARCHAR(10), 
    jt VARCHAR(10), dept_id INT, sal DECIMAL(10, 2))
BEGIN
    INSERT INTO employee(`name`, sex, age, phone_number, hire_date,
        education_backgroud, job_title, department_id, salary) 
    VALUES(emp_name, emp_sex, emp_age, phNum ,
     CURRENT_DATE(),
         edubkg, jt, dept_id, sal);
END $
DELIMITER ;





CREATE VIEW emp_viw
AS  
SELECT e.employee_id, e.name, e.sex, e.age,
e.phone_number, e.hire_date,
e.education_backgroud, e.job_title,
d.department_name, e.salary
FROM employee as e JOIN department AS d
ON e.department_id = d.department_id;




-- 更新
DELIMITER $
CREATE PROCEDURE update_employee(emp_id INT, emp_name VARCHAR(10), emp_sex CHAR(1), 
    emp_age TINYINT, phNum VARCHAR(15), edubkg VARCHAR(10), 
    jt VARCHAR(10), dept_id INT, sal DECIMAL(10, 2))
BEGIN
    UPDATE employee 
    SET name = emp_name, sex = emp_sex, age = emp_age,
    phone_number = phNum, education_backgroud = edubkg, job_title =jt,
    department_id = dept_id, salary = sal
    WHERE employee_id = emp_id;
END $
DELIMITER ;





DELIMITER $
CREATE PROCEDURE query_employee (
    emp_name VARCHAR(10),
    low_salary DECIMAL(10, 2),
    high_salary DECIMAL(10, 2),
    dept_name VARCHAR(15)
)
BEGIN
    SELECT * FROM emp_viw
    WHERE name = emp_name
    UNION
    SELECT * FROM emp_viw
    WHERE salary BETWEEN low_salary AND high_salary
    UNION
    SELECT * FROM emp_viw
    WHERE department_name = dept_name; 
END $
DELIMITER ;


DELIMITER $
CREATE PROCEDURE query_employee_count (
    emp_name VARCHAR(10),
    low_salary DECIMAL(10, 2),
    high_salary DECIMAL(10, 2),
    dept_name VARCHAR(15)
)
BEGIN
    SELECT COUNT(*) FROM (
        SELECT * FROM emp_viw
        WHERE name = emp_name
        UNION
        SELECT * FROM emp_viw
        WHERE salary BETWEEN low_salary AND high_salary
        UNION
        SELECT * FROM emp_viw
        WHERE department_name = dept_name
    ) AS a;
    
END $
DELIMITER ;


