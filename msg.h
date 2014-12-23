#ifndef msg_H
#define msg_H

#include <string>

/*
 *
 * OPT = 0 ASK
 * OPT = 1 Add Game
 * OPT = 2 Play Game
 * OPT = 3 Giveup GAME
 * OPT = 4 End GAME
 *
 */

class msg
{
private:
	std::string username;
	std::string password;
	int opt;
	int pos_x,pos_y;
public:
	msg(const msg& x);
	msg(std::string user,std::string psd,int op,int px,int py);
	msg(std::string);
	std::string str();
	void load(std::string);
	std::string get_user() const;
	std::string get_psd() const;
	int get_opt() const;
	int get_posx() const;
	int get_posy() const;
};

#endif