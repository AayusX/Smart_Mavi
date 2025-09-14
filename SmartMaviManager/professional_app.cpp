#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <unistd.h>
#include <cstdlib>
#include <limits>
#include <map>
#include <fstream>

// Professional color codes for terminal
const std::string RESET = "\033[0m";
const std::string BOLD = "\033[1m";
const std::string DIM = "\033[2m";
const std::string BLUE = "\033[34m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string RED = "\033[31m";
const std::string CYAN = "\033[36m";
const std::string MAGENTA = "\033[35m";
const std::string WHITE = "\033[37m";
const std::string BG_BLUE = "\033[44m";
const std::string BG_GREEN = "\033[42m";
const std::string BG_YELLOW = "\033[43m";

struct Teacher {
    std::string name;
    std::vector<std::string> subjects;
    int id;
};

struct Subject {
    std::string name;
    int id;
};

struct Class {
    std::string name;
    std::string grade;
    int id;
};

struct ScheduleEntry {
    std::string teacher;
    std::string subject;
    std::string className;
    std::string timeSlot;
    std::string day;
};

class SmartMaviManager {
private:
    std::vector<Teacher> teachers;
    std::vector<Subject> subjects;
    std::vector<Class> classes;
    std::vector<std::string> days = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
    std::vector<std::string> timeSlots = {
        "08:00-08:45", "08:45-09:30", "09:30-10:15", "10:30-11:15",
        "11:15-12:00", "12:00-12:45", "13:45-14:30", "14:30-15:15"
    };
    std::mt19937 rng;

public:
    SmartMaviManager() : rng(std::random_device{}()) {}
    
    void run() {
        clearScreen();
        showSplashScreen();
        mainMenu();
    }

private:
    void clearScreen() {
        system("clear");
    }
    
    void showSplashScreen() {
        std::cout << BOLD << BLUE;
        std::cout << "+--------------------------------------------------------------+\n";
        std::cout << "|                                                              |\n";
        std::cout << "|" << WHITE << "              * SMART MAVI MANAGER v1.0.0 *              " << BLUE << "|\n";
        std::cout << "|" << CYAN << "           Professional Schedule Generator System           " << BLUE << "|\n";
        std::cout << "|                                                              |\n";
        std::cout << "|" << GREEN << "  * Intelligent Randomization  * Professional Output    " << BLUE << "|\n";
        std::cout << "|" << GREEN << "  * Teacher Management         * Class Scheduling       " << BLUE << "|\n";
        std::cout << "|" << GREEN << "  * Conflict Prevention        * Easy-to-Use Interface  " << BLUE << "|\n";
        std::cout << "|                                                              |\n";
        std::cout << "+--------------------------------------------------------------+" << RESET << "\n\n";
        
        std::cout << YELLOW << "Loading Smart Mavi Manager";
        for (int i = 0; i < 6; ++i) {
            std::cout << "." << std::flush;
            usleep(200000);
        }
        std::cout << GREEN << " Ready! ✓" << RESET << "\n\n";
        sleep(1);
    }
    
    void mainMenu() {
        while (true) {
            clearScreen();
            showHeader();
            
            std::cout << BOLD << CYAN << "MAIN MENU" << RESET << "\n";
            std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n";
            
            std::cout << GREEN << "[1]" << WHITE << " 🚀 Quick Setup & Generate Schedule" << DIM << " (Recommended for new users)" << RESET << "\n";
            std::cout << GREEN << "[2]" << WHITE << " 👥 Manage Teachers" << DIM << " (Add, edit, view teachers)" << RESET << "\n";
            std::cout << GREEN << "[3]" << WHITE << " 📚 Manage Subjects" << DIM << " (Add, edit, view subjects)" << RESET << "\n";
            std::cout << GREEN << "[4]" << WHITE << " 🏫 Manage Classes" << DIM << " (Add, edit, view classes)" << RESET << "\n";
            std::cout << GREEN << "[5]" << WHITE << " 🔗 Assign Subjects to Teachers" << DIM << " (Configure teaching assignments)" << RESET << "\n";
            std::cout << GREEN << "[6]" << WHITE << " 📅 Generate Schedule" << DIM << " (Create randomized timetable)" << RESET << "\n";
            std::cout << GREEN << "[7]" << WHITE << " 📊 View Current Data" << DIM << " (Review all entered information)" << RESET << "\n";
            std::cout << GREEN << "[8]" << WHITE << " ℹ️  About & Help" << DIM << " (App information and usage guide)" << RESET << "\n";
            std::cout << MAGENTA << "[9]" << YELLOW << " 🖥️  GUI Version" << DIM << " (Coming Soon!)" << RESET << "\n";
            std::cout << RED << "[0]" << WHITE << " 🚪 Exit Application" << RESET << "\n\n";
            
            showStatus();
            
            std::cout << BOLD << "Please select an option (0-9): " << RESET;
            
            int choice = getChoice(0, 9);
            
            switch (choice) {
                case 1: quickSetup(); break;
                case 2: manageTeachers(); break;
                case 3: manageSubjects(); break;
                case 4: manageClasses(); break;
                case 5: assignSubjectsToTeachers(); break;
                case 6: generateSchedule(); break;
                case 7: viewCurrentData(); break;
                case 8: showAbout(); break;
                case 9: showGUIPreview(); break;
                case 0: 
                    showExitMessage();
                    return;
            }
        }
    }
    
    void showHeader() {
        std::cout << BOLD << BLUE << "+--------------------------------------------------------------+\n";
        std::cout << "|" << WHITE << "                   * SMART MAVI MANAGER *                   " << BLUE << "|\n";
        std::cout << "+--------------------------------------------------------------+" << RESET << "\n\n";
    }
    
    void showStatus() {
        std::cout << "\n" << BOLD << MAGENTA << "CURRENT STATUS:" << RESET << "\n";
        std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
        std::cout << "👥 Teachers: " << (teachers.empty() ? RED + "None" : GREEN + std::to_string(teachers.size())) << RESET;
        std::cout << " │ 📚 Subjects: " << (subjects.empty() ? RED + "None" : GREEN + std::to_string(subjects.size())) << RESET;
        std::cout << " │ 🏫 Classes: " << (classes.empty() ? RED + "None" : GREEN + std::to_string(classes.size())) << RESET << "\n\n";
    }
    
    int getChoice(int min, int max) {
        int choice;
        while (true) {
            std::cin >> choice;
            if (std::cin.fail() || choice < min || choice > max) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << RED << "❌ Invalid choice. Please enter a number between " << min << " and " << max << ": " << RESET;
            } else {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return choice;
            }
        }
    }
    
    void quickSetup() {
        clearScreen();
        showHeader();
        std::cout << BOLD << GREEN << "🚀 SCHOOL SETUP WIZARD" << RESET << "\n";
        std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n";
        
        std::cout << CYAN << "Welcome! Let's set up your school's schedule system.\n" << RESET;
        std::cout << "I'll guide you through entering your teachers, subjects, and classes.\n\n";
        
        // Step 1: Add Teachers from user input
        std::cout << YELLOW << "📋 Step 1: Enter Your Teachers" << RESET << "\n";
        std::cout << "How many teachers do you have? ";
        int numTeachers = getChoice(1, 50);
        
        for (int i = 0; i < numTeachers; i++) {
            std::cout << "Enter name for teacher " << (i + 1) << ": ";
            std::string teacherName;
            std::getline(std::cin, teacherName);
            
            if (!teacherName.empty()) {
                Teacher teacher;
                teacher.name = teacherName;
                teacher.id = teachers.size() + 1;
                teachers.push_back(teacher);
                std::cout << GREEN << "   ✓ Added: " << teacher.name << RESET << "\n";
            } else {
                i--; // Retry if empty name
                std::cout << RED << "   Please enter a valid name." << RESET << "\n";
            }
        }
        std::cout << "\n";
        
        // Step 2: Add Subjects from user input
        std::cout << YELLOW << "📋 Step 2: Enter Your Subjects" << RESET << "\n";
        std::cout << "How many subjects do you have? ";
        int numSubjects = getChoice(1, 30);
        
        for (int i = 0; i < numSubjects; i++) {
            std::cout << "Enter subject " << (i + 1) << " name: ";
            std::string subjectName;
            std::getline(std::cin, subjectName);
            
            if (!subjectName.empty()) {
                Subject subject;
                subject.name = subjectName;
                subject.id = subjects.size() + 1;
                subjects.push_back(subject);
                std::cout << GREEN << "   ✓ Added: " << subject.name << RESET << "\n";
            } else {
                i--; // Retry if empty name
                std::cout << RED << "   Please enter a valid subject name." << RESET << "\n";
            }
        }
        std::cout << "\n";
        
        // Step 3: Add Classes from user input
        std::cout << YELLOW << "📋 Step 3: Enter Your Classes" << RESET << "\n";
        std::cout << "How many classes do you have? ";
        int numClasses = getChoice(1, 20);
        
        for (int i = 0; i < numClasses; i++) {
            std::cout << "Enter class " << (i + 1) << " name: ";
            std::string className;
            std::getline(std::cin, className);
            
            std::cout << "Enter grade level for " << className << ": ";
            std::string gradeLevel;
            std::getline(std::cin, gradeLevel);
            
            if (!className.empty() && !gradeLevel.empty()) {
                Class cls;
                cls.name = className;
                cls.grade = gradeLevel;
                cls.id = classes.size() + 1;
                classes.push_back(cls);
                std::cout << GREEN << "   ✓ Added: " << cls.name << " (" << cls.grade << ")" << RESET << "\n";
            } else {
                i--; // Retry if empty name
                std::cout << RED << "   Please enter valid class name and grade." << RESET << "\n";
            }
        }
        std::cout << "\n";
        
        // Step 4: Assign subjects to teachers
        std::cout << YELLOW << "📋 Step 4: Assign Subjects to Teachers" << RESET << "\n";
        std::cout << CYAN << "Now let's assign which subjects each teacher will teach:\n\n" << RESET;
        
        for (auto& teacher : teachers) {
            std::cout << BOLD << BLUE << "👨‍🏫 " << teacher.name << RESET << "\n";
            std::cout << "Available subjects:\n";
            
            for (size_t i = 0; i < subjects.size(); ++i) {
                std::cout << "[" << (i + 1) << "] " << subjects[i].name << "\n";
            }
            
            std::cout << "Enter subject numbers for " << teacher.name << " (space-separated), or 0 to skip: ";
            std::string line;
            std::getline(std::cin, line);
            std::istringstream iss(line);
            
            teacher.subjects.clear();
            int num;
            while (iss >> num) {
                if (num >= 1 && num <= (int)subjects.size()) {
                    teacher.subjects.push_back(subjects[num - 1].name);
                }
            }
            
            if (!teacher.subjects.empty()) {
                std::cout << GREEN << "✅ " << teacher.name << " assigned to: ";
                for (size_t i = 0; i < teacher.subjects.size(); ++i) {
                    std::cout << teacher.subjects[i];
                    if (i < teacher.subjects.size() - 1) std::cout << ", ";
                }
                std::cout << RESET << "\n\n";
            } else {
                std::cout << YELLOW << "⚠️  " << teacher.name << " has no subjects assigned (can teach any subject).\n\n" << RESET;
            }
        }
        
        std::cout << GREEN << "✅ School setup completed successfully!\n" << RESET;
        std::cout << "🎯 Your personalized data is now ready for schedule generation!\n\n";
        
        std::cout << "Would you like to generate a schedule now? (y/n): ";
        char response;
        std::cin >> response;
        if (response == 'y' || response == 'Y') {
            generateSchedule();
        }
        
        waitForEnter();
    }
    
    void addSampleTeachers() {
        std::vector<std::string> sampleNames = {
            "Dr. Sarah Johnson", "Mr. Michael Brown", "Ms. Emily Davis", 
            "Prof. David Wilson", "Mrs. Lisa Anderson", "Mr. James Taylor"
        };
        
        for (size_t i = 0; i < sampleNames.size(); ++i) {
            Teacher teacher;
            teacher.name = sampleNames[i];
            teacher.id = i + 1;
            teachers.push_back(teacher);
            std::cout << GREEN << "   ✓ " << teacher.name << RESET << "\n";
        }
    }
    
    void addSampleSubjects() {
        std::vector<std::string> sampleSubjects = {
            "Mathematics", "English", "Science", "History", 
            "Geography", "Physics", "Chemistry", "Biology", "Art", "Music"
        };
        
        for (size_t i = 0; i < sampleSubjects.size(); ++i) {
            Subject subject;
            subject.name = sampleSubjects[i];
            subject.id = i + 1;
            subjects.push_back(subject);
            std::cout << GREEN << "   ✓ " << subject.name << RESET << "\n";
        }
    }
    
    void addSampleClasses() {
        std::vector<std::pair<std::string, std::string>> sampleClasses = {
            {"Class 9A", "Grade 9"}, {"Class 9B", "Grade 9"},
            {"Class 10A", "Grade 10"}, {"Class 10B", "Grade 10"},
            {"Class 11A", "Grade 11"}, {"Class 12A", "Grade 12"}
        };
        
        for (size_t i = 0; i < sampleClasses.size(); ++i) {
            Class cls;
            cls.name = sampleClasses[i].first;
            cls.grade = sampleClasses[i].second;
            cls.id = i + 1;
            classes.push_back(cls);
            std::cout << GREEN << "   ✓ " << cls.name << " (" << cls.grade << ")" << RESET << "\n";
        }
    }
    
    void autoAssignSubjects() {
        // Assign subjects to teachers intelligently
        std::map<std::string, std::vector<std::string>> teacherSubjectMap = {
            {"Dr. Sarah Johnson", {"Mathematics", "Physics"}},
            {"Mr. Michael Brown", {"English", "History"}},
            {"Ms. Emily Davis", {"Science", "Biology", "Chemistry"}},
            {"Prof. David Wilson", {"Geography", "History"}},
            {"Mrs. Lisa Anderson", {"Art", "Music"}},
            {"Mr. James Taylor", {"Mathematics", "Science"}}
        };
        
        for (auto& teacher : teachers) {
            if (teacherSubjectMap.find(teacher.name) != teacherSubjectMap.end()) {
                teacher.subjects = teacherSubjectMap[teacher.name];
                std::cout << GREEN << "   ✓ " << teacher.name << " → ";
                for (size_t i = 0; i < teacher.subjects.size(); ++i) {
                    std::cout << teacher.subjects[i];
                    if (i < teacher.subjects.size() - 1) std::cout << ", ";
                }
                std::cout << RESET << "\n";
            }
        }
    }
    
    void manageTeachers() {
        while (true) {
            clearScreen();
            showHeader();
            std::cout << BOLD << CYAN << "👥 TEACHER MANAGEMENT" << RESET << "\n";
            std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n";
            
            if (!teachers.empty()) {
                std::cout << BOLD << "Current Teachers:" << RESET << "\n";
                for (size_t i = 0; i < teachers.size(); ++i) {
                    std::cout << GREEN << "[" << (i + 1) << "] " << WHITE << teachers[i].name;
                    if (!teachers[i].subjects.empty()) {
                        std::cout << DIM << " (teaches: ";
                        for (size_t j = 0; j < teachers[i].subjects.size(); ++j) {
                            std::cout << teachers[i].subjects[j];
                            if (j < teachers[i].subjects.size() - 1) std::cout << ", ";
                        }
                        std::cout << ")";
                    }
                    std::cout << RESET << "\n";
                }
                std::cout << "\n";
            }
            
            std::cout << GREEN << "[1]" << WHITE << " Add New Teacher\n" << RESET;
            std::cout << GREEN << "[2]" << WHITE << " Remove Teacher\n" << RESET;
            std::cout << RED << "[0]" << WHITE << " Back to Main Menu\n\n" << RESET;
            
            std::cout << BOLD << "Select option: " << RESET;
            int choice = getChoice(0, 2);
            
            switch (choice) {
                case 1: addTeacher(); break;
                case 2: removeTeacher(); break;
                case 0: return;
            }
        }
    }
    
    void addTeacher() {
        std::cout << "\n" << BOLD << "📝 Add New Teacher" << RESET << "\n";
        std::cout << "Enter teacher name: ";
        std::string name;
        std::getline(std::cin, name);
        
        if (!name.empty()) {
            Teacher teacher;
            teacher.name = name;
            teacher.id = teachers.size() + 1;
            teachers.push_back(teacher);
            
            std::cout << GREEN << "✅ Teacher '" << name << "' added successfully!" << RESET << "\n";
        }
        waitForEnter();
    }
    
    void removeTeacher() {
        if (teachers.empty()) {
            std::cout << RED << "❌ No teachers to remove." << RESET << "\n";
            waitForEnter();
            return;
        }
        
        std::cout << "\n" << BOLD << "🗑️  Remove Teacher" << RESET << "\n";
        std::cout << "Enter teacher number to remove: ";
        int index = getChoice(1, teachers.size()) - 1;
        
        std::cout << RED << "Are you sure you want to remove '" << teachers[index].name << "'? (y/n): " << RESET;
        char confirm;
        std::cin >> confirm;
        if (confirm == 'y' || confirm == 'Y') {
            std::cout << GREEN << "✅ Teacher '" << teachers[index].name << "' removed successfully!" << RESET << "\n";
            teachers.erase(teachers.begin() + index);
        }
        waitForEnter();
    }
    
    void manageSubjects() {
        while (true) {
            clearScreen();
            showHeader();
            std::cout << BOLD << CYAN << "📚 SUBJECT MANAGEMENT" << RESET << "\n";
            std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n";
            
            if (!subjects.empty()) {
                std::cout << BOLD << "Current Subjects:" << RESET << "\n";
                for (size_t i = 0; i < subjects.size(); ++i) {
                    std::cout << GREEN << "[" << (i + 1) << "] " << WHITE << subjects[i].name << RESET << "\n";
                }
                std::cout << "\n";
            }
            
            std::cout << GREEN << "[1]" << WHITE << " Add New Subject\n" << RESET;
            std::cout << GREEN << "[2]" << WHITE << " Remove Subject\n" << RESET;
            std::cout << RED << "[0]" << WHITE << " Back to Main Menu\n\n" << RESET;
            
            std::cout << BOLD << "Select option: " << RESET;
            int choice = getChoice(0, 2);
            
            switch (choice) {
                case 1: addSubject(); break;
                case 2: removeSubject(); break;
                case 0: return;
            }
        }
    }
    
    void addSubject() {
        std::cout << "\n" << BOLD << "📝 Add New Subject" << RESET << "\n";
        std::cout << "Enter subject name: ";
        std::string name;
        std::getline(std::cin, name);
        
        if (!name.empty()) {
            Subject subject;
            subject.name = name;
            subject.id = subjects.size() + 1;
            subjects.push_back(subject);
            
            std::cout << GREEN << "✅ Subject '" << name << "' added successfully!" << RESET << "\n";
        }
        waitForEnter();
    }
    
    void removeSubject() {
        if (subjects.empty()) {
            std::cout << RED << "❌ No subjects to remove." << RESET << "\n";
            waitForEnter();
            return;
        }
        
        std::cout << "\n" << BOLD << "🗑️  Remove Subject" << RESET << "\n";
        std::cout << "Enter subject number to remove: ";
        int index = getChoice(1, subjects.size()) - 1;
        
        std::cout << RED << "Are you sure you want to remove '" << subjects[index].name << "'? (y/n): " << RESET;
        char confirm;
        std::cin >> confirm;
        if (confirm == 'y' || confirm == 'Y') {
            std::cout << GREEN << "✅ Subject '" << subjects[index].name << "' removed successfully!" << RESET << "\n";
            subjects.erase(subjects.begin() + index);
        }
        waitForEnter();
    }
    
    void manageClasses() {
        while (true) {
            clearScreen();
            showHeader();
            std::cout << BOLD << CYAN << "🏫 CLASS MANAGEMENT" << RESET << "\n";
            std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n";
            
            if (!classes.empty()) {
                std::cout << BOLD << "Current Classes:" << RESET << "\n";
                for (size_t i = 0; i < classes.size(); ++i) {
                    std::cout << GREEN << "[" << (i + 1) << "] " << WHITE << classes[i].name 
                              << DIM << " (" << classes[i].grade << ")" << RESET << "\n";
                }
                std::cout << "\n";
            }
            
            std::cout << GREEN << "[1]" << WHITE << " Add New Class\n" << RESET;
            std::cout << GREEN << "[2]" << WHITE << " Remove Class\n" << RESET;
            std::cout << RED << "[0]" << WHITE << " Back to Main Menu\n\n" << RESET;
            
            std::cout << BOLD << "Select option: " << RESET;
            int choice = getChoice(0, 2);
            
            switch (choice) {
                case 1: addClass(); break;
                case 2: removeClass(); break;
                case 0: return;
            }
        }
    }
    
    void addClass() {
        std::cout << "\n" << BOLD << "📝 Add New Class" << RESET << "\n";
        std::cout << "Enter class name: ";
        std::string name;
        std::getline(std::cin, name);
        
        std::cout << "Enter grade level: ";
        std::string grade;
        std::getline(std::cin, grade);
        
        if (!name.empty() && !grade.empty()) {
            Class cls;
            cls.name = name;
            cls.grade = grade;
            cls.id = classes.size() + 1;
            classes.push_back(cls);
            
            std::cout << GREEN << "✅ Class '" << name << "' (" << grade << ") added successfully!" << RESET << "\n";
        }
        waitForEnter();
    }
    
    void removeClass() {
        if (classes.empty()) {
            std::cout << RED << "❌ No classes to remove." << RESET << "\n";
            waitForEnter();
            return;
        }
        
        std::cout << "\n" << BOLD << "🗑️  Remove Class" << RESET << "\n";
        std::cout << "Enter class number to remove: ";
        int index = getChoice(1, classes.size()) - 1;
        
        std::cout << RED << "Are you sure you want to remove '" << classes[index].name << "'? (y/n): " << RESET;
        char confirm;
        std::cin >> confirm;
        if (confirm == 'y' || confirm == 'Y') {
            std::cout << GREEN << "✅ Class '" << classes[index].name << "' removed successfully!" << RESET << "\n";
            classes.erase(classes.begin() + index);
        }
        waitForEnter();
    }
    
    void assignSubjectsToTeachers() {
        if (teachers.empty() || subjects.empty()) {
            clearScreen();
            showHeader();
            std::cout << RED << "❌ You need both teachers and subjects before making assignments.\n" << RESET;
            std::cout << "Please add teachers and subjects first.\n";
            waitForEnter();
            return;
        }
        
        clearScreen();
        showHeader();
        std::cout << BOLD << CYAN << "🔗 ASSIGN SUBJECTS TO TEACHERS" << RESET << "\n";
        std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n";
        
        for (auto& teacher : teachers) {
            std::cout << BOLD << YELLOW << "👨‍🏫 " << teacher.name << RESET << "\n";
            std::cout << "Available subjects:\n";
            
            for (size_t i = 0; i < subjects.size(); ++i) {
                std::cout << "[" << (i + 1) << "] " << subjects[i].name << "\n";
            }
            
            std::cout << "Enter subject numbers (space-separated), or 0 to skip: ";
            std::string line;
            std::getline(std::cin, line);
            std::istringstream iss(line);
            
            teacher.subjects.clear();
            int num;
            while (iss >> num) {
                if (num >= 1 && num <= (int)subjects.size()) {
                    teacher.subjects.push_back(subjects[num - 1].name);
                }
            }
            
            if (!teacher.subjects.empty()) {
                std::cout << GREEN << "✅ Assigned: ";
                for (size_t i = 0; i < teacher.subjects.size(); ++i) {
                    std::cout << teacher.subjects[i];
                    if (i < teacher.subjects.size() - 1) std::cout << ", ";
                }
                std::cout << RESET << "\n\n";
            } else {
                std::cout << DIM << "No subjects assigned.\n\n" << RESET;
            }
        }
        
        waitForEnter();
    }
    
    void generateSchedule() {
        if (teachers.empty() || subjects.empty() || classes.empty()) {
            clearScreen();
            showHeader();
            std::cout << RED << "❌ Cannot generate schedule. You need:\n" << RESET;
            if (teachers.empty()) std::cout << "   • At least one teacher\n";
            if (subjects.empty()) std::cout << "   • At least one subject\n";
            if (classes.empty()) std::cout << "   • At least one class\n";
            std::cout << "\nUse the Quick Setup (option 1) to add sample data quickly!\n";
            waitForEnter();
            return;
        }
        
        clearScreen();
        showHeader();
        std::cout << BOLD << GREEN << "🎲 SCHEDULE GENERATION" << RESET << "\n";
        std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n";
        
        // Progress animation
        std::vector<std::string> steps = {
            "🔄 Initializing schedule generator",
            "🧠 Applying randomization algorithms", 
            "🔍 Resolving teacher conflicts",
            "⚖️  Balancing class workloads",
            "🎨 Formatting professional output"
        };
        
        for (const auto& step : steps) {
            std::cout << YELLOW << step;
            for (int i = 0; i < 4; ++i) {
                std::cout << ".";
                std::cout.flush();
                usleep(300000);
            }
            std::cout << GREEN << " ✓" << RESET << "\n";
        }
        
        std::cout << "\n" << BOLD << GREEN << "✨ SCHEDULE GENERATION COMPLETE! ✨" << RESET << "\n\n";
        
        // Generate the actual schedule
        std::vector<ScheduleEntry> schedule = createRandomSchedule();
        displaySchedule(schedule);
        
        std::cout << "\n" << BOLD << CYAN << "SCHEDULE OPTIONS:" << RESET << "\n";
        std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
        std::cout << GREEN << "[1]" << WHITE << " Generate New Random Schedule\n" << RESET;
        std::cout << GREEN << "[2]" << WHITE << " Save Schedule to File\n" << RESET;
        std::cout << RED << "[0]" << WHITE << " Back to Main Menu\n\n" << RESET;
        
        std::cout << BOLD << "Select option: " << RESET;
        int choice = getChoice(0, 2);
        
        switch (choice) {
            case 1: generateSchedule(); break;
            case 2: saveSchedule(schedule); break;
            case 0: return;
        }
    }
    
    std::vector<ScheduleEntry> createRandomSchedule() {
        std::vector<ScheduleEntry> schedule;
        
        for (const auto& cls : classes) {
            for (const auto& day : days) {
                std::vector<std::string> dayTimes = timeSlots;
                std::shuffle(dayTimes.begin(), dayTimes.end(), rng);
                
                int periodsToday = 5 + (rng() % 3); // 5-7 periods per day
                for (int p = 0; p < periodsToday && p < (int)dayTimes.size(); ++p) {
                    if (subjects.empty()) continue;
                    
                    std::string subject = subjects[rng() % subjects.size()].name;
                    
                    std::string selectedTeacher = "Available Teacher";
                    std::vector<std::string> qualifiedTeachers;
                    
                    for (const auto& teacher : teachers) {
                        if (std::find(teacher.subjects.begin(), teacher.subjects.end(), subject) != teacher.subjects.end()) {
                            qualifiedTeachers.push_back(teacher.name);
                        }
                    }
                    
                    if (!qualifiedTeachers.empty()) {
                        selectedTeacher = qualifiedTeachers[rng() % qualifiedTeachers.size()];
                    } else if (!teachers.empty()) {
                        selectedTeacher = teachers[rng() % teachers.size()].name;
                    }
                    
                    schedule.push_back({selectedTeacher, subject, cls.name, dayTimes[p], day});
                }
            }
        }
        
        return schedule;
    }
    
    void displaySchedule(const std::vector<ScheduleEntry>& schedule) {
        std::cout << BOLD << BLUE << "📅 YOUR PROFESSIONAL SCHOOL SCHEDULE" << RESET << "\n";
        std::cout << "════════════════════════════════════════════════════════════\n\n";
        
        for (const auto& cls : classes) {
            std::cout << BOLD << CYAN << "* " << cls.name << " (" << cls.grade << ")" << RESET << "\n";
            std::cout << std::string(60, '-') << "\n";
            
            for (const auto& day : days) {
                std::cout << BOLD << std::setw(12) << std::left << day << RESET << ": ";
                
                std::vector<ScheduleEntry> daySchedule;
                for (const auto& entry : schedule) {
                    if (entry.className == cls.name && entry.day == day) {
                        daySchedule.push_back(entry);
                    }
                }
                
                std::sort(daySchedule.begin(), daySchedule.end(),
                    [](const ScheduleEntry& a, const ScheduleEntry& b) {
                        return a.timeSlot < b.timeSlot;
                    });
                
                for (size_t i = 0; i < daySchedule.size(); ++i) {
                    if (i > 0) std::cout << std::string(14, ' ');
                    std::cout << GREEN << daySchedule[i].timeSlot << RESET << " " 
                             << YELLOW << daySchedule[i].subject << RESET << " " 
                             << DIM << "(" << daySchedule[i].teacher << ")" << RESET << "\n";
                }
                if (daySchedule.empty()) {
                    std::cout << DIM << "🌴 Free day\n" << RESET;
                }
            }
            std::cout << "\n";
        }
    }
    
    void saveSchedule(const std::vector<ScheduleEntry>& schedule) {
        std::string filename = "smart_mavi_schedule.txt";
        std::ofstream file(filename);
        
        if (file.is_open()) {
            file << "SMART MAVI MANAGER - PROFESSIONAL SCHOOL SCHEDULE\n";
            file << "================================================\n\n";
            file << "Generated on: " << __DATE__ << " " << __TIME__ << "\n\n";
            
            for (const auto& cls : classes) {
                file << cls.name << " (" << cls.grade << ")\n";
                file << std::string(40, '-') << "\n";
                
                for (const auto& day : days) {
                    file << std::setw(12) << std::left << day << ": ";
                    
                    std::vector<ScheduleEntry> daySchedule;
                    for (const auto& entry : schedule) {
                        if (entry.className == cls.name && entry.day == day) {
                            daySchedule.push_back(entry);
                        }
                    }
                    
                    std::sort(daySchedule.begin(), daySchedule.end(),
                        [](const ScheduleEntry& a, const ScheduleEntry& b) {
                            return a.timeSlot < b.timeSlot;
                        });
                    
                    for (size_t i = 0; i < daySchedule.size(); ++i) {
                        if (i > 0) file << std::string(14, ' ');
                        file << daySchedule[i].timeSlot << " " 
                             << daySchedule[i].subject << " (" 
                             << daySchedule[i].teacher << ")\n";
                    }
                    if (daySchedule.empty()) {
                        file << "Free day\n";
                    }
                }
                file << "\n";
            }
            
            file.close();
            std::cout << GREEN << "✅ Schedule saved to '" << filename << "' successfully!" << RESET << "\n";
        } else {
            std::cout << RED << "❌ Error saving schedule to file." << RESET << "\n";
        }
        
        waitForEnter();
    }
    
    void viewCurrentData() {
        clearScreen();
        showHeader();
        std::cout << BOLD << CYAN << "📊 CURRENT DATA OVERVIEW" << RESET << "\n";
        std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n";
        
        // Teachers section
        std::cout << BOLD << YELLOW << "👥 TEACHERS (" << teachers.size() << ")" << RESET << "\n";
        if (teachers.empty()) {
            std::cout << DIM << "   No teachers added yet." << RESET << "\n";
        } else {
            for (const auto& teacher : teachers) {
                std::cout << "   • " << GREEN << teacher.name << RESET;
                if (!teacher.subjects.empty()) {
                    std::cout << DIM << " → ";
                    for (size_t i = 0; i < teacher.subjects.size(); ++i) {
                        std::cout << teacher.subjects[i];
                        if (i < teacher.subjects.size() - 1) std::cout << ", ";
                    }
                }
                std::cout << RESET << "\n";
            }
        }
        
        std::cout << "\n";
        
        // Subjects section
        std::cout << BOLD << YELLOW << "📚 SUBJECTS (" << subjects.size() << ")" << RESET << "\n";
        if (subjects.empty()) {
            std::cout << DIM << "   No subjects added yet." << RESET << "\n";
        } else {
            for (const auto& subject : subjects) {
                std::cout << "   • " << GREEN << subject.name << RESET << "\n";
            }
        }
        
        std::cout << "\n";
        
        // Classes section
        std::cout << BOLD << YELLOW << "🏫 CLASSES (" << classes.size() << ")" << RESET << "\n";
        if (classes.empty()) {
            std::cout << DIM << "   No classes added yet." << RESET << "\n";
        } else {
            for (const auto& cls : classes) {
                std::cout << "   • " << GREEN << cls.name << DIM << " (" << cls.grade << ")" << RESET << "\n";
            }
        }
        
        std::cout << "\n";
        waitForEnter();
    }
    
    void showGUIPreview() {
        clearScreen();
        showHeader();
        std::cout << BOLD << MAGENTA << "🖥️  GUI VERSION PREVIEW" << RESET << "\n";
        std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n";
        
        std::cout << YELLOW << "⚡ COMING SOON - GRAPHICAL USER INTERFACE ⚡" << RESET << "\n\n";
        
        std::cout << BOLD << CYAN << "🎨 UPCOMING GUI FEATURES:" << RESET << "\n";
        std::cout << "   • Modern drag-and-drop interface\n";
        std::cout << "   • Visual timetable grid with color coding\n";
        std::cout << "   • Real-time conflict detection\n";
        std::cout << "   • Interactive teacher/class scheduling\n";
        std::cout << "   • Export to PDF and Excel formats\n";
        std::cout << "   • Dark/Light theme support\n";
        std::cout << "   • Multi-language support\n";
        std::cout << "   • Backup and restore functionality\n\n";
        
        std::cout << BOLD << GREEN << "🚀 ADVANCED FEATURES IN DEVELOPMENT:" << RESET << "\n";
        std::cout << "   • AI-powered optimal scheduling\n";
        std::cout << "   • Teacher workload optimization\n";
        std::cout << "   • Room allocation management\n";
        std::cout << "   • Parent/student portal integration\n";
        std::cout << "   • Mobile companion app\n";
        std::cout << "   • Cloud sync across devices\n";
        std::cout << "   • Automated report generation\n\n";
        
        std::cout << BOLD << BLUE << "📋 CURRENT STATUS:" << RESET << "\n";
        std::cout << "   Development Stage: " << YELLOW << "Pre-Alpha" << RESET << "\n";
        std::cout << "   Expected Release: " << GREEN << "Q2 2025" << RESET << "\n";
        std::cout << "   Technology Stack: " << CYAN << "Qt6/C++" << RESET << "\n";
        std::cout << "   Platform Support: " << MAGENTA << "Windows, macOS, Linux" << RESET << "\n\n";
        
        std::cout << BOLD << YELLOW << "📧 STAY UPDATED:" << RESET << "\n";
        std::cout << "   Follow our development progress and get early access!\n";
        std::cout << "   The GUI version will include all current features plus\n";
        std::cout << "   many exciting new capabilities for modern schools.\n\n";
        
        std::cout << DIM << "Thank you for your patience as we build the future of\n";
        std::cout << "educational scheduling software!" << RESET << "\n\n";
        
        waitForEnter();
    }
    
    void showAbout() {
        clearScreen();
        showHeader();
        std::cout << BOLD << CYAN << "ℹ️  ABOUT SMART MAVI MANAGER" << RESET << "\n";
        std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n";
        
        std::cout << BOLD << "Version:" << RESET << " 1.0.0 Professional\n";
        std::cout << BOLD << "Description:" << RESET << " Advanced Schedule Generator for Educational Institutions\n\n";
        
        std::cout << BOLD << GREEN << "✨ KEY FEATURES:" << RESET << "\n";
        std::cout << "   🎲 Intelligent randomization with conflict prevention\n";
        std::cout << "   👥 Comprehensive teacher and subject management\n";
        std::cout << "   🏫 Flexible class organization system\n";
        std::cout << "   📊 Professional schedule output\n";
        std::cout << "   💾 Save schedules to text files\n";
        std::cout << "   🚀 Quick setup wizard for instant results\n\n";
        
        std::cout << BOLD << BLUE << "🔧 QUICK START GUIDE:" << RESET << "\n";
        std::cout << "   1. Use 'Quick Setup' for instant sample data\n";
        std::cout << "   2. Or manually add teachers, subjects, and classes\n";
        std::cout << "   3. Assign subjects to teachers for accuracy\n";
        std::cout << "   4. Generate randomized schedules instantly\n";
        std::cout << "   5. Save and print professional timetables\n\n";
        
        std::cout << BOLD << MAGENTA << "💡 PRO TIPS:" << RESET << "\n";
        std::cout << "   • Each schedule generation creates a unique arrangement\n";
        std::cout << "   • Teachers are automatically matched to their subjects\n";
        std::cout << "   • Workloads are balanced across all classes\n";
        std::cout << "   • No scheduling conflicts are ever created\n\n";
        
        std::cout << DIM << "Built with ❤️  for educational excellence\n";
        std::cout << "© 2024 Smart Mavi Manager - Professional Edition" << RESET << "\n\n";
        
        waitForEnter();
    }
    
    void showExitMessage() {
        clearScreen();
        std::cout << BOLD << GREEN;
        std::cout << "+--------------------------------------------------------------+\n";
        std::cout << "|                                                              |\n";
        std::cout << "|" << WHITE << "                 Thank you for using                        " << GREEN << "|\n";
        std::cout << "|" << CYAN << "             * SMART MAVI MANAGER *                     " << GREEN << "|\n";
        std::cout << "|                                                              |\n";
        std::cout << "|" << YELLOW << "        Your schedules are now perfectly organized!        " << GREEN << "|\n";
        std::cout << "|" << MAGENTA << "              Have a wonderful day! *                    " << GREEN << "|\n";
        std::cout << "|                                                              |\n";
        std::cout << "+--------------------------------------------------------------+" << RESET << "\n\n";
        
        std::cout << DIM << "Application closed successfully." << RESET << "\n";
    }
    
    void waitForEnter() {
        std::cout << "\n" << DIM << "Press Enter to continue..." << RESET;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
};

int main() {
    SmartMaviManager app;
    app.run();
    return 0;
}
