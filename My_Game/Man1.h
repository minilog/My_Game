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
	XMan *mXman;
	HinhAnh *mTest;
	GameDebugDraw *mGameDebugDraw;

	void TaoBanDoVaCamera();
	void TaoDanhSachDoiTuong();
	void TaoDanhSachTileset();
	void VeHinhAnhBanDoGame(const Vec2& in_DoDoi);

	void CapNhatDanhSachDoiTuong(float in_tg);
	void VeDanhSachDoiTuong(const Vec2& in_DoDoi);


	std::vector<DoiTuong*> mDS_DoiTuongXetVaCHam;
	void XuLyVaChamChung();
};

