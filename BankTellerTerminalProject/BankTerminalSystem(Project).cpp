////////////////////////////////////////////////////////////////////////////////
// Name:            Donald Tran                                               //
// Date:            04/20/17                                                  //
// AU User ID:      DZT0021                                                   //
// File Name:       Project2.cpp                                              //
//                                                                            //
// Instructions to compile:                                                   //
// g++ -std=c++11 -Wall -g -o Project2 Project2.cpp                           //
//                                                                            //
// Ran driver with the following command: ./Project2                          //
//                                                                            //
// Read Me:                                                                   //
// This program was created using "CLion" IDE and                             //
// compiled using CMake version 3.6 and the g++ compiler on                   //
// Tux064 via SSH protocol.                                                   //
//                                                                            //
// References:                                                                //
// (1) http://en.cppreference.com/w/cpp/language/template_specialization      //
// (2) http://www.cplusplus.com/reference/sstream/stringstream/               //
// (3) http://stackoverflow.com/questions/3946558/c-read-from                 //
//     -text-file-and-separate-into-variable                                  //
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <iomanip>
#include <limits>
#include <locale>
#include <cctype>
#undef max
using namespace std;

// Global Class Declarations //
class AdminMenu;
class ClientMenu;
class SystemMenu;
class Client;

// Global Struct Declarations //
struct Account;
struct User;

// Global constant //
static const int MAX_SIZE = 1000;

/*******************************************************************
 * User is a struct which represents one of two types of Terminal  *
 * System end users--System Admin and Branch Staff Member. User    *
 * has no functionality and is only instantiated to retain user    *
 * information until such time User's values need to be recorded   *
 * or retrieved for authentication purposes.                       *
 *******************************************************************/
struct User {
    string userName = "";
    int userRole;
    string userPassword = "";
};

/*********************************************************************
 * The struct Account contains information about client accounts and *
 * is maintained separate from client data. It includes account      *
 * number, account balance, and account type.                        *
 *********************************************************************/
struct Account {
    string acctNum = "NA";
    string acctType = "NA";
    int acctBalance = 0;
};

/***********************************************************************************
 * Client is a class which contains member variables associated with               *
 * bank clientele. There are two instances of Client in ClientMenu--one            *
 * for data on current clients and the other is for new clientele being created.   *
 ***********************************************************************************/
class Client {

private:
    // Member Variables
    string cName, cAddress, cSSAN, cEmployer;
    int cIncome;

public:
    // Member struct
    Account account;

    //Member Functions
    string getName();
    string getAddress();
    string getSocial();
    string getEmployer();
    int getIncome();
    void setName(string nameIn);
    void setAddress(string addressIn);
    void setSocial(string socialIn);
    void setEmployer(string employerIn);
    void setIncome(int incomeIn);

    // Member struct functions
    string getAcctNum();
    int getAcctBal();
    string getAcctType();
    void setAcctNum(string acctNumIn);
    void setAcctBal(int balanceIn);
    void setAcctType(int acctTypeIn);

};

/**
 * @return client name
 */
string Client::getName() {
        return cName;
}

/**
 * @return client address
 */
string Client::getAddress() {
        return cAddress;
}

/**
 * @return client social security number
 */
string Client::getSocial() {
        return cSSAN;
}

/**
 * @return client employer
 */
string Client::getEmployer() {
        return cEmployer;
}

/**
 * @return client income
 */
int Client::getIncome() {
        return cIncome;
}

/**
 * Sets client name
 * @param nameIn
 */
void Client::setName(string nameIn) {
        cName = nameIn;
}

/**
 * Sets client address
 * @param addressIn
 */
void Client::setAddress(string addressIn) {
        cAddress = addressIn;
}

/**
 * Sets client social security number
 * @param socialIn
 */
void Client::setSocial(string socialIn) {
        cSSAN = socialIn;
}

/**
 * Sets client employer
 * @param employerIn
 */
void Client::setEmployer(string employerIn) {
        cEmployer = employerIn;
}

/**
 * Sets client income
 * @param incomeIn
 */
void Client::setIncome(int incomeIn) {
        cIncome = incomeIn;
}

/**
 * @return client account number
 */
string Client::getAcctNum() {
        return account.acctNum;
}

/**
 * @return client account balance
 */
int Client::getAcctBal() {
        return account.acctBalance;
}

/**
 * @return client account type (Branch employee or Administrator)
 */
string Client::getAcctType() {
        return account.acctType;
}

/**
 * Sets client account number
 * @param acctNumIn
 */
void Client::setAcctNum(string acctNumIn) {
       account.acctNum = acctNumIn;
}

/**
 * Sets client account balance
 * @param balanceIn
 */
void Client::setAcctBal(int balanceIn) {
        account.acctBalance = balanceIn;
}

/**
 * Sets client account type (Savings or Checking)
 * @param acctTypeIn '1' for Checking and '2' for Savings
 */
void Client::setAcctType(int acctTypeIn) {
    if (acctTypeIn == 1) {
        account.acctType = "checking";
    }
    if (acctTypeIn == 2) {
        account.acctType = "savings";
    }
    if (acctTypeIn != 1 && acctTypeIn != 2){
        cout << "\nInvalid account type.\n" << endl;
    }
}

/***********************************************************************
 * ClientMenu is a friend of SystemMenu and handles all attributes     *
 * manipulation of Clients and Accounts contained within.              *
 * Furthermore, ClientMenu can add new clients to the bank and modify  *
 * client data to include depositing and withdrawing client funds.     *
 * ClientMenu manages file I/O manipulation for client records.        *
 ***********************************************************************/
class ClientMenu {

private:
    // Member Class and Variables
    ifstream fileIn;
    string line;
    int writeSize = 0;
    int readSize = 0;

public:
    friend class Client;
    friend class SystemMenu;
    // Member Variables
    string namesArr[MAX_SIZE];
    string addressArr[MAX_SIZE];
    string ssanArr[MAX_SIZE];
    string employArr[MAX_SIZE];
    int incomeArr[MAX_SIZE];
    string acctNumArr[MAX_SIZE];
    int acctBalArr[MAX_SIZE];
    string acctTypeArr[MAX_SIZE];
    Client client;

    // Member Functions
    void readClientData();
    void writeClientData();
    void addClient();
    void addAccount();
    void editClient();
    void manageAcct();

};

/********************************************************************
* GLOBAL BASE TEMPLATE FUNCTION                                     *
* Tokenizes each line from a given text stream.                     *
* Allows for conversion to a specified data type.                   *
*********************************************************************/
template <typename T>
void getVal(stringstream &ss, T &val) {
    string token;
    getVal(ss, token);
    stringstream ss2(token);
    ss2>>val;
}
/*************************************************
 * EXPLICIT FUNCTION SPECIALIZATION              *
 * Overloads the base template.                  *
 * Uses getline() with a separator specification *
 *************************************************/
template <>
void getVal<string>(stringstream &ss, string &val)
{
    getline(ss, val, '\t'); //Note the separator specification
}

/******************************************************************
 * Reads client data from input file into member variable arrays. *
 * Input file: "clients.txt". Refer to template function getVal() *
 ******************************************************************/
void ClientMenu::readClientData() {
    string name, address, social, employer, acctNumber, acctType;
    int income, acctBalance;
    int i = 0;
    fileIn.open("clients.txt");
    while (getline(fileIn, line)) {
            stringstream ss(line);
            getVal(ss, name);
            getVal(ss, address);
            getVal(ss, social);
            getVal(ss, employer);
            getVal(ss, income);
            getVal(ss, acctNumber);
            getVal(ss, acctBalance);
            getVal(ss, acctType);
            namesArr[i] = name;
            addressArr[i] = address;
            ssanArr[i] = social;
            employArr[i] = employer;
            incomeArr[i] = income;
            acctNumArr[i] = acctNumber;
            acctBalArr[i] = acctBalance;
            acctTypeArr[i] = acctType;
            i++;
            readSize++;
    }
    fileIn.close();
}

/********************************************************
 * Writes updated client information to file output.    *
 * Output file: "clients.txt"                           *
 ********************************************************/
void ClientMenu::writeClientData() {
    ofstream outFile("clients.txt");
    if (outFile.is_open()) {
        for (int i = 0; i < MAX_SIZE; i++) {
            outFile << namesArr[i] << "\t" << addressArr[i]
                    << "\t" << ssanArr[i] <<  "\t" << employArr[i]
                    << "\t" << incomeArr[i] << "\t" << acctNumArr[i]
                    << "\t" << acctBalArr[i] << "\t" << acctTypeArr[i] << endl;
            if (acctTypeArr[i + 1] == "") {
                break;
            }
            writeSize++;
        }
        outFile.close();
    } else {
        cout << "ERROR: There was an issue writing client data to file.\n" << endl;
    }
}

/**
 * Adds a new client
 */
void ClientMenu::addClient() {
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    bool quit = false;
    int namespaces;
    int digitCount;
    int letterCount;
    while (!quit) {
        char name[MAX_SIZE], address[MAX_SIZE], social[MAX_SIZE],
                employer[MAX_SIZE], income[MAX_SIZE];
        cout << "\nA new client will be added:" << endl;

        // NAME INPUT //
        cout << "\nClient name: ";
        cin.getline(name, 50);
        namespaces = 0;
        digitCount = 0;
        letterCount = 0;
        string nam(name);
        for (int a = 0; a < nam.size(); a++) {
            if (!(isalpha(name[a])) && !(isspace(name[a])))  {
                letterCount++;
            }
            if (isdigit(name[a])) {
                digitCount++;
            }
            if (isspace(name[a])) {
                namespaces++;
            }
        }
        if (letterCount >= 1) {
            cout << "\n\tError - Client name must not contain non-alphabetic characters.";
            cout << " Try again.\n";
        }
        if (digitCount >= 1) {
            cout << "\n\tError - Client name must not contain numeric characters.";
            cout << " Try again.\n";
        }
        if (namespaces < 1) {
            cout << "\n\tError - Please include (at minimum) the first and last name.";
            cout << " Try again.\n";
        }
        if (namespaces > 2) {
            cout << "\n\tError - Please provide no more than client first, middle, and last name.";
            cout << " Try again.\n";
        }
        if (nam.size() > 50) {
            cout << "\n\tError - Please limit client name to 50 characters.";
            cout << " Try again.\n";
        }
        if (letterCount >= 1 || digitCount >= 1 || namespaces < 1 || namespaces >= 3 || nam.size() > 50) {
            continue;
        }
        client.setName(nam);

        // ADDRESS INPUT //
        cout << "Address: ";
        cin.getline(address, 100);
        string addr(address);
        client.setAddress(addr);

        // SSN INPUT //
        cout << "Social Security Number: ";
        cin.getline(social, 12);
        namespaces = 0;
        digitCount = 0;
        letterCount = 0;
        string soc(social);
        for (int b = 0; b < soc.size(); b++) {
            if (isalpha(social[b])) {
                letterCount++;
            }
            if (isdigit(social[b])) {
                digitCount++;
            }
            if (isspace(social[b])) {
                namespaces++;
            }
        }
        if (letterCount >= 1) {
            cout << "\n\tError - Client SSN must not contain alphabetic characters.";
            cout << " Try again.\n";
        }
        if (digitCount != 9) {
            cout << "\n\tError - Client SSN must contain 9 digits.";
            cout << " Try again.\n";
        }
        if (namespaces >= 1) {
            cout << "\n\tError - Client SSN may not include spaces.";
            cout << " Try again.\n";
        }
        if (soc.size() > 11) {
            cout << "\n\tError - Limit client SSN to 11 characters (if using hyphen).";
            cout << " Try again.\n";
        }
        if (letterCount >= 1 || digitCount != 9 || namespaces >= 1 || soc.size() > 11) {
            continue;
        }
        client.setSocial(soc);

        // EMPLOYER INPUT //
        cout << "Employer: ";
        cin.getline(employer, 100);
        string emp(employer);
        client.setEmployer(emp);

        // INCOME INPUT //
        cout << "Annual Income: ";
        cin.getline(income, 100);
        string inc(income);
        int ndigiCount = 0;
        int spaceCount = 0;
        for (int g = 0; g < inc.size(); g++) {
            if (!isdigit(inc[g])) {
                ndigiCount++;
            }
            if (isspace(inc[g])) {
                spaceCount++;
            }
        }
        if (ndigiCount >= 1) {
            cout << "\n\tError - The income amount must be a numeric value"
                    "\n\t\t\tand cannot include any special characters. Try again.\n";
        }
        if (spaceCount >= 1) {
            cout << "\n\tError - The income must contain no spaces. Try again.\n";
        }
        if (ndigiCount >= 1 || spaceCount >= 1) {
            continue;
        }
        client.setIncome(stoi(inc));


        // Reads client data, writes new client values to EOF
        readClientData(); // Reads client file data to to populate client information
        namesArr[readSize] = client.getName();
        addressArr[readSize] = client.getAddress();
        ssanArr[readSize] = client.getSocial();
        employArr[readSize] = client.getEmployer();
        incomeArr[readSize] = client.getIncome();
        acctTypeArr[readSize] = client.getAcctType();
        acctBalArr[readSize] = client.getAcctBal();
        acctNumArr[readSize] = client.getAcctNum();
        writeClientData();
        cout << "\nA new client was added!" << endl;
        cout << "\nPress enter to continue...\n";
        cin.get();
        cin.sync();
        quit = true;

    }
}

/**
 * Adds a new account for an existing client
 * who does not currently have an account
 */
void ClientMenu::addAccount() {
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    int clientIndex;
    char acctNum[MAX_SIZE];
    char acctType[MAX_SIZE];
    char acctBal[MAX_SIZE];
    bool quit = false;
    char clientName[MAX_SIZE];
    bool found = false;
    while (!quit) {
        cout << "\nChoose a client: ";
        cin.getline(clientName, 100);
        string cli(clientName);
        readClientData(); // Read client data first
        for (int i = 0; i < readSize; i++) {
            if (namesArr[i] == cli) {
                clientIndex = i;
                found = true;
            }
        }
        if (!found) {
            cout << "\n\tError - The client '" << cli << "' is not in the system.";
            cout << " Try again.\n";
            continue;
        }
        else if (found) {

            // Conditions for client account number
            cout << "\nA new account will be created for " << cli << "..." << endl;
            cout << "\nAccount Number: ";
            cin.getline(acctNum, 100);
            string actNum(acctNum);
            int ndigiCount = 0;
            int spaceCount = 0;
            for (int j = 0; j < actNum.size(); j++) {
                if (!isdigit(actNum[j])) {
                    ndigiCount++;
                }
                if (isspace(actNum[j])) {
                    spaceCount++;
                }
            }
            if (ndigiCount >= 1) {
                cout << "\n\tError - The account number must contain only numeric values.";
                cout << " Try again.\n";
            }
            if (actNum.size() < 8 || actNum.size() > 10) {
                cout << "\n\tError - The account number must be 8 - 10 characters.";
                cout << " Try again.\n";
            }
            if (spaceCount >= 1) {
                cout << "\n\tError - The account number must contain no spaces.";
                cout << " Try again.\n";
            }
            if (ndigiCount >= 1 || actNum.size() < 8 || actNum.size() > 10 || spaceCount >= 1) {
                continue;
            }
            client.setAcctNum(actNum);


            // CONDITIONS FOR ACCOUNT TYPE
            cout << "\nAccount Type: ";
            cin.getline(acctType, 100);
            string actTyp(acctType);
            ndigiCount = 0;
            spaceCount = 0;
            for (int n = 0; n < actTyp.size(); n++) {
                actTyp[n] = tolower(actTyp[n]);
            }
            for (int k = 0; k < actTyp.size(); k++) {
                if (!isalpha(actTyp[k])) {
                    ndigiCount++;
                }
                if (isspace(actTyp[k])) {
                    spaceCount++;
                }
            }
            if (ndigiCount >= 1) {
                cout << "\n\tError - The account type must be either Checking or Savings"
                        "\n\t\t\tand cannot include any special characters. Try again.\n";
            }
            if (actTyp != "checking" && actTyp != "savings") {
                cout << "\n\tError - The account type entered does not exist! Try again\n";
            }
            if (spaceCount >= 1) {
                cout << "\n\tError - The account type must contain no spaces.";
                cout << " Try again.\n";
            }
            if (ndigiCount >= 1 || (actTyp != "checking" && actTyp != "savings") || spaceCount >= 1) {
                continue;
            }
            if (actTyp == "checking") {
                client.setAcctType(1);
            }
            if (actTyp == "savings") {
                client.setAcctType(2);
            }

            // CONDITIONS FOR ACCOUNT BALANCE
            cout << "\nBalance: ";
            cin.getline(acctBal, 100);
            string actBal(acctBal);
            ndigiCount = 0;
            spaceCount = 0;
            for (int g = 0; g < actBal.size(); g++) {
                if (!isdigit(actBal[g])) {
                    ndigiCount++;
                }
                if (isspace(actBal[g])) {
                    spaceCount++;
                }
            }
            if (ndigiCount >= 1) {
                cout << "\n\tError - The account balance must be a numeric value"
                        "\n\t\t\tand cannot include any special characters. Try again.\n";
            }
            if (spaceCount >= 1) {
                cout << "\n\tError - The account balance must contain no spaces. Try again.\n";
            }
            if (ndigiCount >= 1 || spaceCount >= 1) {
                continue;
            }
            client.setAcctBal(stoi(actBal));


            // Reads client data, writes new client values to EOF
            // Overwrites previous account placeholder values
            readClientData(); // Reads client file data to to populate client information
            acctTypeArr[clientIndex] = client.getAcctType();
            acctBalArr[clientIndex] = client.getAcctBal();
            acctNumArr[clientIndex] = client.getAcctNum();
            writeClientData();
            cout << "\nA new account was created for " << cli << "!" << endl;
            cout << "\nPress enter to continue...\n";
            cin.get();
            cin.sync();
            quit = true;

        }
    }

}


/**
 * Edit existing client information
 */
void ClientMenu::editClient() {
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    int clientIndex;
    char opt[MAX_SIZE];
    bool quit = false;
    char clientName[MAX_SIZE];
    bool found = false;
    while (!quit) {
        cout << "\nChoose a client: ";
        cin.getline(clientName, 100);
        string cli(clientName);
        readClientData(); // Read client data first
        for (int i = 0; i < readSize; i++) {
            if (namesArr[i] == cli) {
                clientIndex = i;
                found = true;
            }
        }
        if (!found) {
            cout << "\n\tError - The client '" << cli << "' is not in the system.";
            cout << " Try again.\n";
            continue;
        }
        if (found) {
            cout << "\nDisplay " << cli << "'s information:" << endl;
            cout << "Address: " << addressArr[clientIndex] << endl;
            cout << "Social Security Number: " << ssanArr[clientIndex] << endl;
            cout << "Employer: " << employArr[clientIndex] << endl;
            cout << "Annual Income: " << incomeArr[clientIndex] << endl;
            quit = true;
        }
    }
    if (quit) {
        cout << "\nClient " << namesArr[clientIndex] << "'s information will be updated..." << endl;
        bool cancel = false;
        while (!cancel) {
            cout << "\n1) Confirm" << endl;
            cout << "\n2) Cancel" << endl;
            cout << "\n\tPlease choose an option: ";
            cin.getline(opt, 100);
            string choice(opt);
            if (choice == "1") {
                bool next = false;
                int namespaces;
                int digitCount;
                int letterCount;
                while (!next) {
                    char address[MAX_SIZE], social[MAX_SIZE],
                            employer[MAX_SIZE], income[MAX_SIZE];

                    // ADDRESS INPUT //
                    cout << "\nAddress: ";
                    cin.getline(address, 100);
                    string addr(address);
                    client.setAddress(addr);

                    // SSN INPUT //
                    cout << "Social Security Number: ";
                    cin.getline(social, 12);
                    namespaces = 0;
                    digitCount = 0;
                    letterCount = 0;
                    string soc(social);
                    for (int b = 0; b < soc.size(); b++) {
                        if (isalpha(social[b])) {
                            letterCount++;
                        }
                        if (isdigit(social[b])) {
                            digitCount++;
                        }
                        if (isspace(social[b])) {
                            namespaces++;
                        }
                    }
                    if (letterCount >= 1) {
                        cout << "\n\tError - Client SSN must not contain alphabetic characters.";
                        cout << " Try again.\n";
                    }
                    if (digitCount != 9) {
                        cout << "\n\tError - Client SSN must contain 9 digits.";
                        cout << " Try again.\n";
                    }
                    if (namespaces >= 1) {
                        cout << "\n\tError - Client SSN may not include spaces.";
                        cout << " Try again.\n";
                    }
                    if (soc.size() > 11) {
                        cout << "\n\tError - Limit client SSN to 11 characters (if using hyphen).";
                        cout << " Try again.\n";
                    }
                    if (letterCount >= 1 || digitCount != 9 || namespaces >= 1 || soc.size() > 11) {
                        continue;
                    }
                    client.setSocial(soc);

                    // EMPLOYER INPUT //
                    cout << "Employer: ";
                    cin.getline(employer, 100);
                    string emp(employer);
                    client.setEmployer(emp);

                    // INCOME INPUT //
                    cout << "Annual Income: ";
                    cin.getline(income, 100);
                    string inc(income);
                    int e = 0;
                    for (int c = 0; c < inc.size(); c++) {
                        if (!isdigit(inc[c])) {
                            e++;
                        }
                    }
                    if (e >= 1) {
                        cout << "\n\tError - Income must only be numeric.";
                        cout << " Try again.\n";
                        continue;
                    }
                    int deci = stoi(inc);
                    client.setIncome(deci);

                    // Reads client data, writes new client values to EOF
                    readClientData(); // Reads client file data to to populate client information
                    addressArr[clientIndex] = client.getAddress();
                    ssanArr[clientIndex] = client.getSocial();
                    employArr[clientIndex] = client.getEmployer();
                    incomeArr[clientIndex] = client.getIncome();
                    writeClientData();
                    cout << "\nClient " << namesArr[clientIndex] << "'s information was updated!" << endl;
                    cout << "\nPress enter to continue...\n";
                    cin.get();
                    cin.sync();
                    next = true;
                    cancel = true;
                }

            }
            if (choice != "2" && choice != "1") {
                cout << "\nInvalid input. Try again.\n";
                continue;
            }
            if (choice == "2") {
                cancel = true;
            }
        }
    }
}

/**
 * Manage a client's account
 */
 void ClientMenu::manageAcct() {
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    char acctNum[MAX_SIZE];
    int clientIndex;
    bool found = false;
    bool quit = false;
    bool cancel = false;
    readClientData(); // Read client data first
    while (!quit) {
        cout << "\nWhich account will be managed? ";
        cin.getline(acctNum, 100);
        string actNum(acctNum);
        for (int i = 0; i < readSize; i++) {
            if (acctNumArr[i] == actNum) {
                clientIndex = i;
                found = true;
                quit = true;
            }
        }
        if (!found) {
            cout << "\n\tError - The account '" << actNum << "' is not in the system.\n";
            while (!cancel) {
                char opt[MAX_SIZE];
                cout << "\n1) Manage an Account." << endl;
                cout << "2) Cancel" << endl;
                cout << "\n\tPlease choose an option: ";
                cin.getline(opt, 100);
                string newOpt(opt);
                if (newOpt == "1") {
                    cancel = true;
                }
                else if (newOpt != "2") {
                    cout << "\nInvalid input. Try again.\n";
                    continue;
                }
                else {
                    quit = true;
                    break;
                }
            }
        }
    }
    if (found) {
        char opt[MAX_SIZE];
        bool f2 = false;
        char deposit[MAX_SIZE];
        char withdraw[MAX_SIZE];
        while (!f2) {
            cout << "\nManage account " << acctNumArr[clientIndex] << " for ";
            cout << namesArr[clientIndex] << endl;
            cout << "\n1) Deposit\n2) Withdraw\n3) Cancel\n";
            cout << "\n\tPlease choose an option: ";
            cin.getline(opt, 100);
            string s2(opt);
            if (s2 == "1") {
                cout << "\nDeposit Amount: ";
                cin.getline(deposit, 100);
                string dep(deposit);
                int d = 0;
                for (int c = 0; c < dep.size(); c++) {
                    if (!isdigit(dep[c])) {
                        d++;
                    }
                }
                if (d >= 1) {
                    cout << "\n\tError - Income can only be numeric!";
                    cout << " Try again.\n";
                    continue;
                }
                int deci = stoi(dep);
                int currentBal = acctBalArr[clientIndex];
                acctBalArr[clientIndex] = deci + currentBal;
                cout << "\nThe new balance of account "
                     << acctNumArr[clientIndex]
                     << " is : " << acctBalArr[clientIndex] << endl;
                writeClientData();
            }
            else if (s2 == "2") {
                cout << "\nWithdraw Amount: ";
                cin.getline(withdraw, 100);
                string with(withdraw);
                int e = 0;
                for (int c = 0; c < with.size(); c++) {
                    if (!isdigit(with[c])) {
                        e++;
                    }
                }
                if (e >= 1) {
                    cout << "\n\tError - Income can only be numeric!";
                    cout << " Try again.\n";
                    continue;
                }
                int deci2 = stoi(with);
                int currentBal = acctBalArr[clientIndex];
                if (currentBal < deci2) {
                    cout << "\nThe withdraw amount exceeds the current balance. Try again.\n";
                }
                if (currentBal >= deci2) {
                    acctBalArr[clientIndex] = currentBal - deci2;
                    cout << "\nThe new balance of account "
                         << acctNumArr[clientIndex]
                         << " is : " << acctBalArr[clientIndex] << endl;
                    writeClientData();
                }
            }
            else if (s2 == "3") {
                f2 = true;
            }
            else {
                cout << "\nInvalid Input. Try again.\n";
            }
        }
    }
}



/****************************************************************************
 * SystemMenu is the primary menu class comprising of all other menu class  *
 * objects it will call upon. It is responsible for transitioning the user  *
 * between "idle" and "active" menus and facilitates user login. It is the  *
 * class which handles password changes for existing TigerBank staff.       *
 ***************************************************************************/
class SystemMenu {

private:
    // Member Variables
    char newPw[MAX_SIZE];
    User currentUser;
    string line;
    int readSize = 0;
    int writeSize = 0;

    // Member Functions
    void readUserData();
    void writeUserData();

public:
    friend class AdminMenu;

    // Member Variables
    ifstream input;
    string userNames[MAX_SIZE];
    string userPasswords[MAX_SIZE];
    int userRoles[MAX_SIZE];

    // Member class instances
    ClientMenu clientMenu;

    //Member Functions
    void displayIdleMenu();
    void displayLogin();
    void displayBranchmenu();
    void displayClientMenu();
    void displayAdminMenu();
    void changePassword();
    void addStaffMbr();
    void deleteStaffMbr();
    void viewStaffMbrs();
};


/**
 * Reads in staff data from file
 */
void SystemMenu::readUserData() {
    string user, pw;
    int role;
    input.open("Staff.txt");
    int i = 0;
    while (getline(input, line)) {
        stringstream ss(line);
        getVal(ss, user);
        getVal(ss, pw);
        getVal(ss, role);
        userNames[i] = user;
        userPasswords[i] = pw;
        userRoles[i] = role;
        i++;
    }
    readSize = i;
    input.close();
}

/*************************************************
 * Displays Client and Account Management Menu   *
 *************************************************/
void SystemMenu::displayClientMenu() {
    char opt;
    bool quit = false;

    while(!quit) {
        cout << "\n===========================================================================" << endl;
        cout << "|        Teller Terminal System - Client and Account Management           |" << endl;
        cout << "===========================================================================" << endl;
        cout << "\n1) Add a Client" << endl;
        cout << "2) Add an Account" << endl;
        cout << "3) Edit Client Information" << endl;
        cout << "4) Manage an Account" << endl;
        cout << "5) Save Client and Account Information" << endl;
        cout << "6) Exit" << endl;
        cout << "\n\tPlease choose an option: ";
        cin >> opt;
        switch (opt) {
            case '1':
                clientMenu.addClient();
                break;
            case '2':
                clientMenu.addAccount();
                break;
            case '3':
                clientMenu.editClient();
                break;
            case '4':
                clientMenu.manageAcct();
                break;
            case '5':
                cout << "\nClient and account information has been saved in the client-info file." << endl;
                cout << "\nPress enter to continue...\n";
                cin.ignore().get();
                cin.sync();
                break;
            case '6':
                quit = true;
                break;
            default:
                cout << "\n\tInvalid input. Try again." << endl;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
        }
    }

}

/**
 * Adds new employee to the staff roster
 */
void SystemMenu::addStaffMbr() {
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    char name[MAX_SIZE], pw[MAX_SIZE], role[MAX_SIZE];
    bool quit = false;
    bool quit2 = false;
    bool quit3 = false;
    int namespaces;
    int letterCount;
    int alphaCount = 0;
    int digitCount = 0;
    int upperCount = 0;
    int lowerCount = 0;
    int spaceCount = 0;
    string goodPass;
    string nameOut;
    int roleOut;

    while (!quit) {
        cout << "\nA new user will be generated:" << endl;
        // NAME INPUT //
        cout << "\nUser name: ";
        cin.getline(name, 50);
        namespaces = 0;
        letterCount = 0;
        string nam(name);
        for (int a = 0; a < nam.size(); a++) {
            if (!(isalnum(name[a])))  {
                letterCount++;
            }
            if (isspace(name[a])) {
                namespaces++;
            }
        }
        if (letterCount >= 1) {
            cout << "\n\tError - User name must contain only alphanumeric characters.";
            cout << " Try again.\n";
        }
        if (namespaces >= 1) {
            cout << "\n\tError - User name must not contain spaces.";
            cout << " Try again.\n";
        }
        if (nam.size() > 25) {
            cout << "\n\tError - Limit user name to 25 characters.";
            cout << " Try again.\n";
        }
        if (nam.size() < 8) {
            cout << "\n\tError - Limit user name must be a minimum of 8 characters.";
            cout << " Try again.\n";
        }
        if (letterCount >= 1 || namespaces >= 1 || nam.size() < 8 || nam.size() > 25) {
            continue;
        }
        else if (letterCount < 1 && namespaces < 1 && nam.size() >= 8 && nam.size() <= 25) {
            nameOut = nam;
            quit = true;
        }
    }

    // PASSWORD LOOP
    while (!quit2) {
        cout << "\nNew Password: ";
        cin.getline(newPw, 100);
        string newPass(newPw);

        // Checks number of password specific conditions for the password
        for (int j = 0; j < newPass.length(); j++) {
            if (isdigit(newPw[j])) {
                digitCount++;
            }
            if (isalpha(newPw[j])) {
                alphaCount++;
            }
            if (isupper(newPw[j])) {
                upperCount++;
            }
            if (islower(newPw[j])) {
                lowerCount++;
            }
            if (isspace(newPw[j])) {
                spaceCount++;
            }
        }
        // Evaluates the password conditions and loops back if conditions aren't met
        if (digitCount < 2) {
            cout << "\nError - Your new password must contain at least two numbers.\n";
        }

        if (alphaCount < 2) {
            cout << "\nError - Your new password must contain at least two letters.\n";
        }

        if (upperCount < 2) {
            cout << "\nError - Your new password must contain at least two uppercase characters.\n";
        }

        if (lowerCount < 2) {
            cout << "\nError - Your new password must contain at least two lower case characters.\n";
        }

        if (spaceCount >= 1) {
            cout << "\nError - Your new password must not contain spaces.\n";
        }
        // If new password is too short or too long
        if (newPass.length() < 8 || newPass.length() > 12) {
            cout << "\nError - Your new password length must be between 8 - 12 characters.\n";
        }
        else if (alphaCount >=2 && digitCount >= 2 && upperCount >= 2 && lowerCount >= 2 && spaceCount < 1)
        {
            goodPass = newPass;
            quit2 = true;
        }
    }

    while (!quit3) {
        cout << "\nRole (1 - Administrator; 2 - Branch Staff): ";
        cin.getline(role, 100);
        string rol(role);
        if (rol == "1") {
            roleOut = 1;
            quit3 = true;
        }
        if (rol == "2") {
            roleOut = 2;
            quit3 = true;
        }
        else if (rol != "1" && rol != "2") {
            cout << "\nInvalid entry. Try again.\n";
        }
    }
    if (quit && quit2 && quit3) {
        char optOut[MAX_SIZE];
        bool confirm = false;
        while (!confirm) {
            cout << "\n1) Confirm\n2) Cancel\n";
            cout << "\n\tPlease choose an option: ";
            cin.getline(optOut, 100);
            string op(optOut);
            if (op == "1") {
                userNames[readSize] = nameOut;
                userPasswords[readSize] = goodPass;
                userRoles[readSize] = roleOut;
                writeUserData();
                string type;
                if (roleOut == 1) {
                    type = "System Administrator";
                }
                else {
                    type = "Staff Member";
                }
                cout << "\nA new branch staff member was added!\n";
                cout << "User Name: " << nameOut << "    Role: " << type << endl;
                confirm = true;
            }
            if (op == "2") {
                confirm = true;
            }
            if (op != "1" && op != "2") {
                cout << "\nInvalid input. Try again.\n";
            }
        }
    }

}

/**
 * Deletes a user from the system
 */
void SystemMenu::deleteStaffMbr() {
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    readUserData();
    int userIndex;
    char name[MAX_SIZE];
    bool quit = false;
    bool found = false;
    while (!quit) {
        cout << "\nDelete a user - User Name: ";
        cin.getline(name, 100);
        string nam(name);
        for (int i = 0; i < readSize; i++) {
            if (userNames[i] == nam && nam != "" && nam != " ") {
                userIndex = i;
                found = true;
            }
        }
        if (!found) {
            cout << "\n\tError - User '" << nam << "' is not in the system. No user is deleted!\n";
            quit = true;
        }
        if (found) {
            char optOut[MAX_SIZE];
            bool confirm = false;
            while (!confirm) {
                cout << "\n1) Confirm\n2) Cancel\n";
                cout << "\n\tPlease choose an option: ";
                cin.getline(optOut, 100);
                string op(optOut);
                string deleted;
                if (op == "1") {
                    deleted = userNames[userIndex];
                    for (int k = userIndex; k < readSize - 1; k++) {
                        userNames[k] = userNames[k + 1];
                        userPasswords[k] = userPasswords[k + 1];
                        userRoles[k] = userRoles[k + 1];
                    }
                    writeUserData();
                    cout << "\nUser " << deleted << " was deleted!" << endl;
                    confirm = true;
                    quit = true;
                }
                if (op == "2") {
                    confirm = true;
                }
                if (op != "1" && op != "2") {
                    cout << "\nInvalid input. Try again.\n";
                }
            }
        }
    }
}

/**
 * Displays staff members
 */
void SystemMenu::viewStaffMbrs() {
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    readUserData();
    string role;
    cout << "\nThere are " << readSize << " users in the system.\n";
    for (int i = 0; i < readSize; i++) {
        role = (userRoles[i] == 1 ? "System Administrator" : "Branch Staff");
        cout << i + 1 << ". User Name: " << userNames[i] << "\t\t\tRole: " << role << endl;
    }
}


/*************************************************
 *      Displays System Administration Menu      *
 *************************************************/
void SystemMenu::displayAdminMenu() {
    char opt;
    bool quit = false;

    while(!quit) {
        cout << "\n===========================================================================" << endl;
        cout << "|             Teller Terminal System - System Administration              |" << endl;
        cout << "===========================================================================" << endl;
        cout << "\n1) Client and Account Management" << endl;
        cout << "2) Add a Branch Staff Member" << endl;
        cout << "3) Delete a Branch Staff Member" << endl;
        cout << "4) Display Branch Staff" << endl;
        cout << "5) Change Password" << endl;
        cout << "6) Exit" << endl;
        cout << "\n\tPlease choose an option: ";
        cin >> opt;
        switch (opt) {
            case '1':
                displayClientMenu();
                break;
            case '2':
                addStaffMbr();
                cout << "\nPress enter to continue...\n";
                cin.get();
                cin.sync();
                break;
            case '3':
                deleteStaffMbr();
                cout << "\nPress enter to continue...\n";
                cin.get();
                cin.sync();
                break;
            case '4':
                viewStaffMbrs();
                cout << "\nPress enter to continue...\n";
                cin.get();
                cin.sync();
                break;
            case '5':
                changePassword();
                cout << "\nPress enter to continue...\n";
                cin.get();
                cin.sync();
                break;
            case '6':
                quit = true;
                break;
            default:
                cout << "\n\tInvalid input. Try again." << endl;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
        }
    }
}

/**
 * Writes staff data to file
 */
void SystemMenu::writeUserData() {
    ofstream outFile("Staff.txt");
    if (outFile.is_open()) {
        for (int i = 0; i < MAX_SIZE; i++) {
            outFile << userNames[i] << "\t" << userPasswords[i]
                    << "\t" << userRoles[i] << endl;
            if (userNames[i + 1] == "") {
                break;
            }
            writeSize++;
        }
        outFile.close();
    } else {
        cout << "ERROR: There was an issue writing client data to file.\n" << endl;
    }
}

/**
 * Allows password change from either admin
 * menu or branch staff menu
 */
void SystemMenu::changePassword() {
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    int alphaCount = 0;
    int digitCount = 0;
    int upperCount = 0;
    int lowerCount = 0;
    int spaceCount = 0;
    bool quit = false;
    string goodPass;

    while (!quit) {
        cout << "\nNew Password: ";
        cin.getline(newPw, 100);
        string newPass(newPw);
        bool diffPass = true;

        // First loop checks to see if the entered password is the same as the old one
        for (int i = 0; i < readSize; i++) {
            // If the new password is the same as the old one
            if (userNames[i] == currentUser.userName && userPasswords[i] == newPass) {
                diffPass = false;
                cout << "\nError - Your new password must be different from the old one!\n";
            }
        }
        // Checks number of password specific conditions for the password
        for (int j = 0; j < newPass.length(); j++) {
            if (isdigit(newPw[j])) {
                digitCount++;
            }
            if (isalpha(newPw[j])) {
                alphaCount++;
            }
            if (isupper(newPw[j])) {
                upperCount++;
            }
            if (islower(newPw[j])) {
                lowerCount++;
            }
            if (isspace(newPw[j])) {
                spaceCount++;
            }
        }
        // Evaluates the password conditions and loops back if conditions aren't met
        if (digitCount < 2) {
            cout << "\nError - Your new password must contain at least two numbers.\n";
        }

        if (alphaCount < 2) {
            cout << "\nError - Your new password must contain at least two letters.\n";
        }

        if (upperCount < 2) {
            cout << "\nError - Your new password must contain at least two uppercase characters.\n";
        }

        if (lowerCount < 2) {
            cout << "\nError - Your new password must contain at least two lower case characters.\n";
        }

        if (spaceCount >= 1) {
            cout << "\nError - Your new password must not contain spaces.\n";
        }
        // If new password is too short or too long
        if (newPass.length() < 8 || newPass.length() > 12) {
            cout << "\nError - Your new password length must be between 8 - 12 characters.\n";
        }
        else if (diffPass && alphaCount >=2 && digitCount >= 2 && upperCount >= 2 && lowerCount >= 2 && spaceCount < 1)
        {
            goodPass = newPass;
            quit = true;
        }
    }
    for (int k = 0; k < readSize; k++) {
        if (userNames[k] == currentUser.userName) {
            userPasswords[k] = goodPass;
        }
    }
    writeUserData();
    cout << "\nPassword was changed!" << endl;
}

/*************************************************
 *      Displays Branch Staff Member Menu        *
 *************************************************/
void SystemMenu::displayBranchmenu() {
    char opt;
    bool quit = false;
    while(!quit) {
        cout << "\n===========================================================================" << endl;
        cout << "|                Teller Terminal System - Branch Staff                    |" << endl;
        cout << "===========================================================================" << endl;
        cout << "\n1) Client and Account Management" << endl;
        cout << "2) Change Password" << endl;
        cout << "3) Exit" << endl;
        cout << "\n\tPlease choose an option: ";
        cin >> opt;
        switch (opt) {
            case '1':
                displayClientMenu();
                break;
            case '2':
                changePassword();
                cout << "\nPress enter to continue...\n";
                cin.get();
                cin.sync();
                break;
            case '3':
                cout <<"\n\tExiting system. Goodbye." << endl;
                quit = true;
                break;
            default:
                cout << "\n\tInvalid input. Try again." << endl;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
        }
    }
}

/**
 * Displays Login Menu and Prompts user for name and password
 */
void SystemMenu::displayLogin() {
    bool logout = false;
    int logCount = 0;
    char userNameArr[MAX_SIZE];
    char userPwArr[MAX_SIZE];
    bool quit = false;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (!quit) {
        cout << "\n===========================================================================" << endl;
        cout << "|                  Login to Access Teller Terminal System                 |" << endl;
        cout << "===========================================================================" << endl;
        int i;
        logCount++;
        cout << "\nUsername: ";
        cin.getline(userNameArr, 100);
        cout << "Password: ";
        cin.getline(userPwArr, 100);
        string userName(userNameArr);
        string userPw(userPwArr);
        readUserData(); // Begin reading staff data
        /****************************************************************
         * Checks entered username and pw against all staff records and *
         * and splits menus for branch staff and system admin.           *
         ****************************************************************/
        for (i = 0; i < readSize; i++) {
            if (userName == userNames[i] && userPw == userPasswords[i]) {
                if (userRoles[i] == 1) {
                    currentUser.userName = userName;
                    currentUser.userPassword = userPw;
                    currentUser.userRole = 1;
                    displayAdminMenu();
                    logout = true;
                    continue;
                }
                else {
                    // Go to Regular Branch Staff Menu
                    currentUser.userName = userName;
                    currentUser.userPassword = userPw;
                    currentUser.userRole = 2;
                    displayBranchmenu();
                    logout = true;
                    continue;
                }
            }
        }
        if (logCount > 3) {
            cout << "\nYou have exceeded the number of allowable login attempts." << endl;
            cout << "Please see a system administrator to restore your password." << endl;
            exit(1);
        }
        if (userPw != userPasswords[i] && !logout) {
            cout << "\nThe username or password is incorrect. Try again!" << endl;
            continue;
        }
        if (logout) {
            break;
        }
    }
}

/**
 * Displays Idle status menu
 */
void SystemMenu::displayIdleMenu() {
    char opt;
    bool quit = false;

    while(!quit) {
        cout << "\n===========================================================================" << endl;
        cout << "|              Welcome to the Auburn Branch of Tiger Bank                 |" << endl;
        cout << "===========================================================================" << endl;
        cout << "\n1) Login" << endl;
        cout << "2) Quit" << endl;
        cout << "\n\tPlease choose an option: ";
        cin >> opt;
        switch (opt) {
            case '1':
                displayLogin();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
            case '2':
                cout <<"\n\tExiting system. Goodbye." << endl;
                exit(1);
                break;
            default:
                cout << "\n\tInvalid input. Try again." << endl;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
        }
    }
}


int main() {
    SystemMenu root;
    root.displayIdleMenu();
    return 0;
};