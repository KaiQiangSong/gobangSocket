#include "gobangServer.h"

gobangServer::gobangServer():matches(),users(),MatchLock(),UserLock(){}

gobangServer::gobangServer(const gobangServer& x)
{
	for (auto it : x.matches)
		matches.push_back(it);
	for (auto it : x.users)
		users.push_back(it);
	MatchLock = x.MatchLock;
	UserLock = x.UserLock;
}

gobangServer::~gobangServer()
{
	matches.clear();
	users.clear();
}

int gobangServer::get_size()
{
	MatchLock.Lock();
	int size = matches.size();
	MatchLock.Unlock();
	return size;
}

int gobangServer::add_Match_U(user x)
{
	UserLock.Lock();
	users.push_back(x);
	UserLock.Unlock();
	//push in Queue

	UserLock.Lock();
	if (users.size() > 1)
	{
		user x = users[0];
		user y = users[1];
		users.clear();
		match M(x,y);
		M.set_StateCode(0);
		MatchLock.Lock();
		matches.push_back(M);
		MatchLock.Unlock();
	}
	UserLock.Unlock();
	//get Match

	return msgr_reply_addGame;
}

int gobangServer::play_Match_U(user x, int px, int py)
{
	MatchLock.Lock();
	m_iter it = find(x);
	if (it == matches.end())
	{
		MatchLock.Unlock();
		return 0;
	}
	char z;
	if (x == it->get_p1())
		z = 'b';
	else
		z = 'w';
	bool rc = it->set_pos(px,py,z);
	MatchLock.Unlock();
	if (rc)
		return msgr_reply_playGame;
	return 0;
}

int gobangServer::giveup_Match_U(user x)
{
	MatchLock.Lock();
	m_iter it = find(x);
	if (it == matches.end())
	{
		MatchLock.Unlock();
		return 0;
	}
	int stateCode;
	if (x == it->get_p1())
		stateCode = 0x4;
	else
		stateCode = 0x5;
	it->set_StateCode(stateCode);
	MatchLock.Unlock();
	return msgr_reply_giveupGame;
}

bool gobangServer::exit_Match_U(user x)
{
	MatchLock.Lock();
	m_iter it = find(x);
	if (it == matches.end())
	{
		MatchLock.Unlock();
		return false;
	}
	if (x == it->get_p1())
		it->exitGame(0x1);
	else
		it->exitGame(0x2);
	if (it->get_exitCode() == 3)
		matches.erase(it);
	MatchLock.Unlock();
	return true;
}

m_iter gobangServer::find(user x)
{
	m_iter it;
	for (it = matches.begin(); it != matches.end(); ++it)
		if ( x == it->get_p1() || x == it->get_p2())
			break;
	return it;
}

std::string gobangServer::Reply(std::string message)
{
	msg input(message);
	int px,py;
	int reply_code = 0, head = 0;
	user x(input.get_user(),input.get_psd());
	bool verify = x.user_already_registered();
	bool exit_code = false;
	head |= msgr_verify;
	reply_code |= msgr_verify;
	if (verify)
	{
		int opt = input.get_opt();
		switch(opt)
		{
			case 0 :
				head |= msgr_show;
				break;
			case 1:
				head |= msgr_show;
				reply_code |= add_Match_U(x);
				head |= msgr_reply_addGame;
				break;
			case 2:
				head |= msgr_show;
				px = input.get_posx();
				py = input.get_posy();
				reply_code |= play_Match_U(x,px,py);
				head |= msgr_reply_playGame;
				break;
			case 3:
				head |= msgr_show;
				reply_code |= giveup_Match_U(x);
				head |= msgr_reply_giveupGame;
				break;
			default:
				head |= msgr_exit;
				exit_code = exit_Match_U(x);
				break;
		}
	}
	MatchLock.Lock();
	m_iter it = gobangServer::find(x);
	if (it!=matches.end())
	{
		match m_match(*it);
		MatchLock.Unlock();
		msgr output(head,m_match,reply_code,verify,exit_code);
		return output.str();
	}
	match m_match;
	MatchLock.Unlock();
	msgr output(head,m_match,reply_code,verify,exit_code);
	return output.str();
}
