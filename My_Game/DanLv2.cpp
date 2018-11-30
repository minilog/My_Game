#include "DanLv2.h"

DanLv2::DanLv2(const Vec2 & in_ToaDo, const Vec2 & in_VanToc)
	:DanLv(in_ToaDo, in_VanToc, 15, 12)
{
	mLoaiDoiTuong = eLDT_DanLv2;

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

	mHH_HienTai->CapNhat(in_tg);

	if (mTrangThai == eTTDan_BanRa)
	{
		mTG_DemPhaHuy += in_tg;

		if (mTG_DemPhaHuy > mTG_PhaHuy)
			DangTonTai();
	}

	if (mTrangThai == eTTDan_DangTonTai)
	{
		mToaDo.x += mVanToc.x * in_tg;
		mToaDo.y += mVanToc.y * in_tg;
	}

	if (mTrangThai == eTTDan_DangTanBien)
	{
		mTG_DemPhaHuy += in_tg;

		if (mTG_DemPhaHuy > mTG_PhaHuy)
			mTrangThai = eTTDan_DaBiPhaHuy;
	}

	if (!VaChamGame::get_DaVaCham(get_HCNGioiHan(), Camera::get_HCNGioiHan()))
	{
		mTrangThai = eTTDan_DaBiPhaHuy;
	}
}

void DanLv2::Ve(const Vec2 & in_DoDoi)
{
	if (mTrangThai == eTTDan_DaBiPhaHuy)
		return;

	mHH_HienTai->set_LatTheoChieuNgang(mLatHinh);
	mHH_HienTai->set_ToaDo(mToaDo);
	mHH_HienTai->set_DoDoi(in_DoDoi);
	mHH_HienTai->Ve();
}

void DanLv2::XuLyVaCham(const DoiTuong * in_DoiTuong)
{
	if (mTrangThai == eTTDan_DaBiPhaHuy || mTrangThai == eTTDan_DangTanBien)
		return;

	if (in_DoiTuong->get_LoaiDoiTuong() == eLDT_DoiTuongTinh)
	{
		if (VaChamGame::get_DaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan()))
		{
			if (!mLatHinh)
				mToaDo.x += 10.0f;
			else
				mToaDo.x -= 10.0f;

			DangTanBien();
		}
	}

	if (in_DoiTuong->get_LoaiDoiTuong() == eLDT_Ech)
	{
		if (VaChamGame::get_DaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan()))
		{
			DangTanBien();
		}
	}

}

void DanLv2::LoadHinhAnhVao()
{
	std::vector<ThongTinFrame> lDSTTFrame;

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 16, 14, 0.03f, HCN(26, 42, 7, 21)));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 24, 24, 0.03f, HCN(46, 70, 2, 26)));
	mHH_DangTanBien = new HoatHinh("Resources_X3/XMan/DanLv2.png", lDSTTFrame, D3DCOLOR_XRGB(50, 96, 166));

	mTG_PhaHuy = 0.0f;
	for (int i = 0; i < (int)lDSTTFrame.size(); i++)
	{
		mTG_PhaHuy += lDSTTFrame[i].ThoiGian;
	}

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 36, 12, 0.08f, HCN(75, 103, 8, 20)));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 40, 8,  0.08f, HCN(109, 141, 10, 18)));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 46, 12, 0.08f, HCN(148, 186, 8, 20)));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 44, 22, 0.08f, HCN(191, 227, 3, 25)));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 46, 12, 0.08f, HCN(232, 270, 8, 20)));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 48, 22, 0.08f, HCN(276, 316, 3, 25)));
	mHH_DangTonTai = new HoatHinh("Resources_X3/XMan/DanLv2.png", lDSTTFrame, D3DCOLOR_XRGB(50, 96, 166));
}

void DanLv2::DangTanBien()
{
	mHH_HienTai = mHH_DangTanBien;
	mHH_HienTai->Remake();
	mTrangThai = eTTDan_DangTanBien;
	mTG_DemPhaHuy = 0.0f;
}

void DanLv2::DangTonTai()
{
	mHH_HienTai = mHH_DangTonTai;
	mHH_HienTai->Remake();
	mTrangThai = eTTDan_DangTonTai;
}

void DanLv2::Ban()
{
	mHH_HienTai = mHH_DangTanBien;
	mHH_HienTai->Remake();
	mTrangThai = eTTDan_BanRa;
	mTG_DemPhaHuy = 0.0f;
}