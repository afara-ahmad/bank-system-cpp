#include <iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<vector>
using namespace std;
void MainMenuOption();
void TransActionOption();
const string ClientFile = "ClientFile.txt";
enum enMainMenuOptions { ShowClientList = 1, AddNewClient = 2, Delete = 3, Update = 4, Find = 5, eTrans=6, enExit = 7 };
enum enTransAction { Dep = 1, with = 2, Total = 3, Main = 4 };
struct stClient {
	string AccountNumber;
	double AccountBalance;
	string Name;
	string Phone;
	string PinCode;
	bool MarkForDelete = false;
};
string ReadAccountNumber() {
	string AccountNumber;
	cout << "Enter Account Number ? ";
	cin >> AccountNumber;
	return AccountNumber;
}
enMainMenuOptions ReadMenuOptions() {
	short Number = 0;
	do {
		cout << "Choose What Do You want to do ? [1 to 7]?";
		cin >> Number;
	} while (Number < 1 || Number>7);
	return (enMainMenuOptions)Number;
}
enTransAction ReadTransActionMenu() {
	short Number = 0;
	do {
		cout << "Choose What Do You want to do ? [1 to 4]?";
		cin >> Number;
	} while (Number < 1 || Number>4);
	return (enTransAction)Number;
}
stClient ReadDataClient(string AccountNumber) {
	stClient Client;
	Client.AccountNumber = AccountNumber;
	cout << "Enter PinCode? ";
	getline(cin>>ws, Client.PinCode);
	cout << "Enter Name? ";
	getline(cin, Client.Name);
	cout << "Enter Phone? ";
	getline(cin, Client.Phone);
	cout << "Enter Account Balance? ";
	cin>> Client.AccountBalance;

	return Client;
}
vector<string> SplitString(string DataLine,string Delim){
	vector<string>vString;
	short Pos=0;
	string sWord = "";
	while ((Pos = DataLine.find(Delim)) != std::string::npos) {
		sWord = DataLine.substr(0, Pos);
		if (sWord != "") {
			vString.push_back(sWord);
		}
		DataLine.erase(0, Pos + Delim.length());
	}
	if (DataLine != "") {
		vString.push_back(DataLine);
	}
	return vString;
}
string ConvertRecordToLine(stClient &Client,string Delim) {
	string S1 = "";
	S1 = S1 + Client.AccountNumber + Delim;
	S1 = S1 + Client.PinCode + Delim;
	S1 = S1 + Client.Name + Delim;
	S1 = S1 + Client.Phone + Delim;
	S1 = S1 + to_string(Client.AccountBalance);
	return S1;

}
stClient ConvertLineToRecord(string &DataLine) {
	vector<string>vClient = SplitString(DataLine, "#//#");
	stClient Client;
	Client.AccountBalance =stod(vClient[4]);
	Client.AccountNumber = vClient[0];
	Client.Name = vClient[2];
	Client.Phone = vClient[3];
	Client.PinCode = vClient[1];
	return Client;
}
vector<stClient>LoadDataClientFromFile(string FileName) {
	vector<stClient>vClient;
	fstream MyFile;
	MyFile.open(FileName, ios::in);
	if (MyFile.is_open()) {
		string Line;
		stClient Client;
		while (getline(MyFile, Line)) {
			Client = ConvertLineToRecord(Line);
			vClient.push_back(Client);
		}
		MyFile.close();
	}
	return vClient;
}
void PrintClientData(stClient Client) {
	cout << "The following are the client details:\n";
	cout << "---------------------------------------\n";
	cout << "Account Number : " << Client.AccountNumber << endl;
	cout << "Pin Code     : " << Client.PinCode << endl;
	cout << "Name       : " << Client.Name << endl;
	cout << "Phone     :" << Client.Phone << endl;
	cout << "Account Balance : " << Client.AccountBalance << endl;
	cout << "---------------------------------------\n";

}
void PrintClient(stClient &Client) {
	cout << "| " << left << setw(15) << Client.AccountNumber;
	cout << "| " << left << setw(10) << Client.PinCode;
	cout << "| " << left << setw(40) << Client.Name;
	cout << "| " << left << setw(12) << Client.Phone;
	cout << "| " << left << setw(12) << Client.AccountBalance;
}
void PrintAllClient(vector<stClient> &vClient) {
	cout << "\n\t\t\t\t\t" << "Client List (" << vClient.size() << ") Client (s).";
	cout << "\n__________________________________________________________";
	cout << "_____________________________________________\n" << endl;

	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Account Balance";
	cout << "\n__________________________________________________________";
	cout << "_____________________________________________\n" << endl;

	for (stClient & S : vClient) {
		PrintClient(S);
		cout << endl;
	}
	cout << "\n__________________________________________________________";
	cout << "_____________________________________________\n" << endl;
}
void SaveDataClientToFile(string FileName,string DataLine) {
	fstream MyFile;
	vector<string>vClient = SplitString(DataLine, "#//#");
	MyFile.open(FileName, ios::out | ios::app);
	if (MyFile.is_open()) {

			if (DataLine != "") {
				cout << endl;
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}
void SaveToFile(vector<stClient>vClient,string FileName) {
	fstream MyFile;
	MyFile.open(FileName, ios::out);
	if (MyFile.is_open()) {
		for (stClient C : vClient) {
			string Line;
			if (C.MarkForDelete == false) {
				Line = ConvertRecordToLine(C, "#//#");
				MyFile << Line << endl;
			}
		}
	}
}
bool MarkForDeleteClient(vector<stClient>&vClient,string AccountNumber) {
	for (stClient& C : vClient) {
		if (C.AccountNumber == AccountNumber) {
			C.MarkForDelete = true;
			return true;
		}
	}
	return false;
}
bool FindClientByAccountNumber(vector<stClient>vClient, string AccountNumber, stClient& Client) {
	vClient = LoadDataClientFromFile(ClientFile);
	for (stClient& C : vClient) {
		if (C.AccountNumber == AccountNumber) {
			Client = C;
			return true;
		}
	}
	return false;
}
bool DeleteClientByAccountNumber(vector<stClient>vClient, string AccountNumber, stClient& Client) {
	vClient = LoadDataClientFromFile(ClientFile);
	char Answer = 'n';
	if (FindClientByAccountNumber(vClient, AccountNumber, Client)) {
		PrintClientData(Client);
		cout << "\n\nAre You sure you want delete this client? y/n ?";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {
			MarkForDeleteClient(vClient, AccountNumber);
			SaveToFile(vClient, ClientFile);

			vClient = LoadDataClientFromFile(ClientFile);
			cout << "Client Deleted Successfully." << endl;
			return true;


		}
	}
	else {
		cout << "Client with Account Number [" << AccountNumber << "] is Not Found!" << endl;

		return false;
	}
}
bool UpdateClientByAccountNumber(vector<stClient>vClient, string AccountNumber, stClient& Client) {
	vClient = LoadDataClientFromFile(ClientFile);
	char Answer = 'n';
	if (FindClientByAccountNumber(vClient, AccountNumber, Client)) {
		PrintClientData(Client);
		cout << "\n\nAre You sure you want Update this client? y/n ?";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') {

			for (stClient & C : vClient) {
				if (AccountNumber == C.AccountNumber) {
					C = ReadDataClient(AccountNumber);
				}
			}

			SaveToFile(vClient, ClientFile);

			cout << "Client Updated Successfully." << endl;

			return true;


		}
	}
	else {
		cout << "Client with Account Number ["<<AccountNumber<<"] is Not Found!" << endl;
		return false;
	}
}
void ShowAllClients() {
	vector<stClient> vClient = LoadDataClientFromFile(ClientFile);
	PrintAllClient(vClient);
}
bool IsAccountNumberExists(vector<stClient>& vClient, string AccountNumber) {
	for (stClient& C : vClient) {
		if (C.AccountNumber == AccountNumber)
			return true;
	}
	return false;
}
void AddClient() {
	
		cout << "\n==========================================\n";
		cout << "\tAdd New Clients Screen \n";
		cout << "==========================================\n";
		cout << "Adding New Client :\n\n";
		char AddMore = 'y';
		do {
			vector<stClient> vClient = LoadDataClientFromFile(ClientFile);
			string AccountNumber = ReadAccountNumber();
			while (IsAccountNumberExists(vClient, AccountNumber)) {
				cout << "Client with [" << AccountNumber << "] Already Exists, Enter Another Account Number ? ";
				cin >> AccountNumber;
			}
			stClient Client = ReadDataClient(AccountNumber);
			string S1 = ConvertRecordToLine(Client, "#//#");
			SaveDataClientToFile(ClientFile, S1);
			cout << "Client Added Successfully, Do You Want to Add More Clients? Y/N ? ";
			cin >> AddMore;
		} while (AddMore == 'y' || AddMore == 'Y');
	}

void DeleteClientScreen() {
	cout << "\n==========================================\n";
	cout << "\tDelete Client Screen \n";
	cout << "==========================================\n\n";
	string AccountNumber = ReadAccountNumber();
	vector<stClient>vClient = LoadDataClientFromFile(ClientFile);
	stClient Client;
	DeleteClientByAccountNumber(vClient, AccountNumber, Client);

}
void UpdateClientScreen() {
	cout << "\n==========================================\n";
	cout << "\tUpdate Client Screen \n";
	cout << "==========================================\n\n";
	string AccountNumber = ReadAccountNumber();
	vector<stClient>vClient = LoadDataClientFromFile(ClientFile);
	stClient Client;
	UpdateClientByAccountNumber(vClient, AccountNumber, Client);
}
void FindClient() {
	cout << "\n==========================================\n";
	cout << "\tFind Client Screen \n";
	cout << "==========================================\n\n";
	string AccountNumber = ReadAccountNumber();
	vector<stClient>vClient = LoadDataClientFromFile(ClientFile);
	stClient Client;
	if (FindClientByAccountNumber(vClient, AccountNumber, Client)) {
		PrintClientData(Client);
	}
	else {
		cout << "Client with Account Number [" << AccountNumber << "] is Not Found!" << endl;

	}
}
void Exits() {
	cout << "\n==========================================\n";
	cout << "\Program Ends :-) \n";
	cout << "==========================================\n\n";
	
}
void ShowMainMenu() {
	system("cls");
	cout << "===========================================\n";
	cout << "\t\tMain Menu Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transaction.\n";
	cout << "\t[7] Exit.\n";
	cout << "===========================================\n";



}
void GoBack() {

	cout << "Press Any Key to Go Back to Main Menu... ";
	system("pause>nul");
	MainMenuOption();

}
void GoBackToTransActionMenu() {

	cout << "Press Any Key to Go Back to Main Menu... ";
	system("pause>nul");
	TransActionOption();

}
void TaransActionMenuScreen() {
	system("cls");
	cout << "===========================================\n";
	cout << "\t\tTransAction Menu Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] Deposit.\n";
	cout << "\t[2] WithDraw.\n";
	cout << "\t[3] Total Balance.\n";
	cout << "\t[4] Main Menu.\n";
	cout << "===========================================\n";

}
bool DepositClientByAccountNumber(vector<stClient>vClient, string AccountNumber, stClient& Client) {
	vClient = LoadDataClientFromFile(ClientFile);
	double DepositAmmount = 0;
	char Answer = 'n';
	if (FindClientByAccountNumber(vClient, AccountNumber, Client)) {
		PrintClientData(Client);
		cout << "\n\nPlease Enter Deposit Amount? ?";
		cin >> DepositAmmount;
		cout << "\n\nAre You Sure you want Perform this transAction? y/n ?";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y') {

			for (stClient& C : vClient) {
				if (AccountNumber == C.AccountNumber) {
					C.AccountBalance= C.AccountBalance + DepositAmmount;
					break;
				}
			}

			SaveToFile(vClient, ClientFile);

			cout << "\nDone Successfully ." << endl;

			return true;


		}
	}
	else {
		cout << "Client With ["<<AccountNumber<<"] does not exist." << endl;
		return false;
	}
}
bool WithDrawClientByAccountNumber(vector<stClient>vClient, string AccountNumber, stClient& Client) {
	vClient = LoadDataClientFromFile(ClientFile);
	double WithDrawAmmount = 0;
	char Answer = 'n';
	if (FindClientByAccountNumber(vClient, AccountNumber, Client)) {
		PrintClientData(Client);
		cout << "\n\nPlease Enter WithDraw Amount ?";
		cin >> WithDrawAmmount;
		

		for (stClient& C : vClient) {
			if (AccountNumber == C.AccountNumber) {
				while (WithDrawAmmount > C.AccountBalance) {
					cout << "Amount exceeds the balance, you can withdraw up to : " << C.AccountBalance << endl;
					cout << "Please Enter Another Amount ? ";
					cin >> WithDrawAmmount;
				}
				C.AccountBalance = C.AccountBalance - WithDrawAmmount;
				break;
			}
		}

			SaveToFile(vClient, ClientFile);

			cout << "\nDone Successfully ." << endl;

			return true;


		
	}
	else {
		cout << "Client With [" << AccountNumber << "] does not exist." << endl;
		return false;
	}
}
void DepositScreen() {
	cout << "\n==========================================\n";
	cout << "\tDeposit Screen \n";
	cout << "==========================================\n\n";
	string AccountNumber = ReadAccountNumber();
	vector<stClient>vClient = LoadDataClientFromFile(ClientFile);
	stClient Client;
	DepositClientByAccountNumber(vClient, AccountNumber, Client);
}
void WithDrawScreen() {
	cout << "\n==========================================\n";
	cout << "\tWithDraw Screen \n";
	cout << "==========================================\n\n";
	string AccountNumber = ReadAccountNumber();
	vector<stClient>vClient = LoadDataClientFromFile(ClientFile);
	stClient Client;
	WithDrawClientByAccountNumber(vClient, AccountNumber, Client);
}
double TotalBalanceForClients(vector<stClient>& vClient) {
	double TotalBalance = 0;
	for (stClient& C : vClient) {
		TotalBalance += C.AccountBalance;
	}
	return TotalBalance;
}
void TotalBalance(stClient& Client) {
	cout << "| " << left << setw(15) << Client.AccountNumber;
	cout << "| " << left << setw(40) << Client.Name;
	cout << "| " << left << setw(12) << Client.AccountBalance;
}
void PrintTotalBalance(vector<stClient>& vClient) {
	cout << "\n\t\t\t\t\t" << "Client List (" << vClient.size() << ") Client (s).";
	cout << "\n__________________________________________________________";
	cout << "_____________________________________________\n" << endl;

	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Account Balance";
	cout << "\n__________________________________________________________";
	cout << "_____________________________________________\n" << endl;

	for (stClient& S : vClient) {
		TotalBalance(S);
		cout << endl;
	}
	cout << "\n__________________________________________________________";
	cout << "_____________________________________________\n" << endl;
	cout << "\t\t\t\t\tTotal Balances = " << TotalBalanceForClients(vClient) << "\n\n";
}
void TotalBalancesScreen() {
	vector<stClient> vClient = LoadDataClientFromFile(ClientFile);
	PrintTotalBalance(vClient);
}




int main() {
	MainMenuOption();
	
}
void MainMenuOption() {
	ShowMainMenu();
	enMainMenuOptions Option = ReadMenuOptions();
	switch (Option) {
	case enMainMenuOptions::ShowClientList:
		system("cls");
		ShowAllClients();
		GoBack();

		break;
	case enMainMenuOptions::AddNewClient:
		system("cls");
		AddClient();
		GoBack();
		break;
	case enMainMenuOptions::Delete:
		system("cls");
		DeleteClientScreen();
		GoBack();
		break;
	case enMainMenuOptions::Update:
		system("cls");
		UpdateClientScreen();
		GoBack();
		break;
	case enMainMenuOptions::Find:
		system("cls");
		FindClient();
		GoBack();
		break;
	case enMainMenuOptions::eTrans:
		system("cls");
		TransActionOption();
		GoBack();
		break;
	case enMainMenuOptions::enExit:
		system("cls");
		Exits();
		
		break;
	}
}
void TransActionOption() {
	TaransActionMenuScreen();
	enTransAction Trans;
	Trans = ReadTransActionMenu();
	switch (Trans) {
	case enTransAction::Dep:
		system("cls");
		DepositScreen();
		GoBackToTransActionMenu();
		break;
	case enTransAction::with:
		system("cls");
		WithDrawScreen();
		GoBackToTransActionMenu();
		break;
	case enTransAction::Total:
		system("cls");
		TotalBalancesScreen();
		GoBackToTransActionMenu();
		break;
	case enTransAction::Main:
		system("cls");
		MainMenuOption();
		
		break;
	}
}
