#include "msgr.h"

#include "string.h"

#include <string>
#include <sstream>

msgr::msgr(const msgr& x)
{
	memcpy(this,&x,sizeof(msgr));
}

msgr::msgr(int h, std::string u1, std::string u2, int st, int sc, int lx, int ly, int reply, bool v, bool ec)
{
	head = h;
	user1=u1;
	user2=u2;
	step =st;
	stateCode = sc;
	last_x = lx;
	last_y = ly;
	reply_code = reply;
	verify = v;
	exit_code = ec;
}

msgr::msgr(std::string message)
{
	std::stringstream ss(message);
	std::string tmp,str;
	//head
	ss >> tmp >> head;
	//verif
	if (head & msgr_verify)
	{
		ss >> tmp >> str;
		if (str =="1")
			verify = true;
		else
			verify = false;
	}
	//reply AddGame
	if (head & msgr_reply_addGame)
	{
		ss >> tmp >> str;
		if (str == "1")
			reply_code |= msgr_reply_addGame;
	}
	//reply PlayGame
	if (head & msgr_reply_playGame)
	{
		ss >> tmp >> str;
		if (str == "1")
			reply_code |= msgr_reply_playGame;
	}
	//reply GiveupGame
	if (head & msgr_reply_giveupGame)
	{
		ss >> tmp >> str;
		if (str == "1")
			reply_code |= msgr_reply_giveupGame;
	}
	//Show State
	if (head & msgr_show)
	{
		std::string u1,u2;
		int state_code,px,py;
		ss >> tmp >> u1 >> tmp >> u2;
		ss >> tmp >> tmp;
		ss >> tmp >> state_code;
		ss >> tmp >> px;
		ss >> tmp >> py;
		user1 = u1;
		user2 = u2;
		stateCode = state_code;
		last_x = px;
		last_y = py;
	}
	//Game exit
	if (head & msgr_exit)
	{
		ss >> tmp >> str;
		if (str == "1")
			exit_code = true;
		else
			exit_code = false;
	} else
		exit_code = false;
}

std::string msgr::str() const
{
	std::stringstream ss;
	//Head
	ss << "Head: " << head << std::endl;
	//std::cout << "Head Done\n";
	// verify
	if (head & msgr_verify)
	{
		ss << "Verfiy: ";
		if (verify)
			ss << "1";
		else
			ss << "0";
		ss << std::endl;
	}
	//std::cout << "Verify Done\n";
	//reply AddGame
	if (head & msgr_reply_addGame)
	{
		ss << "opt_AddGame: ";
		if (reply_code & msgr_reply_addGame)
			ss << "1";
		else
			ss << "0";
		ss << std::endl;
	}
	//std::cout << "AddGame Done\n";
	//reply PlayGame
	if (head & msgr_reply_playGame)
	{
		ss << "opt_PlayGame: ";
		if (reply_code & msgr_reply_playGame)
			ss << "1";
		else
			ss << "0";
		ss << std::endl;
	}
	//std::cout << "PlayGame Done\n";
	//reply GiveupGame
	if (head & msgr_reply_giveupGame)
	{
		ss << "opt_GiveupGame: ";
		if (reply_code & msgr_reply_giveupGame)
			ss << "1";
		else
			ss << "0";
		ss << std::endl;
	}
	//std::cout << "GiveupGame Done\n";
	//Show State
	if (head & msgr_show)
	{
		ss << "user_black: " <<user1<< std::endl;
		ss << "user_white: " << user2 << std::endl;
		ss << "Step: " << step << std::endl;
		ss << "State: " << stateCode << std::endl;
		ss << "PositionX: " << last_x << std::endl;
		ss << "PositionY: " << last_y << std::endl;
	}
	//std::cout << "Show Done\n";
	//Exit Game
	if (head & msgr_exit)
	{
		ss << "Exit: ";
		if (exit_code)
			ss << "1";
		else
			ss << "0";
		ss << std::endl;
	}
	//std::cout << "Exit Done\n";
	return ss.str();
}

void msgr::load(std::string message)
{
	std::stringstream ss(message);
	std::string tmp,str;
	//head
	ss >> tmp >> head;
	//verif;
	if (head & msgr_verify)
	{
		ss >> tmp >> str;
		if (str =="1")
			verify = true;
		else
			verify = false;
	}
	//reply AddGame
	if (head & msgr_reply_addGame)
	{
		ss >> tmp >> str;
		if (str == "1")
			reply_code |= msgr_reply_addGame;
	}
	//reply PlayGame
	if (head & msgr_reply_playGame)
	{
		ss >> tmp >> str;
		if (str == "1")
				reply_code |= msgr_reply_playGame;
	}
	//reply GiveupGame
	if (head & msgr_reply_giveupGame)
	{
		ss >> tmp >> str;
		if (str == "1")
			reply_code |= msgr_reply_giveupGame;
	}
	//Show State
	if (head & msgr_show)
	{
		std::string u1,u2;
		int state_code,px,py;
		ss >> tmp >> u1 >> tmp >> u2;
		ss >> tmp >> tmp;
		ss >> tmp >> state_code;
		ss >> tmp >> px;
		ss >> tmp >> py;
		user1 = u1;
		user2 = u2;
		stateCode = state_code;
		last_x = px;
		last_y = py;
	}
	//Game exit
	if (head & msgr_exit)
	{
		ss >> tmp >> str;
		if (str == "1")
			exit_code = true;
		else
			exit_code = false;
	} else
		exit_code = false;
}

void msgr::set_exitCode(bool ec)
{
	exit_code = ec;
}

std::string msgr::get_u1() const
{
	return user1;
}

std::string msgr::get_u2() const
{
	return user2;
}

int msgr::get_step() const
{
	return step;
}

int msgr::get_lastx() const
{
	return last_x;
}

int msgr::get_lasty() const
{
	return last_y;
}

bool msgr::get_verify() const
{
	return verify;
}

bool msgr::get_exitCode() const
{
	return exit_code;
}

int msgr::get_stateCode() const
{
	return stateCode;
}