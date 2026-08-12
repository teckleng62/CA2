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
int selectedrow, selectedseat;
// Iskandar
void checkout(string movie, int adultTickets, int childTickets);
// Irfan
void cashReceipt(string movie, int adultTickets, int childTickets, double total);
void paywaveReceipt(string movie, int adultTickets, int childTickets, double total);


int main()
{
	int choice = 0;
	int people=0;
	int adultTickets;
	int childTickets;
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
	do {
		people = BookSeat();  // get people <- bookseat;
		if (people <= 0) {
			cout << "\nWould you like to try again? (Y/N): ";
			char tryAgain;
			cin >> tryAgain;
			if (tryAgain == 'N' || tryAgain == 'n') {
				return 0;
			}
			system("cls");
			DisplaySeats();  // Show updated seat map
		}
	} while (people <= 0);
	
	cout << "\n=====================================\n";
	cout << "          TICKET SELECTION\n";
	cout << "=====================================\n";
	
	cout << "Number of adult tickets: ";
	cin >> adultTickets;

	cout << "Number of child tickets: ";
	cin >> childTickets;


	// Make sure adult + child tickets
	// match the number of seats booked
	while (adultTickets + childTickets != people)
	{
		cout << "\nThe number of adult and child tickets";
		cout << " must equal " << people << ".\n";
		cout << "Please try again.\n\n";
		cout << "Number of adult tickets: ";
		cin >> adultTickets;

		cout << "Number of child tickets: ";
		cin >> childTickets;
	}
		// Send the information to checkout
		checkout(selectedtitle, adultTickets, childTickets);

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
	int people;
	bool available = true;

	cout << "\nEnter row (1-8): ";
	cin >> selectedrow;

	cout << "Enter starting seat (1-20): ";
	cin >> selectedseat;

	cout << "Number of people: ";
	cin >> people;

	if (selectedrow  < 1 || selectedrow  > ROWS)
	{
		cout << "Invalid row!";
		(void)_getch();
		return 0;
	}

	if (selectedseat < 1 || selectedseat > COLS)
	{
		cout << "Invalid seat!";
		(void)_getch();
		return 0;
	}

	if (selectedseat + people - 1 > COLS)
	{
		cout << "Not enough seats in this row!";
		(void)_getch();
		return 0;
	}

	for (int i = 0; i < people; i++)
	{
		if (seats[selectedrow - 1][selectedseat - 1 + i] == 'X')
		{
			available = false;
			break;
		}
	}

	if (!available)
	{
		cout << "\nSome seats are already booked!";
		return 0;
	}
	else
	{
		for (int i = 0; i < people; i++)
		{
			seats[selectedrow - 1][selectedseat - 1 + i] = 'X';
		}

		SaveSeats();

		cout << "\nBooking Successful!";
		(void)_getch();
		return people;
	}
}


// Iskandar
void checkout(string movie, int adultTickets, int childTickets)
{
	double adultPrice = 12.00;
	double childPrice = 10.00;

	int numberOfTickets = adultTickets + childTickets;

	double total = (adultTickets * adultPrice) +
		(childTickets * childPrice);

	int paymentMethod;
	char confirm;


	// DISPLAY CHECKOUT
	cout << "\n";
	cout << "=====================================\n";
	cout << "              CHECKOUT\n";
	cout << "=====================================\n";

	cout << fixed << setprecision(2);

	cout << "Movie             : " << movie << endl;
	cout << "Adult tickets     : " << adultTickets << endl;
	cout << "Child tickets     : " << childTickets << endl;
	cout << "Total tickets     : " << numberOfTickets << endl;
	cout << "Adult price       : $" << adultPrice << endl;
	cout << "Child price       : $" << childPrice << endl;
	cout << "Total             : $" << total << endl;

	cout << "=====================================\n";


	// CONFIRM BOOKING
	cout << "\nConfirm your selection? (Y/N): ";
	cin >> confirm;


	// Invalid input
	while (confirm != 'Y' && confirm != 'y' &&
		confirm != 'N' && confirm != 'n')
	{
		cout << "\nInvalid choice.\n";
		cout << "Please enter Y or N.\n";

		cout << "\nConfirm your selection? (Y/N): ";
		cin >> confirm;
	}


	// Output = N
	if (confirm == 'N' || confirm == 'n')
	{
		cout << "\nBooking cancelled.\n";
		return;
	}


	// Output = Y
	cout << "\nBooking confirmed!\n";


	// PAYMENT METHOD
	paymentMethod = 0;

	while (paymentMethod != 1 && paymentMethod != 2)
	{
		cout << "\nPayment Method\n";
		cout << "1. Cash\n";
		cout << "2. PayWave\n";
		cout << "Enter your choice: ";
		cin >> paymentMethod;

		if (paymentMethod != 1 && paymentMethod != 2)
		{
			cout << "\nInvalid payment method.\n";
			cout << "Please try again.\n";
		}
	}


	// CASH PAYMENT
	if (paymentMethod == 1)
	{
		cout << "\nPayment Method: Cash\n";
		cout << "Please pay at the counter.\n";
		cout << "Present your booking receipt at the counter.\n";

		cout << "\nBooking successfully created.\n";
		cout << "Please proceed to the counter for payment.\n";

		// IRFAN CODE
		cashReceipt(movie, adultTickets, childTickets, total);
	}


	// PAYWAVE PAYMENT
	else if (paymentMethod == 2)
	{
		cout << "\nPayment Method: PayWave\n";
		cout << "Please tap your card/device...\n";

		cout << "\nPayment received successfully!\n";

		// IRFAN CODE
		paywaveReceipt(movie, adultTickets, childTickets, total);
	}

}


// Irfan
void cashReceipt(string movie, int adultTickets, int childTickets, double total)
{
	cout << "\n";
	cout << "=====================================\n";
	cout << "           CASH RECEIPT\n";
	cout << "=====================================\n";

	cout << fixed << setprecision(2);

	cout << "Movie             : " << movie << endl;
	cout << "Adult tickets     : " << adultTickets << endl;
	cout << "Child tickets     : " << childTickets << endl;
	cout << "Total tickets     : "
		<< adultTickets + childTickets << endl;
	cout << "Total             : $" << total << endl;

	cout << "Payment Method    : Cash" << endl;
	cout << "Payment Status    : Pay at counter" << endl;

	cout << "=====================================\n";
	cout << "   Thank you for your booking! 67:)\n";
	cout << "=====================================\n";
}


// PAYWAVE RECEIPT FUNCTION
void paywaveReceipt(string movie, int adultTickets, int childTickets, double total)
{
	cout << "\n";
	cout << "=====================================\n";
	cout << "         PAYWAVE RECEIPT\n";
	cout << "=====================================\n";

	cout << fixed << setprecision(2);

	cout << "Movie             : " << movie << endl;
	cout << "Adult tickets     : " << adultTickets << endl;
	cout << "Child tickets     : " << childTickets << endl;
	cout << "Total tickets     : "
		<< adultTickets + childTickets << endl;
	cout << "Total             : $" << total << endl;

	cout << "Payment Method    : PayWave" << endl;
	cout << "Payment Status    : Payment received" << endl;

	cout << "=====================================\n";
	cout << "   Thank you for your booking! 67:)\n";
	cout << "=====================================\n";
}