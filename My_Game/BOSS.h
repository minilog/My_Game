#pragma once
#include "DoiTuong.h"
#include "HoatHinh.h"
#include "DS_HinhAnh.h"

class BOSS :
	public DoiTuong
{
// CONSTRUCTURE
public:
	BOSS(const Vec2& in_ToaDo);
	void CapNhat(float in_tg) {} // NOT USE
// FUNCTION
public:
	void CapNhat(float in_tg, const DoiTuong *in_DoiTuong);
	void XuLyVaCham(const DoiTuong* in_DoiTuong);
	void Ve(const Vec2& in_DoDoi); // Độ dời phụ thuộc Camera hiện tại
// INFORMATION
private:
	bool LatHinh = false;
	HoatHinh *HH_HienTai,
		*HH_DungIm,
		*HH_ChuanBiDamKim,
		*HH_DamKim,
		*HH_ThaOng;
	HoatHinh *HH_CanhOng;
// SUB-FUNCTION
private:
	void LoadThongTinHoatHinh();
// DESTRUCTURE
public:
	~BOSS();
};

