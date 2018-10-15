#pragma once

#include "ManGame.h"

class QuanLyManGame
{
private:
	QuanLyManGame();
public:
	static QuanLyManGame *NhanTruongHop();
	ManGame* NhanManGameHienTai();
	void CapNhat(float in_tg);
	void ThayTheManGame(ManGame *in_BanDo);

private:
	static QuanLyManGame *mTruongHop;
	ManGame *mManGameHienTai;
};

