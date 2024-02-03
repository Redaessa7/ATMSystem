#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include "ATMSystemOperations.h"
using namespace std;

const string clientsFile = "ClientsData.txt";

// global client
sClients Currentclient;

enum mainMenu {
    QuickWithdraw = 1, NormalWithdraw = 2, Deposit = 3, CheckBalance = 4, LogOut = 5
};

enum quickWithdraw {
    Withdraw20= 1, Withdraw50 = 2, Withdraw100 = 3, Withdraw200 = 4, Withdraw400 = 5,
    Withdraw600 = 6, Withdraw800 = 7, Withdraw1000 = 8, eExit = 9
};

// declaration
void loginScreen();
void welcomeScreen();
void mainMenuScreen();
void quickWithdrawScreen();

void pleaseWait(string msg)
{
    cout << "\n\t\t\t\t "+msg+" ";
    for (short i = 0; i < 4; i++)
    {
        cout << "*";
        this_thread::sleep_for(chrono::milliseconds(800));
    }
}
void worngScreen(string msg)
{
    system("cls");
    system("color 4F");
    printf("\n\t\t\t\t %s!",msg.c_str());
    printf("\n\t\t\t\t Enter any keyborad to try again...");
    system("pause > 0");
    system("cls");
    system("color 0F");
}
void goBackMainMeue()
{
    printf("\n\t\t\t\tEnter any key to back main menu screen....");
    system("pause>0");
    mainMenuScreen();
}
void printTitleScreen(string title)
{
    system("cls");
    short numberOfSpace = 10 + title.size();
    string wihteSpace = "", separetor = "";

    for (short i = 0; i <= numberOfSpace + 10; i++)
    {
        separetor += '-';
    }

    for (short i = 0; i < ((numberOfSpace - title.size()) + 10) / 2; i++)
    {
        wihteSpace += ' ';
    }

    printf("\n\t\t\t\t%s\n", separetor.c_str());
    printf("\t\t\t\t%s%s%s", wihteSpace.c_str(), title.c_str(), wihteSpace.c_str());
    printf("\n\t\t\t\t%s\n", separetor.c_str());
}
void printMenu(const vector <string> & menu, bool vertical = false)
{
    printf("\n");
    if (vertical)
    {
        short count(0);
        printf("\t\t\t\t\t");
        for (short i = 0; i < menu.size(); i++)
        {
            if (count == 2)
            {
                printf("\n\t\t\t\t\t");
                count = 0;
            }
            printf("[%d]: %s       ", i + 1, menu.at(i).c_str());
            count++;
        }
    }
    else
    {
        for (short i = 0; i < menu.size(); i++)
        {
            printf("\t\t\t\t\t[%d]: %s\n", i + 1, menu.at(i).c_str());
        }
    }
    printf("\n\t\t\t\t-------------------------------------\n");
}

void withdrawperform(int amout)
{
    char ask = 'y';
    printf("\n\t\t\t\t(*)Are you sure to wirtdraw this amount(Y/N)? ");
    cin >> ask;

    if (ask == 'y' || ask == 'Y')
    {
        if (withdraw(amout, clientsFile, Currentclient))
        {
            printf("\n\t\t\t\tDone Successfully, New balance: %.2f", Currentclient.accountBalance);
        }
        else
        {
            printf("\n\t\t\t\tYour enter amount grater than your current balance");
        }
    }
}
void depositperform(int amout)
{
    char ask = 'y';
    printf("\n\t\t\t\t(*)Are you sure to wirtdraw this amount(Y/N)? ");
    cin >> ask;

    if (ask == 'y' || ask == 'Y')
    {
        if (deposit(amout, clientsFile, Currentclient))
        {
            printf("\n\t\t\t\tDone Successfully, New balance: %.2f", Currentclient.accountBalance);
        }
        else
        {
            printf("\n\t\t\t\tYour enter amount less than 0");
        }
    }
}

bool quickWMenuChoice(short choice)
{
    switch ((quickWithdraw)choice)
    {
    case quickWithdraw::Withdraw20:
        withdrawperform(20);
        goBackMainMeue();
        return true;
    case quickWithdraw::Withdraw50:
        withdrawperform(50);
        goBackMainMeue();
        return true;
    case quickWithdraw::Withdraw100:
        withdrawperform(100);
        goBackMainMeue();
        return true;
    case quickWithdraw::Withdraw200:
        withdrawperform(200);
        goBackMainMeue();
        return true;
    case quickWithdraw::Withdraw400:
        withdrawperform(400);
        goBackMainMeue();
        return true;
    case quickWithdraw::Withdraw600:
        withdrawperform(600);
        goBackMainMeue();
        return true;
    case quickWithdraw::Withdraw800:
        withdrawperform(800);
        goBackMainMeue();
        return true;
    case quickWithdraw::Withdraw1000:
        withdrawperform(1000);
        goBackMainMeue();
        return true;
    case quickWithdraw::eExit:
        goBackMainMeue();
        return false;
    default:
        break;
    }

}
void quickWithdrawScreen()
{
    printTitleScreen("Quick Withdraw Screen");
    vector<string> quickMenu = { "20","50","100","200","400","600","800","1000","Exit" };
    printMenu(quickMenu,true);
    short choice(0);
    do
    {
        printf("\t\t\t\t(*): Current Account Balance: %.2f\n", Currentclient.accountBalance);
        printf("\n\t\t\t\t(*): Please enter number of choice: ");
        cin >> choice;
    } while (quickWMenuChoice(choice));
}
void normalWithdrawScreen()
{
    printTitleScreen("Normal Withdraw Screen");
    printf("\t\t\t\t(*): Current Account Balance: %.2f\n", Currentclient.accountBalance);
    int amout(0);
    do
    {
        printf("\n\t\t\t\t(*): Please enter an amount multiple 5's: ");
        cin >> amout;
    } while (amout % 5 != 0);

    withdrawperform(amout);
}
void depositScreen()
{
    printTitleScreen("Deposit Screen");
    printf("\t\t\t\t(*): Current Account Balance: %.2f\n", Currentclient.accountBalance);
    int amout(0);
    do
    {
        printf("\n\t\t\t\t(*): Please enter an amount multiple 5's: ");
        cin >> amout;
    } while (amout % 5 != 0 || amout <= 0);
    depositperform(amout);
}
void checkBalanceScreen()
{
    printTitleScreen("Check Balance Screen");
    printf("\n\t\t\t\tYour account balance is: %.2f\n", Currentclient.accountBalance);
}

bool mainMenuChoice(short choice)
{
    switch ((mainMenu)choice)
    {
    case mainMenu::QuickWithdraw:
        quickWithdrawScreen();
        goBackMainMeue();
        return true;
    case mainMenu::NormalWithdraw:
        normalWithdrawScreen();
        goBackMainMeue();
        return true;
    case mainMenu::Deposit:
        depositScreen();
        goBackMainMeue();
        return true;
    case mainMenu::CheckBalance:
        checkBalanceScreen();
        goBackMainMeue();
        return true;
    case mainMenu::LogOut:
        welcomeScreen();
        return false;
    default:
        break;
    }

}
void mainMenuScreen()
{
    vector<string> menu = {"Quick Withdraw", "Normal Withdraw", "Deposit", "Check Balance", "LogOut" };
    printTitleScreen("ATM System");
    printMenu(menu);

    short choice(0);
    do
    {
        printf("\t\t\t\t(*): Please enter number of choice: ");
        cin >> choice;
    } while (mainMenuChoice(choice));
}
void loginScreen()
{
    string accountNumber, pinCode;
    bool loginSucces = false;
    do
    {
        printTitleScreen("Login Screen");

        // get account number from client
        printf("\n\t\t\t\t(*) Account number: ");
        getline(cin >> ws, accountNumber);

        printf("\n\t\t\t\t(*) PinCode: ");
        getline(cin, pinCode);

        vector<string> lines = getDataFromFile(clientsFile);
        vector<sClients> clients = convertAllLinestoRecords(lines);
        loginSucces = checkClientLoginInfo(accountNumber, pinCode, clients, Currentclient);

        pleaseWait("Please wait, Verifying");

        if (loginSucces)
        {
            system("cls");
            pleaseWait("Login Successfully, Loading");
            break;
        }
        else
        {

            worngScreen("Your Account number or pincode is wrong");
        }

    } while (true);

    mainMenuScreen();

}
void welcomeScreen()
{
    printTitleScreen("Welcome To Essa Bank");
    pleaseWait("Loading ATM System");
    loginScreen();
}

int main()
{
    welcomeScreen();
}