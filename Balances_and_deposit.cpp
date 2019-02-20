// Author: Winson Gin
// Course: CPSC 301 7-9:50pm
// Date created: February 12, 2019
// Last updated: February 20, 2019
// Purpose of this program:
//    This program will read in a text file and display the text file. Then, it will
//    find the richest person with the maximum balance. It will also prompt the user
//    to deposit money into their account. Finally, the file will be overwritten with
//    the updated balances.

#include <iostream>
#include <fstream>
#include <string.h>
#include <iomanip>

using namespace std;


struct PERSON{
  char Name[20];
  float Balance;
};

int countLines();
void fillArray(PERSON array[], int N);
void Display(PERSON array[], int N);
void findRichest(PERSON array[], int N);
void Deposit(string name, PERSON array[], int N);
void newCopy(string file, PERSON array[], int N);

int main(){

  int numLines = 0;
  numLines = countLines();
  PERSON P[numLines];

  fillArray(P, numLines); //passing numLines as first argument and the array, P, as the arguments
  Display(P, numLines); // passing the array, P, as the first argument, and numLines as the second argument
  cout << endl;
  findRichest(P, numLines);

  string name;

  cout << "Enter your full name to deposit your money: " << endl;
  getline(cin, name);

  Deposit(name, P, numLines);
  newCopy("data.txt", P, numLines);
  return 0;
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

// This function will receive the size of the .txt file and store names and balances in that array
void fillArray(PERSON array[], int N){
  string fname, lname, fullname;
  string empty = "";
  double balance;
  int i = 0;
  ifstream file;

  file.open("data.txt");

  if(!file){
    cout << "Error: Could not open file.";
  }

  while(!file.eof()){
    file >> fname >> lname;
    file >> balance;
    fullname = fname + " " + lname;
    strcpy(array[i].Name, fullname.c_str());
    array[i].Balance = balance;
    getline(file, empty);
    i++;
  }
  file.close();
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
  cout << "The customer with maximum balance is ";
  cout << array[richest].Name << endl;
}

// This function will prompt the user for how much money they want to deposit into their account
void Deposit(string name, PERSON array[], int N){
  double deposit = 0.0;
  int count = 0;

  for(int i = 0; i < N; i++){
    if(name == array[i].Name){
      cout << name << ", how much would you like to deposit? " << endl << "$";
      cin >> deposit;
      array[i].Balance += deposit;
      cout << "Now your new balance is: " << array[i].Balance << endl;
    }
    else{
      count++;
    }
  }
  if(count == N){
    cout << "That name does not exist in our system." << endl;
  }
}

// This function will overwrite the .txt file
void newCopy(string FILE, PERSON array[], int N){
  ofstream file;
  file.open(FILE);
  for(int i = 0; i < N; i++){
    file << array[i].Name << " ";
    file << array[i].Balance << endl;
  }
  file.close();
}
