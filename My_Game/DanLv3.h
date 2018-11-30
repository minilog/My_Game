﻿#pragma once
#include "DoiTuong.h"

#include <d3d9.h>
#include <d3dx9.h>
#include "KieuDuLieu.h"
#include "HoatHinh.h"
#include <map>
#include "VaChamGame.h"
#include "Camera.h"
#include "DanLv.h"

class DanLv3 :
	public DanLv
{

public:
	DanLv3(const Vec2& in_ToaDo = Vec2(), const Vec2& in_VanToc = Vec2());
	~DanLv3();

	void CapNhat(float in_tg);
	void Ve(const Vec2& in_DoDoi); // Độ dời phụ thuộc Camera hiện tại
	void XuLyVaCham(const DoiTuong* in_DoiTuong);

	void Remake()
	{
		Ban();
	}

	eTrangThai get_TrangThai() const
	{
		return mTrangThai;
	}

	void set_LatHinh(bool a)
	{
		mLatHinh = a;
	}

	int get_Damage() const
	{
		return 3;
	}

private:
	HoatHinh *mHH_DangTonTai;
	HoatHinh *mHH_DangTanBien;
	HoatHinh *mHH_BanRa;
	HoatHinh *mHH_HienTai;

	bool mLatHinh = false;

	float mTG_PhaHuy; // giá trị phụ thuộc vào HH_BiPhaHuy
	float mTG_DemPhaHuy = 0.0f;

	float mTG_BanRa;
	float mTG_DemBanRa = 0.0f;

	eTrangThai mTrangThai;

	void LoadHinhAnhVao();
	void DangTanBien();
	void DangTonTai();
	void Ban();
public:
	static constexpr float mVanTocDan = 400.0f /*0.0f*/;
};

