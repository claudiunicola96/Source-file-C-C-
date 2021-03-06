#pragma once
#include "BookstoreController.h"

class BookstoreConsole {
private:
	BookstoreController& ctrl;

	/**
	* Print the menu of application
	*/
	void printMenu();

	/**
	* Get the command from standard input
	*/
	int getCommand();

	/**
	* Print a Book
	*/
	void print(const Book& book);

	/**
	* Show all books
	*/
	void showUi(const vector<Book>&);

	/**
	* Add a book
	*/
	void addUi();

	/**
	* Delete a book
	*/
	void deleteUi();

	/**
	* Update a book
	*/
	void updateUi();

	/**
	* Search a book
	*/
	void searchBook();

	/**
	* Filter by title
	*/
	void filterByTitle();

	/**
	* Filter by year
	*/
	void filterByYear();

	/**
	* Sort by title
	*/
	void sortByTitle();

	/**
	* Sort by author
	*/
	void sortByAuthor();

	/**
	* Sort by year and subject
	*/
	void sortMultiple();

	/**
	* Add a book in cart
	*/
	void addBookCart();

	/**
	* Empty cart
	*/
	void emptyCart();

	/**
	* Generate random cart
	*/
	void generateCart();

	/**
	* Show cart
	*/
	void showCart();

	/**
	* Export the cart
	*/
	void exportTo(const int);

	/**
	* Undo action 
	*/
	void undo();
public:
	BookstoreConsole(BookstoreController&);
	BookstoreConsole(BookstoreConsole& other) = delete;

	void runApp();

	virtual ~BookstoreConsole();
};