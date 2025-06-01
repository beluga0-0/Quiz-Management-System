#ifndef QUIZ_H
#define QUIZ_H

#include <iostream>
#include <chrono>
#include<string>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

class Question {
private:
    string questionText;
    string optionA, optionB, optionC, optionD;
    char correctOption;

public:
    Question() {}
    Question(string q, string a, string b, string c, string d, char correct) {
        questionText = q;
        optionA = a;
        optionB = b;
        optionC = c;
        optionD = d;
        correctOption = correct;
    }

    void display() {
        cout << questionText << endl;
        cout << "A. " << optionA << endl;
        cout << "B. " << optionB << endl;
        cout << "C. " << optionC << endl;
        cout << "D. " << optionD << endl;
    }

    char getCorrectOption() {
        return correctOption;
    }

    string getText() { return questionText; }

    void setQuestion(string q) { questionText = q; }
    void setOptionA(string a) { optionA = a; }
    void setOptionB(string b) { optionB = b; }
    void setOptionC(string c) { optionC = c; }
    void setOptionD(string d) { optionD = d; }
    void setCorrectOption(char c) { correctOption = c; }

    void saveToFile(ofstream& out) {
        out << questionText << endl
            << optionA << endl
            << optionB << endl
            << optionC << endl
            << optionD << endl
            << correctOption << endl;
    }

    void loadFromFile(ifstream& in) {
        getline(in, questionText);
        getline(in, optionA);
        getline(in, optionB);
        getline(in, optionC);
        getline(in, optionD);
        in >> correctOption;
        in.ignore();
    }
};

class Quiz {
private:
    vector<Question> questions;
    static int totalQuizzesTaken;

public:
    void addQuestion(Question q) {
        questions.push_back(q);
    }

    void saveQuestionsToFile() {
        ofstream file("questions.txt");
        file << questions.size() << endl;
        for (Question q : questions)
            q.saveToFile(file);
        file.close();
    }

    void loadQuestionsFromFile() {
        questions.clear();
        ifstream file("questions.txt");
        int count;
        file >> count;
        file.ignore();
        for (int i = 0; i < count; i++) {
            Question q;
            q.loadFromFile(file);
            questions.push_back(q);
        }
        file.close();
    }

    void displayAllQuestions() {
        for (int i = 0; i < questions.size(); i++) {
            cout << "\nQuestion " << i + 1 << ":\n";
            questions[i].display();
        }
    }

    void updateQuestion(int index, Question updated) {
        if (index >= 0 && index < questions.size()) {
            questions[index] = updated;
        }
    }

    void deleteQuestion(int index) {
        if (index >= 0 && index < questions.size()) {
            questions.erase(questions.begin() + index);
        }
    }

    void searchQuestion(string keyword) {
        bool found = false;
        for (int i = 0; i < questions.size(); i++) {
            if (questions[i].getText().find(keyword) != string::npos) {
                cout << "\nQuestion " << i + 1 << ":\n";
                questions[i].display();
                found = true;
            }
        }
        if (!found) cout << "No question found matching keyword.\n";
    }

    void startQuiz() {
        int score = 0;
        char answer;

        // Set the time limit (in seconds)
        const int timeLimit = 60;

        // Record the start time
        auto startTime = chrono::high_resolution_clock::now();

        for (int i = 0; i < questions.size(); i++) {
            // Check elapsed time
            auto currentTime = chrono::high_resolution_clock::now();
            auto elapsedTime = chrono::duration_cast<chrono::seconds>(currentTime - startTime).count();

            if (elapsedTime >= timeLimit) {
                cout << "\nTime's up!!!!!!    Ending the Quiz \n"; 
                    
                    break;
            }
            
           
                // Display the question and get the user's answer
                cout << "\nQuestion " << i + 1 << ":\n";
                questions[i].display();
                cout << "Your answer: ";

                cin >> answer;

                // Check if the answer is correct
                if (toupper(answer) == questions[i].getCorrectOption()) {
                    score++;
                }
            
        }

        // Calculate total elapsed time
        auto endTime = chrono::high_resolution_clock::now();
        auto totalElapsedTime = chrono::duration_cast<chrono::seconds>(endTime - startTime).count();

        totalQuizzesTaken++;
        cout << "\nYour score: " << score << "/" << questions.size() << endl;
        cout << "Time taken: " << totalElapsedTime << " seconds" << endl;
    }
    static int getTotalQuizzesTaken() {
        return totalQuizzesTaken;
    }

    friend void reportSummary(Quiz);
};

int Quiz::totalQuizzesTaken = 0;

void reportSummary(Quiz q) {
    cout << "\nTotal questions: " << q.questions.size() << endl;
    cout << "Total quizzes taken: " << Quiz::getTotalQuizzesTaken() << endl;
}

#endif