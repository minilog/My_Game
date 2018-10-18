#pragma once

#include "ManGame.h"

class QuanLyManGame
{
private:
	QuanLyManGame();
public:
	static QuanLyManGame *qlmgTruongHop();
	void ThayTheManGame(ManGame *in_BanDo);

public:
	ManGame* mgManGameHienTai();

private:
	static QuanLyManGame *mTruongHop;
	ManGame *mManGameHienTai;
};

