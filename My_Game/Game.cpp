﻿//bắt đầu từ Game -> Màn Game -> Bản Đồ Game
//bắt đầu từ Game -> Màn Game -> Người Chơi
#include "Game.h"
#include "ToanCauGame.h"
#include "ThoiGianGame.h"
#include "QuanLyManGame.h"
#include "ManGioiThieu.h"

Game::Game(int in_FPS)
{
	mFPS = in_FPS;
	//QuanLyManGame::qlmgTruongHop()->ThayTheManGame(new ManGioiThieu());
	mHoatHinh = new HoatHinh("Resources/Zero.png", 15, 10, 1, 1.0f);
	mHoatHinh->ThietLapToaDo(D3DXVECTOR3(300, 300, 0));
	TaoVongLapGame();
}

void Game::TaoVongLapGame()
{
	MSG lMessage;
	float lThoiGianThayDoi = float(1.0f / mFPS), lThoiGian = 0;

	while (ToanCauGame::mGameDangChay)
	{
		ThoiGianGame::tggTruongHop()->BatDauDem();

		if (PeekMessage(&lMessage, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&lMessage);
			DispatchMessage(&lMessage);
		}

		lThoiGian += ThoiGianGame::tggTruongHop()->fThoiGianDemDuoc();

		if (lThoiGian >= lThoiGianThayDoi)
		{
			CapNhat((lThoiGian));
			lThoiGian = 0;
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
	mHoatHinh->CapNhat(in_tg);

	Ve();
}

void Game::Ve()
{
	auto lThietBi = ToanCauGame::ddThietBi();
	//auto lManGame = QuanLyManGame::qlmgTruongHop()->mgManGameHienTai();
	lThietBi->Clear(0, NULL, D3DCLEAR_TARGET, /*lManGame->cMauNen()*/D3DCOLOR_XRGB(255, 255, 255), 0.0f, 0);

	{
		lThietBi->BeginScene();

		// bắt đầu vẽ
		ToanCauGame::sXuLyHinhAnh()->Begin(D3DXSPRITE_ALPHABLEND);

		// vẽ ở đây
		mHoatHinh->Ve();
		//lManGame->Ve();

		// kết thúc vẽ
		ToanCauGame::sXuLyHinhAnh()->End();

		lThietBi->EndScene();
	}

	lThietBi->Present(0, 0, 0, 0);
}
