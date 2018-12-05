#pragma once

#include "DoiTuong.h"
#include "HoatHinh.h"
#include "DS_HinhAnh.h"

class LoCot : public DoiTuong
{
public:
	LoCot(const Vec2& in_ToaDo);
// FUNCTION
	// ko xài cái này
	void CapNhat(float in_tg)
	{
	}

	// FUNCTION

	void CapNhat(float in_tg, const DoiTuong *in_XMan);
	void Ve(const Vec2& in_DoDoi);
	void XuLyVaCham(const DoiTuong* in_DoiTuong);
// INFORMATION
private:
	HoatHinh *mHH_DuyNhat;
	HoatHinh *mHH_HieuUngPhatNo;

	Vec2 mToaDoXuatHien;

	int mHP;
	static constexpr int mMaxHP = 5;

	bool mLatHinh = false;

	bool mNamTrongCamera = false;

	bool mIsShining = false;
	static constexpr float mTG_Shining = 0.15f;
	float mTGDem_Shining = 0.0f;

	static constexpr float mTG_HieuUngNoTung = 0.08f * 6;
	float mTGDem_HieuUngNoTung = mTG_HieuUngNoTung + 0.1f;
// SUB-FUNCTION
private:
	void LoadThongTinHoatHinh();

public:
	~LoCot();
};

