#include <iostream>
#include "inc/IUserManager.h"

int main()
{
    setlocale(LC_ALL, "Russian");
    IUserManager user_manager;
    user_manager.LoginMenu();
}