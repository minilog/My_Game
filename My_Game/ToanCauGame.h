#pragma once
#ifndef __Toan_Cau_Game__
#define __Toan_Cau_Game__

#include <d3dx9.h>
#include <d3d9.h>
#include <Windows.h>

class ToanCauGame
{
public:
	ToanCauGame() = default;
	static void ThietLapTruongHopXuLy(HINSTANCE in_TruongHopXuLy)
	{
		mTruongHopXuLy = in_TruongHopXuLy;
	}
	static HINSTANCE NhanTruongHopXuLy()
	{
		return mTruongHopXuLy;
	}
	static void ThietLapCuaSo(HWND in_CuaSo)
	{
		mCuaSo = in_CuaSo;
	}
	static HWND NhanCuaSo()
	{
		return mCuaSo;
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
	static HINSTANCE mTruongHopXuLy;
	static HWND mCuaSo;
	static LPD3DXSPRITE mXuLyHinhAnh;
	static LPDIRECT3DDEVICE9 mThietBi;
	static int mChieuRong, mChieuCao;
public:
	static LPDIRECT3DSURFACE9 matSau;
	static bool gameDangChay;
};

#endif