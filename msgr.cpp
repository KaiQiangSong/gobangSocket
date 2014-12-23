#include "msgr.h"

#include "string.h"

#include <string>
#include <sstream>

msgr::msgr(const msgr& x)
{
	memcpy(this,&x,sizeof(msgr));
}

msgr::msgr(int h,match mm,int reply, bool v, bool ec)
{
	head = h;
	m_match = mm;
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
		user p1(u1,"");
		user p2(u2,"");
		m_match.set_p1(p1);
		m_match.set_p2(p2);
		m_match.set_StateCode(state_code);
		m_match.set_lastx(px);
		m_match.set_lasty(py);
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
	//Show State
	if (head & msgr_show)
	{
		ss << "user_black: " << m_match.get_p1().get_user() << std::endl;
		ss << "user_white: " << m_match.get_p2().get_user() << std::endl;
		ss << "Step: " << m_match.get_step() << std::endl;
		ss << "State: " << m_match.get_stateCode() << std::endl;
		ss << "PositionX: " << m_match.get_lastx();
		ss << "PositionY: " << m_match.get_lasty();
	}
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
		user p1(u1,"");
		user p2(u2,"");
		m_match.set_p1(p1);
		m_match.set_p2(p2);
		m_match.set_StateCode(state_code);
		m_match.set_lastx(px);
		m_match.set_lasty(py);
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
