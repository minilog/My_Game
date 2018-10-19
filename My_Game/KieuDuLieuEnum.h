#pragma once

#include <d3d9.h>

enum ePhiaVaCham
{
	eTrai, ePhai, eTren, eDuoi,
	eTraiBenTren, ePhaiBenTren, 
	eTraiBenDuoi, ePhaiBenDuoi,
	eKhongXacDinh
};

struct eKetQuaVaCham
{
	bool DaVaCham;
	RECT VungVaCham;
};

enum eLoaiThucThe
{
	eKhongCo, eVienGach, eKeThu, eMario, eThucTheTinh, eVienGachVangBinhThuong, eVienGachVangAnDuoc
};

enum eHuongDiChuyen
{
	eDiChuyenSangTrai, eDiChuyenSangPhai, eDungIm
};

enum eTrangThai
{
	eDangDung, eDangChay, eDangRoi, eDangNhay, eHiSinh // hi sinh = chết :))
};