#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <conio.h>
#include <vector>
using namespace std;
// TL
void showtitle();
void getTitles();
void addTitle();
void Title();
int titleCount = 0;
vector<string> titles;
string selectedtitle;
// Ryzal
const int ROWS = 8;
const int COLS = 20;
char seats[ROWS][COLS];
void LoadSeats();
void SaveSeats();
void DisplaySeats();
int BookSeat();
//


int main()
{
	int choice = 0;
	int people=0;
	getTitles();		// Get titles from text file. MUST be first line
	showtitle();
	LoadSeats();
	cout << "[A/D] Movie Selection" << endl;
	cout << "[0] Movie Selection Editor" << endl;
	cout << "[Esc] Close the Programme" << endl;
	
	char key = _getch();
	if (key == '0') { addTitle(); return 0; }		// add title
	else if (key == 27) { return 0; }
	else if (key == 'd' || key == 'a') { Title(); }	// get selectedtitle <- title;
	people = BookSeat();							// get people <- bookseat;
	if (people <= 0) { return 0; }
	else	//show checkout page
	{
			
	}
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

void addTitle()
{
	system("cls");
	fstream titleout;
	ofstream title;
	string titlename;
	title.open("Titles.txt", ofstream::app);		// open text file. append/edit.
	if (!title.is_open() )
	{
		cout << "Unable to open file." << endl;
	}
	cout << "[Space] Add a new movie title." << endl;
	cout << "[Esc] Go back to Main Menu" << endl;
	char key = _getch();
	if (key == ' ')
	{
		system("cls");

		cout << "Type the title of the movie: " << endl;
		cin >> titlename;
		title << endl << titlename;
	}
	else if (key == 27) { main(); }
	titleout.open("Titles.txt");
	if (!titleout.is_open())
	{
		cout << "Unable to open file." << endl;
	}
	cout << endl;
	while (getline(titleout, titlename))
	{
		cout << titlename << endl;
	}
	title.close();
}

void Title()
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
			DisplaySeats();
			break;
		}
		else if (key == 27)			// if 'Esc' is pressed, Exit
		{
			cout << "\nHave a nice day!" << endl;
			exit(0);
			break;
		}
		system("cls");
		selectedtitle = titles[x];
	}
}



void LoadSeats()		// Ryzal
{
	ifstream fin("Seats.txt");

	if (fin.fail())
	{
		cout << "Unable to open file!";
		exit(1);
	}

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			fin >> seats[i][j];
		}
	}

	fin.close();
}

void SaveSeats()
{
	ofstream fout("Seats.txt");

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			fout << seats[i][j] << " ";
		}

		fout << endl;
	}

	fout.close();
}

void DisplaySeats()
{
	int border = 67;
	cout << "\n" << endl;
	for (int z = 0; z < border; z++) { cout << "="; } cout << endl;
	cout << "\n\t\t\t\tSCREEN\n" << endl;
	for (int z = 0; z < border; z++) { cout << "="; } cout << endl;

	// Print seat numbers
	cout << "        ";          // 8 spaces

	for (int i = 1; i <= COLS; i++)
	{
		cout << setw(2) << i << " ";
	}

	cout << "\n";

	// Print seats
	for (int i = 0; i < ROWS; i++)
	{
		cout << "Row " << i + 1 << "   ";

		for (int j = 0; j < COLS; j++)
		{
			cout << setw(2) << seats[i][j] << " ";
		}

		cout << endl;
	}

	cout << "\n";
	cout << "O = Available\n";
	cout << "X = Booked\n\n";
}

int BookSeat()
{
	int row, seat, people;
	bool available = true;

	cout << "\nEnter row (1-8): ";
	cin >> row;

	cout << "Enter starting seat (1-20): ";
	cin >> seat;

	cout << "Number of people: ";
	cin >> people;

	if (row < 1 || row > ROWS)
	{
		cout << "Invalid row!";
		(void)_getch();
		return 0;
	}

	if (seat < 1 || seat > COLS)
	{
		cout << "Invalid seat!";
		(void)_getch();
		return 0;
	}

	if (seat + people - 1 > COLS)
	{
		cout << "Not enough seats in this row!";
		(void)_getch();
		return 0;
	}

	for (int i = 0; i < people; i++)
	{
		if (seats[row - 1][seat - 1 + i] == 'X')
		{
			available = false;
			break;
		}
	}

	if (!available)
	{
		cout << "\nSome seats are already booked!";
	}
	else
	{
		for (int i = 0; i < people; i++)
		{
			seats[row - 1][seat - 1 + i] = 'X';
		}

		SaveSeats();

		cout << "\nBooking Successful!";
	}

	return people;
}