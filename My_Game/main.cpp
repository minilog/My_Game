#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>
#include <iostream>
#include <sstream>
#include <dinput.h>
#include <windowsx.h>
#include "ToanCauGame.h"
#include "ThoiGianGame.h"
#include "QuanLyManGame.h"
#include "Game.h"

using namespace std;

#define WIN_NAME L"Ten Game DirectX"
#define WIN_TITLE L"Title Cua Game DrectX"
#define FPS 60

//////////////////////////////////
/*								*/
//////////////////////////////////

int KhoiTaoCuaSo(int cmdShow);
int KhoiTaoThietBi();
LRESULT CALLBACK ThuTucCuaSo(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

LPD3DXSPRITE		mXuLyHinhAnh;
PDIRECT3D9			mD3d;
LPDIRECT3DDEVICE9	mThietBi;
HINSTANCE			mTruongHopXuLy;

// Ham Main bat dau
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int cmdShow)
{
	mTruongHopXuLy = hInstance;
	KhoiTaoCuaSo(cmdShow);
	return 0;
}

int	KhoiTaoCuaSo(int cmdShow)
{
	WNDCLASSEX lopCuaSo;
	lopCuaSo.cbSize = sizeof(WNDCLASSEX);
	lopCuaSo.style = CS_HREDRAW | CS_VREDRAW;
	lopCuaSo.hInstance = mTruongHopXuLy;
	lopCuaSo.lpfnWndProc = (WNDPROC)ThuTucCuaSo;
	lopCuaSo.cbClsExtra = 0;
	lopCuaSo.cbWndExtra = 0;
	lopCuaSo.hIcon = NULL;
	lopCuaSo.hCursor = LoadCursor(NULL, IDC_ARROW);
	lopCuaSo.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	lopCuaSo.lpszMenuName = NULL;
	lopCuaSo.lpszClassName = WIN_NAME;
	lopCuaSo.hIconSm = NULL;
	RegisterClassEx(&lopCuaSo);

	//WS_OVERLAPPEDWINDOW <=> WS_EX_TOPMOST | WS_POPUP | WS_VISIBLE
	HWND cuaSoXuLy = CreateWindow(
		WIN_NAME,
		WIN_TITLE,
		WS_OVERLAPPEDWINDOW,
		300,
		100,
		ToanCauGame::get_ChieuRong(),
		ToanCauGame::get_ChieuCao(),
		NULL,
		NULL,
		mTruongHopXuLy,
		NULL);

	ToanCauGame::set_TruongHopXuLy(mTruongHopXuLy);
	ToanCauGame::set_CuaSoXuLy(cuaSoXuLy);

	ShowWindow(cuaSoXuLy, cmdShow);
	UpdateWindow(cuaSoXuLy);

	if (KhoiTaoThietBi())
	{
		Game *game = new Game(FPS);
	}

	return 0;
}

int KhoiTaoThietBi()
{
	mD3d = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = ToanCauGame::get_ChieuRong();
	d3dpp.BackBufferHeight = ToanCauGame::get_ChieuCao();

	HRESULT dvresult = mD3d->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		ToanCauGame::get_CuaSoXuLy(),
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&mThietBi);

	ToanCauGame::set_ThietBi(mThietBi);

	D3DXCreateSprite(ToanCauGame::get_ThietBi(), &mXuLyHinhAnh);

	ToanCauGame::set_XuLyHinhAnh(mXuLyHinhAnh);

	return 1;
}

LRESULT CALLBACK ThuTucCuaSo(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	/*
	su dung cac event cua window
	*/
	switch (message)
	{
	case WM_DESTROY:
		ToanCauGame::mGameDangChay = false;
		PostQuitMessage(0);
		break;

	case WM_LBUTTONDOWN:
		QuanLyManGame::get_ManGame()->OnMouseDown((float)GET_X_LPARAM(lParam),
			(float)GET_Y_LPARAM(lParam));
		break;

	case WM_KEYDOWN:
		QuanLyManGame::get_ManGame()->OnKeyDown(wParam);
		break;

	case WM_KEYUP:
		QuanLyManGame::get_ManGame()->OnKeyUp(wParam);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}