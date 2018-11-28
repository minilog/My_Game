#include "DanLv2.h"

DanLv2::DanLv2(const Vec2 & in_ToaDo, const Vec2 & in_VanToc)
	:DoiTuong(in_ToaDo, in_VanToc, 0, 0)
{
	mLoaiDoiTuong = eLDT_DanLV2;

	LoadHinhAnhVao();

	mHH_HienTai = mHH_DangTanBien;
	mTrangThai = eTTDan_DaBiPhaHuy;
}

DanLv2::~DanLv2()
{
	if (mHH_DangTanBien)
		delete mHH_DangTanBien;
	if (mHH_DangTonTai)
		delete mHH_DangTonTai;
}

void DanLv2::CapNhat(float in_tg)
{
	if (mTrangThai == eTTDan_DaBiPhaHuy)
		return;

	if (mTrangThai == eTTDan_Ban)
	{
		mTG_DemPhaHuy += in_tg;

		if (mTG_DemPhaHuy > mTG_PhaHuy)
			DangTonTai();
	}

	if (mTrangThai == eTTDan_DangTonTai)
	{
		mToaDo.x += mVanToc.x;
		mToaDo.y += mVanToc.y;
	}
}

void DanLv2::Ve(const Vec2 & in_DoDoi)
{
	if (mTrangThai == eTTDan_DaBiPhaHuy)
		return;

	mHH_HienTai->set_ToaDo(mToaDo);
	mHH_HienTai->set_DoDoi(in_DoDoi);
	mHH_HienTai->Ve();
}

void DanLv2::XuLyVaCham(DoiTuong * in_DoiTuong)
{
}

void DanLv2::LoadHinhAnhVao()
{
	std::vector<ThongTinFrame> lDSTTFrame;

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 16, 14, 0.1f, HCN(26, 42, 7, 21)));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 24, 24, 0.1f, HCN(46, 70, 2, 26)));
	mHH_DangTonTai = new HoatHinh("Resources_X3/XMan/DanLv2.png", lDSTTFrame, D3DCOLOR_XRGB(50, 96, 166));

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 28, 12, 0.1f, HCN(75, 103, 8, 20)));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 32, 8, 0.1f, HCN(109, 141, 10, 18)));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 38, 12, 0.1f, HCN(148, 186, 8, 20)));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 36, 22, 0.1f, HCN(191, 227, 3, 25)));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 38, 12, 0.1f, HCN(232, 270, 8, 20)));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 40, 22, 0.1f, HCN(276, 416, 3, 25)));
	mHH_DangTanBien = new HoatHinh("Resources_X3/XMan/DanLv2.png", lDSTTFrame, D3DCOLOR_XRGB(50, 96, 166));

	mTG_PhaHuy = 0.0f;
	for (int i = 0; i < (int)lDSTTFrame.size(); i++)
	{
		mTG_PhaHuy += lDSTTFrame[i].ThoiGian;
	}
}

void DanLv2::DangTanBien()
{
	mHH_HienTai = mHH_DangTanBien;
	mTrangThai = eTTDan_DangTanBien;
	mTG_DemPhaHuy = 0.0f;
}

void DanLv2::DangTonTai()
{
	mHH_HienTai = mHH_DangTonTai;
	mTrangThai = eTTDan_DangTonTai;
}

void DanLv2::Ban()
{
	mHH_HienTai = mHH_DangTanBien;
	mTrangThai = eTTDan_Ban;
	mTG_DemPhaHuy = 0.0f;
}