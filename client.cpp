#include "clientSocket.h"
#include "socketexception.h"

#include "msg.h"
#include "msgr.h"
#include <string>
#include <cstdlib>

using namespace std;


const int black = 1;
const int empty = 0;
const int white = -1;


ClientSocket *clientSocket;
std::string *username;
std::string *password;
int Board[SIZE][SIZE];
bool isBegin, exitCode;
int step , color, stateCode;
msgr * reply;

std::string ShowGame()
{
	msg(*username,*password,0,-1,-1);
	return msg.str();
}

std::string AddGame()
{
	msg(*username,*password,1,-1,-1);
	return msg.str();
}

std::string PlayGame(int px, int py)
{
	msg(*username,*password,2,px,py);
	return msg.str();
}

std::string GiveupGame()
{
	msg(*username,*password,3,-1,-1);
	return msg.str();
}

std::string EndGame()
{
	msg(*username,*password,4,-1,-1);
	return msg.str();
}


void Print_Head()
{
	cout << "Hello, my friend. This is a small UI for gobang Game\n";
	cout << "KaiQiangSong  @ CopyRight\n";
	if (!isBegin)
		cout << "Operation 1 for NewGame\n";
	else
	{
		cout << "Operation 2 for PlayGame\n";
		cout << "Operation 3 for GiveupGame\n";
	}
	cout << "Operation 4 for ExitGame\n";
}

void Init()
{
	isBegin = false;
	exitCode = false;
	color = empty;
	step = 0;
	stateCode = 0;
}

void Add_Game_U()
{
	string message;
	clientSocket->Send(AddGame());
	clientSocket->Receive(message);
	reply = new msgr(message);
	if (reply->get_verify())
	{
		isBegin = true;
		if (*username == reply->get_u1())
			color = black;
		else
			color = white;
	}
	delete reply;
}

void Play_Game_U(int x, int y)
{
	string message;
	clientSocket->Send(PlayGame(x,y));
	clientSocket->Receive(message);

	reply = new msgr(message);
	if (reply->get_verify())
	{
		step= reply->get_step();
		stateCode = reply->get_stateCode();
		if (stateCode == goBang_Wait_Black && color == black || stateCode == goBang_Wait_White && color == white)
		{
			Board[x][y] = color;
		}
	}
	delete reply;
}

bool Wait_Game_U()
{
	string message;
	clientSocket->Send(ShowGame());
	clientSocket->Receive(message);

	reply = new msgr(message);
	if (reply->get_verify())
	{
		step = reply->get_step;
		stateCode = reply->get_stateCode();
		if (step > 0)
			Board[reply->get_lastx()][reply->get_lasty()] = -color;
		if (stateCode > 1 || step == SIZE * SIZE)
		{
			delete reply;
			return false;
		}
		if (stateCode == goBang_Wait_Black && color == black || stateCode == goBang_Wait_White && color == white)
		{
			delete reply;
			return false;
		}
	}
	delete reply;
	return true;
}

void Giveup_Game_U()
{
	string message;
	clientSocket->Send(GiveupGame());
	clientSocket->Receive(message);
	reply = new msgr(message);
	delete reply;
}

void End_Game_U()
{
	string message;
	clientSocket->Send(EndGame());
	clientSocket->Receive(message);
	reply = new msgr(message);
	delete reply;
}

void Win_Black()
{
	if (color == black)
		cout << "你赢啦!\n";
	else
		cout << "你输啦!\n";
}

void Win_White()
{
	if (color == white)
		cout << "你赢啦!\n";
	else
		cout << "你输啦!\n";

}

void Giveup_Black()
{
	if (color == white)
		cout << "对手认输,你赢了!\n";
	else
		cout << "认输成功,你输了!\n";
}

void Giveup_White()
{
	if (color == black)
		cout << "对手认输,你赢了!\n";
	else
		cout << "认输成功,你输了!\n";
}

void Draw()
{
	cout << "平局\n";
}

void UI()
{
	Init();
	int opt = 0;
	int x, y;
	while (!exitCode)
	{
		Print_Head();
		while (Wait_Game_U());
		if (stateCode > 1)
		{
			switch (stateCode)
			{
				case 2:
					Win_Black();
					break;
				case 3:
					Win_White();
					break;
				case 4:
					Giveup_Black();
					break;
				case 5:
					Giveup_White();
					break;
				default:
					break;
			}
			Init();
		}
		if (step == SIZE*SIZE)
		{
			Draw();
			Init();
		}
		cin >> opt;
		switch(opt)
		{
			//Add Game
			case 1:
				Add_Game_U();
				break;
			case 2:
				cin >> x >> y;
				Play_Game_U(x,y);
				break;
			case 3:
				Giveup_Game_U();
				break;
			case 4:
				Giveup_Game_U();
				End_Game_U();
			default:
				break;
		}
		system("clear");
	}
}


int main(int argc,char *argv[])
{
	username = new string(argv[1]);
	password = new string(argv[2]);

	cout << "Running Client ..." << endl;
	cout << "Username : " << *username << endl;

	try
	{
		clientSocket = new ClientSocket("127.0.0.1",12345);
	}
	catch( SocketException& ex)
	{
		cout << "Exception was caught:" << ex.Description() << endl;
	}
	return 0;
}
