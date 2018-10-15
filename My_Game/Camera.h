#pragma once

#include <d3dx9.h>
#include <d3d9.h>

class Camera
{
public:
	Camera(int in_ChieuRong, int in_ChieuCao);
	void ThietLapViTri(D3DXVECTOR3 in_ViTri);
	void ThietLapViTri(float in_X, float in_Y);
	int NhanChieuRong();
	int NhanChieuCao();
	D3DXVECTOR3 NhanViTri();
	RECT NhanGioiHanHCN();

private:
	int mChieuRong;
	int mChieuCao;
	D3DXVECTOR3 mViTri; // chính giữa camera
};

