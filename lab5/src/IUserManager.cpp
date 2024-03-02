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
	cout << "Ââåäèòå ëîãèí" << endl;
	cin >> login;
	cout << "Ââåäèòå ïàðîëü" << endl;
	cin >> password;
	User user = user_repo.GetByLogin(login);

	if (!user.m_login.empty() && password == user.m_password) {
		current_user = user;
		ofstream file("../sessions.txt");
		file << user.m_id << " " << user.m_name << " " << user.m_login << " " << user.m_password << "\n";
		file.close();

		cout << "Ïîëüçîâàòåëü " << user.m_login << " áûë óñïåøíî àâòîðèçîâàí." << endl;
	}
	else cout << "Ãäå-òî òóò îøèáêà" << endl;
}

void IUserManager::SignOut() {
	ofstream file("../sessions.txt");
	file << " ";
    file.close();
    cout << "Âû âûøëè èç àêêàóíòà." << endl;
	current_user = User();
}

void IUserManager::SignUp() {
	string login, password, name;
	cout << "Ââåäèòå ëîãèí" << endl;
	cin >> login;
	cout << "Ââåäèòå ïàðîëü" << endl;
	cin >> password;
	cout << "Ââåäèòå èìÿ" << endl;
	cin >> name;

	User tmp = user_repo.GetByLogin(login);
	if (!tmp.m_login.empty()) {
		cout << "Ëîãèí çàíÿò" << endl;
	}
	else {
		User user;
		user.m_login = login;
		user.m_name = name;
		user.m_password = password;
		user.m_id = user_repo.GetNewId();
		user_repo.NewUser(user);
		cout << "Ïîëüçîâàòåëü çàðåãèñòðèðîâàí, ââåäèòå äàííûå åùå ðàç, ÷òîáû âîéòè â àêêàóíò" << endl;
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
		cout << "Ïîëüçîâàòåëü " << user.m_login << " áûë óñïåøíî àâòîðèçîâàí." << endl;
	}
	else {
		cout << "Ïîñëåäíåé ñåññèè íå îáíàðóæåíî" << endl;
	}
}

void IUserManager::LoginMenu() {
	while (true) {
		if (!IsAuthorized()) {
			cout << "Êîìàíäû:" << endl << "Âîññòàíîâèòü ïîñëåäíþþ ñåññèþ - 1" << endl << "Âîéòè ñ äðóãîãî àêêàóíòà - 2" << endl << "Çàðåãèñòðèðîâàòüñÿ - 3" << endl << "Çàâåðøèòü ïðîãðàììó - 4" << endl;
		}
		else cout << "Êîìàíäû:" << endl << "Âûéòè - 2" << endl << "Çàâåðøèòü ïðîãðàììó - 4" << endl;
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
		else cout << "Íåèçâåñòíàÿ êîìàíäà" << endl;
	}
}

bool IUserManager::IsAuthorized() {
	return (!current_user.m_login.empty());
};
