#pragma once

#include <d3dx9.h>
#include <d3d9.h>
#include "ThucThe.h"
#include "KieuDuLieuEnum.h"

class VaChamGame
{
public:
	static bool DaVaCham(RECT in_HCN1, RECT in_HCN2);
	static bool DiemVaHCN(float in_X, float in_Y, RECT in_HCN);
	static bool HCNVaHinhTron(RECT in_HCN, int in_TamX, int in_TamY, int in_BanKinh);

	static KetQuaVaCham HCNVaHCN(RECT in_HCN1, RECT in_HCN2);
	static PhiaVaCham NhanPhiaVaCham(ThucThe *in_ThucThe1, KetQuaVaCham in_KetQuaVaCham);
	// nếu Rectangle quá to thì va chạm có thể bị sai
	static PhiaVaCham NhanPhiaVaCham(ThucThe *in_ThucThe1, ThucThe *in_ThucThe2);
};

