﻿#pragma once



class HCN
{
public:
	HCN(int in_Trai = 0, int in_Phai = 0, int in_Tren = 0, int in_Duoi = 0)
	{
		Trai = in_Trai;
		Phai = in_Phai;
		Tren = in_Tren;
		Duoi = in_Duoi;
	}

	int Trai;
	int Phai;
	int Tren;
	int Duoi;
};

class Vec2
{
public:
	Vec2(float in_x = 0, float in_y = 0){
		x = in_x;
		y = in_y;
	}
	Vec2& operator += (const Vec2& in)
	{
		x += in.x;
		y += in.y;
		return *this;
	}
	float x;
	float y;
};

// sử dụng cho lớp Hoạt Hình
class ThongTinFrame
{
public:
	ThongTinFrame(const Vec2& in_ToaDo, int in_ChieuRong, int in_ChieuCao)
	{
		ToaDo = in_ToaDo;
		ChieuRong = in_ChieuRong;
		ChieuCao = in_ChieuCao;
	}

	Vec2 ToaDo;
	int ChieuRong;
	int ChieuCao;
};

enum ePhiaVaCham
{
	ePVC_Trai, ePVC_Phai, ePVC_Tren, ePVC_Duoi,
	ePVC_TraiTren, ePVC_PhaiTren, 
	ePVC_TraiDuoi, ePVC_PhaiDuoi,
	ePVC_KhongXacDinh
};

struct eKetQuaVaCham
{
	bool eKQVC_DaVaCham;
	HCN eKQVC_VungVaCham;
};

enum eLoaiDoiTuong
{
	eLDT_KhongCo, eLDT_VienGach, eLDT_KeThu, eLDT_Mario, eLDT_DoiTuongTinh, 
	eLDT_VienGachBinhThuong, eLDT_VienGachVang
};

enum eHuongDiChuyen
{
	eHDC_DiChuyenSangTrai, eHDC_DiChuyenSangPhai, eHDC_DungIm
};

enum eTrangThai
{
	eTT_DungIm, 
	eTT_ChaySangTrai, eTT_ChaySangPhai,
	eTT_Roi, 
	eTT_Nhay,
	eTT_HiSinh // hi sinh = chết :))
};

