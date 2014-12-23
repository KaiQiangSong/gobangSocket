#ifndef msgr_H
#define msgr_H

#define msgr_reply_addGame (0x1)
#define msgr_reply_playGame (0x2)
#define msgr_reply_giveupGame (0xc)
#define msgr_show (0x10)
#define msgr_verify (0x20)
#define msgr_exit (0x40)

/*
 *
 *					|        GiveupGame		|  PlayGame	|   AddGame
 * Success	|	  01 user     10 _user	|         1			|          1
 *   Failed	|                00					|         0			|          0
 *  Forbid	|               0xc					|		0x2			|		  0x1
 *
 */

#include "match.h"
#include <string>

class msgr{
private:
	int head;
	match m_match;
	int reply_code;
	bool verify;
	bool exit_code;
public:
	msgr():head(0),m_match(),reply_code(0),verify(false),exit_code(false){};
	msgr(const msgr&x);
	msgr(int,match,int,bool,bool);
	msgr(std::string);
	std::string str() const;
	void load(std::string);
	void set_exitCode(bool);
};

#endif
