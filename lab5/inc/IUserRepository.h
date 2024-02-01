#pragma once

#include "../inc/IDataRepository.h"
#include "../inc/User.h"

class IUserRepository : IDataRepository<User> {

public:
	IUserRepository();
	User GetById(int id);
	User GetByLogin(std::string login);
	int GetNewId();
	void NewUser(User user);
	void ReadFile();
};