#include "LoCot.h"
#include "Camera.h"
#include "VaChamGame.h"

LoCot::LoCot(const Vec2 & in_ToaDo)
	:
	DoiTuong(in_ToaDo, Vec2(), 38, 46)
{
	mLoaiDoiTuong = eLDT_LoCot;
	mToaDoXuatHien = in_ToaDo;

	LoadThongTinHoatHinh();
}

void LoCot::CapNhat(float in_tg, const DoiTuong * in_XMan)
{
	if (mTGDem_HieuUngNoTung <= mTG_HieuUngNoTung)
	{
		mTGDem_HieuUngNoTung += in_tg;
		mHH_HieuUngPhatNo->CapNhat(in_tg);
	}

	// nếu đang nằm trong Camera mà vẫn đang va chạm Camera thì ko có gì xảy ra
	if (mNamTrongCamera &&
		!VaChamGame::get_DaVaCham(get_HCNGioiHan(), Camera::get_HCNGioiHan()))
	{
		mTrangThai = eTT_Ech_BienMat;
		// xét tiếp Tọa độ ban đầu có Nằm trong Camera hay ko?
		mToaDo = mToaDoXuatHien;
		if (!VaChamGame::get_DaVaCham(get_HCNGioiHan(), Camera::get_HCNGioiHan()))
		{
			mNamTrongCamera = false;
		}
	}
	// nếu đang nằm ngoài Camera mà ko có va chạm Camera thì ko có gì xảy ra
	else if (!mNamTrongCamera &&
		VaChamGame::get_DaVaCham(get_HCNGioiHan(), Camera::get_HCNGioiHan()))
	{
		mHP = mMaxHP;
		mNamTrongCamera = true;
	}

	// nếu Ếch đã bị phá hủy thì bỏ qua
	if (mTrangThai == eTT_Ech_BienMat)
	{
		return;
	}

	if (mHP <= 0 && mTrangThai != eTT_Ech_DangTanBien)
	{
	/*	DangTanBien();*/
	}

	if (mIsShining)
	{
		mTGDem_Shining += in_tg;
		if (mTGDem_Shining > mTG_Shining)
		{
			mTGDem_Shining = 0.0f;
			mIsShining = false;
		}
	}

	mHH_DuyNhat->CapNhat(in_tg);

	switch (mTrangThai)
	{

	}
}

void LoCot::Ve(const Vec2 & in_DoDoi)
{
	mHH_DuyNhat->Ve(DS_HinhAnh::get_TH()->LoCot_png, false, mToaDo, in_DoDoi);
	//if (mTGDem_HieuUngNoTung <= mTG_HieuUngNoTung)
	//{
	//	mHH_HieuUngPhatNo->Ve(DS_HinhAnh::get_TH()->HieuUngPhatNo_png, false, mToaDo/*mToaDo_HieuUngNoTung*/, in_DoDoi);
	//}

	//// nếu Ếch đã bị phá hủy thì bỏ qua
	//if (mTrangThai == eTT_Ech_BienMat)
	//{
	//	return;
	//}

	//if (mIsShining)
	//{
	//	if (mTrangThai != eTT_Ech_DangTanBien)
	//	{
	//		mHH_DuyNhat->Ve(DS_HinhAnh::get_TH()->Ech_Shining_png, mLatHinh, mToaDo, in_DoDoi);
	//	}
	//}
	//else
	//{
	//	if (mTrangThai == eTT_Ech_DangTanBien)
	//	{
	//		mHH_DuyNhat->Ve(DS_HinhAnh::get_TH()->Ech_png, mLatHinh, mToaDo, in_DoDoi, D3DCOLOR_ARGB(120, 255, 255, 225));
	//	}
	//	else
	//	{
	//		mHH_DuyNhat->Ve(DS_HinhAnh::get_TH()->Ech_png, mLatHinh, mToaDo, in_DoDoi);
	//	}
	//}
}

void LoCot::XuLyVaCham(const DoiTuong * in_DoiTuong)
{
}

void LoCot::LoadThongTinHoatHinh()
{
	std::vector<ThongTinFrame> lDSTTFrame;

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(38, 44, HCN(1, 1 + 38, 3, 3 + 46)));
	mHH_DuyNhat = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(16, 24, HCN(1 - 1, 1 + 16 - 1, 56 - 43, 56 + 16 - 43), 0.08f));
	lDSTTFrame.push_back(ThongTinFrame(32, 40, HCN(26 - 1, 26 + 32 - 1, 48 - 43, 48 + 32 - 43), 0.08f));
	lDSTTFrame.push_back(ThongTinFrame(28, 36, HCN(66 - 1, 66 + 28 - 1, 51 - 43, 51 + 24 - 43), 0.08f));
	lDSTTFrame.push_back(ThongTinFrame(30, 40, HCN(103 - 1, 103 + 30 - 1, 47 - 43, 47 + 28 - 43), 0.08f));
	lDSTTFrame.push_back(ThongTinFrame(32, 36, HCN(143 - 1, 143 + 32 - 1, 43 - 43, 43 + 28 - 43), 0.08f));
	lDSTTFrame.push_back(ThongTinFrame(32, 38, HCN(187 - 1, 187 + 32 - 1, 53 - 43, 53 + 30 - 43), 0.08f));
	mHH_HieuUngPhatNo = new HoatHinh(lDSTTFrame);
}

LoCot::~LoCot()
{
}
