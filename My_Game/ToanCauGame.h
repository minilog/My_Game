#pragma once

#include <d3dx9.h>
#include <d3d9.h>
#include <Windows.h>

class ToanCauGame
{
public:
	static void ThietLapTruongHopXuLy(HINSTANCE in_TruongHopXuLy);
	static HINSTANCE NhanTruongHopXuLy();
	static void ThietLapCuaSoXuLy(HWND in_CuaSoXuLy);
	static HWND NhanCuaSoXuLy();
	static void ThietLapXuLyHinhAnh(LPD3DXSPRITE in_XuLyHinhAnh);
	static LPD3DXSPRITE NhanXuLyHinhAnh();
	static void ThietLapThietBi(LPDIRECT3DDEVICE9 in_ThietBi);
	static LPDIRECT3DDEVICE9 NhanThietBi();
	static void ThietLapChieuRong(int in_ChieuRong);
	static int NhanChieuRong();
	static void ThietLapChieuCao(int in_ChieuCao);
	static int NhanChieuCao();

private:
	static HINSTANCE			mTruongHopXuLy;
	static HWND					mCuaSoXuLy;
	static LPD3DXSPRITE			mXuLyHinhAnh;
	static LPDIRECT3DDEVICE9	mThietBi;
	static int					mChieuRong;
	static int					mChieuCao;
public:
	static LPDIRECT3DSURFACE9	mMatSau;
	static bool					mLaGameDangChay;
};
