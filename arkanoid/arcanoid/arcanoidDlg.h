
// arcanoidDlg.h : header file
//

#pragma once


// CarcanoidDlg dialog
class CarcanoidDlg : public CDialogEx
{
// Construction
public:
	CarcanoidDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_ARCANOID_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	struct Enemy
	{
		CPoint coord;
		Enemy* next;
	};
	afx_msg void ButtonStartGame();
	afx_msg void ButtonLoadMap();
	const int dlinaEnemy = 70;  // длина врагов
	const int shirinaEnemy = 15;// ширина врагов
	int countEnemy;
	Enemy* first;
	Enemy * tmp;
	
	afx_msg void ButtonCreatLvl();
};
