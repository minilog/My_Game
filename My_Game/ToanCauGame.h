#pragma once

#include <d3dx9.h>
#include <d3d9.h>
#include <Windows.h>

class ToanCauGame
{
public:
	static void ThietLapTruongHopXuLy(HINSTANCE in_TruongHopXuLy);
	static void ThietLapCuaSoXuLy(HWND in_CuaSoXuLy);
	static void ThietLapThietBi(LPDIRECT3DDEVICE9 in_ThietBi);
	static void ThietLapXuLyHinhAnh(LPD3DXSPRITE in_XuLyHinhAnh);
	static void ThietLapChieuRong(int in_ChieuRong);
	static void ThietLapChieuCao(int in_ChieuCao);

public:
	static HINSTANCE hiTruongHopXuLy();
	static HWND hwCuaSoXuLy();
	static LPD3DXSPRITE sXuLyHinhAnh();
	static LPDIRECT3DDEVICE9 ddThietBi();
	static int iChieuRong();
	static int iChieuCao();

private:
	static HINSTANCE			mTruongHopXuLy;
	static HWND					mCuaSoXuLy;
	static LPDIRECT3DDEVICE9	mThietBi;
	static LPD3DXSPRITE			mXuLyHinhAnh;
	static int					mChieuRong;
	static int					mChieuCao;
public:
	static LPDIRECT3DSURFACE9	mMatSau;
	static bool					mGameDangChay;
};
