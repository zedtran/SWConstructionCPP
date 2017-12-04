//
// Name:            Donald Tran
// Date:            02/05/17
// AU User ID:      DZT0021
// File Name:       hw2.cpp
//
// Instructions to compile:
// g++ -std=c++11 hw2.cpp
// 
// README:
// This program was created using the "CLion" IDE and 
// compiled using CMake Version 3.6 and the g++ compiler on 
// Tux056 via SSH Protocol
//

#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

int main () {

    double balanceAmt, annualRate, monthpAmt;
    double monthRate, princpAmt, minimumpAmt;
    double interest, totalInterest;
    int monthCount = 0;

    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);

    cout << "\nLoan Amount: ";
    cin >> balanceAmt;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entry Invalid. Enter a 'number' to try again.\n\n";
        cout << "Loan Amount: ";
        cin >> balanceAmt;
    }

    cout << "Interest Rate (% per year): ";
    cin >> annualRate;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entry Invalid. Enter a 'number' to try again.\n\n";
        cout << "Interest Rate (% per year): ";
        cin >> annualRate;
    }

    cout << "Monthly Payments: ";
    cin >> monthpAmt;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entry Invalid. Enter a 'number' to try again.\n\n";
        cout << "Monthly Payments:: ";
        cin >> monthpAmt;
    }

    // Calculates the monthly interest rate which will be used
    // to determine the amount of interest compounded each month
    monthRate = (annualRate / 100) / 12;
    minimumpAmt = balanceAmt * monthRate;

    if (monthpAmt <= minimumpAmt) {
        cout << "\n\nYour monthly minimum payment must be ";
        cout << "greater than " << minimumpAmt << " in order to pay off this debt.\n";
        cout << "Please try again later.\n\n";
        return 0;
    }

    cout << "\n********************************************************************************\n";
    cout << "\t\t\tAmortization Table\n";
    cout << "********************************************************************************\n";

    cout << left << setw(8) << setfill(' ') << "Month";
    cout << left << setw(15) << setfill(' ') << "Balance";
    cout << left << setw(15) << setfill(' ') << "Payment";
    cout << left << setw(15) << setfill(' ') << "Rate";
    cout << left << setw(15) << setfill(' ') << "Interest";
    cout << left << setw(15) << setfill(' ') << "Principal" << endl;

    cout << left << setw(8) << setfill(' ') << "0";
    cout << "$";
    cout << left << setw(14) << setfill(' ') << balanceAmt;
    cout << left << setw(15) << setfill(' ') << "N/A";
    cout << left << setw(15) << setfill(' ') << "N/A";
    cout << left << setw(15) << setfill(' ') << "N/A";
    cout << left << setw(15) << setfill(' ') << "N/A" << endl;

    while  (monthpAmt <= balanceAmt) {
        interest = balanceAmt * monthRate;
        princpAmt = monthpAmt - interest;
        balanceAmt -= princpAmt;
        totalInterest += interest;
        ++monthCount;

        cout << left << setw(8) << setfill(' ') << monthCount;
        cout << "$";
        cout << left << setw(14) << setfill(' ') << balanceAmt;
        cout << "$";
        cout << left << setw(14) << setfill(' ') << monthpAmt;
        cout << left << setw(15) << setfill(' ') << (monthRate * 100);
        cout << "$";
        cout << left << setw(14) << setfill(' ') << interest;
        cout << "-$";
        cout << left << setw(15) << setfill(' ') << princpAmt << endl;
    }

    if (monthpAmt > balanceAmt && balanceAmt > 0) {
        monthpAmt = balanceAmt;
        interest = monthpAmt * monthRate;
        princpAmt = balanceAmt;
        totalInterest += interest;
        balanceAmt = 0;
        ++monthCount;

        cout << left << setw(8) << setfill(' ') << monthCount;
        cout << "$";
        cout << left << setw(14) << setfill(' ') << balanceAmt;
        cout << "$";
        cout << left << setw(14) << setfill(' ') << monthpAmt;
        cout << left << setw(15) << setfill(' ') << (monthRate * 100);
        cout << "$";
        cout << left << setw(14) << setfill(' ') << interest;
        cout << "-$";
        cout << left << setw(15) << setfill(' ') << princpAmt << endl;

    }

    cout << "********************************************************************************\n\n";
    cout << "It takes " << monthCount << " months to pay off your loan.\n";
    cout << "Total interest paid is: $" << totalInterest << endl;
    return 0;

}
