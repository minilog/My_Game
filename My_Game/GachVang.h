#pragma once

#include "VienGach.h"

class GachVang : public VienGach
{
public:
	GachVang(D3DXVECTOR3 in_ToaDo);
	virtual const char* cTenFile();
	virtual int iTongKhuonHinh();
	virtual int iSoHang();
	virtual int iSoCot();
	virtual float fThoiGianThayDoi();
};

