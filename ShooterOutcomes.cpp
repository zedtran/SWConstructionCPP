#include <iostream>
#include <cstdlib>
#include <cassert>
#include <ctime>
using namespace std;

//
// Name:            Donald Tran
// Date:            02/13/17
// AU User ID:      DZT0021
// File Name:       hw3.cpp
//
// Instructions to compile:
// g++ -std=c++11 hw3.cpp
//
// README:
// This program was created using the "CLion" IDE and
// compiled using CMake Version 3.6 and the g++ compiler on
// Tux058 via SSH Protocol
//

// Main Method Prototypes
bool at_least_two_alive(bool& A_alive, bool& B_alive, bool& C_alive);
void Aaron_shoots1(bool& B_alive, bool& C_alive);
void Bob_shoots(bool& A_alive, bool& C_alive);
void Charlie_shoots(bool& A_alive, bool& B_alive);
void Aaron_shoots2(bool& B_alive, bool& C_alive, int first);

// Test Case Prototypes
void test_at_least_two_alive(void);
void test_Aaron_shoots1(void);
void test_Bob_shoots(void);
void test_Charlie_shoots(void);
void test_Aaron_shoots2(void);

// Class constants
const int TOTAL_RUNS = 10000;
const int AARONS_RATE = 33; // Aaron has a hit rate of 1:3
const int BOBS_RATE = 5; // Bob has a hit rate of 1:2
const int CHARLIES_RATE = 100; // Charlie has a hit rate of 1:1

int main() {
    srand(time(0));

    //Class identifiers for strategy 1
    int i = 0;
    int a_wins = 0;
    int b_wins = 0;
    int c_wins = 0;
    bool aaron = true;
    bool bob = true;
    bool charlie = true;
    //Class identifiers for strategy 2
    int j = 0;
    int a_wins2 = 0;
    int b_wins2 = 0;
    int c_wins2 = 0;
    bool aaron2 = true;
    bool bob2 = true;
    bool charlie2 = true;

    cout << "\n*** Welcome to Don's Duel Simulator ***" << endl;
    test_at_least_two_alive();

    cout << "\nPress any key to continue...\n";
    cin.ignore().get(); // Pause command for Linux Terminal
    test_Aaron_shoots1();

    cout << "\nPress any key to continue...\n";
    cin.ignore().get(); // Pause command for Linux Terminal
    test_Bob_shoots();

    cout << "\nPress any key to continue...\n";
    cin.ignore().get(); // Pause command for Linux Terminal
    test_Charlie_shoots();

    cout << "\nPress any key to continue...\n";
    cin.ignore().get(); // Pause command for Linux Terminal
    test_Aaron_shoots2();

    cout << "Ready to test strategy 1 (run 10000 times):" << endl;
    cout << "Press any key to continue...\n";
    cin.ignore().get(); // Pause command for Linux Terminal

    while (i < TOTAL_RUNS) {
        aaron = true;
        bob = true;
        charlie = true;

        do {
            Aaron_shoots1(bob, charlie);
            if (charlie == false) {
                while (aaron == true && bob == true) {
                    Bob_shoots(aaron, charlie);
                    if (aaron == false) {
                        break;
                    }
                    else if (aaron == true) {
                        Aaron_shoots1(bob, charlie);
                        if (bob == false) {
                            break;
                        }
                    }
                }
            }
            else if (charlie == true) {
                Bob_shoots(aaron, charlie);
                if (charlie == false) {
                    while (aaron == true && bob == true) {
                        Aaron_shoots1(bob, charlie);
                        if (bob == false) {
                            break;
                        }
                        else if (bob == true) {
                            Bob_shoots(aaron, charlie);
                            if (aaron == false) {
                                break;
                            }
                        }
                    }
                }
                else if (charlie == true) {
                    Charlie_shoots(aaron, bob);
                    if (bob == false) {
                        Aaron_shoots1(bob, charlie);
                        if (charlie == false) {
                            continue;
                        }
                        else if (charlie == true) {
                            Charlie_shoots(aaron, bob);
                            if (aaron == false) {
                                continue;
                            }
                        }
                    }
                }
            }
        } while (at_least_two_alive(aaron, bob, charlie));
        if (aaron == true) {
            a_wins++;
        }
        else if (bob == true) {
            b_wins++;
        }
        else {
            c_wins++;
        }
        i++;
    }

    cout << "\nAaron won " << a_wins << "/10000 " << "duels or " << (double)a_wins/10000 * 100 << " percent." << endl;
    cout << "Bob won " << b_wins << "/10000 " << "duels or " << (double)b_wins/10000 * 100 << " percent." << endl;
    cout << "Charlie won " << c_wins << "/10000 " << "duels or " << (double)c_wins/10000 * 100 << " percent." << endl;

    /**
     * INITIATING STRATEGY 2
     * This second strategy will output results for what will happen
     * if Aaron skips his first opportunity to shoot.
     */
    cout << "\nReady to test strategy 2 (run 10000 times):" << endl;
    cout << "Press any key to continue...\n";
    cin.ignore().get(); // Pause command for Linux Terminal

    while (j < TOTAL_RUNS) {
        aaron2 = true;
        bob2 = true;
        charlie2 = true;

        do {
            Aaron_shoots2(bob2, charlie2, 1);
            if (charlie2 == false) {
                while (aaron2 == true && bob2 == true) {
                    Bob_shoots(aaron2, charlie2);
                    if (aaron2 == false) {
                        break;
                    }
                    else if (aaron2 == true) {
                        Aaron_shoots1(bob2, charlie2);
                        if (bob2 == false) {
                            break;
                        }
                    }
                }
            }
            else if (charlie2 == true) {
                Bob_shoots(aaron2, charlie2);
                if (charlie2 == false) {
                    while (aaron2 == true && bob2 == true) {
                        Aaron_shoots1(bob2, charlie2);
                        if (bob2 == false) {
                            break;
                        }
                        else if (bob2 == true) {
                            Bob_shoots(aaron2, charlie2);
                            if (aaron2 == false) {
                                break;
                            }
                        }
                    }
                }
                else if (charlie2 == true) {
                    Charlie_shoots(aaron2, bob2);
                    if (bob2 == false) {
                        Aaron_shoots1(bob2, charlie2);
                        if (charlie2 == false) {
                            continue;
                        }
                        else if (charlie2 == true) {
                            Charlie_shoots(aaron2, bob2);
                            if (aaron2 == false) {
                                continue;
                            }
                        }
                    }
                }
            }
        } while (at_least_two_alive(aaron2, bob2, charlie2));
        if (aaron2 == true) {
            a_wins2++;
        }
        else if (bob2 == true) {
            b_wins2++;
        }
        else {
            c_wins2++;
        }

        j++;
    }
    cout << "\nAaron won " << a_wins2 << "/10000 " << "duels or " << (double)a_wins2/10000 * 100 << " percent." << endl;
    cout << "Bob won " << b_wins2 << "/10000 " << "duels or " << (double)b_wins2/10000 * 100 << " percent." << endl;
    cout << "Charlie won " << c_wins2 << "/10000 " << "duels or " << (double)c_wins2/10000 * 100 << " percent." << endl;
    return 0;
}

/**
 * @param A_alive indicates if aaron is dead or alive
 * @param B_alive indicates if bob is dead or alive
 * @param C_alive indicates if charlie is dead or alive
 * @return true if at least two of the three are alive
 */
bool at_least_two_alive(bool& A_alive, bool& B_alive, bool& C_alive) {

    if (A_alive == true && B_alive == true && C_alive == true) {
        return true;
    }
    else if (A_alive == true && B_alive == true && C_alive == false) {
        return true;
    }
    else if (A_alive == true && B_alive == false && C_alive == true) {
        return true;
    }
    else if (A_alive == false && B_alive == true && C_alive == true) {
        return true;
    }
    else if (A_alive == true && B_alive == true && C_alive == false) {
        return true;
    }
    else if (A_alive == false && B_alive == true && C_alive == true) {
        return true;
    }
    else if (A_alive == true && B_alive == false && C_alive == true) {
        return true;
    }
    else {
        return false;
    }
}

/**
 * Aaron's first shooting strategy
 * @param B_alive indicates if bob is dead or alive
 * @param C_alive indicates if charlie is dead or alive
 * Return: Change B_alive into false if Bob is killed.
 * Change C_alive into false if Charlie is killed.
 */
void Aaron_shoots1(bool& B_alive, bool& C_alive) {
    int rand_1 = (rand() % 100);
    assert(B_alive || C_alive);
    if (C_alive == true) {
        cout << "\tAaron is shooting at Charlie." << endl;
        if (rand_1 <= AARONS_RATE) {
        cout << "\tAaron killed Charlie.\n" << endl;
        C_alive = false;
        }
        else {
            cout << "\tAaron missed Charlie.\n" << endl;
        }
    }
    else if (B_alive == true) {
        cout << "\tAaron is shooting at Bob." << endl;
        if (rand_1 <= AARONS_RATE) {
        cout << "\tAaron killed Bob.\n" << endl;
        B_alive = false;
        }
        else {
            cout << "\tAaron missed Bob.\n" << endl;
        }
    }
}

/**
 * Bob's turn to shoot
 * @param A_alive indicates if aaron is dead or alive
 * @param C_alive indicates whether Charlie is alive or dead
 * Return: Change A_alive into false if Aaron is killed.
 * Change C_alive into false if Charlie is killed.
 */
void Bob_shoots(bool& A_alive, bool& C_alive) {
    int rand_1 = (rand() % 10);
    assert(A_alive || C_alive);
    if (C_alive == true) {
        cout << "\tBob is shooting at Charlie." << endl;
        if (rand_1 <= BOBS_RATE) {
        cout << "\tBob killed Charlie.\n" << endl;
        C_alive = false;
        }
        else {
            cout << "\tBob missed Charlie.\n" << endl;
        }
    }
    else if (A_alive == true) {
        cout << "\tBob is shooting at Aaron." << endl;
        if (rand_1 <= BOBS_RATE) {
            cout << "\tBob killed Aaron.\n" << endl;
            A_alive = false;
        }
        else {
            cout << "\tBob missed Aaron.\n" << endl;
        }
    }
}

/**
 * @param A_alive indicates if aaron is dead or alive
 * @param B_alive indicates if bob is dead or alive
 * Return: Change A_alive into false if Aaron is killed.
 * Change B_alive into false if Bob is killed.
 */
void Charlie_shoots(bool& A_alive, bool& B_alive) {
    int rand_1 = (rand() % 100);
    assert(A_alive || B_alive);
    if (B_alive == true) {
        cout << "\tCharlie is shooting at Bob." << endl;
        if (rand_1 <= CHARLIES_RATE) {
            cout << "\tCharlie killed Bob.\n" << endl;
            B_alive = false;
        }
    }
    else if (A_alive == true) {
        cout << "\tCharlie is shooting at Aaron." << endl;
        if (rand_1 <= CHARLIES_RATE) {
            cout << "\tCharlie killed Aaron.\n" << endl;
            A_alive = false;
        }
    }
}

/**
* Strategy 2: Use call by reference
* @param B_alive indicates if bob is dead or alive
* @param B_alive indicates if bob is dead or alive
* @param first indicates how many skips Aaron will skip at the start of every round
* Return: Change B_alive into false if Bob is killed.
* Change C_alive into false if Charlie is killed.
*/
void Aaron_shoots2(bool& B_alive, bool& C_alive, int first) {
    int rand_1 = (rand() % 100);
    assert(B_alive || C_alive);
    if (first == 1) {
        first--;
        cout << "\tAaron intentionally misses his first shot." << endl;
        cout << "\tBoth Bob and Charlie are alive.\n" << endl;
        return;
    }
    if (C_alive == true) {
        cout << "\tAaron is shooting at Charlie." << endl;
        if (rand_1 <= 33) {
            cout << "\tAaron killed Charlie.\n" << endl;
            C_alive = false;
        }
        else {
            cout << "\tAaron missed Charlie.\n" << endl;
        }
    }
    else if (B_alive == true) {
        cout << "\tAaron is shooting at Bob." << endl;
        if (rand_1 <= 33) {
            cout << "\tAaron killed Bob.\n" << endl;
            B_alive = false;
        }
        else {
            cout << "\tAaron missed Bob.\n" << endl;
        }
    }
}

/**
 * Test case 1: Determines if at least two shooters are alive
 * Tests 2^3 possible outcomes
 */
void test_at_least_two_alive(void) {
    bool a = true;
    bool b = true;
    bool c = true;

    cout << "Unit Testing 1: Function – at_least_two_alive()\n";
    cout << "\tCase 1: Aaron alive, Bob alive, Charlie alive\n";
    assert(true == at_least_two_alive(a, b, c));
    cout << "\tCase passed ...\n\n";

    a = false;
    b = true;
    c = true;
    cout << "\tCase 2: Aaron dead, Bob alive, Charlie alive\n";
    assert(true == at_least_two_alive(a, b, c));
    cout << "\tCase passed ...\n\n";

    a = true;
    b = false;
    c = true;
    cout << "\tCase 3: Aaron alive, Bob dead, Charlie alive\n";
    assert(true == at_least_two_alive(a, b, c));
    cout << "\tCase passed ...\n\n";

    a = true;
    b = true;
    c = false;
    cout << "\tCase 4: Aaron alive, Bob alive, Charlie dead\n";
    assert(true == at_least_two_alive(a, b, c));
    cout << "\tCase passed ...\n\n";

    a = true;
    b = false;
    c = false;
    cout << "\tCase 5: Aaron alive, Bob dead, Charlie dead\n";
    assert(false == at_least_two_alive(a, b, c));
    cout << "\tCase passed ...\n\n";

    a = false;
    b = true;
    c = false;
    cout << "\tCase 6: Aaron dead, Bob alive, Charlie dead\n";
    assert(false == at_least_two_alive(a, b, c));
    cout << "\tCase passed ...\n\n";

    a = false;
    b = false;
    c = true;
    cout << "\tCase 7: Aaron dead, Bob dead, Charlie alive\n";
    assert(false == at_least_two_alive(a, b, c));
    cout << "\tCase passed ...\n\n";

    a = false;
    b = false;
    c = false;
    cout << "\tCase 8: Aaron dead, Bob dead, Charlie dead\n";
    assert(false == at_least_two_alive(a, b, c));
    cout << "\tCase passed ...\n";
}

/**
 * Test case 2: Tests Aaron's first shooting strategy
 */
void test_Aaron_shoots1(void) {
    bool b;
    bool c;

    b = true;
    c = true;
    cout << "Unit Testing 2: Function – Aaron_shoots1(B_alive, C_alive)\n";
    cout << "\tCase 1: Bob alive, Charlie alive\n";
    Aaron_shoots1(b, c);

    b = true;
    c = false;
    cout << "\tCase 2: Bob alive, Charlie dead\n";
    Aaron_shoots1(b, c);

    b = false;
    c = true;
    cout << "\tCase 3: Bob dead, Charlie alive\n";
    Aaron_shoots1(b, c);
}

/**
 * Test case 3: Tests Bob's shooting choices
 */
void test_Bob_shoots(void) {
    bool a;
    bool c;

    a = true;
    c = true;
    cout << "Unit Testing 3: Function – Bob_shoots(A_alive, C_alive)\n";
    cout << "\tCase 1: Aaron alive, Charlie alive\n";
    Bob_shoots(a, c);

    a = true;
    c = false;
    cout << "\tCase 2: Aaron alive, Charlie dead\n";
    Bob_shoots(a, c);

    a = false;
    c = true;
    cout << "\tCase 3: Aaron dead, Charlie alive\n";
    Bob_shoots(a, c);
}

/**
 * Test case 4: Tests Charlie's shooting choices
 */
void test_Charlie_shoots(void) {
    bool a;
    bool b;

    a = true;
    b = true;
    cout << "Unit Testing 4: Function – Charlie_shoots(A_alive, B_alive)\n";
    cout << "\tCase 1: Aaron alive, Bob alive\n";
    Charlie_shoots(a, b);

    a = true;
    b = false;
    cout << "\tCase 2: Aaron alive, Bob dead\n";
    Charlie_shoots(a, b);

    a = false;
    b = true;
    cout << "\tCase 3: Aaron dead, Bob alive\n";
    Charlie_shoots(a, b);
}

/**
 * Test case 5: Tests Aaron's second shooting strategy
 */
void test_Aaron_shoots2(void) {
    bool b;
    bool c;

    b = true;
    c = true;
    cout << "Unit Testing 5: Function – Aaron_shoots2(B_alive, C_alive, 1)\n";
    cout << "\tCase 1: Bob alive, Charlie alive\n";
    Aaron_shoots2(b, c, 1);

    b = true;
    c = false;
    cout << "\tCase 2: Bob alive, Charlie dead\n";
    Aaron_shoots2(b, c, 0);

    b = false;
    c = true;
    cout << "\tCase 3: Bob dead, Charlie alive\n";
    Aaron_shoots2(b, c, 0);
}

