#ifndef STUDENT_H
#define STUDENT_H

#include "User.h"
#include "Quiz.h"

class Student : public User {
private:
    Quiz quiz;

public:
    Student(string uname, string pass) : User(uname, pass) {
        quiz.loadQuestionsFromFile();
    }

    void showMenu() {
        int choice;
        while (true) {
            cout << "\nStudent Menu:\n";
            cout << "1. Take Quiz\n2. Report Summary\n3. Logout\nChoice: ";
            cin >> choice;

            if (choice == 1) {
                quiz.startQuiz();
            }
            else if (choice == 2) {
                reportSummary(quiz);
            }
            else if (choice == 3) {
                break;
            }
            else {
                cout << "Invalid choice. Try again.\n";
            }
        }
    }
};

#endif
