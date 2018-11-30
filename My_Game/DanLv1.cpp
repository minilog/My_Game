#include "DanLv1.h"

DanLv1::DanLv1(const Vec2 & in_ToaDo, const Vec2 & in_VanToc)
	:
	DanLv(in_ToaDo, in_VanToc, 6, 4)
{
	mLoaiDoiTuong = eLDT_DanLv1;

	LoadHinhAnhVao();

	mHH_HienTai = mHH_DangTonTai;
	mTrangThai = eTTDan_DaBiPhaHuy;
}

DanLv1::~DanLv1()
{
	if (mHH_DangTonTai)
		delete mHH_DangTonTai;
	if (mHH_DangTanBien)
		delete mHH_DangTanBien;
}

void DanLv1::CapNhat(float in_tg)
{
	if (mTrangThai == eTTDan_DaBiPhaHuy)
	{
		return;
	}

	if (mTrangThai == eTTDan_DangTonTai)
	{
		mToaDo.x += mVanToc.x * in_tg;
		mToaDo.y += mVanToc.y * in_tg;
	}

	if (mTrangThai == eTTDan_DangTanBien)
	{
		mHH_HienTai->CapNhat(in_tg);
		mTG_DemPhaHuy += in_tg;

		if (mTG_DemPhaHuy > mTG_PhaHuy)
		{
			mTrangThai = eTTDan_DaBiPhaHuy;
		}
	}

	if (!VaChamGame::get_DaVaCham(get_HCNGioiHan(), Camera::get_HCNGioiHan()))
	{
		mTrangThai = eTTDan_DaBiPhaHuy;
	}
}

void DanLv1::Ve(const Vec2 & in_DoDoi)
{
	if (mTrangThai != eTTDan_DaBiPhaHuy)
	{
		mHH_HienTai->set_ToaDo(mToaDo);
		mHH_HienTai->set_DoDoi(in_DoDoi);
		mHH_HienTai->Ve();
	}
}

// Độ dời phụ thuộc Camera hiện tại

void DanLv1::XuLyVaCham(const DoiTuong * in_DoiTuong)
{
	if (mTrangThai == eTTDan_DangTonTai)
	{
		if (in_DoiTuong->get_LoaiDoiTuong() == eLDT_DoiTuongTinh)
		{
			eKetQuaVaCham lKQVC = VaChamGame::get_KetQuaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan());

			if (lKQVC.eKQVC_DaVaCham)
			{
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
}

void DanLv1::LoadHinhAnhVao()
{
	std::vector<ThongTinFrame> lDSTTFrame;

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 8, 6, 999.9f, HCN(113, 121, 535, 541)));
	mHH_DangTonTai = new HoatHinh("Resources_X3/XMan/Weapons and Items.png", lDSTTFrame, D3DCOLOR_XRGB(50, 96, 166));

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 12, 12, 0.07f, HCN(127, 139, 532, 544)));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 14, 14, 0.07f, HCN(144, 157, 531, 544)));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 16, 16, 0.07f, HCN(162, 178, 530, 545)));
	mHH_DangTanBien = new HoatHinh("Resources_X3/XMan/Weapons and Items.png", lDSTTFrame, D3DCOLOR_XRGB(50, 96, 166));

	mTG_PhaHuy = 0.0f;
	for (int i = 0; i < (int)lDSTTFrame.size(); i++)
	{
		mTG_PhaHuy += lDSTTFrame[i].ThoiGian;
	}
}

void DanLv1::DangTanBien()
{
	mTG_DemPhaHuy = 0.0f;
	mTrangThai = eTTDan_DangTanBien;
	mHH_HienTai = mHH_DangTanBien;
	mHH_HienTai->Remake();
}

void DanLv1::DangTonTai()
{
	mTrangThai = eTTDan_DangTonTai;
	mHH_HienTai = mHH_DangTonTai;
	mHH_HienTai->Remake();
}
