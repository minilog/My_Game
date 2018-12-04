#include "Ech.h"
#include "DanNo1.h"
#include "DanLv.h"



Ech::Ech(const Vec2 & in_ToaDo, const Vec2 & in_VanToc, int in_Rong, int in_Cao)
	:
	DoiTuong(in_ToaDo, in_VanToc, 22, 30)
{
	mLoaiDoiTuong = eLDT_Ech;
	mTrangThai = eTT_Ech_BienMat;

	mToaDoXuatHien = in_ToaDo;

	LoadThongTinHoatHinh();

	mBui = new Bui(Vec2(), Vec2());
	mHH_HienTai = mHH_DangTanBien;
}

void Ech::CapNhat(float in_tg, const DoiTuong * in_XMan)
{
	if (mTGDem_HieuUngNoTung <= mTG_HieuUngNoTung)
	{
		mTGDem_HieuUngNoTung += in_tg;
		mHH_HieuUngNoTung->CapNhat(in_tg);
	}	

	// nếu đang nằm trong Camera mà vẫn đang va chạm Camera thì ko có gì xảy ra
	if (mNamTrongCamera &&
		!VaChamGame::get_DaVaCham(get_HCNGioiHan(), Camera::get_HCNGioiHan()))
	{
		mTrangThai = eTT_Ech_BienMat;
		// xét tiếp Tọa độ ban đầu có Nằm trong Camera hay ko?
		mToaDo = mToaDoXuatHien;
		if (!VaChamGame::get_DaVaCham(get_HCNGioiHan(), Camera::get_HCNGioiHan()))
		{
			mNamTrongCamera = false;
		}
	}
	// nếu đang nằm ngoài Camera mà ko có va chạm Camera thì ko có gì xảy ra
	else if (!mNamTrongCamera &&
		VaChamGame::get_DaVaCham(get_HCNGioiHan(), Camera::get_HCNGioiHan()))
	{
		ChuanBiNhay();
		mHP = mMaxHP;
		mNamTrongCamera = true;
	}

	// nếu Ếch đã bị phá hủy thì bỏ qua
	if (mTrangThai == eTT_Ech_BienMat)
	{
		return;
	}

	if (mHP <= 0 && mTrangThai != eTT_Ech_DangTanBien)
	{
		DangTanBien();
	}

	if (mIsShining)
	{
		mTGDem_Shining += in_tg;
		if (mTGDem_Shining > mTG_Shining)
		{
			mTGDem_Shining = 0.0f;
			mIsShining = false;
		}
	}

	mBui->CapNhat(in_tg);

	mKhoangCach_XMan = mToaDo.x - in_XMan->get_ToaDo().x;

	mToaDo.x += mVanToc.x * in_tg;
	mToaDo.y += mVanToc.y * in_tg;

	mHH_HienTai->CapNhat(in_tg);

	switch (mTrangThai)
	{
	case eTT_Ech_ChuanBiNhay:
		CapNhat_ChuanBiNhay(in_tg);
		break;

	case eTT_Ech_Nhay:
		CapNhat_Nhay(in_tg);
		break;

	case eTT_Ech_Roi:
		CapNhat_Roi(in_tg);
		break;

	case eTT_Ech_TiepDat:
		CapNhat_TiepDat(in_tg);
		break;

	case eTT_Ech_NhamBan1:
		CapNhat_NhamBan1(in_tg);
		break;

	case eTT_Ech_HaNhamBan1:
		CapNhat_HaNhamBan1(in_tg);
		break;

	case eTT_Ech_BanDan1:
		CapNhat_BanDan1(in_tg);
		break;

	case eTT_Ech_NhamBan3:
		CapNhat_NhamBan3(in_tg);
		break;

	case eTT_Ech_BanDan3:
		CapNhat_BanDan3(in_tg);
		break;

	case eTT_Ech_HaNhamBan3:
		CapNhat_HaNhamBan3(in_tg);
		break;

	case eTT_Ech_NhamBan2:
		CapNhat_NhamBan2(in_tg);
		break;

	case eTT_Ech_BanDan2:
		CapNhat_BanDan2(in_tg);
		break;

	case eTT_Ech_HaNhamBan2:
		CapNhat_HaNhamBan2(in_tg);
		break;

	case eTT_Ech_DangTanBien:
		CapNhat_DangTanBien(in_tg);
		break;

	default:
		break;
	}
}

void Ech::Ve(const Vec2 & in_DoDoi)
{
	if (mTGDem_HieuUngNoTung <= mTG_HieuUngNoTung)
	{
		mHH_HieuUngNoTung->Ve(DS_HinhAnh::get_TH()->DanNo1_png, false, mToaDo_HieuUngNoTung, in_DoDoi);
	}

	// nếu Ếch đã bị phá hủy thì bỏ qua
	if (mTrangThai == eTT_Ech_BienMat)
	{
		return;
	}

	if (mIsShining)
	{
		if (mTrangThai != eTT_Ech_DangTanBien)
		{
			mHH_HienTai->Ve(DS_HinhAnh::get_TH()->Ech_Shining_png, mLatHinh, mToaDo, in_DoDoi);
		}
	}
	else
	{
		if (mTrangThai == eTT_Ech_DangTanBien)
		{
			mHH_HienTai->Ve(DS_HinhAnh::get_TH()->Ech_png, mLatHinh, mToaDo, in_DoDoi, D3DCOLOR_ARGB(120, 255, 255, 225));
		}
		else
		{
			mHH_HienTai->Ve(DS_HinhAnh::get_TH()->Ech_png, mLatHinh, mToaDo, in_DoDoi);
		}
	}

	mBui->Ve(in_DoDoi);
}

void Ech::XuLyVaCham(const DoiTuong * in_DoiTuong)
{
	// nếu Ếch đã bị phá hủy thì bỏ qua
	if (mTrangThai == eTT_Ech_BienMat || mTrangThai == eTT_Ech_DangTanBien)
	{
		return;
	}

	// xét va chạm với đạn Lv đang tồn tại
	if (in_DoiTuong->get_LoaiDoiTuong() == eLDT_DanLv1 ||
		in_DoiTuong->get_LoaiDoiTuong() == eLDT_DanLv2 ||
		in_DoiTuong->get_LoaiDoiTuong() == eLDT_DanLv3)
	{
		if (VaChamGame::get_DaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan()))
		{
			mIsShining = true;
			mHP -= ((DanLv*) in_DoiTuong)->get_Damage();
		}
	}

	// xét va chạm với đối tượng tĩnh khi Ếch đang Nhảy hoặc Rơi
	if (in_DoiTuong->get_LoaiDoiTuong() == eLDT_DoiTuongTinh)
	{
		if (mTrangThai != eTT_Ech_Nhay &&
			mTrangThai != eTT_Ech_Roi)
		{
			return;
		}

		eKetQuaVaCham lKQVC = VaChamGame::get_KetQuaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan());

		if (lKQVC.eKQVC_DaVaCham)
		{
			ePhiaVaCham lPVC = VaChamGame::get_PhiaVaCham(this, lKQVC);
			switch (lPVC)
			{
			case ePVC_Duoi:
				mToaDo.y -= lKQVC.eKQVC_VungVaCham.Duoi - lKQVC.eKQVC_VungVaCham.Tren + 1;
				if (mTrangThai == eTT_Ech_Roi)
				{
					mVanToc.y = 0.0f;
					TiepDat();
				}
				break;

			case ePVC_Tren:
				mToaDo.y += lKQVC.eKQVC_VungVaCham.Duoi - lKQVC.eKQVC_VungVaCham.Tren + 1;
				if (mTrangThai == eTT_Ech_Nhay)
				{
					mVanToc.y = 0.0f;
					Roi();
				}
				break;

			case ePVC_TraiTren:
			case ePVC_Trai:
			case ePVC_TraiDuoi:
				mToaDo.x += lKQVC.eKQVC_VungVaCham.Phai - lKQVC.eKQVC_VungVaCham.Trai;
				break;

			case ePVC_Phai:
			case ePVC_PhaiTren:
			case ePVC_PhaiDuoi:
				mToaDo.x -= lKQVC.eKQVC_VungVaCham.Phai - lKQVC.eKQVC_VungVaCham.Trai;
				break;

			default:
				break;
			}
		}
	}
}

void Ech::NhamBan2()
{
	mTrangThai = eTT_Ech_NhamBan2;
	mHH_HienTai = mHH_NhamBan2;
	mHH_HienTai->Remake();
	mTGDem_NhamBan2 = 0.0f;
}

void Ech::BanDan2()
{
	mTrangThai = eTT_Ech_BanDan2;
	mHH_HienTai = mHH_BanDan2;
	mHH_HienTai->Remake();
	mTGDem_BanDan = 0.0f;
	mTGDem_BuiXuatHien = 0.35f;
}

void Ech::HaNhamBan2()
{
	mTrangThai = eTT_Ech_HaNhamBan2;
	mHH_HienTai = mHH_HaNhamBan2;
	mHH_HienTai->Remake();
	mTGDem_HaNhamBan2 = 0.0f;
}

void Ech::NhamBan3()
{
	mTrangThai = eTT_Ech_NhamBan3;
	mHH_HienTai = mHH_NhamBan3;
	mHH_HienTai->Remake();
	mTGDem_NhamBan3 = 0.0f;
}

void Ech::BanDan3()
{
	mTrangThai = eTT_Ech_BanDan3;
	mHH_HienTai = mHH_BanDan3;
	mHH_HienTai->Remake();
	mTGDem_BanDan = 0.0f;
	mTGDem_BuiXuatHien = 0.35f;
}

void Ech::HaNhamBan3()
{
	mTrangThai = eTT_Ech_HaNhamBan3;
	mHH_HienTai = mHH_HaNhamBan3;
	mHH_HienTai->Remake();
	mTGDem_HaNhamBan3 = 0.0f;
}

void Ech::BanDan1()
{
	mTrangThai = eTT_Ech_BanDan1;
	mHH_HienTai = mHH_BanDan1;
	mHH_HienTai->Remake();
	mTGDem_BanDan = 0.0f;
	mTGDem_BuiXuatHien = 0.35f;
}

void Ech::NhamBan1()
{
	mTrangThai = eTT_Ech_NhamBan1;
	mHH_HienTai = mHH_NhamBan1;
	mHH_HienTai->Remake();
	mTGDem_NhamBan1 = 0.0f;
}

void Ech::HaNhamBan1()
{
	mTrangThai = eTT_Ech_HaNhamBan1;
	mHH_HienTai = mHH_HaNhamBan1;
	mHH_HienTai->Remake();
	mTGDem_HaNhamBan1 = 0.0f;
}

void Ech::ChuanBiNhay()
{
	mTrangThai = eTT_Ech_ChuanBiNhay;
	mHH_HienTai = mHH_ChuanBiNhay;
	mHH_HienTai->Remake();
	mTGDem_ChuanBiNhay = 0.0f;
	mVanToc.x = mVanToc.y = 0.0f;
	mTGDem_HieuUngNoTung = mTG_HieuUngNoTung + 0.1f;
}

void Ech::Nhay()
{
	mTrangThai = eTT_Ech_Nhay;
	mHH_HienTai = mHH_Nhay;
	mVanToc.y = -mVanTocRoiToiDa;
}

void Ech::Roi()
{
	mTrangThai = eTT_Ech_Roi;
	mHH_HienTai = mHH_Nhay;
}

void Ech::TiepDat()
{
	mTrangThai = eTT_Ech_TiepDat;
	mHH_HienTai = mHH_ChuanBiNhay;
	mHH_HienTai->Remake();
	mTGDem_TiepDat = 0.0f;
	mVanToc.x = mVanToc.y = 0.0f;
}

void Ech::DangTanBien()
{
	mTGDem_TanBien = 0.0f;
	mHH_HienTai = mHH_DangTanBien;
	mTrangThai = eTT_Ech_DangTanBien;
	mVanToc.y = -mVanTocRoiToiDa / 1.1f;
	if (mKhoangCach_XMan < 0.0f)
	{
		mVanToc.x = -mVanTocNhay / 1.2f;
	}
	else
	{
		mVanToc.x = +mVanTocNhay / 1.2f;
	}

	// khi chuyển sang trạng thái Đang Tan Biến thì Hiệu Ứng Nổ Tung xuất hiện
	mTGDem_HieuUngNoTung = 0.0f;
	mToaDo_HieuUngNoTung = mToaDo + Vec2(0.0f, -1.0f);
	mHH_HieuUngNoTung->Remake();
}


void Ech::LoadThongTinHoatHinh()
{
	std::vector<ThongTinFrame> lDSTTFrame;

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(58, 26, HCN(31, 31 + 58, 154, 154 + 26)));
	mHH_DangTanBien = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(48, 32, HCN(5, 5 + 40, 6, 38), 0.14f));
	lDSTTFrame.push_back(ThongTinFrame(44, 46, HCN(7, 7 + 38, 61, 64 + 40), 0.14f));
	lDSTTFrame.push_back(ThongTinFrame(38, 56, HCN(48, 48 + 34, 56, 56 + 44), 0.14f));
	lDSTTFrame.push_back(ThongTinFrame(28, 62, HCN(92, 92 + 30, 53, 53 + 48), 0.14f));
	mHH_NhamBan2 = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(48, 32, HCN(5, 5 + 40, 6, 38), 0.14f));
	lDSTTFrame.push_back(ThongTinFrame(44, 46, HCN(7, 7 + 38, 61, 64 + 40), 0.14f));
	lDSTTFrame.push_back(ThongTinFrame(38, 56, HCN(48, 48 + 34, 56, 56 + 44), 0.14f));
	lDSTTFrame.push_back(ThongTinFrame(28, 62, HCN(92, 92 + 30, 53, 53 + 48), 0.14f));
	mHH_NhamBan2 = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(28, 62, HCN(92, 92 + 30, 53, 53 + 48), 0.25f));
	lDSTTFrame.push_back(ThongTinFrame(28, 60, HCN(139, 139 + 30, 106, 106 + 46), 0.25f));
	mHH_BanDan2 = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(28, 62, HCN(92, 92 + 30, 53, 53 + 48), 0.14f));
	lDSTTFrame.push_back(ThongTinFrame(38, 56, HCN(48, 48 + 34, 56, 56 + 44), 0.14f));
	lDSTTFrame.push_back(ThongTinFrame(44, 46, HCN(7, 7 + 38, 61, 64 + 40), 0.14f));
	lDSTTFrame.push_back(ThongTinFrame(48, 32, HCN(5, 5 + 40, 6, 38), 0.14f));
	mHH_HaNhamBan2 = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(48, 32, HCN(5, 5 + 40, 6, 38), 0.12f));
	lDSTTFrame.push_back(ThongTinFrame(48, 32, HCN(49, 49 + 40, 6, 38), 0.12f));
	lDSTTFrame.push_back(ThongTinFrame(48, 32, HCN(100, 100 + 42, 6, 38), 0.12f));
	lDSTTFrame.push_back(ThongTinFrame(48, 32, HCN(49, 49 + 40, 6, 38), 0.12f));
	lDSTTFrame.push_back(ThongTinFrame(48, 32, HCN(5, 5 + 40, 6, 38), 0.12f));
	mHH_ChuanBiNhay = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(48, 32, HCN(146, 146 + 48, 2, 2 + 42)));
	mHH_Nhay = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(48, 32, HCN(5, 5 + 40, 6, 38), 0.14f));
	lDSTTFrame.push_back(ThongTinFrame(44, 46, HCN(7, 7 + 38, 61, 64 + 40), 0.14f));
	lDSTTFrame.push_back(ThongTinFrame(38, 56, HCN(48, 48 + 34, 56, 56 + 44), 0.14f));
	mHH_NhamBan1 = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(38, 56, HCN(48, 48 + 34, 56, 56 + 44), 0.14f));
	lDSTTFrame.push_back(ThongTinFrame(44, 46, HCN(7, 7 + 38, 61, 64 + 40), 0.14f));
	lDSTTFrame.push_back(ThongTinFrame(48, 32, HCN(5, 5 + 40, 6, 38), 0.14f));
	mHH_HaNhamBan1 = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(38, 56, HCN(48, 48 + 34, 56, 56 + 44), 0.25f));
	lDSTTFrame.push_back(ThongTinFrame(38, 54, HCN(95, 95 + 36, 110, 110 + 44), 0.25f));
	mHH_BanDan1 = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame( 48, 32, HCN(5, 5 + 40, 6, 38), 0.14f));
	lDSTTFrame.push_back(ThongTinFrame( 44, 46, HCN(7, 7 + 38, 61, 64 + 40), 0.14f));
	lDSTTFrame.push_back(ThongTinFrame( 38, 56, HCN(48, 48 + 34, 56, 56 + 44), 0.14f));
	lDSTTFrame.push_back(ThongTinFrame( 28, 62, HCN(92, 92 + 30, 53, 53 + 48), 0.14f));
	lDSTTFrame.push_back(ThongTinFrame( 24, 64, HCN(131, 131 + 28, 52, 52 + 48), 0.14f));
	mHH_NhamBan3 = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(24, 64, HCN(131, 131 + 28, 52, 52 + 48), 0.25f));
	lDSTTFrame.push_back(ThongTinFrame(24, 62, HCN(178, 178 + 28, 105, 105 + 48), 0.25f));
	mHH_BanDan3 = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(24, 64, HCN(131, 131 + 28, 52, 52 + 48), 0.14f));
	lDSTTFrame.push_back(ThongTinFrame(28, 62, HCN(92, 92 + 30, 53, 53 + 48), 0.14f));
	lDSTTFrame.push_back(ThongTinFrame(38, 56, HCN(48, 48 + 34, 56, 56 + 44), 0.14f));
	lDSTTFrame.push_back(ThongTinFrame(44, 46, HCN(7, 7 + 38, 61, 64 + 40), 0.14f));
	lDSTTFrame.push_back(ThongTinFrame(48, 32, HCN(5, 5 + 40, 6, 38), 0.14f));
	mHH_HaNhamBan3 = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(16, 24, HCN(1 - 1, 1 + 16 - 1, 56 - 43, 56 + 16 - 43), 0.08f));
	lDSTTFrame.push_back(ThongTinFrame(32, 40, HCN(26 - 1, 26 + 32 - 1, 48 - 43, 48 + 32 -43), 0.08f));
	lDSTTFrame.push_back(ThongTinFrame(28, 36, HCN(66 - 1, 66 + 28 - 1, 51 - 43, 51 + 24 - 43), 0.08f));
	lDSTTFrame.push_back(ThongTinFrame(30, 40, HCN(103 - 1, 103 + 30 - 1, 47 - 43, 47 + 28 - 43), 0.08f));
	lDSTTFrame.push_back(ThongTinFrame(32, 36, HCN(143 - 1, 143 + 32 - 1, 43 - 43, 43 + 28 - 43), 0.08f));
	lDSTTFrame.push_back(ThongTinFrame(32, 38, HCN(187 - 1, 187 + 32 - 1, 53 - 43, 53 + 30 - 43), 0.08f));
	mHH_HieuUngNoTung = new HoatHinh(lDSTTFrame);
}

void Ech::CapNhat_NhamBan2(float in_tg)
{
	if (mKhoangCach_XMan < 0)
	{
		mLatHinh = true;
	}
	else
	{
		mLatHinh = false;
	}
	mTGDem_NhamBan2 += in_tg;
	if (mTGDem_NhamBan2 > mTG_NhamBan2)
	{
		BanDan2();
	}
}

void Ech::CapNhat_BanDan2(float in_tg)
{
	mTGDem_BanDan += in_tg;
	if (mTGDem_BanDan > mTG_BanDan)
	{
		HaNhamBan2();
	}
	mTGDem_BuiXuatHien += in_tg;
	if (mTGDem_BuiXuatHien > mTG_BanDan / 3.0f)
	{
		if (mLatHinh)
		{
			mBui->set_ToaDo(mToaDo + Vec2(11.0f, -29.0f));
		}
		else
		{
			mBui->set_ToaDo(mToaDo + Vec2(-11.0f, -29.0f));
		}
		mBui->Remake();
		mTGDem_BuiXuatHien = 0.0f;
	}
}

void Ech::CapNhat_HaNhamBan2(float in_tg)
{
	mTGDem_HaNhamBan2 += in_tg;
	if (mTGDem_HaNhamBan2 > mTG_HaNhamBan2)
	{
		ChuanBiNhay();
	}
}

void Ech::CapNhat_ChuanBiNhay(float in_tg)
{
	mTGDem_ChuanBiNhay += in_tg;
	if (mKhoangCach_XMan < 0)
	{
		mLatHinh = true;
	}
	else
	{
		mLatHinh = false;
	}
	if (mTGDem_ChuanBiNhay > mTG_ChuanBiNhay)
	{
		if (mLatHinh)
		{
			mVanToc.x = mVanTocNhay;
		}
		else
		{
			mVanToc.x = -mVanTocNhay;
		}
		Nhay();
	}
}

void Ech::CapNhat_Nhay(float in_tg)
{
	mVanToc.y += mGiaTocTrongTruong * in_tg;
	if (mVanToc.y > 0.0f)
	{
		mVanToc.y = 0.0f;
		Roi();
	}
}

void Ech::CapNhat_Roi(float in_tg)
{
	mVanToc.y += mGiaTocTrongTruong * in_tg;
	if (mVanToc.y > mVanTocRoiToiDa)
	{
		mVanToc.y = mVanTocRoiToiDa;
	}
}

void Ech::CapNhat_TiepDat(float in_tg)
{
	float lKC = mKhoangCach_XMan;
	if (lKC < 0)
		lKC = -lKC;

	mTGDem_TiepDat += in_tg;
	if (mTGDem_TiepDat > mTG_TiepDat)
	{
		if (lKC > 100.0f)
		{
			NhamBan1();
		}
		else if (lKC > 50.0f)
		{
			NhamBan2();
		}
		else
		{
			NhamBan3();
		}
	}
}

void Ech::CapNhat_NhamBan1(float in_tg)
{
	if (mKhoangCach_XMan < 0)
	{
		mLatHinh = true;
	}
	else
	{
		mLatHinh = false;
	}
	mTGDem_NhamBan1 += in_tg;
	if (mTGDem_NhamBan1 > mTG_NhamBan1)
	{
		BanDan1();
	}
}

void Ech::CapNhat_HaNhamBan1(float in_tg)
{
	mTGDem_HaNhamBan1 += in_tg;
	if (mTGDem_HaNhamBan1 > mTG_HaNhamBan1)
	{
		ChuanBiNhay();
	}
}

void Ech::CapNhat_BanDan1(float in_tg)
{
	mTGDem_BanDan += in_tg;
	if (mTGDem_BanDan > mTG_BanDan)
	{
		HaNhamBan1();
	}
	mTGDem_BuiXuatHien += in_tg;
	if (mTGDem_BuiXuatHien > mTG_BanDan / 3.0f)
	{
		if (mLatHinh)
		{
			mBui->set_ToaDo(mToaDo + Vec2(17.0f, -26.0f));
		}
		else
		{
			mBui->set_ToaDo(mToaDo + Vec2(-17.0f, -26.0f));
		}
		mBui->Remake();
		mTGDem_BuiXuatHien = 0.0f;
	}
}

void Ech::CapNhat_NhamBan3(float in_tg)
{
	if (mKhoangCach_XMan < 0)
	{
		mLatHinh = true;
	}
	else
	{
		mLatHinh = false;
	}

	mTGDem_NhamBan3 += in_tg;
	if (mTGDem_NhamBan3 > mTG_NhamBan3)
	{
		BanDan3();
	}
}

void Ech::CapNhat_BanDan3(float in_tg)
{
	mTGDem_BanDan += in_tg;
	if (mTGDem_BanDan > mTG_BanDan)
	{
		HaNhamBan3();
	}
	mTGDem_BuiXuatHien += in_tg;
	if (mTGDem_BuiXuatHien > mTG_BanDan / 3.0f)
	{
		mBui->set_ToaDo(mToaDo + Vec2(0.0f, -31.0f));
		mBui->Remake();
		mTGDem_BuiXuatHien = 0.0f;
	}
}

void Ech::CapNhat_HaNhamBan3(float in_tg)
{
	mTGDem_HaNhamBan3 += in_tg;
	if (mTGDem_HaNhamBan3 > mTG_HaNhamBan3)
	{
		ChuanBiNhay();
	}
}

void Ech::CapNhat_DangTanBien(float in_tg)
{
	mVanToc.y += mGiaTocTrongTruong * in_tg;
	mTGDem_TanBien += in_tg;
	if (mTGDem_TanBien > mTG_TanBien)
	{
		mTrangThai = eTT_Ech_BienMat;
		mToaDo = mToaDoXuatHien;
	}
}

Ech::~Ech()
{
	if (mHH_ChuanBiNhay)
		delete mHH_ChuanBiNhay;

	if (mHH_Nhay)
		delete mHH_Nhay;

	if (mHH_NhamBan1)
		delete mHH_NhamBan1;

	if (mHH_BanDan1)
		delete mHH_BanDan1;

	if (mHH_HaNhamBan1)
		delete mHH_HaNhamBan1;

	if (mHH_NhamBan2)
		delete mHH_NhamBan2;

	if (mHH_BanDan2)
		delete mHH_BanDan2;

	if (mHH_HaNhamBan2)
		delete mHH_HaNhamBan2;

	if (mHH_NhamBan3)
		delete mHH_NhamBan3;

	if (mHH_BanDan3)
		delete mHH_BanDan3;

	if (mHH_HaNhamBan3)
		delete mHH_HaNhamBan3;

	if (mBui)
		delete mBui;

	if (mHH_DangTanBien)
		delete mHH_DangTanBien;

	if (mHH_HieuUngNoTung)
		delete mHH_HieuUngNoTung;

}

