#include <iostream>
#include <string>
#include "book.h"

int Book::book_count = 0;
int Book::income = 0;

Book::Book() {
	id = author = title = "";
	price = count = 0;
}

Book::Book(string id, string author, string title, int price,  int count) {
	this->id = id;
	this->author = author;
	this->title = title;
	this->price = price;
	this->count = count;

	book_count += count;
}

// Total book count
int Book::getBooks() {
	return book_count;
}

void Book::setBooks(int new_count) {
	book_count = new_count;
}

// Total income from the sold books
int Book::getIncome() {
	return income;
}

void Book::setIncome(int new_income) {
	income = new_income;
}

// ID
string Book::getId() const {
	return this->id;
}

void Book::setId(string new_id) {
	this->id = new_id;
}

// Author
string Book::getAuthor() const {
	return this->author;
}

void Book::setAuthor(string new_author) {
	this->author = new_author;
}

// Title
string Book::getTitle() const {
	return this->title;
}

void Book::setTitle(string new_title) {
	this->title = new_title;
}

// Price
int Book::getPrice() const {
	return this->price;
}

void Book::setPrice(int new_price) {
	this->price = new_price;
}

// Count
int Book::getCount() const {
	return this->count;
}

void Book::setCount(int new_count) {
	this->count = new_count;
}

// Every variable
void Book::setAll(string new_id, string new_author, string new_title, int new_price, int new_count) {
	this->id = new_id;
	this->author = new_author;
	this->title = new_title;
	this->price = new_price;
	this->count = new_count;
}

Book::~Book() {}