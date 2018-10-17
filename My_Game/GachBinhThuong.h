#pragma once

#include "VienGach.h"

class GachBinhThuong : public VienGach
{
public:
	GachBinhThuong(D3DXVECTOR3 in_ToaDo);

	virtual const char* cTenFile();
	virtual int iTongKhuonHinh();
	virtual int iSoHang();
	virtual int iSoCot();
	virtual float fThoiGianThayDoi();
};

