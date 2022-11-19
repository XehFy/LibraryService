#pragma once

#include <string>
#include <vector>

namespace Model {

	using namespace std;

	struct ReceiptRecord
	{
		ReceiptRecord(int userId, int bookId);
		int UserId;
		int BookId;
	};

	class Book {
	public:
		Book();
		Book(std::string name, std::string author);
		int Id;
		std::string Name;
		std::string Author;
	};

	class User
	{
	public:
		User(std::string name, std::string login, std::string password);
		int Id;
		std::string Name;
		std::string Login;
		std::string Password;
		//vector<Book> Books;
	};

	class Admin {
	public:
		Admin(std::string name, std::string login, std::string password, int passportNumber);
		int Id;
		std::string Name;
		std::string Login;
		std::string Password;
		int PassportNumber;
	};
}
