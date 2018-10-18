#pragma once

#include <d3dx9.h>
#include <d3d9.h>

class Camera
{
public:
	Camera(int in_ChieuRong, int in_ChieuCao);
	void ThietLapToaDo(D3DXVECTOR3 in_ViTri);
	void ThietLapToaDo(float in_X, float in_Y);

	D3DXVECTOR3 vToaDo();
	int iChieuRong();
	int iChieuCao();
	RECT rHCNGioiHan();

private:
	D3DXVECTOR3 mViTri; // chính giữa camera
	int mChieuRong;
	int mChieuCao;
};

