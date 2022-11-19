#pragma once

#include <vector>
#include "Model.h"
#include "AVL.h"

namespace Controller {

	using namespace std;

	const string userData = "Users.txt";
	const string adminData = "AdminUsers.txt";
	const string bookData = "Books.txt";
	const string receiptRecordData = "ReceiptRecords.txt";

	class UserController {
	public:
		vector<Model::User> users;
		int IdCounter = 0;
		UserController();
		void printUsers();
		Model::User FindUser(std::string login, std::string password);
		Model::User FindUser(int id);
		Model::User AddUser(std::string name, std::string login, std::string password);
	};

	class AdminUserController {
	public:
		vector<Model::Admin> admins;
		int IdCounter = 0;
		AdminUserController();
		Model::Admin FindAdmin(std::string login, std::string password);
		Model::Admin AddAdmin(std::string name, std::string login, std::string password, int passportNumber);
	};

	class BookController {
	public:
		AVL<int, Model::Book> books;
		//vector<Model::Book> books;
		int IdCounter = 0;
		BookController();
		Model::Book FindBook(int id);
		void ShowBooks();
		Model::Book AddBook(std::string name, std::string author);
	};

	class ReceiptRecordController {
	public:
		vector<Model::ReceiptRecord> receiptRecords;
		ReceiptRecordController();
		Model::ReceiptRecord AddRecord(int userId, int bookId);
		Model::ReceiptRecord DeleteRecord(int userId, int bookId);
	};
}
