#include <stdio.h>
#include <windows.h>

bool sctr_X[3][3];
bool sctr_O[3][3];

class screen
{
	public:
		screen();
		~screen();
		void print_screen();
		void krest(int, int);
		void nol(int, int);
		char buf_screen[380];
	private:
		COORD pos;
		HANDLE output;
} mscreen;

screen::screen()
{
	memset(this->buf_screen, ' ', 380);
	this->pos.X = 0;
	this->pos.Y = 0;
	this->output = GetStdHandle(STD_OUTPUT_HANDLE);
}

screen::~screen()
{
	
}

void screen::print_screen()
{
	SetConsoleCursorPosition(this->output, this->pos);
	for(int i = 0; i < 380; i++)
		printf("%c", this->buf_screen[i]);
}

void screen::krest(int num_strok, int num_stolb)
{
	num_stolb += 1;
	this->buf_screen[num_strok * 20 + num_stolb] = '*';
	this->buf_screen[(num_strok - 1) * 20 + (num_stolb - 1)] = '*';
	this->buf_screen[(num_strok - 1) * 20 + (num_stolb + 1)] = '*';
	this->buf_screen[(num_strok + 1) * 20 + (num_stolb - 1)] = '*';
	this->buf_screen[(num_strok + 1) * 20 + (num_stolb + 1)] = '*';
}

void screen::nol(int num_strok, int num_stolb)
{
	num_stolb += 1;
	this->buf_screen[(num_strok - 1) * 20 + num_stolb] = '*';
	this->buf_screen[(num_strok + 1) * 20 + num_stolb] = '*';
	this->buf_screen[num_strok * 20 + (num_stolb + 1)] = '*';
	this->buf_screen[num_strok * 20 + (num_stolb - 1)] = '*';
}

class game
{
	public:
		game();
		~game();
		void game_start();
		void format_level();
		bool game_over();
		bool player_O();
		bool player_X();
	private:
};

game::game()
{
	
}

game::~game()
{
	
}

void game::game_start()
{
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			sctr_X[i][j] = false;
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			sctr_O[i][j] = false;
	mscreen.buf_screen[3 * 20 + 4] = '1';
	mscreen.buf_screen[3 * 20 + 10] = '2';
	mscreen.buf_screen[3 * 20 + 16] = '3';
	mscreen.buf_screen[9 * 20 + 4] = '4';
	mscreen.buf_screen[9 * 20 + 10] = '5';
	mscreen.buf_screen[9 * 20 + 16] = '6';
	mscreen.buf_screen[15 * 20 + 4] = '7';
	mscreen.buf_screen[15 * 20 + 10] = '8';
	mscreen.buf_screen[15 * 20 + 16] = '9';
}

bool game::game_over()
{
	if((sctr_X[0][0] && sctr_X[0][1] && sctr_X[0][2]) ||
	   (sctr_X[1][0] && sctr_X[1][1] && sctr_X[1][2]) ||
	   (sctr_X[2][0] && sctr_X[2][1] && sctr_X[2][2]) ||
	   (sctr_X[0][0] && sctr_X[1][0] && sctr_X[2][0]) ||
	   (sctr_X[0][1] && sctr_X[1][1] && sctr_X[2][1]) ||
	   (sctr_X[0][2] && sctr_X[1][2] && sctr_X[2][2]) ||
	   (sctr_X[0][0] && sctr_X[1][1] && sctr_X[2][2]) ||
	   (sctr_X[0][2] && sctr_X[1][1] && sctr_X[2][0]))
	   {
		   printf("\nKrestiki pobedili.\n");
		   return false;
	   }

	if((sctr_O[0][0] && sctr_O[0][1] && sctr_O[0][2]) ||
	   (sctr_O[1][0] && sctr_O[1][1] && sctr_O[1][2]) ||
	   (sctr_O[2][0] && sctr_O[2][1] && sctr_O[2][2]) ||
	   (sctr_O[0][0] && sctr_O[1][0] && sctr_O[2][0]) ||
	   (sctr_O[0][1] && sctr_O[1][1] && sctr_O[2][1]) ||
	   (sctr_O[0][2] && sctr_O[1][2] && sctr_O[2][2]) ||
	   (sctr_O[0][0] && sctr_O[1][1] && sctr_O[2][2]) ||
	   (sctr_O[0][2] && sctr_O[1][1] && sctr_O[2][0]))
	   {
		   printf("\nNoliki pobedili.\n");
		   return false;
	   }
	if((mscreen.buf_screen[3 * 20 + 4] != '1') &&
	   (mscreen.buf_screen[3 * 20 + 10] != '2') &&
	   (mscreen.buf_screen[3 * 20 + 16] != '3') &&
	   (mscreen.buf_screen[9 * 20 + 4] != '4') &&
	   (mscreen.buf_screen[9 * 20 + 10] != '5') &&
	   (mscreen.buf_screen[9 * 20 + 16] != '6') &&
	   (mscreen.buf_screen[15 * 20 + 4] != '7') &&
	   (mscreen.buf_screen[15 * 20 + 10] != '8') &&
	   (mscreen.buf_screen[15 * 20 + 16] != '9')
	   )
	   {
		   printf("\nNich'ya.\n");
		   return false;
	   }
	return true;
}

void game::format_level()
{
	//верхняя и нижняя граница рамки
	for(int i = 0; i < 19; i++)
	{
		mscreen.buf_screen[0 * 20 + i] = '#';
		mscreen.buf_screen[18 * 20 + i] = '#';
	}
	//правая и левая гранца рамки
	for(int i = 0; i < 19; i++)
	{
		mscreen.buf_screen[i * 20 + 1] = '#';
		mscreen.buf_screen[i * 20 + 19] = '#';
	}
	//вертикальное разграничение поля
	for(int i = 0; i < 19; i++)
	{
		mscreen.buf_screen[i * 20 + 7] = '#';
		mscreen.buf_screen[i * 20 + 13] = '#';
	}
	//горизонтальное разграничение поля
	for(int i = 0; i < 19; i++)
	{
		mscreen.buf_screen[6 * 20 + i] = '#';
		mscreen.buf_screen[12 * 20 + i] = '#';
	}
	for(int i = 0; i < 19; i++)
		mscreen.buf_screen[i * 20] = '\n';
	mscreen.buf_screen[380] = '\n';
	mscreen.print_screen();
}

bool game::player_X()
{
	if(GetAsyncKeyState('1') && (!sctr_X[0][0]) && (!sctr_O[0][0]))
	{
		mscreen.krest(3, 3);
		sctr_X[0][0] = true;
		return true;
	}
	if(GetAsyncKeyState('2') && (!sctr_X[0][1]) && (!sctr_O[0][1]))
	{	
		mscreen.krest(3, 9);
		sctr_X[0][1] = true;
		return true;
	}	
	if(GetAsyncKeyState('3') && (!sctr_X[0][2]) && (!sctr_O[0][2]))
	{	
		mscreen.krest(3, 15);
		sctr_X[0][2] = true;
		return true;
	}	
	if(GetAsyncKeyState('4') && (!sctr_X[1][0]) && (!sctr_O[1][0]))
	{	
		mscreen.krest(9, 3);
		sctr_X[1][0] = true;
		return true;
	}	
	if(GetAsyncKeyState('5') && (!sctr_X[1][1]) && (!sctr_O[1][1]))
	{	
		mscreen.krest(9, 9);
		sctr_X[1][1] = true;
		return true;
	}	
	if(GetAsyncKeyState('6') && (!sctr_X[1][2]) && (!sctr_O[1][2]))
	{	
		mscreen.krest(9, 15);
		sctr_X[1][2] = true;
		return true;
	}	
	if(GetAsyncKeyState('7') && (!sctr_X[2][0]) && (!sctr_O[2][0]))
	{	
		mscreen.krest(15, 3);
		sctr_X[2][0] = true;
		return true;
	}
	if(GetAsyncKeyState('8') && (!sctr_X[2][1]) && (!sctr_O[2][1]))
	{	
		mscreen.krest(15, 9);
		sctr_X[2][1] = true;
		return true;
	}	
	if(GetAsyncKeyState('9') && (!sctr_X[2][2]) && (!sctr_O[2][2]))
	{	
		mscreen.krest(15, 15);
		sctr_X[2][2] = true;
		return true;
	}
	return false;
}

bool game::player_O()
{
	if(GetAsyncKeyState('1') && (!sctr_O[0][0]) && (!sctr_X[0][0]))
	{
		mscreen.nol(3, 3);
		sctr_O[0][0] = true;
		mscreen.buf_screen[3 * 20 + 4] = ' ';
		return true;
	}
	if(GetAsyncKeyState('2') && (!sctr_O[0][1]) && (!sctr_X[0][1]))
	{	
		mscreen.nol(3, 9);
		sctr_O[0][1] = true;
		mscreen.buf_screen[3 * 20 + 10] = ' ';
		return true;
	}	
	if(GetAsyncKeyState('3') && (!sctr_O[0][2]) && (!sctr_X[0][2]))
	{	
		mscreen.nol(3, 15);
		sctr_O[0][2] = true;
		mscreen.buf_screen[3 * 20 + 16] = ' ';
		return true;
	}	
	if(GetAsyncKeyState('4') && (!sctr_O[1][0]) && (!sctr_X[1][0]))
	{	
		mscreen.nol(9, 3);
		sctr_O[1][0] = true;
		mscreen.buf_screen[9 * 20 + 4] = ' ';
		return true;
	}	
	if(GetAsyncKeyState('5') && (!sctr_O[1][1]) && (!sctr_X[1][1]))
	{	
		mscreen.nol(9, 9);
		sctr_O[1][1] = true;
		mscreen.buf_screen[9 * 20 + 10] = ' ';
		return true;
	}	
	if(GetAsyncKeyState('6') && (!sctr_O[1][2]) && (!sctr_X[1][2]))
	{	
		mscreen.nol(9, 15);
		sctr_O[1][2] = true;
		mscreen.buf_screen[9 * 20 + 16] = ' ';
		return true;
	}	
	if(GetAsyncKeyState('7') && (!sctr_O[2][0]) && (!sctr_X[2][0]))
	{	
		mscreen.nol(15, 3);
		sctr_O[2][0] = true;
		mscreen.buf_screen[15 * 20 + 4] = ' ';
		return true;
	}
	if(GetAsyncKeyState('8') && (!sctr_O[2][1]) && (!sctr_X[2][1]))
	{	
		mscreen.nol(15, 9);
		sctr_O[2][1] = true;
		mscreen.buf_screen[15 * 20 + 10] = ' ';
		return true;
	}	
	if(GetAsyncKeyState('9') && (!sctr_O[2][2]) && (!sctr_X[2][2]))
	{	
		mscreen.nol(15, 15);
		sctr_O[2][2] = true;
		mscreen.buf_screen[15 * 20 + 16] = ' ';
		return true;
	}
	return false;
}

int main()
{
	bool step = true;
	game my;
	my.game_start();
	while(my.game_over())
	{
		my.format_level();
		if(step)
		{
			if(my.player_X())
				step = false;
			Sleep(100);
		}
		if(!step)
		{
			if(my.player_O())
				step = true;
			Sleep(100);
		}
		my.format_level();
	}
	getchar();
	return 0;
}