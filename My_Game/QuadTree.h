#pragma once

#include <d3dx9.h>
#include <d3d9.h>
#include <vector>
#include "VaChamGame.h"
#include "Camera.h"
#include "DoiTuong.h"
#include "KieuDuLieu.h"

class QuadTree
{
public:
	QuadTree(int in_CapDo, const HCN& in_HCN);
	~QuadTree();
	void DonDep();
	void ThemDoiTuong(DoiTuong *in_DoiTuong);
	void get_CacDoiTuongCoTheVaCham(std::vector<DoiTuong*> &out_CacDoiTuong, DoiTuong *in_DoiTuong);
	void get_TatCaDoiTuong(std::vector<DoiTuong*> &out_CacDoiTuong);
	int get_TongDoiTuong();

private:
	int get_ViTri(const HCN& in_DoiTuong);
	void ChiaNhanh();
	bool get_CoChua(const DoiTuong *in_DoiTuong);

	int mCapDo;
	HCN mGioiHan;
	QuadTree **mBonNhanh;
	std::vector<DoiTuong*> mDSDoiTuong;
};

