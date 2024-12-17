#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace std;


struct Question {
    string questionText;
    vector<string> options;
    char correctOption;
};


void registerPlayer(string &playerName);
vector<Question> loadQuestions(const string &filename);
void playQuiz(const vector<Question> &questions, int &score);
void displayScore(const string &playerName, int score);
void writeScoreToFile(const string &playerName, int score);

int main() {
    string playerName;
    vector<Question> questions;
    int score = 0;

    
    registerPlayer(playerName);

    
    questions = loadQuestions("questions.txt");

    if (questions.empty()) {
        cout << "No questions loaded. Exiting..." << endl;
        return 1;
    }

   
    playQuiz(questions, score);

    
    displayScore(playerName, score);

    
    writeScoreToFile(playerName, score);

    return 0;
}


void registerPlayer(string &playerName) {
    cout << "Welcome to the Quiz Game!" << endl;
    cout << "Please enter your name to register: ";
    getline(cin, playerName);
    cout << "Hi " << playerName << "! Let's start the quiz.\n" << endl;
}


vector<Question> loadQuestions(const string &filename) {
    vector<Question> questions;
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cout << "Error: Could not open file '" << filename << "'." << endl;
        return questions;
    }

    while (getline(file, line)) {
        stringstream ss(line);
        Question q;
        string option;
        char correct;

        
        getline(ss, q.questionText, ';');

      
        for (int i = 0; i < 4; ++i) {
            getline(ss, option, ';');
            q.options.push_back(option);
        }

        
        ss >> q.correctOption;

        questions.push_back(q);
    }
    file.close();
    return questions;
}


void playQuiz(const vector<Question> &questions, int &score) {
    srand(time(0));
    int numQuestions = questions.size();

    for (int i = 0; i < 5; ++i) { 
        int index = rand() % numQuestions; 
        const Question &q = questions[index];

        cout << "Q" << (i + 1) << ": " << q.questionText << endl;

        
        char optionLabel = 'A';
        for (const auto &opt : q.options) {
            cout << optionLabel << ". " << opt << endl;
            optionLabel++;
        }

        
        char answer;
        cout << "Your answer: ";
        cin >> answer;

        if (toupper(answer) == q.correctOption) {
            cout << "Correct!" << endl;
            score += 10; 
        } else {
            cout << "Wrong! Correct answer was " << q.correctOption << "." << endl;
        }
        cout << endl;
    }
}

void displayScore(const string &playerName, int score) {
    cout << "----------------------------------" << endl;
    cout << "Quiz Completed!" << endl;
    cout << "Player: " << playerName << endl;
    cout << "Final Score: " << score << endl;
    cout << "----------------------------------" << endl;
}

void writeScoreToFile(const string &playerName, int score) {
    ofstream outFile("scores.txt", ios::app);
    if (!outFile) {
        cout << "Error saving score!" << endl;
        return;
    }
    outFile << playerName << " - Score: " << score << endl;
    outFile.close();
    cout << "Your score has been saved successfully!" << endl;
}
