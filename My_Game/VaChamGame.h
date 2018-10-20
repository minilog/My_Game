#pragma once

#include <d3dx9.h>
#include <d3d9.h>
#include "DoiTuong.h"
#include "KieuDuLieuEnum.h"

class VaChamGame
{
public:
	static eKetQuaVaCham kqvcHCNVaHCN(RECT in_HCN1, RECT in_HCN2);
	static ePhiaVaCham pvcPhiaVaCham(const DoiTuong *in_DoiTuong, eKetQuaVaCham in_KetQuaVaCham);
	// nếu Rectangle quá to thì va chạm có thể bị sai
	static ePhiaVaCham pvcPhiaVaCham(const DoiTuong *in_DoiTuong1, const DoiTuong *in_DoiTuong2);

	static bool bDaVaCham(RECT in_HCN1, RECT in_HCN2);
	static bool bDiemVaHCN(float in_X, float in_Y, RECT in_HCN);
	static bool bHCNVaHinhTron(RECT in_HCN, int in_TamX, int in_TamY, int in_BanKinh);
};

