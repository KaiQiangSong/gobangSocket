#ifndef MATCH_H
#define MATCH_H

#include "gobang.h"
#include "user.h"

class match : public gobang
{
private:
	int id;
	user p1 ,p2;
	int exit_code;

public:
	match();
	match(const match& x);
	match(user x, user y);
	int get_id() const;
	user get_p1() const;
	user get_p2() const;
	int get_step() const;
	int get_stateCode() const;
	int get_exitCode() const;
	void set_id(int x);
	void set_p1(user x);
	void set_p2(user x);
	void set_StateCode(int x);
	void exitGame(int x);
};

#endif
