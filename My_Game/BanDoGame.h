//bắt đầu từ Game -> Màn Game -> Bản Đồ Game
//bắt đầu từ Game -> Màn Game -> Người Chơi
#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include "HinhAnh.h"
#include "MapReader/Tmx.h.in"
#include "ToanCauGame.h"
#include "VaChamGame.h"

class BanDoGame
{
public:
	BanDoGame(char *in_DuongDan);
private:
	void TaiBanDo(char* in_DuongDan);
public:
	void CapNhat(float in_tg);
	void Ve();
	~BanDoGame();

public:
	Tmx::Map *bdBanDo();
	int iChieuRong();
	int iChieuCao();
	int iChieuRongTile();
	int iChieuCaoTile();
	RECT rHCNGioiHanBanDo();
	bool bCaMeraChamBienTrai();
	bool bCameraChamBienPhai();
	bool bCameraChamBienTren();
	bool bCameraChamBienDuoi();
	std::map<int, HinhAnh*> sDanhSachTileSet();

private:
	Tmx::Map *mBanDo;
	int mChieuRong;
	int mChieuCao;
	int mChieuRongTile;
	int mChieuCaoTile;
	std::map<int, HinhAnh*> mDanhSachTileSet;
};

