-- Smart MA.VI Manager Database Initialization Script
-- This script creates the initial database structure and default data

-- Create default admin user
INSERT OR REPLACE INTO users (username, password_hash, role) 
VALUES ('admin', 'admin123', 'admin');

-- Insert sample classes
INSERT OR REPLACE INTO classes (id, name, grade, capacity, room_number, teacher_id, description, is_active) VALUES
(1, 'Class A', 1, 40, 'Room 101', 0, 'Grade 1 Class A', 1),
(2, 'Class B', 1, 35, 'Room 102', 0, 'Grade 1 Class B', 1),
(3, 'Class A', 2, 40, 'Room 201', 0, 'Grade 2 Class A', 1),
(4, 'Class B', 2, 35, 'Room 202', 0, 'Grade 2 Class B', 1),
(5, 'Class A', 3, 40, 'Room 301', 0, 'Grade 3 Class A', 1),
(6, 'Class B', 3, 35, 'Room 302', 0, 'Grade 3 Class B', 1),
(7, 'Class A', 4, 40, 'Room 401', 0, 'Grade 4 Class A', 1),
(8, 'Class B', 4, 35, 'Room 402', 0, 'Grade 4 Class B', 1),
(9, 'Class A', 5, 40, 'Room 501', 0, 'Grade 5 Class A', 1),
(10, 'Class B', 5, 35, 'Room 502', 0, 'Grade 5 Class B', 1);

-- Insert sample teachers
INSERT OR REPLACE INTO teachers (id, name, subject, contact, email, address, assigned_class, join_date, is_active) VALUES
(1, 'Mr. Ram Bahadur', 'Mathematics', '+977123456789', 'ram.bahadur@school.edu.np', 'Kathmandu, Nepal', 1, '2024-01-01', 1),
(2, 'Mrs. Sita Devi', 'English', '+977987654321', 'sita.devi@school.edu.np', 'Lalitpur, Nepal', 2, '2024-01-01', 1),
(3, 'Mr. Hari Prasad', 'Science', '+977112233445', 'hari.prasad@school.edu.np', 'Bhaktapur, Nepal', 3, '2024-01-01', 1),
(4, 'Ms. Gita Kumari', 'Nepali', '+977556677889', 'gita.kumari@school.edu.np', 'Kathmandu, Nepal', 4, '2024-01-01', 1),
(5, 'Mr. Krishna Kumar', 'Social Studies', '+977998877665', 'krishna.kumar@school.edu.np', 'Lalitpur, Nepal', 5, '2024-01-01', 1);

-- Insert sample students
INSERT OR REPLACE INTO students (id, roll_no, name, class_id, guardian_name, guardian_contact, guardian_email, address, date_of_birth, gender, admission_date, is_active) VALUES
(1, 'ST001', 'Aarav Sharma', 1, 'Rajesh Sharma', '+977111111111', 'rajesh.sharma@email.com', 'Kathmandu, Nepal', '2017-05-15', 'Male', '2024-01-01', 1),
(2, 'ST002', 'Ananya Patel', 1, 'Priya Patel', '+977222222222', 'priya.patel@email.com', 'Lalitpur, Nepal', '2017-08-20', 'Female', '2024-01-01', 1),
(3, 'ST003', 'Arjun Singh', 2, 'Vikram Singh', '+977333333333', 'vikram.singh@email.com', 'Bhaktapur, Nepal', '2017-03-10', 'Male', '2024-01-01', 1),
(4, 'ST004', 'Zara Khan', 2, 'Ahmed Khan', '+977444444444', 'ahmed.khan@email.com', 'Kathmandu, Nepal', '2017-11-25', 'Female', '2024-01-01', 1),
(5, 'ST005', 'Vivaan Gupta', 3, 'Rahul Gupta', '+977555555555', 'rahul.gupta@email.com', 'Lalitpur, Nepal', '2016-07-12', 'Male', '2024-01-01', 1),
(6, 'ST006', 'Aisha Joshi', 3, 'Sunil Joshi', '+977666666666', 'sunil.joshi@email.com', 'Bhaktapur, Nepal', '2016-09-30', 'Female', '2024-01-01', 1),
(7, 'ST007', 'Advait Reddy', 4, 'Krishna Reddy', '+977777777777', 'krishna.reddy@email.com', 'Kathmandu, Nepal', '2016-12-05', 'Male', '2024-01-01', 1),
(8, 'ST008', 'Kiara Verma', 4, 'Raj Verma', '+977888888888', 'raj.verma@email.com', 'Lalitpur, Nepal', '2016-04-18', 'Female', '2024-01-01', 1),
(9, 'ST009', 'Dhruv Malhotra', 5, 'Amit Malhotra', '+977999999999', 'amit.malhotra@email.com', 'Bhaktapur, Nepal', '2015-10-22', 'Male', '2024-01-01', 1),
(10, 'ST010', 'Myra Kapoor', 5, 'Vikram Kapoor', '+977000000000', 'vikram.kapoor@email.com', 'Kathmandu, Nepal', '2015-06-14', 'Female', '2024-01-01', 1);

-- Insert sample holidays for 2024
INSERT OR REPLACE INTO holidays (date, description) VALUES
('2024-01-15', 'Maghe Sankranti'),
('2024-02-19', 'Shivaratri'),
('2024-03-25', 'Ram Navami'),
('2024-04-09', 'Nepali New Year'),
('2024-05-01', 'Labor Day'),
('2024-06-15', 'Eid al-Fitr'),
('2024-07-16', 'Guru Purnima'),
('2024-08-26', 'Krishna Janmashtami'),
('2024-09-17', 'Indra Jatra'),
('2024-10-02', 'Dashain'),
('2024-11-01', 'Tihar'),
('2024-12-25', 'Christmas');

-- Insert sample events
INSERT OR REPLACE INTO events (date, title, description) VALUES
('2024-01-20', 'Parent-Teacher Meeting', 'First parent-teacher meeting of the year'),
('2024-02-15', 'Annual Sports Day', 'Annual sports competition for all grades'),
('2024-03-10', 'Science Fair', 'Student science project exhibition'),
('2024-04-20', 'Cultural Program', 'Nepali New Year cultural celebration'),
('2024-05-15', 'Mid-Term Exams', 'Mid-term examination period'),
('2024-06-20', 'Annual Day', 'School annual day celebration'),
('2024-07-25', 'Art Competition', 'Inter-class art and craft competition'),
('2024-08-30', 'Independence Day', 'Independence day celebration'),
('2024-09-25', 'Dashain Celebration', 'Dashain festival celebration at school'),
('2024-10-15', 'Tihar Celebration', 'Tihar festival celebration at school'),
('2024-11-20', 'Final Exams', 'Final examination period'),
('2024-12-20', 'Winter Break', 'School closes for winter vacation');

-- Update class teacher assignments
UPDATE classes SET teacher_id = 1 WHERE id = 1;
UPDATE classes SET teacher_id = 2 WHERE id = 2;
UPDATE classes SET teacher_id = 3 WHERE id = 3;
UPDATE classes SET teacher_id = 4 WHERE id = 4;
UPDATE classes SET teacher_id = 5 WHERE id = 5;

-- Insert sample attendance for today (if not already present)
-- This would typically be done by the application, but we'll add some sample data
INSERT OR IGNORE INTO attendance (student_id, class_id, date, status, remarks) VALUES
(1, 1, date('now'), 0, 'Present'),
(2, 1, date('now'), 0, 'Present'),
(3, 2, date('now'), 0, 'Present'),
(4, 2, date('now'), 1, 'Absent - Sick'),
(5, 3, date('now'), 0, 'Present'),
(6, 3, date('now'), 0, 'Present'),
(7, 4, date('now'), 2, 'Leave - Family function'),
(8, 4, date('now'), 0, 'Present'),
(9, 5, date('now'), 0, 'Present'),
(10, 5, date('now'), 3, 'Late - Traffic');

-- Create indexes for better performance
CREATE INDEX IF NOT EXISTS idx_students_class_id ON students(class_id);
CREATE INDEX IF NOT EXISTS idx_teachers_assigned_class ON teachers(assigned_class);
CREATE INDEX IF NOT EXISTS idx_attendance_date ON attendance(date);
CREATE INDEX IF NOT EXISTS idx_attendance_student_id ON attendance(student_id);
CREATE INDEX IF NOT EXISTS idx_attendance_class_id ON attendance(class_id);
CREATE INDEX IF NOT EXISTS idx_holidays_date ON holidays(date);
CREATE INDEX IF NOT EXISTS idx_events_date ON events(date);
CREATE INDEX IF NOT EXISTS idx_users_username ON users(username);

-- Update database version
PRAGMA user_version = 1;
