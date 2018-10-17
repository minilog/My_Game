#pragma once

#include <d3d9.h>

enum ePhiaVaCham
{
	Trai, Phai, Tren, Duoi,
	TraiBenTren, PhaiBenTren, 
	TraiBenDuoi, PhaiBenDuoi,
	KhongXacDinh
};

struct eKetQuaVaCham
{
	bool DaVaCham;
	RECT VungVaCham;
};

enum eLoaiThucThe
{
	KhongCo, VienGach, KeThu, Mario, ThucTheTinh, VienGachVangBinhThuong, VienGachVangAnDuoc
};

enum eHuongDiChuyen
{
	DiChuyenSangTrai,
	DiChuyenSangPhai,
	DungIm
};

enum eTrangThai
{
	DangDung, DangChay, DangRoi, DangNhay, HiSinh // hi sinh = chết :))
};