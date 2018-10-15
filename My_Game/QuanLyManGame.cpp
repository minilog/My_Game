#include "QuanLyManGame.h"

QuanLyManGame* QuanLyManGame::mTruongHop = NULL;

QuanLyManGame::QuanLyManGame()
{
	mManGameHienTai = nullptr;
}

void QuanLyManGame::CapNhat(float in_tg)
{
	mManGameHienTai->CapNhat(in_tg);
}

void QuanLyManGame::ThayTheManGame(ManGame * in_BanDo)
{
	delete mManGameHienTai;
	mManGameHienTai = in_BanDo;
}




















///////////////////////////////////////////////////////////////////////////////////
/*								 Các hàm đơn giản					             */
///////////////////////////////////////////////////////////////////////////////////

QuanLyManGame * QuanLyManGame::NhanTruongHop()
{
	if (!mTruongHop)
	{
		mTruongHop = new QuanLyManGame();
	}
	return mTruongHop;
}

ManGame * QuanLyManGame::NhanManGameHienTai()
{
	return mManGameHienTai;
}