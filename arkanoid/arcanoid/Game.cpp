// Game.cpp : implementation file
//

#include "stdafx.h"
#include "arcanoid.h"
#include "Game.h"
#include "arcanoidDlg.h"
#include "afxdialogex.h"


// Game dialog

IMPLEMENT_DYNAMIC(Game, CDialogEx)

Game::Game(CWnd* pParent /*=NULL*/)
	: CDialogEx(Game::IDD, pParent)
{
	crd.x = 0;
	crd.y = 0;
	timer = 0;
	start = 0;
	tchka.x = 0;
	tchka.y = 0;
	countEnemy = 0;
	alf = -90;
	score = "1";
	firsts = 0;
	speed = 2;
	first = new Enemy;
}

Game::~Game()
{
}

void Game::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Game, CDialogEx)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
//	ON_WM_SYSCOMMAND()
ON_WM_MOVE()
END_MESSAGE_MAP()


// Game message handlers


void Game::OnPaint()
{
	CPaintDC dc(this); 
	CRect rect;
	CarcanoidDlg Wind;
	GetClientRect(&rect);
	int x = rect.Width();
	int y = rect.Height();
	CString *hi = &Wind.hi;
	//MessageBox(*hi);
	countEnemy = Wind.countEnemy;
	for (int i = 0; i < countEnemy / 2; i++)
	{
		for (int y = 50; y <= countEnemy / 5 * 50; y += 50)
		{
			Enemy * second = new Enemy;
			second->coord.x = i*dlinaEnemy + i * 5 + 50;
			second->coord.y = y;
			second->next = first;
			first = second;
		}
	}

	CBrush br;
	CPen pn;
	pn.CreatePen(0, 5, RGB(255, 255, 255));
	br.CreateSolidBrush(RGB(255, 255, 255));
	dc.SelectObject(br);
	dc.SelectObject(pn);
	dc.Rectangle(0, 0, x, y);
	printEnemy();
	Score();
}


void Game::OnMouseMove(UINT nFlags, CPoint point)
{
	Player(point);
}

void Game::Player(CPoint point)
{
	CClientDC DC(this);
	CRect rect;
	static double a = 0; // запоминалка 
	CPen pn;
	pn.CreatePen(0, 10, RGB(255, 255, 255));
	GetClientRect(&rect);
	DC.SelectObject(pn);
	int y = rect.Height();
	int x = rect.Width();
	DC.Rectangle(a - (68 / 2), y - 43, a + (68 / 2), y - 50);
	CDC* pDC = &DC;
	CBitmap bmp;
	bmp.LoadBitmap(IDB_BITMAP1);
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	dc.SelectObject(&bmp);
	pDC->BitBlt(point.x - (68 / 2), y - 50, 68, 7, &dc, 0, 0, SRCCOPY);
	a = point.x;
	crd.x = point.x - (68 / 2);
	crd.y = y - 50;
	if (!start)
	{

		DC.Rectangle(0, y - 65 + 6, x, y - 65);
		CDC* pDC = &DC;
		CBitmap bmp;
		bmp.LoadBitmap(IDB_BITMAP2);
		CDC dc;
		dc.CreateCompatibleDC(pDC);
		dc.SelectObject(&bmp);
		pDC->BitBlt(point.x - 6, y - 65, 12, 12, &dc, 0, 0, SRCCOPY);
	}
}


void Game::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (!start){
		tchka.x = crd.x + (68 / 2) - 6;
		tchka.y = crd.y - 15;
		start = 1;
		ball();
	}
}

void Game::ball()
{
	CClientDC DC(this);
	CRect rect;
	CPen pn;
	pn.CreatePen(0, 1, RGB(255, 255, 255));
	DC.SelectObject(pn);
	GetClientRect(&rect);
	int x = rect.Width() / 2;
	int y = rect.Height() / 2;
	SetTimer(1, 1, 0);
	DC.Rectangle(tchka.x + (timer - speed)*cos(3.14*alf / 180.0), tchka.y + (timer - speed)*sin(3.14*alf / 180.0), tchka.x + 12 + (timer - speed)*cos(3.14*alf / 180.0), tchka.y + 12 + (timer - speed)*sin(3.14*alf / 180.0));


	switch (logicBall(tchka, timer, alf))
	{
	case 1:{
		tchka.x = tchka.x + timer*cos(3.14*alf / 180.0);
		tchka.y = tchka.y + timer*sin(3.14*alf / 180.0);
		if (((crd.x + 34) - (tchka.x)) >= 0){
			alf = -1 * ygl(double(abs((crd.x + 34) - (tchka.x))), double(7.0)) - 90;
		}
		else alf = ygl(double(abs((crd.x + 34) - (tchka.x))), double(7.0)) - 90;
		timer = 0;

	}break;

	case 2:{
		tchka.x = tchka.x + timer*cos(3.14*alf / 180.0);
		tchka.y = tchka.y + timer*sin(3.14*alf / 180.0);
		alf *= -1;
		alf -= 180;
		timer = 0;

	}break;

	case 3:{
		tchka.x = (tchka.x + timer*cos(3.14*alf / 180.0)) + 1;
		tchka.y = tchka.y + timer*sin(3.14*alf / 180.0);
		alf *= -1;
		alf += 180;
		timer = 0;

	}break;

	case 4:{
		tchka.x = tchka.x + timer*cos(3.14*alf / 180.0);
		tchka.y = tchka.y + timer*sin(3.14*alf / 180.0);
		alf *= -1;
		timer = 0;

	}break;

	case 5:{
		tchka.x = tchka.x + timer*cos(3.14*alf / 180.0);
		tchka.y = (tchka.y + timer*sin(3.14*alf / 180.0)) + 1;
		alf *= -1;
		timer = 0;
	}break;

	default: break;
	}
	CDC* pDC = &DC;
	CBitmap bmp;
	bmp.LoadBitmap(IDB_BITMAP2);
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	dc.SelectObject(&bmp);
	pDC->BitBlt(tchka.x + timer*cos(3.14*alf / 180.0), tchka.y + timer*sin(3.14*alf / 180.0), 12, 12, &dc, 0, 0, SRCCOPY);
	timer += speed;
}

double Game::ygl(double a, double b)
{
	double ygl = double(atan(a / b)*180.0 / 3.14);
	return ygl;
}


void Game::OnTimer(UINT_PTR nIDEvent)
{
	ball();
}


void Game::printEnemy()
{
	Enemy* print = new Enemy;
	print = first;
	CClientDC dc(this);
	CBrush brush;
	brush.CreateSolidBrush(RGB(255, 0, 0));
	dc.SelectObject(brush);
	for (int i = 0; i < countEnemy; i++)
	{
		dc.Rectangle(print->coord.x, print->coord.y, print->coord.x + dlinaEnemy, print->coord.y + shirinaEnemy);
		print = print->next;
	}
	delete print;
}

int Game::logicBall(CPoint tchka, int timer, double alf)
{
	CClientDC DC(this);
	CRect rect;
	GetClientRect(&rect);
	Enemy* write = new Enemy;
	write = first;
	int x = rect.Width() / 2;
	int y = rect.Height() / 2;

	if (((tchka.x + timer*cos(3.14*alf / 180.0)) < (crd.x + 68)) &&
		((tchka.x + 12 + timer*cos(3.14*alf / 180.0)) > crd.x) &&
		((tchka.y + 12 + timer*sin(3.14*alf / 180.0)) > crd.y) &&
		((tchka.y + timer*sin(3.14*alf / 180.0)) < (crd.y + 7)))
	{
		return 1;
	}

	//////////////////////////////////Шарик об правую стенку

	if ((tchka.x + 12 + timer*cos(3.14*alf / 180.0)) >= (x * 2)){
		return 2;
	}

	///////////////////////////////////Шарик об левую стенку

	if ((tchka.x + timer*cos(3.14*alf / 180.0)) <= 0){
		return 3;
	}

	/////////////////////////////////////Шарик об потолок

	if ((tchka.y + timer*sin(3.14*alf / 180.0)) <= 0){
		return 4;
	}

	///////////////////////////////////Шарик об противника

	for (int i = 0; i < countEnemy; i++)
	{
		if (
			((tchka.x + timer*cos(3.14*alf / 180.0)) <= (write->coord.x + dlinaEnemy)) &&
			((tchka.x + 12 + timer*cos(3.14*alf / 180.0)) >= write->coord.x) &&
			((tchka.y + 12 + timer*sin(3.14*alf / 180.0)) >= write->coord.y) &&
			((tchka.y + timer*sin(3.14*alf / 180.0)) <= (write->coord.y + shirinaEnemy))
			){

			if (
				((tchka.y + 6 + timer*sin(3.14*alf / 180.0)) <= (write->coord.y + shirinaEnemy + (6 * sqrt(2.0)) / 2)) &&
				((tchka.y + 6 + timer*sin(3.14*alf / 180.0)) >= (write->coord.y - (6 * sqrt(2.0)) / 2)) &&
				((tchka.x + 6 + timer*cos(3.14*alf / 180.0)) >= (write->coord.x + dlinaEnemy))
				)
			{
				Kill(i);
				return 3;
			}
			if (
				((tchka.y + 6 + timer*sin(3.14*alf / 180.0)) <= (write->coord.y + shirinaEnemy + (6 * sqrt(2.0)) / 2)) &&
				((tchka.y + 6 + timer*sin(3.14*alf / 180.0)) >= (write->coord.y - (6 * sqrt(2.0)) / 2)) &&
				((tchka.x + 6 + timer*cos(3.14*alf / 180.0)) <= (write->coord.x))
				)
			{
				Kill(i);
				return 2;
			}
			if (
				((tchka.x + 6 + timer*cos(3.14*alf / 180.0)) <= (write->coord.x + dlinaEnemy + (6 * sqrt(2.0)) / 2)) &&
				((tchka.x + 6 + timer*cos(3.14*alf / 180.0)) >= (write->coord.x - (6 * sqrt(2.0)) / 2)) &&
				((tchka.y + 6 + timer*sin(3.14*alf / 180.0)) <= (write->coord.y))
				)
			{
				Kill(i);
				return 4;
			}
			if (
				((tchka.x + 6 + timer*cos(3.14*alf / 180.0)) <= (write->coord.x + dlinaEnemy + (6 * sqrt(2.0)) / 2)) &&
				((tchka.x + 6 + timer*cos(3.14*alf / 180.0)) >= (write->coord.x - (6 * sqrt(2.0)) / 2)) &&
				((tchka.y + 6 + timer*sin(3.14*alf / 180.0)) >= (write->coord.y + shirinaEnemy))
				)
			{
				Kill(i);
				return 5;
			}


		}
		write = write->next;
	}

	/////////////////////// Шарик об нижнюю стенку

	if ((tchka.y + 12 + timer*sin(3.14*alf / 180.0)) >= (y * 2)) Lose();

	return 0;
}

void Game::Kill(int num)
{
	CClientDC DC(this);
	CBrush br;
	CPen pn;
	pn.CreatePen(0, 5, RGB(255, 255, 255));
	br.CreateSolidBrush(RGB(255, 255, 255));
	DC.SelectObject(br);
	DC.SelectObject(pn);
	Enemy* kill = new Enemy;
	kill = first;
	if (!num)
	{
		DC.Rectangle(kill->coord.x, kill->coord.y, kill->coord.x + dlinaEnemy, kill->coord.y + shirinaEnemy);
		first = first->next;

	}
	else{
		for (int i = 0; i < num - 1; i++) kill = kill->next;
		DC.Rectangle(kill->next->coord.x, kill->next->coord.y, kill->next->coord.x + dlinaEnemy, kill->next->coord.y + shirinaEnemy);
		kill->next = kill->next->next;
	}
	countEnemy--;
	if (!countEnemy)Win();
}

void Game::Win()
{
	KillTimer(1);
	CClientDC DC(this);
	CBrush br;
	CPen pn;
	pn.CreatePen(0, 5, RGB(255, 255, 255));
	br.CreateSolidBrush(RGB(255, 255, 255));
	DC.SelectObject(br);
	DC.SelectObject(pn);
	tchka.x = 480 / 2 - (12 / 2);
	tchka.y = 325 / 2;
	alf = -90;
	crd.x = 0;
	timer = 0;
	crd.y = 0;
	start = 0;
	speed++;
	countEnemy = 10;
	first = new Enemy;
	for (int i = 0; i < countEnemy / 2; i++)
	{
		for (int y = 50; y <= countEnemy / 5 * 50; y += 50)
		{
			Enemy * second = new Enemy;
			second->coord.x = i*dlinaEnemy + i * 5 + 50;
			second->coord.y = y;
			second->next = first;
			first = second;
		}
	}
	CWnd::Invalidate(1);
}

void Game::Lose()
{
	KillTimer(1);
	MessageBox(L"You Lose");
	firsts = 0;
	score = "1";
	CClientDC DC(this);
	CBrush br;
	CPen pn;
	pn.CreatePen(0, 5, RGB(255, 255, 255));
	br.CreateSolidBrush(RGB(255, 255, 255));
	DC.SelectObject(br);
	DC.SelectObject(pn);
	tchka.x = 480 / 2 - (12 / 2);
	tchka.y = 325 / 2;
	alf = -90;
	crd.x = 0;
	timer = 0;
	crd.y = 0;
	speed = 2;
	start = 0;
	countEnemy = 10;
	first = new Enemy;
	for (int i = 0; i < countEnemy / 2; i++)
	{
		for (int y = 50; y <= countEnemy / 5 * 50; y += 50)
		{
			Enemy * second = new Enemy;
			second->coord.x = i*dlinaEnemy + i * 5 + 50;
			second->coord.y = y;
			second->next = first;
			first = second;
		}
	}
	CWnd::Invalidate(1);
}

void Game::Score()
{
	CClientDC DC(this);
	char buf[6];
	for (int i = 0; i < strlen(buf); i++)buf[i] = score[i];
	if (!firsts)firsts = 1;
	else _itoa_s(atoi(buf) + 1, buf, 10);
	score = buf;
	DC.TextOutW(10, 300, L"LvL : ");
	DC.TextOutW(50, 300, score);
}


void Game::OnMove(int x, int y)
{
	static int buf = 0;
	//if(buf > 2)MessageBox(L"сдвиг плохо работает");
	buf++;
}
