#include "gobang.h"

bool gobang::set_pos(int x, int y, char z)
{
	if (z == 'b' || z == 'w')
	{
		board[x][y] = z;
		last_x = x;
		last_y = y;
		bool flag = check_win();
		if (flag)
		{
			if (z == 'b')
				state_code = goBang_Win_Black;
			else
				state_code = goBang_Win_White;
		} else
		{
			if (z == 'b')
				state_code = goBang_Wait_White;
			else
				state_code = goBang_Wait_Black;
		}
		return true;
	}
	return false;
}

char gobang::get_pos(int x, int y) const
{
	return board[x][y];
}

bool gobang::in_board(int x, int y) const
{
	return (0<=x && x<SIZE && 0<=y && y<SIZE);
}

char gobang::check_win() const
{
	for (int i = 0; i < SIZE; ++i)
	{
		char cur = board[i][0];
		int cnt = 0;
		for (int j = 1; j < SIZE; ++j)
		{
			if (board[i][j] == cur)
				++cnt;
			else
			{
				cur = board[i][j];
				cnt = 0;
			}
			if (cnt >= 5) return cur;
		}
	}
	//Check Each Row
	for (int i = 0; i < SIZE; ++i)
	{
		char cur = board[0][i];
		int cnt = 0;
		for (int j = 1; j < SIZE; ++j)
		{
			if (board[j][i] == cur)
				++cnt;
			else
			{
				cur = board[j][i];
				cnt = 0;
			}
			if (cnt >= 5) return cur;
		}
	}
	//Check Each Col
	for (int k = -SIZE + 1; k < SIZE; ++k)
	{
		bool first = true;
		char cur;
		int cnt;
		for (int i = 0; i < SIZE; ++i)
		{
			int j = i + k;
			if (in_board(i, j))
			{
				if (first)
				{
					first = false;
					cur = board[i][j];
				}
				if (board[i][j] == cur)
					++cnt;
				if (cnt >= 5) return cur;
			}
		}
	}
	//right down
	for (int k = 0; k < SIZE * 2 + 1; ++k)
	{
		bool first = true;
		char cur;
		int cnt;
		for (int i = 0; i < SIZE; ++i)
		{
			int j = k - i;
			if (in_board(i, j))
			{
				if (first)
				{
					first = false;
					cur = board[i][j];
				}
				if (board[i][j] == cur)
					++cnt;
				if (cnt >= 5) return cur;
			}
		}
	}
	return 'n';
}


int gobang::get_lastx() const
{
	return last_x;
}

int gobang::get_lasty() const
{
	return last_y;
}

void gobang::set_lastx(int x)
{
	last_x = x;
}

void gobang::set_lasty(int y)
{
	last_y = y;
}