#include <iostream>
#include <string.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <bits/stdc++.h> 
#include <unistd.h>
#ifdef __linux__
#include <pwd.h>
#include <termios.h>
#endif

using namespace std;

void journal(string, string);
void editentries(string, string);
void root(void);


void decorate(int space, int num)
{
	for(unsigned int i = 0; i < space; i++)
	{
		cout << " ";
	} 
	for(unsigned int i = 0; i < num; i++)
	{
		cout << "-";
	}
	cout << endl;
}


char * string_to_charr(string str)
{
	int usize = str.length();
	char str2arr[usize + 1];
	strcpy(str2arr, str.c_str());
	char *username = str2arr;
	return username;
}


string lower(string str)
{
	string lc;
	for (unsigned int i = 0; i < str.length(); i++)
	{
		if (str[i] >= 'A' and str[i] <= 'Z')
		{
			lc += char(int(str[i]) + 32);
		}
		else
		{
			lc += str[i];
		}
	}
	return lc;
}


string trim(string s)
{
	bool q = true;
	while (q)
	{
		if (s[0] == ' ')
			s = s.substr(1, s.length());
		else
			q = false;
	}
	q = true;
	while (q)
	{
		if (s[s.length() - 1] == ' ')
			s = s.substr(0, (s.length() - 1));
		else
			q = false;
	}
	return s;
}


vector<string> split(string s, string ele)
{
	unsigned int pos = 0, c = 0;
	string temp, t = s;
	vector<string> splitted;
	for (unsigned int i = 0; i <= s.length(); i++)
	{
		pos = t.find(ele);
		if (pos == 4294967295)
		{
			break;
		}
		t = t.substr(pos + 1, t.length() - pos);
		c++;
	}
	for (unsigned int i = 0; i <= c; i++)
	{
		pos = s.find(ele);
		temp = s.substr(0, pos);
		splitted.push_back(temp);
		s = s.substr(pos + 1, s.length() - pos);
	}
	return splitted;
}


string replace(string s, string ele, string rep)
{
	unsigned int pos = 0, c = 0;
	string temp, spt, t = s;
	for (unsigned int i = 0; i < t.length(); i++)
	{
		pos = t.find(ele);
		if (pos == 4294967295)
		{
			break;
		}
		t = t.substr(pos + 1, t.length() - pos);
		c++;
	}
	for (unsigned int i = 0; i < c; i++)
	{
		pos = s.find(ele);
		temp = s.substr(0, pos);
		spt += temp + rep;
		s = s.substr(pos + 1, s.length() - pos);
	}
	spt += s;
	return spt;
}


char enshift(char ch, unsigned short shift)
{
	short ind;
	char shifted;
	int newshift;
	string alpha = "abcdefghijklmnopqrstuvwxyz";
	ind = alpha.find(ch);
	if (shift >= (alpha.length() - ind))
	{
		newshift = shift - (alpha.length() - ind);
		shifted = alpha[newshift];
	}
	else
	{
		shifted = alpha[ind + shift];
	}
	return shifted;
}


char deshift(char ch, unsigned short shift)
{
	short ind;
	char shifted;
	int newshift, tempshift;
	string temp, alpha = "abcdefghijklmnopqrstuvwxyz";
	ind = alpha.find(ch);
	temp = alpha.substr(0, ind + 1);
	tempshift = temp.length();
	if (shift >= tempshift)
	{
		newshift = shift - tempshift;
		shifted = alpha[25 - newshift];
	}
	else
	{
		shifted = alpha[ind - shift];
	}
	return shifted;
}


vector<string> encrypt(string u, string p)
{
	unsigned int shift;
	string uencrypt, pencrypt, alpha = "abcdefghijklmnopqrstuvwxyz";
	char s;
	for (unsigned int i = 0; i < p.length(); i++)
	{
		if (p[i] >= '1' && p[i] <= '9')
		{
			shift = p[i];
			shift -= 48;
			break;
		}
		else if (p[i] == '0')
		{
			shift = (int(p[i - 1]) - int('0')) % 10;
		}
	}
	for (unsigned int i = 0; i < u.length(); i++)
	{
		for (int j = 0; j < 26; j++)
		{
			if (alpha.find(u[i]) != string::npos)
			{
				s = enshift(u[i], shift);
				uencrypt += s;
				break;
			}
			else
			{
				uencrypt += char(int(u[i]) + shift);
				break;
			}
		}
	}
	for (unsigned int i = 0; i < p.length(); i++)
	{
		for (int j = 0; j < 26; j++)
		{
			if (alpha.find(p[i]) != string::npos)
			{
				s = enshift(p[i], shift);
				pencrypt += s;
				break;
			}
			else if (p[i] != char(shift + 48))
			{
				if (p[i] == '0')
				{
					pencrypt += p[i];
					break;
				}
				else
				{
					pencrypt += char(int(p[i]) + shift);
					break;
				}
			}
			else
			{
				pencrypt += p[i];
				break;
			}
		}
	}
	vector<string> encrypted;
	encrypted.push_back(uencrypt);
	encrypted.push_back(pencrypt);
	return encrypted;
}


vector<string> decrypt(string u, string p)
{
	unsigned int shift;
	string udecrypt, pdecrypt, alpha = "abcdefghijklmnopqrstuvwxyz";
	char s;
	for (unsigned int i = 0; i < p.length(); i++)
	{
		if (p[i] >= '1' && p[i] <= '9')
		{
			shift = p[i];
			shift -= 48;
			break;
		}
		else if (p[i] == '0')
		{
			shift = (int(p[i - 1]) - int('0')) % 10;
		}
	}
	for (unsigned int i = 0; i < u.length(); i++)
	{
		for (int j = 0; j < 26; j++)
		{
			if (alpha.find(u[i]) != string::npos)
			{
				s = deshift(u[i], shift);
				udecrypt += s;
				break;
			}
			else
			{
				udecrypt += char(int(u[i]) - shift);
				break;
			}
		}
	}
	for (unsigned int i = 0; i < p.length(); i++)
	{
		for (int j = 0; j < 26; j++)
		{
			if (alpha.find(p[i]) != string::npos)
			{
				s = deshift(p[i], shift);
				pdecrypt += s;
				break;
			}
			else if (p[i] != char(shift + 48))
			{
				if (p[i] == '0')
				{
					pdecrypt += p[i];
					break;
				}
				else
				{
					pdecrypt += char(int(p[i]) - shift);
					break;
				}
			}
			else
			{
				pdecrypt += p[i];
				break;
			}
		}
	}
	vector<string> decrypted;
	decrypted.push_back(udecrypt);
	decrypted.push_back(pdecrypt);
	return decrypted;
}


bool checkuser(string user)
{
	bool q;
	q = true;
	vector<string> decrypted;
	string line;
	#ifdef __linux__
	uid_t uid = getuid();
	struct passwd *pw = getpwuid(uid);
	string filepath = pw->pw_dir;
	#elif _WIN64
	string filepath = getenv("USERPROFILE");
	#endif
	chdir(filepath.c_str());
	chdir("cJournal");
	ifstream ud;
	ud.open("udata.txt");
	while (getline(ud, line))
	{
		vector<string> splitted;
		splitted = split(line, " ");
		decrypted = decrypt(splitted[0], splitted[1]);
		if (user == decrypted[0])
		{
			q = false;
			return q;
		}
		else
		{
			continue;
		}
	}
	return q;
}


int getch() 
{
    int ch;
    struct termios t_old, t_new;
    tcgetattr(STDIN_FILENO, &t_old);
    t_new = t_old;
    t_new.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t_new);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &t_old);
    return ch;
}


string getpass(const char *prompt, bool show_asterisk = true)
{
  const char BACKSPACE=127;
  const char RETURN=10;
  string password;
  unsigned char ch=0;
  cout << prompt;
  while((ch = getch()) != RETURN)
    {
       if(ch == BACKSPACE)
         {
            if(password.length() != 0)
              {
                 if(show_asterisk)
                 cout << "\b \b";
                 password.resize(password.length() - 1);
              }
         }
       else
         {
             password += ch;
             if(show_asterisk)
                 cout << '*';
         }
    }
  cout << endl;
  return password;
}


void cdlinux(void)
{
	uid_t uid = getuid();
	struct passwd *pw = getpwuid(uid);
	string filepath = pw->pw_dir;
	chdir(filepath.c_str());
	chdir("cJournal");
}


string finddate(void)
{
	const int MAXLEN = 80;
	char s[MAXLEN];
	time_t t = time(0);
	strftime(s, MAXLEN, "%d.%m.%Y", localtime(&t));
	return s;
}


int countoccur(string s, string ele)
{
	unsigned int pos = 0, c = 0;
	string temp, t = s;
	for (unsigned int i = 0; i <= s.length(); i++)
	{
		pos = t.find(ele);
		if (pos == 4294967295)
		{
			break;
		}
		t = t.substr(pos + 1, t.length() - pos);
		c++;
	}
	return c++;
}


bool checklinenum(string num, string date, string pass)
{
	string line, alpha = "abcdefghijklmnopqrstuvwxyz";
	vector<string> splitted, decrypted;
	unsigned int c = 0, k = 0;
	if ((num[num.length() - 1] == ',') or (num[0] == ','))
	{
		return false;
	}
	for (unsigned int i = 0; i < num.length() - 1; i++)
	{
		if ((num[i] == ',') and (num[i + 1] == ','))
		{
			return false;
		}
		if ((alpha.find(num[i]) != string::npos) or (alpha.find(num[i + 1]) != string::npos))
		{
			return false;
		}
	}
	unsigned int ln = countoccur(num, ",");
	splitted = split(num, ",");
	ifstream temp;
	temp.open(date);
	while (getline(temp, line))
	{
		c++;
	}
	temp.close();
	line = "";
	string linenum[c];
	ifstream file;
	file.open(date);
	while (getline(file, line))
	{
		decrypted = decrypt(line, pass);
		linenum[k] = decrypted[0][0];
		k++;
	}
	file.close();
	bool b = false;
	for (unsigned int i = 0; i <= ln; i++)
	{
		for (unsigned int j = 0; j < c; j++)
		{
			if (splitted[i] == linenum[j])
			{
				b = true;
				break;
			}
			else
			{
				b = false;
				continue;
			}
		}
		if (splitted[i] == num.substr(num.length() - 1, num.length()))
		{
			break;
		}
		if (!b)
		{
			return false;
		}
	}
	if (b)
		return true;
	else
		return false;
}


bool checkdate(string date)
{
	bool c;
	c = false;
	vector<string> splitted;
	splitted = split(date, "/");
	string temp = splitted[2];
	if (temp.length() > 4)
	{
		c = false;
		return c;
	}
	int dd, mm;
	long int yyyy;
	dd = stoi(splitted[0]);
	mm = stoi(splitted[1]);
	yyyy = stoi(splitted[2]);
	int m30[] = {4, 6, 9, 11};
	int m31[] = {1, 3, 5, 7, 8, 10, 12};
	for (unsigned int i = 0; i < sizeof(m30); i++)
	{
		if (m30[i] == mm)
		{
			if ((dd > 0) and (dd <= 30))
			{
				c = true;
			}
		}
	}
	for (unsigned int i = 0; i < sizeof(m31); i++)
	{
		if (m31[i] == mm)
		{
			if ((dd > 0) and (dd <= 31))
			{
				c = true;
			}
		}
	}
	if (mm == 2)
	{
		if (yyyy % 4 == 0)
		{
			if ((dd > 0) and (dd <= 29))
			{
				c = true;
			}
		}
		else if (yyyy % 4 != 0)
		{
			if ((dd > 0) and (dd <= 28))
			{
				c = true;
			}
		}
	}
	return c;
}


void listentries(string user, string pass)
{
	cdlinux();
	vector<string> namemonths{" ", "January", "Feburary", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
	vector<string> encrypted;
	encrypted = encrypt(user, pass);
	char *username = string_to_charr(encrypted[0]);
	chdir(username);
	string file;
	vector<string> filenames;
	struct dirent *dirp;
	uid_t uid = getuid();
	struct passwd *pw = getpwuid(uid);
	string filepath = pw->pw_dir;
	filepath = filepath + "/cJournal/" + encrypted[0];
	char *path = string_to_charr(filepath);
	DIR *dir = opendir(path);
	while ((dirp = readdir(dir)) != NULL) 
	{
		file = dirp->d_name;
		filenames.push_back(file);
	}
	closedir(dir);
	if (filenames.size() == 2)
	{
		decorate(5, 62);
		cout << "     NO ENTRIES TO BE LISTED" << endl;
		decorate(0, 67);
		cout << "\n";
		return;
	}
	vector<string> splitted, days, months, years;
	for(unsigned int i = 0; i < filenames.size(); i++)
	{
		if (filenames[i].length() == 14)
		{
			splitted = split(filenames[i], ".");
			days.push_back(splitted[0]);
			months.push_back(splitted[1]);
			years.push_back(splitted[2]);
		}
	}
	cout << "   > ENTRIES ON THIS JOURNAL: " << endl;
	decorate(5, 62);
	for(unsigned int i = 0; i < filenames.size() - 2; i++)
	{
		cout<< "     > ";
		if (days[i][1] == '1')
		{
			cout << days[i] << "st";
		}
		else if (days[i][1] == '2')
		{
			cout << days[i] << "nd";
		}
		else if (days[i][1] == '3')
		{
			cout << days[i] << "rd";
		}
		else
		{
			cout << days[i] << "th";
		}
		cout << ", " << namemonths[stoi(months[i])] << ", " << years[i] << endl;
		decorate(5, 62);
	}
	decorate(0, 67);
	cout << "\n";
}


void editentries(string user, string pass)
{
	cdlinux();
	vector<string> encrypted;
	encrypted = encrypt(user, pass);
	char *username = string_to_charr(encrypted[0]);
	chdir(username);
	bool t = false;
	string choice;
	string goback = "@" + user;
	string prompt = "     $edit@" + user + ":> ";
	while (t == false)
	{
		try
		{
			cout << prompt;
			getline(cin, choice);
		}
		catch (...)
		{
			continue;
		}
		choice = lower(choice);
		choice = trim(choice);
		decorate(5, 62);
		if (choice == "del")
		{
			bool v = false;
			string d;
			while (v == false)
			{
				cout << "          Date (dd/mm/yyyy):> ";
				try
				{
					getline(cin, d);
					int pos;
					pos = d.find("/");
					if (pos == -1)
					{
						decorate(10, 57);
						cout << "          > INVALID DATE" << endl;
						decorate(10, 57);
						continue;
					}
				}
				catch (...)
				{
					continue;
				}
				try
				{
					if (checkdate(d))
					{
						v = true;
					}
					else
					{
						throw - 1;
					}
				}
				catch (...)
				{
					decorate(10, 57);
					cout << "          > INVALID DATE" << endl;
					decorate(10, 57);
				}
			}
			string datefile;
			d = replace(d, "/", ".");
			datefile = d + ".txt";
			ifstream entry;
			entry.open(datefile);
			string line;
			vector<string> decry;
			if (entry)
			{
				decorate(10, 57);
				cout << "          > ENTRIES ON THIS DAY: " << endl;
				decorate(10, 57);
				while (getline(entry, line))
				{
					decry = decrypt(line, pass);
					cout << "          " <<decry[0] << endl;
				}
				entry.close();
				decorate(10, 57);
			}
			else
			{
				decorate(10, 57);
				cout << "          > NO ENTRIES ON THIS DAY" << endl;
				decorate(5, 62);
				continue;
			}
			string l1;
			vector<string> decrypted;
			bool t1 = false;
			string takenum;
			while (t1 == false)
			{
				cout << "        > Entry number(s): ";
				try
				{
					getline(cin, takenum);
					if (takenum == "")
					{
						continue;
					}
				}
				catch (...)
				{
					continue;
				}
				if (checklinenum(takenum, datefile, pass))
				{
					t1 = true;
				}
				else
				{
					decorate(10, 57);
					cout << "          INVALID ENTRY NUMBERS(S)." << endl;
					decorate(10, 57);
				}
			}
			string lines, x, y;
			vector<string> splitted, decrypting, alllines, removal, remlines;
			splitted = split(takenum, ",");
			unsigned int taken = countoccur(takenum, ",");
			sort(splitted.begin(), splitted.end());
			int i = 0, l = taken;
			ifstream file;
			file.open(datefile);
			while (getline(file, lines))
			{
				decrypting = decrypt(lines, pass);
				alllines.push_back(decrypting[0]);
				i++;
			}
			for (unsigned int i = 0; i <= taken; i++)
			{
				x = splitted[i];
				for (unsigned int j = 0; j < alllines.size(); j++)
				{
					y = alllines[j];
					if (y.find(x) == 0)
					{
						removal.push_back(y);
						break;
					}
				}
				l--;
			}
			for (unsigned int i = 0; i < removal.size(); i++)
			{
				for (unsigned int j = 0; j <= alllines.size(); j++)
				{
					if (removal[i] == alllines[j])
					{
						alllines.erase(alllines.begin() + j);
						break;
					}
				}
			}
			if (alllines.empty())
			{
				remove(datefile.c_str());
			}
			else
			{
				int temp = 1;
				ofstream finaldel(datefile);
				vector<string> finalout;
				for (unsigned int i = 0; i < alllines.size(); i++)
				{
					x = alllines[i];
					x[0] = '0' + temp;
					alllines[i] = x;
					finalout = encrypt(alllines[i], pass);
					finaldel << finalout[0] << endl;
					temp++;
				}
				finaldel.close();
			}
			decorate(5, 62);
			cout << "     ENTRY(S) DELETED SUCCESSFULLY\n";
			decorate(5, 62);
			cout << "\n";
		}
		else if (choice == "add")
		{
			bool v = false;
			string d;
			while (v == false)
			{
				cout << "          Date (dd/mm/yyyy):> ";
				try
				{
					getline(cin, d);
					int pos;
					pos = d.find("/");
					if (pos == -1)
					{
						decorate(10, 57);
						cout << "          > INVALID DATE" << endl;
						decorate(10, 57);
						continue;
					}
				}
				catch (...)
				{
					continue;
				}
				try
				{
					if (checkdate(d))
					{
						v = true;
					}
					else
					{
						throw - 1;
					}
				}
				catch (...)
				{
					decorate(10, 57);
					cout << "          > INVALID DATE" << endl;
					decorate(10, 57);
				}
			}
			string datefile;
			d = replace(d, "/", ".");
			datefile = d + ".txt";
			ifstream entry;
			entry.open(datefile);
			if (entry)
			{
				string line;
				vector<string> decrypted;
				decorate(10, 57);
				cout << "          ENTRIES ON THIS DAY: " << endl;
				decorate(10, 57);
				while (getline(entry, line))
				{
					decrypted = decrypt(line, pass);
					cout << "          " <<decrypted[0] << endl;
				}
				entry.close();
				decorate(10, 57);
			}
			else
			{
				decorate(10, 57);
				cout << "          NO ENTRIES ON THIS DAY" << endl;
				decorate(10, 57);
			}
			string addline;
			bool t = false;
			while(t == false)
			{
				cout << "          ADD:> ";
				try
				{
					getline(cin, addline);
				}
				catch (...)
				{
					continue;
				}
				if (addline == "")
				{
					continue;
				}
				t = true;
			}
			string line, last;
			vector<string> splitted, encrypted, decrypted;
			ifstream ud;
			ud.open(datefile);
			if (!ud)
			{
				ofstream ud(datefile, ios::out | ios::app);
				ud.close();
			}
			ud.seekg(0, ios::end);
			int filesize;
			filesize = ud.tellg();
			ud.close();
			if (filesize == -1)
			{
				vector<string> encrypted;
				addline = "1 | " + addline;
				encrypted = encrypt(addline, pass);
				ofstream udate(datefile, ios::out | ios::app);
				udate << encrypted[0] << endl;
				udate.close();
			}
			else
			{
				ifstream ud;
				ud.open(datefile);
				while (getline(ud, line))
				{
					last = line;
				}
				ud.close();
				decrypted = decrypt(last, pass);
				splitted = split(decrypted[0], " | ");
				int lastn = stoi(splitted[0]);
				lastn += 1;
				string lastnum = to_string(lastn);
				addline = lastnum + " | " + addline;
				encrypted = encrypt(addline, pass);
				ofstream udate(datefile, ios::out | ios::app);
				udate << encrypted[0] << endl;
				udate.close();
			}
			decorate(5, 62);
			cout << "     ENTRY(S) ADDED SUCCESSFULLY\n";
			decorate(5, 62);
			cout << "\n";
		}
		else if (choice == "help")
		{
			cout << "     Type any of these commands:\n";
			decorate(5, 62);
			cout << "\t1. add: Add entries under a date.\n\t2. del: Delete entries under a date.\n\t3. clear: Clears the screen.\n\t4. @username: Go back to your user profile.\n\t5. @root: Go back to root profile.\n\t6. kill: Quits cJournal." << endl;
			decorate(5, 62);
			cout << "\n";
		}
		else if (choice == "kill")
		{
			decorate(0, 67);
			cout << "\n";
			exit(0);
		}
		else if (choice == "clear")
		{
			cout << "\033[2J\033[1;1H";
		}
		else if (choice == goback)
		{
			decorate(0, 67);
			cout << "\n";
			journal(user, pass);
		}
		else if (choice == "@root")
		{
			decorate(0, 67);
			cout << "\n";
			root();
		}
		else
		{
			cout << "     \'" << choice << "\':" << " Command not found. Type \'help\' for more info" << endl;
			decorate(5, 62);
		}
	}
}


void journal(string user, string pass)
{
	cdlinux();
	vector<string> encrypted;
	encrypted = encrypt(user, pass);
	char *username = string_to_charr(encrypted[0]);
	chdir(username);
	string choice, prompt, entryin;
	prompt = "@" + user + ":> ";
	bool q = false;
	string date, datefilename;
	date = finddate();
	datefilename = date + ".txt";
	while (q == false)
	{
		cout << prompt;
		getline(cin, choice);
		choice = lower(choice);
		choice = trim(choice);
		if (choice == "entry")
		{
			decorate(0, 67);
			bool temp = false;
			while (temp == false)
			{
				cout << "     Entry:> ";
				getline(cin, entryin);
				decorate(0, 67);
				if (entryin != "")
				{
					temp = true;
				}
			}
			ifstream entry;
			entry.open(datefilename);
			if (!entry)
			{
				ofstream entry(datefilename, ios::out | ios::app);
				entry.close();
			}
			entry.seekg(0, ios::end);
			int filesize;
			filesize = entry.tellg();
			entry.close();
			if (filesize == -1)
			{
				vector<string> encrypted;
				entryin = "1 | " + entryin;
				encrypted = encrypt(entryin, pass);
				ofstream udate(datefilename, ios::out | ios::app);
				udate << encrypted[0] << endl;
				udate.close();
			}
			else
			{
				string line, last;
				vector<string> splitted, encrypted, decrypted;
				ifstream ud;
				ud.open(datefilename);
				while (getline(ud, line))
				{
					last = line;
				}
				ud.close();
				decrypted = decrypt(last, pass);
				splitted = split(decrypted[0], " | ");
				int lastn = stoi(splitted[0]);
				lastn += 1;
				string lastnum = to_string(lastn);
				entryin = lastnum + " | " + entryin;
				encrypted = encrypt(entryin, pass);
				ofstream udate(datefilename, ios::out | ios::app);
				udate << encrypted[0] << endl;
				udate.close();
			}
			cout << "> ENTRY WRITTEN SUCCESSFULLY\n";
			decorate(0, 67);
			cout << "\n";
		}
		else if (choice == "check")
		{
			decorate(0, 67);
			string d;
			string datefile;
			bool v = false;
			while (v == false)
			{
				cout << "     Date (dd/mm/yyy):> ";
				try
				{
					getline(cin, d);
					int pos;
					pos = d.find("/");
					if (pos == -1)
					{
						decorate(5, 62);
						cout << "   > INVALID DATE" << endl;
						decorate(5, 62);
						continue;
					}
				}
				catch (...)
				{
					continue;
				}
				try
				{
					if (checkdate(d))
					{
						v = true;
					}
					else
					{
						throw - 1;
					}
				}
				catch (...)
				{
					decorate(5, 62);
					cout << "   > INVALID DATE" << endl;
					decorate(5, 62);
				}
			}
			d = replace(d, "/", ".");
			datefile = d + ".txt";
			ifstream entry;
			entry.open(datefile);
			;
			if (entry)
			{
				string line;
				vector<string> decrypted;
				decorate(5, 62);
				cout << "     ENTRIES ON THIS DAY: " << endl;
				decorate(5, 62);
				while (getline(entry, line))
				{
					decrypted = decrypt(line, pass);
					cout << "     " <<decrypted[0] << endl;
				}
				entry.close();
			}
			else
			{
				decorate(0, 67);
				cout << "NO ENTRIES ON THIS DAY" << endl;
			}
			decorate(0, 67);
			cout << "\n";
		}
		else if (choice == "edit")
		{
			decorate(0, 67);
			editentries(user, pass);
		}
		else if (choice == "list")
		{
			decorate(0, 67);
			listentries(user, pass);
		}
		else if (choice == "kill")
		{
			decorate(0, 67);
			exit(0);
		}
		else if (choice == "clear")
		{
			cout << "\033[2J\033[1;1H";
		}
		else if (choice == "@root")
		{
			decorate(0, 67);
			cout << "\n";
			root();
		}
		else if (choice == "help")
		{
			decorate(0, 67);
			cout << "     > Type any of these commands:\n";
			decorate(5, 62);
			cout << "\t1. entry: Adds an entry for today.\n\t2. check: See all your entries under a particular date.\n\t3. edit: Add or delete entries under a particular date.\n\t4. list: Lists out all entries in your Journal.\n\t5. @root: Go back to root profile.\n\t6. clear: Clears the screen.\n\t7. kill: Quits cJournal.\n";
			decorate(0, 67);
			cout << "\n";
		}
		else
		{
			decorate(0, 67);
			cout << "\'" << choice << "\':" << " Command not found. Type \'help\' for more info" << endl;
			decorate(0, 67);
		}
		
	}
}

void actualsignup(string user, string pwd)
{
	vector<string> encrypted;
	encrypted = encrypt(user, pwd);
	#ifdef __linux__
	uid_t uid = getuid();
	struct passwd *pw = getpwuid(uid);
	string filepath = pw->pw_dir;
	#elif _WIN64
	string filepath = getenv("USERPROFILE");
	#endif
	chdir(filepath.c_str());
	mkdir("cJournal");
	chdir("cJournal");
	char *username = string_to_charr(encrypted[0]);
	mkdir(username);
	ofstream ud("udata.txt", ios::out | ios::app);
	string enuser, enpass;
	enuser = encrypted[0] + ' ';
	enpass = encrypted[1] + '\n';
	ud << enuser << enpass;
	ud.close();
	cout << "> USER CREDENTIALS SUCCESSFULLY WRITTEN" << endl;
	decorate(0, 67);
	cout << "\n";
}


void signup(void)
{
	bool q = false;
	string user;
	string pwd;
	int spaces;
	spaces = 0;
	while (q == false)
	{
		try
		{
			cout << "   > Username: ";
			getline(cin, user);
			decorate(5, 62);
			if (checkuser(user))
			{
				for (unsigned int i = 0; i < user.length(); i++)
				{
					if (user[i] == ' ')
					{
						spaces++;
					}
				}
				if (spaces == 0 and (user.length() >= 5 and user.length() <= 15))
				{
					q = true;
				}
				else
				{
					cout << "     Username should not contain spaces and should be 5-15 characters long." << endl;
					decorate(5, 62);
				}
			}
			else
			{
				cout << "     USERNAME ALREADY EXISTS" << endl;
				decorate(5, 62);
				continue;
			}
		}
		catch (...)
		{
			continue;
		}
	}
	q = false;
	string n = "0123456789";
	while (q == false)
	{
		int numbers;
		numbers = 0;
		try
		{
			#ifdef __linux__
			pwd = getpass("   > Password: ", true);
			#elif _WIN64
			cout << "   > Password: ";
			cin >> pwd;
			#endif
			for (unsigned int i = 0; i < pwd.length(); i++)
			{
				if (n.find(pwd[i]) < n.length())
				{
					numbers++;
				}
			}
			if (numbers > 0 and (pwd.length() >= 5 and pwd.length() <= 15))
			{
				q = true;
			}
			else
			{
				decorate(5, 62);
				cout << "     Password should have numbers and should be 5-15 characters long.\n";
				decorate(5, 62);
			}
			
		}
		catch (...)
		{
			continue;
		}
	}
	decorate(0, 67);
	actualsignup(user, pwd);
}


void actuallogin(string user, string pwd)
{
	bool c;
	c = false;
	string line;
	vector<string> splitted, decrypted;
	#ifdef __linux__
	uid_t uid = getuid();
	struct passwd *pw = getpwuid(uid);
	string filepath = pw->pw_dir;
	#elif _WIN64
	string filepath = getenv("USERPROFILE");
	#endif
	chdir(filepath.c_str());
	DIR* dir = opendir("cJournal");
	if (dir)
	{
		closedir(dir);
	}
	else if (ENOENT == errno)
	{
		decorate(0, 67);
		cout << "> NO USER CREDENTIALS AVAILABLE. USE \'signup\' COMMAND.\n";
		decorate(0, 67);
		cout << "\n";
		return;
	}
	ifstream ud;
	ud.open("udata.txt");
	while (getline(ud, line))
	{
		splitted = split(line, " ");
		decrypted = decrypt(splitted[0], splitted[1]);
		if ((decrypted[0] == user) and (decrypted[1] == pwd))
		{
			decorate(0, 67);
			cout << "> LOGIN SUCCESSFUL" << endl;
			decorate(0, 67);
			cout  << "\n";
			c = true;
			break;
		}
	}
	if (c == true)
	{
		/*	journal(user, pwd); */
		cout << "Logged in" << endl;
	}
	else
	{
		decorate(0, 67);
		cout << "> INVALID USER CREDENTIALS" << endl;
		decorate(0, 67);
		cout << "\n";
	}
	ud.close();
}


void login(void)
{
	bool v;
	string user, pwd;
	v = false;
	while (v == false)
	{
		try
		{
			cout << "   > Username: ";
			getline(cin, user);
			v = true;
		}
		catch (...)
		{
			continue;
		}
	}
	decorate(5, 62);
	v = false;
	while (v == false)
	{
		try
		{
			#ifdef __linux__
			pwd = getpass("   > Password: ", true);
			#elif _WIN64
			cout << "   > Password: ";
			cin >> pwd;
			#endif

			v = true;
		}
		catch (...)
		{
			continue;
		}
	}
	actuallogin(user, pwd);
}


void root()
{
	bool q;
	q = false;
	string choice;
	while (q == false)
	{
		try
		{
			cout << "@root:> ";
			getline(cin, choice);
			choice = lower(choice);
			choice = trim(choice);
			if (choice == "login")
			{
				decorate(0, 67);
				login();
			}
			else if (choice == "signup")
			{
				decorate(0, 67);
				signup();
			}
			else if (choice == "kill")
			{
				decorate(0, 67);
				cout << "\n";
				exit(0);
			}
			else if (choice == "quit")
			{
				decorate(0, 67);
				cout << "> Use \"kill\" instead.\n";
				decorate(0, 67);
			}
			else if (choice == "clear")
			{
				cout << "\033[2J\033[1;1H";
			}
			else if (choice == "help")
			{
				decorate(0, 67);
				cout << "     > To get started with cJournal, type any of these commands:\n";
				decorate(5, 62);
				cout << "\t1. signup: Creates a Journal for you.\n\t2. login: Logs you into your Journal.\n\t3. clear: Clears the screen.\n\t4. kill: Quits cJournal.\n";
				decorate(0, 67);
				cout << "> You can type \'help\' anywhere to get a list of all the commands.\n";
				decorate(0, 67);
				cout << "\n";
			}
			else if (choice == "")
			{
				continue;
			}
			else
			{
				decorate(0, 67);
				cout << "\'" << choice << "\':" << " Command not found. Type \'help\' for more info" << endl;
				decorate(0, 67);
			}
		}
		catch (...)
		{
			decorate(0, 67);
			cout << "> I'm sorry, something went wrong." << endl;
			decorate(0, 67);
			cout << "\n";
			continue;
		}
	}
}


int main(void)
{
	cout << "\n";
	decorate(0, 67);
	cout << "|                         cJournal v4.0                           |" << endl;
	decorate(0, 67);
	cout << "\n";
	root();
	return 0;
}
