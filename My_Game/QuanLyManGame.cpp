#include "QuanLyManGame.h"

ManGame* QuanLyManGame::mManGameHienTai = nullptr;

void QuanLyManGame::ThayTheManGame(ManGame * in_BanDo)
{
	delete mManGameHienTai;
	mManGameHienTai = in_BanDo;
}




















///////////////////////////////////////////////////////////////////////////////////
/*								 Các hàm đơn giản					             */
///////////////////////////////////////////////////////////////////////////////////


ManGame * QuanLyManGame::mgManGameHienTai()
{
	return mManGameHienTai;
}