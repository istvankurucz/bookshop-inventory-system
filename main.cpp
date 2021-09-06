#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "book.h"

using namespace std;

void main_menu();
void menu(char submenu);

bool unique_id(string id);
string generate_id();
string* slice_row(string row);
Book search_book(string id = "", string author = "", string title = "");
bool id_checker(string id);

void book_list();
int book_number();
int income();
void remove_book(bool buy = true);
void add_books();

int main() {
	cout << "#####################################" << endl;
	cout << "      BOOKSHOP INVENTORY SYSTEM" << endl;
	cout << "#####################################" << endl;

	srand(time(NULL));
	char option = '0';

	do {
		main_menu();
		cout << endl << "Option: "; cin >> option;

		switch (option) {
		case '1':
			cout << endl << "########## LIST OF THE BOOKS ##########" << endl <<endl;
			book_list();
			break;

		case '2':
			cout << endl << "########## NUMBER OF THE BOOKS ##########" << endl << endl;
			cout << "Total number of the books: " << book_number() << endl;
			break;

		case '3':
			cout << endl << "########## TOTAL INCOME ##########" << endl << endl;
			cout << "The total income from the sold books: " << income() << " Ft." << endl;
			break;

		case '4':
			cout << endl << "########## PURCHASE BOOK(S) ##########" << endl << endl;
			remove_book();
			break;

		case '5':
			cout << endl << "########## ADD BOOK(S) ##########" << endl << endl;
			add_books();
			break;

		case '6':
			cout << endl << "########## DELETE BOOK(S) ##########" << endl << endl;
			remove_book(false);
			break;

		case '0':
			cout << endl << "########## EXIT ##########" << endl << endl;
			break;

		default:
			cout << "Invalid input!" << endl;
		}


	} while (option != '0');
}

void main_menu() {
	cout << endl << endl << "------------- MAIN MENU -------------" << endl << endl;
	cout << "\t1. List of books" << endl;
	cout << "\t2. Number of the books" << endl;
	cout << "\t3. Total income" << endl;
	cout << "\t4. Purchase book(s)" << endl;
	cout << "\t5. Add book(s)" << endl;
	cout << "\t6. Delete book(s)" << endl;
	cout << "\t0. Exit" << endl << endl;
	cout << "-------------------------------------" << endl;
}

void menu(char submenu) {
	cout << endl << "---------- MENU ----------" << endl << endl;
	switch (submenu)
	{
	case '4':
		cout << "   1. Purchase other book(s)" << endl;
		break;

	case '5':
		cout << "   1. Add other book(s)" << endl;
		break;

	case '6':
		cout << "   1. Delete other book(s)" << endl;
		break;

	default:
		break;
	}
	cout << "   0. Back to main menu" << endl;
	cout << endl << "--------------------------" << endl;
}

bool unique_id(string id) {
	string row;

	ifstream fin("books.txt");
	while (!fin.eof()) {
		getline(fin, row);

		if (row.substr(0, 8) == id) return false;
	}
	fin.close();

	return true;
}

string generate_id() {
	char chars[36] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
	string id = "";

	do {
		for (int i = 0; i < 8; i++) {
			int index = rand() % 36;
			bool uppercase = rand() % 2 == 0;

			if (uppercase) id += toupper(chars[index]);
			else id += chars[index];
		}
	} while (!unique_id(id));

	return id;
}

string* slice_row(string row) {
	int index = 0, from = 0, i = 0;
	string* user_data = new string[5];

	do {
		index = row.find(";", from);

		user_data[i] = row.substr(from, index - from);
		i++;

		from = index + 1;
	} while (index != -1);

	return user_data;
}

Book search_book(string id, string author, string title) {
	Book result;
	string row;
	bool correct = false;

	ifstream fin("books.txt");
	if (id != "") {
		while (!fin.eof()) {
			getline(fin, row);

			if (row.substr(0, 8) == id) {
				string* data = slice_row(row);
				if ((author != "" and data[1] == author and title != "" and data[2] == title) or (author == "" and title == "")) {
					result.setAll(data[0], data[1], data[2], stoi(data[3]), stoi(data[4]));
					correct = true;
				}
				else cout << "There is no book with this ID, author and title!" << endl;

				delete[] data;
				return result;
			}
		}
		if (!correct) cout << "There is no books with this ID (" << id << ")!" << endl;
		return result;
	}
	else if (author != "" and title != "") {
		while (!fin.eof()) {
			getline(fin, row);
			string* data = slice_row(row);

			if (data[1] == author and data[2] == title) {
				result.setAll(data[0], data[1], data[2], stoi(data[3]), stoi(data[4]));

				correct = true;
				return result;
			}

			delete[] data;
		}
		if (!correct) cout << "There is no books with this author and title (" << author << ": " << title << ")!" << endl;
		return result;
	}
	else {
		cout << "You should enter the ID or the AUTHOR AND TITLE or both!" << endl;
		return result;
	}
	fin.close();
}

bool id_checker(string id) {
	char chars[36] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
	bool correct;

	if (id.length() != 8) return false;
	else {
		for (int i = 0; i < 8; i++) {
			correct = false;
			for (int j = 0; j < 36; j++) {
				if (tolower(id[i]) == chars[j]) correct = true;
			}
			if (!correct) return false;
		}
		return true;
	}
}

void book_list() {
	string row;

	ifstream fin("books.txt");
	cout << setw(10) << "ID |" << setw(25) << "Author |" << setw(25) << "Title |" << setw(12) << "Price (Ft) |" << setw(10) << "Count" << endl;
	cout << "----------------------------------------------------------------------------------" << endl;
	while (!fin.eof()) {
		getline(fin, row);

		if (row != "") {
			string* data = slice_row(row);
			cout << setw(8) << data[0] << " |" << setw(23) << data[1] << " |" << setw(23) << data[2] << " |" << setw(10) << data[3] << " |" << setw(10) << data[4] << endl;
			delete[] data;
		}
	}
	fin.close();
	
}

int book_number() {
	if (!Book::getBooks()) {
		int count = 0;
		string row;

		ifstream fin("books.txt");
		while (!fin.eof()) {
			getline(fin, row);

			if (row != "") {
				string* data;
				data = slice_row(row);
				count += stoi(data[4]);
				delete[] data;
			}
		}
		fin.close();

		Book::setBooks(count);
	}
	return Book::getBooks();
}

int income() {
	if (!Book::getIncome()) {
		int income = 0;

		ifstream fin("sold.txt");
		while (!fin.eof()) {
			string row;

			getline(fin, row);
			if (row != "") {
				string* data = slice_row(row);
				income += stoi(data[3]);
				delete[] data;
			}
		}
		fin.close();

		Book::setIncome(income);
	}
	return Book::getIncome();
}

void remove_book(bool buy) {
	char option = '1';

	do {
		if (option == '1') {
			string id, author, title;

			// User input to find the book
			cout << endl << "You can find the book by its ID or by its AUTHOR AND TITLE or both." << endl;
			cin.get();
			cout << setw(8) << "ID: "; getline(cin, id);
			cout << setw(8) << "Author: "; getline(cin, author);
			cout << setw(8) << "Title: "; getline(cin, title);

			Book result = search_book(id, author, title);
			cout << endl << "***** RESULT *****" << endl;
			if (result.getId() == "") cout << "No result found." << endl;
			else {
				cout << setw(8) << "ID: " << result.getId() << endl;
				cout << setw(8) << "Author: " << result.getAuthor() << endl;
				cout << setw(8) << "Title: " << result.getTitle() << endl;
				cout << setw(8) << "Price: " << result.getPrice() << endl;
				cout << setw(8) << "Count: " << result.getCount() << endl;
				cout << "******************" << endl << endl;

				int remove_count = -1;
				bool correct = false;

				while (remove_count != 0 and !correct)
				{
					if (buy) cout << "How many would you like to buy? (Count: " << result.getCount() << ") / To quit type 0 /  ";
					else cout << "How many would you like to delete? (Count: " << result.getCount() << ") / To quit type 0 /  ";
					cin >> remove_count;

					if (remove_count <= result.getCount() and remove_count > 0) {
						correct = true;

						// Update books.txt
						ofstream fout("temp.txt");
						ifstream fin("books.txt");
						string row;
						while (!fin.eof()) {
							getline(fin, row);

							if (row != "") {
								if (row.substr(0, 8) == result.getId()) {
									if (result.getCount() != remove_count) fout << result.getId() << ";" << result.getAuthor() << ";" << result.getTitle() << ";" << result.getPrice() << ";" << result.getCount() - remove_count << endl;
								}
								else fout << row << endl;
							}
						}
						fin.close();
						fout.close();

						remove("books.txt");
						bool renamed = rename("temp.txt", "books.txt");
						if (renamed) cout << "Error updating 'books.txt'" << endl;

						if (buy) {
							// Add the sold book to sold.txt
							fout.open("sold.txt", ios_base::app);
							fout << result.getId() << ";" << result.getAuthor() << ";" << result.getTitle() << ";" << result.getPrice() << ";" << remove_count << endl;
							fout.close();

							// Update income static variable
							if (!Book::getIncome()) Book::setIncome(income());
							else Book::setIncome(Book::getIncome() + remove_count * result.getPrice());

							cout << "Book successfully purchased!" << endl;
						}
						else cout << "Book successfully deleted!" << endl;

						// Update book_count static variable
						if (!Book::getBooks()) Book::setBooks(book_number());
						else Book::setBooks(Book::getBooks() - remove_count);
					}
					else if (!remove_count) break;
					else cout << "Invalid count!" << endl;
				}
			}
		}
		else if (option == '0') break;
		else cout << "Invalid input!" << endl;

		if (buy) menu('4');
		else menu('6');
		cout << endl << "Option: "; cin >> option;
	} while (option != '0');
}

void add_books() {
	char option = '1';
	string id, author, title, row;
	int price = 0, count = 0;

	do {
		if (option == '1') {
			cin.get();
			cout << "ID (type ENTER to auto-generate): "; getline(cin, id);
			if (id == "") id = generate_id();
			else if (!id_checker(id)) {
				cout << "The ID is not correct!" << endl;
				break;
			}

			cout << "Author: "; getline(cin, author);
			if (author == "") {
				cout << "You have to add the author of the book!" << endl;
				break;
			}

			cout << "Title: "; getline(cin, title);
			if (author == "") {
				cout << "You have to add the title of the book!" << endl;
				break;
			}

			cout << "Price: "; cin >> price;
			if (price <= 0) {
				cout << "The price of the book cannot be 0 or negative!" << endl;
				break;
			}

			cout << "Count: "; cin >> count;
			if (count <= 0) {
				cout << "The count of the book cannot be 0 or negative!" << endl;
				break;
			}

			bool same_book = false, correct_id = true;

			ofstream fout("temp.txt");
			ifstream fin("books.txt");
			while (!fin.eof())
			{
				getline(fin, row);

				if (row != "") {
					string* data = slice_row(row);

					if (data[0] == id) {
						if (data[1] == author and data[2] == title and stoi(data[3]) == price) {
							fout << id << ";" << author << ";" << title << ";" << price << ";" << stoi(data[4]) + count << endl;
							same_book = true;
						}
						else correct_id = false;
					} 
					else fout << row << endl;

					delete[] data;
				}
			}
			fin.close();

			if (!same_book and correct_id) fout << id << ";" << author << ";" << title << ";" << price << ";" << count << endl;
			fout.close();

			if (correct_id) {
				remove("books.txt");
				bool renamed = rename("temp.txt", "books.txt");
				if (renamed) cout << "Error updating 'books.txt'" << endl;

				// Update book_count static variable
				if (!Book::getBooks()) Book::setBooks(book_number());
				else Book::setBooks(Book::getBooks() + count);

				cout << endl << "Book successfully added!" << endl;
			}
			else {
				remove("temp.txt");

				cout << endl << "This ID already belongs to an other book!" << endl;
				cout << "The new book was not added." << endl;
			}
		}
		else if (option == '0') break;
		else cout << "Invalid input!" << endl;

		menu('5');
		cout << endl << "Option: "; cin >> option;

	} while (option != '0');
}