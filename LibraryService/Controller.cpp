#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Controller.h"
#include "Model.h"


using namespace Controller;
using namespace Model;
using namespace std;

//User implementation
UserController::UserController() {
	string id, name, login, password;
	ifstream data(userData);
	if (data.is_open()) {
		while (getline(data, id, ' '))
		{
			getline(data, name, ' ');
			getline(data, login, ' ');
			getline(data, password, '\n');
			User tmpUser = User(name, login, password);
			tmpUser.Id = stoi(id);
			users.push_back(tmpUser);
			IdCounter++;
		}
		data.close();
	}
}

void UserController::printUsers() {
	for (int i = 0; i < IdCounter; i++) {
		cout << users[i].Name << " " << users[i].Password << endl;
	}
}

User UserController::AddUser(std::string name, std::string login, std::string password) {
	ofstream data(userData, ios::app);

	User tmpUser = User(name, login, password);
	tmpUser.Id = IdCounter + 1;
	data << "\n";
	data << tmpUser.Id << " " << tmpUser.Name << " " << tmpUser.Login << " " << tmpUser.Password;
	data.close();
	users.push_back(tmpUser);
	IdCounter++;
	return tmpUser;
}

User UserController::FindUser(std::string login, std::string password) {
	for (User user : users) {
		if (user.Login == login && user.Password == password) {
			return user;
		}
	}
	User tmp = User("","","");
	return tmp;
}

User UserController::FindUser(int id) {
	for (User user : users) {
		if (user.Id == id) {
			return user;
		}
	}
	User tmp = User("", "", "");
	return tmp;
}

//Admin implementation
AdminUserController::AdminUserController() {
	string id, name, login, password, passportNum;
	ifstream data(adminData);
	if (data.is_open()) {
		while (getline(data, id, ' '))
		{
			getline(data, name, ' ');
			getline(data, login, ' ');
			getline(data, password, ' ');
			getline(data, passportNum, '\n');
			Admin tmpUser = Admin(name, login, password, stoi(passportNum));
			tmpUser.Id = stoi(id);
			admins.push_back(tmpUser);
			IdCounter++;
		}
		data.close();
	}
}

Admin AdminUserController::AddAdmin(std::string name, std::string login, std::string password, int passport) {
	ofstream data(adminData, ios::app);

	Admin tmpUser = Admin(name, login, password, passport);
	tmpUser.Id = IdCounter + 1;
	data << "\n";
	data << tmpUser.Id << " " << tmpUser.Name << " " << tmpUser.Login << " " << tmpUser.Password << " " << tmpUser.PassportNumber;
	data.close();
	admins.push_back(tmpUser);
	IdCounter++;
	return tmpUser;
}

Admin AdminUserController::FindAdmin(std::string login, std::string password) {
	for (Admin user : admins) {
		if (user.Login == login && user.Password == password) {
			return user;
		}
	}
	Admin tmp = Admin("", "", "", -1);
	return tmp;
}

//Book implementation
BookController::BookController() {
	string id, name, author;
	ifstream data(bookData);
	if (data.is_open()) {
		while (getline(data, id))
		{
			getline(data, name);
			getline(data, author);
			Book tmp = Book(name, author);
			tmp.Id = stoi(id);
			books.Insert(tmp.Id, tmp);
			//books.push_back(tmp);
			IdCounter++;
		}
		data.close();
	}
}

void BookController::ShowBooks() {
	AVL<int, Model::Book>::Iterator<int, Model::Book> iter(&books);
	Model::Book book = Book("", "");
	int key = 1;
	bool more;
	more = iter.GetFirst(key, book);
	cout << "-----------------------------------------------------------------" << endl;
	while (more)
	{
		cout << book.Id << " | " << book.Name << " | " << book.Author << endl;
		cout << "-----------------------------------------------------------------" << endl;
		more = iter.GetNext(key, book);
	}
	/*cout << "-----------------------------------------------------------------" << endl;
	for (int i = 0; i < IdCounter; i++) {
		cout << books[i].Id << " | " << books[i].Name << " | " << books[i].Author << endl;
		cout << "-----------------------------------------------------------------" << endl;
	}*/
}

Book BookController::FindBook(int id) {
	/*for (Book book : books) {
		if (book.Id == id) {
			return book;
		}
	}*/
	Book tmp = Book("", "");
	bool more;
	more = books.Find(id, tmp);

	return tmp;
}

Book BookController::AddBook(std::string name, std::string author) {
	ofstream data(bookData, ios::app);

	Book tmpBook = Book(name, author);
	tmpBook.Id = IdCounter + 1;
	//data << "\n";
	data << tmpBook.Id << endl;
	data << tmpBook.Name << endl;
	data << tmpBook.Author << endl;
	data.close();
	//books.push_back(tmpBook);
	books.Insert(tmpBook.Id, tmpBook);
	IdCounter++;
	return tmpBook;
}

//Record implementation
ReceiptRecordController::ReceiptRecordController() {
	string userId, bookId;
	ifstream data(receiptRecordData);
	if (data.is_open()) {
		while (getline(data, userId, ' '))
		{
			getline(data, bookId, '\n');
			ReceiptRecord tmp = ReceiptRecord(stoi(userId), stoi(bookId));
			receiptRecords.push_back(tmp);
		}
		data.close();
	}
}

ReceiptRecord ReceiptRecordController::AddRecord(int userId, int bookId) {
	ofstream data(receiptRecordData, ios::app);

	ReceiptRecord tmp = ReceiptRecord(userId, bookId);
	//data << "\n";
	data << tmp.UserId << " " << tmp.BookId << endl;
	data.close();
	receiptRecords.push_back(tmp);
	return tmp;
}

ReceiptRecord ReceiptRecordController::DeleteRecord(int userId, int bookId) {
	ofstream data(receiptRecordData);

	ReceiptRecord tmp = ReceiptRecord(-1, -1);
	int i = 0;
	bool flag = true;
	/*for (ReceiptRecord record : receiptRecords) {
		if (!(record.UserId == userId && record.BookId == bookId && flag)) {
			data << record.UserId << " " << record.BookId << endl;
			i++;
		}
		else {
			flag = false;
			tmp = record;
			receiptRecords.erase(receiptRecords.begin() + i);
			data << record.UserId << " " << record.BookId << endl;
		}
	}*/
	int length = receiptRecords.size();
	for (int i = 0; i < length; i++) {
		if (!(receiptRecords[i].UserId == userId && receiptRecords[i].BookId == bookId && flag)) {
			data << receiptRecords[i].UserId << " " << receiptRecords[i].BookId << endl;
		}
		else {
			flag = false;
			tmp = receiptRecords[i];
			receiptRecords.erase(receiptRecords.begin() + i);
			i--;
			length--;
		}
	}
	data.close();
	return tmp;
}