#pragma once

#include "DoiTuong.h"
#include "HoatHinh.h"
#include "DS_HinhAnh.h"
#include "DanNo1.h"
#include "TenLua.h"

class LoCot : public DoiTuong
{
public:
	LoCot(const Vec2& in_ToaDo, std::vector<DanNo1*>& in_DS_DanNo1, std::vector<TenLua*>& in_DS_TenLua);

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
	// các đối tượng khác
	std::vector<DanNo1*> mDS_DanNo1; // chỉ chứa con trỏ chỉ đến 
	std::vector<TenLua*> mDS_TenLua; // trỏ đến Tên Lửa Màn 1
	
	HoatHinh *mHH_DuyNhat;
	HoatHinh *mHH_HieuUngPhatNo;
	Vec2 ToaDoPhatNo;

	bool mNamTrongCamera = false;
	bool mLatHinh = false;

	static constexpr float TG_BanTL = 2.0f;
	static constexpr float TG_BanDan = 2.0f;
	static constexpr float TG_HieuUngPhatNo = 0.08f * 6;
	float mTG_Dem = 0.0f;
	float mTGDem_DanDuocBanRa = 0.0f;
	float mTGDem_HieuUngPhatNo = TG_HieuUngPhatNo + 0.1f;
	static constexpr int MaxHP = 7;
	int HP = 7;
	bool IsShining = false;
	float TGDem_IsShining = 0.0f;

// SUB-FUNCTION
private:
	void LoadThongTinHoatHinh();
	
	void BanDan();
	void BanTL();
	void BienMat();

	int get_HP() const { return HP; }

public:
	~LoCot();
};

