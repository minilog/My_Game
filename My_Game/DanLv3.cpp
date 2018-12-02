#include "DanLv3.h"



DanLv3::DanLv3(const Vec2 & in_ToaDo, const Vec2 & in_VanToc)
	:
	DanLv(in_ToaDo, in_VanToc, 24, 20)
{
	mLoaiDoiTuong = eLDT_DanLv3;
	mDamage = 4;

	LoadHinhAnhVao();

	mHH_HienTai = mHH_DangTanBien;
	mTrangThai = eTTDan_DaBiPhaHuy;
}

DanLv3::~DanLv3()
{
	if (mHH_BanRa)
		delete mHH_BanRa;
	
	if (mHH_DangTonTai)
		delete mHH_DangTonTai;

	if (mHH_DangTanBien)
		delete mHH_DangTanBien;
}

void DanLv3::CapNhat(float in_tg)
{
	if (mTrangThai == eTTDan_DaBiPhaHuy)
		return;

	mHH_HienTai->CapNhat(in_tg);

	if (mTrangThai == eTTDan_BanRa)
	{
		mTG_DemBanRa += in_tg;

		if (mTG_DemBanRa > mTG_BanRa)
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

void DanLv3::Ve(const Vec2 & in_DoDoi)
{
	if (mTrangThai == eTTDan_DaBiPhaHuy)
		return;

	mHH_HienTai->set_LatTheoChieuNgang(mLatHinh);
	mHH_HienTai->set_ToaDo(mToaDo);
	mHH_HienTai->set_DoDoi(in_DoDoi);
	mHH_HienTai->Ve();
}

void DanLv3::XuLyVaCham(const DoiTuong * in_DoiTuong)
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
	//if (in_DoiTuong->get_LoaiDoiTuong() == eLDT_Ech)
	//{
	//	if (VaChamGame::get_DaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan()))
	//	{
	//		if (!mLatHinh)
	//			mToaDo.x += 10.0f;
	//		else
	//			mToaDo.x -= 10.0f;

	//		DangTanBien();
	//	}
	//}

}

void DanLv3::LoadHinhAnhVao()
{
	std::vector<ThongTinFrame> lDSTTFrame;

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 14, 20, 0.03f, HCN(15, 15 + 14, 10, 10 + 20)));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 24, 16, 0.03f, HCN(46, 46 + 24, 2, 2 + 16)));
	mHH_BanRa = new HoatHinh("Resources_X3/XMan/DanLv3.png", lDSTTFrame, D3DCOLOR_XRGB(50, 96, 166));

	mTG_BanRa = 0.0f;
	for (int i = 0; i < (int)lDSTTFrame.size(); i++)
	{
		mTG_BanRa += lDSTTFrame[i].ThoiGian;
	}

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 54, 32, 0.03f, HCN(64, 64 + 46, 5, 5 + 32)));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 52, 30, 0.03f, HCN(115, 115 + 46, 6, 6 + 30)));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 48, 32, 0.03f, HCN(164, 164 + 42, 5, 5 + 32)));
	mHH_DangTonTai = new HoatHinh("Resources_X3/XMan/DanLv3.png", lDSTTFrame, D3DCOLOR_XRGB(50, 96, 166));

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 14, 20, 0.03f, HCN(258, 258 + 14, 10, 10 + 20)));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 24, 28, 0.03f, HCN(276, 276 + 24, 6, 6 + 28)));
	mHH_DangTanBien = new HoatHinh("Resources_X3/XMan/DanLv3.png", lDSTTFrame, D3DCOLOR_XRGB(50, 96, 166));

	mTG_PhaHuy = 0.0f;
	for (int i = 0; i < (int)lDSTTFrame.size(); i++)
	{
		mTG_PhaHuy += lDSTTFrame[i].ThoiGian;
	}
}

void DanLv3::DangTanBien()	
{
	mHH_HienTai = mHH_DangTanBien;
	mHH_HienTai->Remake();
	mTrangThai = eTTDan_DangTanBien;
	mTG_DemPhaHuy = 0.0f;
}

void DanLv3::DangTonTai()
{
	mHH_HienTai = mHH_DangTonTai;
	mHH_HienTai->Remake();
	mTrangThai = eTTDan_DangTonTai;
}

void DanLv3::Ban()
{
	mHH_HienTai = mHH_DangTanBien;
	mHH_HienTai->Remake();
	mTrangThai = eTTDan_BanRa;
	mTG_DemBanRa = 0.0f;
}
