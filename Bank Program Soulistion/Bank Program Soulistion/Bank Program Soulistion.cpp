#include <iostream>
#include<string>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;

const string FileName = "MyFile.txt";

void ShowMainMenue();// function declaration

void showTransctionsMenueScreen(); // function declaration

struct sClient
{
	string AcountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AcountBalance;
	bool MarkClient = false;
};

vector <string> SplitClient(string S1, string Delim )
{
	vector <string> vString;
	string sWord;
	short pos;
	while ((pos = S1.find(Delim)) != std::string::npos)
	{
		sWord = S1.substr(0, pos);
		if (sWord != " ")
		{
			vString.push_back(sWord);
		}
		S1.erase(0, pos + Delim.length());
	}
	if (S1 != " ")
	{
		vString.push_back(S1);
	}
	return vString;
}

sClient ConvertLineToRecord(string Line, string Operater = "#//#")
{
	sClient Client;
	vector<string> vString;
	vString = SplitClient(Line, Operater);
	Client.AcountNumber = vString[0];
	Client.PinCode = vString[1];
	Client.Name = vString[2];
	Client.Phone = vString[3];
	Client.AcountBalance = stod(vString[4]);
	return Client;
}

string ConvertRecordToLine(sClient Client ,string Operater = "#//#")
{
	string ConvertLine;
	ConvertLine += Client.AcountNumber + Operater;
	ConvertLine += Client.PinCode + Operater;
	ConvertLine += Client.Name + Operater;
	ConvertLine += Client.Phone + Operater;
	ConvertLine += to_string(Client.AcountBalance);
	return ConvertLine;
}

bool ClientExistsByAccountNumber(string AcountNumber, string FileName)
{
	vector <sClient> vClient;
	fstream MyFile;
	MyFile.open(FileName, ios::in);
	if (MyFile.is_open())
	{
		string Line;
		sClient Client;
		while (getline(MyFile, Line))
		{
			Client = ConvertLineToRecord(Line);
			if (Client.AcountNumber == AcountNumber)
			{
				MyFile.close();
				return true;
			}
			vClient.push_back(Client);
		}
		MyFile.close();
	}
	return false;
}

sClient ReadNewClient()
{
	sClient Client;
	cout << "\n====================================================\n";
	cout << "\n Enter Acount Number : ";
	getline(cin >> ws, Client.AcountNumber);
	while (ClientExistsByAccountNumber(Client.AcountNumber, FileName))
	{
		cout << "\nClient with [" << Client.AcountNumber << "] already exists, Enter another Account Number? ";     
		getline(cin >> ws, Client.AcountNumber);
	}
	cout << "\n Enter Pin Code : ";
	getline(cin, Client.PinCode);
	cout << " \n Enter Name : ";
	getline(cin, Client.Name);
	cout << "\n Enter Phone : ";
	getline(cin, Client.Phone);
	cout << "\n Enter Acount Balance : ";
	cin >> Client.AcountBalance;
	cout << "\n====================================================\n";
	return Client;
}

vector <sClient> LoadCleintsDataFromFile(string FileName)
{
	vector<sClient> vClient;
	fstream MyFile;
	MyFile.open(FileName, ios::in);
	if (MyFile.is_open())
	{
		sClient Client;
		string Line;
		while (getline(MyFile, Line))
		{
			Client = ConvertLineToRecord(Line);
			vClient.push_back(Client);
		}
		MyFile.close();
	}
	return vClient;
}

void ShowMenu(sClient Client)
{
	cout <<"|"<<setw(20) << left << Client.AcountNumber;
	cout <<"|"<< setw(16) << left << Client.PinCode;
	cout<<"|"<<setw(26) << left << Client.Name;
	cout<<"|"<< setw(20) << left << Client.Phone;
	cout<<"|"<< setw(24) << left << Client.AcountBalance;
	
}

int TotalBalnce()
{
	int Sum = 0;
	vector<sClient> vClients = LoadCleintsDataFromFile(FileName);
	for (sClient C : vClients)
	{
		Sum += C.AcountBalance;
	}
	return Sum;
}

void ShowMainMenu(sClient Client)
{
	cout << "|" << setw(30) << left << Client.AcountNumber;
	cout << "|" << setw(40) << left << Client.Name;
	cout << "|" << setw(30) << left << Client.AcountBalance;

}

void ShowAllClientsScreen()
{
	vector<sClient> vClients = LoadCleintsDataFromFile(FileName);
	cout << "\n\t\t\t\t\t Client List (" << vClients.size() << ") Client(s)";
	cout << "\n\n-------------------------------------------------------------";
	cout << "--------------------------------------------\n";
	cout << "|" << setw(20) << left << "Acount Number";
	cout << "|" << setw(16) << left << "Pin Code";
	cout << "|" << setw(26) << left << "Name";
	cout << "|" << setw(20) << left << "Phone";
	cout << "|" << setw(24) << left << "Acount Bamance";
	cout << "\n-------------------------------------------------------------";
	cout << "--------------------------------------------\n";
	if (vClients.size() == 0)     
		cout << "\t\t\t\tNo Clients Available In the System!"; 
	else
	for (sClient Client : vClients)
	{
		ShowMenu(Client);
		cout << endl<<endl;
	}
	cout << "\n-------------------------------------------------------------";
	cout << "--------------------------------------------\n";
}

void ShowAllClientsScreenMainMenue()
{
	vector<sClient> vClients = LoadCleintsDataFromFile(FileName);
	cout << "\n\t\t\t\t\t Client List (" << vClients.size() << ") Client(s)";
	cout << "\n\n-------------------------------------------------------------";
	cout << "--------------------------------------------\n";
	cout << "|" << setw(30) << left << "Acount Number";
	
	cout << "|" << setw(40) << left << "Client Name";
	
	cout << "|" << setw(30) << left << " Balance";
	cout << "\n-------------------------------------------------------------";
	cout << "--------------------------------------------\n";
	if (vClients.size() == 0)
		cout << "\t\t\t\tNo Clients Available In the System!";
	else
		for (sClient Client : vClients)
		{
			ShowMainMenu(Client);
			cout << endl << endl;
		}
	cout << "\n-------------------------------------------------------------";
	cout << "--------------------------------------------\n";
	cout << "\n\t\t\t\t Totale Balance : " << TotalBalnce();
}

void AddClient(string NFile , string DataLine)
{
	fstream MyFile;
	MyFile.open(NFile, ios::out | ios::app);
	if (MyFile.is_open())
	{
		MyFile << DataLine << endl;
		MyFile.close();
	}
}

void AddNewClient()
{
	sClient Client;
	Client = ReadNewClient();
	AddClient(FileName, ConvertRecordToLine(Client));
}

void PrintClientInFile()
{
	char Answer = 'n';
	do
	{
		cout << "\n====================";
		cout << "\n Record Client      |";
		AddNewClient();
		cout << "\n Client added Successfully , Do you want to add more clients : (y/n) ? ";
		cin >> Answer;
	} while (Answer == 'y' || Answer == 'Y');
}

void ShowAddNewClientsScreen()
{
	system("cls");
	cout << "\n\t\t --------------------------";
	cout << "\n\t\t    Add a new client ";
	cout << "\n\t\t --------------------------\n";
	PrintClientInFile();
}

string ReadAcountNumber()
{
	string AcountNumber;
	cout << "\n Please enter Acount number : ";
	cin >> AcountNumber;
	return AcountNumber;
}

void PrintAcountClient(sClient Client)
{
	cout <<"\n\nThe following are the client details : \n";   
	cout <<"------------------------------------ ";  
	cout <<"\nAccout Number : "<<Client.AcountNumber;  
	cout <<"\nPin Code : "<<Client.PinCode;   
	cout <<"\nName : "<<Client.Name;   
	cout <<"\nPhone : "<<Client.Phone;   
	cout <<"\nAccount Balance : "<<Client.AcountBalance;   
	cout <<"\n------------------------------------ \n";
}

bool FindAcountNumberFromRecordClient(string AcountNumber, vector<sClient> vClient, sClient &Client)
{
	for (sClient C : vClient)
	{
		if (C.AcountNumber == AcountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}

bool MarkAcountClient(string AcountNumber, vector <sClient> &vClient)
{
	for (sClient &C : vClient)
	{
		if (C.AcountNumber == AcountNumber)
		{
			C.MarkClient = true;
			return true;
		}
	}
	return false;
}

vector<sClient> SaveCleintsDataToFile(string FileName, vector<sClient>vClient)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);
	string DateLine;
	if (MyFile.is_open())
	{
		for (sClient C : vClient)
		{
			if (C.MarkClient == false)
			{
				DateLine = ConvertRecordToLine(C);
				MyFile << DateLine << endl;
			}
		}
		MyFile.close();
	}
	return vClient;
}

bool DeleteClientFromFile(string AcountNumber, vector<sClient>& vClient)
{
	sClient Client;
	char Answer = 'n';
	if (FindAcountNumberFromRecordClient(AcountNumber, vClient, Client))
	{
		PrintAcountClient(Client);
		cout << "\n Are you sure do you want delete this acount client : (y/n) ? ";
		cin >> Answer;
		if (/*tolower */ (Answer) == 'Y' || Answer=='y')
		{
			MarkAcountClient(AcountNumber , vClient);
			SaveCleintsDataToFile(FileName, vClient);
			vClient = LoadCleintsDataFromFile(FileName);
			cout << "\n Client is delete \n";
			return true;
		}
	}
	else
	{

			cout << "\nClient with Account Number (" << AcountNumber << ") is Not Found!";
			return false;
	}
}

sClient UpDateClient(string AcountNumber)
{
	sClient Client;
	cout << "\n Reacord New Client \n";
	Client.AcountNumber = AcountNumber;
	cout << "\n Enter Pin Code : ";
	getline(cin>>ws, Client.PinCode);
	cout << " \n Enter Name : ";
	getline(cin, Client.Name);
	cout << "\n Enter Phone : ";
	getline(cin, Client.Phone);
	cout << "\n Enter Acount Balance : ";
	cin >> Client.AcountBalance;
	return Client;
}

bool UpdateClientFromFile(string AcountNumber, vector<sClient>& vClient)
{
	sClient Client;
	char Answer = 'n';
	if (FindAcountNumberFromRecordClient(AcountNumber, vClient, Client))
	{
		PrintAcountClient(Client);
		cout << "\n Are you sure do you want Update this acount client : (y/n) ? ";
		cin >> Answer;
		if ((Answer) == 'Y'|| Answer=='y')
		{
	    	for (sClient& C : vClient)
			{
				if (C.AcountNumber == AcountNumber)
				{
					C = UpDateClient(AcountNumber);
					break;
				}
			}
		
		  SaveCleintsDataToFile(FileName, vClient);
			//vClient = LoadCleintsDataFromFile(FileName);
			cout << "\n Client is Update \n";
			return true;
		}
	}
	else
	{

		cout << "\nClient with Account Number (" << AcountNumber << ") is Not Found!";
		return false;
	}
}

void ShowDeleteClientScreen()
{
	cout << "\n-----------------------------------\n"; 
	cout << "\tDelete Client Screen";  
	cout << "\n-----------------------------------\n";
	vector<sClient> vClient = LoadCleintsDataFromFile(FileName);
	string AcountNumber = ReadAcountNumber();
	DeleteClientFromFile(AcountNumber, vClient);
}

void ShowUpdateClientScreen()
{
	cout << "\n-----------------------------------\n";  
	cout << "\tUpdate Client Info Screen";  
	cout << "\n-----------------------------------\n";
	vector<sClient> vClient = LoadCleintsDataFromFile(FileName);
	string AcountNumber = ReadAcountNumber();
	UpdateClientFromFile(AcountNumber, vClient);
}

void ShowFindClientScreen()
{
	cout << "\n-----------------------------------\n";  
	cout << "\tFind Client Screen"; 
	cout << "\n-----------------------------------\n"; 
	vector <sClient> vClients = LoadCleintsDataFromFile(FileName);
	sClient Client;
	string AccountNumber = ReadAcountNumber();
	if (FindAcountNumberFromRecordClient(AccountNumber, vClients, Client))  
		PrintAcountClient(Client);
	else
	{
		cout << "\nClient with Account Number[" << AccountNumber << "] is not found!";
	}

}

void ShowEndScreen()
{ 
	cout << "\n-----------------------------------\n";  
	cout << "\tProgram Ends :-)";   
	cout << "\n-----------------------------------\n";
}

short ReadHowDepositAcountPalnse()
{
	short HowToDeposit = 0;
	cout << "\nPlease enter  depsit amount : ";
	cin >> HowToDeposit;
	return HowToDeposit;
}

bool AreYouExsist()
{
	char answer = 'n';
	cout << "\n Are you sure do you want perform this transaction : (y/n) ? ";
	cin >> answer;
	if (answer == 'y' || answer == 'Y')
	{
		return true;
	}
	else
		return false;
}

void Exist(string AcountNumber , vector<sClient>vClient , short Bosit)
{
	double AddAcountBalnce = 0;
	for (sClient& C : vClient)
	{
		if (C.AcountNumber == AcountNumber)
		{
			if (AreYouExsist())
			{
				C.AcountBalance = C.AcountBalance + (Bosit);
				cout << "\n Your acount balnce now are : " << C.AcountBalance;
			}
		}
		SaveCleintsDataToFile(FileName, vClient);
	}

}

void Exist2(string AcountNumber, vector<sClient>vClient, short Bosit)
{
	double AddAcountBalnce = 0;
	for (sClient &C : vClient)
	{
		if (C.AcountNumber == AcountNumber)
		{
			while (C.AcountBalance < Bosit)
			{
				cout << "\n Amount Exceeds the balance , you can withdraw up to : " << C.AcountBalance;
				cout << "\n Please enter another amount : ";
				cin >> Bosit;
			}
			if (AreYouExsist())
			{
				
				C.AcountBalance = C.AcountBalance - (Bosit);
				cout << "\n Your acount balnce now are : " << C.AcountBalance;
			}
		}
		SaveCleintsDataToFile(FileName, vClient);
	}

}

void ExistAcountNumber()
{
	vector <sClient> vClients = LoadCleintsDataFromFile(FileName);
	sClient Client;
	string AccountNumber = ReadAcountNumber();
	while (FindAcountNumberFromRecordClient(AccountNumber, vClients, Client) == false)
	{
		cout << "\nClient with Account Number[" << AccountNumber << "] is not exist !";
		cout << "\n Please enter acount number : ";
		getline(cin >> ws, AccountNumber);
	}
	PrintAcountClient(Client);
	short AddBosit = ReadHowDepositAcountPalnse();
	Exist(AccountNumber, vClients, AddBosit);
	vClients = LoadCleintsDataFromFile(FileName);
	

}

void GoBackToMainMenue()
{ 
      cout << "\n\nPress any key to go back to Main Menue...";  
      system("pause>0");    
      ShowMainMenue();
}

void GoBackToMainMenue2()
{
	cout << "\n\nPress any key to go back to Main Menue...";
	system("pause>0");
	showTransctionsMenueScreen();
}

void showDeposit()
{
	cout << "\n\t -----------------------------------\n";
	cout << " \t\t Deposit Screen";
	cout << "\n\t -----------------------------------\n";
	ExistAcountNumber();
}

void drawWithAcountBalnce()
{
	vector <sClient> vClients = LoadCleintsDataFromFile(FileName);
	sClient Client;
	string AccountNumber = ReadAcountNumber();
	while (FindAcountNumberFromRecordClient(AccountNumber, vClients, Client) == false)
	{
		cout << "\nClient with Account Number[" << AccountNumber << "] is not exist !";
		cout << "\n Please enter acount number : ";
		getline(cin >> ws, AccountNumber);
	}
	PrintAcountClient(Client);
	short AddBosit = ReadHowDepositAcountPalnse();
    Exist2(AccountNumber, vClients, AddBosit);
	vClients = LoadCleintsDataFromFile(FileName);
}

void ShowWithDraw()
{
	cout << "\n\t -----------------------------------\n";
	cout << " \t\t Deposit Screen";
	cout << "\n\t -----------------------------------\n";
	drawWithAcountBalnce();
}

short ReadTransactionOption()
{
	cout << "\nChoose what do you want to do? [1 to 4]? ";
	short Choice = 0;
	cin >> Choice;
	return Choice;
}

enum enTransactionsMenueScreen
{
	eDeposit = 1 , eWithdraw=2, eTotalBalance = 3, eMainMenue = 4
};

void PerfromTransactionMenueOption(enTransactionsMenueScreen TransactionMenue)
{
	switch (TransactionMenue)
	{
	case (enTransactionsMenueScreen::eDeposit):

		system("cls");
		showDeposit();
		GoBackToMainMenue2();
		break;

	case (enTransactionsMenueScreen::eWithdraw):
		system("cls");
		ShowWithDraw();
		GoBackToMainMenue2();
		break;
	case(enTransactionsMenueScreen::eTotalBalance):
		system("cls");
		ShowAllClientsScreenMainMenue();
		GoBackToMainMenue2();
		break;
	case(enTransactionsMenueScreen::eMainMenue):
		system("cls");
		ShowMainMenue();
	}
}

void showTransctionsMenueScreen()
{
	system("cls");
	cout << "\n===============================================";
	cout << "\n\t\t Transactions Menue Screen ";
	cout << "\n===============================================\n";

	cout << "\n\t\t [1] Deposit .";
	cout << "\n\t\t [2] Withdraw .";
	cout << "\n\t\t [3] Totale Balances .";
	cout << "\n\t\t [4] Main Menue .\n";

	cout << "\n===============================================";

	PerfromTransactionMenueOption((enTransactionsMenueScreen)ReadTransactionOption());
}

enum enMainMenueOptions   // Waht the chosse
{
	eListClients = 1, eAddNewClient = 2, eDeleteClient = 3, eUpdateClient = 4, eFindClient = 5, eTransactions = 6, eExit = 7
};    

short ReadMainMenueOption()  // Read our chosse
{
	cout << "\nChoose what do you want to do? [1 to 7]? ";
	short Choice = 0;
	cin >> Choice;
	return Choice;
} 

void PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
{
	switch (MainMenueOption)
	{
	case (enMainMenueOptions::eListClients):
		
		system("cls");
		ShowAllClientsScreen();
		GoBackToMainMenue();
		break;
		
	case(enMainMenueOptions::eAddNewClient):
	    
		system("cls");
		ShowAddNewClientsScreen(); 
		GoBackToMainMenue(); 
		break;
	    
	case(enMainMenueOptions::eDeleteClient):  

		system("cls");   
		ShowDeleteClientScreen();  
		GoBackToMainMenue(); 
		break;

	case(enMainMenueOptions::eUpdateClient):

		system("cls");  
		ShowUpdateClientScreen();  
		GoBackToMainMenue();
		break; 

	case(enMainMenueOptions::eFindClient):

		system("cls"); 
		ShowFindClientScreen();   
		GoBackToMainMenue(); 
		break;
     
	case(enMainMenueOptions::eTransactions):

		system("cls");
		showTransctionsMenueScreen();
		break;
	case(enMainMenueOptions::eExit):

		system("cls");   
		ShowEndScreen();
		break;
	}
}

void ShowMainMenue()
{
	    system("cls");
	    cout << "\n===============================================";
		cout << "\n\t\t Main Menue Screen ";
		cout << "\n===============================================";
	
		cout << "\n\t\t [1] Show Client List .";
		cout << "\n\t\t [2] Add New Client .";
		cout << "\n\t\t [3] Delete Client .";
		cout << "\n\t\t [4] Update Client Info .";
		cout << "\n\t\t [5] Find Client .";
		cout << "\n\t\t [6] Transactions .";
		cout << "\n\t\t [7] Exit .";
	
		cout << "\n===============================================";

		PerfromMainMenueOption((enMainMenueOptions)ReadMainMenueOption());
}      // show List Menue

int main()
{
	ShowMainMenue();
	system("pause>0");
	return 0;
}

