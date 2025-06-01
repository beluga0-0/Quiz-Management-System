#ifndef ADMIN_H
#define ADMIN_H

#include "User.h"
#include "Quiz.h"

class Admin : public User {
private:
    Quiz quiz;

public:
    Admin(string uname, string pass) : User(uname, pass) {
        quiz.loadQuestionsFromFile();
    }

    void showMenu() {
        int choice;
        while (true) {
            cout << "\nAdmin Menu:\n";
            cout << "1. Add Question\n2. View All Questions\n3. Save Questions\n4. Start Quiz\n5. Update Question\n6. Delete Question\n7. Search Question\n8. Report Summary\n9. Logout\nChoice: ";
            cin >> choice;
            cin.ignore();

            if (choice == 1) {
                string q, a, b, c, d;
                char correct;
                cout << "Enter question: "; getline(cin, q);
                cout << "Option A: "; getline(cin, a);
                cout << "Option B: "; getline(cin, b);
                cout << "Option C: "; getline(cin, c);
                cout << "Option D: "; getline(cin, d);
                cout << "Correct option (A/B/C/D): "; cin >> correct;
                Question newQ(q, a, b, c, d, toupper(correct));
                quiz.addQuestion(newQ);
            }
            else if (choice == 2) {
                quiz.displayAllQuestions();
            }
            else if (choice == 3) {
                quiz.saveQuestionsToFile();
                cout << "Questions saved successfully!\n";
            }
            else if (choice == 4) {
                quiz.startQuiz();
            }
            else if (choice == 5) {
                int index;
                cout << "Enter question number to update: ";
                cin >> index; cin.ignore();
                string q, a, b, c, d; char correct;
                cout << "Enter updated question: "; getline(cin, q);
                cout << "Option A: "; getline(cin, a);
                cout << "Option B: "; getline(cin, b);
                cout << "Option C: "; getline(cin, c);
                cout << "Option D: "; getline(cin, d);
                cout << "Correct option (A/B/C/D): "; cin >> correct;
                Question updated(q, a, b, c, d, toupper(correct));
                quiz.updateQuestion(index - 1, updated);
            }
            else if (choice == 6) {
                int index;
                cout << "Enter question number to delete: ";
                cin >> index;
                quiz.deleteQuestion(index - 1);
            }
            else if (choice == 7) {
                string keyword;
                cout << "Enter keyword to search: ";
                cin.ignore();
                getline(cin, keyword);
                quiz.searchQuestion(keyword);
            }
            else if (choice == 8) {
                reportSummary(quiz);
            }
            else if (choice == 9) {
                break;
            }
            else {
                cout << "Invalid choice. Try again.\n";
            }
        }
    }
};

#endif
