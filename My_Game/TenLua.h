﻿#pragma once

#include "DoiTuong.h"
#include "HoatHinh.h"
#include "VaChamGame.h"
#include "DS_HinhAnh.h"


class TenLua :
	public DoiTuong
{
public:
	TenLua();

// FUNCTION
	void CapNhat(float in_tg);
	void Ve(const Vec2& in_DoDoi);
	void XuLyVaCham(const DoiTuong* in_DoiTuong);
	void BanRa(const Vec2& in_ToaDo, const Vec2& in_VanToc);
	void PhatNo();

// INFORMATION
private:
	HoatHinh *mHH_Dan;
	HoatHinh *mHH_HieuUngPhatNo;

	static constexpr float TG_NoTung = 0.08f * 6;
	float TGDem_NoTung = TG_NoTung + 0.1f;

	// lỡ như ko va chạm thì Đạn có thể tự động biến mất để có thể dùng tiếp
	static constexpr float TG_TuDongBienMat = 1.1f;
	float TGDem_TuDongBienMat = 0.0f;



	// SUB-FUNCTION
	void LoadThongTinHoatHinh();

	//DESTRUCTURE
	~TenLua();

};

