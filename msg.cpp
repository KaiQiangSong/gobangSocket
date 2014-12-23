#include "msg.h"

#include "string.h"
#include <sstream>

msg::msg(const msg& x)
{
	memcpy(this,&x,sizeof(msg));
}


msg::msg(std::string user, std::string psd,int op, int px, int py)
{
	username = user;
	password = psd;
	opt = op;
	pos_x = px;
	pos_y = py;
}

msg::msg(std::string message)
{
	std::stringstream ss;
	std::string tmp;
	ss >> tmp >> username;
	ss >> tmp >> password;
	ss >> tmp >> opt;
	if (opt == 2)
	{
		ss >> tmp >> pos_x;
		ss >> tmp >> pos_y;
	} else
	{
		pos_x = 0;
		pos_y = 0;
	}
}

std::string msg::str()
{
	std::stringstream ss;
	//User Info
	ss << "Username: " << username << std::endl;
	ss << "Password: " << password << std::endl;
	//Opteration
	ss << "Operation: "  << opt << std::endl;
	if (opt == 2)
	{
		ss << "Position_X: " << pos_x << std::endl;
		ss << "Position_Y: " << pos_y << std::endl;
	}
	return ss.str();
}

void msg::load(std::string message)
{
	std::stringstream ss(message);
	std::string tmp;
	ss >> tmp >> username;
	ss >> tmp >> password;
	ss >> tmp >> opt;
	if (opt == 2)
	{
		ss >> tmp >> pos_x;
		ss >> tmp >> pos_y;
	} else
	{
		pos_x = 0;
		pos_y = 0;
	}
}

std::string msg::get_user() const
{
	return username;
}

std::string msg::get_psd() const
{
	return password;
}


int msg::get_opt() const
{
	return opt;
}

int msg::get_posx() const
{
	return pos_x;
}

int msg::get_posy() const
{
	return pos_y;
}
