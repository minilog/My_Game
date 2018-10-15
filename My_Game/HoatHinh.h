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
	virtual void CapNhat(float dt);
	void Ve();
protected:
	void KhoiTaoVoiHoatHinh(int in_TongKhuonHinh, int in_SoHang, int in_SoCot, float in_ThoiGianThayDoi);

protected:
	int mTongSoKhuonHinh;
	int mSoHang;
	int mSoCot;
	int mViTriHienTai;
	int mHangHienTai;
	int mCotHienTai;
	int mChieuRongKhuonHinh;
	int mChieuCaoKhuonHinh;
	float mThoiGianThayDoi;
	float mTongThoiGianHienTai;
	RECT mHCN;
};

