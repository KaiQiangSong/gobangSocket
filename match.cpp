#include "match.h"

#include <string.h>

match::match():p1(),p2()
{
	memset(board,0,sizeof(board));
	id = 0;
	state_code = -1;
	last_x =-1;
	last_y = -1;
	exit_code = 0;
}

match::match(user x, user y):p1(x),p2(y)
{
	memset(board,0,sizeof(board));
	id = 0;
	state_code = -1;
	last_x =-1;
	last_y = -1;
	exit_code = 0;
}

match::match(const match& x):p1(x.p1),p2(x.p2),exit_code(x.exit_code)
{
	last_x = x.last_x;
	last_y = x.last_y;
	state_code = x.state_code;
	memcpy(&board,&(x.board),sizeof(board));
}

int match::get_id() const
{
	return id;
}

user match::get_p1() const
{
	return p1;
}

user match::get_p2() const
{
	return p2;
}

int match::get_step() const
{
	int step = 0;
	for (int i = 0; i < SIZE; ++i)
		for (int j = 0; j < SIZE; ++j)
			if (board[i][j] != 0)
				++step;
	return step;
}

int match::get_stateCode() const
{
	return state_code;
}


void match::set_id(int x)
{
	id = x;
}

void match::set_p1(user x)
{
	p1 = x;
	std::cout << "P1:" << p1.get_user() << " " << p1.get_psd() <<std::endl;
	std::cout << "X:" << x.get_user() << " " << x.get_psd() <<std::endl;
}

void match::set_p2(user x)
{
	p2 = x;
}

void match::set_StateCode(int x)
{
	state_code = x;
}

void match::exitGame(int x)
{
	exit_code |= x;
}

int match::get_exitCode() const
{
	return exit_code;
}

const match& match::operator = (match m)
{
 	memcpy(this,&m,sizeof(match));
	return (*this);
}
