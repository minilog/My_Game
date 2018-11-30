﻿#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "DoiTuong.h"
#include "KieuDuLieu.h"
#include "HoatHinh.h"
#include <map>
#include "VaChamGame.h"
#include "Camera.h"
#include "DanLv.h"
#include "XMan.h"

class Ech : public DoiTuong
{
public:
	Ech(const Vec2& in_ToaDo, const Vec2& in_VanToc, int in_Rong = 26, int in_Cao = 30);


	// ko xài cái này
	void CapNhat(float in_tg) 
	{
	}

	void CapNhat(float in_tg, const XMan *in_XMan);
	void Ve(const Vec2& in_DoDoi);
	void XuLyVaCham(const DoiTuong* in_DoiTuong);

private:
	void NhamBan2();
	void BanDan2();
	void HaNhamBan2();
	void NhamBan3();
	void BanDan3();
	void HaNhamBan3();
	void BanDan1();
	void NhamBan1();
	void HaNhamBan1();
	void ChuanBiNhay();
	void Nhay();
	void Roi();
	void TiepDat();

	void LoadHinhAnhVao();

private:
	int mHP = 5;

	BuiKhiLuot *mBui;

	HoatHinh *mHH_ChuanBiNhay,
		*mHH_Nhay,
		*mHH_Roi,
		*mHH_NhamBan1,
		*mHH_BanDan1,
		*mHH_HaNhamBan1,
		*mHH_NhamBan3,
		*mHH_BanDan3,
		*mHH_HaNhamBan3,
		*mHH_NhamBan2,
		*mHH_BanDan2,
		*mHH_HaNhamBan2,
		*mHH_DangTanBien;
	HoatHinh *mHH_HienTai;	
	HoatHinh *mHH_Shining;

	bool mIsShining = false;
	const float mTG_Shining = 0.15f;
	float mTGDem_Shining = 0.0f;

	float mTGDem_BuiXuatHien = 0.35f;

	const float mTG_ChuanBiNhay = 0.12f * 5 - 0.05f;
	float mTGDem_ChuanBiNhay = 0.0f;

	const float mTG_TiepDat = 0.12f * 5;
	float mTGDem_TiepDat = 0.0f;

	const float mTG_NhamBan1 = 0.14f * 3;
	float mTGDem_NhamBan1 = 0.0f;

	const float mTG_HaNhamBan1 = 0.14f * 3;
	float mTGDem_HaNhamBan1 = 0.0f;

	const float mTG_BanDan = 0.25f * 2 * 3;
	float mTGDem_BanDan = 0.0f;

	const float mTG_NhamBan2 = 0.14f * 4;
	float mTGDem_NhamBan2 = 0.0f;

	const float mTG_HaNhamBan2 = 0.14f * 4;
	float mTGDem_HaNhamBan2 = 0.0f;

	const float mTG_NhamBan3 = 0.14f * 5;
	float mTGDem_NhamBan3 = 0.0f;

	const float mTG_HaNhamBan3 = 0.14f * 5;
	float mTGDem_HaNhamBan3 = 0.0f;

	const float mGiaTocTrongTruong = 1000.0f;
	const float mVanTocRoiToiDa = 300.0f;
	const float mVanTocNhay = 120.0f;

	bool mLatHinh = false;

	eTrangThai mTrangThai;

	void CapNhat_NhamBan2(float in_tg, float in_KhoangCach_XMan);
	void CapNhat_BanDan2(float in_tg);
	void CapNhat_HaNhamBan2(float in_tg);
	void CapNhat_ChuanBiNhay(float in_tg, float in_KhoangCach_XMan);
	void CapNhat_Nhay(float in_tg);
	void CapNhat_Roi(float in_tg);
	void CapNhat_TiepDat(float in_tg, float in_KhoangCach_XMan);
	void CapNhat_NhamBan1(float in_tg, float in_KhoangCach_XMan);
	void CapNhat_HaNhamBan1(float in_tg);
	void CapNhat_BanDan1(float in_tg);
	void CapNhat_NhamBan3(float in_tg, float in_KhoangCach_XMan);
	void CapNhat_BanDan3(float in_tg);
	void CapNhat_HaNhamBan3(float in_tg);

public:
	~Ech();
};

