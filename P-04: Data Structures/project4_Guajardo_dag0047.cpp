/* Project 4
 * Demarco Guajardo
 * dag0047@auburn.edu
 * project4_Guajardo_dag0047.cpp
 * I used "g++ -std=c++11" to compile my code.
 * I used the project 4 file on Canvas.
 * I used softwareengineering.stackexhange to learn about structures
 * and a respective constructor (although not required)
 * I used softwaretestinghelp to learn about <cassert>
 * I used geeksforgeeks to find length of linked list
 */

//#define UNIT_TESTING
#include <iostream>
#include <cassert>
#include <cstddef>

using namespace std;

/*
 * STEP 1
 * Structure that defines a TriviaNode that holds a question, answer,
 * and the points it's worth, along with a pointer to the next TriviaNode.
 */
struct TriviaNode {

    string question;
    string answer;
    int points;
    //Points to next TriviaNode
    TriviaNode* next;

    //Constructor that initializes the structure's variables
    TriviaNode(const string& qIn, const string& aIn, int pIn)
            : question(qIn), answer(aIn), points(pIn), next(nullptr) {
    }
};

/*
 * Function that gets the size of the TriviaList
 */
int countOfTriviaList(TriviaNode* head) {
    //Initialize count to 0
    int count = 0;

    //Set current to first TriviaNode in TriviaList
    TriviaNode* current = head;

    while (current != nullptr) {
        count++;
        current = current->next;
    }

    return count;
}

/*
 * STEPS 2 AND 3
 * Linked List of 3 TriviaNode objects that holds 3 questions, answers,
 * and point values.
 */
void TriviaList(TriviaNode*& head) {
    //Head is the first question in the list.
    head = new TriviaNode("How long was the shortest war on record? "
                          "(Hint: how many minutes)", "38", 100);
    //SecondTriviaNode is the second question in the list.
    TriviaNode* secondTriviaNode = new TriviaNode("What was Bank of America’s "
                                                  "original name? (Hint: "
                                                  "Bank of Italy or Bank of Germany)",
                                                  "Bank of Italy", 50);
    //First question points to second question in the list.
    head->next = secondTriviaNode;
    //ThirdTriviaNode is the third and last question in the list.
    TriviaNode* thirdTriviaNode = new TriviaNode("What is the best-selling video game of "
                                                 "all time? (Hint: Call of Duty or "
                                                 "Wii Sports)?", "Wii Sports", 20);
    //Second question points to third and last question in the list.
    secondTriviaNode->next = thirdTriviaNode;
    //Third question points to end of list
    thirdTriviaNode->next = nullptr;
}


/*
 * STEP 4
 * Function that adds a TriviaNode object to the TriviaList.
 */
void addTriviaNode(TriviaNode*& head, TriviaNode* newTriviaNode) {
    //If TriviaList is empty, place new node in front
    if (head == nullptr) {
        head = newTriviaNode;
    }
        //Otherwise, place new TriviaNode after last TriviaNode in the list.
    else {
        TriviaNode* current = head;
        //Find the last TriviaNode in the list.
        while (current->next != nullptr) {
            current = current->next;
        }
        //Make the last TriviaNode point to the newTriviaNode.
        current->next = newTriviaNode;
    }
}


/*
 * STEP 5
 * Function that asks the player a certain number of questions from the TriviaList.
 */
int askingTriviaQuestions(TriviaNode* head, int numberOfQuestions) {

    //If number of questions is 0, issue a warning
    if (numberOfQuestions == 0) {
        cout << "Warning – The number of trivia to be asked must equal to or be larger than 1.";
        cout << endl;
        return 1;
    }

    int numberOfTrivia = countOfTriviaList(head);

    if (numberOfTrivia < numberOfQuestions) {
        cout << "Warning – There is only 3 trivia in the list.";
        cout << endl;
        return 1;
    }

    //Initialize total points to 0.
    int totalPoints = 0;
    //Initialize current TriviaNode to the head of TriviaList (first TriviaNode object)
    TriviaNode* current = head;

    //Player's answer
    string playerAnswer;

    //For every TriviaNode in the list,
    for (int i = 0; i < numberOfQuestions && current != nullptr; i++) {
        //Display a question and ask for user's answer.
        cout << "Question: " << current->question << endl;
        cout << "Answer: ";
        getline(cin, playerAnswer);

        //If player's answer is the correct answer, award them points
        if (playerAnswer == current->answer) {
            cout << "Your answer is correct. You receive " << current->points << " points.\n";
            totalPoints += current->points;
        }
            //Otherwise, they're wrong. Tell them the correct answer.
        else {
            cout << "Your answer is wrong. The correct answer is: " << current->answer << endl;

        }

        cout << "Your total points: " << totalPoints << endl << endl;

        //If number of questions is 1, and the question is wrong
        if (numberOfQuestions == 1 && playerAnswer != current->answer) {
            return 1;
        }

        //Move to the next TriviaNode object/question.
        current = current->next;

    }

    return 0;
}

#ifdef UNIT_TESTING
/*
 * STEP 6
 * TEST function that tests askingTriviaQuestions function.
 * Assuming there are 3 questions in TriviaList, the function covers the cases in which:
 * 0 questions are asked,
 * 1 question (the first) is asked from TriviaList,
 * 3 questions (all) are asked from TriviaList,
 * 5 questions (more than expected) are asked from TriviaList
 */
void TESTaskingTriviaQuestions(TriviaNode* head) {
    cout << "*** This is a debugging version ***" << endl;

    //Test Case 1: 0 questions asked.
    cout << "Unit Test Case 1: Ask no question. The program should give a warning message\n";
    int result1 = askingTriviaQuestions(head, 0);
    assert(result1 == 1);
    cout << "Case 1 Passed\n";

    //Test Case 2.1: 1 question asked -- incorrect answer.
    cout << "\nUnit Test Case 2.1: Ask 1 question in the linked list. The tester enters "
         << "an incorrect answer.\n";
    int result2_1 = askingTriviaQuestions(head, 1);
    assert(result2_1 == 1);
    cout << "Case 2.1 Passed\n";

    //Test Case 2.2: 1 question asked -- correct answer.
    cout << "\nUnit Test Case 2.2: Ask 1 question in the linked list. The tester enters "
         << "a correct answer.\n";
    int result2_2 = askingTriviaQuestions(head, 1);
    assert(result2_2 == 0);
    cout << "Case 2.2 Passed\n";

    //Test Case 3: 3 questions asked
    cout << "\nUnit Test Case 3: Ask all the questions of the last trivia in the "
         << "linked list.\n";
    int result3 = askingTriviaQuestions(head, 3);
    assert(result3 == 0);
    cout << "Case 3 Passed\n";

    //Test Case 4: 5 questions asked
    cout << "\nUnit Test Case 4: Ask 5 questions in the linked list.\n";
    int result4 = askingTriviaQuestions(head, 5);
    assert(result4 == 1);
    cout << "Case 4 Passed\n";

    cout << "\n*** End of the Debugging Version ***";
}

int main() {

    TriviaNode* originalQuestions = nullptr;
    //Makes list of original questions
    TriviaList(originalQuestions);
    //Tests the original questions
    TESTaskingTriviaQuestions(originalQuestions);

    cout << endl;

    return 0;
}

#else

/*
 * Main function that plays the trivia game.
 */
int main() {

    //Welcome message
    cout << "*** Welcome to Demarco's trivia quiz game ***" << endl;

    //Initializes trivia list of 3 questions
    TriviaNode* triviaQuestions = nullptr;
    TriviaList(triviaQuestions);

    //Create player-created questions
    string userChoice;

    do {
        string question;
        string answer;
        int points;

        cout << "Enter a question: ";
        getline(cin, question);
        cout << "Enter an answer: ";
        getline(cin, answer);
        cout << "Enter award points: ";
        cin >> points;
        cin.ignore();  // Consume the newline character.

        //Creates the new TriviaNode
        TriviaNode* newTriviaNode = new TriviaNode(question, answer, points);
        //Adds the new TriviaNode to the list
        addTriviaNode(triviaQuestions, newTriviaNode);

        cout << "Continue? (Yes/No): ";
        getline(cin, userChoice);

    } while (userChoice == "Yes");

    cout << endl;

    //Number of Trivia Questions
    int triviaCount = countOfTriviaList(triviaQuestions);

    //Starts the actual trivia with all questions.
    //Allowing up to 5 player-created questions
    askingTriviaQuestions(triviaQuestions, triviaCount);

    //Goodbye message
    cout << "*** Thank you for playing the trivia quiz game. Goodbye! ***";

    cout << endl;

    return 0;
}

#endif
