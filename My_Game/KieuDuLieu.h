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
	ThongTinFrame(int in_ChieuRong, int in_ChieuCao, const HCN& in_Hcn, float in_ThoiGian = 1.0f)
	{
		ChieuRong = in_ChieuRong;
		ChieuCao = in_ChieuCao;
		ThoiGian = in_ThoiGian;
		Hcn = in_Hcn;
	}
	int ChieuRong;
	int ChieuCao;
	HCN Hcn;
	float ThoiGian;
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
	eLDT_DoiTuongTinh, 
	eLDT_XMan,
	eLDT_DanLv1,
	eLDT_DanLv2,
	eLDT_DanLv3,
	eLDT_Ech,
	eLDT_DanNo1,
	eLDT_XacUop,
	eLDT_LoCot,
	eLDT_TenLua,
	eLDT_ThangMay,
	eLDT_TrucXoay,
	eLDT_Gai,
	eLDT_DoiTuongTinh2,
	eLDT_CuaDanhBoss,
	eLDT_BOSS1
};

enum eHuongDiChuyen
{
	eHDC_DiChuyenSangTrai, eHDC_DiChuyenSangPhai, eHDC_DungIm
};

enum eTrangThai
{
	// XMAN
	eTT_XMan_DungIm,
	eTT_XMan_Chay,
	eTT_XMan_Roi,
	eTT_XMan_Nhay,
	eTT_XMan_ChuanBiChay,
	eTT_XMan_TiepDat,
	eTT_XMan_Truot,
	eTT_XMan_Luot,
	eTT_XMan_BatRa,
	eTT_XMan_DinhSatThuong,
	eTT_XMan_PhatNo,
	eTT_XMan_XuatHien,

	eTT_DanNo1_BienMat,
	eTT_DanNo1_TonTai,

	eTT_Ech_BienMat,
	eTT_Ech_DangTanBien,
	eTT_Ech_ChuanBiNhay,
	eTT_Ech_Nhay,
	eTT_Ech_Roi,
	eTT_Ech_TiepDat,
	eTT_Ech_NhamBan1,
	eTT_Ech_HaNhamBan1,
	eTT_Ech_BanDan1,
	eTT_Ech_NhamBan2,
	eTT_Ech_HaNhamBan2,
	eTT_Ech_BanDan2,
	eTT_Ech_NhamBan3,
	eTT_Ech_HaNhamBan3,
	eTT_Ech_BanDan3,

	eTT_XacUop_DungIm,
	eTT_XacUop_TanCong,
	eTT_XacUop_DiChuyen,

	eTT_Dan_BienMat,
	eTT_Dan_TonTai,
	eTT_Dan_DangTanBien,
	eTT_Dan_BanRa,

	eTT_LoCot_BienMat,
	eTT_LoCot_BanTenLua,
	eTT_LoCot_BanDanNo,

	eTT_TenLua_TonTai,
	eTT_TenLua_PhatNo,
	eTT_TenLua_BienMat,

	eTT_ThangMay_DungIm,
	eTT_ThangMay_DiChuyen,
	eTT_ThangMay_BienMat,

	eTT_CuaDanhBoss_MoCua,
	eTT_CuaDanhBoss_DongCua,
	eTT_CuaDanhBoss_KhoaCua,

	eTT_BOSS1_XuatHien,
	eTT_BOSS1_BienMat,
	eTT_BOSS1_TanCong1,
	eTT_BOSS1_TanCong2,
	eTT_BOSS1_TanCong3
};

