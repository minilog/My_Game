#pragma once

#include "DoiTuong.h"
#include "DS_HinhAnh.h"
#include "HoatHinh.h"

class BOSS2 :
	public DoiTuong
{
public:
	BOSS2(const Vec2& in_ToaDo);

	void CapNhat(float in_tg) {}

// FUNCTION
	void CapNhat(float in_tg, const DoiTuong *in_DoiTuong);
	void XuLyVaCham(const DoiTuong* in_DoiTuong);
	void Ve(const Vec2& in_DoDoi); // Độ dời phụ thuộc Camera hiện tại

// INFORMATION
private:
	HoatHinh* HH_BOSS;

// SUB-FUNCTION
	void LoadThongTinHoatHinh();

public:
	~BOSS2();
};

