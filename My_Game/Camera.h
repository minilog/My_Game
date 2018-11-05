#pragma once

#include <d3dx9.h>
#include <d3d9.h>

class Camera
{
public:
	static void CungCapDuLieu(D3DXVECTOR3 in_ToaDo, int in_ChieuRong, int in_ChieuCao);
	static void ThietLapToaDo(D3DXVECTOR3 in_ToaDo);

	static D3DXVECTOR3 vToaDo();
	static int iChieuRong();
	static int iChieuCao();
	static RECT rHCNGioiHan();

private:
	static D3DXVECTOR3 mToaDo; // chính giữa camera
	static int mChieuRong;
	static int mChieuCao;
};

