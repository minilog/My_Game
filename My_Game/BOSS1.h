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
	static constexpr int MAX_HP = 100;
	int HP = MAX_HP;
	float TG_Dem;
	int Color_AnhSang = 0;
	
	static constexpr float TG_Shining = 0.07f;
	float TGDem_Shining = TG_Shining + 0.1f;

	static constexpr float GiaTocTrongTruong = 1000.0f;
	static constexpr float VanTocRoiToiDa = 360.0f;

	Vec2 ToaDo_Pet;
	Vec2 ToaDo_BanDau;

	HoatHinh* HH_ConPet;
	HoatHinh* HH_AnhSang;

	HoatHinh* HH_XuatHien;
	HoatHinh* HH_TanCong;
	HoatHinh* HH_TanCong3;
	HoatHinh* HH_HienTai;
	HoatHinh* HH_Shining;

	HoatHinh *mHH_HieuUngPhatNo[4];

// SUB-FUNCTION
	void XuatHien();
	void TanCong1();
	void TanCong2();
	void TanCong3();
public:
	void BienMat();
private:

	void LoadThongTinHoatHinh();

// DESTRUCTURE
public:
	~BOSS1();
};

