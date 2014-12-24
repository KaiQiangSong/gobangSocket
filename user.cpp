#include "user.h"

user::user():username(""),password(""){};

user::user(std::string name, std::string psd)
{
	username = name;
	password = psd;
}

user::user(const user&x)
{
	username = x.username;
	password = x.password;
}

bool user::user_verify(user x)
{
	return (x.username==username && x.password == password);
}

bool user_load(std::istream &ifs,user &x)
{
	return (ifs >> x.username >> x.password);
	//return (x.username == "");
}

bool user::user_already_registered()
{
	std::ifstream ifs("user.list");
	user x;
	while (user_load(ifs,x))
	{
		//std::cout << x.username << "@"<< x.password << std::endl;
		//std::cout << username <<"#"<< password <<std::endl;
		if (x.user_verify(*this))
		{
			ifs.close();
			return true;
		}
	}
	ifs.close();
	return false;
}

bool user::user_register()
{
	if (this->user_already_registered())
		return false;
	std::ofstream ofs("user.list", std::ios::app);
	ofs<< username << " " << password << std::endl;
	ofs.close();
	return true;
}

std::string user::get_user() const
{
	return username;
}

std::string user::get_psd() const
{
	return password;
}


bool user::operator == (const user&x)
{
	return (username == x.get_user() && password == x.get_psd());
}

const user& user::operator = (user x)
{
	username = x.username;
	password = x.password;
	return (*this);
}
