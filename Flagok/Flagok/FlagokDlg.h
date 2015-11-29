
// FlagokDlg.h : header file
//

#pragma once


// CFlagokDlg dialog
class CFlagokDlg : public CDialogEx
{
// Construction
public:
	CFlagokDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_FLAGOK_DIALOG };

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

		void CFlagokDlg::Print();
		const int amplituda = 5;
		const int deg = 45;
		const int X = 50;
		const int Y = 150;
		const int shirina = 50;
		const int kof = 5; //раст€гивалка
		
		afx_msg void OnTimer(UINT_PTR nIDEvent);
};
