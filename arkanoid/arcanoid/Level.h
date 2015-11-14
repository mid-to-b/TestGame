#pragma once


// Level dialog

class Level : public CDialogEx
{
	DECLARE_DYNAMIC(Level)

public:
	Level(CWnd* pParent = NULL);   // standard constructor
	virtual ~Level();

// Dialog Data
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	struct Enemy
	{
		CPoint coord;
		Enemy* next;
		Enemy* previous;
	};
	afx_msg void OnBnClickedButton1();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	const int dlinaEnemy = 70;  // длина врагов
	const int shirinaEnemy = 15;// ширина врагов
	afx_msg void OnPaint();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	Enemy* first;
	Enemy* tmp;
	int countEnemy;
	bool Check(CPoint point,int a);
	void Level::Print();
};
