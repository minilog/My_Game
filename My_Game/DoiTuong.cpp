#include "DoiTuong.h"

void DoiTuong::ThietLapToaDo(D3DXVECTOR3 in_ToaDo)
{
	mToaDo = in_ToaDo;
}

void DoiTuong::ThietLapVanToc(D3DXVECTOR3 in_VanToc)
{
	mVanToc = in_VanToc;
}

void DoiTuong::ThietLapChieuRong(int in_ChieuRong)
{
	mChieuRong = in_ChieuRong;
}

void DoiTuong::ThietLapChieuCao(int in_ChieuCao)
{
	mChieuCao = in_ChieuCao;
}

D3DXVECTOR3 DoiTuong::vToaDo() const
{
	return mToaDo;
}

D3DXVECTOR3 DoiTuong::vVanToc() const
{
	return mVanToc;
}

int DoiTuong::iChieuRong() const
{
	return mChieuRong;
}

int DoiTuong::iChieuCao() const
{
	return mChieuCao;
}

RECT DoiTuong::rHCNGioiHan() const
{
	RECT lHCN;
	lHCN.left = int(mToaDo.x - mChieuRong / 2.0f);
	lHCN.right = int(mToaDo.x + mChieuRong / 2.0f);
	lHCN.top = int(mToaDo.y - mChieuCao / 2.0f);
	lHCN.bottom = int(mToaDo.y + mChieuCao / 2.0f);

	return lHCN;
}
