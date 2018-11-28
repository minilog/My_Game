#pragma once

#include "ManGame.h"
#include "HinhAnh.h"
#include "XMan.h"
#include "GameDebugDraw.h"
#include "DoiTuongTinh.h"
#include <vector>
#include "QuadTree.h"


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

	void DrawQuadTree(QuadTree *in_QuadTree);
	void DrawCollidable();

	QuadTree *mQuadTree;

private:
	std::map<int, bool> mKeys;
	HinhAnh *mBanDoMap1;
	XMan *mXMan;
	HinhAnh *mTest;
	GameDebugDraw *mGameDebugDraw;

	void TaoBanDoVaCamera();
	void TaoDanhSachDoiTuong();
	void TaoDanhSachTileset();
	void VeHinhAnhBanDoGame(const Vec2& in_DoDoi);

	void CapNhatDanhSachDoiTuong(float in_tg);
	void VeDanhSachDoiTuong(const Vec2& in_DoDoi);

	void DieuChinhCamera();


	std::vector<DoiTuong*> mDS_DoiTuongXetVaCham;
	void XuLyVaChamChung();


	ID3DXFont *font;
	RECT fRectangle;
	std::string message;

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
};

