#pragma once

#include "ManGame.h"

class QuanLyManGame
{
private:
	QuanLyManGame()
	{
		mManGameHienTai = nullptr;
	}
public:
	static QuanLyManGame *NhanTruongHop()
	{
		if (!mTruongHop)
		{
			mTruongHop = new QuanLyManGame();
		}
		return mTruongHop;
	}
	ManGame* NhanManGameHienTai()
	{
		return mManGameHienTai;
	}
	void CapNhat(float in_tg)
	{
		mManGameHienTai->CapNhat(in_tg);
	}
	void ThayTheManGame(ManGame *in_BanDo)
	{
		delete mManGameHienTai;
		mManGameHienTai = in_BanDo;
	}

private:
	static QuanLyManGame *mTruongHop;
	ManGame *mManGameHienTai;
};

