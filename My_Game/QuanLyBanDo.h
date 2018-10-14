#pragma once

#include "BanDo.h"

class QuanLyBanDo
{
private:
	QuanLyBanDo()
	{
		mBanDoHienTai = nullptr;
	}
public:
	static QuanLyBanDo *NhanTruongHop()
	{
		if (!mTruongHop)
		{
			mTruongHop = new QuanLyBanDo();
		}
		return mTruongHop;
	}
	BanDo* NhanBanDoHienTai()
	{
		return mBanDoHienTai;
	}
	void CapNhat(float in_tg)
	{
		mBanDoHienTai->CapNhat(in_tg);
	}
	void ThayTheBanDo(BanDo *in_BanDo)
	{
		delete mBanDoHienTai;
		mBanDoHienTai = in_BanDo;
	}

private:
	static QuanLyBanDo *mTruongHop;
	BanDo *mBanDoHienTai;
};

