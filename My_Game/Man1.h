#pragma once

#include "ManGame.h"
#include "HinhAnh.h"
#include "XMan.h"
#include "GameDebugDraw.h"
#include "DoiTuongTinh.h"
#include <vector>
#include "QuadTree.h"
#include "DanLv.h"
#include "Ech.h"
#include "ThanhMau.h"
#include "HoatHinh.h"
#include "XacUop.h"



class Man1 : public ManGame
{
public:
	Man1();
	~Man1();

// FUNCTION
public:
	void TaiDuLieu();
	void CapNhat(float in_tg);
	void Ve();
	void OnKeyDown(int in_KeyCode);
	void OnKeyUp(int in_KeyCode);
	void OnMouseDown(float in_x, float in_y) {}

	void DrawQuadTree(QuadTree *in_QuadTree);
	void DrawCollidable();



// INFORMATION
private:
	QuadTree *mQuadTree;
	//XacUop *mXacUop;
	//DanNo1 *mDanNo1;
	XMan *mXMan;
	std::vector<DoiTuong*> mDS_DoiTuongTinhXetVaCham;
	//std::vector<DanLv*> mDS_DanLv;
	//std::vector<Ech*> mDS_Ech;

	//ThanhMau *mThanhMauXMan;
	//HinhAnh *mTest;
	HinhAnh *mBanDoMap1;
	std::map<int, bool> mKeys;
	GameDebugDraw *mGameDebugDraw;

// TEST INFOR
	ID3DXFont *font;
	RECT fRectangle;
	std::string message;

	//HoatHinh *mHoatHinhTest;

public:
	void DrawTextDebug()
	{
		int x = int(mXMan->get_ToaDo().x);
		int y = int(mXMan->get_ToaDo().y);
		message = "XMan.X = ";
		message.append(std::to_string(x));
		message.append("\n");
		message.append("XMan.Y = ");
		message.append(std::to_string(y));
		message.append("\nLEFT = ");
		message.append(std::to_string((int)Camera::get_ToaDo().x - (int)Camera::get_ChieuRong() / 2));
		message.append("\nTOP = ");
		message.append(std::to_string((int)Camera::get_ToaDo().y - (int)Camera::get_ChieuCao() / 2));

		if (font)
		{
			font->DrawTextA(NULL, message.c_str(), -1, &fRectangle, DT_LEFT, D3DCOLOR_XRGB(255, 25, 25));
		}
	}

// SUB-FUNCTION
private:
	void TaoBanDoVaCamera();
	void TaoDanhSachDoiTuongVaQuai();
	void CapNhatDanhSachDoiTuong(float in_tg);
	void VeDanhSachDoiTuong(const Vec2& in_DoDoi);
	void DieuChinhCamera();
	void XuLyVaChamChung();
};

