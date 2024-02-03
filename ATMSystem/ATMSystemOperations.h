#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

// create a struct sClients
struct sClients
{
	string name, accountNumber, pinCode, phone;
	float accountBalance;
};

// global variable of number
const int noclinetpos = -234252654643;

// function to return a vector of words in a string.
vector<string> spilt_str(const string& str, string sep);
// function to return a string of join elements in vector.
string join(const vector<string>& tokens, string sep);
//return line of string data which record converted to line.
string convertRecordToLine(sClients& client);
// return a list of lines clients data.
vector<string> convertAllRecordstoLines(vector<sClients>& clients);
// return all clients data from file in list of lines
vector<string> getDataFromFile(string fileName);
// return  a record which convert line to record.
sClients convertLinetoRecord(const string& line);
// return a list of records clients data.
vector<sClients> convertAllLinestoRecords(vector<string>& lines);
// function to updata clients data in file
bool updateDataInFile(const vector<string>& lines, string fileName);
// function to add new a clients in the file.
bool pushDatatofile(const vector<string>& lines, string fileName);
// function to add new a clients in the file.
bool pushClientDatatofile(const string& line, string fileName);

int findClient(string accountNum, const vector<sClients>& clients);
// check if index return from findClient function is correct or no.
bool isCorrectIndex(int index);
// return true if client account number and pincode is correct or false if not.
bool checkClientLoginInfo(string accountNumber, string pinCode, const vector<sClients>& clients, sClients& clientInfo);

// withdraw operation
bool withdraw(int amout, string fileName, sClients& client);
// deposit operation
bool deposit(int amout, string fileName, sClients& client);