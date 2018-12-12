#pragma once

#include "DoiTuong.h"
#include "DS_HinhAnh.h"
#include "HoatHinh.h"

class BOSS2 :
	public DoiTuong
{
public:
	BOSS2(const Vec2& in_ToaDo = Vec2(4990.0f, 984.0f));

	void CapNhat(float in_tg) {}

// FUNCTION
	void CapNhat(float in_tg, const DoiTuong *in_DoiTuong);
	void XuLyVaCham(const DoiTuong* in_DoiTuong);
	void Ve(const Vec2& in_DoDoi); // Độ dời phụ thuộc Camera hiện tại

// INFORMATION
private:
	HoatHinh	*HH_1,
				*HH_2;
	Vec2 ToaDo_HH1;
	Vec2 ToaDo_HH2;


	float DEM = 0.0f;
	static constexpr float TG_XuatHien = 4.33f;
	static constexpr float TG_BoChay = 4.33f;


// SUB-FUNCTION
	void XuatHien();
	void BocVac();
	void BoChay();
	void BienMat();

	void LoadThongTinHoatHinh();

public:
	~BOSS2();
};

