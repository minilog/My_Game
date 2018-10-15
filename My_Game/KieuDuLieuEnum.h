#pragma once

#include <d3d9.h>

enum PhiaVaCham
{
	Trai, Phai, Tren, Duoi,
	TraiBenTren, PhaiBenTren, 
	TraiBenDuoi, PhaiBenDuoi,
	KhongXacDinh
};

struct KetQuaVaCham
{
	bool DaVaCham;
	RECT VungVaCham;
};

enum LoaiThucThe
{
	KhongCo, VienGach, KeThu, Mario, ThucTheTinh, VienGachVangBinhThuong, VienGachVangAnDuoc
};