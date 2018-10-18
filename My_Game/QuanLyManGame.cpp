#include "QuanLyManGame.h"

QuanLyManGame* QuanLyManGame::mTruongHop = NULL;

QuanLyManGame::QuanLyManGame()
{
	mManGameHienTai = nullptr;
}

void QuanLyManGame::ThayTheManGame(ManGame * in_BanDo)
{
	delete mManGameHienTai;
	mManGameHienTai = in_BanDo;
}




















///////////////////////////////////////////////////////////////////////////////////
/*								 Các hàm đơn giản					             */
///////////////////////////////////////////////////////////////////////////////////

QuanLyManGame * QuanLyManGame::qlmgTruongHop()
{
	if (!mTruongHop)
	{
		mTruongHop = new QuanLyManGame();
	}
	return mTruongHop;
}

ManGame * QuanLyManGame::mgManGameHienTai()
{
	return mManGameHienTai;
}