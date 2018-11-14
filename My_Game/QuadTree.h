#pragma once

#include <d3dx9.h>
#include <d3d9.h>
#include <vector>
#include "VaChamGame.h"
#include "Camera.h"
#include "DoiTuong.h"

class QuadTree
{
public:
	QuadTree();
	~QuadTree();

private:
	//int get_Index(HinhChuNhat in_HCN);
	//void ChiaNhanh();
	//bool get_CoChua(DoiTuong *in_DoiTuong);

	QuadTree **Nodes;
	std::vector<DoiTuong*> mDSDoiTuong;
	int mCapDo;
};

