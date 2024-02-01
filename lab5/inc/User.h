#pragma once

#include <iostream>

class User {
public:

	int m_id;
	std::string m_name;
	std::string m_login;
	std::string m_password;

	User() {}
	User(int id, std::string name, std::string login, std::string password) {
		m_id = id;
		m_name = name;
		m_login = login;
		m_password = password;
	}
	bool operator==(const User& user) {
		return user.m_id == m_id;
	}
	~User() {}
	int GetId() { return m_id; }
	std::string GetName() { return m_name; }
	std::string GetLogin() { return m_login; }
	std::string GetPassword() { return m_password; }
};