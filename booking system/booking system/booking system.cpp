#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

typedef struct
{
	string  name;
	int place[17];
} structsessions;

vector<structsessions> sessions;
structsessions session;

void readsessions()
{
	ifstream read("sessionsgold.txt");
	if (!read.is_open())
	{
		cout << "can not find the file" << endl;
	}

	int time;
	int place;
	char package;
	while (!read.eof())
	{
		read >> session.name >> time >> place >> package;
		read.get();
		if (read.peek() == '/n')
		{
			break;
		}
		if (sessions.size() == 0)
		{
			sessions.push_back(session);
			//memset(sessions[sessions.size() - 1].place, 0, sizeof(int[17]));
			sessions[sessions.size() - 1].place[time] += place;
			sessions[sessions.size() - 1].place[2] = package;
			if (place)
			{
				sessions[sessions.size() - 1].place[0]++;
			}
		}
		else
		{
			bool flag = false;
			for (unsigned int i = 0; i < sessions.size(); i++)
			{
				if (session.name == sessions[i].name && package == sessions[i].place[2])
				{
					if (place && sessions[i].place[time] == 0)
					{
						sessions[i].place[0]++;
					}
					sessions[i].place[time] += place;
					flag = true;
					break;
				}
			}
			if (flag == false)
			{
				sessions.push_back(session);
				//memset(sessions[sessions.size() - 1].place, 0, sizeof(int[17]));
				sessions[sessions.size() - 1].place[time] += place;
				sessions[sessions.size() - 1].place[2] = package;
				if (place)
				{
					sessions[sessions.size() - 1].place[0]++;
				}
			}
		}
	}
	read.close();
}

void writesessionsList(void)
{
	ofstream write("sessionsList.txt");
	if (!write.is_open())
	{
		cout << "can not find the file" << endl;
	}
	else
	{
		for (unsigned int i = 0; i<sessions.size(); i++)
		{
			write << sessions[i].name << " \t";
			for (int t = 0; t<17; t++)
			{
				write << sessions[i].place[t] << "\t";
			}
			write << endl;
		}
	}
	write.flush();
	write.close();
}

void readsessionsList(void)
{
	ifstream read("sessionsList.txt");
	if (!read.is_open())
	{
		readsessions();
		writesessionsList();
		return;
	}

	while (true)
	{
		sessions.push_back(session);
		read >> sessions[sessions.size() - 1].name;
		for (int t = 0; t<17; t++)
		{
			read >> sessions[sessions.size() - 1].place[t];
		}
		if (read.eof())
		{
			sessions.pop_back();
			break;
		}
	}
	read.close();
}

void sessionslistShow()
{
	cout << "--------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "Id\t" << "Name\t\t" << "Time\t" << "Place" << endl;
	cout << "--------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	for (unsigned int i = 1; i<sessions.size(); i++)
	{
		bool flag = false;

		for (int t = 10; t<17; t++)
		{
			if (flag == true)
			{
				if (sessions[i].place[t])
				{
					cout << "\t\t\t";
					cout << t << "\t" << sessions[i].place[t] << endl;
				}
			}
			else
			{
				if (sessions[i].place[t])
				{
					cout << i << "\t" << sessions[i].name << " \t" << t << "\t" << sessions[i].place[t] << endl;
					sessions[i].place[1] = t;
					flag = true;
				}
			}
		}
	}
}

int checkInput(string beCheck) // check user input is string or number 
{
	int ret;
	try
	{
		ret = stoi(beCheck);
	}
	catch (exception const& e)
	{
		if (beCheck == "exit")
		{
			ret = 0;
		}
		else
		{
			ret = -1;
		}
	}
	return(ret);
}


int main()
{
	readsessionsList();
	//sessionslistShow();
	string firstname;
	string surname;
	int packageid;
	const string th[] = { "1st choise", "2nd choise", "3th choise", "4th choise", "5th choise" };
	int sessionid;
	int userentertime;
	int confirmnum;
	const int starttime = 10;
	while (true)
	{
		cout << "____________________________________________________________________________________________________________________________________________" << endl;
		cout << "********************************************************************************************************************************************" << endl;
		cout << "********************************************************************************************************************************************" << endl;
		cout << "Welcome to the online booking system." << endl;
		cout << "Please enter first name: ";
		cin >> firstname;
		if (firstname == "exit")
		{
			continue;
		}
		cout << "Please enter surname: ";
		cin >> surname;
		if (surname == "exit")
		{
			continue;
		}
		cout << "--------------------------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "There are two choices (Please enter 1 or 2 for the package or enter \"exit\" to exit the program)" << endl;
		cout << "--------------------------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "No.\t" << "Package\t\t" << "Place\t" << "Price\t" << "Note" << endl;
		cout << "--------------------------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "1)\tStandard\t\t$40\t" << "Must choose exactly four sessions to attend. This is not include the session called \"Welcome\"." << endl;
		cout << "2)\tGold        \t" << sessions[0].place[9] << "\t$60\t" << "Must choose exactly six sessions to attend. This must include the session called \"Welcome\" at 9am." << endl;
		cout << "--------------------------------------------------------------------------------------------------------------------------------------------" << endl;
		while (true)
		{
			cout << "Enter the package number please: ";
			string checkpackageid;
			cin >> checkpackageid;
			packageid = checkInput(checkpackageid);
			if (packageid < 0 || packageid>2)
			{
				cout << "Input error,try again." << endl;
				continue;
			}
			break;
		}
		if (packageid == 0)// exit the program
		{
			continue;
		}
		sessionslistShow();
		cout << "--------------------------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "Please enter the session ID." << endl;
		cout << "--------------------------------------------------------------------------------------------------------------------------------------------" << endl;
		int record[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

		for (int i = 0; i < 3 + packageid; i++)
		{
			while (true) // sessionid check if choise the same session
			{
				if (i != 0)
				{
					cout << "--------------------------------------------------------------------------------------------------------------------------------------------" << endl;
					for (int id = 0; id < i; id++)
					{
						cout << "Session " << sessions[record[id]].name << " have been selected." << endl;
					}
					cout << "--------------------------------------------------------------------------------------------------------------------------------------------" << endl;
				}
				cout << th[i] << ": ";
				string checksessionid;
				cin >> checksessionid;
				sessionid = checkInput(checksessionid);

				if (sessions[sessionid].place[0] == 1)
				{
					if (record[sessions[sessionid].place[1]] != 0)
					{
						cout << "The time you have been selected is not available,try again." << endl;
						continue;
					}
				}
				if (i != 0)
				{
					bool a = false;
					for (int id = 0; id < i; id++)
					{
						if (sessionid == record[id])
						{
							a = true;
							break;
						}
					}
					if (a == true)
					{
						cout << "Can not select the same session twice,try again. " << endl;
						continue;
					}
				}
				if (sessionid < 0 || sessionid >12)
				{
					cout << "Input error,try again." << endl;
					continue;
				}
				break;
			}
			if (sessions[sessionid].place[0] > 1)
			{
				while (true)                     // check user input session time 
				{
					cout << "Please select the time period: ";
					string checkuserentertime;
					cin >> checkuserentertime;
					userentertime = checkInput(checkuserentertime);
					if (userentertime < starttime || sessions[sessionid].place[userentertime] == 0 || userentertime >16)
					{
						cout << "The time you have been selected is not available,try again." << endl;
						continue;
					}
					if (record[userentertime] != 0)
					{
						cout << "You can't select the same time period for two different sessions." << endl;
						continue;
					}
					break;
				}
			}
			else if (sessions[sessionid].place[0] == 1)      // check if the user pick the same time 
			{
				for (int t = 10; t < 17; t++)
				{
					if (sessions[sessionid].place[t] != 0)
					{
						userentertime = t;
						break;
					}
				}
			}
			record[userentertime] = sessionid;
			record[i] = sessionid;
		}
		cout << "--------------------------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "This is the following session you have been chose" << endl;
		cout << "--------------------------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "Name \t\t" << "\tTime\t" << endl;
		cout << "--------------------------------------------------------------------------------------------------------------------------------------------" << endl;
		if (packageid == 2)
		{
			cout << sessions[0].name << "\t\t\t9" << endl;
		}
		for (int t = 10; t < 17; t++)
		{
			if (record[t] != 0)
			{
				cout << sessions[record[t]].name << "  \t\t" << t << endl;
			}
		}
		while (true) // check user input session time 
		{
			cout << "--------------------------------------------------------------------------------------------------------------------------------------------" << endl;
			cout << "Please enter 1)accept or 2)reject this plan." << endl;
			cout << "Please enter the num: ";
			string checkconfirmnum;
			cin >> checkconfirmnum;
			confirmnum = checkInput(checkconfirmnum);
			if (confirmnum != 1 && confirmnum != 2)
			{
				cout << "Input error,try again" << endl;
				continue;
			}
			break;
		}
		if (confirmnum == 2)
		{
			cout << "--------------------------------------------------------------------------------------------------------------------------------------------" << endl;
			continue;
		}
		if (packageid == 2)
		{
			sessions[0].place[9] -= 1;
		}
		for (int t = 10; t < 17; t++)
		{
			if (record[t] != 0)
			{
				sessions[record[t]].place[t] -= 1;
				if (sessions[record[t]].place[t] == 0)
				{
					sessions[record[t]].place[0] -= 1;
				}
			}
		}
		writesessionsList();
		string filename = surname + ".txt";
		ofstream write(filename);
		if (!write.is_open())
		{
			cout << "can not find the file" << endl;
		}
		else
		{
			write << firstname << "\t" << surname << endl;
			write << "------------------------------" << endl;
			write << "Name \t\t" << "\tTime\t" << endl;
			if (packageid == 2)
			{
				write << sessions[0].name << "\t\t\t9" << endl;
			}
			for (int t = 10; t < 17; t++)
			{
				if (record[t] != 0)
				{
					write << sessions[record[t]].name << "  \t\t" << t << endl;
				}
			}
		}
		write.flush();
		write.close();
		cout << "Please enter 0 to quit the program or enter 1 to continue." << endl;
		int quit;
		cin >> quit;
		if (quit == 0)
		{
			break;
		}
	}
}





