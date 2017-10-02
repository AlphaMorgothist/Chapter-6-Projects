// Chapter6Projects.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "Chapter6Projects.h"

using namespace std;

int main()
{
	bool over = false;
	while (over != true) {
		int choice;
		welcome();
		cout << "\nChoice: ";
		cin >> choice;
		system("CLS");
		switch (choice) {
		case 1: {runShip1();	}break;
		case 2: {runShip2();	}break;
		case 3: {runHscore();	}break;
		case 4: {runCrit();		}break;
		case 5: {runHheld(); }break;
		case 0: {over = true; break; }	break;
		}
	}
    return 0;
}


