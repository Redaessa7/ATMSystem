#include "ATMSystemOperations.h"

// function to return a string of join elements in vector.
string join(const vector<string>& tokens, string sep = " ")
{
    string str = "";

    // check if strList is empty.
    if (tokens.empty())
        return str;

    for (const string& word : tokens)
        str += (word + sep);
    // remove last delimiter
    return str.substr(0, (str.length() - sep.length()));
}
//return line of string data which record converted to line.
string convertRecordToLine(sClients& client)
{
    // convert record to list of tokens
    vector<string> tokens = { client.accountNumber, client.pinCode,client.name,client.phone,to_string(client.accountBalance) };

    // convert record to line
    return join(tokens, "#//#");
}
// return a list of lines clients data.
vector<string> convertAllRecordstoLines(vector<sClients>& clients)
{
    vector<string> lines;

    for (sClients& client : clients)
    {
        lines.push_back(convertRecordToLine(client));
    }

    return lines;
}


// function to return a vector of words in a string.
vector<string> spilt_str(const string& str, string sep = " ")
{
    vector<string> tokens;

    // check if str or delimiter is empty or no
    if (str.empty() || sep.empty())
    {
        return tokens; // return empty vector
    }

    short posDelim(0), startWord(0), lenDelim = sep.length();
    string word = "";
    /*
        [1]: Take part of the string [posDelim: str.length()] using substr function.
        [2]: searching for the delimiter in the part that was taken in the first step using find function.
        [3]: increment the index to return from step 2 by lenDelim (to ignore delimiter position).
        [4]: add The index to return from step 3  to posDelim.
        [5]: increment the increase at 4 steps above to std::string::npos For comparison between posDelim and npos
    */

    while ((posDelim += (str.substr(posDelim, str.length()).find(sep)) + lenDelim) != std::string::npos + (startWord + lenDelim))
    {
        // store the word
        word = str.substr(startWord, posDelim - (startWord + lenDelim));

        if (!word.empty()) // case if word not empty
        {
            tokens.push_back(word);
        }
        startWord = posDelim;
    }

    // last word in string and add in vector
    word = str.substr(startWord, str.length());
    if (!word.empty())
    {
        tokens.push_back(word);
    }

    return tokens;
}
// return all clients data from file in list of lines
vector<string> getDataFromFile(string fileName)
{
    ifstream file(fileName);
    vector<string> lines;

    if (file.is_open())
    {
        string line;

        while (getline(file, line))
        {
            lines.push_back(line);
        }

        file.close();
        return lines;
    }

    return lines;
}
// return  a record which convert line to record.
sClients convertLinetoRecord(const string& line)
{
    sClients client;

    vector<string> tokens = spilt_str(line, "#//#");

    // convert line to record
    client.accountNumber = tokens[0];
    client.pinCode = tokens[1];
    client.name = tokens[2];
    client.phone = tokens[3];
    client.accountBalance = stof(tokens[4]);

    return client;
}
// return a list of records clients data.
vector<sClients> convertAllLinestoRecords(vector<string>& lines)
{
    vector<sClients> clients;

    for (string& line : lines)
        clients.push_back(convertLinetoRecord(line));

    return clients;
}

// function to add new a clients in the file.
bool pushDatatofile(const vector<string>& lines, string fileName)
{
    fstream file;

    file.open(fileName, ios::out | ios::app);

    if (file.is_open())
    {
        // push data to file.
        for (const string& line : lines)
            file << line << endl;

        file.close();
        return true;
    }
    // if push data field.
    return false;
}
// function to add new a clients in the file.
bool pushClientDatatofile(const string& line, string fileName)
{
    fstream file;

    file.open(fileName, ios::out | ios::app);

    if (file.is_open())
    {
        // push data to file.
        file << line << endl;

        file.close();
        return true;
    }
    // if push data field.
    return false;
}
// function to updata clients data in file
bool updateDataInFile(const vector<string>& lines, string fileName)
{
    fstream file;

    file.open(fileName, ios::out);

    if (file.is_open())
    {
        // write new data to file.
        for (const string& line : lines)
            file << line << endl;

        file.close();
        return true;
    }
    // if write data field.
    return false;
}


// return true if user username and password is correct or false if not.
bool checkClientLoginInfo(string accountNumber, string pinCode, const vector<sClients>& clients, sClients& clientInfo)
{

    int posUser = findClient(accountNumber, clients);

    if (posUser == noclinetpos)
    {
        return false;
    }
    else if (clients[posUser].accountNumber == accountNumber && clients[posUser].pinCode == pinCode)
    {
        clientInfo = clients[posUser];
        return true;
    }
    return false;
}
// function to search to a client in the file. return position if found.
int findClient(string accountNum, const vector<sClients>& clients)
{
    for (int index = 0; index < clients.size(); index++)
    {
        if (clients[index].accountNumber == accountNum)
        {
            return index;
        }
    }
    // if not found return size of clients + 2;
    return noclinetpos;
}
// check if index return from findClient function is correct or no.
bool isCorrectIndex(int index)
{
    return (index != noclinetpos);
}

// withdraw operation
bool withdraw(int amout , string fileName,sClients &client)
{
    if (amout > client.accountBalance)
    {
        return false;
    }
    vector<string> lines = getDataFromFile(fileName);
    vector<sClients> clients = convertAllLinestoRecords(lines);

    for (sClients& cl : clients)
    {
        if (client.accountNumber == cl.accountNumber)
        {
            client.accountBalance -= amout;
            cl.accountBalance = client.accountBalance;
            break;
        }
    }

    lines = convertAllRecordstoLines(clients);
    return updateDataInFile(lines, fileName);
}

// deposit operation
bool deposit(int amout, string fileName, sClients& client)
{
    if (amout <= 0)
    {
        return false;
    }
    vector<string> lines = getDataFromFile(fileName);
    vector<sClients> clients = convertAllLinestoRecords(lines);

    for (sClients& cl : clients)
    {
        if (client.accountNumber == cl.accountNumber)
        {
            client.accountBalance += amout;
            cl.accountBalance = client.accountBalance;
            break;
        }
    }

    lines = convertAllRecordstoLines(clients);
    return updateDataInFile(lines, fileName);
}
