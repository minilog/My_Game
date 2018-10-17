#include "GachVang.h"

GachVang::GachVang(D3DXVECTOR3 in_ToaDo)
{
	VienGach::KhoiTao(in_ToaDo);
}

const char * GachVang::cTenFile()
{
	return "Resources/goldbrick.png";
}

int GachVang::iTongKhuonHinh()
{
	return 4;
}

int GachVang::iSoHang()
{
	return 1;
}

int GachVang::iSoCot()
{
	return 4;
}

float GachVang::fThoiGianThayDoi()
{
	return 0.8f;
}
