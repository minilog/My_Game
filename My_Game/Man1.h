﻿#pragma once

#include "ManGame.h"
#include "HinhAnh.h"
#include "XMan.h"
#include "GameDebugDraw.h"
#include "DoiTuongTinh.h"
#include <vector>
 
class Man1 : public ManGame
{
public:
	Man1();
	~Man1();
	virtual void TaiDuLieu();
	virtual void CapNhat(float in_tg);
	virtual void Ve();
	virtual void OnKeyDown(int in_KeyCode);
	virtual void OnKeyUp(int in_KeyCode);
	virtual void OnMouseDown(float in_x, float in_y) {}

private:
	std::map<int, bool> mKeys;
	HinhAnh *mBanDoMap1;
	XMan *mXman;
	HinhAnh *mTest;
	GameDebugDraw *mGameDebug;

	std::vector<DoiTuongTinh*> mDanhSachDoiTuongTinh;

	void TaoBanDoVaCamera();
	void TaoDanhSachDoiTuong();
	void VeHinhAnhBanDoGame(const Vec2& in_DoDoi);
	void CapNhatDanhSachDoiTuong(float in_tg);
	void VeDanhSachDoiTuong(const Vec2& in_DoDoi);
};

