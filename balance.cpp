// Author: Winson Gin
// Course: CPSC 301 7-9:50pm
// Date created: February 12, 2019
// Last updated: April 11, 2019
// Purpose of this program:
//    This program will read in a text file and display the text file. Then, it will
//    find the richest person with the maximum balance. It will also prompt the user
//    to deposit money into their account. Finally, the file will be overwritten with
//    the updated balances.

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;


struct PERSON{
  char Name[20];
  float Balance;
};

void printmenu();
int countLines();
PERSON* readData(int N);
void Display(PERSON array[], int N);
void findRichest(PERSON array[], int N);
bool verifyName(string fullname, PERSON array[], int N);
void Deposit(string name, PERSON array[], int N, double amount);
void newCopy(string file, PERSON array[], int N);

int main()
{
  int numLines = 0;
  string fullname;
  string fname;
  string lname;
  numLines = countLines();
  PERSON* P;
  P = readData(numLines); //the PERSON* P will catch the address of the starting point of the new array
    int choice;
    do
    {
        printmenu();
        cin >> choice;
        switch(choice)
        {
            case 1:
                // Act on display
                Display(P, numLines); // passing the array, P, as the first argument, and numLines as the second argument
                cout << endl;
                break;

            case 2:
                // Act on deposit
                cout << "Enter name: ";
                cin >> fname >> lname;
                fname = fname.substr(0, 9);
                lname = lname.substr(0, 10);
                fullname = fname + " " + lname;

                double amount;
                bool found;
                found = verifyName(fullname, P, numLines);

                if(found == true){
                  cout << "Amount: ";
                  cin >> amount;
                  Deposit(fullname, P, numLines, amount);
                }
                else{
                  cout << "Record not found." << endl;
                }
                break;

            case 3:
                // Act highest balance
                findRichest(P, numLines);
                break;

            case 4:
                // Act on update records
                newCopy("data.txt", P, numLines);
                cout << "File Updated. . ." << endl;
                break;

            case 5:
                // Must call update records here before exiting the program
                newCopy("data.txt", P, numLines);
                cout << "File Updated. . ." << endl;
                break;

            default:
                cout << "Invalid entry" << endl;
                break;
        }
        cout << endl;
   } while(choice != 5);
      return 0;
}
void printmenu() {
    cout << "Please enter a choice:" << endl;
    cout << "1. Display records"<< endl;
    cout << "2. Deposit funds"<< endl;
    cout << "3. Find Highest Balance" << endl;
    cout << "4. Update records" << endl;
    cout << "5. Exit the program" << endl;
}

// This function will read in the .txt file and count how many lines there are.
int countLines(){
  ifstream file;
  string fname;
  int counter = 0;
  file.open("data.txt");

  if(!file){
    cout << "Cannot open input file.\n";
  }

  while(getline(file, fname)){
    counter++;
  }

  file.close();
  return counter;
}

//reads the data from the .txt file and stores it into a dynamically allocated array and returns a PERSON*
PERSON* readData(int N){
  PERSON* P = new PERSON[N];
  string fname;
  string lname;
  string fullname;
  string balance;
  ifstream file;
  file.open("data.txt");

  if(!file){
    cout << "Cannot open input file.\n";
  }

  for(int i = 0; i < N; i++){
    file >> fname;
    file >> lname;
    fname = fname.substr(0, 9);
    lname = lname.substr(0, 10);
    fullname = fname + " " + lname;
    strcpy(P[i].Name, fullname.c_str());
    file >> P[i].Balance;
  }

  file.close();
  return P;
  delete[] P;
  P = NULL;
}

// This function will display all the names and balances in the .txt file
void Display(PERSON array[], int N){
  cout << left << setw(18)<< "Name";
  cout << right << setw(18) << "Balance" << endl;
  cout << "---------------------------------------" << endl;
  for(int i = 0; i < N; i++){
    cout << left << setw(18) << array[i].Name << " ";
    cout << fixed << setprecision(2) << right << setw(18) << array[i].Balance;
    cout << endl;
  }
}

// This function will find the richest person in the array and print their name
void findRichest(PERSON array[], int N){
  double max = 0;
  int richest = 0;
  for(int i = 0; i < N; i++){
    if(array[i].Balance > max){
      max = array[i].Balance;
      richest = i;
    }
  }
  cout << "Highest balance: ";
  cout << array[richest].Name << endl;
}

// verifyName will check to see if the name exists in the system or not
bool verifyName(string name, PERSON array[], int N){
  bool found = false;
    for(int i = 0; i < N; i++){
      if(name == array[i].Name){
        found = true;
      }
    }
  return found;
}
// This function will deposit the amount that was determined in main.
void Deposit(string name, PERSON array[], int N, double amount){
  for(int i = 0; i < N; i++){
    if(name == array[i].Name){
      array[i].Balance += amount;
      cout << fixed << setprecision(2) << "New balance: " << array[i].Balance << endl;
    }
  }
}

// This function will overwrite the .txt file
void newCopy(string FILE, PERSON array[], int N){
  ofstream file;
  file.open(FILE);
  for(int i = 0; i < N; i++){
    file << array[i].Name << " ";
    file << fixed << setprecision(2) << array[i].Balance << endl;
  }
  file.close();
}
