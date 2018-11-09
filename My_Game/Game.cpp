#include "Game.h"
#include "ToanCauGame.h"
#include "ThoiGianGame.h"
#include "QuanLyManGame.h"
#include "ManGioiThieu.h"

Game::Game(int in_FPS)
{
	mFPS = in_FPS;

	QuanLyManGame::set_ManGame(new ManGioiThieu());

	TaoVongLapGame();

}

void Game::TaoVongLapGame()
{
	MSG lMessage;
	float lThoiGianThayDoi = float(1.0f / mFPS), lThoiGian = 0;

	while (ToanCauGame::mGameDangChay)
	{
		ThoiGianGame::get_TruongHop()->BatDauDem();

		if (PeekMessage(&lMessage, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&lMessage);
			DispatchMessage(&lMessage);
		}

		lThoiGian += ThoiGianGame::get_TruongHop()->get_ThoiGianDemDuoc();

		if (lThoiGian >= lThoiGianThayDoi)
		{
			CapNhat((lThoiGian));
			lThoiGian -= lThoiGianThayDoi;
		}
		else
		{
			Sleep(DWORD(lThoiGianThayDoi - lThoiGian));
			lThoiGian = lThoiGianThayDoi;
		}
	}
}

void Game::CapNhat(float in_tg)
{
	QuanLyManGame::get_ManGame()->CapNhat(in_tg);

	Ve();
}

void Game::Ve()
{
	auto lThietBi = ToanCauGame::get_ThietBi();
	lThietBi->Clear(0, NULL, D3DCLEAR_TARGET, QuanLyManGame::get_ManGame()->cMauNen(), 0.0f, 0);

	{
		lThietBi->BeginScene();

		// bắt đầu vẽ
		ToanCauGame::get_XuLyHinhAnh()->Begin(D3DXSPRITE_ALPHABLEND);

		// vẽ ở đây
		QuanLyManGame::get_ManGame()->Ve();	

		// kết thúc vẽ
		ToanCauGame::get_XuLyHinhAnh()->End();

		lThietBi->EndScene();
	}

	lThietBi->Present(0, 0, 0, 0);
}
