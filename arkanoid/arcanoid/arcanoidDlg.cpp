
// arcanoidDlg.cpp : implementation file
//

#include "stdafx.h"
#include "arcanoid.h"
#include "Game.h"
#include "arcanoidDlg.h"
#include "afxdialogex.h"'
#include <cstdlib>
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
{
	countEnemy = 10;
	first = new Enemy;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CarcanoidDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

}

BEGIN_MESSAGE_MAP(CarcanoidDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_BN_CLICKED(IDC_BUTTON1, &CarcanoidDlg::ButtonStartGame)
	ON_BN_CLICKED(IDC_BUTTON2, &CarcanoidDlg::ButtonLoadMap)
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
		
		
	
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CarcanoidDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}






void CarcanoidDlg::ButtonStartGame()
{
	
	Game start;
	
	start.DoModal();
}


void CarcanoidDlg::ButtonLoadMap()
{
	Game En;
	
	En.countEnemy = 20;
	countEnemy = 20;
	ButtonStartGame();
}
