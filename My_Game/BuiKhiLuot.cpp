#include "BuiKhiLuot.h"

BuiKhiLuot::BuiKhiLuot(const Vec2 & in_ToaDo)
	:
	DoiTuong(in_ToaDo, Vec2(0.0f, -35.0f), 0, 0)
{
	std::vector<ThongTinFrame> lDSTTFrame;

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 8, 8, 0.08f, HCN(30, 38, 609, 617)));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 10, 11, 0.08f, HCN(40, 50, 610, 621)));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 13, 13, 0.08f, HCN(53, 66, 610, 623)));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 14, 14, 0.08f, HCN(71, 85, 609, 623)));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 14, 14, 0.08f, HCN(88, 102, 609, 623)));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 14, 14, 0.08f, HCN(106, 120, 609, 623)));
	mHoatHinh = new HoatHinh("Resources_X3/XMan/Z.png", lDSTTFrame, D3DCOLOR_XRGB(0, 128, 128));

	mTG_TonTai = 0.0f;
	for (int i = 0; i < (int)lDSTTFrame.size(); i++)
	{
		mTG_TonTai += lDSTTFrame[i].ThoiGian;
	}

	mBienMat = true;
	mTG_DemTonTai = 999.9f;
}

BuiKhiLuot::~BuiKhiLuot()
{
	delete mHoatHinh;
}

void BuiKhiLuot::CapNhat(float in_tg)
{
	if (mBienMat)
	{
		return;
	}
	if (!mBienMat)
	{
		mTG_DemTonTai += in_tg;
		mHoatHinh->CapNhat(in_tg);
		mToaDo.x += mVanToc.x * in_tg;
		mToaDo.y += mVanToc.y * in_tg;
	}
	if (mTG_DemTonTai > mTG_TonTai && !mBienMat)
	{
		mBienMat = true;
	}
}

void BuiKhiLuot::Ve(const Vec2 & in_DoDoi)
{
	if (!mBienMat)
	{
		mHoatHinh->set_ToaDo(mToaDo);
		mHoatHinh->set_DoDoi(in_DoDoi);
		mHoatHinh->Ve();
	}
}

void BuiKhiLuot::Remake()
{
	mTG_DemTonTai = 0.0f;
	mBienMat = false;
	mHoatHinh->Remake();
}
