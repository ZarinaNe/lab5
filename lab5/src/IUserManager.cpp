#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../inc/User.h"
#include "../inc/IUserRepository.h"
#include "../inc/IUserManager.h"

using namespace std;


void IUserManager::SignIn() {
	string login, password;
	cout << "Введите логин" << endl;
	cin >> login;
	cout << "Введите пароль" << endl;
	cin >> password;
	User user = user_repo.GetByLogin(login);

	if (!user.m_login.empty() && password == user.m_password) {
		current_user = user;
		ofstream file("../sessions.txt");
		file << user.m_id << " " << user.m_name << " " << user.m_login << " " << user.m_password << "\n";
		file.close();

		cout << "Пользователь " << user.m_login << " был успешно авторизован." << endl;
	}
	else cout << "Где-то тут ошибка" << endl;
}

void IUserManager::SignOut() {
	ofstream file("../sessions.txt");
	file << " ";
    file.close();
    cout << "Вы вышли из аккаунта." << endl;
	current_user = User();
}

void IUserManager::SignUp() {
	string login, password, name;
	cout << "Введите логин" << endl;
	cin >> login;
	cout << "Введите пароль" << endl;
	cin >> password;
	cout << "Введите имя" << endl;
	cin >> name;

	User tmp = user_repo.GetByLogin(login);
	if (!tmp.m_login.empty()) {
		cout << "Логин занят" << endl;
	}
	else {
		User user;
		user.m_login = login;
		user.m_name = name;
		user.m_password = password;
		user.m_id = user_repo.GetNewId();
		user_repo.NewUser(user);
		cout << "Пользователь зарегистрирован, введите данные еще раз, чтобы войти в аккаунт" << endl;
		SignIn();
	}
}

void IUserManager::RestoreLast() {
	ifstream file("../sessions.txt");
	int id = -1;
	if (file.is_open()) {
		file >> id;
		file.close();
	}
	User user = user_repo.GetById(id);
	if (!user.m_login.empty()) {
		current_user = user;
		cout << "Пользователь " << user.m_login << " был успешно авторизован." << endl;
	}
	else {
		cout << "Последней сессии не обнаружено" << endl;
	}
}

void IUserManager::LoginMenu() {
	while (true) {
		if (!IsAuthorized()) {
			cout << "Команды:" << endl << "Восстановить последнюю сессию - 1" << endl << "Войти с другого аккаунта - 2" << endl << "Зарегистрироваться - 3" << endl << "Завершить программу - 4" << endl;
		}
		else cout << "Команды:" << endl << "Выйти - 2" << endl << "Завершить программу - 4" << endl;
		int command;
		cin >> command;
		if (command == 1 && !IsAuthorized()) {
			RestoreLast();
		}
		else if (command == 2) {
			if (!IsAuthorized()) SignIn();
			else SignOut();
		}
		else if (command == 3 && !IsAuthorized()) {
			SignUp();
		}
		else if (command == 4) {
			break;
		}
		else cout << "Неизвестная команда" << endl;
	}
}

bool IUserManager::IsAuthorized() {
	return (!current_user.m_login.empty());
};
