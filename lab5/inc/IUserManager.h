#pragma once

#include "../inc/IUserRepository.h"
#include "../inc/User.h"

class IUserManager {
private:
	IUserRepository user_repo;
	User current_user;
public:
	IUserManager() { LoginMenu(); };
	~IUserManager() {};
	//int PasswordCheck(std::string login, std::string password);
	void SignIn();
	void SignUp();
	void RestoreLast();
	void LoginMenu();
	void SignOut();
	bool IsAuthorized();
};