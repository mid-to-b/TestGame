#pragma once


// Game dialog

class Game : public CDialogEx
{
	DECLARE_DYNAMIC(Game)

public:
	Game(CWnd* pParent = NULL);   // standard constructor
	virtual ~Game();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	struct Enemy
	{
		CPoint coord;
		Enemy* next;
	};
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	double Game::ygl(double a, double b);
	CPoint crd; // координаты платформы (н.л. угл)
	bool start;
	int countEnemy;  // число вргов
	const int dlinaEnemy = 70;  // длина врагов
	const int shirinaEnemy = 15;// ширина врагов
	int Game::logicBall(CPoint tchka, int timer, double alf);
	void Game::printEnemy();
	void Game::Kill(int num);
	void Game::Win();
	void Game::Lose();
	void Game::Score();
	bool firsts;
	void Game::ball();
	void Game::Player(CPoint point);
	int speed;
	CString score;
	double alf;
	int timer;
	CPoint tchka;
	Enemy* first;
	void Game::Determination();
//	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnMove(int x, int y);
};
