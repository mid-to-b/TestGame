
// arcanoidDlg.cpp : implementation file
//

#include "stdafx.h"
#include "arcanoid.h"
#include "arcanoidDlg.h"
#include "afxdialogex.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CarcanoidDlg dialog



CarcanoidDlg::CarcanoidDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CarcanoidDlg::IDD, pParent)
	, HELP(0)
{
	crd.x = 0;
	crd.y = 0;
	first = new Enemy;
	for (int i = 0; i < countEnemy/2; i++)
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
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CarcanoidDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, HELP);
}

BEGIN_MESSAGE_MAP(CarcanoidDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CarcanoidDlg message handlers

BOOL CarcanoidDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CarcanoidDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CarcanoidDlg::OnPaint()
{

		CPaintDC dc(this);
		CRect rect;
		GetClientRect(&rect);
		int x = rect.Width();
		int y = rect.Height();
		printEnemy();
		
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CarcanoidDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CarcanoidDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	Player(point);
}

void CarcanoidDlg::Player(CPoint point)
{
	CClientDC DC(this);
	CRect rect;
	static double a=0; // запоминалка 
	CPen pn;
	pn.CreatePen(0, 10, RGB(255, 255, 255));
	GetClientRect(&rect);
	DC.SelectObject(pn);
	int y = rect.Height();
	DC.Rectangle(a - (68 / 2), y - 43, a + (68 / 2), y - 50);
	CDC* pDC = &DC;
	CBitmap bmp;
	bmp.LoadBitmap(IDB_BITMAP1);
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	dc.SelectObject(&bmp);
	pDC->BitBlt(point.x-(68/2), y-50, 68, 7, &dc, 0, 0, SRCCOPY);
	a = point.x;
	crd.x = point.x - (68 / 2);
	crd.y = y - 50;
}

void CarcanoidDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	static bool start = 0;
	if (!start){
		start = 1;
		ball();
	}
	
	
}

void CarcanoidDlg::ball()
{
	UpdateData(0);
	CClientDC DC(this);
	CRect rect;
	CPen pn;
	pn.CreatePen(0, 1, RGB(255, 255, 255));
	DC.SelectObject(pn);
	GetClientRect(&rect);
	int x = rect.Width()/2;
	int y = rect.Height()/2;
	SetTimer(1, 1, 0);
	static double alf = 90;
	static int timer = 0;
	static CPoint tchka(x - (12 / 2),y);
	static int cygl = 0; // kof ygla

	DC.Rectangle(tchka.x + (timer - 3)*cos(3.14*alf / 180.0), tchka.y  + (timer - 3)*sin(3.14*alf / 180.0), tchka.x + 12 + (timer - 3)*cos(3.14*alf / 180.0), tchka.y +12+ (timer - 3)*sin(3.14*alf / 180.0));
	
	
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
		tchka.x = tchka.x + timer*cos(3.14*alf / 180.0);
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
		tchka.y = tchka.y + timer*sin(3.14*alf / 180.0);
		alf = 90;
		//alf -= 180;
		timer = 0;
	}break;

	default: break;
	}
	HELP = alf;
	CDC* pDC = &DC;
	CBitmap bmp;
	bmp.LoadBitmap(IDB_BITMAP2);
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	dc.SelectObject(&bmp);
	pDC->BitBlt(tchka.x + timer*cos(3.14*alf / 180.0), tchka.y + timer*sin(3.14*alf / 180.0), 12, 12, &dc, 0, 0, SRCCOPY);
	timer++;
	

}

double CarcanoidDlg::ygl(double a, double b)
{
	UpdateData(0);
	double ygl = double(atan(a / b)*180.0/3.14);
	return ygl;
}

void CarcanoidDlg::OnTimer(UINT_PTR nIDEvent)
{
	ball();
}

void CarcanoidDlg::printEnemy()
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

int CarcanoidDlg::logicBall(CPoint tchka,int timer,double alf)
{
	CClientDC DC(this);
	CRect rect;
	GetClientRect(&rect);
	Enemy* write = new Enemy;
	write = first;
	int x = rect.Width() / 2;
	int y = rect.Height() / 2;
	
	if (((tchka.x + timer*cos(3.14*alf / 180.0)) <= (crd.x + 68)) &&
		((tchka.x + 12 + timer*cos(3.14*alf / 180.0)) >= crd.x) &&
		((tchka.y + 12 + timer*sin(3.14*alf / 180.0)) >= crd.y) &&
		((tchka.y + timer*sin(3.14*alf / 180.0)) <= (crd.y + 7)))
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

			if(
				((tchka.y + 6 + timer*sin(3.14*alf / 180.0)) <= (write->coord.y + shirinaEnemy)) &&
				((tchka.y + 6 + timer*sin(3.14*alf / 180.0)) >= write->coord.y) &&
				((tchka.x + 6 + timer*cos(3.14*alf / 180.0)) > (write->coord.x + dlinaEnemy/2))
				)return 3;
			if (
				((tchka.y + 6 + timer*sin(3.14*alf / 180.0)) <= (write->coord.y + shirinaEnemy)) &&
				((tchka.y + 6 + timer*sin(3.14*alf / 180.0)) >= write->coord.y) &&
				((tchka.x + 6 + timer*cos(3.14*alf / 180.0)) < (write->coord.x + dlinaEnemy/2))
				)return 2;
			if (
				((tchka.x + 6 + timer*cos(3.14*alf / 180.0)) <= (write->coord.x + dlinaEnemy)) &&
				((tchka.x + 6 + timer*cos(3.14*alf / 180.0)) >= write->coord.x) &&
				((tchka.y + 6 + timer*sin(3.14*alf / 180.0)) < (write->coord.y + shirinaEnemy)/2)
				)return 4;
			if (
				((tchka.x + 6 + timer*cos(3.14*alf / 180.0)) <= (write->coord.x + dlinaEnemy)) &&
				((tchka.x + 6 + timer*cos(3.14*alf / 180.0)) >= write->coord.x) &&
				((tchka.y + 6 + timer*sin(3.14*alf / 180.0)) > (write->coord.y + shirinaEnemy/2))
				)return 4;

				
		}
		write = write->next;
	}
	
	return 0;
}
