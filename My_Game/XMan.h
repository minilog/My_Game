﻿#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "DoiTuong.h"
#include "KieuDuLieu.h"
#include "HoatHinh.h"
#include <map>
#include "BuiKhiLuot.h"

#include "HieuUngLuot.h"
#include "HieuUngBatRa.h"
#include "DanLv1.h"
#include "DanLv2.h"
#include "DanLv3.h"
#include "DanLv.h"

class XMan : public DoiTuong
{
private:

	static constexpr int PUSH_BUTTON = 'X';
	static constexpr int JUMP_BUTTON = 'C';
	static constexpr int FIRE_BUTTON = 'V';

public:
	XMan(const Vec2& in_ToaDo);
	~XMan();

	virtual void CapNhat(float in_tg);
	virtual void Ve(const Vec2& in_DoDoi); // Độ dời phụ thuộc Camera hiện tại
	virtual void XuLyVaCham(DoiTuong* in_DoiTuong);

	void XuLyBanPhim(std::map<int, bool> in_Keys);


	
private:
	HoatHinh *mHH_HieuUngNapDanLv2;
	HoatHinh *mHH_HieuUngNapDanLv3;

	DanLv3 *mDanLv3;
	DanLv2 *mDanLv2;
	float mTG_TichDanLv2 = 0.5f;
	float mTG_DemTichDan = 0.0f;

	static constexpr int mSoLuongDanLv1 = 7;
	DanLv1 *mDS_DanLv1[mSoLuongDanLv1];

	static constexpr int mSoLuongBui = 7;
	BuiKhiLuot *mDS_BuiKhiLuot[mSoLuongBui];
	float mTG_Bui = 0.085f;
	float mTG_DemBui = 0.0f;

	HieuUngLuot *mHieuUngLuot;
	HieuUngBatRa *mHieuUngBatRa;

	HoatHinh *mHH_DungIm,
		*mHH_Chay,
		*mHH_ChuanBiChay,
		*mHH_Nhay,
		*mHH_Roi,
		*mHH_TiepDat,
		*mHH_Luot,
		*mHH_Truot,
		*mHH_BatRa;
	HoatHinh *mHH_DungIm_Ban,
		*mHH_Chay_Ban,
		*mHH_ChuanBiChay_Ban,
		*mHH_Nhay_Ban,
		*mHH_Roi_Ban,
		*mHH_TiepDat_Ban,
		*mHH_Luot_Ban,
		*mHH_Truot_Ban,
		*mHH_BatRa_Ban;
	HoatHinh *mHH_HienTai;
	HoatHinh *mAnimationShining;

	float mTimes = 0.0f;
	float mTG_BamTuong = 0.18f;
	float mTG_DemBamTuong = 0.0f;
	float mTG_ChuanBiChay = 0.06f/*0.5f*/;
	float mTG_DemChuanBiChay = 0.0f;
	float mTG_TiepDat = 0.14f/*3.0f*/;
	float mTG_DemTiepDat = 0.0f;
	float mTG_Luot = 0.55f;
	float mTG_DemLuot = 0.0f;
	bool mChoPhepLuot = true;
	bool mDuocTangTocLucDangBay = false;
	float mVanTocCongThem = 100.0f * 1.2f;
	float mVanTocTruotToiDa = 160.0f;
	
	float mTG_BatRa = 0.12f;
	float mTG_DemBatRa = 0.0f;

	float mGiaTocTrongTruong = 970.0f/*40.0f*/;
	float mVanTocRoiToiDa = 380.0f/*100.0f*/;

	float mVanTocChayToiDa = 130.0f/*0.0f*/;

	std::map<int, bool> mKeys;
	bool mChoPhepNhay = true;
	bool mCoChuongNgaiVatTrai = false;
	bool mCoChuongNgaiVatPhai = false;

	eTrangThai mTrangThai;

	bool		mLatHinh = false;

	// Xét trạng thái bắn đạn
	bool mBanDan = false;
	float mTG_BanDan = 0.35f/*0.8f*/;
	float mTG_DemBanDan = mTG_BanDan + 0.1f;
	bool mChoPhepBan = true;
	
	// vì hàm xử lý va chạm: thực hiện với một DS đối tượng trước khi Cập Nhật
	// phải xét hết tất cả đối tượng, nếu không có đối tượng nào bên dưới thì mới rơi
	bool mDangDungTuNhienRoi = false;



	void LoadHinhAnhVao();

	void DungIm();
	void ChuanBiChay();
	void Chay();
	void Nhay();
	void Roi();
	void TiepDat();
	void Luot();
	void Truot();
	void BatRa();

	void ChuyenHH_BanDan();
	void ChuyenHH_KoBanDan();
			
	void CapNhat_DungIm();
	void CapNhat_ChuanBiChay(float in_tg);
	void CapNhat_Chay();
	void CapNhat_TiepDat(float in_tg);
	void CapNhat_Nhay(float in_tg);
	void CapNhat_Roi(float in_tg);
	void CapNhat_Luot(float in_tg);
	void CapNhat_BatRa(float in_tg);
	void CapNhat_Truot(float in_tg);

	void XuLyBanPhim_DungIm(std::map<int, bool> in_Keys);
	void XuLyBanPhim_Chay(std::map<int, bool> in_Keys);
	void XuLyBanPhim_Roi(std::map<int, bool> in_Keys);
	void XuLyBanPhim_TiepDat(std::map<int, bool> in_Keys);
	void XuLyBanPhim_ChuanBiChay(std::map<int, bool> in_Keys);
	void XuLyBanPhim_Nhay(std::map<int, bool> in_Keys);
	void XuLyBanPhim_Luot(std::map<int, bool> in_Keys);
	void XuLyBanPhim_Truot(std::map<int, bool> in_Keys);

	void XuLyBanPhim_BanDan(std::map<int, bool> in_Keys);

	void BanDanLv1();
	Vec2 DoDoiDanLv1() const;

	void BanDanLv2();
	Vec2 DoDoiDanLv2() const;
	void BanDanLv3();

	bool mIsShining = false;

	float mTimeChangeShining = 0.03f;
	float mTimeCount_ChangeShining = 0.0f;

	void DrawAnimationShining(const Vec2& in_DoDoi);

public:
	void get_DS_Dan(std::vector<DanLv*>& out);
};


