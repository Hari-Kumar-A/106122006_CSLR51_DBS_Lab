-- Create Student table
CREATE TABLE Student (
    Std_rollno INT PRIMARY KEY,
    Std_name VARCHAR(50),
    Dept VARCHAR(50),
    Course1 CHAR(50),
    Course2 CHAR(50),
    Course3 CHAR(50),
    Course4 CHAR(50)
);

-- Insert 5 student records
INSERT INTO Student (Std_rollno, Std_name, Dept, Course1, Course2, Course3, Course4) VALUES
(1, 'Ram  ', 'Operating Systems', 'DBMS', 'OS', 'DS', 'Maths'),
(2, 'Jane Smith', 'ECE', 'Signals', 'Networks', 'Electronics', 'Maths'),
(3, 'Alice Johnson', 'MECH', 'Thermo', 'Fluid', 'Mechanical', 'Maths'),
(4, 'Bob Brown', 'CIVIL', 'Structures', 'Geo', 'Hydraulics', 'Maths'),
(5, 'Charlie Davis', 'EEE', 'Circuits', 'EMF', 'Power', 'Maths');

-- Drop Course2 and Course3 columns
ALTER TABLE Student
DROP COLUMN Course2;

ALTER TABLE Student
DROP COLUMN Course3;

-- Add DOB and email columns
ALTER TABLE Student
ADD DOB DATE NOT NULL,
ADD email VARCHAR(50) CONSTRAINT email_format CHECK (email LIKE '%@nitt.edu');

-- Change Course1 datatype to VARCHAR2
ALTER TABLE Student
MODIFY Course1 VARCHAR2(50);

-- Rename Std_rollno to Std_rno
ALTER TABLE Student
RENAME COLUMN Std_rollno TO Std_rno;

-- Update Course1 from 'DBMS' to 'OS'
UPDATE Student
SET Course1 = 'OS'
WHERE Course1 = 'DBMS';

-- Delete students with name starting with 'S'
DELETE FROM Student
WHERE Std_name LIKE 'S%';

-- Select students born after 2005
SELECT * FROM Student
WHERE DOB > '2005-12-31';

-- Simulate DROP TABLE
DROP TABLE Student;

-- Recreate the table to simulate TRUNCATE
CREATE TABLE Student (
    Std_rno INT PRIMARY KEY,
    Std_name VARCHAR(50),
    Dept VARCHAR(50),
    Course1 VARCHAR2(50),
    Course4 CHAR(50),
    DOB DATE NOT NULL,
    email VARCHAR(50) CONSTRAINT email_format CHECK (email LIKE '%@nitt.edu')
);

-- Simulate TRUNCATE
TRUNCATE TABLE Student;