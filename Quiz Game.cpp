#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
#include <algorithm> // Added for random_shuffle
using namespace std;

// Struct to hold each question's details
struct Question {
    string text;           // The question text
    vector<string> options; // 4 options
    int correctIndex;      // Index of correct option (0-3)
    string explanation;    // Optional explanation for correct answer
};

// User struct for registration and scoring
struct User {
    string username;
    string password;
    int score = 0; // Current quiz score
};

// Global data
vector<Question> questions;
map<string, User> users;

// Initialize questions
void initializeQuestions() {
    questions.push_back({
        "Which one is the Capital of Pakistan?",
        {"Berlin", "Paris", "Islamabad", "NewYork"},
        2, // Correct index (Islamabad)
        "Islamabad is the capital city of Pakistan."
    });
    questions.push_back({
        "What is 2+2?",
        {"4", "5", "6", "10"},
        0,
        "Basic arithmetic: 2 + 2 equals 4."
    });
    questions.push_back({
        "Who wrote 'Romeo and Juliet'?",
        {"Shakespeare", "Dickens", "Tolkien", "Austen"},
        0,
        "William Shakespeare is the author of 'Romeo and Juliet'."
    });
    questions.push_back({
        "What is the chemical symbol for water?",
        {"H2O", "CO2", "NaCl", "O2"},
        0,
        "The chemical symbol for water is H2O."
    });
    questions.push_back({
        "In which year did World War II end?",
        {"1945", "1918", "1939", "1960"},
        0,
        "World War II ended in 1945."
    });
    questions.push_back({
        "What is the largest planet in our Solar System?",
        {"Earth", "Mars", "Jupiter", "Saturn"},
        2,
        "Jupiter is the largest planet in our Solar System."
    });
    questions.push_back({
        "Who was the first President of the United States?",
        {"Abraham Lincoln", "George Washington", "Thomas Jefferson", "John Adams"},
        1,
        "George Washington was the first U.S. President, serving from 1789 to 1797."
    });
    questions.push_back({
        "What is the square root of 16?",
        {"2", "3", "4", "5"},
        2,
        "The square root of 16 is 4, since 4 * 4 = 16."
    });
    questions.push_back({
        "Which country is known as the Land of the Rising Sun?",
        {"China", "Japan", "Thailand", "South Korea"},
        1,
        "Japan is called the Land of the Rising Sun due to its position east of Asia."
    });
    questions.push_back({
        "Who painted the Mona Lisa?",
        {"Vincent van Gogh", "Pablo Picasso", "Leonardo da Vinci", "Claude Monet"},
        2,
        "Leonardo da Vinci painted the Mona Lisa."
    });
    questions.push_back({
        "What gas do plants use for photosynthesis?",
        {"Oxygen", "Nitrogen", "Carbon Dioxide", "Hydrogen"},
        2,
        "Plants use carbon dioxide during photosynthesis to produce energy."
    });
    questions.push_back({
        "In which year did the Titanic sink?",
        {"1905", "1912", "1920", "1898"},
        1,
        "The Titanic sank in 1912 after hitting an iceberg."
    });
    questions.push_back({
        "What is the capital city of Australia?",
        {"Sydney", "Melbourne", "Canberra", "Brisbane"},
        2,
        "Canberra is the capital city of Australia."
    });
    questions.push_back({
        "Who wrote the novel 'Pride and Prejudice'?",
        {"Charlotte Bronte", "Jane Austen", "Emily Dickinson", "Virginia Woolf"},
        1,
        "Jane Austen wrote 'Pride and Prejudice', published in 1813."
    });
    questions.push_back({
        "What is the chemical symbol for gold?",
        {"Au", "Ag", "Fe", "Cu"},
        0,
        "The chemical symbol for gold is Au, from the Latin 'aurum'."
    });
    questions.push_back({
        "Which sport is associated with Wimbledon?",
        {"Cricket", "Football", "Tennis", "Golf"},
        2,
        "Wimbledon is a famous tennis tournament held in London."
    });
    questions.push_back({
        "What is the longest river in the world?",
        {"Amazon", "Nile", "Yangtze", "Mississippi"},
        1,
        "The Nile is considered the longest river, stretching over 6,650 km."
    });
    questions.push_back({
        "Who discovered penicillin?",
        {"Alexander Fleming", "Marie Curie", "Louis Pasteur", "Gregor Mendel"},
        0,
        "Alexander Fleming discovered penicillin in 1928."
    });
    questions.push_back({
        "What is 10% of 200?",
        {"10", "20", "30", "40"},
        1,
        "10% of 200 is 20, calculated as (10/100) * 200."
    });
    questions.push_back({
        "Which element is the most abundant in Earth's atmosphere?",
        {"Oxygen", "Hydrogen", "Nitrogen", "Carbon"},
        2,
        "Nitrogen makes up about 78% of Earth's atmosphere."
    });
}

// Registration function
bool registerUser() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    if (users.find(username) != users.end()) {
        cout << "Username already exists!\n";
        return false;
    }
    cout << "Enter password: ";
    cin >> password;
    users[username] = {username, password, 0};
    cout << "Registration successful!\n";
    return true;
}

// Login function: Verify credentials
string loginUser() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    auto it = users.find(username);
    if (it != users.end() && it->second.password == password) {
        cout << "Login successful!\n";
        return username;
    }
    cout << "Invalid username or password!\n";
    return "";
}

// Display correct answers at the end
void displayCorrectAnswers(const vector<Question>& selectedQuestions, const vector<int>& userAnswers) {
    cout << "\nReview:\n";
    for (size_t i = 0; i < selectedQuestions.size(); ++i) {
        const Question& q = selectedQuestions[i];
        cout << "Question " << (i + 1) << ": " << q.text << endl;
        cout << "Your answer: " << (userAnswers[i] >= 0 ? q.options[userAnswers[i]] : "No answer") << endl;
        cout << "Correct answer: " << q.options[q.correctIndex] << endl;
        cout << "Explanation: " << q.explanation << endl << endl;
    }
}

// Implement the quiz logic
void startQuiz(const string& username) {
    if (questions.empty()) {
        cout << "No questions available!\n";
        return;
    }
    User& user = users[username];
    user.score = 0;
    vector<int> userAnswers; // Store user's chosen indices
    vector<Question> selectedQuestions;

    // Randomize: Seed random and shuffle
    srand(time(0));
    vector<Question> shuffled = questions;
    random_shuffle(shuffled.begin(), shuffled.end());
    int numQuestions = min(5, (int)shuffled.size()); // Take 5 questions
    selectedQuestions.assign(shuffled.begin(), shuffled.begin() + numQuestions);

    for (int i = 0; i < numQuestions; ++i) {
        const Question& q = selectedQuestions[i];
        cout << "\nQuestion " << (i + 1) << ": " << q.text << endl;
        for (int j = 0; j < q.options.size(); ++j) {
            cout << (j + 1) << ". " << q.options[j] << endl;
        }
        int answer;
        cout << "Your answer (1-4): ";
        while (!(cin >> answer) || answer < 1 || answer > 4) {
            cout << "Invalid input! Enter a number between 1 and 4: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        int chosenIndex = answer - 1;
        userAnswers.push_back(chosenIndex);
        if (chosenIndex == q.correctIndex) {
            user.score += 10; // 10 points per correct answer
            cout << "Correct!\n";
        } else {
            cout << "Incorrect.\n";
        }
    }
    // Display score
    cout << "\nQuiz complete! Your score: " << user.score << "/" << (numQuestions * 10) << endl;
    // Display correct answers
    displayCorrectAnswers(selectedQuestions, userAnswers);
}

int main() {
    initializeQuestions();
    int choice;
    string currentUser;
    while (true) {
        cout << "\n--- Quiz Game Menu ---\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Start Quiz (must be logged in)\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        while (!(cin >> choice) || choice < 1 || choice > 4) {
            cout << "Invalid choice! Enter a number between 1 and 4: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        if (choice == 1) {
            registerUser();
        } else if (choice == 2) {
            currentUser = loginUser();
        } else if (choice == 3) {
            if (currentUser.empty()) {
                cout << "Please login first!\n";
            } else {
                startQuiz(currentUser);
            }
        } else if (choice == 4) {
            break;
        }
    }
    return 0;
}