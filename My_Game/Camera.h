#pragma once

#include <d3dx9.h>
#include <d3d9.h>

class Camera
{
public:
	Camera(int in_ChieuRong, int in_ChieuCao);
	void ThietLapToaDo(const D3DXVECTOR3& in_ToaDo);

	D3DXVECTOR3 vToaDo() const;
	int iChieuRong() const;
	int iChieuCao() const;
	RECT rHCNGioiHan() const;

private:
	D3DXVECTOR3 mToaDo; // chính giữa camera
	int mChieuRong;
	int mChieuCao;
};

