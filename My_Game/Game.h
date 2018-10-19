//bắt đầu từ Game -> Màn Game -> Bản Đồ Game
//bắt đầu từ Game -> Màn Game -> Người Chơi

#pragma once

#include "d3dx9.h"
#include "d3d9.h"
#include <Windows.h>
#include <dinput.h>
#include "HoatHinh.h"

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

	HoatHinh *mHoatHinh;
};

