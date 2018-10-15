#pragma once

#include <d3dx9.h>
#include <d3d9.h>

class Camera
{
public:
	Camera(int in_ChieuRong, int in_ChieuCao)
	{
		mChieuRong = in_ChieuRong;
		mChieuCao = in_ChieuCao;
		mViTri = D3DXVECTOR3(0, 0, 0);
	}
	void ThietLapViTri(D3DXVECTOR3 in_ViTri)
	{
		mViTri = in_ViTri;
	}
	void ThietLapViTri(float in_X, float in_Y)
	{
		ThietLapViTri(D3DXVECTOR3(in_X, in_Y, 0));
	}
	int NhanChieuRong()
	{
		return mChieuRong;
	}
	int NhanChieuCao()
	{
		return mChieuCao;
	}
	D3DXVECTOR3 NhanViTri()
	{
		return mViTri;
	}
	RECT NhanGioiHanHCN();

private:
	int mChieuRong;
	int mChieuCao;
	D3DXVECTOR3 mViTri; // chính giữa camera
};

