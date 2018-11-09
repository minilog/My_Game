#pragma once

#include <d3d9.h>

class Game
{
public:
	Game(int in_FPS = 60);
protected:
	void TaoVongLapGame();
	void CapNhat(float in_tg);
	void Ve();

protected:
	int						mFPS;
	int                     mChieuRong;
	int						mChieuCao;
	PDIRECT3DSURFACE9       mMatSau;
	PDIRECT3DSURFACE9		mDemSau;
};

