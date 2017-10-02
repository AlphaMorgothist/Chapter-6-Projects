#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <ctime>
#include <Windows.h>

using namespace std;

//extras
void runShip1();
void runShip2();
void runCrit();
void typeSlow(string &str) {
	int length = str.size();
	for (int i = 0; i < length; i++)
	{
		if (str[i] == '\n') { Sleep(600); }
		Sleep(50);
		cout << str[i];
	}
}
int getInput() {
	cout << "\nSelection: ";
	int choice;
	cin >> choice;
	system("CLS");
	return choice;
}

//Classes
class Handheld {
public:
	void TogglePower();
	void DisplayGames();
	void Play() const;
	void SetGameNumber(int NewGameNumber);
	void RaiseVolume();
	void LowerVolume();
	void Options();
	int GetInput();
private:
	bool m_IsOn = false;
	int m_GameNumber = 0;
	int m_Volume = 5;
	static const int NUM_GAMES = 3;
	static const string GAMES[NUM_GAMES];
	static const int MIN_VOLUME = 0;
	static const int MAX_VOLUME = 10;


};
class Critter {
public:
	bool alive = true;
	Critter(string name, int hunger = 0, int boredom = 0);
	void Talk();
	int GetScore();
	int Eat(int food);
	void Play(int fun);
	int Work(string name, int tools);
	void debug();
	void Reset();
private:
	int m_Hunger;
	int m_Boredom;
	int m_Age = 0;
	int GetMood() const;
	void PassTime(int time = 1);
};
class Ship {
public:
	Ship(string name = "Enterprise", int fuel = 0);
	string name;
	int fuel;
	void Status();
	void Move(int dist);
	void Refuel();

};
class Hscore {
public:
	static const int NUM_ENTRIES = 5;
	string m_Names[NUM_ENTRIES];
	int m_Scores[NUM_ENTRIES];
	void Display();
	void SetDefaultEntries();
	void InsertEntry(string *name, int *score);
};

//Ship Functs
Ship::Ship(string name, int fuel) :
	name(name), fuel(fuel) {}
void Ship::Status()
{
	if (fuel < 0)  fuel = 0;
	cout << "\nShip Status:" << endl;
	cout << "\nName: " << name;
	cout << "\nFuel: " << fuel << endl;
}
void Ship::Move(int dist)
{
	if (fuel < dist) {
		cout << "\nYou try to move the ship, but the fuel is not sufficient too go that distance!" << endl;
	}
	if (fuel >= dist) {
		cout << "\nThe ship moves " << dist << " lightyears.\nRemaining fuel: " << fuel - dist;
		fuel -= dist;
	}
}
void Ship::Refuel()
{
	cout << "You refill your tank at the nearest space gas station" << endl;
	if (fuel >= 10) {
		cout << "\nYou are already at a full tank!" << endl;
	}
	else {
		fuel = 10;
	}
	Status();
	system("pause");
}

//Highscore Functs
void Hscore::Display()
{
	cout << "High Score Table:" << endl;
	for (int i = 0; i < NUM_ENTRIES; i++)
	{
		cout << "\nName: " << m_Names[i] << "\tScore: " << m_Scores[i];
	}
	cout << "\n\n";
}
void Hscore::SetDefaultEntries()
{
	for (int i = 0; i < NUM_ENTRIES; i++)
	{
		m_Names[i] = "Mikey";
	}
	for (int j = 0; j < NUM_ENTRIES; j++)
	{
		m_Scores[j] = 420;
	}
}
void Hscore::InsertEntry(string * name, int * score)
{
	bool changed = false;
	for (int i = 0; i < NUM_ENTRIES; i++)
	{
		if (*score > m_Scores[i] && changed == false) {
			m_Names[i] = *name;
			m_Scores[i] = *score;
			changed = true;
		}
	}
	
}

//Critter Functs
Critter::Critter(string name, int hunger, int boredom) :
	m_Hunger(hunger),
	m_Boredom(boredom)
{
	cout << "\nAn egg has hatched!" << endl;
	cout << "\nA new creature, named " << name << ", is born!\n" << endl;
}
void Critter::Talk()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 0x40);
	if (alive == false) {
		cout << "\nYour creature is dead. It can't talk.";
	}
	else {
		cout << "\nYour creature says: " << endl;
		cout << "I feel ";
		int mood = GetMood();
		if (mood > 15) {
			cout << "angry.";
			if (m_Hunger > 7) {
				cout << "\nMy stomach hurts!" << endl;
			}
			if (m_Boredom > 7) {
				cout << "I am soooo bored." << endl;
			}
		}
		else if (mood > 10) {
			cout << "frustraited ";
			if (m_Hunger > 6) {
				cout << "\nMy stomach hurts!" << endl;
			}
			if (m_Boredom > 6) {
				cout << "I am soooo bored." << endl;
			}
		}
		else if (mood > 5) {
			cout << "alright.. ";
			if (m_Hunger > 3) {
				cout << "\nI'm kind of peckish" << endl;
			}
			if (m_Boredom > 3) {
				cout << "Are there any toys around?" << endl;
			}
		}
		else {
			cout << "happy ";
		}
		if (m_Age <= 1) {
			cout << "\n\nYour critter is a toddler" << endl;
		}
		else if (m_Age > 1) {
			cout << "\n\nYour critter is " << m_Age << " cycles old." << endl;
			if (m_Age > 16) {
				cout << "Your creature is getting old, you may ony have a few cycles left" << endl;
			}
		}
		PassTime();
	}
	SetConsoleTextAttribute(h, 0x0F);
}
int Critter::Eat(int food)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 0x40);
	int fed = food - m_Hunger;
	if (alive == false) {
		cout << "\nYour creature is dead. It can't eat." << endl;
	}
	else {
		if (food > 0 && m_Hunger > 0) {
			cout << "BLEUGHH.\n";
			m_Hunger -= food;
			
		}
		if (food <= 0) {
			cout << "\nYou don't have any more food! Go to the market and buy some." << endl;
		}
		if (m_Hunger <= 0) {
			cout << "\nYour creature is full!" << endl;
			m_Hunger = 0;
		}
		PassTime();
	}
	SetConsoleTextAttribute(h, 0x0F);
	return fed;
}
void Critter::Play(int fun)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 0x40);
	if (alive == false) {
		cout << "You try to play with your creature, but it's dead." << endl;
	}
	else {
		if (fun <= 2) {
			cout << "Wee!\nThat was fun! It would be more fun with some toys to play with though." << endl;
		}
		else if (fun >= 4) {
			cout << "Wee!\nThat was fun! Thank you for the toys!" << endl;
		}
		m_Boredom -= fun;
		if (m_Boredom < 0) {
			m_Boredom = 0;
		}
		PassTime();
	}
	SetConsoleTextAttribute(h, 0x0F);
}
int Critter::Work(string name, int tools)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 0x40);
	if (alive == false) { cout << "You ask your creature to work, but it just lays there motionless" << endl;  
	SetConsoleTextAttribute(h, 0x0F);
	return 0; }
	else if (alive == true) {
		cout << "Your critter, " << name << ", goes off to work with " << tools << " tools." << endl;
		srand(time(NULL));
		int moneymade = rand() % 20 + (tools * 10);
		cout << "\n" << name << " made " << moneymade << " dollars at work" << endl;
		PassTime();
		SetConsoleTextAttribute(h, 0x0F);
		return moneymade;
	}
}
void Critter::debug()
{
	cout << "Hunger level: " << m_Hunger << "\nBoredom level: " << m_Boredom << endl;
}
int Critter::GetMood() const
{
	return (m_Hunger + m_Boredom);
}
void Critter::PassTime(int time)
{
	m_Hunger += time;
	m_Boredom += time;
	m_Age += time;
	if (m_Age >= 50) {
		alive = false;
	}
	else if (m_Hunger >= 20) {
		alive = false;
	}
}
int Critter::GetScore() {
	int score = GetMood() * 10;
	return score;
}
void Critter::Reset() {
	m_Hunger = 0;
	m_Boredom = 0;
}

//Game Runners
void runHscore() {

	Hscore run;
	run.SetDefaultEntries();
	int switcher = 5;
	while (switcher != 0) {
		cout << "Welcome to the High Score Table" << endl;
		cout << "\n0: Quit";
		cout << "\n1: Display Table";
		cout << "\n2: Add Entry" << endl;
		cout << "\nChoice: ";
		cin >> switcher;
		switch (switcher) {
		case 0: {break; }break;
		case 1: {
			run.Display(); }break;
		case 2: {
			string names;
			cout << "\n\nName: ";
			cin >> names;
			string *name = &names;
			cout << "\nScore: ";
			int scores;
			cin >> scores;
			system("CLS");
			int *point = &scores;
			run.InsertEntry(name, point);
			system("pause");
			run.Display();
			system("pause");
			break;
		}break;
		}
		cin.ignore();
	}

}
void welcome() {
	cout << "Chapter 6 Projects" << endl;
	cout << "\n1: [Projects 6.1] The 'Ship' Class" << endl;
	cout << "2: [Projects 6.2] Advanced 'Ship' Class" << endl;
	cout << "3: [Projects 6.3] High Score Table" << endl;
	cout << "4: [Projects 6.4] Critter Caretaker" << endl;
	cout << "5: [Projetcs 6.5] Hand Held Game System" << endl;
	cout << "0: Quit" << endl;
}
void runShip1() {
	Ship sv1;
	sv1.Status();

	Ship sv2("Voyager", 10);
	sv2.Status();

	Ship sv3("Millennium Falcon", -10);
	sv3.Status();
	system("pause");
	system("CLS");
}
void runShip2() {
	cin.ignore();
	cout << "Fly the ship and refuel it if neccessary" << endl;
	cout << "\nName of new ship: ";
	string newName;
	getline(cin, newName);
	Ship s1(newName, 0);
	s1.Status();
	system("pause");
	bool quit = false;
	while (quit != true) {
		cout << "\nAlright, what would you like to do?" << endl;
		cout << "\n1: Refuel" << endl;
		cout << "2: Travel" << endl;
		cout << "3: Quit" << endl;
		cout << "\nChoice: ";
		int choice;
		cin >> choice;
		system("CLS");
		switch (choice) {
		case 1: {
			s1.Refuel();
		}break;
		case 2: {
			cout << "\nHow far would you like to go? 1 AU/FUEL" << endl;
			unsigned short int dist;
			cout << "Distance: ";
			cin >> dist;
			s1.Move(dist);
		}break;
		case 3: {
			quit = true;
			break;
		}break;
		}
	}
}
void runCrit()
{
	cin.ignore();
	enum { listen = 1, feed, play, work, market, quit, debug = 10, reset };
	string intro = "\n\t\t\tWelcome to Critter Caretaker!\nYour first critter is free, here you go!\nMake sure to listen to your creature often, it can and will die of neglect\nAlso, creatures are known to only live 50 life cycles.";
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 0x0E);
	for (int i = 0; i < intro.size(); i++)
	{
		cout << intro[i];
		Sleep(50);
	}
	cout << "\nAny key to continue.." << endl;
	cin.ignore();
	SetConsoleTextAttribute(h, 0x0F);
	cout << "\n\nWhat will you name your first critter?" << endl;
	cout << "\nName :";
	string name;
	getline(cin, name);
	Critter crit(name, 0, 0);
	system("pause");
	int fun = 2;
	int food = 0;
	int money = 10;
	int tools = 0;
	bool quitter = false;
	system("CLS");

	while (true) {
		if (quitter == true) {
			break;
		}
		SetConsoleTextAttribute(h, 0xA0);
		cout << "\nMoney: " << money;
		SetConsoleTextAttribute(h, 0x8C);
		cout << "\nFood: " << food << endl;
		SetConsoleTextAttribute(h, 0x0F);
		cout << "\nWhat would you like to do?" << endl;
		cout << "\n1: Listen to your critter" << endl;
		cout << "2: Feed your critter" << endl;
		cout << "3: Play with your critter" << endl;
		cout << "4: Send your critter to work" << endl;
		cout << "5: Go to the market" << endl;
		cout << "6: Submit Score & Quit [if your creature is dead]" << endl;
		cout << "Selection :";
		int select;
		cin >> select;
		system("CLS");
		switch (select) {
		case listen: {
			crit.Talk();
			system("pause");
		}break;
		case feed: {
			if (food > 0) {
				food = crit.Eat(food);
			}
			else {
				cout << "\nYou don't have enough food!" << endl;
			}
		}break;
		case play: {
			crit.Play(fun);
		}break;
		case work: {
			int moneymade = crit.Work(name, tools);
			money += moneymade;
			cout << "\nYour creature says: " << endl;
			if (crit.alive == false) {
				cout << "\nNothing. Because it's dead." << endl;
			}
			else if (moneymade > 20 && crit.alive == true) {
				cout << "I made lots today!" << endl;
			}
			else if (moneymade > 10 && crit.alive == true) {
				cout << "I made a decent amount today!" << endl;
			}
			else if (moneymade < 10 && crit.alive == true) {
				cout << "I didn't really make a whole lot..." << endl;
			}

		}break;
		case market: {
			system("CLS");
			while (true) {
				cout << "\nWelcome to the Market! Please select an item to buy: " << endl;
				cout << "\n\n1: Food" << endl;
				cout << "2: Toys" << endl;
				cout << "3: Tools" << endl;
				cout << "0: Leave Store" << endl;
				//	cout << "4: Eggs" << endl;
				enum { groceries = 1, toys, works, eggs };
				SetConsoleTextAttribute(h, 0xA0);
				cout << "\nMoney: " << money << endl;
				SetConsoleTextAttribute(h, 0x0F);
				cout << "Selection: ";
				int choice;
				cin >> choice;
				system("CLS");
				if (choice == 0) {
					break;
				}
				switch (choice) {
				case groceries: {
					cout << "\nFood market: " << endl;
					cout << "\n0:Nothing" << endl;
					cout << "1: 10 Food - $10" << endl;
					cout << "2: 20 Food - $18" << endl;
					cout << "3: 30 Food - $25" << endl;
					SetConsoleTextAttribute(h, 0xA0);
					cout << "\nMoney: " << money << endl;
					SetConsoleTextAttribute(h, 0x0F);
					cout << "Selection: ";
					int select;
					cin >> select;
					system("CLS");
					switch (select) {
					case 1: {
						if (money >= 10) {
							food += 10;
							money -= 10;
						}
						else {
							cout << "\nYou don't have enough money!" << endl;
						}
					}break;
					case 2: {if (money >= 18) {
						food += 20;
						money -= 18;
					}
							else {
								cout << "\nYou don't have enough money!" << endl;
							}

					}break;
					case 3: {
						if (money >= 25) {
							food += 30;
							money -= 25;
						}
						else {
							cout << "\nYou don't have enough money!" << endl;
						}
					}break;
					}
				}break;
				case toys: {
					cout << "\nWelcome to the Toy Store!" << endl;
					cout << "\nWhat would you like to buy?" << endl;
					cout << "\n0: Nothing" << endl;
					cout << "1: Teddy Bear - $40" << endl;
					cout << "2: Toy Box - $60" << endl;
					cout << "3: Swing Set - $120" << endl;
					SetConsoleTextAttribute(h, 0xA0);
					cout << "\nMoney: " << money << endl;
					SetConsoleTextAttribute(h, 0x0F);
					cout << "Selection: ";
					int toysel;
					cin >> toysel;
					system("CLS");
					switch (toysel) {
					case 1: {
						if (money >= 40) {
							fun += 4;
							money -= 40;
						}
						else {
							cout << "\nYou don't have enough money!" << endl;
						}
					}break;
					case 2: {
						if (money >= 60) {
							fun += 7;
							money -= 60;
						}
						else {
							cout << "\nYou don't have enough money!" << endl;
						}
					}break;
					case 3: {
						if (money >= 120) {
							fun += 12;
							money -= 120;
						}
						else {
							cout << "\nYou don't have enough money!" << endl;
						}
					}break;
					}
				}break;
				case works: {
					cout << "\nWelcome to the Tool Store" << endl;
					cout << "\nWhat would you like to buy?" << endl;
					cout << "\n0: Nothing" << endl;
					cout << "1: A Wrench - $20" << endl;
					cout << "2: Tool Box - $100" << endl;
					cout << "3: Workshop of Tools - $250" << endl;
					SetConsoleTextAttribute(h, 0xA0);
					cout << "\nMoney: " << money << endl;
					SetConsoleTextAttribute(h, 0x0F);
					cout << "Selection: ";
					int toolsel;
					cin >> toolsel;
					system("CLS");
					switch (toolsel) {
					case 1: {
						if (money >= 20) {
							tools += 1;
							money -= 20;
						}
						else {
							cout << "\nYou don't have enough money!" << endl;
						}
					}break;
					case 2: {
						if (money >= 100) {
							tools += 5;
							money -= 100;
						}
						else {
							cout << "\nYou don't have enough money!" << endl;
						}
					}break;
					case 3: {
						if (money >= 250) {
							tools += 12;
							money -= 250;
						}
						else {
							cout << "\nYou don't have enough money!" << endl;
						}
					}break;
					}break;
				}
				}
			}break;
		case debug: {
			crit.debug();
		}break;
		case reset: {
			crit.Reset();
		}break;
		}break;
		case quit: {
			int score = money * 2 - crit.GetScore();
			if (crit.alive == true) {
				cout << "\nAre you sure you want to quit? Your creature is still alive!" << endl;
				cout << "Response (y/n): ";
				char confirm;
				cin >> confirm;
				if (confirm == 'y') {
					cout << "Thank you for playing!\nYour score was: " << score << endl;
					quitter = true;
				}
			}
			else {
				cout << "Thank you for playing!\nYour score was: " << score << endl;
				quitter = true;
			}
		}break;
		}
	}
	cin.ignore();
	system("pause");
	system("CLS");
}
void runHheld() {
	bool quit = false;
	cout << "\n\t\tWelcome to the Hand-Held System" << endl;
	Handheld hh;
	while (quit != true) {
		cout << "\n";
		hh.Options();
		int choice = getInput();
		switch (choice) {
		case 0: {quit = true; }break;
		case 1: { hh.TogglePower(); }break;
		case 2: {
			hh.DisplayGames();
			int gamenum = hh.GetInput();
			hh.SetGameNumber(gamenum);
		}break;
		case 3: {hh.RaiseVolume(); }break;
		case 4: {hh.LowerVolume(); }break;
		case 5: {hh.Play(); }break;
		}
	}
}

//Handheld Functs
void Handheld::TogglePower()
{
	if (m_IsOn == false) {
		m_IsOn = true;
	}
	else {
		m_IsOn = false;
	}
}
void Handheld::DisplayGames()
{
	vector<string> gamelist = { "Skyrim", "Pac-Man", "Mrs. Pac-Man", "Devil May Cry", "Old School Doom" };
	vector<string>::iterator iter;
	int listnum = 1;
	if (m_IsOn == true) {
		for (iter = gamelist.begin(); iter < gamelist.end(); iter++) {
			cout << listnum << ": " << *iter << endl;
			listnum++;
		}
	}
}
void Handheld::Play() const
{
	if (m_IsOn == true) {
		if (m_GameNumber == 0) {
			cout << "\nNo game selected." << endl;
		}
		switch (m_GameNumber) {
		case 1: {
			string sucss = "The stone arrow flies aimlessly into the sky and miraculously pierces the dragon's eye, killing it.\nYou have won this battle!";
			string playsky = "\nYou gear up your level 12 dark elf mage for the battle against the elder dragon.\n";
			string playsky2 = "\nThe battle rages for what seems like hours..\nYour last ounce of mana spent, you take a hail-mary shot with a garbage bow from your inventory.\n";
			typeSlow(playsky);
			typeSlow(playsky2);
			srand(time(NULL));
			int chance = rand() % 10 + 1;
			if (chance >= 5) {
				typeSlow(sucss);
			}
			else {
				string fail = "The stone arrow flies aimlessly into the sky and lands, predictably, nowhere near target.\nThe dragon swoops in and devours you. You have died";
				typeSlow(fail);
			}
		}break;
		case 2: {
			string sucss = "\nYou expertly dodge and devour all of the ghosts. All of the points are belong to you.\nYou got a new high score!";
			string play = "\n'WaKa WaKa WaKa'\nYour Pac-Man fires to life and you navigate the maze of dots attempting to dodge the ghosts\n";
			string play2 = "\nYou have collected a lot of points..however just as you go for the last blue dot a ghost cuts you off ahead\nYou are cornered!";
			string fail = "\nYou attempt to dodge the ghosts and outwit them\nBut you lack the neccessary wit and become corenered\nYou have died and brought shame to your family.";
			typeSlow(play);
			typeSlow(play2);
			srand(time(NULL));
			int chance = rand() % 10 + 1;
			if (chance > 5) {
				typeSlow(sucss);
			}
			else {
				typeSlow(fail);
			}
		}break;
		case 3: {
			string sucss = "\nYou expertly dodge and devour all of the ghosts. All of the points are belong to you.\nYou got a new high score!";
			string play = "\n'WaKa WaKa WaKa'\nYour Mrs. Pac-Man fires to life and you navigate the maze, collecting dots and attempting to dodge the ghosts\n";
			string play2 = "\nYou have collected a lot of points..however just as you go for the last blue dot a ghost cuts you off ahead\nYou are cornered!";
			string fail = "\nYou attempt to dodge the ghosts and outwit them\nBut you lack the neccessary wit and become corenered\nYou have died and brought shame to your family.";
			typeSlow(play);
			typeSlow(play2);
			srand(time(NULL));
			int chance = rand() % 10 + 1;
			if (chance > 5) {
				typeSlow(sucss);
			}
			else {
				typeSlow(fail);
			}
		}break;
		case 4: {
			string sucss = "\nA volley of cannonfire from your trusty pistols dispatches the boss with ease.\nYou're too good at this. New high score!";
			string play = "\nDante stands before an army of demons, bold-faced and cocky as ever.\nWith a whirlwind of swordslashes and a myraid of bullets the army is quickly dispatched";
			string play2 = "\nA giant ornate gate swings open, and Dante proceeds through it\nIt's the final boss! He roars and flails his giant mace around the castle courtyard";
			string fail = "\nAfter dodging and flipping and emptying out endless clips, the boss proves to be too difficult to defeat\nDante is killed.\nGame ovveerrrrr";
			typeSlow(play);
			typeSlow(play2);
			srand(time(NULL));
			int chance = rand() % 10 + 1;
			if (chance > 5) {
				typeSlow(sucss);
			}
			else {
				typeSlow(fail);
			}
		}break;
		case 5: {
			string sucss = "\nWith a huge BOOM the BFG9000 rips a giant hole in the minotaur, the glorious gore of it's defeat litters the landscape.\nThe Gateway behind it roars and legions of demons come pouring out.\nYou reload. Even after having won the battle, you know that war,\nWar is never over.";
			string play = "\nThe atmosphere of the moon Phobos is heavy with the deaths of an entire colony of scientists.\nThe Mars Acquisitions Team, or TMAT, had attempted to open a portal to Earth for their trillion-dollar sub-space travel experiment.";
			string play2 = "\nThe experiement failed, legions of demons came pouring through instead.\nAs corporal Fly Mctaggart, you are the last line of defense.\nAfter slaying hundreds of demons, the Gateway was finally in sight\nWith the mighty BFG on full-charge, you proceed forward intent on destroying the demons' means of transport.\nSuddenly a minotuar the size of a house steps into the open between you and the Gateway.\n";
			string fail = "\nYou aim the BFG 9000 dead-square at the massive minotaur\nBut one of it's rockets hits you first, your screen twitches sending your shot from the end-game superweapon flying into a pile of explosive barrels behind you\nYour body gibs into a thousand gorey pieces as the cascading explosion tears through the space you used to inhabit.\nYou have failed, and the Earth has been lost to demons forever.";
			typeSlow(play);
			typeSlow(play2);
			srand(time(NULL));
			int chance = rand() % 10 + 1;
			if (chance >= 5) {
				typeSlow(sucss);
			}
			else {
				typeSlow(fail);
			}
		}break;
		}
	}
}
void Handheld::SetGameNumber(int NewGameNumber)
{
	if (m_IsOn == true) {
		m_GameNumber = NewGameNumber;
		cout << "\nGame number " << NewGameNumber << " set" << endl;
	}
}
void Handheld::RaiseVolume()

{
	if (m_IsOn == true) {
		m_Volume++;
		cout << "\nVolume level: " << m_Volume << endl;
		Beep(600, 200);
		Sleep(200);
		Beep(700, 200);
		Sleep(200);
		Beep(800, 200);
		Sleep(200);
	}
}
void Handheld::LowerVolume()
{
	if (m_IsOn == true) {
		m_Volume--;
		cout << "\nVolume level: " << m_Volume << endl;
		Beep(800, 200);
		Sleep(200);
		Beep(700, 200);
		Sleep(200);
		Beep(600, 200);
		Sleep(200);
	}
}
void Handheld::Options() {
	cout << "\n0: Quit\n1: Toggle system power" << endl;
	if (m_IsOn == true) {
		cout << "2: Select a game for the system\n";
		cout << "3: Raise the system volume\n";
		cout << "4: Lower the system volume\n";
		cout << "5: Play the system" << endl;
	}
}
int Handheld::GetInput() {
	if (m_IsOn == true) {
		cout << "\nSelection: ";
		int choice;
		cin >> choice;
		system("CLS");
		return choice;
	}
}

