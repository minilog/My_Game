#pragma once



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
	Vec2& operator -= (const Vec2& in)
	{
		x -= in.x;
		y -= in.y;
		return *this;
	}
	friend Vec2 operator - (const Vec2& in_a, const Vec2& in_b)
	{
		Vec2 lVec;
		lVec.x = in_a.x - in_b.x;
		lVec.y = in_a.y - in_b.y;

		return lVec;
	}
	friend Vec2 operator + (const Vec2& in_a, const Vec2& in_b)
	{
		Vec2 lVec;
		lVec.x = in_a.x + in_b.x;
		lVec.y = in_a.y + in_b.y;

		return lVec;
	}
	float x;
	float y;
};

// sử dụng cho lớp Hoạt Hình
class ThongTinFrame
{
public:
	ThongTinFrame(const Vec2& in_ToaDo, int in_ChieuRong, int in_ChieuCao, float in_ThoiGian, const HCN& in_Hcn = HCN())
	{
		ToaDo = in_ToaDo;
		ChieuRong = in_ChieuRong;
		ChieuCao = in_ChieuCao;
		ThoiGian = in_ThoiGian;
		Hcn = in_Hcn;
	}

	Vec2 ToaDo;
	int ChieuRong;
	int ChieuCao;
	float ThoiGian;
	HCN Hcn;
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
	eLDT_VienGachBinhThuong, eLDT_VienGachVang,
	eLDT_XMan,
	eLDT_DanLv1,
	eLDT_DanLv2,
	eLDT_DanLv3,
	eLDT_Ech,
	eLDT_DanNo1,
	eLDT_XacUop
};

enum eHuongDiChuyen
{
	eHDC_DiChuyenSangTrai, eHDC_DiChuyenSangPhai, eHDC_DungIm
};

enum eTrangThai
{
	eTT_DungIm,
	eTT_Chay,
	eTT_Roi,
	eTT_Nhay,
	eTT_HiSinh, // hi sinh = chết :)),
	eTT_ChuanBiChay,
	eTT_TiepDat,
	eTT_Truot,
	eTT_Luot,
	eTT_BatRa,
	eTTDan_DangTanBien,
	eTTDan_DangTonTai,
	eTTDan_DaBiPhaHuy,
	eTTDan_BanRa,
	eTT_ChuanBiNhay,
	eTTEch_NhamBan1,
	eTTEch_HaNhamBan1,
	eTTEch_NhamBan3,
	eTTEch_HaNhamBan3,
	eTTEch_ChuanBiNhay,
	eTTEch_Nhay,
	eTTEch_TiepDat,
	eTTEch_Roi,
	eTTEch_BanDan1,
	eTTEch_BanDan3,
	eTTEch_NhamBan2,
	eTTEch_BanDan2,
	eTTEch_HaNhamBan2,
	eTTEch_DangTanBien, 
	eTTEch_DaBiPhaHuy,
	eTT_DinhSatThuong,
	eTTXacUop_DungIm,
	eTTXacUop_DiChuyen,
	eTTXacUop_TanCong
};

