/*
Angel
April 2021
Project
*/

// import libraries
#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include <fstream>
using namespace std;

//prototypes
void arrayTutorial();
void addSeating();
void removeSeating();
void viewList();
void viewProfit();
//global variables
const string FILENAME = "Seating.txt";

//Entry point app
int main()
{
	//seed
	srand(time(0));

	//password
	string password = "";
	string appPass = "passWord";
	bool success = false;
	for (int i = 0; i < 3; i++) {
		cout << "Enter password: ";
		cin >> password;
		if (password == appPass) {
			success = true;
			break;
		}
		else {
			cout << "\nInvalid password.\n" << endl;
		}
	}
	if (success == true) {
		cout << "\nWelcome.\n" << endl;
	}
	else {
		cout << "\nAccess Denied.\n" << endl;
		system("pause");
		return -1;
	}
	//input
	int choice = 0;
	do {
		system("cls");
		cout << "Menu\n" << endl;
		cout << "1) Add Seating" << endl;
		cout << "2) Remove Seating" << endl;
		cout << "3) View Seating List" << endl;
		cout << "4) View Profits" << endl;
		cout << "5) Array Tutorial" << endl;
		cout << "6) Close\n" << endl;
		cout << "Enter your choice: ";
		cin >> choice;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "\nError. Please use numbers only. No letters or characters." << endl;
			choice = -1;
		}
		else {
			cin.ignore(100, '\n');
		}
		switch (choice)
		{
		case 1:
			addSeating();
			break;
		case 2:
			removeSeating();
			break;
		case 3:
			viewList();
			break;
		case 4:
			viewProfit();
			break;
		case 5:
			arrayTutorial();
			break;
		case 6:
			cout << "\nGoodbye" << endl;
			break;
		default:
			cout << "\nError. Please select from the menu." << endl;
			cout << "Choice must be 1 to 5." << endl;
			cout << "Try again: ";
			cin >> choice;
			break;
		}

		//pause
		cout << endl;
		system("pause");
	} while (choice != 6);
	return 0;
}

void arrayTutorial()
{
	cout << "\nArray Tutorial\n" << endl;
	cout << "First step: create the array" << endl;
	cout << "\tdatatype arrayName[size];" << endl;
	cout << "- for example: int numbers[10]; //create integer array of 10\n" << endl;
	cout << "Second step: load the array using a for loop" << endl;
	cout << "\tfor(int i = 0; i < arraySize; i++) " << endl;
	cout << "\t{" << endl;
	cout << "\t\tarrayName[i] = value;" << endl;
	cout << "\t}\n" << endl;
	cout << "Third step: display the array's contents using a for loop" << endl;
	cout << "\tfor (int i = 0; i < arraySize; i++)" << endl;
	cout << "\t{" << endl;
	cout << "\t\t cout << arrayName[i] << endl;" << endl;
	cout << "\t}" << endl;

	cout << "\n\nHere is the output of the integer array from above:" << endl;
	int numbers[10];
	int min = 10;
	int max = 99;
	for (int i = 0; i < 10; i++) {
		numbers[i] = rand() % (max - min + 1) + min;
	}
	for (int i = 0; i < 10; i++) {
		cout << numbers[i] << endl;
	}
}

void addSeating()
{
	string tableNum, partySize, guestName, orderNum, orderPrice;
	cout << "\nEnter table number: ";
	getline(cin, tableNum);
	cout << "Enter party size: ";
	getline(cin, partySize);
	cout << "Enter guest name: ";
	getline(cin, guestName);
	cout << "Enter order number: ";
	getline(cin, orderNum);
	cout << "Enter order price: ";
	getline(cin, orderPrice);

	ofstream oFile(FILENAME, ios::app);

	oFile << tableNum << '#' << partySize << '#' << guestName << '#' << orderNum << '#' << orderPrice << endl;

	oFile.close();

	cout << "\nList updated." << endl;
}

void removeSeating()
{
	ofstream oFile(FILENAME, ios::app);
	bool found = false;
	string removeSeat;
	cout << "\nEnter seat to clear: ";
	getline(cin, removeSeat);
	//ifstream iFile(FILENAME);
	ifstream iFile(FILENAME + ".tmp");
	while (iFile.peek() > -1) {
		string tableNum, partySize, guestName, orderNum, orderPrice;
		getline(iFile, tableNum, '#');
		getline(iFile, partySize, '#');
		getline(iFile, guestName, '#');
		getline(iFile, orderNum);
		if (tableNum == removeSeat) {
			found = true;
		}
		else {
			oFile << tableNum << '#' << partySize << '#' << guestName << '#' << orderNum << endl;
		}
	}
	iFile.close();
	oFile.close();
	remove(FILENAME.c_str());
	rename((FILENAME + ".tmp").c_str(), FILENAME.c_str());
	if (found == true) {
		cout << "\nRecord was deleted." << endl;
	}
	else {
		cout << "\nRecord was not found." << endl;
	}
}

void viewList()
{
	cout << "\nSeating List\n" << endl;
	ifstream iFile(FILENAME);
	if (iFile.is_open()) {
		while (iFile.peek() > -1) {
			string tableNum, partySize, guestName, orderNum, orderPrice;
			getline(iFile, tableNum, '#');
			getline(iFile, partySize, '#');
			getline(iFile, guestName, '#');
			getline(iFile, orderNum, '#');
			getline(iFile, orderPrice);
			cout << "Table " << tableNum << endl;
			cout << "\tParty Size: " << partySize << endl;
			cout << "\tName: " << guestName << endl;
			cout << "\tOrder Number: " << orderNum << endl;
			cout << "\tOrder Profit: " << orderPrice << '\n' << endl;
		}
		iFile.close();
	}
}

void viewProfit()
{
	cout << "\nProfit List\n" << endl;
	ifstream iFile(FILENAME);
	if (iFile.is_open()) {
		while (iFile.peek() > -1) {
			string tableNum, partySize, guestName, orderNum, orderPrice;
			getline(iFile, orderNum, '#');
			getline(iFile, orderPrice);
			cout << "Order #" << orderNum << ": " << endl;
			cout << "\tOrder Profit: $" << orderPrice << '\n' << endl;
		}
		iFile.close();
	}
}