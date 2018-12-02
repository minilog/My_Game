#include "DanNo1.h"

void DanNo1::LoadHinhAnhVao()
{
	std::vector<ThongTinFrame> lDSTTFrame;

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 8, 8, 99.9f, HCN(0, 8, 0, 8)));
	mHH_Dan = new HoatHinh("Resources_X3/Enemies/DanNo1.png", lDSTTFrame, D3DCOLOR_XRGB(255, 0, 255));

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 16, 24, 0.08f, HCN(1 - 1, 1 + 16 - 1, 56 - 43, 56 + 16 - 43)));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 32, 40, 0.08f, HCN(26 - 1, 26 + 32 - 1, 48 - 43, 48 + 32 - 43)));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 28, 36, 0.08f, HCN(66 - 1, 66 + 28 - 1, 51 - 43, 51 + 24 - 43)));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 30, 40, 0.08f, HCN(103 - 1, 103 + 30 - 1, 47 - 43, 47 + 28 - 43)));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 32, 36, 0.08f, HCN(143 - 1, 143 + 32 - 1, 43 - 43, 43 + 28 - 43)));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 32, 38, 0.08f, HCN(187 - 1, 187 + 32 - 1, 53 - 43, 53 + 30 - 43)));
	mHH_HieuUngNoTung = new HoatHinh("Resources_X3/Enemies/NoTung.png", lDSTTFrame);
}
