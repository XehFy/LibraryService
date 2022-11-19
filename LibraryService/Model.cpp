#include <stdlib.h>
#include <string>
#include <vector>
#include "Model.h"

using namespace std;
using namespace Model;
	
	Book::Book() {
		Name = "";
		Author = "";
	}
	Book::Book(string name, string author) {
		Name = name;
		Author = author;
	}

	User::User(string name, string login, string password) {
		Name = name;
		Login = login;
		Password = password;
	}

	Admin::Admin(string name, string login, string password, int passportNumber) {
		Name = name;
		Login = login;
		Password = password;
		PassportNumber = passportNumber;
	}

	ReceiptRecord::ReceiptRecord(int userId, int bookId) {
		UserId = userId;
		BookId = bookId;
	}
