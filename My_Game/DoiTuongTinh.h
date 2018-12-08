#pragma once

#include "DoiTuong.h"

class DoiTuongTinh : public DoiTuong
{
public:
	DoiTuongTinh(Vec2 in_ToaDo, int in_Width, int in_Height, int in_K = 0) :
		DoiTuong(in_ToaDo, Vec2(0, 0), in_Width, in_Height)
	{
		K = in_K;
		if (K == 0)
		{
			DoiTuong::mLoaiDoiTuong = eLDT_DoiTuongTinh;
		}
		if (K == -1)
		{
			mLoaiDoiTuong = eLDT_Gai;
		}
	}

	virtual void CapNhat(float in_tg) {}
	virtual void Ve(const Vec2& in_DoDoi) {}
	virtual void XuLyVaCham(const DoiTuong* in_DoiTuong) {}
private:
	int K;
};

