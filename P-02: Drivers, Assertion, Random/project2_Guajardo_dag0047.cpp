/* Project 2
 * Demarco Guajardo
 * dag0047@auburn.edu
 * projecC2_Guajardo_dag0047.cpp
 * I used g++ to compile my code.
 * I used the project 2 hints on Canvas.
 * I used stack overflow to learn that you can add booleans
 * into an integer variable.
 * I used cplusplus.com to learn how to cast a variable.
 * I used a pdf from math.uaa.alaska.edu called RandomFunctions
 * to learn how to generate a random number.
 * I used stack overflow to learn to use time(nullptr).
 */

# include <iostream>
# include <cstdlib>
# include <assert.h>
# include <ctime>
using namespace std;

//Initializing Variables
const double AaronProbability = 1.0/3.0;
const double BobProbability = 1.0/2.0;
const double CharlieProbability = 1.0;

const int numOfDuels = 10000; //We're going to run 10,000 duels.

//Functions

/*
 * This function enters a prompt to hit "Enter" to continue.
 */
void continueKey() {
    cout << "Press Enter to continue...";
    cin.get();
}

/*
 * This function returns a boolean value returning true if at least two people
 * are still alive and returns false otherwise.
 */
bool atLeastTwoAlive(bool AaronAlive, bool BobAlive, bool CharlieAlive) {
    //Count how many are alive
    int totalAlive = AaronAlive + BobAlive + CharlieAlive;
    //Return boolean value depending on if at least two are alive.
    if (totalAlive >= 2) {
        return true;
    }
    return false;
}

/*
 * This function represents Aaron shooting under strategy 1.
 * Changes boolean values of BobAlive and CharlieAlive depending on whether
 * they died (false) or lived (true).
 */
void AaronShoots1(bool& BobAlive, bool& CharlieAlive) {
    //Generating number 0 to 1 for accuracy purposes.
    double random = static_cast<double>(rand())/RAND_MAX;

    //Checking if Aaron hit the target.
    if (random <= AaronProbability) {
        //Due to strategy 1, Aaron shoots the most accurate shooter still alive.
        if (CharlieAlive) {
            CharlieAlive = false; //Kill Charlie first since most dangerous.
        }
        else if (BobAlive) {
            BobAlive = false; //Charlie already dead; kill Bob instead.
        }
    }
    //If the condition above doesn't run, then Aaron missed.
}

/*
 * This function represents Bob shooting under strategy 1.
 * Changes boolean values of AaronAlive and CharlieAlive depending on
 * whether they died (false) or lived (true).
 */
void BobShoots(bool& AaronAlive, bool& CharlieAlive) {
    //Generate num from 0-1.
    double random = static_cast<double>(rand())/RAND_MAX;

    //Checking if Bob hit.
    if (random <= BobProbability) {
        //Bob will always shoot most dangerous shooter.
        if (CharlieAlive) {
            CharlieAlive = false; //Kill Charlie first.
        }
        else if (AaronAlive) {
            AaronAlive = false; //Charlie already dead. Kill Aaron.
        }
    }
    //If condition above not met, then he missed.
}

/*
 * This function represents Charlie shooting under strategy 1.
 * Changes boolean values of AaronAlive and BobAlive depending on
 * whether they died (false) or lived (true).
 */
void CharlieShoots(bool& AaronAlive, bool& BobAlive) {
    //Charlie will shoot the next most dangerous shooter.
    //Charlie never misses.
    if (BobAlive) {
        BobAlive = false; //Kill Bob first.
    }
    else if (AaronAlive) {
        AaronAlive = false; //Bob already dead. Kill Aaron.
    }
}

/*
 * This function represents Aaron shooting under strategy 2.
 * This means he will intentionally miss his first shot, while the
 * rest of the duel will follow Strategy 1.
 * Changes boolean value of BobAlive and CharlieAlive depending on
 * whether they died (false) or lived (true).
 */
void AaronShoots2(bool& BobAlive, bool& CharlieAlive) {
    //Generating number 0 to 1 for accuracy purposes.
    double random = static_cast<double>(rand())/RAND_MAX;

    //Aaron intentionally misses his first shot (since both are alive) and follows up
    //with Strategy 1.
    if (BobAlive && CharlieAlive) {
        BobAlive = true;
        CharlieAlive = true;
        return;
    }

    //Checking if Aaron hit the target.
    else if (random <= AaronProbability) {
        //Due to strategy 1, Aaron shoots the most accurate shooter still alive.
        if (CharlieAlive) {
            CharlieAlive = false; //Kill Charlie first since most dangerous.
        }
        else if (BobAlive) {
            BobAlive = false; //Charlie already dead; kill Bob instead.
        }
    }
    //If condition doesn't go in, then Aaron missed.
}

//Testing the Functions

//Testing atLeastTwoAlive
void TESTAtLeastTwoAlive(void) {
    cout << "Unit Testing 1: Function - atLeastTwoAlive()\n";

    //Testing Case 1
    cout << "\tCase 1: Aaron alive, Bob alive, Charlie alive\n";
    assert(true == atLeastTwoAlive(true, true, true));
    cout << "\tCase passed ...\n";

    //Testing Case 2
    cout << "\tCase 2: Aaron dead, Bob alive, Charlie alive\n";
    assert(true == atLeastTwoAlive(false, true, true));
    cout << "\tCase passed ...\n";

    //Testing Case 3
    cout << "\tCase 3: Aaron alive, Bob dead, Charlie alive\n";
    assert(true == atLeastTwoAlive(true, false, true));
    cout << "\tCase passed ...\n";

    //Testing Case 4
    cout << "\tCase 4: Aaron alive, Bob alive, Charlie dead\n";
    assert(true == atLeastTwoAlive(true, true, false));
    cout << "\tCase passed ...\n";

    //Testing Case 5
    cout << "\tCase 5: Aaron dead, Bob dead, Charlie alive\n";
    assert(false == atLeastTwoAlive(false, false, true));
    cout << "\tCase passed ...\n";

    //Testing Case 6
    cout << "\tCase 6: Aaron dead, Bob alive, Charlie dead\n";
    assert(false == atLeastTwoAlive(false, true, false));
    cout << "\tCase passed ...\n";

    //Testing Case 7
    cout << "\tCase 7: Aaron alive, Bob dead, Charlie dead\n";
    assert(false == atLeastTwoAlive(true, false, false));
    cout << "\tCase passed ...\n";

    //Testing Case 8
    cout << "\tCase 8: Aaron dead, Bob dead, Charlie dead\n";
    assert(false == atLeastTwoAlive(false, false, false));
    cout << "\tCase passed ...\n";

    //Press Enter to Continue
    continueKey();
}

//Testing AaronShoots1
void TESTAaronShoots1(void) {
    cout << "\nUnit Testing 2: Function - AaronShoots1(BobAlive, CharlieAlive)\n";

    //Testing Case 1
    cout << "\tCase 1: Bob alive, Charlie alive\n";
    bool BobAliveC1 = true;
    bool CharlieAliveC1 = true;
    AaronShoots1(BobAliveC1, CharlieAliveC1);
    assert((BobAliveC1 && !CharlieAliveC1) || (BobAliveC1 && CharlieAliveC1));
    cout << "\t\tAaron is shooting at Charlie\n";

    //Testing Case 2
    cout << "\tCase 2: Bob dead, Charlie alive\n";
    bool BobAliveC2 = false;
    bool CharlieAliveC2 = true;
    AaronShoots1(BobAliveC2, CharlieAliveC2);
    assert((!BobAliveC2 && !CharlieAliveC2) || (!BobAliveC2 && CharlieAliveC2));
    cout << "\t\tAaron is shooting at Charlie\n";

    //Testing Case 3
    cout << "\tCase 3: Bob alive, Charlie dead\n";
    bool BobAliveC3= true;
    bool CharlieAliveC3 = false;
    AaronShoots1(BobAliveC3, CharlieAliveC3);
    assert((!BobAliveC3 && !CharlieAliveC3) || (BobAliveC3 && !CharlieAliveC3));
    cout << "\t\tAaron is shooting at Bob\n";

    //Press Enter to Continue.
    continueKey();
}

//Testing BobShoots
void TESTBobShoots(void) {
    cout << "\nUnit Testing 3: Function - BobShoots(AaronAlive, CharlieAlive)\n";
    
    //Testing Case 1
    cout << "\tCase 1: Aaron alive, Charlie alive\n";
    bool AaronAliveC1 = true;
    bool CharlieAliveC1 = true;
    BobShoots(AaronAliveC1, CharlieAliveC1);
    assert((AaronAliveC1 && !CharlieAliveC1) || (AaronAliveC1 && CharlieAliveC1));
    cout << "\t\tBob is shooting at Charlie\n";

    //Testing Case 2
    cout << "\tCase 2: Aaron dead, Charlie alive\n";
    bool AaronAliveC2 = false;
    bool CharlieAliveC2 = true;
    BobShoots(AaronAliveC2, CharlieAliveC2);
    assert((!AaronAliveC2 & !CharlieAliveC2) || (!AaronAliveC2 && CharlieAliveC2));
    cout << "\t\tBob is shooting at Charlie\n";

    //Testing Case 3
    cout << "\tCase 3: Aaron alive, Charlie dead\n";
    bool AaronAliveC3 = true;
    bool CharlieAliveC3 = false;
    BobShoots(AaronAliveC3, CharlieAliveC3);
    assert((!AaronAliveC3 && !CharlieAliveC3) || (AaronAliveC3 && !CharlieAliveC3));
    cout << "\t\tBob is shooting at Aaron\n";

    continueKey();
}

//Testing CharlieShoots
void TESTCharlieShoots(void) {
    cout << "\nUnit Testing 4: Function - CharlieShoots(AaronAlive, BobAlive)\n";

    //Testing Case 1
    cout << "\tCase 1: Aaron alive, Bob alive\n";
    bool AaronAliveC1 = true;
    bool BobAliveC1 = true;
    CharlieShoots(AaronAliveC1, BobAliveC1);
    assert((AaronAliveC1 && !BobAliveC1) || (AaronAliveC1 && BobAliveC1));
    cout << "\t\tCharlie is shooting at Bob\n";

    //Testing Case 2
    cout << "\tCase 2: Aaron dead, Bob alive\n";
    bool AaronAliveC2 = false;
    bool BobAliveC2 = true;
    CharlieShoots(AaronAliveC2, BobAliveC2);
    assert((!AaronAliveC2 && !BobAliveC2) || (!AaronAliveC2 && BobAliveC2));
    cout << "\t\tCharlie is shooting at Bob\n";

    //Testing Case 3
    cout << "\tCase 3: Aaron alive, Bob dead\n";
    bool AaronAliveC3 = true;
    bool BobAliveC3 = false;
    CharlieShoots(AaronAliveC3, BobAliveC3);
    assert((!AaronAliveC3 && !BobAliveC3) || (AaronAliveC3 && !BobAliveC3));
    cout << "\t\tCharlie is shooting at Aaron\n";

    continueKey();
}

//Testing AaronShoots2
void TESTAaronShoots2(void) {
    cout << "\nUnit Testing 5: Function - AaronShoots2(BobAlive, CharlieAlive)\n";

    //Testing Case 1
    cout << "\tCase 1: Bob alive, Charlie alive\n";
    bool BobAliveC1 = true;
    bool CharlieAliveC1 = true;
    AaronShoots2(BobAliveC1, CharlieAliveC1);
    assert(BobAliveC1 && CharlieAliveC1);
    cout << "\t\tAaron intentionally misses his first shot\n"
         << "\t\tBoth Bob and Charlie are alive.\n";
    //Testing Case 2
    cout << "\tCase 2: Bob dead, Charlie alive\n";
    bool BobAliveC2 = false;
    bool CharlieAliveC2 = true;
    AaronShoots2(BobAliveC2, CharlieAliveC2);
    assert((!BobAliveC2 && !CharlieAliveC2) || (!BobAliveC2 && CharlieAliveC2));
    cout << "\t\tAaron is shooting at Charlie\n";
    //Testing Case 3
    cout << "\tCase 3: Bob alive, Charlie dead\n";
    bool BobAliveC3 = true;
    bool CharlieAliveC3 = false;
    AaronShoots2(BobAliveC3, CharlieAliveC3);
    assert((!BobAliveC3 && !CharlieAliveC3) || (BobAliveC3 && !CharlieAliveC3));
    cout << "\t\tAaron is shooting at Bob\n";

    continueKey();
}

/*
 * The actual simulation.
 */
int main() {
    //Creating new number each time.
    srand(static_cast<unsigned>(time(nullptr)));

    cout << "*** Welcome to Demarco's Duel Simulator ***" << endl;

    //Start running tests.
    TESTAtLeastTwoAlive();
    TESTAaronShoots1();
    TESTBobShoots();
    TESTCharlieShoots();
    TESTAaronShoots2();


    //Formatting the percentages.
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    //STRATEGY 1

    //Continuing Output
    cout << "\nReady to test strategy 1 (run 10000 times):\n";
    continueKey();

    //Keeping track for everyone's wins
    int AaronWinsS1 = 0;
    int BobWinsS1 = 0;
    int CharlieWinsS1 = 0;

    //Running through 10k duels for strategy 1
    for (int i = 0; i < numOfDuels; i++) {

        //Everyone starts the duel alive
        bool AaronAlive = true;
        bool BobAlive = true;
        bool CharlieAlive = true;

        //Start playing.
        while(atLeastTwoAlive(AaronAlive, BobAlive, CharlieAlive)) {
            //Aaron starts or is his turn; he shoots the stronger opponent.
            if (AaronAlive) {
                AaronShoots1(BobAlive, CharlieAlive);
            }
            //Bob's turn. He shoots the stronger opponent.
            if (BobAlive) {
                BobShoots(AaronAlive, CharlieAlive);
            }
            //Charlie's turn. He shoots stronger opponent.
            if (CharlieAlive) {
                CharlieShoots(AaronAlive, BobAlive);
            }
        }

        //Change the win counters based on who lived.
        if (AaronAlive) {
            AaronWinsS1++;
        }
        else if (BobAlive) {
            BobWinsS1++;
        }
        else {
            CharlieWinsS1++;
        }

    }

    //Calculate Win Percentage Per Person for Strategy 1
    double WinPercentageAaronS1 = (static_cast<double>(AaronWinsS1)/numOfDuels) * 100;
    double WinPercentageBobS1 = (static_cast<double>(BobWinsS1)/numOfDuels) * 100;
    double WinPercentageCharlieS1 = (static_cast<double>(CharlieWinsS1)/numOfDuels) * 100;



    //Display Results of Strategy 1
    cout << "\nAaron won " << AaronWinsS1 << "/" << numOfDuels << " duels or "
         << WinPercentageAaronS1 << "%";
    cout << "\nBob won " << BobWinsS1 << "/" << numOfDuels << " duels or "
         << WinPercentageBobS1 << "%";
    cout << "\nCharlie won " << CharlieWinsS1 << "/" << numOfDuels << " duels or "
         << WinPercentageCharlieS1 << "%\n";

    //STRATEGY 2

    //Continuing Output
    cout << "\nReady to test strategy 2 (run 10000 times):\n";
    continueKey();

    //Keeping track of everyone's wins.
    int AaronWinsS2 = 0;
    int BobWinsS2 = 0;
    int CharlieWinsS2 = 0;

    //Running through 10k duels for strategy 2
    for (int i = 0; i < numOfDuels; i++) {

        //Everyone starts the duel alive
        bool AaronAlive = true;
        bool BobAlive = true;
        bool CharlieAlive = true;

        //Start playing.
        while (atLeastTwoAlive(AaronAlive, BobAlive, CharlieAlive)) {
            //Aaron starts or is his turn; he shoots the stronger opponent.
            if (AaronAlive) {
                AaronShoots2(BobAlive, CharlieAlive);
            }

            //Bob's turn. He shoots the stronger opponent.
            if (BobAlive) {
                BobShoots(AaronAlive, CharlieAlive);
            }

            //Charlie's turn. He shoots stronger opponent.
            if (CharlieAlive) {
                CharlieShoots(AaronAlive, BobAlive);
            }
        }

        //Change the win counters based on who lived.
        if (AaronAlive) {
            AaronWinsS2++;
        } else if (BobAlive) {
            BobWinsS2++;
        } else {
            CharlieWinsS2++;
        }
    }

    //Calculate Win Percentage Per Person for Strategy 2
    double WinPercentageAaronS2 = (static_cast<double>(AaronWinsS2)/numOfDuels) * 100;
    double WinPercentageBobS2 = (static_cast<double>(BobWinsS2)/numOfDuels) * 100;
    double WinPercentageCharlieS2 = (static_cast<double>(CharlieWinsS2)/numOfDuels) * 100;

    //Display Results of Strategy 2
    cout << "\nAaron won " << AaronWinsS2 << "/" << numOfDuels << " duels or "
         << WinPercentageAaronS2 << "%";
    cout << "\nBob won " << BobWinsS2 << "/" << numOfDuels << " duels or "
         << WinPercentageBobS2 << "%";
    cout << "\nCharlie won " << CharlieWinsS2 << "/" << numOfDuels << " duels or "
         << WinPercentageCharlieS2 << "%\n";


    // WHICH STRATEGY IS BETTER?

    if (WinPercentageAaronS1 > WinPercentageAaronS2) {
        cout << "\nStrategy 1 is better than strategy 2.\n";
    }
    else {
        cout << "\nStrategy 2 is better than strategy 1.\n";
    }


    return 0;
}
