#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <d3d9.h>
#include <vector>

#include "HinhAnh.h"

using namespace std;

class HoatHinh : public HinhAnh
{
public:
	HoatHinh(const char* in_DuongDan, int in_TongKhuonHinh, int in_SoHang, int in_SoCot, float in_ThoiGianThayDoi)
		:HinhAnh(in_DuongDan)
	{
		KhoiTaoVoiHoatHinh(in_TongKhuonHinh, in_SoHang, in_SoCot, in_ThoiGianThayDoi);
	}
protected:
	void KhoiTaoVoiHoatHinh(int in_TongKhuonHinh, int in_SoHang, int in_SoCot, float in_ThoiGianThayDoi);
public:
	virtual void CapNhat(float tg);
	void Ve()
	{
		HinhAnh::Ve();
	}


protected:
	int mTongSoKhuonHinh;
	int mSoHang;
	int mSoCot;
	float mThoiGianThayDoi;
	int mHangHienTai;
	int mCotHienTai;
	float mTongThoiGianHienTai;
};

