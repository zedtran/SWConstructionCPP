// Name:            Donald Tran
// Date:            03/20/17
// AU User ID:      DZT0021
// File Name:       Project1.cpp
//
// Instructions to compile:
// g++ -o main -std=c++11 -Wall Project1.cpp
//
// Read Me:
// This program was created using "CLion" IDE and
// compiled using CMake version 3.6 and the g++ compiler on
// Tux051 via SSH protocol
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#undef max
using namespace std;

// Global Class Declarations
class character;
class main_menu;
class game_menu;
class encounter;
class high_scores;

// Global constant
const int MAX_SIZE = 10;

/** Character class containing all data about individual players */
class character{

private:
    int intelligence = 15;
    int time = 25;
    int money = 10;
    int position = 0;

public:
    char name[21];
    int getIntel();
    int getTime();
    int getMoney();
    int getPosition();
    int getScore();
    void setTime(int newTime);
    void setPosition(int newPosition);
    void setIntel(int newIntel);
    void setMoney(int newMoney);
    string getName();

};

void character::setTime(int newTime) {
    time = newTime;
}

void character::setPosition(int newPosition) {
    position = newPosition;
}

void character::setIntel(int newIntel) {
    intelligence = newIntel;
}

void character::setMoney(int newMoney) {
    money = newMoney;
}

int character::getIntel() {
    return intelligence;
}

int character::getMoney() {
    return money;
}

int character::getTime() {
    return time;
}

int character::getPosition() {
    return position;
}

int character::getScore() {
    return intelligence * time * money;
}

string character::getName() {
    return name;
}

// Global class instance
character p;

/** Class for high scores which manages all aspects of maintaining
 * scores and updating new scores to the "scores.txt" file */
class high_scores{

private:
    ifstream fileIn;
    string lines;

public:
    int scoresArr[MAX_SIZE];
    string namesArr[MAX_SIZE];
    void addScore();
    void readCurrentScores();
    void sortScores();
    void writeScores();
    void printScores();
    int getNumberOfScores();

};

int high_scores::getNumberOfScores() {
        int numberOfScores = 0;
        fileIn.open("scores.txt");
        if (fileIn.fail()) {
            fileIn.close();
        }
        while (getline(fileIn, lines)) {
            if (numberOfScores >= 10) {
                break;
            }
            if (lines == "") {
                break;
            }
            else {
                ++numberOfScores;
            }
        }
        fileIn.close();
        return numberOfScores;
}

void high_scores::readCurrentScores() {
    fileIn.open("scores.txt");
    if (fileIn.fail()) {
        cout << "\nError during file opening\n\n";
        fileIn.close();
    }
    else {
        for (int i = 0; i < MAX_SIZE; i++) {
            fileIn >> namesArr[i];
            fileIn >> scoresArr[i];
        }
    }
    fileIn.close();
}

void high_scores::addScore() {
    int i, j;
    int pos = 0;
    for (i = 0; i < MAX_SIZE - 1; ++i) {
        if (scoresArr[i] <= p.getScore() && p.getScore() < scoresArr[i + 1]) {
            pos = i + 1;
            break;
        }
    }
    for (j = MAX_SIZE - 1; j > pos; --j) {
        scoresArr[j] = scoresArr[j - 1];
        namesArr[j] = namesArr[j - 1];
    }
    scoresArr[pos]= p.getScore();
    namesArr[pos] = p.getName();
}

void high_scores::sortScores() {
    int i, j, temp1;
    string temp2;
    for (i = 0; i < MAX_SIZE - 1; ++i)
    {
        for (j = i + 1; j < MAX_SIZE - 1; ++j)
        {
            if (scoresArr[i] < scoresArr[j])
            {
                temp1 = scoresArr[i];
                scoresArr[i] = scoresArr[j];
                scoresArr[j] = temp1;

                temp2 = namesArr[i];
                namesArr[i] = namesArr[j];
                namesArr[j] = temp2;
            }
        }
    }
}

void high_scores::writeScores() {
    ofstream outFile("scores.txt");
    if (outFile.is_open()) {
        for (int i = 0; i < MAX_SIZE; i++) {
            outFile << namesArr[i] << " " << scoresArr[i] << endl;
            if (scoresArr[i + 1] == 0) {
                break;
            }
        }
        outFile.close();
    } else {
        cout << "GAME ERROR: There was a problem writing to the score board.\n" << endl;
    }
}

void high_scores::printScores() {
    string name; //name output to file
    int score; //score output to file
    int count1 = 0;
    int count2 = 0;
    int scoreCount = getNumberOfScores();

    if (scoreCount == 0) {
        cout << "\nNo new high score added.\n\n";
    }
    else if (scoreCount == 1) {
        fileIn.open("scores.txt");
        if (fileIn.fail()) {
            cout << "\nThere was an error reading high scores.\n\n";
            exit(1);
        }
        cout << "\nThe New top High Score is:\n\n";
        while ((fileIn >> name >> score) && count1 < 10) {
            cout << "\t";
            cout << left << setw(25) << setfill(' ') << name;
            cout << left << setw(20) << setfill(' ') << score << endl;
            ++count1;
        }
        cout << "\n\t--NO  MORE  SCORES  TO  SHOW--\n\n\n";
        fileIn.close();
    }
    else {
        fileIn.open("scores.txt");
        if (fileIn.fail()) {
            cout << "\nThere was an error reading high scores.\n\n";
            exit(1);
        }
        cout << "\nThe New top " << scoreCount << " High Scores are:\n\n";
        while ((fileIn >> name >> score) && count2 < 10) {
            cout << "\t";
            cout << left << setw(25) << setfill(' ') << name;
            cout << left << setw(20) << setfill(' ') << score << endl;
            ++count2;
        }
        cout << "\n\t--NO  MORE  SCORES  TO  SHOW--\n\n\n";
        fileIn.close();
    }
}

// Global class instance
high_scores hs;

/** Main menu class handles all initial menu options */
class main_menu{

private:
    int choice;
    ifstream inFile;
    string lines;

public:
    void getCharName();
    void removeNameSpaces(char* s);
    void selectMainOption();
    void viewTopScores();
    int getNumberOfScores();
    void startGame();
};

void main_menu::startGame() {
    p.setIntel(p.getIntel() + (rand() % 6));
    p.setTime(p.getTime() + (rand() % 6));
    p.setMoney(p.getMoney() + (rand() % 6));
    cout << "\nEntering the game...\n" << endl;
    cout << "You have: \n\n";
    cout << "Intelligence: " << p.getIntel() << endl;
    cout << "Time: " << p.getTime() << endl;
    cout << "Money: " << "$" << p.getMoney() << ".00\n\n";
    cout << "You are " << (20 - p.getPosition()) << " steps from the goal. ";
    cout << "Time left: " << p.getTime() << ".\n\n";
}

int main_menu::getNumberOfScores() {
    int numberOfScores = 0;
    inFile.open("scores.txt");
    if (inFile.fail()) {
        inFile.close();
    }
    while (getline(inFile, lines)) {
        if (numberOfScores >= 10) {
            break;
        }
        if (lines == "") {
            break;
        }
        else {
            ++numberOfScores;
        }
    }
    inFile.close();
    return numberOfScores;
}

void main_menu::viewTopScores() {
    string name; //name output to file
    int score; //score output to file
    int count1 = 0;
    int count2 = 0;
    int scoreCount = getNumberOfScores();

    if (scoreCount == 0) {
        cout << "\nThere are currently no high scores. Try your luck and be the first.";
    }
    else if (scoreCount == 1) {
        inFile.open("scores.txt");
        if (inFile.fail()) {
            inFile.close();
            cout << "\nThere was an error reading high scores.\n\n";
            exit(1);
        }
        cout << "\nThe top High Score is:\n\n";
        while ((inFile >> name >> score) && count1 < 10) {
            cout << "\t";
            cout << left << setw(25) << setfill(' ') << name;
            cout << left << setw(20) << setfill(' ') << score << endl;
            ++count1;
        }
        cout << "\n\t--NO  MORE  SCORES  TO  SHOW--\n";
        inFile.close();
    }
    else {
        inFile.open("scores.txt");
        if (inFile.fail()) {
            inFile.close();
            cout << "\nThere was an error reading high scores.\n\n";
            exit(1);
        }
        cout << "\nThe top " << scoreCount << " High Scores are:\n\n";
        while ((inFile >> name >> score) && count2 < 10) {
            cout << "\t";
            cout << left << setw(25) << setfill(' ') << name;
            cout << left << setw(20) << setfill(' ') << score << endl;
            ++count2;
        }
        cout << "\n\t--NO  MORE  SCORES  TO  SHOW--\n";
        inFile.close();
    }
}

void main_menu::removeNameSpaces(char* s) {
    char* cpy = s;  // an alias to iterate through s without moving s
    char* temp = s;

    while (*cpy)
    {
        if (*cpy != ' ')
            *temp++ = *cpy;
            cpy++;
    }
    *temp = 0;
}

void main_menu::getCharName() {
    cout << "What's your name? \n"
            "(limit 20 characters, no spaces): ";
    cin.getline(p.name, 21);
    removeNameSpaces(p.name);
    cout << "\n===========================================================================" << endl;
    cout << "                          Welcome, " << p.getName() << "!" << endl;
    cout << "===========================================================================";
}

void main_menu::selectMainOption() {
    bool valid = false;
    int loopCount = 0;
    while (!valid) {
        cout << "\n\n1) Start a New Game of Shelby Center and Dragons!" << endl;
        cout << "2) View top 10 High Scores" << endl;
        cout << "3) Quit" << endl;
        cout << "\n\tPlease choose an option: ";
        cin >> choice;

        /** Catches condition where when the input name was longer than 20 characters
         choice defaults to zero, causing switch statement to jump to default.
         Counts the number of loops this condition is met
         and then loops back to the beginning of the while loop if
         the condition has been met more than once. Continues otherwise. */
        if (choice == 0) {
            while (choice == 0) {
                if (loopCount == 1)
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\n" << "\nInvalid response. Try again: ";
                    cin >> choice;
                    if (choice != 0)
                    {
                        break;
                    }
                }
                else
                {
                    loopCount++;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin >> choice;
                    if (choice != 0)
                    {
                        break;
                    }
                }
            }
        }

        switch (choice) {
            case 1:
                startGame();
                valid = true;
                break;

            case 2:
                getNumberOfScores();
                viewTopScores();
                break;

            case 3:
                cout << "\nYou quit before you even started. How sad and tragic your life must be.\n\n";
                exit(1);

            default:
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout << "\n" << "\nInvalid response. Try again.";
                continue;
        }
        continue;
    }
}

/** Encounter class handles all possible encounters
 * including puzzles */
class encounter{

public:
    void faceRandPuzzles();
    void faceProfessor();
    void faceGradStud();
    void faceGruntWork();
    void faceGrading();
    void faceNothing();
};

void encounter::faceRandPuzzles() {
    int rand_answer4 = (rand() % 10 + 1);
    int rand_puzzle = (rand() % 5 + 1);
    switch (rand_puzzle) {
        case 1:
            int answer1;
            cout << "\nPUZZLE: It’s a riddling imp. I hate riddling imps. But fine, he asks:\n"
                    "“A murderer has been condemned to death. He has to choose between three rooms.\n"
                    "The first is full of raging fires, the second with assassins who have loaded guns,\n"
                    "and the third room is full of lions who haven't eaten in three years.\n"
                    "Which room is safest for him?“\n\n";
            cout << "\t1) Room 1\n\t2) Room 2\n\t3) Room 3\n\t4) Uhh...None?\n\n";
            cout << "Choose Wisely (You have 15 seconds to answer this question or lose): ";
            cin >> answer1;
            if (answer1 == 1) {
                cout << "\n\nThe murderer suffers fatal burns. Your answer has cost you the game.\n";
                // Updating scoreboard. Player lost.
                hs.readCurrentScores();
                hs.addScore();
                hs.sortScores();
                hs.writeScores();
                p.setTime(0);
            }
            else if (answer1 == 2) {
                cout << "\n\nThe murderer is shot by assassins. Your answer has cost you the game.\n"
                     << "You lose all remaining time.\n";
                // Updating scoreboard. Player lost.
                hs.readCurrentScores();
                hs.addScore();
                hs.sortScores();
                hs.writeScores();
                p.setTime(0);
            }
            else if (answer1 == 3) {
                p.setPosition(p.getPosition() + 1);
                cout << "\n\nThe murderer is certainly safe in this room. You have been\n"
                     << "rewarded with five units of time.\n";
                p.setTime(p.getTime() + 5);
                if (p.getPosition() >= 20) {
                    cout << "\nYOU SUCCESSFULLY MADE IT TO THE END OF THE HALL. CONGRATULATIONS!\n\n";
                    hs.readCurrentScores();
                    hs.addScore();
                    hs.sortScores();
                    hs.writeScores();
                    hs.printScores();
                    exit(1);
                }
            }
            else if (answer1 == 4) {
                cout << "\n\nThe murderer is shot from behind for non-compliance.\n"
                     << "Your answer has cost you the game. You forfeit your remaining time.\n";
                // Updating scoreboard. Player lost.
                hs.readCurrentScores();
                hs.addScore();
                hs.sortScores();
                hs.writeScores();
                p.setTime(0);
            }
            else {
                p.setPosition(p.getPosition() + 1);
                cout << "\n\nYou can't even choose from the available options.\n"
                     << "You are hopeless, and therefore lose the game by way of forfeiting all remaining time.\n";
                // Updating scoreboard. Player lost.
                hs.readCurrentScores();
                hs.addScore();
                hs.sortScores();
                hs.writeScores();
                p.setTime(0);
            }
            break;

        case 2:
            int answer2;
            if ((p.getTime() - 1) <= 0) {
                cout << "\nYou have run out of time with nowhere to go!\n\n";
                // Updating scoreboard. Player lost.
                hs.readCurrentScores();
                hs.addScore();
                hs.sortScores();
                hs.writeScores();
                p.setTime(p.getTime() - 1);
                break;
            }
            p.setTime(p.getTime() - 1);
            cout << "\nPUZZLE: It’s a riddling imp. I hate riddling imps. But fine, he asks:\n"
                    "“You walk into a room with a rabbit holding a carrot, a pig eating\n"
                    "slop, and a chimp holding a banana. Which animal in the room is the\n"
                    "smartest?“\n\n";
            cout << "\t1) The Rabbit\n\t2) The Pig\n\t3) The Chimp\n\t4) Uhh...none of those?\n\n";
            cout << "Choose Wisely (You have 3 seconds to answer this question or lose): ";
            cin >> answer2;
            if (answer2 == 1) {
                cout << "\n\nThe rabbit is a cunning creature, but not as sharp as another--\n"
                     << "or so I thought. Lose 15 units of intelligence.\n";
                if ((p.getIntel() - 15) <= 0) {
                    cout << "\nYou have no more intelligence. Seems accurate.\n\n";
                    // Updating scoreboard. Player lost.
                    hs.readCurrentScores();
                    hs.addScore();
                    hs.sortScores();
                    hs.writeScores();
                    p.setIntel(p.getIntel() - 15);
                }
            }
            else if (answer2 == 2) {
                p.setPosition(p.getPosition() + 1);
                cout << "\n\nThe pig? ... Really? Where did you get that idea. Lose 15\n"
                     << "units of intelligence\n";
                if ((p.getIntel() - 15) <= 0) {
                    cout << "\nYou have no more intelligence. Seems accurate.\n\n";
                    // Updating scoreboard. Player lost.
                    hs.readCurrentScores();
                    hs.addScore();
                    hs.sortScores();
                    hs.writeScores();
                    p.setIntel(p.getIntel() - 15);
                }
            }
            else if (answer2 == 3) {
                p.setPosition(p.getPosition() + 1);
                cout << "\n\nWell, the chimp IS a close relative to animal that SHOULD be the smartest.\n"
                     << "In any case, you are wrong. You lose 15 units of intelligence\n";
                if ((p.getIntel() - 15) <= 0) {
                    cout << "\nYou have no more intelligence. Seems accurate.\n\n";
                    // Updating scoreboard. Player lost.
                    hs.readCurrentScores();
                    hs.addScore();
                    hs.sortScores();
                    hs.writeScores();
                    p.setIntel(p.getIntel() - 15);
                }
            }
            else if (answer2 == 4) {
                p.setPosition(p.getPosition() + 1);
                cout << "\n\nYou must indeed be the smartest animal in the room. You gain\n"
                     << "8 units of intelligence.\n";
                p.setIntel(p.getIntel() + 8);
                if (p.getPosition() >= 20) {
                    cout << "\nYOU SUCCESSFULLY MADE IT TO THE END OF THE HALL. CONGRATULATIONS!\n\n";
                    hs.readCurrentScores();
                    hs.addScore();
                    hs.sortScores();
                    hs.writeScores();
                    hs.printScores();
                    exit(1);
                }
            }
            else {
                cout << "\n\nYou can't even choose from the available options.\n"
                     << "You are hopeless, and therefore forfeit all intelligence.\n";
                // Updating scoreboard. Player lost.
                hs.readCurrentScores();
                hs.addScore();
                hs.sortScores();
                hs.writeScores();
                p.setIntel(0);
            }
            break;

        case 3:
            int answer3;
            if ((p.getTime() - 1) <= 0) {
                cout << "\nYou have run out of time with nowhere to go!\n\n";
                // Updating scoreboard. Player lost.
                hs.readCurrentScores();
                hs.addScore();
                hs.sortScores();
                hs.writeScores();
                p.setTime(p.getTime() - 1);
                break;
            }
            p.setTime(p.getTime() - 1);
            cout << "\nPUZZLE: Mr. Smith has 4 daughters. Each of his daughters has a brother.\n"
                    "How many children does Mr. Smith have?\n\n";
            cout << "Choose Wisely (Don't think too hard): ";
            cin >> answer3;
            if (answer3 == 5) {
                p.setPosition(p.getPosition() + 1);
                cout << "\n\nI guess you can count after all. I will reward you with $5.00...\n"
                        "for each of Mr. Smith's children.\n";
                p.setMoney(p.getMoney() + 25);
                if (p.getPosition() >= 20) {
                    cout << "\nYOU SUCCESSFULLY MADE IT TO THE END OF THE HALL. CONGRATULATIONS!\n\n";
                    hs.readCurrentScores();
                    hs.addScore();
                    hs.sortScores();
                    hs.writeScores();
                    hs.printScores();
                    exit(1);
                }
            }
            else if (answer3 != 5) {
                cout << "\n\nThis was a rather trivial riddle. You could have even googled the answer.\n"
                     << "Your mistake will cost you $5.00 for each of Mr. Smith's daughters...\n";
                if ((p.getMoney() - 20) <= 0) {
                    // Updating scoreboard. Player lost.
                    hs.readCurrentScores();
                    hs.addScore();
                    hs.sortScores();
                    hs.writeScores();
                    hs.printScores();
                    exit(1);
                }
            }
            break;

        case 4:
            int answer4;
            if ((p.getTime() - 1) <= 0) {
                cout << "\nYou have run out of time with nowhere to go!\n\n";
                // Updating scoreboard. Player lost.
                hs.readCurrentScores();
                hs.addScore();
                hs.sortScores();
                hs.writeScores();
                p.setTime(p.getTime() - 1);
                break;
            }
            p.setTime(p.getTime() - 1);
            cout << "\nGUESS THE NUMBER: I am thinking of a number between 1 - 10.\n"
                    "Guess the number correctly to advance your position in the hall by two steps.\n"
                    "Guess incorrectly and go back one step! MUAHAHAHahahahahahaaa...\n\n";

            cout << "Test your psychic abilities and enter a number (1 - 10): ";
            cin >> answer4;
            if (answer4 == rand_answer4) {
                cout << "\n\nIMPOSSIBLE! You must be able to speak to the beyond. Watch your back.\n"
                     << "You are free to move two steps forward.\n";
                p.setPosition(p.getPosition() + 2);
                if (p.getPosition() >= 20) {
                    cout << "\nYOU SUCCESSFULLY MADE IT TO THE END OF THE HALL. CONGRATULATIONS!\n\n";
                    hs.readCurrentScores();
                    hs.addScore();
                    hs.sortScores();
                    hs.writeScores();
                    hs.printScores();
                    exit(1);
                }
            }
            if (answer4 != rand_answer4) {
                cout << "\n\nYou have affirmed you are nothing more than a mere mortal.\n"
                     << "In the words of Gandalf, that means \"YOU SHALL NOT PASS!\"!\n"
                     << "Move one step back, loser.\n";
                p.setPosition(p.getPosition() - 1);
                if (p.getPosition() < 0) {
                    p.setPosition(0);
                }
            }
            break;

        default:
            int answer5;
            cout << "\nTEST YOUR LOGIC: A man is standing in front of a painting of a man, "
                    "and he tells us the following: \n"
                    "\"Brothers and sisters have I none, but this man's father is my father's son\". \n"
                    "Who is on the painting?\n\n";
            cout << "\t1) His father\n\t2) He himself\n\t3) His son\n\t4) His great uncle (once removed)\n\n";
            cout << "Choose Wisely (TIME is of the essence): ";
            cin >> answer5;
            if (answer5 == 1) {
                p.setPosition(p.getPosition() + 1);
                cout << "\n\nIncorrect. You lose 7 units of time!\n";
                if ((p.getTime() - 7) <= 0) {
                    // Updating scoreboard. Player lost.
                    hs.readCurrentScores();
                    hs.addScore();
                    hs.sortScores();
                    hs.writeScores();
                }
                p.setTime(p.getTime() - 7);
            }
            else if (answer5 == 2) {
                p.setPosition(p.getPosition() + 1);
                cout << "\n\nIncorrect. You lose 7 units of time!\n";
                if ((p.getTime() - 7) <= 0) {
                    // Updating scoreboard. Player lost.
                    hs.readCurrentScores();
                    hs.addScore();
                    hs.sortScores();
                    hs.writeScores();
                }
                p.setTime(p.getTime() - 7);
            }
            else if (answer5 == 3) {
                p.setPosition(p.getPosition() + 1);
                cout << "\n\nWow. I'm impressed. Fine! I'll be nice and give you six units of time...\n";
                p.setTime(p.getTime() + 6);
                if (p.getPosition() >= 20) {
                    cout << "\nYOU SUCCESSFULLY MADE IT TO THE END OF THE HALL. CONGRATULATIONS!\n\n";
                    hs.readCurrentScores();
                    hs.addScore();
                    hs.sortScores();
                    hs.writeScores();
                    hs.printScores();
                    exit(1);
                }

            }
            else if (answer5 == 4) {
                p.setPosition(p.getPosition() + 1);
                cout << "\n\nIncorrect. You lose 7 units of time! I thought this would be CLEARLY wrong.\n";
                if ((p.getTime() - 7) <= 0) {
                    // Updating scoreboard. Player lost.
                    hs.readCurrentScores();
                    hs.addScore();
                    hs.sortScores();
                    hs.writeScores();
                }
                p.setTime(p.getTime() - 7);
            }
            else {
                p.setPosition(p.getPosition() + 1);
                cout << "\n\nSuperb fail... You can't even follow directions. \n"
                        "For that, you lose all remaining time.\n";
                // Updating scoreboard. Player lost.
                hs.readCurrentScores();
                hs.addScore();
                hs.sortScores();
                hs.writeScores();
                p.setTime(0);
            }
            break;
    }
    if (p.getTime() <= 0) {
        cout << "\n\nTIME HAS FALLEN TO ZERO. YOU DIE.\n";
        // Print new scores
        hs.printScores();
        exit(1);
    }
    else if (p.getIntel() <= 0) {
        cout << "\n\nINTELLIGENCE HAS FALLEN TO ZERO. YOU DIE.\n";
        // Print new scores
        hs.printScores();
        exit(1);
    }
    else if (p.getMoney() <= 0) {
        cout << "\n\nMONEY HAS FALLEN TO ZERO. YOU DIE.\n";
        // Print new scores
        hs.printScores();
        exit(1);
    }
}

void encounter::faceGradStud() {
    int rand_time = (rand() % 4 + 1);
    cout << "\nYOU RUN INTO A FELLOW GRAD STUDENT!\n\n";
    cout << "You lose " << rand_time << " unit(s) of time.\n\n";
    if ((p.getTime() - rand_time) <= 0) {
        cout << "\nYou have run out of time with nowhere to go!\n\n";
        cout << "TIME HAS FALLEN TO ZERO. YOU DIE.\n";
        // Updating scoreboard. Player lost.
        hs.readCurrentScores();
        hs.addScore();
        hs.sortScores();
        hs.writeScores();
        hs.printScores();
        exit(1);
    }
    p.setTime(p.getTime() - rand_time);
    p.setPosition(p.getPosition() + 1);
    if (p.getPosition() >= 20) {
        cout << "\nYOU SUCCESSFULLY MADE IT TO THE END OF THE HALL. CONGRATULATIONS!\n\n";
        hs.readCurrentScores();
        hs.addScore();
        hs.sortScores();
        hs.writeScores();
        hs.printScores();
        exit(1);
    }
    cout << "You are " << (20 - p.getPosition()) << " steps from the goal. ";
    cout << "Time left: " << p.getTime() << endl;

}

void encounter::faceProfessor() {
    int rand_time = (rand() % 4 + 1);
    cout << "\nYOU RUN INTO ONE OF YOUR PROFESSORS!\n\n";
    cout << "You spent " << rand_time << " unit(s) of time, but gained 4 units of intelligence.\n\n";
    if ((p.getTime() - rand_time) <= 0) {
        cout << "\nYou have run out of time with nowhere to go!\n\n";
        cout << "TIME HAS FALLEN TO ZERO. YOU DIE.\n";
        // Updating scoreboard. Player lost.
        hs.readCurrentScores();
        hs.addScore();
        hs.sortScores();
        hs.writeScores();
        hs.printScores();
        exit(1);
    }
    p.setTime(p.getTime() - rand_time);
    p.setPosition(p.getPosition() + 1);
    if (p.getPosition() >= 20) {
        cout << "\nYOU SUCCESSFULLY MADE IT TO THE END OF THE HALL. CONGRATULATIONS!\n\n";
        hs.readCurrentScores();
        hs.addScore();
        hs.sortScores();
        hs.writeScores();
        hs.printScores();
        exit(1);
    }
    p.setIntel(p.getIntel() + 4);
    cout << "You are " << (20 - p.getPosition()) << " steps from the goal. ";
    cout << "Time left: " << p.getTime() << endl;

}

void encounter::faceGrading() {
        cout << "\nYOU FIND SOME PAPERS TO GRADE.\n\n";
        cout << "You spent two units of time, but gained $5.00!\n\n";
        if ((p.getTime() - 2) <= 0) {
            cout << "\nYou have run out of time with nowhere to go!\n\n";
            cout << "TIME HAS FALLEN TO ZERO. YOU DIE.\n";
            // Updating scoreboard. Player lost.
            hs.readCurrentScores();
            hs.addScore();
            hs.sortScores();
            hs.writeScores();
            hs.printScores();
            exit(1);
        }
        p.setTime(p.getTime() - 2);
        p.setPosition(p.getPosition() + 1);
        if (p.getPosition() >= 20) {
            cout << "\nYOU SUCCESSFULLY MADE IT TO THE END OF THE HALL. CONGRATULATIONS!\n\n";
            hs.readCurrentScores();
            hs.addScore();
            hs.sortScores();
            hs.writeScores();
            hs.printScores();
            exit(1);
        }
        p.setMoney(p.getMoney() + 5);
        cout << "You are " << (20 - p.getPosition()) << " steps from the goal. ";
        cout << "Time left: " << p.getTime() << endl;
}

void encounter::faceGruntWork() {
        cout << "\nAttacked by grunt work!\n\n";
        cout << "You lose two units of time AND 3 units of intelligence.\n\n";
        if ((p.getTime() - 2) <= 0) {
            cout << "\nYou have run out of time with nowhere to go!\n\n";
            cout << "TIME HAS FALLEN TO ZERO. YOU DIE.\n";
            // Updating scoreboard. Player lost.
            hs.readCurrentScores();
            hs.addScore();
            hs.sortScores();
            hs.writeScores();
            hs.printScores();
            exit(1);
        }
        if ((p.getIntel() - 3) <= 0) {
            cout << "\nYou have run out of intelligence points!\n\n";
            cout << "INTELLIGENCE HAS FALLEN TO ZERO. YOU DIE.\n";
            // Updating scoreboard. Player lost.
            hs.readCurrentScores();
            hs.addScore();
            hs.sortScores();
            hs.writeScores();
            hs.printScores();
            exit(1);
        }
        p.setTime(p.getTime() - 2);
        p.setPosition(p.getPosition() + 1);
        if (p.getPosition() >= 20) {
            cout << "\nYOU SUCCESSFULLY MADE IT TO THE END OF THE HALL. CONGRATULATIONS!\n\n";
            hs.readCurrentScores();
            hs.addScore();
            hs.sortScores();
            hs.writeScores();
            hs.printScores();
            exit(1);
        }
        p.setIntel(p.getIntel() - 3);
        cout << "You are " << (20 - p.getPosition()) << " steps from the goal. ";
        cout << "Time left: " << p.getTime() << endl;
}

void encounter::faceNothing() {
        cout << "\nNOTHING HAPPENS!\n\n";
        cout << "You spent one unit of time.\n\n";
        if ((p.getTime() - 1) <= 0) {
            cout << "\nYou have run out of time with nowhere to go!\n\n";
            cout << "TIME HAS FALLEN TO ZERO. YOU DIE.\n";
            // Updating scoreboard. Player lost.
            hs.readCurrentScores();
            hs.addScore();
            hs.sortScores();
            hs.writeScores();
            hs.printScores();
            exit(1);
        }
        p.setTime(p.getTime() - 1);
        p.setPosition(p.getPosition() + 1);
        if (p.getPosition() >= 20) {
            cout << "\nYOU SUCCESSFULLY MADE IT TO THE END OF THE HALL. CONGRATULATIONS!\n\n";
            hs.readCurrentScores();
            hs.addScore();
            hs.sortScores();
            hs.writeScores();
            hs.printScores();
            exit(1);
        }
        cout << "You are " << (20 - p.getPosition()) << " steps from the goal. ";
        cout << "Time left: " << p.getTime() << endl;

}

// Global class instance
encounter e;

/** Game menu handles all possible actions player could take
 * from after starting the game */
class game_menu{

public:
    int option;
    void viewPlayer();
    void boostIntel();
    void boostMoney();
    void endGame();
    void selectGameOption();
    void dealEncounters();
};

void game_menu::dealEncounters() {
    int rand_case1 = (rand() % 100);
    cout << "\nYou move forward one step, and..." << endl;

    if (rand_case1 < 10) {
        e.faceGrading();
    }
    else if (rand_case1 >= 10 && rand_case1 < 25) {
        e.faceGruntWork();
    }
    else if (rand_case1 >= 25 && rand_case1 < 35) {
        e.faceProfessor();
    }
    else if (rand_case1 >= 35 && rand_case1 < 50) {
        e.faceGradStud();
    }
    else if (rand_case1 >= 50 && rand_case1 < 75) {
        e.faceRandPuzzles();
    }
    else {
        e.faceNothing();
    }
}

void game_menu::endGame() {
    cout << "\nSo you acknowledge your failure and accept defeat.\n"
         << "Chances are, you would have failed anyways...\n\n";
    hs.readCurrentScores();
    hs.addScore();
    hs.sortScores();
    hs.writeScores();
    hs.printScores();
    exit(1);
}

void game_menu::viewPlayer() {
    cout << "\nYou have: \n\n";
    cout << "Intelligence: " << p.getIntel() << endl;
    cout << "Time: " << p.getTime() << endl;
    cout << "Money: " << "$" << p.getMoney() << ".00\n\n";
    cout << "You are " << (20 - p.getPosition()) << " steps from the goal. ";
    cout << "Time left: " << p.getTime() << ".\n\n";
}

void game_menu::boostIntel() {
    int rand_2 = (rand() % 10 + 1);
    cout << "\nYou read through some technical papers. You gain " << rand_2 << " unit(s) of intelligence, but\n"
            "lose 2 units of time.\n\n";
    p.setIntel(p.getIntel() + rand_2);
    // Player's time has run out. Updating Scoreboard.
    if ((p.getTime() - 2) <= 0) {
        cout << "\nTIME HAS FALLEN TO ZERO. YOU DIE.\n\n";
        hs.readCurrentScores();
        hs.addScore();
        hs.sortScores();
        hs.writeScores();
        hs.printScores();
        exit(1);
    }
    p.setTime(p.getTime() - 2);
}

void game_menu::boostMoney() {
    int rand_3 = (rand() % 20 + 1);
    cout << "\nYou found some loose change. You gain $" << rand_3 << ".00, but\n"
            "lose 2 units of time.\n\n";
    p.setMoney(p.getMoney() + rand_3);
// Player's time has run out. Updating Scoreboard.
    if ((p.getTime() - 2) <= 0) {
        cout << "\nTIME HAS FALLEN TO ZERO. YOU DIE.\n\n";
        hs.readCurrentScores();
        hs.addScore();
        hs.sortScores();
        hs.writeScores();
        hs.printScores();
        exit(1);
    }
    p.setTime(p.getTime() - 2);

}

void game_menu::selectGameOption() {
    bool valid = false;
    while (!valid) {
        cout << "\n\t1) Move forward (takes time, could be risky...)" << endl;
        cout << "\t2) Read technical papers (boost intelligence, takes time)" << endl;
        cout << "\t3) Search for loose change (boost money, takes time)" << endl;
        cout << "\t4) View character" << endl;
        cout << "\t5) Quit the game" << endl;
        cout << "\n\tPlease choose an action: ";
        cin >> option;

        switch (option) {
            case 1:
                dealEncounters();
                break;

            case 2:
                boostIntel();
                break;

            case 3:
                boostMoney();
                break;

            case 4:
                viewPlayer();
                break;

            case 5:
                endGame();
                break;

            default:
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout << "\n" << "\nInvalid response. Try again.\n\n";
                continue;
        }
        continue;
    }
}

/** Main driver */
int main() {
    srand(time(NULL));
    main_menu mm;
    game_menu gm;
    mm.getCharName();
    mm.selectMainOption();
    gm.selectGameOption();
    return 0;
};