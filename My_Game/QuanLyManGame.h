#pragma once

#include "ManGame.h"

class QuanLyManGame
{
private:
	QuanLyManGame();
public:
	static QuanLyManGame *NhanTruongHop();
	void CapNhat(float in_tg);
	void ThayTheManGame(ManGame *in_BanDo);

public:
	ManGame* NhanManGameHienTai();

private:
	static QuanLyManGame *mTruongHop;
	ManGame *mManGameHienTai;
};

