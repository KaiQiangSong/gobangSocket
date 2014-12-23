#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>
#include <fstream>

class user
{
public:
	std::string username;
	std::string password;
public:
	user();
	user(std::string name, std::string psd);
	user(const user& x);
	bool user_verify(user x);
	bool user_already_registered();
	bool user_register();
	std::string get_user() const;
	std::string get_psd() const;
	friend bool user_load(std::istream ifs);
	bool operator==(const user&x);

};

#endif