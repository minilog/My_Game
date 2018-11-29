﻿#pragma once
#include "DoiTuong.h"
class DanLv :
	public DoiTuong
{
public:
	DanLv(const Vec2& in_ToaDo = Vec2(), const Vec2& in_VanToc = Vec2(), int in_Rong = 0, int in_Cao = 0)
		:
		DoiTuong(in_ToaDo, in_VanToc, in_Rong, in_Cao)
	{

	}
	~DanLv()
	{

	}

	virtual void CapNhat(float in_tg) = 0;
	virtual void Ve(const Vec2& in_DoDoi) = 0; // Độ dời phụ thuộc Camera hiện tại
	virtual void XuLyVaCham(DoiTuong* in_DoiTuong) = 0;

};

