//
// Name:            Donald Tran
// Date:            02/24/17
// AU User ID:      DZT0021
// File Name:       hw4.cpp
//
// Instructions to compile:
// g++ -std=c++11 hw4.cpp
//
// README:
// This program was created using the "CLion" IDE and
// compiled using CMake Version 3.6 and the g++ compiler on
// Tux062 via SSH Protocol
//
// CITED SOURCES:
// (1) Mergesort reference:
//     http://www.algolist.net/Algorithms/Merge/Sorted_arrays
//
// (2) How to create an output file from the contents of an array:
//     http://stackoverflow.com/questions/22190048/
//     how-to-write-the-content-of-an-array-into-text-file-c
//
// (3) How to make access files and their placement in my local directory:
//     http://stackoverflow.com/questions/15224343/
//     exe-does-not-find-a-text-file-in-the-same-directory
//

#include <iostream>
#include <cstdlib> //for exit()
#include <fstream>
#include <string>
#include <cassert>
using namespace std;

// Main Function Prototypes
int readfile(int inputArray[], ifstream& inStream);
int sort(int inputArray1[], int inputArray1_size, int inputArray2[], int inputArray2_size, int outputArray[]);
void writefile(int outputArray[], int outputArray_size);
void linePause(void);
void getArrElements(int inputArray[], int array_size);
void getArrElements2(int inputArray[], int array_size);

// Test Case Prototypes
void readFile_test(ifstream& inStream);
void sort_test(void);

// Class constants
const int MAX_SIZE = 1000;

int main() {

    ifstream inStream;
    string filename_1;
    string filename_2;
    string filename_3;
    int iArray1[MAX_SIZE];
    int iArray2[MAX_SIZE];
    int oArray[MAX_SIZE];
    int iArray1_size;
    int iArray2_size;
    int oArray_size;

    cout << "*** Unit Test Cases ***\n";
    readFile_test(inStream);
    linePause();
    sort_test();
    linePause();

    cout << "*** Welcome to Don's Sorting Program ***" << endl;
    cout << "Enter the first input filename: ";
    cin >> filename_1;
    inStream.open(filename_1);
    iArray1_size = readfile(iArray1, inStream);
    inStream.close();
    cout << "The list of " <<  iArray1_size << " numbers in file ";
    cout << filename_1 << " is:" << endl;
    getArrElements(iArray1, iArray1_size);

    cout << "Enter the second input filename: ";
    cin >> filename_2;
    inStream.open(filename_2);
    iArray2_size = readfile(iArray2, inStream);
    inStream.close();
    cout << "The list of " <<  iArray2_size << " numbers in file ";
    cout << filename_2 << " is:" << endl;
    getArrElements(iArray2, iArray2_size);

    oArray_size = sort(iArray1, iArray1_size, iArray2, iArray2_size, oArray);
    cout << "The sorted list of " << oArray_size;
    cout << " numbers is: ";
    getArrElements2(oArray, oArray_size);
    writefile(oArray, oArray_size);

    return 0;
}

/**
 * Reads in lines from text files
 * @param inputArray
 * @param filename
 * @return array_size
 */
int readfile(int inputArray[], ifstream& inStream) {
    int index = 0;
    if (inStream.fail()) {
        cout << "\tInput file opening failed." << endl;
        exit(1);
    }
    inStream >> inputArray[index];
    while (!inStream.eof() && index < MAX_SIZE) {
        index++;
        inStream >> inputArray[index];
    }
    return index;
}

/**
 * Performs a Mergesort on two given int arrays and ouputs to a 3rd array
 * @param inputArray1
 * @param inputArray1_size
 * @param inputArray2
 * @param inputArray2_size
 * @param outputArray
 * @return outputArray_size
 */
int sort(int inputArray1[], int inputArray1_size, int inputArray2[], int inputArray2_size, int outputArray[]) {
    int i, j, k;
    i = 0;
    j = 0;
    k = 0;

    while (i < inputArray1_size && j < inputArray2_size) {
        if (inputArray1[i] <= inputArray2[j]) {
            outputArray[k] = inputArray1[i];
            i++;
        } else {
            outputArray[k] = inputArray2[j];
            j++;
        }
        k++;
    }
    if (i < inputArray1_size) {
        for (int p = i; p < inputArray1_size; p++) {
            outputArray[k] = inputArray1[p];
            k++;
        }
    }
    else {
        for (int p = j; p < inputArray2_size; p++) {
            outputArray[k] = inputArray2[p];
            k++;
        }
    }
    return k;
}

/**
 * Writes the contents of an array with given array size to an output text file.
 * @param outputArray
 * @param outputArray_size
 */
void writefile(int outputArray[], int outputArray_size) {
    string filename_3;
    cout << "Enter the output filename: ";
    cin >> filename_3;
    ofstream outFile(filename_3);
    if (outFile.is_open()) {
        for (int i = 0; i < outputArray_size; i++) {
            outFile << outputArray[i] << endl;
        }
        outFile.close();
    } else {
        cout << "Unable to open output file.\n" << endl;
        return;
    }
    cout << "*** Please check the new file - " << filename_3 << " ***" << endl;
    cout << "*** Goodbye. ***" << endl;
}

/**
 * Tests readfile() for functionality
 * @param instream
 */
void readFile_test(ifstream& inStream) {

    int test_arr1[MAX_SIZE];
    int test_arr2[MAX_SIZE];
    int test_arr3[MAX_SIZE];

    cout << "Unit Testing 1: Function – readfile(int inputArray[], ifstream& inStream)\n";
    cout << "\tCase 1.1: Testing array size after processing input1.txt\n";
    inStream.open("input1.txt");
    assert(6 == readfile(test_arr1, inStream));
    cout << "\tCase 1.1 passed ...\n\n";
    inStream.close();

    cout << "\tCase 1.2: Testing array size after processing input2.txt\n";
    inStream.open("input2.txt");
    assert(5 == readfile(test_arr2, inStream));
    cout << "\tCase 1.2 passed ...\n\n";
    inStream.close();

    cout << "\tCase 1.3: Test empty file returns a zero array.\n";
    inStream.open("test_input1.txt");
    assert(0 == readfile(test_arr3, inStream));
    cout << "\tCase 1.3 passed ...\n\n";
    inStream.close();

    cout << "\tCase 1.4: Tests standard exceptions including data type errors.\n";
    inStream.open("test_input2.txt");
    assert(inStream.fail());
    cout << "\tCase 1.4 passed ...\n\n";
    inStream.close();
}

/**
 * Tests sort function for functionality
 */
void sort_test(void) {
    int testArr1A[MAX_SIZE] = {};
    int testArr2A[MAX_SIZE] = {1, 2, 3, 4};
    int testArr3A[MAX_SIZE];
    int testArr1A_size = 0;
    int testArr2A_size = 4;
    int testArr3A_size;

    cout << "Unit Testing 2: Function – int sort(int inputArray1[], int inputArray1_size, "
            "int inputArray2[], int inputArray2_size, int outputArray[]);\n";
    cout << "\tCase 2.1: Testing sort can manage an empty array for the first input array\n";
    testArr3A_size = sort(testArr1A, testArr1A_size, testArr2A, testArr2A_size, testArr3A);
    assert(testArr3A_size == 4);
    cout << "\tCase 2.1 passed ...\n\n";

    int testArr1B[MAX_SIZE] = {1, 2, 3, 4};
    int testArr2B[MAX_SIZE] = {};
    int testArr3B[MAX_SIZE];
    int testArr1B_size = 4;
    int testArr2B_size = 0;
    int testArr3B_size;
    cout << "\tCase 2.2: Testing sort can manage an empty array for the second input array\n";
    testArr3B_size = sort(testArr1B, testArr1B_size, testArr2B, testArr2B_size, testArr3B);
    assert(testArr3B_size == 4);
    cout << "\tCase 2.2 passed ...\n\n";

    int testArr1C[MAX_SIZE];
    int testArr2C[MAX_SIZE];
    int testArr3C[MAX_SIZE];
    int testArr1C_size = 0;
    int testArr2C_size = 0;
    int testArr3C_size;
    cout << "\tCase 2.3: Testing sort can manage two empty arrays\n";
    testArr3C_size = sort(testArr1C, testArr1C_size, testArr2C, testArr2C_size, testArr3C);
    assert(testArr3C_size == 0);
    cout << "\tCase 2.3 passed ...\n\n";

    int testArr1D[MAX_SIZE] = {1, 3, 5, 7, 9};
    int testArr2D[MAX_SIZE] = {2, 4, 6, 8, 10};
    int testArr3D[MAX_SIZE];
    int testArr1D_size = 5;
    int testArr2D_size = 5;
    int testArr3D_size;
    cout << "\tCase 2.4: Testing sort on two standard equal length arrays\n";
    testArr3D_size = sort(testArr1D, testArr1D_size, testArr2D, testArr2D_size, testArr3D);
    assert(testArr3D_size == 10 || testArr3D[4] == 5);
    cout << "\tCase 2.4 passed ...\n\n";

    int testArr1E[MAX_SIZE] = {7};
    int testArr2E[MAX_SIZE] = {4};
    int testArr3E[MAX_SIZE];
    int testArr1E_size = 1;
    int testArr2E_size = 1;
    int testArr3E_size;
    cout << "\tCase 2.5: Testing sort on two arrays containing only one element each\n";
    testArr3E_size = sort(testArr1E, testArr1E_size, testArr2E, testArr2E_size, testArr3E);
    assert(testArr3E[1] == 7);
    cout << "\tCase 2.5 passed ...\n\n";

    int testArr1F[MAX_SIZE];
    int testArr2F[MAX_SIZE];
    int testArr3F[MAX_SIZE];
    int testArr1F_size = 500;
    int testArr2F_size = 501;
    int testArr3F_size;

    int count;
    int evens = 2;
    int odds = 1;

    for (count = 0; count < 501; count++) {
        testArr1F[count] = evens;
        testArr2F[count] = odds;
        evens+=2;
        odds +=2;
    }
    cout << "\tCase 2.6: Testing upper bound of array index for accuracy.\n";
    testArr3F_size = sort(testArr1F, testArr1F_size, testArr2F, testArr2F_size, testArr3F);
    assert(testArr3F[MAX_SIZE - 1] == 1000);
    cout << "\tCase 2.6 passed ...\n\n";
}

/**
 * Pause command for Linux Terminal
 */
void linePause(void) {
    cout << "Press any key to continue...\n";
    cin.ignore().get();
}

/**
 * Returns every element of the inputArray on a new line
 * @param inputArray
 * @param array_size
 */
void getArrElements(int inputArray[], int array_size) {
    for (int i = 0; i < array_size; i++) {
        cout << inputArray[i] << endl;
    }
    cout << "\n";
}

/**
 * Returns every element of the inputArray on the same line
 * @param inputArray
 * @param array_size
 */
void getArrElements2(int inputArray[], int array_size) {
    for (int i = 0; i < array_size; i++) {
        cout << inputArray[i] << " ";
    }
    cout << "\n";
}
