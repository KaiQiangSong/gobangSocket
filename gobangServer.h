#ifndef GobangServer_H
#define GobangServer_H

#include "msg.h"
#include "msgr.h"
#include "match.h"
#include "mutex.h"

#include <semaphore.h>
#include <vector>
#include <map>
#include <string>
#include <string.h>

typedef std::vector<match>::iterator m_iter;
typedef std::vector<user>::iterator u_iter;

class gobangServer
{
private:
	std::vector<match> matches;
	std::vector<user> users;
	Mutex MatchLock,UserLock;

public:
	gobangServer();
	gobangServer(const gobangServer& x);
	~gobangServer();
	int get_size();
	//Constructor and Distructor

	int add_Match_U(user x);
	int play_Match_U(user x,int px,int py);
	int giveup_Match_U(user x);
	bool exit_Match_U(user x);
	m_iter find(user x);
	//User Operations;
	std::string Reply(std::string msg);
};

#endif