//Demarco Guajardo
//dag0047@auburn.edu
//project1_Guajardo_dag0047.cpp
//I used g++ to compile my code.
//I used the project 1 hint on Canvas.
//I used stack overflow to help me with the loops for validating
//my variables.
//I used stack overflow to help me with using two warning messages
//for the monthly payment.


#include <iostream>
#include <limits>
using namespace std;

    int main() {

        //Currency Formatting
        cout.setf(ios::fixed);
        cout.setf(ios::showpoint);
        cout.precision(2);

        //Variable Initialization
        double loanAmount = 0;
        double interestRate = 0;
        double monthlyRate = 0;
        double monthlyPayment = 0;
        double monthlyInterest = 0;
        int month = 0;
        double interest = 0;
        double principal = 0;

        int totalMonths = 0;
        double totalInterestPaid = 0;


        //User Input for Loan, Interest Rate, and Monthly Payments

        //Loan
        while (true) {
            cout << "\nLoan Amount: ";
            if (cin >> loanAmount && loanAmount > 0) {
                break; //This input is valid. Exit the while loop.
            }
            else {
                cout << "(Invalid loan)";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        //Interest Rate
        while (true) {
            cout << "Interest Rate (% per year): ";
            if (cin >> interestRate && interestRate >= 0) {
                break; //This input is valid. Exit loop.
            }
            else {
                cout << "(Invalid interest rate)\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }


        //Initializing the total monthly rate and first monthly interest.
        monthlyRate = interestRate/12;
        monthlyInterest = (monthlyRate/100)*loanAmount;


        //Monthly Payment
        while (true) {
            cout << "Monthly Payments: ";
            if (cin >> monthlyPayment && monthlyPayment > 0 && monthlyPayment > monthlyInterest) {
                break; //Monthly payment input is valid.
            }
            else if (cin.fail() || monthlyPayment < 0) {
                cout << "(Invalid payment)\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else {
                cout << "(Insufficient payment)\n";
            }
        }

        //Creating rest of the output.
        cout << "\n********************************************************\n"
             << "        Amorization Table\n"
             << "********************************************************\n"
             << "Month   Balance        Payment Rate   Interest Principal\n";

        //Loop to fill table.
        while (loanAmount > 0) {
            //Starting Month
            if (month == 0) {

                cout << month++ << "\t\t$" << loanAmount;

                if (loanAmount < 1000) {
                    cout << " "; //Adding space for 3 digit # instead of 4 digit #.
                }

                cout << "       N/A     N/A"
                     << "    N/A      N/A\n";
            }
            //Remaining Months
            else {

                //Updating the variables.

                //Calculating monthly interest for new month.
                monthlyInterest = (monthlyRate/100) * loanAmount;
                //Calculating total interest paid.
                totalInterestPaid += monthlyInterest;
                //Check if balance is less than monthly payment.
                if (loanAmount < monthlyPayment) {
                    monthlyPayment = loanAmount + monthlyInterest; //Monthly payment becomes
                    principal = loanAmount; //Principal becomes entire balance.
                    loanAmount = 0; //Zero out the balance.
                }
                else {
                    //Calculating principal amount for new month.
                    principal = monthlyPayment - monthlyInterest;
                    //Subtracting the principal from old loan to update loan.
                    loanAmount -= principal;
                }


                //Displaying the amortization table for the current month.

                cout << month++ << "\t\t$" << loanAmount;

                if (loanAmount < 1000) {
                    cout << " "; //Adding space for 3 digit # instead of 4 digit #.
                }
                if (loanAmount < 100) {
                    cout << " "; //Adding space for 2 digit # instead of 3 digit #.
                }
                if (loanAmount < 10) {
                    cout << " "; //Adding space for 1 digit # instead of 2 digit #.
                }

                cout << "       " << monthlyPayment << "   "
                     << monthlyRate << "   " << monthlyInterest;

                if (monthlyInterest < 10) {
                    cout << " "; //Adding space for 1 digit # instead of 2 digit #.
                }

                cout << "    " << principal;

                if (principal < 10) {
                    cout << " "; // Adding space for 1 digit # instead of 2 digit #.
                }
                cout << "\n";
            }

        }
        //Displaying results.
        cout << "********************************************************\n";
        cout << "\nIt takes " << --month << " months to pay off the loan.\n"
             << "Total interest paid is: $" << totalInterestPaid
             << endl;

        return 0;
    }