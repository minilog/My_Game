#pragma once

#include <d3dx9.h>
#include <d3d9.h>
#include <vector>
#include "VaChamGame.h"
#include "Camera.h"
#include "ThucThe.h"

class CayBonNhanh
{
public:
	CayBonNhanh(int in_CapDo, RECT in_HCNGioiHan);
	void ThemThucThe(ThucThe *in_ThucThe);
	void LayTatCaThucTheCoKhaNangVaCham(std::vector<ThucThe*> &out_DanhSachThucThe, ThucThe *in_ThucThe);
	void LayTatCaThucThe(std::vector<ThucThe*> &out_DanhSachThucThe);
	int iTongSoThucThe();
	void DonDep();
protected:
	/* lấy vị trí của thực thể
	0: nằm trong Nhánh con Trái bên Trên
	1: nằm trong Nhánh Cây con Phải bên Trên
	2: nằm trong Nhánh con Trái bên Dưới
	3: nằm trong Nhánh con Phải bên dưới
	-1: bị dính: > 2 Nhánh con*/
	int iViTriIndex(RECT in_HCNGioiHanThucThe);
	void PhanChia();
	bool bBaoGom(ThucThe *in_ThucThe);

public:
	RECT mHCNGioiHan;
protected:
	CayBonNhanh **mCacNhanhCon;
	int mCapDo;
	std::vector<ThucThe*> mDanhSachThucThe; // các Thực Thể không thuộc Nhánh con
};

