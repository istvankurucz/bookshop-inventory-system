#ifndef __BOOK_H  
#define __BOOK_H

#include <iostream>
#include <string>

using namespace std;

class Book {
private:
	static int book_count, income;
	string id, author, title;
	int price, count;

public:
	Book();
	Book(string id, string author, string title, int price, int count);

	static int getBooks();
	static void setBooks(int new_count);

	static int getIncome();
	static void setIncome(int new_income);

	string getId() const;
	void setId(string new_id);

	string getAuthor() const;
	void setAuthor(string new_author);

	string getTitle() const;
	void setTitle(string new_title);

	int getPrice() const;
	void setPrice(int new_price);

	int getCount() const;
	void setCount(int new_count);

	void setAll(string new_id, string new_author, string new_title, int new_price, int new_count);

	~Book();
};

#endif