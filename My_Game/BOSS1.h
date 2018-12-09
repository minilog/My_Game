#pragma once

#include "DoiTuong.h"
#include "DS_HinhAnh.h"
#include "HoatHinh.h"

class BOSS1 : public DoiTuong
{
public:
// CONSTRUCTURE
	BOSS1(const Vec2& in_ToaDo);

	void CapNhat(float in_tg) {}

// FUNCTION
	void CapNhat(float in_tg, const DoiTuong *in_DoiTuong);
	void XuLyVaCham(const DoiTuong* in_DoiTuong);
	void Ve(const Vec2& in_DoDoi); // Độ dời phụ thuộc Camera hiện tại

// INFORMATION
private:
	HoatHinh* HH_ConPet;
	HoatHinh* HH_AnhSang;
	HoatHinh* HH_XuatHien;

	void LoadThongTinHoatHinh();

// DESTRUCTURE
public:
	~BOSS1();
};

