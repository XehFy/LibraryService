#include <iostream>
#include <conio.h>
#include <string.h>
#include "windows.h"
#include <stdlib.h>
//#include "Model.cpp"
#include "Controller.h"
#include "View.h"

using namespace std;
using namespace View;

	Controller::UserController userController = Controller::UserController();
	Controller::AdminUserController adminController = Controller::AdminUserController();
	Controller::BookController bookController = Controller::BookController();
	Controller::ReceiptRecordController receiptRecordController = Controller::ReceiptRecordController();

	void UIfunctions::color(int color) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
		}
	void UIfunctions::gotoxy(int x, int y) {
			COORD c;
			c.X = x;
			c.Y = y;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
		}

	void UserUI::StartUI(string mod) {
			if (mod == "auth") {
				system("cls");
				cout << "\t\t\tUser authorisation page\n\n ";
				string login, password;
				cout << "Enter your login: ";
				cin >> login;
				cout << "Enter your password: ";
				cin >> password;
				//ïðîâåðêà íà ñóùåñòâîâàíèå ïîëüçîâàòåëÿ
				Model::User tmp = userController.FindUser(login, password);
				if (tmp.Login!="") {
					UserPersonalAccountMenu(tmp);
				}
				else
				{
					cout << "User not found!";
					system("pause");
					return;
				}
			}
			if (mod == "reg") {
				system("cls");
				cout << "\t\t\tUser regestration page\n\n ";
				string login, password, name;
				cout << "Enter your name: ";
				cin >> name;
				cout << "Enter your login: ";
				cin >> login;
				cout << "Enter your password: ";
				cin >> password;
				Model::User tmp = userController.AddUser(name, login, password);
				//ïîïûòêà äîáàâëåíèÿ íîâîãî ïîëüçîâàòåëÿ, âõîä ïðè óñïåõå
				UserPersonalAccountMenu(tmp);
			}
		}
	void UserUI::UserPersonalAccountMenu(Model::User user) {
			int Colors[] = { 8, 7, 7 };
			int counter = 1;
			char key;
			for (int i = 0;;) {
				system("cls");

				gotoxy(0, 0);
				color(13);
				cout << "Welcome, " << user.Name << "!";
				gotoxy(10, 3);
				cout << "LIBRARY VISITOR";

				gotoxy(40, 0);
				color(10);
				cout << "press BACKSPACE to exit account";

				gotoxy(10, 5);
				color(Colors[0]);
				cout << "Show book list ";

				gotoxy(10, 6);
				color(Colors[1]);
				cout << "Take book by ID ";

				gotoxy(10, 7);
				color(Colors[2]);
				cout << "Show my books ";

				key = _getch();

				if (key == 72 && (counter > 1 && counter <= 3)) {
					counter--;
				}
				if (key == 80 && (counter >= 1 && counter < 3)) {
					counter++;
				}
				if (key == '\r') {
					switch (counter)
					{
					case 1: {
						system("cls");
						color(13);
						gotoxy(10, 3);
						cout << "BOOK LIST";
						gotoxy(0, 5);
						color(7);
						bookController.ShowBooks();
						system("pause");
						break;
					}
					case 2: {
						system("cls");
						int bookId;
						cout << "Enter ID of the book: ";
						cin >> bookId;
						Model::Book book = bookController.FindBook(bookId);
						if (book.Name == "") {
							cout << "There is no book with such ID!" << endl;
							system("pause");
							break;
						}
						receiptRecordController.AddRecord(user.Id, book.Id);
						cout << "The book is added to your usage" << endl;
						system("pause");
						break;
					}
					case 3: {
						system("cls");
						for (int i = 0; i < receiptRecordController.receiptRecords.size(); i++) {
							if (user.Id == receiptRecordController.receiptRecords[i].UserId) {
								Model::Book tmpBook = bookController.FindBook(receiptRecordController.receiptRecords[i].BookId);
								cout << tmpBook.Id << " | " << tmpBook.Name << " | " << tmpBook.Author << endl;
							}
						}
						system("pause");
						break;
					}
					default:
						break;
					}
				}
				Colors[0] = 7;
				Colors[1] = 7;
				Colors[2] = 7;
				if (counter == 1) {
					Colors[0] = 8;
				}
				if (counter == 2) {
					Colors[1] = 8;
				}
				if (counter == 3) {
					Colors[2] = 8;
				}
				if (key == 8) break;
			}
		}

	void AdminUI::StartUI(string mod) {
			if (mod == "auth") {
				system("cls");
				cout << "\t\t\tAdministrator authorisation page\n\n ";
				string login, password;
				cout << "Enter your login: ";
				cin >> login;
				cout << "Enter your password: ";
				cin >> password;
				//ïðîâåðêà íà ñóùåñòâîâàíèå àäìèíèñòðàòîðà
				Model::Admin tmp = adminController.FindAdmin(login, password);
				if (tmp.Login != "") {
					AdminPersonalAccountMenu(tmp);
				}
				else
				{
					cout << "User not found!";
					system("pause");
					return;
				}
			}
			if (mod == "reg") {
				system("cls");
				cout << "\t\t\tAdministration regestration page\n\n ";
				string login, password, name;
				int passportNum;
				cout << "Enter your name: ";
				cin >> name;
				cout << "Enter your login: ";
				cin >> login;
				cout << "Enter your password: ";
				cin >> password;
				cout << "Enter your passport number: ";
				cin >> passportNum;
				Model::Admin tmp = adminController.AddAdmin(name, login, password, passportNum);
				//ïîïûòêà äîáàâëåíèÿ íîâîãî ïîëüçîâàòåëÿ, âõîä ïðè óñïåõå
				if (true) {
					AdminPersonalAccountMenu(tmp);
				}
			}
		}
	void AdminUI::AdminPersonalAccountMenu(Model::Admin user) {
		int Colors[] = { 8, 7, 7 };
		int counter = 1;
		char key;
		for (int i = 0;;) {
			system("cls");

			gotoxy(0, 0);
			color(13);
			cout << "Welcome, " << user.Name << "!";
			gotoxy(10, 3);
			cout << "ADMINISTRATOR";

			gotoxy(40, 0);
			color(10);
			cout << "press BACKSPACE to exit account";

			gotoxy(10, 5);
			color(Colors[0]);
			cout << "Add new book ";

			gotoxy(10, 6);
			color(Colors[1]);
			cout << "Show users ";

			gotoxy(10, 7);
			color(Colors[2]);
			cout << "Admit user returning book ";

			key = _getch();

			if (key == 72 && (counter > 1 && counter <= 3)) {
				counter--;
			}
			if (key == 80 && (counter >= 1 && counter < 3)) {
				counter++;
			}
			if (key == '\r') {
				switch (counter)
				{
				case 1: {
					system("cls");
					string name, author;
					cout << "Enter book name: " << endl;
					//cin >> name;
					getline(cin >> ws, name);
					cout << "Enter author: " << endl;
					//cin >> author;
					getline(cin >> ws, author);
					bookController.AddBook(name, author);
					system("pause");
					break;
				}
				case 2: {
					system("cls");

					system("pause");
					break;
				}
				case 3: {
					system("cls");
					int userId, bookId;
					cout << "Enter user ID: " << endl;
					cin >> userId;
					cout << "Enter book ID: " << endl;
					cin >> bookId;
					Model::ReceiptRecord tmp = receiptRecordController.DeleteRecord(userId, bookId);
					if (tmp.UserId == -1) {
						cout << "There were no such record!" << endl;
						system("pause");
						break;
					}
					cout << "Success!\n";
					system("pause");
					break;
				}
				default:
					break;
				}
			}
			Colors[0] = 7;
			Colors[1] = 7;
			Colors[2] = 7;
			if (counter == 1) {
				Colors[0] = 8;
			}
			if (counter == 2) {
				Colors[1] = 8;
			}
			if (counter == 3) {
				Colors[2] = 8;
			}
			if (key == 8) break;
		}
	}
	
	void UI::StartUI() {
			int Colors[] = { 8, 7, 7, 7 };
			int counter = 1;
			char key;
			UserUI userUI;
			AdminUI adminUI;

			for (int i = 0;;) {
				system("cls");
				gotoxy(10, 5);
				color(Colors[0]);
				cout << "Enter as user ";

				gotoxy(10, 6);
				color(Colors[1]);
				cout << "Enter as administrator ";

				gotoxy(10, 7);
				color(Colors[2]);
				cout << "Register new user ";

				gotoxy(10, 8);
				color(Colors[3]);
				cout << "Register new administrator ";
				key = _getch();

				if (key == 72 && (counter > 1 && counter <= 4)) {
					counter--;
				}
				if (key == 80 && (counter >= 1 && counter < 4)) {
					counter++;
				}
				if (key == '\r') {
					switch (counter)
					{
					case 1: {
						system("cls");
						cout << "User enter";
						userUI.StartUI("auth");
						break;
					}
					case 2: {
						system("cls");
						adminUI.StartUI("auth");
						break;
					}
					case 3: {
						system("cls");
						userUI.StartUI("reg");
						break;
					}
					case 4: {
						system("cls");
						adminUI.StartUI("reg");
						break;
					}
					default:
						break;
					}
				}
				Colors[0] = 7;
				Colors[1] = 7;
				Colors[2] = 7;
				Colors[3] = 7;
				if (counter == 1) {
					Colors[0] = 8;
				}
				if (counter == 2) {
					Colors[1] = 8;
				}
				if (counter == 3) {
					Colors[2] = 8;
				}
				if (counter == 4) {
					Colors[3] = 8;
				}
			}
			
		}
