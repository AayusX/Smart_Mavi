#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <iomanip>

// Simplified demo of Smart Mavi Manager core functionality
struct Teacher {
    std::string name;
    std::vector<std::string> subjects;
};

struct Class {
    std::string name;
    std::string grade;
};

struct ScheduleEntry {
    std::string teacher;
    std::string subject;
    std::string className;
    std::string timeSlot;
    std::string day;
};

class SmartMaviDemo {
private:
    std::vector<Teacher> teachers;
    std::vector<std::string> subjects;
    std::vector<Class> classes;
    std::vector<std::string> days = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
    std::vector<std::string> timeSlots = {"08:00-08:45", "08:45-09:30", "09:30-10:15", "10:30-11:15", "11:15-12:00", "12:00-12:45", "13:45-14:30", "14:30-15:15"};
    std::mt19937 rng;

public:
    SmartMaviDemo() : rng(std::random_device{}()) {}
    
    void runSurveyDemo() {
        std::cout << "\n🎓 SMART MAVI MANAGER - DEMO MODE 🎓\n";
        std::cout << "=====================================\n\n";
        
        std::cout << "🎪 Welcome to the fun survey system!\n";
        std::cout << "📊 Let's set up your school schedule...\n\n";
        
        // Sample data setup
        setupSampleData();
        
        std::cout << "✨ Survey completed! Here's what we collected:\n\n";
        
        displaySurveyResults();
        generateSampleSchedule();
    }
    
private:
    void setupSampleData() {
        std::cout << "👨‍🏫 Adding teachers:\n";
        teachers = {
            {"Mr. Johnson", {"Mathematics", "Physics"}},
            {"Ms. Smith", {"English", "Literature"}}, 
            {"Dr. Brown", {"Chemistry", "Biology"}},
            {"Mrs. Davis", {"History", "Geography"}},
            {"Mr. Wilson", {"Art", "Music"}}
        };
        
        for (const auto& teacher : teachers) {
            std::cout << "   ✅ " << teacher.name << " (teaches: ";
            for (size_t i = 0; i < teacher.subjects.size(); ++i) {
                std::cout << teacher.subjects[i];
                if (i < teacher.subjects.size() - 1) std::cout << ", ";
            }
            std::cout << ")\n";
        }
        
        std::cout << "\n📚 Adding subjects:\n";
        subjects = {"Mathematics", "English", "Chemistry", "History", "Art", "Physics", "Literature", "Biology", "Geography", "Music"};
        for (const auto& subject : subjects) {
            std::cout << "   ✅ " << subject << "\n";
        }
        
        std::cout << "\n🏫 Adding classes:\n";
        classes = {
            {"Class A", "Grade 9"},
            {"Class B", "Grade 10"}, 
            {"Class C", "Grade 11"},
            {"Class D", "Grade 12"}
        };
        for (const auto& cls : classes) {
            std::cout << "   ✅ " << cls.name << " (" << cls.grade << ")\n";
        }
    }
    
    void displaySurveyResults() {
        std::cout << "📋 CONFIGURATION SUMMARY:\n";
        std::cout << "========================\n";
        std::cout << "👨‍🏫 Teachers: " << teachers.size() << "\n";
        std::cout << "📚 Subjects: " << subjects.size() << "\n";
        std::cout << "🏫 Classes: " << classes.size() << "\n";
        std::cout << "📅 Days per week: " << days.size() << "\n";
        std::cout << "⏰ Periods per day: " << timeSlots.size() << "\n\n";
    }
    
    void generateSampleSchedule() {
        std::cout << "🎲 GENERATING RANDOMIZED SCHEDULE...\n";
        std::cout << "====================================\n\n";
        
        std::vector<ScheduleEntry> schedule;
        
        // Generate random schedule entries
        for (const auto& day : days) {
            for (const auto& cls : classes) {
                std::vector<std::string> availableSlots = timeSlots;
                std::shuffle(availableSlots.begin(), availableSlots.end(), rng);
                
                int periodsToday = 4 + (rng() % 3); // 4-6 periods per day
                for (int p = 0; p < periodsToday && p < (int)availableSlots.size(); ++p) {
                    // Random subject
                    std::string subject = subjects[rng() % subjects.size()];
                    
                    // Find teacher who teaches this subject
                    std::string selectedTeacher = "Available Teacher";
                    for (const auto& teacher : teachers) {
                        if (std::find(teacher.subjects.begin(), teacher.subjects.end(), subject) != teacher.subjects.end()) {
                            selectedTeacher = teacher.name;
                            break;
                        }
                    }
                    
                    schedule.push_back({selectedTeacher, subject, cls.name, availableSlots[p], day});
                }
            }
        }
        
        // Display sample schedule
        displayScheduleTable(schedule);
        
        std::cout << "\n🎊 SUCCESS! Your Smart Mavi Manager would generate schedules like this!\n";
        std::cout << "\n✨ Key Features Demonstrated:\n";
        std::cout << "   🎲 Randomized time slot assignments\n";
        std::cout << "   👨‍🏫 Teacher-subject matching\n";
        std::cout << "   🏫 Class-specific schedules\n";
        std::cout << "   ⏰ Professional time management\n";
        std::cout << "   📊 Organized table output\n\n";
        
        std::cout << "🚀 The full GUI application includes:\n";
        std::cout << "   ✨ Animated setup wizard\n";
        std::cout << "   🎨 Beautiful modern interface\n";
        std::cout << "   🖨️ PDF & CSV export\n";
        std::cout << "   📋 Multiple view types\n";
        std::cout << "   🎯 Advanced conflict resolution\n\n";
    }
    
    void displayScheduleTable(const std::vector<ScheduleEntry>& schedule) {
        std::cout << "📅 SAMPLE GENERATED SCHEDULE:\n";
        std::cout << std::string(80, '=') << "\n\n";
        
        // Group by class for display
        for (const auto& cls : classes) {
            std::cout << "🏫 " << cls.name << " (" << cls.grade << ")\n";
            std::cout << std::string(50, '-') << "\n";
            
            for (const auto& day : days) {
                std::cout << std::setw(12) << std::left << day << ": ";
                
                std::vector<ScheduleEntry> daySchedule;
                for (const auto& entry : schedule) {
                    if (entry.className == cls.name && entry.day == day) {
                        daySchedule.push_back(entry);
                    }
                }
                
                // Sort by time
                std::sort(daySchedule.begin(), daySchedule.end(), 
                    [](const ScheduleEntry& a, const ScheduleEntry& b) {
                        return a.timeSlot < b.timeSlot;
                    });
                
                for (size_t i = 0; i < daySchedule.size(); ++i) {
                    if (i > 0) std::cout << std::string(14, ' ');
                    std::cout << daySchedule[i].timeSlot << " " 
                             << daySchedule[i].subject << " (" 
                             << daySchedule[i].teacher << ")\n";
                }
                if (daySchedule.empty()) {
                    std::cout << "Free day\n";
                }
            }
            std::cout << "\n";
        }
    }
};

int main() {
    SmartMaviDemo demo;
    demo.runSurveyDemo();
    return 0;
}
