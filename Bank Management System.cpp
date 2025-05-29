#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <cctype>
#include <fstream>
#include <ctime>
using namespace std;
void ShowMainMenu();
void ShowTransactionsMenu();
void GoBackToTransactionsMenu();
struct sClient 
{
    string AccountNumber ;
    string Name ;
    string Phone ;
    string PinCode ;
    double AccountBalance ;
    bool MarkForDelete = false ;
};
vector<string> SplitString (string S1 , string delim)
{
    string sWord = "";
    short Position ;
    vector<string> vString;
    while ((Position = S1.find(delim)) != std::string::npos)
    {
        sWord = S1.substr(0,Position);
        if(sWord != "")
        {
            vString.push_back(sWord);
        }
        S1.erase(0,Position + delim.length());
    }
    if (S1 != "")
    {
        vString.push_back(S1);
    }
    return vString;
}
sClient ConvertLineToRecord (string Line , string Separator = "#//#")
{
    sClient Client ;
    vector<string> vString = SplitString(Line,Separator);
    if (vString.size() == 5)
    {
        Client.AccountNumber = vString[0];
        Client.PinCode = vString[1];
        Client.Name = vString[2];
        Client.Phone = vString[3];
        Client.AccountBalance = stod(vString[4]);
    }
    return Client ;
}
string ConvertRecordToLine (sClient Client , string Separator = "#//#")
{
    return Client.AccountNumber + Separator +
           Client.PinCode + Separator + 
           Client.Name + Separator + 
           Client.Phone + Separator +
           to_string(Client.AccountBalance);
}
vector<sClient> LoadClientDataFromFileToVector (string FileName)
{
    vector<sClient> vClients ;
    fstream MyFile ;
    MyFile.open(FileName,ios::in);
    if (MyFile.is_open())
    {
        string Line ;
        while (getline(MyFile,Line))
        {
            sClient Client = ConvertLineToRecord(Line);
            vClients.push_back(Client);
        }
        MyFile.close();
    }
    return vClients ;
}
bool ClientsExitsByAccountNumber (string AccountNumber , string FileName)
{
    vector<sClient> vClients ;
    fstream MyFile ;
    MyFile.open(FileName,ios::in);
    if (MyFile.is_open())
    {
        string Line ;
        sClient Client ;
        while (getline(MyFile,Line))
        {
            Client = ConvertLineToRecord (Line);
            if (Client.AccountNumber == AccountNumber)
            {
                MyFile.close();
                return true ;
            }
            vClients.push_back(Client);
        }
        MyFile.close();
    }
    return false ;
}
sClient ReadNewClient ()
{
     sClient Client;
     cout << "Enter Account Number ?";
     getline (cin >> ws , Client.AccountNumber);
     while (ClientsExitsByAccountNumber(Client.AccountNumber,"Clients.txt"))
     {
        cout << "Client With [" << Client.AccountNumber << "] is already exist , Enter Another Account Number ? ";
        getline(cin >> ws , Client.AccountNumber);
     }
     cout << "Enter Pin Code ?";
     getline (cin , Client.PinCode);

     cout << "Enter Name ?";
     getline (cin , Client.Name);

     cout << "Enter Phone ?";
     getline (cin , Client.Phone);

     cout << "Enter Balance ?";
     cin >> Client.AccountBalance ;

     return Client ;
     
}
void PrintClientRecordLine (sClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber ;
    cout << "| " << setw(10) << left << Client.PinCode ;
    cout << "| " << setw(40) << left << Client.Name ;
    cout << "| " << setw(12) << left << Client.Phone ;
    cout << "| " << setw(12) << left << Client.AccountBalance ;
}
void PrintClientCard (sClient Client)
{
    cout << "\nThe following are the client details : \n";
    cout << "------------------------------";
    cout << "\nAccount Number : " << Client.AccountNumber ;
    cout << "\nPin Code : " << Client.PinCode ;
    cout << "\nName : " << Client.Name ;
    cout << "\nPhone : " << Client.Phone ;
    cout << "\nBalance : " << Client.AccountBalance ;
    cout << "\n------------------------------\n";
}
bool FindClientByAccountNumber (string AccountNumber , vector<sClient> vClients , sClient &Client)
{
    for (sClient C : vClients)
    {
        if (C.AccountNumber == AccountNumber )
        {
            Client = C ;
            return true ;
        }
    }
    return false ;
}
sClient ChangeClientRecord (string AccountNumber )
{
    sClient Client ;
    Client.AccountNumber = AccountNumber ;

    cout << "Enter PinCode ?" ;
    getline(cin >> ws , Client.PinCode);

    cout << "Enter Name ?";
    getline(cin , Client.Name);

    cout << "Enter Phone?";
    getline(cin , Client.Phone);

    cout << "Enter Balance?";
    cin >> Client.AccountBalance ;

    return Client ;
}
bool MarkClientForDeleteByAccountNumber (string AccountNumber ,vector<sClient> &vClients)
{
   for (sClient &C : vClients)
   {
    if (C.AccountNumber == AccountNumber)
    {
        C.MarkForDelete = true ;
        return true ;
    }
   }
   return false ;
}
vector<sClient> SaveClientDataToFile (string FileName , vector<sClient> vClients)
{
    fstream MyFile ;
    MyFile.open(FileName,ios::out);
    string Line ;
    if (MyFile.is_open())
    {
        for (sClient C : vClients)
        {
            if (C.MarkForDelete == false)  // we only write records that are not marked for delete.
            {
                Line = ConvertRecordToLine(C);
                MyFile << Line << endl;
            }
        }
        MyFile.close();
    }
    return vClients ;
}
void AddDataLineToFile (string FileName , string stDataLine )
{
    fstream MyFile ;
    MyFile.open(FileName,ios::out | ios::app);
    if(MyFile.is_open())
    {
        MyFile << stDataLine << endl;
        MyFile.close();
    }
}
void AddNewClient()
{
    sClient Client ;
    Client = ReadNewClient ();
    AddDataLineToFile("Clients.txt",ConvertRecordToLine(Client));
}
void AddNewClients ()
{
    char AddMore = 'Y';
    do
    {
        // system("cls");
        cout << "Adding New Client : \n\n";
        AddNewClient();
        cout << "\nClient Added Successfully , do you want to add more clients ? [Y,N] " ;
        cin >> AddMore ;
    } while (toupper(AddMore) == 'Y' );
}
bool DeleteClientByAccountNumber (string AccountNumber ,vector<sClient> &vClients)
{
    sClient Client ;
    char Answer = 'n';
    if (FindClientByAccountNumber(AccountNumber,vClients,Client))
    {
        PrintClientCard(Client);
        cout << "Are You Sure you want to delete this client ? ";
        cin >> Answer ;
        if (Answer == 'Y' || Answer == 'y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber,vClients);
            SaveClientDataToFile("Clients.txt",vClients);
             // Refresh Clients
            vClients = LoadClientDataFromFileToVector("Clients.txt");
            cout << "\n\nClient Deleted Successfully !" ;
            return true ;
        }
    }
    else 
    {
        cout << "Client with Account Number (" << AccountNumber << ") Is Not Found !";
        return false ;
    }
    return false ;
}
bool UpdateClientByAccountNumber (string AccountNumber , vector<sClient>&vClients)
{
    sClient Client ;
    char Answer = 'n';
    if (FindClientByAccountNumber(AccountNumber,vClients,Client))
    {
        PrintClientCard(Client);
        cout << "Are you sure to update this client ? [Y,N]";
        cin >> Answer ;
        if (Answer == 'Y' || Answer == 'y')
        {
            for (sClient &C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }
            }
            SaveClientDataToFile("Clients.txt",vClients);
            cout << "\n\nClient Updated Successfully !";
            return true ;
        }
    }
    else
    {
        cout << "Client with Account Number (" << AccountNumber << ") Is Not Found !" ;
        return false ;
    }
    return false ;
}
bool DepositeBalanceToClientByAccountNumber (string AccountNumber , double Amount , vector<sClient> &vClients)
{
    char Answer = 'n';
    cout << "Are you sure you want to perform this transaction ? [Y/N] ";
    cin >> Answer ;
    if (Answer == 'Y' || Answer == 'y')
    {
        for (sClient &C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += Amount ;
                SaveClientDataToFile("Clients.txt",vClients);
                cout << "\n\nDone Successfully. New Balance is : " << C.AccountBalance;
                return true ;
            }
        }
        return false ;
    }
    return false ;
}
string ReadClientAccountNumber ()
{
    string AccountNumber ;
    cout << "Please Enter Account Number ?" ;
    getline(cin >> ws, AccountNumber);
    return AccountNumber ;
}
short ReadTransactionsMenueOption()
{
    cout << "Choose what do you want to do? [1 to 4]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}
void ShowAllClientScreen ()
{
    sClient Client ;
    vector<sClient> vClients = LoadClientDataFromFileToVector("Clients.txt");
    cout << "\n\t\t\t\t\tClients List (" << vClients.size() << ")Client(s)";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << setw(15) << left << "AccountNumber" ;
    cout << "| " << setw(10) << left << "Pin Code" ;
    cout << "| " << setw(40) << left << "Client Name" ;
    cout << "| " << setw(12) << left << "Phone" ;
    cout << "| " << setw(12) << left << "Balance" ;
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    
    if (vClients.size() == 0)
    {
        cout << "\t\t\t\tNo Clients Available In The System !";
    }
    else
    for (sClient Client : vClients)
    {
        PrintClientRecordLine(Client);
        cout << endl;
    }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}
void ShowDeleteClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDelete Client Screen";
    cout << "\n-----------------------------------\n";
    vector<sClient> vClients = LoadClientDataFromFileToVector("Clients.txt");
    string AccountNumber = ReadClientAccountNumber();
    DeleteClientByAccountNumber(AccountNumber,vClients);
}
void ShowUpdateClientScreen ()
{
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate Client Screen";
    cout << "\n-----------------------------------\n";
    vector<sClient> vClients = LoadClientDataFromFileToVector("Clients.txt");
    string AccountNumber = ReadClientAccountNumber();
    UpdateClientByAccountNumber(AccountNumber,vClients);
}
void ShowAddNewClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tAdd New Clients Screen";
    cout << "\n-----------------------------------\n";
    AddNewClients();
}
void ShowFindClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tFind Client Screen";
    cout << "\n-----------------------------------\n";
    vector<sClient> vClients = LoadClientDataFromFileToVector("Clients.txt");
    sClient Client;
    string AccountNumber = ReadClientAccountNumber();
    if (FindClientByAccountNumber(AccountNumber,vClients,Client))
    PrintClientCard(Client);
    else
    cout << "\nClient with Account Number [" << AccountNumber << "] Is Not Found !" ;
}
void ShowDepositeScreen ()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDeposit Screen";
    cout << "\n-----------------------------------\n";
    sClient Client ;
    vector<sClient> vClients = LoadClientDataFromFileToVector("Clients.txt");
    string AccountNumber = ReadClientAccountNumber();
    while (!FindClientByAccountNumber(AccountNumber,vClients,Client))
    {
        cout << "Client with Account Number (" << AccountNumber << ") does not exist." << endl;
        AccountNumber = ReadClientAccountNumber();
    }
    PrintClientCard(Client);
    double Amount = 0 ;
    cout << "Please enter deposite amount ?";
    cin >> Amount ;
    DepositeBalanceToClientByAccountNumber(AccountNumber,Amount,vClients);
}
void ShowWithdrawScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tWithdraw Screen";
    cout << "\n-----------------------------------\n";
    sClient Client ;
    vector<sClient> vClients = LoadClientDataFromFileToVector("Clients.txt");
    string AccountNumber = ReadClientAccountNumber();
    while (!FindClientByAccountNumber(AccountNumber,vClients,Client))
    {
        cout << "Client with Account Number(" << AccountNumber << ") does not exist !";
        AccountNumber = ReadClientAccountNumber();
    }
    PrintClientCard(Client);
    double Amount = 0 ;
    cout << "Please enter withdraw amount ? ";
    cin >> Amount ;
    while (Amount > Client.AccountBalance)
    {
        cout << "\nAmount Exceeds the balance , you can withdraw up to : " << Client.AccountBalance << endl;
        cout << "Please enter another amount ? " ;
        cin >> Amount;
    } 
    DepositeBalanceToClientByAccountNumber(AccountNumber,Amount * -1 ,vClients);
}
void ShowTotalBalances ()
{
    vector<sClient> vClients = LoadClientDataFromFileToVector("Clients.txt");
    cout << "\n\t\t\t\t\tBalance List (" << vClients.size() << ")Clients(s).";
    cout <<"\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout <<"\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    double TotalBalances = 0 ;
    if (vClients.size() == 0)
    {
        cout << "\t\t\t\tNo Clients Available in The System !" ;
    }
    else
    {
        for (sClient C : vClients)
        {
            PrintClientRecordLine(C);
            TotalBalances += C.AccountBalance ;
            cout << endl;
        }
    cout <<"\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "\t\t\t\t\tTotal Balance = " << TotalBalances ;
    }
}
void ShowTotalBalancesScreen ()
{
   ShowTotalBalances();
}
enum enTransactionsMenuOption { eDeposite = 1 , eWithdraw = 2 , eShowTotalBalance = 3 , eShowMainMenu = 4};
void PerfromTransactionsMenuOption (enTransactionsMenuOption TransactionsMenuOption)
{
    switch (TransactionsMenuOption)
    {
    case enTransactionsMenuOption::eDeposite :
        ShowDepositeScreen();
        GoBackToTransactionsMenu();
        break;
    
    case enTransactionsMenuOption::eWithdraw :
        ShowWithdrawScreen();
        GoBackToTransactionsMenu();
        break;
    case enTransactionsMenuOption::eShowTotalBalance :
        ShowTotalBalancesScreen();
        GoBackToTransactionsMenu();
        break;
    case enTransactionsMenuOption::eShowMainMenu :
        ShowMainMenu();
        break;
    }
}
void ShowEndScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tProgram Ends :-)";
    cout << "\n-----------------------------------\n";
}
enum enMainMenuOption 
{
    eListClient = 1 , eAddNewClient = 2 ,
    eDeleteClient = 3 , eUpdateClient = 4 ,
    eFindClient = 5 , eShowTransactionsMenu = 6 ,   eExit = 7 
};
void GoBackToMainMenu ()
{
    cout << "\n\nPress any key to go back to Main Menu....";
    system("pause>0");
    ShowMainMenu();
}
short ReadMainMenuOption()
{
    short Choise ;
    cout << "Choose what do you want to do ? [1 to 7] ";
    cin >> Choise ;
    return Choise ;
}
void PerformMainMenuOption (enMainMenuOption MainMenuOption)
{
    switch (MainMenuOption)
    {
    case enMainMenuOption::eListClient :
        system("cls");
        ShowAllClientScreen();
        GoBackToMainMenu();
        break;
    
    case enMainMenuOption::eAddNewClient :
        system("cls");
        ShowAddNewClientScreen();
        GoBackToMainMenu();
        break;
    case enMainMenuOption::eDeleteClient :
        system("cls");
        ShowDeleteClientScreen();
        GoBackToMainMenu();
        break;
    case enMainMenuOption::eUpdateClient :
        system("cls");
        ShowUpdateClientScreen();
        GoBackToMainMenu();
        break;
    case enMainMenuOption::eFindClient :
        system("cls");
        ShowFindClientScreen();
        GoBackToMainMenu();
        break;
    case enMainMenuOption::eShowTransactionsMenu :
        system("cls");
        ShowTransactionsMenu();
        break;
    case enMainMenuOption::eExit :
        system("cls");
        ShowEndScreen();
        GoBackToMainMenu();
        break;
    }
}
void ShowTransactionsMenu()
{
    system("cls");
    cout << "===============================================" << endl;
    cout << "\t\tTransactions Menu Screen " << endl;
    cout << "===============================================" << endl;
    cout << "\t[1] Deposite." << endl;
    cout << "\t[2] Withdraw." << endl;
    cout << "\t[3] Total Balances." << endl;
    cout << "\t[4] Main Menu." << endl;
    cout << "===============================================" << endl;
    PerfromTransactionsMenuOption((enTransactionsMenuOption)ReadTransactionsMenueOption());
}
void GoBackToTransactionsMenu ()
{
    cout << "\n\nPress any key to go back to Main Menu....";
    system("pause>0");
    ShowTransactionsMenu();
}
void ShowMainMenu()
{
    system("cls");
    cout << "===============================================" << endl;
    cout << "\t\t Main Menu Screen " << endl;
    cout << "===============================================" << endl;
    cout << "\t[1] Show Client List. " << endl;
    cout << "\t[2] Add New Client." << endl;
    cout << "\t[3] Delete Client." << endl;
    cout << "\t[4] Update Client Info." << endl;
    cout << "\t[5] Find Client. " << endl;
    cout << "\t[6] Transactions. " << endl;
    cout << "\t[7] Exit. " << endl;
    cout << "===============================================" << endl;
    PerformMainMenuOption((enMainMenuOption)ReadMainMenuOption());
}
int main()
{
   ShowMainMenu();
   system("pause>0");
    return 0;
}
