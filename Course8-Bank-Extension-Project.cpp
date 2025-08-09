#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;
const string clientsFilePath = "Clients.txt";
const string usersFilePath = "UsersC8.txt";
const string delim = "#//#";


struct stClient
{
	string accountNumber, pinCode, name, phone;
	double accountBalance = 0.0;
	bool markForDelete = false;
};

struct stUser
{
	string username, password;
	short permission;
};

struct sPermission
{
	short listUsers = 1;	// 0.0.0.0.1
	short addUser = 2;		// 0.0.0.1.0  
	short deleteUser = 4;	// 0.0.1.0.0
	short updateUser = 8;	// 0.1.0.0.0
	short findUser = 16;	// 1.0.0.0.0

};

enum enMainMenu
{
	showClient = 1,
	addNewClient = 2,
	deleteClient = 3,
	updateClient = 4,
	findClient = 5,
	transactions = 6,
	manageUsers = 7,
	logout = 8
};

enum enTransactionMenu
{
	deposit = 1,
	withdraw = 2,
	totalBalances = 3,
	mainMenu = 4
};

enum enManageMenu
{
	listUsers = 1,
	addUser = 2,
	deleteUser = 3,
	updateUser = 4,
	findUser = 5,
	returnMainMenu = 6
};

//decalring some functions.
void startProgram();
void selectTransactionMenu(enTransactionMenu choice, vector<stClient>& vClient);
void depositScreen(vector <stClient>& vClient);
void withdrawScreen(vector <stClient>& vClient);
void totalBalance(vector <stClient>& vClient);
void loginScreen();

string readAccountNumber()
{
	string accountNum;
	cout << "\nPlease Enter the Account Number: ";
	cin >> ws >> accountNum;

	return accountNum;
}

enMainMenu readUserChoice()
{
	short num;
	cout << "Choose What Do You Want to Do? [1 to 8]? ";
	do
	{
		cin >> ws >> num;
		if (num < 1 || num > 8)
		{
			cout << "\nSorry wrong input please enter a number between 1 to 8: ";
		}

	} while (num < 1 || num > 8);

	return enMainMenu(num);
}

enTransactionMenu readTransactionChoice()
{
	short num;
	cout << "Choose What Do You Want to Do? [1 to 4]? ";
	do
	{
		cin >> ws >> num;
		if (num < 1 || num > 4)
		{
			cout << "\nSorry wrong input please enter a number between 1 to 4: ";
		}

	} while (num < 1 || num > 4);

	return enTransactionMenu(num);
}

vector <string> splitString(string line)
{
	string word;
	vector <string> vString;
	short pos = 0;

	while ((pos = line.find(delim)) != std::string::npos)
	{
		word = line.substr(0, pos);

		if (word != "")
			vString.push_back(word);

		line.erase(0, pos + delim.length());
	}

	if (line != "")
		vString.push_back(line);

	return vString;
}

stClient assignClientsData(const vector <string>& vString)
{
	stClient client;

	client.accountNumber = vString[0];
	client.pinCode = vString[1];
	client.name = vString[2];
	client.phone = vString[3];
	client.accountBalance = stod(vString[4]);

	return client;
}

stUser assignUsersData(const vector <string>& vString)
{
	stUser user;

	user.username = vString[0];
	user.password = vString[1];
	return user;
}

string convertDataToLine(stClient client)
{
	string line = "";

	line += client.accountNumber + delim;
	line += client.pinCode + delim;
	line += client.name + delim;
	line += client.phone + delim;
	line += to_string(client.accountBalance);

	return line;
}

vector <stClient> readClientsInFile()
{
	fstream myFile;
	vector <string> vString;
	vector <stClient> vClient;
	stClient client;

	myFile.open(clientsFilePath, ios::in);

	if (myFile.is_open())
	{
		string line;

		while (getline(myFile, line))
		{
			vString = splitString(line);
			client = assignClientsData(vString);
			vClient.push_back(client);
		}

		myFile.close();
	}

	return vClient;
}

vector <stUser> readUsersInFIle()
{
	fstream myFile;
	vector <string> vS1;
	vector <stUser> vUser;
	stUser user;

	myFile.open(usersFilePath, ios::in);

	if (myFile.is_open())
	{
		string line;

		while (getline(myFile, line));
		{
			vS1 = splitString(line);
			user = assignUsersData(vS1);
			vUser.push_back(user);
		}

		myFile.close();
	}

	return vUser;
}

void writeClientsInFile(vector <stClient>& vClient)
{
	fstream myFile;

	myFile.open(clientsFilePath, ios::out);

	if (myFile.is_open())
	{
		string line;

		for (stClient& c : vClient)
		{
			if (c.markForDelete == false)
			{
				line = convertDataToLine(c);
				myFile << line << endl;
			}
		}

		myFile.close();
	}
}

stClient getClient(vector <stClient>& vClient, string accountNum)
{
	stClient client;

	for (stClient& c : vClient)
	{
		if (c.accountNumber == accountNum)
			client = c;
	}

	return client;
}

bool FoundClient(vector <stClient>& vClient, string accountNum)
{
	for (stClient& c : vClient)
	{
		if (c.accountNumber == accountNum)
		{
			return true;
		}
	}
	return false;
}

void markForDeletion(vector <stClient>& vClient)
{
	string accountNum;
	stClient client;

	short clientNumber = vClient.size();

	cout << "\n\t\t\t\t Client List (" << clientNumber << ") Client(s).\n";
	cout << "\n___________________________________________________________________________________________\n";
	cout << "\n| Account Number | Pin Code\t| Client Name\t\t\t| Phone\t\t| Balance\n";
	cout << "\n___________________________________________________________________________________________\n";
	for (short i = 0; i < clientNumber; i++)
	{
		cout << "\n| " << vClient[i].accountNumber << "\t\t | " << vClient[i].pinCode << "\t\t| " << left << setw(20) << vClient[i].name << "\t\t| " << vClient[i].phone << "\t| " << fixed << vClient[i].accountBalance;
	}
	cout << "\n___________________________________________________________________________________________\n";


	cout << "\n-----------------------------------";
	cout << "\n\tDelete Client Screen";
	cout << "\n-----------------------------------\n";

	accountNum = readAccountNumber();

	while (!FoundClient(vClient, accountNum))
	{
		cout << "\nClient with [" << accountNum << "] Not Found! , Enter another Account Number: ";
		cin >> accountNum;
	}

	client = getClient(vClient, accountNum);
	cout << "\nThe following are the client details:";
	cout << "\n-----------------------------------\n";

	cout << left << setw(19) << "\nAccount Number" << right << ": " << client.accountNumber;
	cout << left << setw(19) << "\nPin Code" << right << ": " << client.pinCode;
	cout << left << setw(19) << "\nClient Name" << right << ": " << client.name;
	cout << left << setw(19) << "\nPhone" << right << ": " << client.phone;
	cout << left << setw(19) << "\nAccount Balance" << right << ": " << fixed << client.accountBalance << endl;
	cout << "\n-----------------------------------\n";


	char deleteAcc = 'n';
	cout << "\n\nAre you sure you want to delete this client y/n: ";
	cin >> deleteAcc;

	if (tolower(deleteAcc) == 'y')
	{
		for (stClient& c : vClient)
		{
			if (c.accountNumber == accountNum)
			{
				c.markForDelete = true;
			}
		}
		writeClientsInFile(vClient);
		cout << "\n\nClient deleted successfuly.";
		cout << "\n\nPress any key to go back to main menu...";
		system("pause>0");
		system("cls");
		startProgram();
	}
	else
	{
		cout << "\n\nPress any key to go back to main menu...";
		system("pause>0");
		system("cls");
		startProgram();
	}
}

void findClientScreen(vector <stClient>& vClient)
{
	string accountNum;
	stClient client;

	short clientNumber = vClient.size();

	cout << "\n\t\t\t\t Client List (" << clientNumber << ") Client(s).\n";
	cout << "\n___________________________________________________________________________________________\n";
	cout << "\n| Account Number | Pin Code\t| Client Name\t\t\t| Phone\t\t| Balance\n";
	cout << "\n___________________________________________________________________________________________\n";
	for (short i = 0; i < clientNumber; i++)
	{
		cout << "\n| " << vClient[i].accountNumber << "\t\t | " << vClient[i].pinCode << "\t\t| " << left << setw(20) << vClient[i].name << "\t\t| " << vClient[i].phone << "\t| " << fixed << vClient[i].accountBalance;
	}
	cout << "\n___________________________________________________________________________________________\n";

	cout << "\n-----------------------------------";
	cout << "\n\tFind Client Screen";
	cout << "\n-----------------------------------\n";
	accountNum = readAccountNumber();

	while (!FoundClient(vClient, accountNum))
	{
		cout << "\nClient with [" << accountNum << "] Not Found! , Enter another Account Number: ";
		cin >> accountNum;
	}

	client = getClient(vClient, accountNum);
	cout << "\nThe following are the client details:";
	cout << "\n-----------------------------------\n";

	cout << left << setw(19) << "\nAccount Number" << right << ": " << client.accountNumber;
	cout << left << setw(19) << "\nPin Code" << right << ": " << client.pinCode;
	cout << left << setw(19) << "\nClient Name" << right << ": " << client.name;
	cout << left << setw(19) << "\nPhone" << right << ": " << client.phone;
	cout << left << setw(19) << "\nAccount Balance" << right << ": " << fixed << client.accountBalance << endl;
	cout << "\n-----------------------------------\n";
	cout << "\n\nPress any key to go back to main menu...";
	system("pause>0");
	system("cls");
	startProgram();
}

void updateClientFunc(vector <stClient>& vClient)
{
	string accountNum;
	stClient client;

	short clientNumber = vClient.size();

	cout << "\n\t\t\t\t Client List (" << clientNumber << ") Client(s).\n";
	cout << "\n___________________________________________________________________________________________\n";
	cout << "\n| Account Number | Pin Code\t| Client Name\t\t\t| Phone\t\t| Balance\n";
	cout << "\n___________________________________________________________________________________________\n";
	for (short i = 0; i < clientNumber; i++)
	{
		cout << "\n| " << vClient[i].accountNumber << "\t\t | " << vClient[i].pinCode << "\t\t| " << left << setw(20) << vClient[i].name << "\t\t| " << vClient[i].phone << "\t| " << fixed << vClient[i].accountBalance;
	}
	cout << "\n___________________________________________________________________________________________\n";


	cout << "\n-----------------------------------";
	cout << "\n    Update Client Info Screen";
	cout << "\n-----------------------------------\n";

	accountNum = readAccountNumber();

	while (!FoundClient(vClient, accountNum))
	{
		cout << "\nClient with [" << accountNum << "] Not Found! , Enter another Account Number: ";
		cin >> accountNum;
	}

	client = getClient(vClient, accountNum);
	cout << "\nThe following are the client details:";
	cout << "\n-----------------------------------\n";

	cout << left << setw(19) << "\nAccount Number" << right << ": " << client.accountNumber;
	cout << left << setw(19) << "\nPin Code" << right << ": " << client.pinCode;
	cout << left << setw(19) << "\nClient Name" << right << ": " << client.name;
	cout << left << setw(19) << "\nPhone" << right << ": " << client.phone;
	cout << left << setw(19) << "\nAccount Balance" << right << ": " << fixed << client.accountBalance << endl;
	cout << "\n-----------------------------------\n";

	char updateAcc = 'n';
	cout << "\n\nAre you sure you want to update this client y/n: ";
	cin >> updateAcc;

	if (tolower(updateAcc) == 'y')
	{
		for (stClient& c : vClient)
		{
			if (c.accountNumber == accountNum)
			{
				cout << "\nEnter Pin Code: ";
				getline(cin >> ws, c.pinCode);

				cout << "Enter Name: ";
				getline(cin, c.name);

				cout << "Enter Phone: ";
				getline(cin, c.phone);

				cout << "Enter Account Balance: ";
				cin >> ws >> c.accountBalance;

				break;
			}
		}

		writeClientsInFile(vClient);
		cout << "\n\nClient Updated Successfuly.";

		cout << "\n\nPress any key to go back to main menu...";
		system("pause>0");
		system("cls");
		startProgram();
	}
	else
	{
		cout << "\n\nPress any key to go back to main menu...";
		system("pause>0");
		system("cls");
		startProgram();
	}

}

void printTransactionsScreen(vector <stClient>& vClient)
{
	enTransactionMenu menuChoice;

	cout << "\n===========================================\n";
	cout << "\t\tTransactions Menu Screen";
	cout << "\n===========================================\n";
	cout << "\t[1] Deposit.";
	cout << "\n\t[2] Withdraw.";
	cout << "\n\t[3] Total Balances.";
	cout << "\n\t[4] Main Menu.";
	cout << "\n===========================================\n";

	menuChoice = readTransactionChoice();
	selectTransactionMenu(menuChoice, vClient);
}

void selectTransactionMenu(enTransactionMenu choice, vector <stClient>& vClient) //declared above
{
	switch (choice)
	{
	case deposit:
		system("cls");
		depositScreen(vClient);
		break;

	case withdraw:
		system("cls");
		withdrawScreen(vClient);
		break;

	case totalBalances:
		system("cls");
		totalBalance(vClient);
		break;

	default:
		system("cls");
		startProgram();
		break;
	}
}

double calculateTotalBalances(vector <stClient>& vClient)
{
	double total = 0.0;

	for (stClient& c : vClient)
	{
		if (!c.markForDelete)
		{
			total += c.accountBalance;
		}
	}

	return total;
}

void depositScreen(vector <stClient>& vClient) //declared above
{
	string accountNum;
	stClient client;
	double depositAmount = 0.0;

	cout << "\n-----------------------------------";
	cout << "\n          Deposit Screen";
	cout << "\n-----------------------------------\n";

	accountNum = readAccountNumber();

	while (!FoundClient(vClient, accountNum))
	{
		cout << "\nClient with [" << accountNum << "] Not Found! , Enter another Account Number: ";
		cin >> accountNum;
	}

	client = getClient(vClient, accountNum);
	cout << "\nThe following are the client details:";
	cout << "\n-----------------------------------\n";

	cout << left << setw(19) << "\nAccount Number" << right << ": " << client.accountNumber;
	cout << left << setw(19) << "\nPin Code" << right << ": " << client.pinCode;
	cout << left << setw(19) << "\nClient Name" << right << ": " << client.name;
	cout << left << setw(19) << "\nPhone" << right << ": " << client.phone;
	cout << left << setw(19) << "\nAccount Balance" << right << ": " << fixed << client.accountBalance << endl;
	cout << "\n-----------------------------------\n";

	cout << "\nPlease enter deposit amount: ";
	cin >> ws >> depositAmount;

	char updateAcc = 'n';
	cout << "\n\nAre you sure you want to deposit this amount? y/n: ";
	cin >> updateAcc;

	if (tolower(updateAcc) == 'y')
	{
		for (stClient& c : vClient)
		{
			if (c.accountNumber == accountNum)
			{
				c.accountBalance += depositAmount;

				break;
			}
		}

		writeClientsInFile(vClient);
		cout << "\n\nDeposit Successful.";

		cout << "\n\nPress any key to go back to transactions menu...";
		system("pause>0");
		system("cls");
		printTransactionsScreen(vClient);
	}
	else
	{
		cout << "\n\nPress any key to go back to transactions menu...";
		system("pause>0");
		system("cls");
		printTransactionsScreen(vClient);
	}
}

void withdrawScreen(vector <stClient>& vClient) //declared above
{
	string accountNum;
	stClient client;
	double withdrawAmount = 0.0;

	cout << "\n-----------------------------------";
	cout << "\n         Withdraw Screen";
	cout << "\n-----------------------------------\n";

	accountNum = readAccountNumber();

	while (!FoundClient(vClient, accountNum))
	{
		cout << "\nClient with [" << accountNum << "] Not Found! , Enter another Account Number: ";
		cin >> accountNum;
	}

	client = getClient(vClient, accountNum);
	cout << "\nThe following are the client details:";
	cout << "\n-----------------------------------\n";

	cout << left << setw(19) << "\nAccount Number" << right << ": " << client.accountNumber;
	cout << left << setw(19) << "\nPin Code" << right << ": " << client.pinCode;
	cout << left << setw(19) << "\nClient Name" << right << ": " << client.name;
	cout << left << setw(19) << "\nPhone" << right << ": " << client.phone;
	cout << left << setw(19) << "\nAccount Balance" << right << ": " << fixed << client.accountBalance << endl;
	cout << "\n-----------------------------------\n";

	cout << "\nPlease enter withdraw amount: ";

	do
	{
		cin >> ws >> withdrawAmount;

		if (withdrawAmount > client.accountBalance)
			cout << "\nYou dont have that much money!!, Please enter another amount: ";

	} while (withdrawAmount > client.accountBalance);

	char updateAcc = 'n';
	cout << "\n\nAre you sure you want to withdraw this amount? y/n: ";
	cin >> updateAcc;

	if (tolower(updateAcc) == 'y')
	{
		for (stClient& c : vClient)
		{
			if (c.accountNumber == accountNum)
			{
				c.accountBalance -= withdrawAmount;

				break;
			}
		}

		writeClientsInFile(vClient);
		cout << "\n\nWithdraw Successful.";

		cout << "\n\nPress any key to go back to transactions menu...";
		system("pause>0");
		system("cls");
		printTransactionsScreen(vClient);
	}
	else
	{
		cout << "\n\nPress any key to go back to transactions menu...";
		system("pause>0");
		system("cls");
		printTransactionsScreen(vClient);
	}

}

void totalBalance(vector <stClient>& vClient) //declared above
{
	short clientNumber = vClient.size();
	double total = calculateTotalBalances(vClient);

	cout << "\n\t\t\t\t Client List (" << clientNumber << ") Client(s).\n";
	cout << "\n_________________________________________________________________________________\n";
	cout << "\n| Account Number | Client Name\t\t\t| Balance\n";
	cout << "\n_________________________________________________________________________________\n";
	for (short i = 0; i < clientNumber; i++)
	{
		cout << "\n| " << vClient[i].accountNumber << "\t\t | " << left << setw(20) << vClient[i].name << "\t\t| " << fixed << vClient[i].accountBalance;
	}
	cout << "\n_________________________________________________________________________________\n";

	//i used fixed from iomanip library to not print the double in scintific notation
	cout << "\n\t\t\t\t Total Balances = " << fixed << total;

	cout << "\n\nPress any key to go back to transactions menu...";
	system("pause>0");
	system("cls");
	printTransactionsScreen(vClient);
}

void printMainMenu()
{

	cout << "\n===========================================\n";
	cout << "\t\tMain Menu Screen";
	cout << "\n===========================================\n";
	cout << "\t[1] Show Client List";
	cout << "\n\t[2] Add New Client";
	cout << "\n\t[3] Delete Client";
	cout << "\n\t[4] Update Client Info";
	cout << "\n\t[5] Find Client";
	cout << "\n\t[6] Transactions";
	cout << "\n\t[7] Manage Users";
	cout << "\n\t[8] Logout";
	cout << "\n===========================================\n";

}

void printClientList(const vector <stClient>& vClient)
{
	short clientNumber = vClient.size();

	cout << "\n\t\t\t\t Client List (" << clientNumber << ") Client(s).\n";
	cout << "\n___________________________________________________________________________________________\n";
	cout << "\n| Account Number | Pin Code\t| Client Name\t\t\t| Phone\t\t| Balance\n";
	cout << "\n___________________________________________________________________________________________\n";
	for (short i = 0; i < clientNumber; i++)
	{
		cout << "\n| " << vClient[i].accountNumber << "\t\t | " << vClient[i].pinCode << "\t\t| " << left << setw(20) << vClient[i].name << "\t\t| " << vClient[i].phone << "\t| " << fixed << vClient[i].accountBalance;
	}
	cout << "\n___________________________________________________________________________________________\n";
	cout << "\n\nPress any key to go back to main menu...";
	system("pause>0");
	system("cls");
	startProgram();

}

void addClient(vector <stClient>& vClient)
{
	stClient client;
	string num;

	cout << "\n-----------------------------------";
	cout << "\n\tAdd New Clients Screen";
	cout << "\n-----------------------------------\n";

	char answer = 'n';
	do
	{
		cout << "\nAdding New Client:\n";
		num = readAccountNumber();


		while (FoundClient(vClient, num))
		{
			cout << "\nClient with [" << num << "] already exists, Enter another Account Number: ";
			cin >> num;
		}

		client.accountNumber = num;
		cout << "\nEnter Pin Code: ";
		getline(cin >> ws, client.pinCode);

		cout << "Enter Name: ";
		getline(cin, client.name);

		cout << "Enter Phone: ";
		getline(cin, client.phone);

		cout << "Enter Account Balance: ";
		cin >> ws >> client.accountBalance;

		vClient.push_back(client);

		writeClientsInFile(vClient);

		cout << "\n\nClient Added Successfuly, do you want to add more y/n: ";
		cin >> answer;
	} while (tolower(answer) == 'y');

	cout << "\n\nPress any key to go back to main menu...";
	system("pause>0");
	system("cls");
	startProgram();
}

void backToLoginScreen()
{
	system("cls");
	loginScreen();
}

void loginScreen() //declared above
{
	vector <stUser> vUser = readUsersInFIle();
	string username, password;
	bool found = false;

	cout << "\n-----------------------------------";
	cout << "\n\tLogin Screen";
	cout << "\n-----------------------------------\n";

	cout << "\nEnter Username: ";
	getline(cin >> ws, username);

	cout << "\nEnter Password: ";
	cin >> password;

	for (short i = 0; i < vUser.size(); i++)
	{
		if (vUser[i].username == username && vUser[i].password == password)
		{
			found = true;
			break;
		}
	}

	if (!found)
	{
		do
		{
			cout << "\nInvalid Username\\Password!";
			cout << "\nEnter Username: ";
			getline(cin >> ws, username);

			cout << "\nEnter Password: ";
			cin >> password;

			for (short i = 0; i < vUser.size(); i++)
			{
				if (vUser[i].username == username && vUser[i].password == password)
				{
					found = true;
					break;
				}
			}

		} while (!found);
	}

	if (found)
	{
		system("cls");
		startProgram();
	}
}

void selectUserChoice(enMainMenu choice, vector <stClient>& vClient)
{
	switch (choice)
	{
	case showClient:
		printClientList(vClient);
		break;

	case addNewClient:
		addClient(vClient);
		break;

	case deleteClient:
		markForDeletion(vClient);
		break;

	case updateClient:
		updateClientFunc(vClient);
		break;

	case findClient:
		findClientScreen(vClient);
		break;

	case transactions:
		printTransactionsScreen(vClient);
		break;

	case manageUsers:
		//add function;
		break;

	default:
		backToLoginScreen();
		break;
	}
}

void startProgram()  //declared above
{
	vector <stClient> vClient = readClientsInFile();
	printMainMenu();
	enMainMenu choice = readUserChoice();
	system("cls");
	selectUserChoice(choice, vClient);
}

int main()
{
	loginScreen();
	return 0;
}