#include "Camera.h"

// bắt buộc cung cấp cho Compiler
D3DXVECTOR3 Camera::mToaDo = D3DXVECTOR3(); 
int Camera::mChieuRong = 0;
int Camera::mChieuCao = 0;

void Camera::CungCapDuLieu(D3DXVECTOR3 in_ToaDo, int in_ChieuRong, int in_ChieuCao)
{
	mToaDo = in_ToaDo;
	mChieuRong = in_ChieuRong;
	mChieuCao = in_ChieuCao;
}

void Camera::ThietLapToaDo(D3DXVECTOR3 in_ToaDo) {
	mToaDo = in_ToaDo;
}

RECT Camera::rHCNGioiHan()
{
	RECT lHCN;
	lHCN.left = int(mToaDo.x - mChieuRong / 2);
	lHCN.right = lHCN.left + mChieuRong;
	lHCN.top = int(mToaDo.y - mChieuCao / 2);
	lHCN.bottom = lHCN.top + mChieuCao;

	return lHCN;
}

int Camera::iChieuRong()
{
	return mChieuRong;
}

int Camera::iChieuCao()
{
	return mChieuCao;
}

D3DXVECTOR3 Camera::vToaDo()
{
	return mToaDo;
}
