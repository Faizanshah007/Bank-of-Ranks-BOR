#include<iostream>
#include<fstream>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

using namespace std;

char ans = 'y', cs, chbk = 'n'; int p = 0, gc = 0;
class Account
{
private:
	int pin;
public:
	char custname[100];
	float accno;
	float oppbal;
	int visit;
	char rating[6];

	Account()
	{
		strcpy_s(rating, "-----");
	}

	void setpin()
	{
		cout << "Set 4 digit Pin "; cin >> pin;
	}

	int getpin()
	{
		return pin;
	}

	void accept()
	{
		char c;
		cout << "Name "; 
		while ((c = getchar()) != '\n' && c != EOF) {}
		fgets(custname,100,stdin);
		cout << "Account No. "; cin >> accno;
		setpin();
		cout << "Opening Balance "; cin >> oppbal;
	}

	void display()
	{
		cout << "\nVisit Summary:\n";
		cout << "\nName " << custname;
		cout << "Account No. " << accno << endl;
		cout << "Opening Balance " << oppbal << endl;
		cout << "No of times visited " << p << endl;
		cout << "Rating " << rating << endl;
	}

	void deposit()
	{
		float x;
		cout << "How much you want to deposit \n";
		cin >> x;
		oppbal += x;
	}

	void withdraw()
	{
		float w;
		cout << "How much you want to withdraw \n";
		cin >> w;
		if (oppbal - w<0)
		{
			cout << "\nNot able to withdraw\n";
		}
		else
			oppbal -= w;
	}
};

class Current : public Account
{
	int checkbk;

public:

	void checkbook()
	{
		++checkbk;
		cout << "\nYou have borrowed " << checkbk << " checkbook('s)\n";
	}

	void penalty()
	{
		if (strcmp(rating, "*****") != 0)
		{
			if (oppbal<1000)
			{
				cout << "\nDeducting penalty(Rs100) for balance less than 1000\n";
				if (oppbal - 100<0)
					oppbal = 0;
				else
					oppbal -= 100;
			}
		}

	}
}cur, testc;

class Savings : public Account
{
public:

	void interest()
	{
		float t, r, ci;
		cout << "Year passed from the opening date :";
		cin >> t;
		if (strcmp(rating, "*****") == 0)
		{
			r = 10;
		}
		else
			r = 5;
		ci = oppbal * (pow((1 + (r / 400)), (4 * t)));
		oppbal = ci;
	}
}sav, tests;

char ratingup(char fg)
{
	int z = p / 3;
	if (z <= 5)
	{
		for (int i = 0; i<z; ++i)
		{
			if (fg == 'c')
				cur.rating[i] = '*';
			else
				sav.rating[i] = '*';
		}
	}
	return 0;
}

int passkey; float g; char s = 'f', enter, choicedw, inputer, choicedw1, inputer1;

void main()
{
start:
	cout << "              ______________ %BRIEFING%_____________   \n\n";
	cout << "          Welcome  to most popular bank - 'Bank Of Ranks' (BOR)\n";
	cout << "     There are two types of account available for opening:-\n";
	cout << "      1) Savings:-\n";
	cout << "         features:\n";
	cout << "          i] Avail Interest\n";
	cout << "         ii] Withdraw money\n";
	cout << "        iii] Deposit Money\n\n";
	cout << "      2) Current:-\n";
	cout << "         features:\n";
	cout << "          i] Borrow Checkbooks\n";
	cout << "          ii] Withdraw money\n";
	cout << "        iii] Deposit Money\n";
	cout << "         iv] Maintain minimum Balance( Otherwise penalty applicable )\n\n";
	cout << " Customers will be getting 'BOR RATINGS' on the bases of their no. of visits\n";
	cout << " Customer those who will complete 5-star rating will not be deducted in case of penalty( if you are a current user )";
	cout << " and they will get 10% interest (for saving account users)...\n\n";
	cout << "!!!!!!!!!!!!!!!!!!!!! HAPPY BANKING !!!!!!!!!!!!!!!!!!!!!!!!!!\n";
	cout << "Enter 0 to continue\n";
	cout << "Enter any other character to exit\n";
	cin >> enter;
	if (enter != '0')
	{
		exit(0);
	}
	fstream fin, fout, file;
	cout << "Are you a new user(y/n)\n";
	cin >> ans;
	cout << "Current/Saving(c/s)\n";
	cin >> cs;
	if (ans == 'y')
	{
		if (cs == 'c')
		{
			cur.accept();
			file.open("BankC.dat", ios::in | ios::out | ios::binary | ios::app);
			while (!file.eof())
			{
				file.read((char*)&testc, sizeof(testc));
				if (cur.accno == testc.accno)
				{
					cout << "Account No. already exists\n"; file.close(); gc = 1; goto uu;
				}
			}
			file.close();
			file.open("BankS.dat", ios::in | ios::out | ios::binary | ios::app);
			while (!file.eof())
			{
				file.read((char*)&sav, sizeof(sav));
				if (cur.accno == sav.accno)
				{
					cout << "Account no. already exists\n"; gc = 1; goto uu;
				}
			}
		uu:
			file.close();
			if (gc == 1)
			{
				goto go;
			}
			cur.visit = 1;
			p = cur.visit;
			fout.open("BankC.dat", ios::out | ios::binary | ios::app);
			fout.write((char*)&cur, sizeof(cur));
			fout.close();
			cur.penalty();
			strcpy_s(cur.rating, "-----");
			cur.display();
		}

		if (cs == 's')
		{
			sav.accept();
			file.open("BankS.dat", ios::in | ios::out | ios::binary | ios::app);
			while (!file.eof())
			{
				file.read((char*)&tests, sizeof(tests));
				if (sav.accno == tests.accno)
				{
					cout << "Account no. already exists\n"; gc = 1; goto vv;
				}
			}
			file.close();
			file.open("BankC.dat", ios::in | ios::out | ios::binary | ios::app);
			while (!file.eof())
			{
				file.read((char*)&cur, sizeof(cur));
				if (cur.accno == sav.accno)
				{
					cout << "Account no. already exists\n"; gc = 1; goto vv;
				}
			}
		vv:
			file.close();
			if (gc == 1)
			{
				goto go;
			}
			sav.visit = 1;
			p = sav.visit;
			fout.open("BankS.dat", ios::out | ios::binary | ios::app);
			fout.write((char*)&sav, sizeof(sav));
			fout.close();
			strcpy_s(sav.rating, "-----");
			sav.display();
		}
	}

	if (ans == 'n')
	{
		if (cs == 'c')
		{
			cout << "Enter account no. \n";
			cin >> g;
			cout << "Enter 4 digit pin \n";
			cin >> passkey;
			file.open("BankC.dat", ios::in | ios::out | ios::binary);
			float pos;
			while (!file.eof())
			{
				pos = file.tellg();
				file.read((char*)&cur, sizeof(cur));
				if (file.eof())
				{
					cout << "Record not found \n"; file.close(); goto go;
				}
				if (cur.accno == g)
				{
					s = 's'; p = cur.visit; break;
				}
			}
			if (cur.getpin() != passkey)
			{
				cout << "\n\nINVALID PIN\n\n"; _getch(); file.close(); goto start;
			}
			if (s == 's')
			{
			u:
				cout << "Want to deposit or withdraw(d/w)\n";
				cin >> choicedw;
				if (choicedw == 'w' || choicedw == 'W')
				{
					cur.withdraw();
				}
				else if (choicedw == 'd' || choicedw == 'D')
				{
					cur.deposit();
				}
				else
				{
					cout << "Invalid Input" << " ....Want to Exit or Re enter input(e/r)\n";
					cin >> inputer;
					if (inputer == 'r' || inputer == 'r') { goto u; }
					else { file.close(); goto start; }
				}
				++p;
				ratingup('c');
				cur.penalty();
				cout << "\nWant check book(y/n)\n";
				cin >> chbk;
				if (chbk == 'y')
					cur.checkbook();
				cur.display();
				file.seekg(pos);
				cur.visit = p;
				file.write((char*)&cur, sizeof(cur));
			}
			file.close();
		}
		if (cs == 's')
		{
			cout << "Enter account no. \n";
			cin >> g;
			cout << "Enter 4 digit pin \n";
			cin >> passkey;
			file.open("BankS.dat", ios::in | ios::out | ios::binary);
			float pos;
			while (!file.eof())
			{
				pos = file.tellg();
				file.read((char*)&sav, sizeof(sav));
				if (file.eof())
				{
					cout << "Record not found\n"; file.close(); goto go;
				}
				if (sav.accno == g)
				{
					s = 's'; p = sav.visit; break;
				}
			}
			if (sav.getpin() != passkey)
			{
				cout << "\n\nINVALID PIN\n\n"; _getch(); file.close(); goto start;
			}
			if (s == 's')
			{
			x:
				cout << "Want to deposit or withdraw(d/w)\n";
				cin >> choicedw1;
				if (choicedw1 == 'w' || choicedw1 == 'W')
				{
					sav.withdraw();
				}
				else if (choicedw1 == 'd' || choicedw1 == 'D')
				{
					sav.deposit();
				}
				else
				{
					cout << "Invalid Input" << " ....Want to Exit or Re enter input(e/r)\n";
					cin >> inputer1;
					if (inputer1 == 'r' || inputer1 == 'r') { goto x; }
					else { exit(0); }
				}
				++p;
				ratingup('s');
				sav.interest();
				sav.display();
				file.seekg(pos);
				sav.visit = p;
				file.write((char*)&sav, sizeof(sav));
			}
			file.close();
		}
	}
go:
	char op;
	cout << "\n\nWE VALUE $ERVICE AND M@NEY\n\n";
	cout << "THANKS FOR VISITING WANT TO VISIT AGAIN ENTER y\n";
	cout << "Enter any other character to exit\n";
	cin >> op;
	if (op == 'y')
		goto start;
	_getch();
}
