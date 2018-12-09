#include "BOSS1.h"

BOSS1::BOSS1(const Vec2& in_ToaDo)
	:
	DoiTuong(in_ToaDo, Vec2(), 46, 46)
{
	mLoaiDoiTuong = eLDT_BOSS1;

	LoadThongTinHoatHinh();

}

void BOSS1::CapNhat(float in_tg, const DoiTuong * in_DoiTuong)
{
}

void BOSS1::XuLyVaCham(const DoiTuong * in_DoiTuong)
{
}

void BOSS1::Ve(const Vec2 & in_DoDoi)
{
}

void BOSS1::LoadThongTinHoatHinh()
{
	std::vector<ThongTinFrame> lDSTTFrame;

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(22, 22, HCN(246, 246 + 22, 10, 10 + 22), 0.25f));
	lDSTTFrame.push_back(ThongTinFrame(22, 22, HCN(126, 126 + 22, 10, 10 + 22), 0.25f));
	lDSTTFrame.push_back(ThongTinFrame(22, 22, HCN(166, 166 + 22, 10 , 10 + 22), 0.25f));
	lDSTTFrame.push_back(ThongTinFrame(22, 22, HCN(206, 206	 + 22, 10 , 10 + 22), 0.25f));
	HH_ConPet = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(32, 48, HCN(281, 281 + 32, 10, 10 + 48), 0.25f));
	HH_AnhSang = new HoatHinh(lDSTTFrame);
}

BOSS1::~BOSS1()
{
}
