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
	~BanDoGame();
	void ThietLapCamera(Camera *in_Camera);
	void CapNhat(int in_tg);
	void Ve();
	Tmx::Map *bdBanDo();
	RECT rHCNGioiHanBanDo();
	int iChieuRong();
	int iChieuCao();
	int iChieuRongTile();
	int iChieuCaoTile();
	std::map<int, HinhAnh*> sDanhSachTileSet();
	bool bCaMeraChamBienTrai();
	bool bCameraChamBienPhai();
	bool bCameraChamBienTren();
	bool bCameraChamBienDuoi();

	std::vector<VienGach*> vgDanhSachVienGach();

private:
	std::vector<VienGach*> vsDanhSachVienGach;
};

