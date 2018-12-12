#include "BOSS2.h"



BOSS2::BOSS2(const Vec2& in_ToaDo)
	:
	DoiTuong(in_ToaDo, Vec2(), 0, 0)
{
	mLoaiDoiTuong = eLDT_BOSS2;

	LoadThongTinHoatHinh();

	XuatHien();
}


void BOSS2::CapNhat(float in_tg, const DoiTuong * in_DoiTuong)
{
	if (mTrangThai == eTT_BOSS2_BienMat)
	{
		return;
	}

	DEM += in_tg;


	switch (mTrangThai)
	{
	case eTT_BOSS2_XuatHien:
		CapNhat_XuatHien(in_tg);
		break;

	case eTT_BOSS2_BocVac:
		if (DEM > 1.0f)
		{
	
		}

		break;

	case eTT_BOSS2_BoChay:
		CapNhat_BoChay(in_tg);
		break;

	default:
		break;
	}


}

void BOSS2::XuLyVaCham(const DoiTuong * in_DoiTuong)
{
}

void BOSS2::Ve(const Vec2 & in_DoDoi)
{
	//if (mTrangThai == eTT_BOSS2_BienMat)
	//{
	//	return;
	//}

	HH_2->Ve(DS_HinhAnh::get_TH()->BOSS2_png, false, ToaDo_HH2, in_DoDoi);
	HH_1->Ve(DS_HinhAnh::get_TH()->BOSS2_png, false, ToaDo_HH1, in_DoDoi);
}

void BOSS2::XuatHien()
{
	DEM = 0.0f;
	mTrangThai = eTT_BOSS2_XuatHien;
	mVanToc.y = 40.0f;
	ToaDo_HH1 = mToaDo;
	ToaDo_HH2 = mToaDo + Vec2(56.0f, -10.0f);
}

void BOSS2::BocVac()
{
	DEM = 0.0f;
	mTrangThai = eTT_BOSS2_BocVac;
	mVanToc.y = 0.0f;
}

void BOSS2::BoChay()
{
	DEM = 0.0f;
	mTrangThai = eTT_BOSS2_BoChay;
	mVanToc.y = -40.0f;
}

void BOSS2::BienMat()
{
	DEM = 0.0f;
	mTrangThai = eTT_BOSS2_BienMat;
	mVanToc.y = 0.0f;
}

void BOSS2::CapNhat_XuatHien(float in_tg)
{
	if (DEM < TG_XuatHien / 2.0f)
	{
		ToaDo_HH1.y += mVanToc.y * in_tg;
	}
	ToaDo_HH2.y += mVanToc.y * in_tg;
	if (DEM > TG_XuatHien)
	{
		BocVac();
	}
}

void BOSS2::CapNhat_BoChay(float in_tg)
{
	if (DEM >= TG_BoChay / 2.0f + 0.05f)
	{
		ToaDo_HH1.y += mVanToc.y *in_tg;
	}
	ToaDo_HH2.y += mVanToc.y * in_tg;
	if (DEM > TG_BoChay)
	{
		XuatHien();
	}
}

void BOSS2::LoadThongTinHoatHinh()
{
	std::vector<ThongTinFrame> lDSTTFrame;

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(256, 88, HCN(0, 256, 0, 88)));
	HH_1 = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(144, 108, HCN(112, 112 + 144, 89, 89 + 108)));
	HH_2 = new HoatHinh(lDSTTFrame);
}

BOSS2::~BOSS2()
{
}
