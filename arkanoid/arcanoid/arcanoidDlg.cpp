
// arcanoidDlg.cpp : implementation file
//

#include "stdafx.h"
#include "arcanoid.h"
#include "Game.h"
#include "Level.h"
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
	countEnemy = 0;
	first = new Enemy;
	tmp = new Enemy;
	tmp = first;
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
	ON_BN_CLICKED(IDC_BUTTON3, &CarcanoidDlg::ButtonCreatLvl)
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
	Enemy * tmp_1 = new Enemy;
	tmp_1 = first;
	CFileDialog fileDialog(TRUE, NULL, L".txt", NULL, L"Text file (*.txt)|*.txt|");
	int result = fileDialog.DoModal();
	if (result == IDOK)
	{
		CStdioFile File(fileDialog.GetPathName(), CFile::modeRead);
		bool count = 0;
		bool swap = 0;
		CString buffer;
		char buff[5] = "";
		char * buf = new char[File.GetLength()];
		File.Read(buf, File.GetLength());
		for (int i = 0; i < File.GetLength(); i++)
		{
			if (buf[i] == 'þ'){
				continue;
			}
			if (int(buf[i]) == 0)
			{	
				if (!count)
				{
					countEnemy = _wtoi(buffer);
					for (int i = 1; i < countEnemy; i++)
					{
						Enemy * write = new Enemy;
						tmp_1->next = write;
						tmp_1 = write;
					}
					tmp_1 = first;
					buffer = "";
					count = 1;
					continue;
				}
				else
				{
					if (!swap)
					{
						tmp_1->coord.x = _wtoi(buffer);
						buffer = "";
						swap = 1;
						continue;
					}
					else {
						tmp_1->coord.y = _wtoi(buffer);
						tmp_1 = tmp_1->next;
						buffer = "";
						swap = 0;
						continue;
					}
				}
			}
			buffer += buf[i];
		}
		count = 0;
		swap = 0;
	}
	tmp_1 = first;
	ButtonStartGame();
}


void CarcanoidDlg::ButtonCreatLvl()
{
	Level create;
	create.DoModal();
}
