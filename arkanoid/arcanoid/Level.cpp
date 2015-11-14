// Level.cpp : implementation file
//

#include "stdafx.h"
#include "arcanoid.h"
#include "Level.h"
#include "afxdialogex.h"


// Level dialog

IMPLEMENT_DYNAMIC(Level, CDialogEx)

Level::Level(CWnd* pParent /*=NULL*/)
	: CDialogEx(Level::IDD, pParent)
{
	first = new Enemy;
	tmp = new Enemy;
	first = tmp;
	countEnemy = 0;
}

Level::~Level()
{
}

void Level::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Level, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Level::OnBnClickedButton1)
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// Level message handlers
void Level::OnPaint()
{
	CPaintDC dc(this);
	CRect rect;
	GetClientRect(&rect);
	int x = rect.Width();
	int y = rect.Height();
	CBrush br;
	CPen blackpn;
	CPen pn;
	blackpn.CreatePen(0, 1, RGB(0, 0, 0));
	pn.CreatePen(0, 5, RGB(255, 255, 255));
	br.CreateSolidBrush(RGB(255, 255, 255));
	dc.SelectObject(br);
	dc.SelectObject(pn);
	dc.Rectangle(0, 0, x, y-100);
	dc.SelectObject(blackpn);
	dc.MoveTo(0, y - 98);
	dc.LineTo(x, y - 98);
}

void Level::OnBnClickedButton1()
{
	if (!countEnemy)MessageBox(L"Нет блоков");
	else{
		Enemy * write = new Enemy;
		write = first;
		CFileDialog fileDialog(FALSE, NULL, L".txt", NULL, L"Text file (*.txt)|*.txt|");
		int result = fileDialog.DoModal();
		if (result == IDOK)
		{
			CFile File;
			char buf[4]="o";
			File.Open(fileDialog.GetPathName(), CFile::modeCreate | CFile::modeWrite, NULL);
			for (int i = 0; i < (countEnemy+1); i++)
			{
				if (!i)
				{
					_itoa_s(countEnemy, buf, 4, 10);
					File.Write(buf, 4);
				}
				else{
					_itoa_s(write->coord.x, buf, 4, 10);
					File.Write(buf, 4);
					_itoa_s(write->coord.y, buf, 4, 10);
					File.Write(buf, 4);
					write = write->next;
				}
			}

		}
	}
}

void Level::OnMouseMove(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	CRect rect;
	GetClientRect(&rect);
	int y = rect.Height();
	if (point.y < (y - 100))
	{
		static CPoint coord;
		CPen blackpn;
		CPen pn;
		blackpn.CreatePen(0, 1, RGB(0, 0, 0));
		pn.CreatePen(0, 1, RGB(255, 255, 255));
		dc.SelectObject(pn);
		dc.Rectangle(coord.x / dlinaEnemy*dlinaEnemy, coord.y / shirinaEnemy*shirinaEnemy, coord.x / dlinaEnemy*dlinaEnemy + dlinaEnemy, coord.y / shirinaEnemy*shirinaEnemy + shirinaEnemy);
		dc.SelectObject(blackpn);
		dc.Rectangle(point.x / dlinaEnemy*dlinaEnemy, point.y / shirinaEnemy*shirinaEnemy, point.x / dlinaEnemy*dlinaEnemy + dlinaEnemy, point.y / shirinaEnemy*shirinaEnemy + shirinaEnemy);
		coord.x = point.x;
		coord.y = point.y;
		Print();
	}
	else return;
}

void Level::OnLButtonUp(UINT nFlags, CPoint point)
{
	CClientDC dc(this);
	CBrush br;
	CBrush redbr;
	CPen blackpn;
	CPen pn;
	redbr.CreateSolidBrush(RGB(255, 0, 0));
	blackpn.CreatePen(0, 1, RGB(0, 0, 0));
	pn.CreatePen(0, 1, RGB(255, 255, 255));
	br.CreateSolidBrush(RGB(255, 255, 255));
	if (Check(point, 1)){
		dc.SelectObject(pn);
		dc.SelectObject(br);
		dc.Rectangle(point.x / dlinaEnemy*dlinaEnemy, point.y / shirinaEnemy*shirinaEnemy, point.x / dlinaEnemy*dlinaEnemy + dlinaEnemy, point.y / shirinaEnemy*shirinaEnemy + shirinaEnemy);
	}
	else{
		Enemy * elem = new Enemy;
		elem->coord.x = point.x / dlinaEnemy*dlinaEnemy;
		elem->coord.y = point.y / shirinaEnemy*shirinaEnemy;
		dc.SelectObject(redbr);
		dc.SelectObject(blackpn);
		dc.Rectangle(elem->coord.x, elem->coord.y, elem->coord.x + dlinaEnemy, elem->coord.y + shirinaEnemy);
		if (!countEnemy)
		{
			tmp->coord.x = elem->coord.x;
			tmp->coord.y = elem->coord.y;
		}
		else{
			tmp->next = elem;
			elem->previous = tmp;
			tmp = elem;
		}
		countEnemy++;
	}


}

bool Level::Check(CPoint point,int a)
{
	Enemy * write = new Enemy;
	write = first;
	for (int i = 0; i < countEnemy; i++)
	{
		if (
			((point.x / dlinaEnemy*dlinaEnemy) == write->coord.x) &&
			((point.y / shirinaEnemy*shirinaEnemy) == write->coord.y)
			){
			if (a)
			{
				if (countEnemy == 1)countEnemy = 0;
				else{
					if (i == (countEnemy - 1)){

						write = write->previous;
						tmp = write;
						countEnemy--;
						return 1;
					}
					if (!i){
						write = write->next;
						first = write;
						countEnemy--;
						return 1;
					}

					write = write->previous;
					write->next = write->next->next;
					write = write->next;
					write->previous = write->previous->previous;
					countEnemy--;

				}

			}
			return 1;
		}
		write = write->next;
	}
	return 0;
}

void Level::Print()
{
	Enemy * print = new Enemy;
	print = first;
	CClientDC dc(this);
	CBrush redbr;
	redbr.CreateSolidBrush(RGB(255, 0, 0));
	dc.SelectObject(redbr);
	for (int i = 0; i < countEnemy; i++)
	{
		dc.Rectangle(print->coord.x, print->coord.y, print->coord.x + dlinaEnemy, print->coord.y + shirinaEnemy);
		print = print->next;
	}


}
