//bắt đầu từ Game -> Màn Game -> Bản Đồ Game
//bắt đầu từ Game -> Màn Game -> Người Chơi
#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include "HinhAnh.h"
#include "MapReader/Tmx.h.in"
#include "Camera.h"
#include "ToanCauGame.h"
#include "VaChamGame.h"
#include "CayBonNhanh.h"
#include "VienGach.h"

class BanDoGame
{
public:
	BanDoGame(char *in_DuongDan);
	void ThietLapCamera(Camera *in_Camera);
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
	std::vector<VienGach*> vgDanhSachVienGach();
	CayBonNhanh* cbnCayBonNhanh();

private:
	Tmx::Map *mBanDo;
	int mChieuRong;
	int mChieuCao;
	int mChieuRongTile;
	int mChieuCaoTile;
	Camera *mCamera;
	std::map<int, HinhAnh*> mDanhSachTileSet;
	std::vector<VienGach*> mDanhSachVienGach;
	CayBonNhanh *mCayBonNhanh;
};

