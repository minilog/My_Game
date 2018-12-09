#pragma once

#include "DoiTuong.h"
#include "DS_HinhAnh.h"
#include "HoatHinh.h"

class BOSS1
{
public:
// CONSTRUCTURE
	BOSS1();

	void CapNhat(float in_tg) {}

// FUNCTION
	void Ve(const Vec2& in_DoDoi); // Độ dời phụ thuộc Camera hiện tại
	void XuLyVaCham(const DoiTuong* in_DoiTuong);
	void CapNhat(float in_tg, const DoiTuong *in_DoiTuong) {}

// DESTRUCTURE
	~BOSS1();
};

