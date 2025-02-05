/* Project 3
 * Demarco Guajardo
 * dag0047@auburn.edu
 * project3_Guajardo_dag0047.cpp
 * I used g++ to compile my code.
 * I used the project 3 hints on Canvas.
 * I used GeeksForGeeks to learn difference between
 * << and >> in streams.
 * I used Stack Overflow to healp learn how to open files.
 */

#include <fstream>
#include <iostream>
#include <cstdlib>

using namespace std;

//Array can't be higher than 100
const int MAX_SIZE = 100;

//METHODS

/*
 * This function reads numbers from a file and puts them into
 * an array and returns the total size of that array.
 */
int readFile(int inputArray[], ifstream& fsIn) {
    //Initialize index
    int i = 0;

    //While the file's data is there, store in inputArray at
    //dedicated index.
    while (fsIn >> inputArray[i]) {
        //cout << inputArray[i] << endl;
        i++;
    }
    return i;
}

/*
 * This function combines and sorts the two arrays into one
 * and returns the total size of the combined array.
 */
int sort(int inputArray1[], int inputArray1Size,
         int inputArray2[], int inputArray2Size,
         int outputArray[]) {
    //Initialize indexes of arrays 1, 2, and the output array.
    int i1 = 0;
    int i2 = 0;
    int iOut = 0;

    //While there are still elements in both arrays,
    while (i1 < inputArray1Size && i2 < inputArray2Size) {
        //If array 1's element smaller than array 2's element,
        if (inputArray1[i1] < inputArray2[i2]) {
            //Put array 1's element into output array first.
            outputArray[iOut++] = inputArray1[i1++];
        }
        else {
            //Otherwise, put array 2's element into output array
            //first.
            outputArray[iOut++] = inputArray2[i2++];
        }
    }

    //While there are elements in array 1 but not array 2,
    while (i1 < inputArray1Size) {
        outputArray[iOut++] = inputArray1[i1++];
    }

    //While there are elements in array 2 but not array 1,
    while (i2 < inputArray2Size) {
        outputArray[iOut++] = inputArray2[i2++];
    }

    return iOut;
}

/*
 * This function writes the numbers from the output array into a new file.
 */
void writeFile(int outputArray[], int outputArraySize, ofstream& fsOut) {
    for (int i = 0; i < outputArraySize; i++) {
        fsOut << outputArray[i] << " ";
    }
}

/*
 * The actual program.
 */
int main () {

    //main method Variables

    //Variables to read data from files 1 and 2 respectively.
    ifstream fsIn1;
    ifstream fsIn2;
    //Variable to write data to file 3 (new file).
    ofstream streamOut;
    //Initializes array for files 1, 2, and 3 that can hold max 100 elements.
    int Array1[MAX_SIZE];
    int Array2[MAX_SIZE];
    int combinedArray[MAX_SIZE];
    //Sizes of each array.
    int Array1Size;
    int Array2Size;
    int combinedArraySize;

    //Begin displaying
    cout << "*** Welcome to Demarco's sorting program ***" << "\n";

    //Read data from file 1
    char fileName1[100];
    cout << "Enter the first input file name: ";
    cin.getline(fileName1, 100);
    fsIn1.open(fileName1);
    if (!fsIn1.is_open()) {
        cout << "Input file opening failed.\n";
        return 1;
    }

    Array1Size = readFile(Array1, fsIn1);
    fsIn1.close();

    cout << "The list of " << Array1Size << " numbers in file "
         << fileName1 << " is:\n";

    //List out each element in file 1.
    for (int i = 0; i < Array1Size; i++) {
        cout << Array1[i] << endl;
    }

    //Read data from file 2.
    char fileName2[100];
    cout << "\nEnter the second input file name: ";
    cin.getline(fileName2, 100);
    fsIn2.open(fileName2);
    if (!fsIn2.is_open()) {
        cout << "Input file opening failed.\n";
        return 1;
    }

    Array2Size = readFile(Array2, fsIn2);
    fsIn2.close();

    //List out each element in file 2.
    cout << "The list of " << Array2Size << " numbers in file "
         << fileName2 << " is: \n";

    for (int i = 0; i < Array2Size; i++) {
        cout << Array2[i] << endl;
    }

    //Combine the two files.
    combinedArraySize = sort(Array1, Array1Size, Array2,
                             Array2Size, combinedArray);

    //List out each element in file 3 (the combined file).
    cout << "\nThe sorted list of " << combinedArraySize << " numbers is: ";

    for (int i = 0; i < combinedArraySize; i++) {
        cout << combinedArray[i] << " ";
    }

    char fileName3[100];
    cout << "\nEnter the output file name: ";
    cin.getline(fileName3, 100);
    streamOut.open(fileName3);
    if (!streamOut.is_open()) {
        cout << "Output file opening failed.\n";
        return 1;
    }



    //Write third file.
    writeFile(combinedArray, combinedArraySize, streamOut);
    streamOut.close();

    cout << "*** Please check the new file - " << fileName3 << " ***";
    cout << "\n*** Goodbye. ***\n";





}
