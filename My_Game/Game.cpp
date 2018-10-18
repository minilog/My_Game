//bắt đầu từ Game -> Màn Game -> Bản Đồ Game
//bắt đầu từ Game -> Màn Game -> Người Chơi
#include "Game.h"
#include "ToanCauGame.h"
#include "ThoiGianGame.h"

Game::Game(int in_FPS)
{
	mFPS = in_FPS;
	//SceneManager::GetInstance()->ReplaceScene(new DemoScene());
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

void Game::CapNhat(float dt)
{
	//SceneManager::GetInstance()->GetCurrentScene()->Update(dt);

	Ve();
}

void Game::Ve()
{
	auto lThietBi = ToanCauGame::ddThietBi();
	//auto scene = SceneManager::GetInstance()->GetCurrentScene();
	lThietBi->Clear(0, NULL, D3DCLEAR_TARGET, /*scene->GetBackcolor()*/ NULL, 0.0f, 0);

	{
		lThietBi->BeginScene();

		// bắt đầu vẽ
		ToanCauGame::sXuLyHinhAnh()->Begin(D3DXSPRITE_ALPHABLEND);

		// vẽ ở đây
		//scene->Draw();

		// kết thúc vẽ
		ToanCauGame::sXuLyHinhAnh()->End();

		lThietBi->EndScene();
	}

	lThietBi->Present(0, 0, 0, 0);
}
