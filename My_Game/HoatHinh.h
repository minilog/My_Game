#pragma once

#include "HinhAnh.h"

using namespace std;

class HoatHinh : public HinhAnh
{
public:
	HoatHinh(const char* in_DuongDan, int in_TongKhuonHinh, int in_SoHang, 
		int in_SoCot, float in_ThoiGianThayDoi);
	~HoatHinh() {}
	void CapNhat(float in_tg);
	void Ve();

private:
	int mTongKhuonHinh;
	int mSoHang;
	int mSoCot;
	int mHangHienTai;
	int mCotHienTai;
	float mThoiGianThayDoi;
	float mTongThoiGianHienTai;
};

