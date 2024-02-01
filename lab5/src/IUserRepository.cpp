#include <string>
#include <fstream>
#include "../inc/IUserRepository.h"
#include "../inc/User.h"

using namespace std;

IUserRepository::IUserRepository() {
	m_arr.clear();
	this->ReadFile();
}

User IUserRepository::GetById(int id) {
	User sought_user;
	for (User user : m_arr) {
		if (user.m_id == id)
			sought_user = user;
	}
	return sought_user;
};

User IUserRepository::GetByLogin(std::string login) {
	User sought_user;
	for (User user : m_arr) {
		if (user.m_login == login)
			sought_user = user;
	}
	return sought_user;
};

int IUserRepository::GetNewId() {
	return m_arr.size();
}

void IUserRepository::NewUser(User user) {
	ofstream file("../users.txt", ios::app);
	file << user.m_id << " " << user.m_name << " " << user.m_login << " " << user.m_password << "\n";
	file.close();
	this->m_arr.push_back(user);
}

void IUserRepository::ReadFile() {
	std::string data;
	std::ifstream file("../users.txt");
	if (file.is_open()) {
		User user;
		while (file >> user.m_id >> user.m_name >> user.m_login >> user.m_password) {
			m_arr.push_back(user);
		}
		file.close();
	}
};
