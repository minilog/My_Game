#pragma once
#include "DoiTuong.h"
#include "HoatHinh.h"
#include "DS_HinhAnh.h"
#include "OngCon.h"
#define VAL 0.0174532925

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
	Vec2 ViTri_CanDenHienTai; // có 2 Vị Trí cho BOSS
	OngCon* get_OngCon0() { return DS_OngCon[0]; }
	OngCon* get_OngCon1() { return DS_OngCon[1]; }
	OngCon* get_OngCon2() { return DS_OngCon[2]; }
	OngCon* get_OngCon3() { return DS_OngCon[3]; }
	OngCon* get_OngCon4() { return DS_OngCon[4]; }
// INFORMATION
private:
	float DX, DY;
	OngCon *DS_OngCon[5];
	Vec2 ViTri1;
	Vec2 ViTri2;
	float KC_BOSS_XMAN;
	float GocSin = 45.0f;
	static constexpr float TG_ThaOng = 0.1f * 9;
	static constexpr float TG_DamKim = 0.9f + 0.06f * 6;
	static constexpr float TG_ChuanBiDamKim = 0.06f * 14;
	static constexpr float VanTocTiepCan = 400.0f;
	static constexpr float VanTocBay = 150.0f;
	static constexpr float VanTocX_VongSo8 = 120.0f;
	float DEM = 0.0f;
	bool DaThaOng = false;
	bool LatHinh = false;
	HoatHinh *HH_HienTai,
		*HH_Bay,
		*HH_ChuanBiDamKim,
		*HH_DamKim,
		*HH_ThaOng;
	HoatHinh *HH_CanhOng;
// SUB-FUNCTION
private:
	void XuatHien();
	void ChuanBiDamKim();
	void DamKim();
	void VaoViTri(const Vec2& in_ViTriCanDen);
	void ThaOng();
	void BayVongSo8();
	void LoadThongTinHoatHinh();
// DESTRUCTURE
public:
	~BOSS();
};

