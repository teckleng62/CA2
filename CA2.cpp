#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <conio.h>
#include <vector>
using namespace std;
void showtitle();
void getTitles();
void addTitle();
int titleCount = 0;
vector<string> titles;
bool Title();

int main()
{
	showtitle();
	cout << "[A/D] Movie Selection" << endl;
	cout << "[0] Movie Selection Editor" << endl;
	cout << "[Esc] Close the Programme" << endl;
	getTitles();		// Get titles from text file. MUST be first line
	char key = _getch();
	if (key == '0') { addTitle(); }		// add title
	else if (key == 'd' || key == 'a') { Title(); }
	else if (key == 27) { return 0; }

	return 0;
}

void getTitles()
{
	fstream title;
	string line;
	title.open("Titles.txt");		// open text file.
	if (!title.is_open())
	{
		cout << "Unable to open file." << endl;
	}

	while (!title.eof())
	{
		while (getline(title, line))		// AI
		{
			if (!line.empty())
			{
				titles.push_back(line);
				titleCount++;
			}								//
		}
		title.close();
	}										
}
/*
void addTitle()		// REMOVE TITLE
{
	system("cls");
	ofstream title, remove;
	string titlename;
	int getline = 1, removeline;
	title.open("Titles.txt",ofstream::app);		// open text file. append.
	remove.open("Titles.txt");
	if (!title.is_open() || !remove.is_open())
	{
		cout << "Unable to open file." << endl;
	}

	cout << "[1] Edit the movies." << endl;
	cout << "[2] Add more movies." << endl;
	char key = _getch();

	if (key == '1') 	// remove selected movies
	{
		for (int x = 0; x < titleCount; x++)
		{
			cout << x << ". " << titles[x] << endl;
		}
		cout << "Enter the number of the title you want to remove: ";
		cin >> removeline;		// get the line to remove

		for (int i = 0; i < titleCount; i++)
		{
			if (i != removeline)
			{
				remove << titles[i] << endl;
			}
			remove.close();
		}
	}

	else if (key == '2')
	{
		system("cls");

		cout << "Type the title of the movie: " << endl;
		cin >> titlename;
		title << endl << titlename;
	}
}
*/

void addTitle()
{
	system("cls");
	ofstream title;
	string titlename;
	title.open("Titles.txt", ofstream::app);		// open text file. append/edit.
	if (!title.is_open())
	{
		cout << "Unable to open file." << endl;
	}

	cout << "[Space] Edit the movies." << endl;
	char key = _getch();
	if (key == ' ')
	{
		system("cls");

		cout << "Type the title of the movie: " << endl;
		cin >> titlename;
		title << endl << titlename;
	}
	title.close();
}

bool Title()
{
	int x = 0;
	char key;

	system("cls");
	while (x < titleCount + 1)			// go to next movie selection if 'D' is pressed		
	{
		int border = 103;
		int lefttitle = (x - 1 + titleCount) % titleCount;
		int righttitle = (x + 1) % titleCount;
		for (int z = 0; z < border; z++) { cout << "="; } cout << endl;	
		cout << left <<  setw(101) << "||" << "||" << endl;
		cout << left
			<< setw(10) << "||    " << setw(22) << titles[lefttitle]
			<< setw(10) << "   |  " << setw(22) << titles[x]
			<< setw(10) << "   |  " << setw(22) << titles[righttitle]
			<< setw(10) << "     ||" << endl;
		cout << left << setw(101) << "||" << "||" << endl;
		for (int z = 0; z < border; z++) { cout << "="; } cout << endl;
		int space1 = 26, space2 = 8;
		cout << left << setw(space2) << " " << setw(space1) << "[A / D] to Browse" << setw(space2) << "|" << setw(space1) << "[Space] to Select" << setw(space2) << "|" << "[Esc] to Quit" << endl;

		// show seating for each movie.

		key = _getch();
		if (key == 'd' && x < titleCount - 1)
		{
			x++;
		}
		else if (key == 'a' && x >= 1)			// move back if 'A' is pressed
		{
			x--;
		}
		else if (key == ' ')			// if 'Space' is pressed, go in to the seat selection
		{
			cout << "\n\nseats" << endl;
			break;
		}
		else if (key == 27)			// if 'Esc' is pressed, Exit
		{
			cout << "\n\nescape" << endl;
			break;
		}
		system("cls");
	}
	return 0;
}
void showtitle()
{
	fstream title;
	string line;
	title.open("Image.txt");
	if (!title.is_open())
	{
		cout << "Unable to open file." << endl;
	}

	while (getline(title, line))
	{
		cout << line << endl;
	}
	cout << "\n\n";
}