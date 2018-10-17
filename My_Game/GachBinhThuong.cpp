#include "GachBinhThuong.h"

GachBinhThuong::GachBinhThuong(D3DXVECTOR3 in_ToaDo)
{
	VienGach::KhoiTao(in_ToaDo);
}

const char * GachBinhThuong::cTenFile()
{
	return "Resources/normalbrick.png";
}

int GachBinhThuong::iTongKhuonHinh()
{
	return 1;
}

int GachBinhThuong::iSoHang()
{
	return 1;
}

int GachBinhThuong::iSoCot()
{
	return 1;
}

float GachBinhThuong::fThoiGianThayDoi()
{
	return 1.0f;
}
