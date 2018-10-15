#pragma once

#include <d3dx9.h>
#include <d3d9.h>
#include <Windows.h>

class ToanCauGame
{
public:
	static void ThietLapTruongHopXuLy(HINSTANCE in_TruongHopXuLy)
	{
		mTruongHopXuLy = in_TruongHopXuLy;
	}
	static HINSTANCE NhanTruongHopXuLy()
	{
		return mTruongHopXuLy;
	}
	static void ThietLapCuaSoXuLy(HWND in_CuaSoXuLy)
	{
		mCuaSoXuLy = in_CuaSoXuLy;
	}
	static HWND NhanCuaSoXuLy()
	{
		return mCuaSoXuLy;
	}
	static void ThietLapXuLyHinhAnh(LPD3DXSPRITE in_XuLyHinhAnh)
	{
		mXuLyHinhAnh = in_XuLyHinhAnh;
	}
	static LPD3DXSPRITE NhanXuLyHinhAnh()
	{
		return mXuLyHinhAnh;
	}
	static void ThietLapThietBi(LPDIRECT3DDEVICE9 in_ThietBi)
	{
		mThietBi = in_ThietBi;
	}
	static LPDIRECT3DDEVICE9 NhanThietBi()
	{
		return mThietBi;
	}
	static void ThietLapChieuRong(int in_ChieuRong)
	{
		mChieuRong = in_ChieuRong;
	}
	static int NhanChieuRong()
	{
		return mChieuRong;
	}
	static void ThietLapChieuCao(int in_ChieuCao)
	{
		mChieuCao = in_ChieuCao;
	}
	static int NhanChieuCao()
	{
		return mChieuCao;
	}

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
