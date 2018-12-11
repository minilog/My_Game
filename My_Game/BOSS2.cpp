#include "BOSS2.h"



BOSS2::BOSS2(const Vec2& in_ToaDo)
	:
	DoiTuong(in_ToaDo, Vec2(), 0, 0)
{
	mLoaiDoiTuong = eLDT_BOSS2;

	LoadThongTinHoatHinh();
}


void BOSS2::CapNhat(float in_tg, const DoiTuong * in_DoiTuong)
{
}

void BOSS2::XuLyVaCham(const DoiTuong * in_DoiTuong)
{
}

void BOSS2::Ve(const Vec2 & in_DoDoi)
{
	HH_BOSS->Ve(DS_HinhAnh::get_TH()->BOSS2_png, false, mToaDo, in_DoDoi);
}

void BOSS2::LoadThongTinHoatHinh()
{
	std::vector<ThongTinFrame> lDSTTFrame;

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(256, 88, HCN(0, 256, 0, 88)));
	HH_BOSS = new HoatHinh(lDSTTFrame);
}

BOSS2::~BOSS2()
{
}
