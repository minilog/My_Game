#pragma once

#include "ManGame.h"

class QuanLyManGame
{
public:
	static void ThayTheManGame(ManGame *in_BanDo);
	static ManGame* mgManGameHienTai();

private:
	static ManGame *mManGameHienTai;
};

