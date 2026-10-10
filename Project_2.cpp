#include<string>
#include<sstream>
#include<iostream>
#include<iomanip>
#include<vector>
#include<fstream>

#define STEP 1234

//reused Funtions

void clr() {
	std::cout << std::flush;
	system("CLS");
}

void pause() {

	std::string p;
	std::cout << "\nEnter any value to continue ";
	getline(std::cin, p);
	clr();
}

bool isint(std::string x) {

	for (int i = 0; i < x.length(); i++) {
		if (i == 0) {
			if ((x[i] < 48 || x[i] > 57) && x[i] != '-') {
				return false;
			}
		}
		else {
			if (x[i] < 48 || x[i] > 57) {
				return false;
			}
		}
	}
	return true;

}

bool isfloat(std::string x) {

	bool dot = false;

	for (int i = 0; i < x.length(); i++) {
		if (i == 0) {
			if ((x[i] < 48 || x[i] > 57) && !(x[i] == '-' || x[i] == '.')) {
				return false;
			}
			if (x[i] == '.') {
				dot = true;
			}
		}
		else if ((x[i] < 48 || x[i] > 57) && !(x[i] == '.' && !(dot))) {
			return false;
		}
		if (x[i] == '.' && dot) {
			return false;
		}
		if (x[i] == '.' && !(dot)) {
			dot = true;
		}
	}
	return true;

}

std::vector<std::string> string_to_vector(std::string abc) {

	std::vector<std::string> vect;
	std::string temp;

	int i = 0;

	while (true) {

		if (abc[i] == ';') {
			vect.push_back(temp);
			temp.clear();
		}
		else {
			temp.push_back(abc[i]);
		}
		i++;
		if (i == abc.length()) {
			vect.push_back(temp);
			break;
		}

	}

	return vect;

}

std::vector<float> Transaction_Convert(std::vector<std::string> vect) {

	std::vector<float> Transactions;

	for (int i = 0; i < vect.size(); i++) {

		Transactions.push_back(stof(vect[i]));

	}

	return Transactions;

}

std::string Currencystof(float x) {

	std::string y = std::to_string(x);
	std::string z;

	for (int i = 0; i < y.length() - 4; i++) {
		z.push_back(y[i]);
	}

	return z;

}

std::string dash_to_space(std::string abc) {

	std::string temp;

	for (int i = 0; i < abc.length(); i++) {
		if (abc[i] == '-') {
			temp.push_back(' ');
		}
		else {
			temp.push_back(abc[i]);
		}
	}

	return temp;

}

std::string space_to_dash(std::string abc) {

	std::string temp;

	for (int i = 0; i < abc.length(); i++) {
		if (abc[i] == ' ') {
			temp.push_back('-');
		}
		else {
			temp.push_back(abc[i]);
		}
	}

	return temp;

}

std::string encryption(std::string s) {
	int step = STEP % 26;
	int length = s.size();
	std::string output;
	for (int i = 0; i < length; i++) {
		if (s[i] == '-') {
			output.push_back(s[i]);
		}
		else {
			output.push_back(s[i] + step);
		}
	}

	return output;
}

std::string decryption(std::string s) {
	int step = STEP % 26;
	int length = s.size();
	std::string output;
	for (int i = 0; i < length; i++) {
		if (s[i] == '-') {
			output.push_back(s[i]);
		}
		else {
			output.push_back(s[i] - step);
		}
	}

	return output;
}



// Date Structure



inline std::tm localtime_xp(std::time_t timer)      // Using this to make localtime a safe function

{

	std::tm bt{};

#if defined(__unix__)

	localtime_r(&timer, &bt);

#elif defined(_MSC_VER)

	localtime_s(&bt, &timer);

#else

	static std::mutex mtx;

	std::lock_guard<std::mutex> lock(mtx);

	bt = *std::localtime(&timer);

#endif

	return bt;

}

struct date
{
	//int day_of_year;   //Used to calculate when fees and interest get automatically paid

	int day;

	int month;

	int year;

	std::string date_formatted;

	date() // Defaults to 0

	{

		std::tm now = localtime_xp(std::time(0));

		day = (now.tm_mday);

		//day_of_year = (now.tm_yday) + 1;

		month = (now.tm_mon) + 1;

		year = (now.tm_year) + 1900;



		std::ostringstream string;

		string << std::setw(2) << std::setfill('0') << day << "/" << std::setw(2) << std::setfill('0') << month << "/" << std::setw(2) << std::setfill('0') << year;// << ":" << std::setw(3) << std::setfill('0') << day_of_year;

		date_formatted = string.str();

	}

	void Change_Date_Manual(std::string date_formatted) // Can input a custom date as well, formatted DD/MM/YYYY

	{

		this->date_formatted = date_formatted;

		day = atoi(date_formatted.substr(0, 2).c_str());

		month = atoi(date_formatted.substr(3, 2).c_str());

		year = atoi(date_formatted.substr(6, 4).c_str());

		//day_of_year = atoi(date_formatted.substr(11, 3).c_str());

	}
} current_date;



//User Class



class User
{

protected:

	int SSN;
	std::string Username;
	std::string Name;
	std::string Organization;
	std::string Password;
	date Date_Of_Birth;
	date Date_Of_Join;

public:

	User()
	{

		SSN = 0;
		Username = "NA";
		Name = "NA";
		Organization = "NA";
		Password = "NA";
		Date_Of_Birth;
		Date_Of_Join;

	}

	User(int ssn, std::string username, std::string name, std::string org, std::string password, date DOB)
	{

		SSN = ssn;
		Username = username;
		Name = name;
		Organization = org;
		Password = password;
		Date_Of_Birth = DOB;
		Date_Of_Join;

	}

};



//Admin Class



class Admin : public User
{
private:

	int AID;
	int Rank;
	bool disabled = false;

public:

	Admin() {}

	Admin(std::string aid, std::string ssn, std::string username, std::string name, std::string rank, std::string org, std::string password, date DOB, date DOJ) {

		AID = stoi(aid);
		std::string temp;
		for (int i = 0; i <= 10; i++) {
			if (i != 3 && i != 6) {
				temp.push_back(ssn[i]);
			}
		}
		SSN = stoi(temp);
		Username = username;
		Name = name;
		Rank = stoi(rank);
		Organization = org;
		Password = password;
		Date_Of_Birth = DOB;
		Date_Of_Join = DOJ;

	}

	Admin(std::string aid, std::string ssn, std::string username, std::string name, std::string rank, std::string org, std::string password, date DOB, date DOJ, std::string disabled) {

		AID = stoi(aid);
		std::string temp;
		for (int i = 0; i <= 10; i++) {
			if (i != 3 && i != 6) {
				temp.push_back(ssn[i]);
			}
		}
		SSN = stoi(temp);
		Username = username;
		Name = name;
		Rank = stoi(rank);
		Organization = org;
		Password = password;
		Date_Of_Birth = DOB;
		Date_Of_Join = DOJ;
		if (disabled == "true")
			this->disabled = true;

	}

	bool Check_Username(std::string Username)
	{

		if (Username == this->Username)
			return true;
		else
			return false;

	}

	bool Check_Password() {

		std::string Input;
		bool exit = false;

		do {

			std::cout << "Enter Admin Password: ";
			getline(std::cin, Input);

			if (Input == "EXIT") {
				exit = true;
			}
			else {
				if (Input == Password) {
					return true;
				}
				else {
					std::cout << "Invalid Admin Password, please try again or enter 'EXIT' to leave" << std::endl;
				}
			}

		} while (!exit);

		return false;

	}

	void Display_Name() {

		std::cout << "Welcome " << Name << ", admin ID: " << AID << ", Rank: " << Rank << std::endl;

	}

	int getRank() {

		return Rank;

	}

	int getAID() { return AID; }

	void Display_Info() {

		std::cout << "AID: " << AID << ", Name: " << Name << ", Rank: " << Rank << ", Date of Join: " << Date_Of_Join.date_formatted << "\n";

	}

	void Create_Admin();

	void Delete_Admin();

	void Admin_Disable() { this->disabled = true; }
	bool admin_is_disabled() { return this->disabled; }

	friend std::ofstream& operator << (std::ofstream& out, Admin& Ad);

};



//Customer Class



class Customer : public User
{
private:

	int CID;
	int Strikes;
	std::string Account_Type;
	std::string Status;
	std::vector<std::string> Messages;
	std::vector<float> Transactions;
	std::vector<std::string> Transaction_Types;
	float Current_Balance;

public:

	Customer() {

		CID = 0;
		Strikes = 0;
		Account_Type = "NA";
		Current_Balance = 0;
		Messages = {};
		Transactions = {};
		Transaction_Types = {};

	}

	Customer(std::string cid, std::string strikes, std::string ssn, std::string username, std::string name, std::string account_type, std::string status, std::string org, date DOB, date DOJ, std::string password, std::string current_balance)
	{

		CID = stoi(cid);
		Strikes = stoi(strikes);
		std::string temp;
		for (int i = 0; i <= 10; i++) {
			if (i != 3 && i != 6) {
				temp.push_back(ssn[i]);
			}
		}
		SSN = stoi(temp);
		Username = username;
		Name = name;
		Account_Type = account_type;
		Status = status;
		Organization = org;
		Date_Of_Birth = DOB;
		Date_Of_Join = DOJ;
		Password = password;
		Current_Balance = stof(current_balance);

	}

	int getCID() { return this->CID; }

	void New_Message(std::string Message) { Messages.push_back(Message); }

	void New_Transaction(float Transaction, std::string Transaction_Type)
	{

		Transactions.push_back(Transaction);
		Transaction_Types.push_back(Transaction_Type);

	}

	void Pay_Interest() // This gets called for every customer by the admin panel
	{					// NOT CALLABLE BY USER
		if (Status == "Active")		// If active, the function runs.

		{
			if (Current_Balance > 0) {	// Awards a strike if balance is less than 0

				int Interest;

				if (Account_Type == "Business") {
					Interest = Current_Balance * .03;
				}
				else {
					Interest = Current_Balance * .02;
				}

				std::string Message = "Interest paid of " + Currencystof(Interest);
				New_Message(Message);
				New_Transaction(Interest, "Interest");
				Current_Balance += Interest;	// Achievement get! Interest

			}

			else {
				New_Message("Account Negative at Interest paid, strike added");
				Strikes += 1;	// YOU'RE HORRIBLE. You're and irredeemable monster!
			}					// Ohhh, ohhhh, what took you so long, IDIOT. *flick*
		}
		else
			return;

	}

	void Increase_Balance(float Inc)
	{

		Current_Balance += Inc;

	}

	bool Check_Username(std::string Input)
	{

		if (Input == Username)
			return true;
		else
			return false;

	}

	bool Check_Password()
	{

		std::string Input;
		bool exit = false;

		do {

			std::cout << "Enter Customer Password: ";
			getline(std::cin, Input);

			if (Input == "EXIT") {
				exit = true;
			}
			else {
				if (Input == Password) {
					return true;
				}
				else {
					std::cout << "Invalid Customer Password, please try again or enter 'EXIT' to leave" << std::endl;
				}
			}

		} while (!exit);

		return false;

	}

	bool Strike_Check()
	{

		if (Strikes >= 4)
			return true;
		else
			return false;

	}

	void Display_Name()
	{

		std::cout << "Welcome " << Name << ", Customer ID: " << CID << std::endl;

	}

	void Display_Info()
	{

		std::cout << "CID: " << CID << ", Name: " << Name << ", Date of Join: " << Date_Of_Join.date_formatted << std::endl;

	}

	void Positive_Display()
	{

		if (Current_Balance > 0)
		{
			std::cout << "CID: " << CID << ", Name: " << Name << ", Username: " << Username << ", Current Balance: " << Currencystof(Current_Balance) << "\n";
		}

	}

	void Negative_Display()
	{

		if (Current_Balance < 0)
		{
			std::cout << "CID: " << CID << ", Name: " << Name << ", Username: " << ", Current Balance: " << Currencystof(Current_Balance) << "\n";
		}

	}

	bool Positive_Check()
	{

		if (Current_Balance > 0)
			return true;
		else
			return false;

	}

	bool Active_Check()
	{

		if (Status == "Active")
			return true;
		else
			return false;

	}

	void Block_Account() {

		do {

			std::string Input;

			std::cout << "CID: " << CID << ", Name: " << Name << ", Strikes: " << Strikes << ", Date of Join: " << Date_Of_Join.date_formatted << "\n";
			std::cout << "Block Account? (Y/N)";
			getline(std::cin, Input);

			if (Input != "Y" && Input != "N") {
				clr();
				std::cout << "Invalid, please Enter Y for yes or N for no\n";
			}
			else {
				if (Input == "Y") {
					clr();
					std::cout << "CID " << CID << " Blocked\n";
					Status = "Inactive";
					break;
				}
				else {
					clr();
					std::cout << "CID " << CID << " Not blocked\n";
					break;
				}
			}

		} while (true);

	}

	void Statement_Summary() {

		std::cout << "Statement Summary\n";

		std::string Input;
		int Number;

		do {

			std::cout << "Enter number of Transactions you would like to see (0 - " << Transactions.size() << "): ";
			getline(std::cin, Input);

			if (!isint(Input)) {
				clr();
				std::cout << "Invalid, please enter an integer\n";
			}
			else {
				Number = stoi(Input);
				if (Number < 0 || Number > Transactions.size()) {
					clr();
					std::cout << "Invalid, please enter a number within range";
				}
				else {
					break;
				}
			}

		} while (true);

		clr();

		for (int i = Transactions.size() - Number; i < Transactions.size(); i++) {
			std::cout << i << ". " << Transaction_Types[i] << ": " << Transactions[i] << "\n";
		}

	}

	void Display_Balance() {

		std::cout << "Current Balance: " << Current_Balance << std::endl;

	}

	void Withdraw() {	// Admins have no overdraft fee, manually blocked if overdraft too much

		std::cout << "Withdraw" << std::endl;

		std::string Input;
		float Withdraw;

		do {

			std::cout << "Enter amount you would like to Withdraw: " << std::endl;
			getline(std::cin, Input);

			if (!isfloat(Input)) {
				clr();
				std::cout << "Invalid, please enter a number" << std::endl;
			}
			else {
				Withdraw = stof(Input);
				if (Withdraw <= 0) {
					clr();
					std::cout << "Invalid, please enter a positive number." << std::endl;
				}
				else {
					break;
				}
			}

		} while (true);

		New_Transaction(Withdraw, "Withdraw");

		std::string message = "Withdrawal of $" + Currencystof(Withdraw);

		New_Message(message);

		Current_Balance -= Withdraw;

	}

	void Deposit() {

		std::cout << "Deposit" << std::endl;

		std::string Input;
		float Deposit;

		do {

			std::cout << "Enter amount you would like to Deposit: ";
			getline(std::cin, Input);

			if (!isfloat(Input)) {
				clr();
				std::cout << "Invalid, please enter a number" << std::endl;
			}
			else {
				Deposit = stof(Input);
				if (Deposit <= 0) {
					clr();
					std::cout << "Invalid, please enter a positive number" << std::endl;
				}
				else {
					break;
				}
			}

		} while (true);

		New_Transaction(Deposit, "Deposit");

		std::string message = "Deposit of $" + Currencystof(Deposit);

		New_Message(message);

		Current_Balance += Deposit;

	}

	void Transfer();	// Dependent on a list defined later in the program

	void Message_Summary() {

		std::cout << "Message Summary\n";

		std::string Input;
		int Number;

		do {

			std::cout << "Enter number of Messagess you would like to see (0 - " << Messages.size() << "): ";
			getline(std::cin, Input);

			if (!isint(Input)) {
				clr();
				std::cout << "Invalid, please enter an integer\n";
			}
			else {
				Number = stoi(Input);
				if (Number < 0 || Number > Messages.size()) {
					clr();
					std::cout << "Invalid, please enter a number within range";
				}
				else {
					break;
				}
			}

		} while (true);

		clr();

		for (int i = Messages.size() - Number; i < Messages.size(); i++) {
			std::cout << i << ". " << Messages[i] << "\n";
		}

	}

	friend std::ofstream& operator << (std::ofstream& out, Customer& Cu);

};



//Reused Functions



std::vector<Admin> Admin_Data;

std::vector<Customer> Customer_Data;

int MIndex[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

bool Date_Check(date DOB, date DOJ) {

	if (DOB.year + 18 < DOJ.year) {
		return true;
	}
	else {
		if (DOB.year + 17 >= DOJ.year) {
			return false;
		}
		else {
			if (DOB.month > DOJ.month) {
				return false;
			}
			else {
				if (DOB.month < DOJ.month) {
					return true;
				}
				else {
					if (DOB.day <= DOJ.day) {
						return true;
					}
					else {
						return false;
					}
				}
			}
		}
	}

}

void Admin::Create_Admin() {

	std::string AID, SSN, rank;
	std::string Username, Name, Organization, Password, DOB;
	date DOJ, Date_Of_Birth;
	std::string Input;
	bool check = false;

	std::cout << "Creating a new Admin\n";

	do {

		check = false;

		std::cout << "Enter new Admin Username: ";
		getline(std::cin, Username);
		for (int i = 0; i < Username.length(); i++) {
			if (Username[i] == ' ') {
				check = true;
				clr();
				std::cout << "Spaces are not allowed in username, please try again\n";
				break;
			}
		}
		for (int i = 0; i < Customer_Data.size(); i++) {
			if (Admin_Data[i].Check_Username(Username)) {
				check = true;
				clr();
				std::cout << "Username is already taken, please try a different Username\n";
				break;
			}
		}

	} while (check);

	clr();

	std::cout << "Creating a new Admin\n";

	std::cout << "Enter new Admin Name: ";
	getline(std::cin, Name);

	clr();

	std::cout << "Creating a new Admin\n";

	std::cout << "Enter new Admin Organization: ";
	getline(std::cin, Organization);

	clr();

	// Enter code for Date of Birth check

	std::cout << "Creating a new Admin\n";

	do {

		check = false;

		std::cout << "Enter new Admin Social Security number (xxx-xx-xxxx): ";
		getline(std::cin, Input);

		if (Input.length() != 11) {
			check = true;
		}
		else {
			if (Input[3] != '-' || Input[6] != '-') {
				check = true;
			}
			else {
				std::string SocTemp;
				for (int i = 0; i < 11; i++) {
					if (i != 3 && i != 6) {
						SocTemp.push_back(Input[i]);
					}
				}
				if (!(isint(SocTemp))) {
					check = true;
				}
				else {
					SSN = Input;
				}
			}
		}

		if (check) {
			clr();
			std::cout << "Invalid input, please enter a string with the valid form\n";
		}

	} while (check);

	clr();

	std::cout << "Creating a new Admin\n";

	do {

		check = false;

		int day, month, year;

		std::cout << "Enter new Admin date of birth (DD/MM/YYYY): ";
		getline(std::cin, DOB);

		if (DOB.length() != 10) {	//check to make sure string is the right length
			check = true;
		}
		else {
			if (DOB[2] != 47 || DOB[5] != 47) {	//check to see if / is in the right place
				check = true;
			}
			else {
				std::string d, m, y;
				d += DOB[0];
				d += DOB[1];
				m += DOB[3];
				m += DOB[4];
				y += DOB[6];
				y += DOB[7];
				y += DOB[8];
				y += DOB[9];
				if (isint(d) && isint(m) && isint(y)) {	//check if each of the date parts are only numbers
					day = stoi(d);
					month = stoi(m);
					year = stoi(y);
					if (month > 0 && month < 13) {
						if (day > 0 && day <= MIndex[month - 1]) {
							if (year > 1900 && year < DOJ.year) {
								Date_Of_Birth.Change_Date_Manual(DOB);
								if (!Date_Check(Date_Of_Birth, DOJ)) {
									check = true;
								}
							}
							else {
								check = true;
							}
						}
						else {
							check = true;
						}
					}
					else {
						check = true;
					}
				}
				else {	//very top, if any of the date elements are not numbers
					check = true;
				}
			}
		}

		if (check) {
			clr();
			std::cout << "Invalid input, please enter a valid date\n";
			std::cout << "Possible issues include numbers that don't work (higher than 12 month, higher than 31 day),\nsingle digit dates (3 instead of 03), and dates below 18 years old\n";
		}

	} while (check);

	clr();

	std::cout << "Creating a new Admin\n";

	do {

		check = false;

		std::cout << "Enter new Admin Password: ";
		getline(std::cin, Password);
		for (int i = 0; i < Password.length(); i++) {
			if (Password[i] == ' ') {
				check = true;
				clr();
				std::cout << "Spaces are not allowed in Password, please try again\n";
				break;
			}
		}
	} while (check);

	clr();

	if (Rank == 11) {
		rank = "10";
		AID = "0";
	}
	else {

		std::cout << "Creating a new Admin\n";

		do {

			check = false;

			std::cout << "Enter new Admin Rank (Can not be equal or greater than own)\n";
			getline(std::cin, rank);
			if (!isint(rank)) {
				clr();
				std::cout << "Invalid, please enter a number";
			}
			else {
				std::string temp = rank;
				int x = stoi(temp);
				if (x >= Rank || x <= 0) {
					check = true;
					clr();
					std::cout << "Please enter a valid Admin Rank (greater than 0, less than own)\n";
				}
			}

		} while (check);

		clr();

		int temp = Admin_Data.back().getAID() + 1;
		AID = std::to_string(temp);

	}

	Admin NewA;

	NewA.Admin::Admin(AID, SSN, Username, Name, rank, Organization, Password, Date_Of_Birth, DOJ);

	Admin_Data.push_back(NewA);

}

void Admin::Delete_Admin() {

	//password is already entered & confirmed

	//select an admin to delete, EXIT to exit
	do
	{
		bool success = false;
		try
		{

			std::string admin_id;
			int current_admin_id = this->getAID();
			std::cout << "Select an admin to disable by entering their AID, enter \"EXIT\" to exit." << std::endl;
			std::getline(std::cin, admin_id);
			if (admin_id.compare("EXIT") == 0)
				break;
			int AID = atoi(admin_id.c_str());
			if (this->getAID() == AID)
			{
				system("CLS");
				std::cout << "You can't disable yourself..." << std::endl;
				continue;
			}
			else if (this->getRank() < Admin_Data.at(AID).getRank())
			{
				system("CLS");
				std::cout << "Unable to complete action, admin outranks you." << std::endl;
				continue;
			}
			else
			{
				Admin_Data.at(AID).Admin_Disable();
				success = true;
			}
		}
		catch (...)
		{
			std::cout << "Admin ID not valid. " << std::endl;
			continue;
		}
		if (success)
			break;
	} while (true);

}

void Customer::Transfer() {

	std::cout << "Transfer\n";

	do
	{
		bool success = false;
		float transfer;
		try
		{
			std::string input;

			int CID;
			std::cout << "Please enter Customer ID to transfer funds to: ";
			std::getline(std::cin, input);
			if (input.compare("EXIT") == 0)
				break;
			CID = atoi(input.c_str());
			if (this->getCID() == CID)
			{
				system("CLS");
				std::cout << "You can't transfer funds to yourself.";
				continue;
			}
			else
			{
				input.clear();
				std::cout << "Enter transfer amount: ";
				std::getline(std::cin, input);
				transfer = atof(input.c_str());
				Customer_Data.at(CID).Increase_Balance(transfer);
				this->Increase_Balance(-transfer);
				success = true;
			}
		}
		catch (...)
		{
			system("CLS");
			std::cout << "Customer does not exist." << std::endl;
			continue;
		}
		if (success)
		{
			std::string message1, message2;
			message1 = "Transfered $" + Currencystof(transfer) + " to CID " + std::to_string(CID);
			message2 = "Got Transfered $" + Currencystof(transfer) + " from CID " + std::to_string(CID);

			this->New_Message(message1);
			Customer_Data[CID].New_Message(message2);

			this->New_Transaction(transfer, "Transfer (out)");
			Customer_Data[CID].New_Transaction(transfer, "Transfer (in)");
			break;
		}

	} while (true);
}

void Save_Data() {

	std::ofstream Admin_Data_Out;
	Admin_Data_Out.open("Admin_Data.txt");
	for (int i = 0; i < Admin_Data.size(); i++) {
		Admin_Data_Out << Admin_Data[i];
	}
	Admin_Data_Out.close();
	std::ofstream Customer_Data_Out;
	Customer_Data_Out.open("Customer_Data.txt");
	for (int i = 0; i < Customer_Data.size(); i++) {
		Customer_Data_Out << Customer_Data[i];
	}
	Customer_Data_Out.close();

}

std::ofstream& operator << (std::ofstream& out, Admin& Ad) {

	std::string aid, rank;

	aid = std::to_string(Ad.AID);

	rank = std::to_string(Ad.Rank);

	out << "AID: " << encryption(aid) << std::endl;

	std::string ssn, temp;
	// Admin_Data_Out << Admin
	temp = std::to_string(Ad.SSN);
	for (int i = 0; i < 3; i++) {
		ssn.push_back(temp[i]);
	}
	ssn.push_back('-');
	for (int i = 3; i < 5; i++) {
		ssn.push_back(temp[i]);
	}
	ssn.push_back('-');
	for (int i = 5; i < 9; i++) {
		ssn.push_back(temp[i]);
	}
	out << "SSN: " << encryption(ssn) << std::endl;

	out << "Username: " << encryption(Ad.Username) << std::endl;

	out << "Name: " << encryption(Ad.Name) << std::endl;

	out << "Rank: " << encryption(rank) << std::endl;

	out << "Organization: " << encryption(Ad.Organization) << std::endl;

	out << "Password: " << encryption(Ad.Password) << std::endl;

	out << "Date-Of-Birth: " << encryption(Ad.Date_Of_Birth.date_formatted) << std::endl;

	out << "Date-Of-Join: " << encryption(Ad.Date_Of_Join.date_formatted) << std::endl;

	if (Ad.disabled)
		out << "DISABLED: " << encryption("true");
	else
		out << "DISABLED: " << encryption("false");

	out << "\n";

	return out;

}

std::ofstream& operator << (std::ofstream& out, Customer& Cu) {

	std::string cid, strikes, tempt;

	cid = std::to_string(Cu.CID);

	strikes = std::to_string(Cu.Strikes);

	out << "CID: " << encryption(cid) << std::endl;

	out << "Strikes: " << encryption(strikes) << std::endl;

	std::string ssn, temp;

	temp = std::to_string(Cu.SSN);
	for (int i = 0; i < 3; i++) {
		ssn.push_back(temp[i]);
	}
	ssn.push_back('-');
	for (int i = 3; i < 5; i++) {
		ssn.push_back(temp[i]);
	}
	ssn.push_back('-');
	for (int i = 5; i < 9; i++) {
		ssn.push_back(temp[i]);
	}
	out << "SSN: " << encryption(ssn) << std::endl;

	out << "Username: " << encryption(Cu.Username) << std::endl;

	out << "Name: " << encryption(Cu.Name) << std::endl;

	out << "Account_Type: " << encryption(Cu.Account_Type) << std::endl;

	out << "Status: " << encryption(Cu.Status) << std::endl;

	out << "Organization: " << encryption(Cu.Organization) << std::endl;

	out << "Date_Of_Birth: " << encryption(Cu.Date_Of_Birth.date_formatted) << std::endl;

	out << "Date_Of_Join: " << encryption(Cu.Date_Of_Join.date_formatted) << std::endl;

	out << "Password: " << encryption(Cu.Password) << std::endl;

	out << "Current_Balance: " << encryption(Currencystof(Cu.Current_Balance)) << std::endl;

	out << "Messages: ";

	for (int i = 0; i < Cu.Messages.size(); i++) {

		if (i != Cu.Messages.size() - 1) {

			out << encryption(space_to_dash(Cu.Messages[i])) << encryption(";");

		}
		else {

			out << encryption(space_to_dash(Cu.Messages[i]));

		}

	}

	out << "\nTransactions: ";

	for (int i = 0; i < Cu.Transactions.size(); i++) {

		tempt = std::to_string(Cu.Transactions[i]);

		if (i != Cu.Transactions.size() - 1) {

			out << encryption(tempt) << encryption(";");

		}
		else {

			out << encryption(tempt);

		}

	}

	out << "\nTransaction_Types: ";

	for (int i = 0; i < Cu.Transaction_Types.size(); i++) {

		if (i != Cu.Transaction_Types.size() - 1) {

			out << encryption(space_to_dash(Cu.Transaction_Types[i])) << encryption(";");

		}
		else {

			out << encryption(space_to_dash(Cu.Transaction_Types[i]));

		}

	}

	out << "\n\n";

	return out;

}

void Customer_Signup() {

	std::string Username, Name, Account_Type, Organization, SSN, Password;
	std::string CID, DOB;
	date DOJ;
	date Date_Of_Birth;
	bool check;
	Customer NewC;

	clr();

	std::cout << "Creating a new customer\n";

	do {

		check = false;

		std::cout << "Enter new customer username: ";
		getline(std::cin, Username);
		for (int i = 0; i < Username.length(); i++) {
			if (Username[i] == ' ') {
				check = true;
				clr();
				std::cout << "Spaces are not allowed in username, please try again\n";
				break;
			}
		}
		for (int i = 0; i < Customer_Data.size(); i++) {
			if (Customer_Data[i].Check_Username(Username)) {
				check = true;
				clr();
				std::cout << "Username is already taken, please try a different Username\n";
				break;
			}
		}

	} while (check);
	clr();

	std::cout << "Creating a new customer\n";

	std::cout << "Enter new customer name: ";
	getline(std::cin, Name);

	clr();

	std::cout << "Creating a new customer\n";

	do {

		check = false;

		std::cout << "Enter new customer account type (Business/Personal): ";
		getline(std::cin, Account_Type);
		if (Account_Type != "Personal" && Account_Type != "Business") {
			check = true;
			clr();
			std::cout << "Invalid input, please enter Business or Personal\n";
		}

	} while (check);

	clr();

	std::cout << "Creating a new customer\n";

	std::cout << "Enter new customer organization: ";
	getline(std::cin, Organization);

	clr();

	std::cout << "Creating a new customer\n";

	do {

		check = false;

		int day, month, year;

		std::cout << "Enter new customer date of birth (DD/MM/YYYY): ";
		getline(std::cin, DOB);

		if (DOB.length() != 10) {	//check to make sure string is the right length
			check = true;
		}
		else {
			if (DOB[2] != 47 || DOB[5] != 47) {	//check to see if / is in the right place
				check = true;
			}
			else {
				std::string d, m, y;
				d += DOB[0];
				d += DOB[1];
				m += DOB[3];
				m += DOB[4];
				y += DOB[6];
				y += DOB[7];
				y += DOB[8];
				y += DOB[9];
				if (isint(d) && isint(m) && isint(y)) {	//check if each of the date parts are only numbers
					day = stoi(d);
					month = stoi(m);
					year = stoi(y);
					if (month > 0 && month < 13) {
						if (day > 0 && day <= MIndex[month-1]) {
							if (year > 1900 && year < DOJ.year) {
								Date_Of_Birth.Change_Date_Manual(DOB);
								if (!Date_Check(Date_Of_Birth, DOJ)) {
									check = true;
								}
							}
							else {
								check = true;
							}
						}
						else {
							check = true;
						}
					}
					else {
						check = true;
					}
				}
				else {	//very top, if any of the date elements are not numbers
					check = true;
				}
			}
		}

		if (check) {
			clr();
			std::cout << "Invalid input, please enter a valid date\n";
			std::cout << "Possible issues include numbers that don't work (higher than 12 month, higher than 31 day),\nsingle digit dates (3 instead of 03), and dates below 18 years old\n";
		}

	} while (check);
	
	clr();

	std::cout << "Creating a new customer\n";

	do {

		check = false;

		std::cout << "Enter new customer Social Security number (xxx-xx-xxxx): ";
		getline(std::cin, SSN);

		if (SSN.length() != 11) {
			check = true;
		}
		else {
			if (SSN[3] != '-' || SSN[6] != '-') {
				check = true;
			}
			else {
				std::string SocTemp;
				for (int i = 0; i < 11; i++) {
					if (i != 3 && i != 6) {
						SocTemp.push_back(SSN[i]);
					}
				}
				if (!(isint(SocTemp))) {
					check = true;
				}
			}
		}

		if (check) {
			clr();
			std::cout << "Invalid input, please enter a string with the valid form\n";
		}

	} while (check);

	clr();

	std::cout << "Creating a new customer\n";

	do {

		check = false;

		std::cout << "Enter new customer Password: ";
		getline(std::cin, Password);
		for (int i = 0; i < Password.length(); i++) {
			if (Password[i] == ' ') {
				check = true;
				clr();
				std::cout << "Spaces are not allowed in Password, please try again\n";
				break;
			}
		}
	} while (check);

	CID = std::to_string(Customer_Data.size());
	std::string Status = "Active";
	std::string Current_Balance = "100";
	std::string Strikes = "0";

	NewC.Customer::Customer(CID, Strikes, SSN, Username, Name, Account_Type, Status, Organization, Date_Of_Birth, DOJ, Password, Current_Balance);
	NewC.New_Message("Welcome. Initial deposit of 100");
	NewC.New_Transaction(100, "Initial Deposit");
	Customer_Data.push_back(NewC);

	clr();
	std::cout << "New customer has been created";
	pause();

}

// CUSTOMER INTERFACE - KEVIN

void Customer_Home(int ID) // PARAMETER: Link userID to the homepage functions
{
	clr();
	Customer_Data[ID].Display_Name();
	while (true) // LOOP: Infinite loop to ensure start and end at customer homepage
	{
		std::string Input;
		int Selection;
		bool check;
		do // LOOP: Do-while Loop to ensure valid inputs
		{
			check = false; // FUNCTIONALITY: Disables loop initially in preparation for potential later re-enabling incase of invalid input

			std::cout << "Choose what you would like to do\n";
			std::cout << "--- 1 --- Statement Summary\n";
			std::cout << "--- 2 --- Check Balance\n";
			std::cout << "--- 3 --- Withdraw\n";
			std::cout << "--- 4 --- Deposit\n";
			std::cout << "--- 5 --- Transfer to other Account\n";
			std::cout << "--- 6 --- Display Messages\n";
			std::cout << "--- 7 --- Logout and save\n";
			std::cout << "Selection: ";
			getline(std::cin, Input);

			if (!isint(Input)) // CONDITION: Checks if the input is an integer
			{
				check = true; // FUNCTIONALITY: Re-enables infinite loop due to invalid input
				clr();
				std::cout << "Invalid: Please enter an integer\n";
			}
			else
			{
				Selection = stoi(Input);
				if (Selection < 1 || Selection > 7) // CONDITION: Checks if the input is a valid selection
				{
					check = true; // FUNCTIONALITY: Re-enables infinite loop due to invalid input
					clr();
					std::cout << "Invalid: Please enter a valid selection";
				}
			}
		} while (check);

		clr();

		// FUNCTIONALITY: Page Redirection
		// NOTE: Consider switching to switch case for more efficiency and nicer looking code

		if (Selection == 1)
		{
			if (Customer_Data[ID].Check_Password())
			{
				Customer_Data[ID].Statement_Summary();
				pause();
			}
		}
		else if (Selection == 2)
		{
			if (Customer_Data[ID].Check_Password())
			{
				Customer_Data[ID].Display_Balance();
			}
		}
		else if (Selection == 3)
		{
			if (Customer_Data[ID].Check_Password())
			{
				Customer_Data[ID].Withdraw();
			}
		}
		else if (Selection == 4)
		{
			if (Customer_Data[ID].Check_Password())
			{
				Customer_Data[ID].Deposit();
			}
		}
		else if (Selection == 5)
		{
			if (Customer_Data[ID].Check_Password())
			{
				Customer_Data[ID].Transfer();
			}
		}
		else if (Selection == 6)
		{
			if (Customer_Data[ID].Check_Password())
			{
				Customer_Data[ID].Message_Summary();
			}
		}
		else if (Selection == 7)
		{
			Save_Data();
			break;
		}
	}
}

void Customer_Login() {

	std::string Input;
	bool check = false, exit = false;
	int ID;

	clr();

	do {
		std::cout << "Enter Customer Username: ";
		getline(std::cin, Input);
		if (Input == "EXIT") {
			exit = true;
		}
		else {
			for (int i = 0; i < Customer_Data.size(); i++) {
				check = Customer_Data[i].Check_Username(Input);
				if (check) {
					ID = i;
					break;
				}
			}
		}

		if (!check) {
			clr();
			std::cout << "Invalid Customer Username: Please try again or enter 'EXIT' to leave\n";
		}

	} while (!(check || exit));

	clr();

	if (!exit) {

		check = Customer_Data[ID].Check_Password();

	}

	if (check) {
		Customer_Home(ID);
	}

	return;

}

// ADMIN INTERFACE - KEVIN

void Admin_Home(int ID) // PARAMETER: Links homepage with userID
{
	clr();
	Admin_Data[ID].Display_Name();
	int size = Customer_Data.size();

	while (true) // LOOP: Infinite loop to ensure the admin home interface starts and ends at the same place
	{
		std::string input;
		int selection;
		bool check;
		do // LOOP: Do-While loop to ensure valid input
		{
			check = false; // FUNCTIONALITY: Breaks infinite loop early on

			std::cout << "Choose a function you would like to execute\n";
			int i = Admin_Data[ID].getRank();	// FUNCTIONALITY: Gets the rank of the logged in admin and checks its rank for their respective capabilities
			if (i >= 1) {
				std::cout << "--- 1 --- Logout of Admin page and save\n";
			}
			if (i >= 2) {
				std::cout << "--- 2 --- Check accounts with positive balance\n";
				std::cout << "--- 3 --- Check accounts with negative balance\n";
			}
			if (i >= 4) {
				std::cout << "--- 4 --- Generate summary report\n";
			}
			if (i >= 5) {
				std::cout << "--- 5 --- Send Warning message to negative accounts\n";
			}
			if (i >= 6) {
				std::cout << "--- 6 --- Pay monthly interest to accounts\n";
			}
			if (i >= 7) {
				std::cout << "--- 7 --- Block accounts with repeated negative balance\n";
			}
			if (i >= 8) {
				std::cout << "--- 8 --- Create new Admin\n";
			}
			if (i >= 9) {
				std::cout << "--- 9 --- Delete Admin\n";
			}

			std::cout << "Selection: ";
			getline(std::cin, input);
			if (!isint(input)) // CONDITION: Checks if the input is an integer
			{
				check = true; // FUNCTIONALITY: Re-enables infinite loop due to invalid input
				clr();
				std::cout << "Invalid: Please enter an integer";
			}
			else
			{
				selection = stoi(input);
				if (selection > Admin_Data[ID].getRank() || selection < 1) // CONDITION: Checks if the input is in range to be valid
				{
					check = true; // FUNCTIONALITY: Re-enables infinite loop due to invalid input
					clr();
					std::cout << "Invalid: Please enter a valid selection";
				}
			}

		} while (check);

		clr();

		int Active = 0, Inactive, Positive = 0, Negative;

		// FUNCTIONALITY: Page Redirection
		// NOTE: Might switch these to case structures for more efficiency and cleaner looking code

		if (selection == 1)
		{
			Save_Data();
			break;
		}
		else if (selection == 2)
		{
			if (Admin_Data[ID].Check_Password())
			{
				for (int i = 0; i < size; i++)
				{
					Customer_Data[i].Positive_Display();
				}
				pause();
			}
		}
		else if (selection == 3)
		{
			if (Admin_Data[ID].Check_Password())
			{
				for (int i = 0; i < size; i++)
				{
					Customer_Data[i].Negative_Display();
				}
				pause();
			}
		}
		else if (selection == 4)
		{
			if (Admin_Data[ID].Check_Password())
			{
				std::cout << "Total Customers: " << size << "\n";
				for (auto i : Customer_Data)
				{
					if (i.Active_Check())
					{
						Active++;
					}
					if (i.Positive_Check())
					{
						Positive++;
					}
				}
				Inactive = size - Active;
				Negative = size - Positive;
				std::cout << "Total Active Customers: " << Active << "\n";
				std::cout << "Total Inactive Customer: " << Inactive << "\n";
				std::cout << "Total Positive Accounts: " << Positive << "\n";
				std::cout << "Total Negative Accounts: " << Negative << "\n";
				pause();
			}
		}
		else if (selection == 5)
		{
			if (Admin_Data[ID].Check_Password())
			{
				for (int i = 0; i < size; i++)
				{
					if (!Customer_Data[i].Positive_Check())
					{
						Customer_Data[i].New_Message("Warning, account negative at checkin");
					}
				}
			}
		}
		else if (selection == 6)
		{
			if (Admin_Data[ID].Check_Password())
			{
				for (int i = 0; i < size; i++)
				{
					Customer_Data[i].Pay_Interest();
				}
			}
		}
		else if (selection == 7)
		{
			if (Admin_Data[ID].Check_Password())
			{
				for (int i = 0; i < size; i++)
				{
					if (Customer_Data[i].Strike_Check())
					{
						Customer_Data[i].Block_Account();
					}
				}
			}
		}
		else if (selection == 8)
		{
			if (Admin_Data[ID].Check_Password())
			{
				Admin_Data[ID].Create_Admin();
			}
		}
		else if (selection == 9)
		{
			if (Admin_Data[ID].Check_Password())
			{
				Admin_Data[ID].Delete_Admin();
			}
		}
	}
}

void Admin_Login() {

	std::string Input;
	bool check = false, exit = false;
	int ID;

	clr();

	do {

		std::cout << "Enter Admin Username: ";
		getline(std::cin, Input);
		if (Input == "EXIT")
			break;
		else 
		{
			for (auto i : Admin_Data) 
			{
				if (i.Check_Username(Input)) 
				{
					ID = i.getAID();
					check = true;
					break;
				}
			}
		}

		if (!check) {
			clr();
			std::cout << "Invalid Admin Username, please try again or enter 'EXIT' to leave. " << std::endl;
		}

	} while (!(check));

	clr();

	if (check && !Admin_Data[ID].admin_is_disabled()) {

		if (Admin_Data[ID].Check_Password())
			Admin_Home(ID);
	}

	else {
		return;
	}
	return;
}

int main() {

	std::ifstream Admin_Data_In;

	Admin_Data_In.open("Admin_Data.txt");

	Admin_Data_In.seekg(0, std::ios::end);

	int length = Admin_Data_In.tellg();

	Admin_Data_In.seekg(0, std::ios::beg);

	if (length == 0) {
		std::cout << "Welcome. No Admin is on file. Please Create first Admin (Creator)\n";
		Admin TemporaryAdmin;
		date DOB, DOJ;
		TemporaryAdmin.Admin::Admin("0", "111-11-1111", "NA", "NA", "11", "NA", "NA", DOB, DOJ);
		TemporaryAdmin.Create_Admin();
	}
	else {

		std::vector<std::string> AID, SSN, Username, Name, Rank, Organization, Password, DOB, DOJ, disabled;

		if (Admin_Data_In.is_open()) {
			int i = 1;	
			int j = 1;
			std::string abc;
			while (!Admin_Data_In.eof()) {
				Admin_Data_In >> abc;
				if (i % 2 == 0) {
					if (j % 10 == 1) {
						AID.push_back(abc);
					}
					else if (j % 10 == 2) {
						SSN.push_back(abc);
					}
					else if (j % 10 == 3) {
						Username.push_back(abc);
					}
					else if (j % 10 == 4) {
						Name.push_back(abc);
					}
					else if (j % 10 == 5) {
						Rank.push_back(abc);
					}
					else if (j % 10 == 6) {
						Organization.push_back(abc);
					}
					else if (j % 10 == 7) {
						Password.push_back(abc);
					}
					else if (j % 10 == 8) {
						DOB.push_back(abc);
					}
					else if (j % 10 == 9) {
						DOJ.push_back(abc);
					}
					else if (j % 10 == 0) {
						disabled.push_back(abc);
					}
					j++;
				}
				i++;
			}
		}

		date Date_Of_Birth, Date_Of_Join;

		for (int i = 0; i < AID.size(); i++) {
			AID[i] = decryption(AID[i]);
			SSN[i] = decryption(SSN[i]);
			Username[i] = decryption(Username[i]);
			Name[i] = decryption(Name[i]);
			Rank[i] = decryption(Rank[i]);
			Organization[i] = decryption(Organization[i]);
			Password[i] = decryption(Password[i]);
			DOB[i] = decryption(DOB[i]);
			DOJ[i] = decryption(DOJ[i]);
			disabled[i] = decryption(disabled[i]);
		}

		for (int i = 0; i < AID.size(); i++) {
			Date_Of_Birth.Change_Date_Manual(DOB[i]);
			Date_Of_Join.Change_Date_Manual(DOJ[i]);
			Admin Admin;
			Admin.Admin::Admin(AID[i], SSN[i], Username[i], Name[i], Rank[i], Organization[i], Password[i], Date_Of_Birth, Date_Of_Join, disabled[i]);
			Admin_Data.push_back(Admin);
		}

	}

	Admin_Data_In.close();

	std::ifstream Customer_Data_In;

	Customer_Data_In.open("Customer_Data.txt");

	std::vector<std::string> CID, Strikes, SSN, Username, Name, Account_Type, Status, Organization, DOB, DOJ, Password, Current_Balance, messages, transaction, transaction_types;

	if (Customer_Data_In.is_open()) {

		int i = 1;
		int j = 1;
		std::string abc;

		while (!Customer_Data_In.eof()) {
			Customer_Data_In >> abc;
			if (i % 2 == 0) {
				if (j % 15 == 1) {
					CID.push_back(abc);
				}
				if (j % 15 == 2) {
					Strikes.push_back(abc);
				}
				if (j % 15 == 3) {
					SSN.push_back(abc);
				}
				if (j % 15 == 4) {
					Username.push_back(abc);
				}
				if (j % 15 == 5) {
					Name.push_back(abc);
				}
				if (j % 15 == 6) {
					Account_Type.push_back(abc);
				}
				if (j % 15 == 7) {
					Status.push_back(abc);
				}
				if (j % 15 == 8) {
					Organization.push_back(abc);
				}
				if (j % 15 == 9) {
					DOB.push_back(abc);
				}
				if (j % 15 == 10) {
					DOJ.push_back(abc);
				}
				if (j % 15 == 11) {
					Password.push_back(abc);
				}
				if (j % 15 == 12) {
					Current_Balance.push_back(abc);
				}
				if (j % 15 == 13) {
					messages.push_back(abc);
				}
				if (j % 15 == 14) {
					transaction.push_back(abc);
				}
				if (j % 15 == 0) {
					transaction_types.push_back(abc);
				}
				j++;
			}
			i++;
		}
	}

	for (int i = 0; i < CID.size(); i++) {
		CID[i] = decryption(CID[i]);
		Strikes[i] = decryption(Strikes[i]);
		SSN[i] = decryption(SSN[i]);
		Username[i] = decryption(Username[i]);
		Name[i] = decryption(Name[i]);
		Account_Type[i] = decryption(Account_Type[i]);
		Status[i] = decryption(Status[i]);
		Organization[i] = decryption(Organization[i]);
		DOB[i] = decryption(DOB[i]);
		DOJ[i] = decryption(DOJ[i]);
		Password[i] = decryption(Password[i]);
		Current_Balance[i] = decryption(Current_Balance[i]);
		messages[i] = decryption(messages[i]);
		transaction[i] = decryption(transaction[i]);
		transaction_types[i] = decryption(transaction_types[i]);
	}

	Customer_Data_In.close();
	
	for (int i = 0; i < CID.size(); i++) {

		messages[i] = dash_to_space(messages[i]);
		std::vector<std::string> Messages = string_to_vector(messages[i]);

		transaction_types[i] = dash_to_space(transaction_types[i]);
		std::vector<std::string> Transaction_Types = string_to_vector(transaction_types[i]);

		std::vector<std::string> temp = string_to_vector(transaction[i]);
		std::vector<float> Transactions = Transaction_Convert(temp);

		date Date_Of_Birth, Date_Of_Join;

		Date_Of_Birth.Change_Date_Manual(DOB[i]);
		Date_Of_Join.Change_Date_Manual(DOJ[i]);

		Customer Customer;
		Customer.Customer::Customer(CID[i], Strikes[i], SSN[i], Username[i], Name[i], Account_Type[i], Status[i], Organization[i], Date_Of_Birth, Date_Of_Join, Password[i], Current_Balance[i]);

		for (int j = 0; j < Messages.size(); j++) {

			Customer.New_Message(Messages[j]);

		}

		for (int j = 0; j < Transactions.size(); j++) {

			Customer.New_Transaction(Transactions[j], Transaction_Types[j]);

		}

		Customer_Data.push_back(Customer);

	}

	// MAIN INTERFACE - KEVIN


	if (Admin_Data.empty())
	{
		std::cout << "Welcome. No Admin is on file. Please Create first Admin (Creator, rank 10)\n";
		Admin TemporaryAdmin;
		date DOB, DOJ;
		TemporaryAdmin.Admin::Admin("0", "111-11-1111", "NA", "NA", "11", "NA", "NA", DOB, DOJ);
		TemporaryAdmin.Create_Admin();
	}

	while (true) // LOOP: Infinite loop to ensure the whole program starts and exits at the main interface
	{
		std::string input;
		do // LOOP: Do-While to ensure a valid input is inputted for proper page redirection
		{
			std::cout << "Welcome to Computer Science C++ Programmers Banking system\n";
			std::cout << "Which page would you like to direct to?\n";
			std::cout << "Admin Login (Enter 1)\n";
			std::cout << "Customer Sign In (Enter 2)\n";
			std::cout << "Customer Sign Up (Enter 3)\n";
			std::cout << "Close Application (Enter 4)\n";
			std::cout << "Selection: ";
			std::getline(std::cin, input);

			if (!(input == "1" || input == "2" || input == "3" || input == "4")) // CONDITION: If invalid input, error message
			{
				clr();
				std::cout << "Invalid input, please enter one of the specified page numbers\n";
			}
		} while (!(input == "1" || input == "2" || input == "3" || input == "4")); // CONDITION: Exits main hub if input is valid

		// FUNCTIONALITY: Page Redirection
		// NOTE: Might change this to a switch case cause this seems a bit inefficient and messy
		if (input == "1")
		{
			Admin_Login();
		}

		else if (input == "2")
		{
			Customer_Login();
		}

		else if (input == "3")
		{
			Customer_Signup();
		}
		else
		{
			Save_Data();
			break; // EXIT: Only means of breaking the infinite loop
		}
	}
}