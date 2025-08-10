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
	short permission = 0;
	bool markDeleteUser = false;
};

struct stPermission
{
	short listClients = 1;			// 0.0.0.0.0.0.1
	short addClient = 2;			// 0.0.0.0.0.1.0  
	short deleteClient = 4;			// 0.0.0.0.1.0.0
	short updateClient = 8;			// 0.0.0.1.0.0.0
	short findClient = 16;			// 0.0.1.0.0.0.0
	short doTransactions = 32;		// 0.1.0.0.0.0.0
	short accessManageUsers = 64;	// 1.0.0.0.0.0.0

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
void startProgram(vector <stUser>& vUser, short permission);
void selectTransactionMenu(enTransactionMenu choice, vector<stClient>& vClient, vector <stUser>& vUser, short permission);
void depositScreen(vector <stClient>& vClient, vector <stUser>& vUser, short permission);
void withdrawScreen(vector <stClient>& vClient, vector <stUser>& vUser, short permission);
void totalBalance(vector <stClient>& vClient, vector <stUser>& vUser, short permission);
void loginScreen();
void selectManageChoice(enManageMenu choice, vector <stUser>& vUser, short permission);
void printManageScreen(vector <stUser> vUser, short permission);


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

enManageMenu readManageChoice()
{
	short num;
	cout << "Choose What Do You Want to Do? [1 to 6]? ";
	do
	{
		cin >> ws >> num;
		if (num < 1 || num > 6)
		{
			cout << "\nSorry wrong input please enter a number between 1 to 6: ";
		}

	} while (num < 1 || num > 6);

	return enManageMenu(num);
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
	user.permission = stoi(vString[2]);
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

string convertUserToLine(stUser user)
{
	string word = "";

	word += user.username + delim
		+ user.password + delim
		+ to_string(user.permission);

	return word;
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

		while (getline(myFile, line))
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

void writeUsersInFile(vector <stUser>& vUser)
{
	fstream myFile;

	myFile.open(usersFilePath, ios::out);

	if (myFile.is_open())
	{
		string line;

		for (stUser& u : vUser)
		{
			if (u.markDeleteUser == false)
			{
				line = convertUserToLine(u);
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

stUser getUser(vector <stUser>& vUser, string username)
{
	stUser user;

	for (stUser& u : vUser)
	{
		if (u.username == username)
			user = u;
	}

	return user;
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

bool FoundUser(vector <stUser>& vUser, string username)
{
	for (stUser& u : vUser)
	{
		if (u.username == username)
		{
			return true;
		}
	}
	return false;
}

void markForDeletion(vector <stClient>& vClient, vector <stUser>& vUser, short permission)
{
	string accountNum;
	stClient client;
	stPermission perm;

	short clientNumber = vClient.size();

	if ((permission & perm.deleteClient) == perm.deleteClient)
	{
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
					break;
				}
			}
			writeClientsInFile(vClient);
			cout << "\n\nClient deleted successfuly.";
			cout << "\n\nPress any key to go back to main menu...";
			system("pause>0");
			system("cls");
			startProgram(vUser, permission);
		}
		else
		{
			cout << "\n\nPress any key to go back to main menu...";
			system("pause>0");
			system("cls");
			startProgram(vUser, permission);
		}
	}
	else
	{
		cout << "\n-----------------------------------";
		cout << "\nAccess Denied,";
		cout << "\nYou dont have permission to do this,";
		cout << "\nPlease contact your admin";
		cout << "\n-----------------------------------";
		cout << "\n\nPress any key to go back to main menu...";
		system("pause>0");
		system("cls");
		startProgram(vUser, permission);
	}
}

void deleteUserScreen(vector <stUser>& vUser, short permission)
{
	stPermission perm;

	if ((permission & perm.deleteClient) == perm.deleteClient)
	{
		string username;
		stUser user;

		cout << "\n-----------------------------------";
		cout << "\n\tDelete Users Screen";
		cout << "\n-----------------------------------\n";
		cout << "\nPlease enter username: ";
		getline(cin >> ws, username);

		if (!FoundUser(vUser, username))
		{
			cout << "\n\nUser with username (" << username << ") is Not found!";
			cout << "\n\nPress any key to go back to manage menu...";
			system("pause>0");
			system("cls");
			printManageScreen(vUser, permission);
		}
		else
		{
			user = getUser(vUser, username);

			if (user.username != "Admin")
			{
				cout << "\n\nThe following are the user details:";
				cout << "\n-----------------------------------\n";
				cout << left << setw(15) << "Username" << ": " << user.username << endl;
				cout << left << setw(15) << "Password" << ": " << user.password << endl;
				cout << left << setw(15) << "Permissions" << ": " << to_string(user.permission);
				cout << "\n-----------------------------------\n";

				char deleteUser = 'n';
				cout << "\n\nAre you sure you want to delete this user? y/n: ";
				cin >> deleteUser;

				if (tolower(deleteUser) == 'y')
				{
					for (stUser& u : vUser)
					{
						if (u.username == username)
						{
							u.markDeleteUser = true;
							break;
						}
					}
					writeUsersInFile(vUser);
					cout << "\n\nUser deleted successfully.";
					cout << "\n\nPress any key to go back to manage menu...";
					system("pause>0");
					system("cls");
					printManageScreen(vUser, permission);
				}
				else
				{
					cout << "\n\nUser is NOT deleted.";
					cout << "\n\nPress any key to go back to manage menu...";
					system("pause>0");
					system("cls");
					printManageScreen(vUser, permission);
				}
			}
			else
			{
				cout << "\n\nYou cannot delete this user.";
				cout << "\n\nPress any key to go back to manage menu...";
				system("pause>0");
				system("cls");
				printManageScreen(vUser, permission);
			}
		}
	}
	else
	{
		cout << "\n-----------------------------------";
		cout << "\n\nAccess Denied,";
		cout << "\nYou dont have permission to do this,";
		cout << "\nPlease contact your admin";
		cout << "\n-----------------------------------";
		cout << "\n\nPress any key to go back to manage menu...";
		system("pause>0");
		system("cls");
		printManageScreen(vUser, permission);
	}
}

void findClientScreen(vector <stClient>& vClient, vector <stUser>& vUser, short permission)
{
	string accountNum;
	stClient client;
	stPermission perm;

	short clientNumber = vClient.size();

	if ((permission & perm.findClient) == perm.findClient)
	{
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
		startProgram(vUser, permission);
	}
	else
	{
		cout << "\n-----------------------------------";
		cout << "\nAccess Denied,";
		cout << "\nYou dont have permission to do this,";
		cout << "\nPlease contact your admin";
		cout << "\n-----------------------------------";
		cout << "\n\nPress any key to go back to main menu...";
		system("pause>0");
		system("cls");
		startProgram(vUser, permission);
	}
}

void updateClientFunc(vector <stClient>& vClient, vector <stUser>& vUser, short permission)
{
	string accountNum;
	stClient client;
	stPermission perm;

	if ((permission & perm.updateClient) == perm.updateClient)
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
			startProgram(vUser, permission);
		}
		else
		{
			cout << "\n\nPress any key to go back to main menu...";
			system("pause>0");
			system("cls");
			startProgram(vUser, permission);
		}
	}
	else
	{
		cout << "\n-----------------------------------";
		cout << "\nAccess Denied,";
		cout << "\nYou dont have permission to do this,";
		cout << "\nPlease contact your admin";
		cout << "\n-----------------------------------";
		cout << "\n\nPress any key to go back to main menu...";
		system("pause>0");
		system("cls");
		startProgram(vUser, permission);
	}

}

void printTransactionsScreen(vector <stClient>& vClient, vector <stUser>& vUser, short permission)
{
	enTransactionMenu menuChoice;
	stPermission perm;

	if((permission & perm.doTransactions) == perm.doTransactions)
	{
		cout << "\n===========================================\n";
		cout << "\t\tTransactions Menu Screen";
		cout << "\n===========================================\n";
		cout << "\t[1] Deposit.";
		cout << "\n\t[2] Withdraw.";
		cout << "\n\t[3] Total Balances.";
		cout << "\n\t[4] Main Menu.";
		cout << "\n===========================================\n";

		menuChoice = readTransactionChoice();
		selectTransactionMenu(menuChoice, vClient, vUser, permission);
	}
	else
	{
		cout << "\n-----------------------------------";
		cout << "\nAccess Denied,";
		cout << "\nYou dont have permission to do this,";
		cout << "\nPlease contact your admin";
		cout << "\n-----------------------------------";
		cout << "\n\nPress any key to go back to main menu...";
		system("pause>0");
		system("cls");
		startProgram(vUser, permission);
		}
}

void selectTransactionMenu(enTransactionMenu choice, vector <stClient>& vClient, vector <stUser>& vUser, short permission) //declared above
{
	switch (choice)
	{
	case deposit:
		system("cls");
		depositScreen(vClient, vUser, permission);
		break;

	case withdraw:
		system("cls");
		withdrawScreen(vClient, vUser, permission);
		break;

	case totalBalances:
		system("cls");
		totalBalance(vClient, vUser, permission);
		break;

	default:
		system("cls");
		startProgram(vUser, permission);
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

void depositScreen(vector <stClient>& vClient, vector <stUser>& vUser, short permission) //declared above
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
		printTransactionsScreen(vClient, vUser, permission);
	}
	else
	{
		cout << "\n\nPress any key to go back to transactions menu...";
		system("pause>0");
		system("cls");
		printTransactionsScreen(vClient, vUser, permission);
	}
}

void withdrawScreen(vector <stClient>& vClient, vector <stUser>& vUser, short permission) //declared above
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
		printTransactionsScreen(vClient, vUser, permission);
	}
	else
	{
		cout << "\n\nPress any key to go back to transactions menu...";
		system("pause>0");
		system("cls");
		printTransactionsScreen(vClient, vUser, permission);
	}

}

void totalBalance(vector <stClient>& vClient, vector <stUser>& vUser, short permission) //declared above
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
	printTransactionsScreen(vClient, vUser, permission);
}

void printManageScreen(vector <stUser> vUser, short permission)
{
	stPermission perm;
	vUser = readUsersInFIle();

	if ((permission & perm.accessManageUsers) == perm.accessManageUsers)
	{
		cout << "\n===========================================\n";
		cout << "\tManage Users Screen";
		cout << "\n===========================================\n";
		cout << "\t[1] List Users";
		cout << "\n\t[2] Add New User";
		cout << "\n\t[3] Delete User";
		cout << "\n\t[4] Update User";
		cout << "\n\t[5] Find User";
		cout << "\n\t[6] Main Menu";
		cout << "\n===========================================\n";
		enManageMenu choice = readManageChoice();
		system("cls");
		selectManageChoice(choice, vUser, permission);
	}
	else
	{
		cout << "\n-----------------------------------";
		cout << "\nAccess Denied,";
		cout << "\nYou dont have permission to do this,";
		cout << "\nPlease contact your admin";
		cout << "\n-----------------------------------";
		cout << "\n\nPress any key to go back to main menu...";
		system("pause>0");
		system("cls");
		startProgram(vUser, permission);
		}
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

void printClientList(const vector <stClient>& vClient, vector <stUser>& vUser, short permission)
{
	short clientNumber = vClient.size();
	stPermission perm;

	if ((permission & perm.listClients) == perm.listClients)
	{
		cout << "\n\t\t\t\t Client List (" << clientNumber << ") Client(s).\n";
		cout << "\n___________________________________________________________________________________________\n";
		cout << "\n| Account Number | Pin Code\t| Client Name\t\t\t| Phone\t\t| Balance\n";
		cout << "\n___________________________________________________________________________________________\n";
		for (short i = 0; i < clientNumber; i++)
		{
			cout << "\n| " << vClient[i].accountNumber << "\t\t | " << vClient[i].pinCode << "\t\t| " << left << setw(20) << vClient[i].name << "\t\t| " << vClient[i].phone << "\t| " << fixed << vClient[i].accountBalance;
		}
		cout << "\n___________________________________________________________________________________________\n";
	}
	else
	{
		cout << "\n-----------------------------------";
		cout << "\nAccess Denied,";
		cout << "\nYou dont have permission to do this,";
		cout << "\nPlease contact your admin";
		cout << "\n-----------------------------------";
	}
	cout << "\n\nPress any key to go back to main menu...";
	system("pause>0");
	system("cls");
	startProgram(vUser, permission);

}

void printListUsers(vector <stUser>& vUser, short permission)
{
	short usersNumber = vUser.size();

	cout << "\n\t\t\t Users List (" << usersNumber << ") User(s).\n";
	cout << "\n______________________________________________________________________\n";
	cout << "\n| User Name\t | Password\t| Permissions\t\t";
	cout << "\n______________________________________________________________________\n";
	for (short i = 0; i < usersNumber; i++)
	{
		cout << "\n| " << vUser[i].username << "\t\t | " << vUser[i].password << "\t\t| " << to_string(vUser[i].permission);
	}
	cout << "\n______________________________________________________________________\n";
	cout << "\n\nPress any key to go back to manage users menu...";
	system("pause>0");
	system("cls");
	printManageScreen(vUser, permission);
}

void addClient(vector <stClient>& vClient, vector <stUser>& vUser, short permission)
{
	stClient client;
	string num;
	stPermission perm;

	cout << "\n-----------------------------------";
	cout << "\n\tAdd New Clients Screen";
	cout << "\n-----------------------------------\n";

	char answer = 'n';
	if ((permission & perm.addClient) == perm.addClient)
	{
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
	}
	else
	{
		cout << "\n-----------------------------------";
		cout << "\nAccess Denied,";
		cout << "\nYou dont have permission to do this,";
		cout << "\nPlease contact your admin";
		cout << "\n-----------------------------------";
	}

	cout << "\n\nPress any key to go back to main menu...";
	system("pause>0");
	system("cls");
	startProgram(vUser, permission);
}

void addUserScreen(vector <stUser>& vUser, short permission)
{
	stUser user;
	stPermission perm;

	cout << "\n-----------------------------------";
	cout << "\n\tAdd New User Screen";
	cout << "\n-----------------------------------\n";

	char moreUsers = 'n';
	do
	{
		bool found = false;
		cout << "\nAdding New User:\n";
		cout << "\nEnter Username: ";
		getline(cin >> ws, user.username);

		while (FoundUser(vUser, user.username))
		{
			cout << "\nUser with [" << user.username << "] already exists, Enter another username: ";
			getline(cin >> ws, user.username);
		}

		cout << "\nEnter Password: ";
		cin >> user.password;

		char fullAccess = 'n';
		cout << "\n\nDo you want to give full access? y/n: ";
		cin >> fullAccess;

		if (tolower(fullAccess) == 'y')
		{
			user.permission = -1;
		}
		else
		{
			cout << "\n\nDo you want to give access to: ";

			char clintListPermission = 'n';
			cout << "\n\nShow Client List? y/n: ";
			cin >> ws >> clintListPermission;

			if (tolower(clintListPermission) == 'y')
				user.permission = (user.permission | perm.listClients);

			//---------------------------------------
			char addClientPermission = 'n';
			cout << "\n\nAdd New Client? y/n: ";
			cin >> addClientPermission;

			if (tolower(addClientPermission) == 'y')
				user.permission = (user.permission | perm.addClient);

			//---------------------------------------
			char deleteClientPermission = 'n';
			cout << "\n\nDelete Clients? y/n: ";
			cin >> deleteClientPermission;

			if (tolower(deleteClientPermission) == 'y')
				user.permission = (user.permission | perm.deleteClient);

			//---------------------------------------
			char updateClientPermission = 'n';
			cout << "\n\nUpdate Clients? y/n: ";
			cin >> updateClientPermission;

			if (tolower(updateClientPermission) == 'y')
				user.permission = (user.permission | perm.updateClient);

			//---------------------------------------
			char findClientPermission = 'n';
			cout << "\n\nFind Client? y/n: ";
			cin >> findClientPermission;

			if (tolower(findClientPermission) == 'y')
				user.permission = (user.permission | perm.findClient);

			//---------------------------------------
			char transactionsPermission = 'n';
			cout << "\n\nTransactions? y/n: ";
			cin >> transactionsPermission;

			if (tolower(transactionsPermission) == 'y')
				user.permission = (user.permission | perm.doTransactions);

			//---------------------------------------
			char manageUsersPermission = 'n';
			cout << "\n\nManage Users? y/n: ";
			cin >> manageUsersPermission;

			if (tolower(manageUsersPermission) == 'y')
				user.permission = (user.permission | perm.accessManageUsers);

		}

		vUser.push_back(user);
		writeUsersInFile(vUser);
		cout << "\n\nUser Added Successfully, do you want to add more users? y/n: ";
		cin >> moreUsers;

	} while (tolower(moreUsers) == 'y');

	cout << "\n\nPress any key to go back to manage users menu...";
	system("pause>0");
	system("cls");
	printManageScreen(vUser, permission);
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
	short permission = 0;
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
			permission = vUser[i].permission;
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
					permission = vUser[i].permission;
					break;
				}
			}

		} while (!found);
	}

	if (found)
	{
		system("cls");
		startProgram(vUser, permission);
	}
}

void selectManageChoice(enManageMenu choice, vector <stUser>& vUser, short permission)
{
	switch (choice)
	{
	case listUsers:
		printListUsers(vUser, permission);
		break;

	case addUser:
		addUserScreen(vUser, permission);
		break;

	case deleteUser:
		deleteUserScreen(vUser, permission);
		break;

	case updateUser:
		// add func
		break;

	case findUser:
		// add func
		break;

	default:
		startProgram(vUser, permission);
		break;
	}
}

void selectUserChoice(enMainMenu choice, vector <stClient>& vClient, vector <stUser>& vUser, short permission)
{
	switch (choice)
	{
	case showClient:
		printClientList(vClient, vUser, permission);
		break;

	case addNewClient:
		addClient(vClient, vUser, permission);
		break;

	case deleteClient:
		markForDeletion(vClient, vUser, permission);
		break;

	case updateClient:
		updateClientFunc(vClient, vUser, permission);
		break;

	case findClient:
		findClientScreen(vClient, vUser, permission);
		break;

	case transactions:
		printTransactionsScreen(vClient, vUser, permission);
		break;

	case manageUsers:
		printManageScreen(vUser, permission);
		break;

	default:
		backToLoginScreen();
		break;
	}
}

void startProgram(vector <stUser>& vUser, short permission)  //declared above
{
	vector <stClient> vClient = readClientsInFile();
	printMainMenu();
	enMainMenu choice = readUserChoice();
	system("cls");
	selectUserChoice(choice, vClient, vUser, permission);
}

int main()
{
	loginScreen();
	return 0;
}