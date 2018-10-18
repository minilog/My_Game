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
	HoatHinh(const char* in_DuongDan, int in_TongKhuonHinh, int in_SoHang, int in_SoCot, float in_ThoiGianThayDoi);
protected:
	void KhoiTaoVoiHoatHinh(int in_TongKhuonHinh, int in_SoHang, int in_SoCot, float in_ThoiGianThayDoi);
public:
	virtual void CapNhat(float in_tg);
	void Ve();

protected:
	int mTongSoKhuonHinh;
	int mSoHang;
	int mSoCot;
	//int mViTriIndexBatDau;
	//int mViTriIndexKetThuc;
	//int mViTriIndexHienTai;
	float mThoiGianThayDoi;
	int mHangHienTai;
	int mCotHienTai;
	float mTongThoiGianHienTai;
};

