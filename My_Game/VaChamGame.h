#pragma once

#include <d3dx9.h>
#include <d3d9.h>
#include "ThucThe.h"
#include "KieuDuLieuEnum.h"

class VaChamGame
{
public:
	static eKetQuaVaCham kqvcHCNVaHCN(RECT in_HCN1, RECT in_HCN2);
	static ePhiaVaCham pvcPhiaVaCham(ThucThe *in_ThucThe1, eKetQuaVaCham in_KetQuaVaCham);
	// nếu Rectangle quá to thì va chạm có thể bị sai
	static ePhiaVaCham pvcPhiaVaCham(ThucThe *in_ThucThe1, ThucThe *in_ThucThe2);

public:
	static bool bDaVaCham(RECT in_HCN1, RECT in_HCN2);
	static bool bDiemVaHCN(float in_X, float in_Y, RECT in_HCN);
	static bool bHCNVaHinhTron(RECT in_HCN, int in_TamX, int in_TamY, int in_BanKinh);
};

