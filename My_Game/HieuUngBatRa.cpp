#include "HieuUngBatRa.h"

HieuUngBatRa::HieuUngBatRa()
	:
	DoiTuong(Vec2(), Vec2(), 0, 0)
{
	std::vector<ThongTinFrame> lDSTTFrame;

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), -6, -2, 0.1f, HCN(126, 138, 607, 619)));
	mHoatHinh = new HoatHinh("Resources_X3/XMan/Z.png", lDSTTFrame, D3DCOLOR_XRGB(0, 128, 128));

	mTG_TonTai = 0.0f;
	for (int i = 0; i < (int)lDSTTFrame.size(); i++)
	{
		mTG_TonTai += lDSTTFrame[i].ThoiGian;
	}

	mBienMat = true;
	mTG_DemTonTai = 999.9f;
}

HieuUngBatRa::~HieuUngBatRa()
{
	if (mHoatHinh)
		delete mHoatHinh;
}

void HieuUngBatRa::CapNhat(float in_tg)
{
	if (!mBienMat)
	{
		mTG_DemTonTai += in_tg;
	}
	if (mTG_DemTonTai > mTG_TonTai && !mBienMat)
	{
		mBienMat = true;
	}
}

void HieuUngBatRa::Ve(const Vec2 & in_DoDoi)
{
	if (!mBienMat)
	{
		mHoatHinh->set_LatTheoChieuNgang(mLatHinh);
		mHoatHinh->set_ToaDo(mToaDo);
		mHoatHinh->set_DoDoi(in_DoDoi);
		mHoatHinh->Ve();
	}
}

void HieuUngBatRa::Remake()
{
	mTG_DemTonTai = 0.0f;
	mBienMat = false;
	mHoatHinh->Remake();
}
