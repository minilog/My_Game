#pragma once

#include <d3dx9.h>
#include <d3d9.h>

class Camera
{
public:
	Camera(int in_ChieuRong, int in_ChieuCao);
	void ThietLapToaDo(D3DXVECTOR3 in_ViTri);
	void ThietLapToaDo(float in_X, float in_Y);
	int iChieuRong();
	int iChieuCao();
	D3DXVECTOR3 vViTri();
	RECT rHCNGioiHan();

private:
	int mChieuRong;
	int mChieuCao;
	D3DXVECTOR3 mViTri; // chính giữa camera
};

