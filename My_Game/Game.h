#pragma once

#include <d3d9.h>
#include <string>
#include <d3dx9.h>

class Game
{
public:
	Game(int in_FPS = 60);
	~Game();
protected:
	void TaoVongLapGame();
	void CapNhat(float in_tg);
	void Ve();

private:
	int						mFPS;
	int                     mChieuRong;
	int						mChieuCao;
	PDIRECT3DSURFACE9       mMatSau;
	PDIRECT3DSURFACE9		mDemSau;

	ID3DXFont *font;
	RECT fRectangle;
	std::string message;
};

