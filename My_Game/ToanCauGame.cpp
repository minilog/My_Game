#include "ToanCauGame.h"

HINSTANCE ToanCauGame::mTruongHopXuLy = NULL;
HWND ToanCauGame::mCuaSoXuLy = NULL;
LPD3DXSPRITE ToanCauGame::mXuLyHinhAnh = NULL;
LPDIRECT3DDEVICE9 ToanCauGame::mThietBi = NULL;
int ToanCauGame::mChieuRong = 600;
int ToanCauGame::mChieuCao = 600;
IDirect3DSurface9* ToanCauGame::mMatSau = nullptr;
bool ToanCauGame::mGameDangChay = true;




















///////////////////////////////////////////////////////////////////////////////////
/*								 Các hàm đơn giản					             */
///////////////////////////////////////////////////////////////////////////////////

void ToanCauGame::ThietLapTruongHopXuLy(HINSTANCE in_TruongHopXuLy)
{
	mTruongHopXuLy = in_TruongHopXuLy;
}

HINSTANCE ToanCauGame::hiTruongHopXuLy()
{
	return mTruongHopXuLy;
}

void ToanCauGame::ThietLapCuaSoXuLy(HWND in_CuaSoXuLy)
{
	mCuaSoXuLy = in_CuaSoXuLy;
}

HWND ToanCauGame::hwCuaSoXuLy()
{
	return mCuaSoXuLy;
}

void ToanCauGame::ThietLapXuLyHinhAnh(LPD3DXSPRITE in_XuLyHinhAnh)
{
	mXuLyHinhAnh = in_XuLyHinhAnh;
}

LPD3DXSPRITE ToanCauGame::sXuLyHinhAnh()
{
	return mXuLyHinhAnh;
}

void ToanCauGame::ThietLapThietBi(LPDIRECT3DDEVICE9 in_ThietBi)
{
	mThietBi = in_ThietBi;
}

LPDIRECT3DDEVICE9 ToanCauGame::ddThietBi()
{
	return mThietBi;
}

void ToanCauGame::ThietLapChieuRong(int in_ChieuRong)
{
	mChieuRong = in_ChieuRong;
}

int ToanCauGame::iChieuRong()
{
	return mChieuRong;
}

void ToanCauGame::ThietLapChieuCao(int in_ChieuCao)
{
	mChieuCao = in_ChieuCao;
}

int ToanCauGame::iChieuCao()
{
	return mChieuCao;
}
