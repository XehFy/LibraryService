#pragma once

#include <string>
#include "Model.h"

namespace View {

	using namespace std;

	class UIfunctions {
	protected:
		void color(int color);
		void gotoxy(int x, int y);
	};

	class UserUI : private UIfunctions {
	public:
		void StartUI(string mod);
		void UserPersonalAccountMenu(Model::User user);
	};
	class AdminUI : private UIfunctions {
	public:
		void StartUI(string mod);
		void AdminPersonalAccountMenu(Model::Admin user);
	};
	class UI : private UIfunctions
	{
	public:
		void StartUI();
	};
}