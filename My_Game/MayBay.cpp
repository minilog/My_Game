#include "MayBay.h"
#include "Camera.h"
#include "DanLv.h"



MayBay::MayBay(const Vec2& in_ToaDo, std::vector<TenLua*>& in_DS_TenLua,
	std::vector<Bui*>& in_Bui)
	:
	DoiTuong(in_ToaDo, Vec2(), 24, 36)
{
	mLoaiDoiTuong = eLDT_MayBay;
	ToaDo_XuatHien = in_ToaDo;

	for (auto TenLua : in_DS_TenLua)
	{
		mDS_TenLua.push_back(TenLua);
	}
	for (auto Bui : in_Bui)
	{
		mDS_Bui.push_back(Bui);
	}

	LoadThongTinHoatHinh();

	DiChuyen();
}

void MayBay::CapNhat(float in_tg, const DoiTuong * in_DoiTuong)
{
	if (NamTrongCamera &&
		!VaChamGame::get_DaVaCham(get_HCNGioiHan(), Camera::get_HCNGioiHan()))
	{
		mTrangThai = eTT_MayBay_PhatNo;
		// xét tiếp Tọa độ ban đầu có Nằm trong Camera hay ko?
		mToaDo = ToaDo_XuatHien;
		if (!VaChamGame::get_DaVaCham(get_HCNGioiHan(), Camera::get_HCNGioiHan()))
		{
			NamTrongCamera = false;
		}
	}
	// nếu đang nằm ngoài Camera mà ko có va chạm Camera thì ko có gì xảy ra
	else if (!NamTrongCamera &&
		VaChamGame::get_DaVaCham(get_HCNGioiHan(), Camera::get_HCNGioiHan()))
	{
		DiChuyen();
		NamTrongCamera = true;
	}

	if (mTrangThai == eTT_MayBay_PhatNo)
	{
		return;
	}

	mToaDo.x += mVanToc.x * in_tg;
	mToaDo.y += mVanToc.y * in_tg;

	if (HP <= 0)
	{
		PhatNo();
	}

	HH_DiChuyen->CapNhat(in_tg);

	if (mTrangThai == eTT_MayBay_DiChuyen)
	{
		if (TGDem > 2.0f)
		{
			TGDem = 0.0f;
		}
		if (TGDem <= 1.0f)
		{
			mVanToc.y = VanTocBay;
		}
		else
		{
			mVanToc.y = -VanTocBay;
		}

		if (!mLatHinh)
		{
			if (in_DoiTuong->get_ToaDo().x < mToaDo.x &&
				(mToaDo.y >= in_DoiTuong->get_ToaDo().y - 10.0f &&
					mToaDo.y <= in_DoiTuong->get_ToaDo().y + 10.0f))
			{
				BanDan();
			}
		}
	}

	if (mTrangThai == eTT_MayBay_BanDan)
	{
		if (TGDem > TG_BanTenLua)
		{
			BoChay();
		}

		TGDem_BanTenLua += in_tg;

		if (TGDem_BanTenLua > TG_BanTenLua / 2.8f)
		{
			for (auto TL : mDS_TenLua)
			{
				if (TL->get_TrangThai() == eTT_TenLua_BienMat)
				{
					if (!mLatHinh)
					{
						TL->BanRa(mToaDo + Vec2(-10.0f, 14.0f), Vec2(-150.0f, 0.0f));
					}
					else
					{
						TL->BanRa(mToaDo + Vec2(10.0f, 14.0f), Vec2(150.0f, 0.0f));
					}

					break; // chỉ dùng 1 viên mỗi lần
				}
			}
			for (int i = 0; i < (int)mDS_Bui.size(); i++)
			{
				// chỉ sử dụng BỤi đã biến mất
				if (mDS_Bui[i]->get_BienMat())
				{
					if (mLatHinh)
					{
						mDS_Bui[i]->set_ToaDo(mToaDo + Vec2(3.0f, 14.0f));
					}
					else
					{
						mDS_Bui[i]->set_ToaDo(mToaDo + Vec2(-3.0f, 14.0f));
					}

					mDS_Bui[i]->Remake();
					break;
				}
			}
			TGDem_BanTenLua = 0.0f;
		}

	}
	// thời gian đếm nên để sau cập nhật các thứ ở trên
	TGDem += in_tg;
}

void MayBay::XuLyVaCham(const DoiTuong * in_DoiTuong)
{
	if (mTrangThai == eTT_MayBay_PhatNo)
	{
		return;
	}

	// xét va chạm với đạn Lv đang tồn tại
	if (in_DoiTuong->get_LoaiDoiTuong() == eLDT_DanLv1 ||
		in_DoiTuong->get_LoaiDoiTuong() == eLDT_DanLv2 ||
		in_DoiTuong->get_LoaiDoiTuong() == eLDT_DanLv3)
	{

		if (((DanLv*)in_DoiTuong)->get_TrangThai() == eTT_Dan_BienMat ||
			((DanLv*)in_DoiTuong)->get_TrangThai() == eTT_Dan_DangTanBien)
		{
			return;
		}

		if (!VaChamGame::get_DaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan()))
		{
			return;
		}

		IsShining = true;
		HP -= ((DanLv*)in_DoiTuong)->get_Damage();
	}
}

void MayBay::Ve(const Vec2 & in_DoDoi)
{
	if (mTrangThai == eTT_MayBay_PhatNo)
	{
		return;
	}

	HH_DiChuyen->Ve(DS_HinhAnh::get_TH()->MayBay_png, mLatHinh, mToaDo, in_DoDoi);
}


void MayBay::DiChuyen()
{
	mTrangThai = eTT_MayBay_DiChuyen;
	TGDem = 0.0f;
	mToaDo = ToaDo_XuatHien;
	HP = MAXHP;
}

void MayBay::BanDan()
{
	mTrangThai = eTT_MayBay_BanDan;
	TGDem = 0.0f;
	mVanToc.x = 0.0f;
	mVanToc.y = 0.0f;
	TGDem_BanTenLua = 0.0f;
}

void MayBay::BoChay()
{
	mTrangThai = eTT_MayBay_BoChay;
	TGDem = 0.0f;
	mVanToc.y = -VanTocBay;
}

void MayBay::PhatNo()
{
	mTrangThai = eTT_MayBay_PhatNo;
	mToaDo = ToaDo_XuatHien;
}

void MayBay::LoadThongTinHoatHinh()
{
	std::vector<ThongTinFrame> lDSTTFrame;

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(38, 38, HCN(9, 9 + 40, 6, 6 + 38),     0.1f));
	lDSTTFrame.push_back(ThongTinFrame(26, 38, HCN(50, 50 + 28, 6 , 6 +38),   0.1f));
	lDSTTFrame.push_back(ThongTinFrame(24, 38, HCN(80, 80 + 24, 6 , 6 +38),   0.1f));
	lDSTTFrame.push_back(ThongTinFrame(24, 38, HCN(108, 108 + 24, 6 , 6 +38), 0.1f));
	lDSTTFrame.push_back(ThongTinFrame(26, 38, HCN(136, 136 + 28, 6 , 6 +38), 0.1f));
	HH_DiChuyen = new HoatHinh(lDSTTFrame);
}

MayBay::~MayBay()
{
}
