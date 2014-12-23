#ifndef GOBANG
#define GOBANG

#define SIZE (15)

#define goBang_Wait_Black (0x0)
#define goBang_Wait_White (0x1)
#define goBang_Win_Black (0x2)
#define goBang_Win_White (0x3)
#define goBang_Giveup_Black (0x5)
#define goBang_Giveup_White (0x6)

class gobang
{
protected:
	char board[15][15];
	int last_x, last_y;
	int state_code;
	/*
	 * 0x0 : playing waiting for black
	 * 0x1 : playing waiting for white
	 * 0x2 : black win
	 * 0x3 : white win
	 * 0x4 : black giveup
	 * 0x5 : white giveup
	 */
public:
	bool set_pos(int x, int y, char z);
	char get_pos(int x, int y) const;
	char check_win() const;
	bool in_board(int x, int y) const;
	int get_lastx() const;
	int get_lasty() const;
	void set_lastx(int);
	void set_lasty(int);
};

#endif
