#define _USE_MATH_DEFINES
#include <iomanip>
#include <cmath>
#include <string.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <limits>

using namespace std;
typedef unsigned long long int ULLI;
typedef long long int LLI;
typedef unsigned int UI;
typedef long double LD;

// ################################################################
// # Universal coloring function string ccout(string) by RP  v0.0 #
// ################################################################
#include <sstream>
#include <iostream>
#ifdef __unix__
#include <curses>
string getBColor(char c){switch(c){case '0':return "40";case '1':return "44";case '2':return "42";case '3':return "46";case '4':return "41";case '5':return "45";case '6':return "43";case '7':return "47";case '8':return "100";case '9':return "104";case 'a':return "102";case 'b':return "106";case 'c':return "101";case 'd':return "105";case 'e':return "103";case 'f':return "107";default:return "255";}}string getFColor(char c){switch(c){case '0':return "30";case '1':return "34";case '2':return "32";case '3':return "36";case '4':return "31";case '5':return "35";case '6':return "33";case '7':return "37";case '8':return "90";case '9':return "94";case 'a':return "92";case 'b':return "96";case 'c':return "91";case 'd':return "95";case 'e':return "93";case 'f':return "97";default:return "255";}}
string ccout(string s){int l=s.length()-1;for(int i=0;i<l;++i){if(s[i]=='&'){cout<<"\033["<<getFColor(s[++i])<<"m";}else if(s[i]=='@'){cout<<"\033["<<getBColor(s[++i])<<"m";}else{cout<<s[i];}}if(l>=1&&(s[l-1]=='&'||s[l-1]=='@'))return "";else if(l>=0)cout<<s[l];return "";}
#else
#ifdef _WIN32
#include <windows.h>
#include <conio.h>
HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);char fcolor=15,bcolor=0;string ccout(string s){int c=0;for(int i=0;i<s.length()-1;++i){if(s[i]=='&'){cout.flush();c=s[++i];fcolor=c>=48&&c<=58?c-48:(c>=97&&c<=102?c-87:15);SetConsoleTextAttribute(hConsole,(bcolor<<4)+fcolor);}else if(s[i]=='@'){cout.flush();c=s[++i];bcolor=c>=48&&c<=58?c-48:(c>=97&&c<=102?c-87:15);SetConsoleTextAttribute(hConsole,(bcolor<<4)+fcolor);}else{cout<<s[i];}}if(s.length()>=2&&(s[s.length()-2]=='&'||s[s.length()-2]=='@'))return "";else if(s.length()>=1)cout<<s[s.length()-1];return "";}
#endif
#endif
//void testcolors(){ostringstream ss;for(int i=0;i<10;++i){for(int j=0;j<10;++j){ss<<"&"<<i<<"@"<<j<<"#";ccout(ss.str());ss.str("");}cout<<endl;}ccout("@0&f");}
void _(void) __attribute__ ((constructor));
// ################################################################
//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//char foreground_color=15, background_color=0;
//
//string ccout(string s) {
//	int color_code = 0;
//	int s_length_minus_1 = s.length()-1;
//	
//	for (int i=0; i < s_length_minus_1; ++i) {
//		if(s[i] == '&') {
//			cout.flush();
//			
//			color_code = s[++i];
//			foreground_color = (color_code>=48 && color_code<=58 ? color_code-48 : (color_code>=97 && color_code<=102 ? color_code-87 : 15));
//			
//			SetConsoleTextAttribute(hConsole, (background_color<<4) + foreground_color);
//		}
//		else if(s[i] == '@') {
//			cout.flush();
//			
//			color_code = s[++i];
//			background_color = (color_code>=48 && color_code<=58 ? color_code-48 : (color_code>=97 && color_code<=102 ? color_code-87 : 15));
//			
//			SetConsoleTextAttribute(hConsole, (background_color<<4) + foreground_color);
//		}
//		else {
//			cout << s[i];
//		}
//	}
//	
//	if (s_length_minus_1>=1 && (s[s_length_minus_1-1]=='&' || s[s_length_minus_1-1]=='@')) {
//		return "";
//	}
//	else if (s_length_minus_1 >= 0) {
//		cout << s[s_length_minus_1];
//	}
//	
//	return "";
//}
// ################################################################































int baseCoreHP[36] = {
	0,
	26000,
	36400,
	46440,
	66564,
	84924,
	110628,
	136332,
	134387,
	136187,
	185801,
	211508,
	238088,
	265824,
	295360,
	325104,
	354640,
	240240,
	265200,
	290160,
	315250,
	340210,
	415880,
	446368,
	477004,
	507640,
	538128,
	568764,
	435150,
	456890,
	480537,
	504184,
	527831,
	551478,
	575125,
	559600};



int getCoreHP(int floor) {
	if (floor > 976) {
		return getCoreHP(976) + (floor-976)*35*1000*1000 + ((floor%4-2)%2)*64;
	}
	if (floor > 945) {
		return getCoreHP(945) + (floor-945)*35*1000*1000;
	}
	if (floor > 35) {
		return getCoreHP(35) + (floor-35)*15*1000;
	}
	return baseCoreHP[floor <= 0 ? 0 : floor];
}



string listHealsAdvanced(int start_hp, int floor) {
	int maxhp = getCoreHP(floor);
	bool maxedcurr, maxedtotal;
	ostringstream ss;
	
	for (int heal = 1, currhp = (start_hp ? start_hp : maxhp), totalhp = maxhp; heal < 12; ++heal) {
		maxedcurr = maxedtotal = 0;
		
		if (currhp > maxhp) {
			currhp = maxhp;
			maxedcurr = 1;
		}
		if (totalhp > maxhp) {
			totalhp = maxhp;
			maxedtotal = 1;
		}
		
		if (heal % 2) {
			ss << "&e" << heal/2+1 << " (&7" << heal << "&e)&6:&e\t";
			ss << (maxedcurr ? "&a" : "&b") << currhp << "\t";
			ss << "&e(" << (maxedtotal ? "&a" : "&b") << totalhp << "&e)" << "\n";
		}
		else {
			ss << "&e  (&7" << heal << "&e)&6:&e\t";
			ss << (maxedcurr ? "&a" : "&b") << currhp << "\t";
			ss << "&e(" << (maxedtotal ? "&a" : "&b") << totalhp << "&e)" << "\n";
		}
		
		currhp += maxhp;
		totalhp += maxhp;
	}
	
	return ss.str();
}
string listHealsSimple(int start_hp, int floor) {
	int maxhp = getCoreHP(floor);
	bool maxedcurr, maxedtotal;
	ostringstream ss;
	
	for (int heal = 1, currhp = (start_hp ? start_hp : maxhp), totalhp = maxhp; heal < 12; ++heal) {
		maxedcurr = maxedtotal = 0;
		
		if (currhp > maxhp) {
			currhp = maxhp;
			maxedcurr = 1;
		}
		if (totalhp > maxhp) {
			totalhp = maxhp;
			maxedtotal = 1;
		}
		
		if (heal % 2) {
			ss << "&e" << heal/2+1 << "&6:&e\t";
			ss << (maxedcurr ? "&a" : "&b") << currhp << "\t";
			ss << "&e(" << (maxedtotal ? "&a" : "&b") << totalhp << "&e)" << "\n";
		}
		
		currhp += maxhp;
		totalhp += maxhp;
	}
	
	return ss.str();
}
string listHPs(int end, int start) {
	ostringstream ss;
	ss << "&e";
	for (int floor=start; floor<=end; ++floor) {
		ss << floor << "&6:&e\t" << getCoreHP(floor) << endl;
	}
	return ss.str();
}


bool isBiggerNumber(string s1, string s2) {
	const ULLI n1 = s1.length(), n2 = s2.length();
	
	if (n1 > n2) return true;
	else if (n1 < n2) return false;
	
	for (ULLI i=0; i<n1; ++i) {
		if (s1[i] > s2[i]) return true;
		else if (s1[i] < s2[i]) return false;
	}
	
	return false;
}
string inputCommand() {
	char current_char = 0;
	string input = "";
	
	while (true) {
		current_char = getch();
		
		switch (current_char) {
			case 13: case 32: {
				cout << endl;
				return input;
			}
			case 8: {
				if (input.length() > 0) {
					input = input.substr(0, input.length()-1);
					cout << '\b' << " " << '\b';
				}
				break;
			}
			case 104: case 119: case 108: {
				if (input.length() == 0) {
					ccout("&b");
				}
				input += current_char;
				cout << current_char;
				break;
			}
			case 97: {
				if (input.length() == 0) {
					ccout("&3");
				}
				input += current_char;
				cout << current_char;
				break;
			}
			case 101: {
				if (input.length() == 0) {
					ccout("&c");
				}
				input += current_char;
				cout << current_char;
				break;
			}
			default: {
				input += current_char;
				cout << current_char;
			}
		}
	}
}
int inputNumber(string message) {
	char current_char = 0;
	string input = "";
	
	ccout("&e" + message + ":\n  &b");
	
	while (true) {
		current_char = getch();
		
		switch (current_char) {
			case 13: case 32: {
				cout << " " << endl;
				
				bool negative = 0;
				if (input[0] == 45) {
					negative = 1;
					input = input.substr(1, input.length()-1);
				}
				
				bool valid_input = 1;
				for (int i=0; i<input.length(); ++i) {
					if (48 > input[i] || input[i] > 57) {
						valid_input = 0;
						input = "";
						ccout("&cInvalid input! Please enter a valid number:\n  &b");
						break;
					}
				}
				if (valid_input) {
					if (isBiggerNumber(input, "2147483647")) {
						input = "";
						ccout("&cInvalid input! Please enter a valid number (|n| < 2147483647):\n  &b");
					}
					else {
						return (negative ? -stoi(input) : stoi(input));
					}
				}
				
				break;
			}
			case 8: {
				if (input.length() > 0) {
					input = input.substr(0, input.length()-1);
					cout << '\b' << " " << " " << '\b' << '\b';
				}
				break;
			}
			case 48: case 49: case 50: case 51: case 52: case 53: case 54: case 55: case 56: case 57: {
				input += current_char;
				cout << current_char;
				break;
			}
			case 45: {
				if (input.length() == 0) {
					input += current_char;
					cout << current_char;
					break;
				}
			}
			default: {
				ccout("&cX");
				cout << '\b';
				ccout("&b");
			}
		}
	}
}
void showHelp() {
	ccout(string("") +
	"&eCommand list:\n" +
	"- &bhelp&e - shows this list\n" +
	"- &bwave&e - list 6 waves of core's HP values\n" +
	"- &blist&e - list core's max HP values for a range of floors\n" +
	"- &3adv&e  - list all 11 heals of core's HP values (&3advanced&e)\n" +
	"- &cexit&e - exits the program\n");
}
void func() {
	string inp;
	bool reopen = 1, loop = 1;
	
	showHelp();
	
	while (reopen) {
		ccout("\n> &b");
		inp = inputCommand();
		
		if (inp == "help") {
			showHelp();
			reopen = 1;
		}
		else if (inp == "wave") {
			ccout(listHealsSimple(
				inputNumber("Input starting core HP (0 = max HP)"),
				inputNumber("Input floor")));
		}
		else if (inp == "adv") {
			ccout(listHealsAdvanced(
				inputNumber("Input starting core HP (0 = max HP)"),
				inputNumber("Input floor")));
		}
		else if (inp == "list") {
			ccout(listHPs(
				inputNumber("End floor"),
				inputNumber("Starting floor")));
		}
		else if (inp == "loop") {
			loop = !loop;
			ccout(string("") + "&eLooping " + (loop ? "&aenabled" : "&cdisabled") + "&e.\n");
		}
		else if (inp == "exit") {
			break;
		}
		else {
			ccout("&cInvalid command\n&e");
			reopen = 1;
		}
		
		reopen = loop;
	}
}































// ################################################################
void _() {
	ios_base::sync_with_stdio(-1);
	srand(time(NULL));
	cout << fixed;
	cout << setprecision(4);
//	ccout("&8");
//	system("pause");
	ccout("&e");
	func();
//	ccout("\n&aDone!");
}
int main() {
	ccout("@0&7\n");
//	system("pause");
	return 0;
}

