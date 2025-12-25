-- ==============================
-- IntelliCare HIS Database Setup
-- Team: GeekyCoders
-- PS03: Hospital Information System
-- ==============================

-- Create Database
CREATE DATABASE IF NOT EXISTS intellicare_his;
USE intellicare_his;

-- ==============================
-- PATIENTS TABLE
-- ==============================
CREATE TABLE patients (
    id INT AUTO_INCREMENT PRIMARY KEY,
    patient_id VARCHAR(20) NOT NULL UNIQUE,
    name VARCHAR(100) NOT NULL,
    age INT NOT NULL,
    gender CHAR(1) NOT NULL,
    diagnosis VARCHAR(255),
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- ==============================
-- DEPARTMENTS TABLE
-- ==============================
CREATE TABLE departments (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100) NOT NULL
);

-- Insert default departments
INSERT INTO departments (name) VALUES
('Emergency'),
('Cardiology'),
('Radiology'),
('Pediatrics'),
('Orthopedics'),
('Neurology'),
('Oncology'),
('General Medicine'),
('ICU'),
('Pharmacy');

-- ==============================
-- DEPARTMENT GRAPH EDGES (BFS)
-- ==============================
CREATE TABLE department_edges (
    id INT AUTO_INCREMENT PRIMARY KEY,
    from_dept INT NOT NULL,
    to_dept INT NOT NULL,
    FOREIGN KEY (from_dept) REFERENCES departments(id),
    FOREIGN KEY (to_dept) REFERENCES departments(id)
);

-- Sample connectivity (undirected graph)
INSERT INTO department_edges (from_dept, to_dept) VALUES
(1,2), (1,3),
(2,4), (2,5),
(3,6),
(4,7),
(5,8),
(6,9),
(7,10);

-- ==============================
-- APPOINTMENTS TABLE
-- ==============================
CREATE TABLE appointments (
    id INT AUTO_INCREMENT PRIMARY KEY,
    patient_id VARCHAR(20) NOT NULL,
    department_id INT NOT NULL,
    priority INT NOT NULL CHECK (priority BETWEEN 1 AND 5),
    status ENUM('scheduled','processed') DEFAULT 'scheduled',
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (patient_id) REFERENCES patients(patient_id),
    FOREIGN KEY (department_id) REFERENCES departments(id)
);

-- ==============================
-- ROOMS TABLE (IPD)
-- ==============================
CREATE TABLE rooms (
    id INT AUTO_INCREMENT PRIMARY KEY,
    room_number INT NOT NULL UNIQUE,
    occupied TINYINT(1) DEFAULT 0,
    patient_id VARCHAR(20),
    FOREIGN KEY (patient_id) REFERENCES patients(patient_id)
);

-- Insert sample rooms (101–120)
INSERT INTO rooms (room_number, occupied) VALUES
(101,0),(102,0),(103,0),(104,0),(105,0),
(106,0),(107,0),(108,0),(109,0),(110,0),
(111,0),(112,0),(113,0),(114,0),(115,0),
(116,0),(117,0),(118,0),(119,0),(120,0);

-- ==============================
-- OPTIONAL SAMPLE DATA (FOR DEMO)
-- ==============================
INSERT INTO patients (patient_id, name, age, gender, diagnosis) VALUES
('P1001','Demo Patient',45,'M','Fever');

INSERT INTO appointments (patient_id, department_id, priority) VALUES
('P1001',1,1);

-- ==============================
-- END OF SCRIPT
-- ==============================
