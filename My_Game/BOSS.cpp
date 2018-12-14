#include "BOSS.h"

BOSS::BOSS(const Vec2& in_ToaDo)
	:
	DoiTuong(in_ToaDo, Vec2(), 26, 46)
{
	mLoaiDoiTuong = eLDT_BOSS;
	LoadThongTinHoatHinh();
	XuatHien();
}

void BOSS::CapNhat(float in_tg, const DoiTuong * in_DoiTuong)
{
	HH_HienTai->CapNhat(in_tg);
	HH_CanhOng->CapNhat(in_tg);
	mToaDo.x += mVanToc.x * in_tg;
	mToaDo.y += mVanToc.y * in_tg;
	DEM += in_tg;
	if (mTrangThai == eTT_BOSS_XuatHien)
	{
		if (DEM > 1.2)
		{
			mVanToc.y = 0.0f;
			HH_HienTai = HH_ThaOng;
		}
		if (DEM > 2.05f)
		{
			HH_HienTai = HH_ChuanBiDamKim;
		}
		if (DEM > 3.0f)
		{
			HH_HienTai = HH_DamKim;
		}
		if (DEM > 3.5f)
		{
			DamKim(in_DoiTuong->get_ToaDo());
		}
	}
}

void BOSS::XuLyVaCham(const DoiTuong * in_DoiTuong)
{
}

void BOSS::Ve(const Vec2 & in_DoDoi)
{
	HH_CanhOng->Ve(DS_HinhAnh::get_TH()->BOSS, LatHinh, mToaDo + Vec2(0.0f, -29.0f), in_DoDoi);
	HH_HienTai->Ve(DS_HinhAnh::get_TH()->BOSS, LatHinh, mToaDo, in_DoDoi);
}


void BOSS::XuatHien()
{
	mTrangThai = eTT_BOSS_XuatHien;
	mToaDo.y = 1750.0f;
	HH_ChuanBiDamKim->Remake(1);
	HH_DamKim->Remake(1);
	HH_ThaOng->Remake(1);
	DEM = 0.0f;
	HH_HienTai = HH_Bay;
	mVanToc.y = 90.0f;
}

void BOSS::DamKim(const Vec2& DiemDen)
{
	mTrangThai = eTT_BOSS_DamKim;
	float DX = DiemDen.x - mToaDo.x;
	float DY = DiemDen.y - mToaDo.y;
	float K = sqrt((VanTocTiepCan * VanTocTiepCan) / (DX * DX + DY * DY));
	mVanToc = Vec2(DX * K, DY * K);
}

void BOSS::LoadThongTinHoatHinh()
{
	std::vector<ThongTinFrame> lDSTTFrame;

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(48, 52, HCN(6, 6 + 50, 10, 10 + 62), 0.1f)); // 1
	lDSTTFrame.push_back(ThongTinFrame(52, 58, HCN(263, 263 + 52, 4, 78),   0.1f)); // 2
	lDSTTFrame.push_back(ThongTinFrame(54, 58, HCN(320, 320 + 48, 4, 78),   0.1f)); // 3
	lDSTTFrame.push_back(ThongTinFrame(56, 56, HCN(377, 377 + 48, 4, 78),   0.1f)); // 4 
	lDSTTFrame.push_back(ThongTinFrame(52, 54, HCN(431, 431 + 46, 4, 78),   0.1f)); // 5
	lDSTTFrame.push_back(ThongTinFrame(54, 58, HCN(483, 483 + 46, 4, 78),   0.1f)); // 6
	lDSTTFrame.push_back(ThongTinFrame(54, 58, HCN(320, 320 + 48, 4, 78),   0.1f)); // 3
	lDSTTFrame.push_back(ThongTinFrame(52, 58, HCN(263, 263 + 52, 4, 78),   0.1f)); // 2
	lDSTTFrame.push_back(ThongTinFrame(48, 52, HCN(6, 6 + 50, 10, 10 + 62), 99.9f)); // 1
	HH_ThaOng = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(44 + 4, 52, HCN(6, 6 + 50, 10, 10 + 62), 0.15f)); // 1
	HH_Bay = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(44 + 4, 52, HCN(6, 6 + 50, 10, 10 + 62),     0.06f)); // 1
	lDSTTFrame.push_back(ThongTinFrame(40 + 4, 54, HCN(61,	61 + 44,  8, 8 + 60 ),  0.06f)); // 2
	lDSTTFrame.push_back(ThongTinFrame(38 + 4, 54, HCN(116, 116 + 38, 9, 9 + 58),   0.06f)); // 3
	lDSTTFrame.push_back(ThongTinFrame(40 + 4, 56, HCN(166, 166 + 40, 7, 7 + 54),   0.06f)); // 4
	lDSTTFrame.push_back(ThongTinFrame(40 + 4, 56, HCN(215, 215 + 40, 8, 8 + 54),   0.06f)); // 5
	lDSTTFrame.push_back(ThongTinFrame(40 + 4, 56, HCN(41, 41 + 40, 92, 92 + 54),   0.06f)); // 6
	lDSTTFrame.push_back(ThongTinFrame(40 + 4, 56, HCN(87, 87 + 40, 91, 91 + 58),   0.06f)); // 7
	lDSTTFrame.push_back(ThongTinFrame(40 + 4, 56, HCN(132, 132 + 40, 92, 92 + 58), 0.06f)); // 8 
	lDSTTFrame.push_back(ThongTinFrame(42 + 4, 56, HCN(177, 177 + 40, 93, 93 + 58), 0.06f)); // 9
	lDSTTFrame.push_back(ThongTinFrame(48 + 4, 56, HCN(222, 222 + 44, 93, 93 + 58), 0.06f)); // 10
	lDSTTFrame.push_back(ThongTinFrame(42 + 4, 56, HCN(272, 272 + 40, 94, 94 + 58), 0.06f)); // 11
	lDSTTFrame.push_back(ThongTinFrame(48 + 4, 56, HCN(315, 315 + 44, 94, 94 + 58), 0.06f)); // 12
	lDSTTFrame.push_back(ThongTinFrame(50 + 4, 56, HCN(364, 364 + 44, 94, 94 + 58), 0.06f)); // 13
	lDSTTFrame.push_back(ThongTinFrame(40 + 4, 56, HCN(87, 87 + 40, 91, 91 + 58), 99.9f)); // 7
	HH_ChuanBiDamKim = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(40 + 4, 56, HCN(87, 87 + 40, 91, 91 + 58), 1.5f)); // 7
	lDSTTFrame.push_back(ThongTinFrame(40 + 4, 56, HCN(41, 41 + 40, 92, 92 + 54), 0.06f)); // 6
	lDSTTFrame.push_back(ThongTinFrame(40 + 4, 56, HCN(215, 215 + 40, 8, 8 + 54), 0.06f)); // 5
	lDSTTFrame.push_back(ThongTinFrame(40 + 4, 56, HCN(166, 166 + 40, 7, 7 + 54), 0.06f)); // 4
	lDSTTFrame.push_back(ThongTinFrame(38 + 4, 54, HCN(116, 116 + 38, 9, 9 + 58), 0.06f)); // 3
	lDSTTFrame.push_back(ThongTinFrame(40 + 4, 54, HCN(61, 61 + 44, 8, 8 + 60),   0.06f)); // 2
	lDSTTFrame.push_back(ThongTinFrame(44 + 4, 52, HCN(6, 6 + 50, 10, 10 + 62),   99.9f)); // 1
	HH_DamKim = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(94, 6, HCN(417, 417 + 98, 171, 171 + 24),	0.032f));
	lDSTTFrame.push_back(ThongTinFrame(94, 42, HCN(417, 417 + 98, 203, 203 + 42),	0.032f));
	//lDSTTFrame.push_back(ThongTinFrame(48, 42, HCN(444, 444 + 48, 250, 250 + 42), 0.005f));
	//lDSTTFrame.push_back(ThongTinFrame(80, 42, HCN(426, 426 + 80, 203, 203 + 42), 0.018f));
	HH_CanhOng = new HoatHinh(lDSTTFrame);
}

BOSS::~BOSS()
{
}
