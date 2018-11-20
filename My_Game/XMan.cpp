﻿#include "XMan.h"
#include <vector>
#include "VaChamGame.h"
#include "GameLog.h"

XMan::XMan(const Vec2& in_ToaDo)
	:DoiTuong(in_ToaDo, Vec2(), 18, 32)
{
	DoiTuong::mLoaiDoiTuong = eLDT_XMan;

	LoadHinhAnhVao();

	Roi();
}


XMan::~XMan()
{
	if (mHH_DungIm)
	{
		delete mHH_DungIm;
	}
	if (mHH_ChuanBiChay)
	{
		delete mHH_ChuanBiChay;
	}
	if (mHH_Chay)
	{
		delete mHH_Chay;
	}
	if (mHH_Nhay)
	{
		delete mHH_Nhay;
	}
	if (mHH_TiepDat)
	{
		delete mHH_TiepDat;
	}
	if (mHH_Roi)
	{
		delete mHH_Roi;
	}
	if (mHH_Luot)
	{
		delete mHH_TiepDat;
	}
}

void XMan::CapNhat(float in_tg)
{
	mHH_HienTai->CapNhat(in_tg);
	mToaDo.x += mVanToc.x * in_tg;
	mToaDo.y += mVanToc.y * in_tg;

	switch (mTrangThai)
	{
	case eTT_DungIm:
		if (mDangDungTuNhienRoi == true)
		{
			Roi();
		}
		break;
	case eTT_ChuanBiChay:
		mTG_DemChuanBiChay += in_tg;
		if (mTG_DemChuanBiChay >= mTG_ChuanBiChay)
		{
			Chay();
		}
		if (mDangDungTuNhienRoi == true)
		{
			Roi();
		}
		break;
	case eTT_Chay:
		if (mDangDungTuNhienRoi == true)
		{
			Roi();
		}
		break;

	case eTT_TiepDat:
		mTG_DemTiepDat += in_tg;
		if (mTG_DemTiepDat >= mTG_TiepDat)
		{
			DungIm();
		}
		break;

	case eTT_Nhay:
		mVanToc.y += mGiaTocTrongTruong * in_tg;
		if (!mKeys['C'])
		{
			mVanToc.y += mGiaTocTrongTruong * in_tg * 10;
		}
		if (mVanToc.y >= 0.0f)
		{
			Roi();
		}
		break;

	case eTT_Roi:
		mVanToc.y += mGiaTocTrongTruong * in_tg;
		if (mVanToc.y > mVanTocRoiToiDa)
		{
			mVanToc.y = mVanTocRoiToiDa;
		}
		break;

	case eTT_Luot:
		mTG_DemLuot += in_tg;
		if (mTG_DemLuot >= mTG_Luot)
		{
			DungIm();
		}
		break;

	case eTT_BatRa:
		mVanToc.y += mGiaTocTrongTruong * in_tg;
		mTG_DemBatRa += in_tg;
		if (!mKeys['C'])
		{
			mVanToc.y += mGiaTocTrongTruong * in_tg * 10;
		}
		if (mVanToc.y >= 0.0f)
		{
			Roi();
		}
		if (mTG_DemBatRa >= mTG_BatRa)
		{
			float lVanTocHienTai = mVanToc.y;
			Nhay();
			mVanToc.y = lVanTocHienTai;
		}

		break;

	default:
		break;
	}

	mDangDungTuNhienRoi = true;
	mCoChuongNgaiVatTrai = mCoChuongNgaiVatPhai = false;
}

void XMan::Ve(const Vec2 & in_DoDoi)
{
	mHH_HienTai->set_LatTheoChieuNgang(mLatHinh);
	mHH_HienTai->set_ToaDo(mToaDo);
	mHH_HienTai->set_DoDoi(in_DoDoi);
	mHH_HienTai->Ve();
}

void XMan::XuLyVaCham(const DoiTuong * in_DoiTuong)
{
	if (in_DoiTuong->get_LoaiDoiTuong() == eLDT_DoiTuongTinh)
	{
		eKetQuaVaCham lKQVC = VaChamGame::get_KetQuaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan());
		ePhiaVaCham lPVC = VaChamGame::get_PhiaVaCham(this, lKQVC);

		if (lKQVC.eKQVC_DaVaCham)
		{
			switch (lPVC)
			{
			case ePVC_Duoi:
				mToaDo.y -= lKQVC.eKQVC_VungVaCham.Duoi - lKQVC.eKQVC_VungVaCham.Tren + 1;
				if (mTrangThai == eTT_Roi)
				{
					TiepDat();
				}
				if (mTrangThai == eTT_Truot)
				{
					TiepDat();
				}
				break;
			case ePVC_Tren:
				mToaDo.y += lKQVC.eKQVC_VungVaCham.Duoi - lKQVC.eKQVC_VungVaCham.Tren + 1;
				if (mTrangThai == eTT_Nhay )
				{
					Roi();
				}
				break;


			case ePVC_TraiTren:
			case ePVC_Trai:
			case ePVC_TraiDuoi:
				mToaDo.x += lKQVC.eKQVC_VungVaCham.Phai - lKQVC.eKQVC_VungVaCham.Trai;
				mCoChuongNgaiVatTrai = true;

				if (mLatHinh &&
					(mTrangThai == eTT_Chay || mTrangThai == eTT_ChuanBiChay ) )
				{
					DungIm();
				}
				break;

			case ePVC_Phai:
			case ePVC_PhaiTren:
			case ePVC_PhaiDuoi:
				mToaDo.x -= lKQVC.eKQVC_VungVaCham.Phai - lKQVC.eKQVC_VungVaCham.Trai;
				mCoChuongNgaiVatPhai = true;

				if (!mLatHinh &&
					(mTrangThai == eTT_Chay || mTrangThai == eTT_ChuanBiChay))
				{
					DungIm();
				}

				break;

			default:
				break;
			}
		}
	}

#pragma region XỬ LÝ BIẾN mDangDungTuNhienRoi
	if (mDangDungTuNhienRoi == true)
	{
		HCN lHCNGioiHanMoRongDay = get_HCNGioiHan();
		lHCNGioiHanMoRongDay.Duoi += 2;

		eKetQuaVaCham lKQVC = VaChamGame::get_KetQuaVaCham(lHCNGioiHanMoRongDay, in_DoiTuong->get_HCNGioiHan());
		ePhiaVaCham lPVC = VaChamGame::get_PhiaVaCham(this, lKQVC);

		if (lKQVC.eKQVC_DaVaCham == true)
		{
			switch (in_DoiTuong->get_LoaiDoiTuong())
			{
			case eLDT_DoiTuongTinh:
				if (lPVC == ePVC_Duoi)
				{
					mDangDungTuNhienRoi = false;
					break;
				}
				break;
			}
		}
	}
#pragma endregion
}

void XMan::XuLyBanPhim(std::map<int, bool> in_Keys)
{
	mKeys = in_Keys;

	switch (mTrangThai)
	{
#pragma region DUNG IM
	case eTT_DungIm:
		if (!in_Keys[VK_RIGHT] || !in_Keys[VK_LEFT])
		{
			if (in_Keys[VK_RIGHT] && !mCoChuongNgaiVatPhai)
			{
				mVanToc = Vec2(mVanTocChayToiDa, 0.0f);
				mLatHinh = false;
				ChuanBiChay();
			}
			if (in_Keys[VK_LEFT] && !mCoChuongNgaiVatTrai)
			{
				mVanToc = Vec2(-mVanTocChayToiDa, 0.0f);
				mLatHinh = true;
				ChuanBiChay();
			}
		}
		if (in_Keys[JUMP_BUTTON] && mChoPhepNhay)
		{
			Nhay();
		}
		if (!in_Keys[JUMP_BUTTON])
		{
			mChoPhepNhay = true;
		}
		if (in_Keys[PUSH_BUTTON] && mChoPhepLuot)
		{
			if (!mLatHinh)
			{
				mVanToc.x = mVanTocChayToiDa + mVanTocCongThem;
				Luot();
			}
			else
			{
				mVanToc.x = -(mVanTocChayToiDa + mVanTocCongThem);
				Luot();
			}
		}
		if (!in_Keys[PUSH_BUTTON])
		{
			mChoPhepLuot = true;
		}

		break;
#pragma endregion

#pragma region CHAY
	case eTT_Chay:
		if ((!in_Keys[VK_LEFT] && mLatHinh) ||
			(!in_Keys[VK_RIGHT] && !mLatHinh) ||
			(in_Keys[VK_LEFT] && in_Keys[VK_RIGHT]))
		{
			DungIm();
		}
		if (in_Keys[JUMP_BUTTON] && mChoPhepNhay)
		{
			Nhay();
		}
		if (!in_Keys[JUMP_BUTTON])
		{
			mChoPhepNhay = true;
		}
		if (in_Keys[PUSH_BUTTON] && mChoPhepLuot)
		{
			if (!mLatHinh)
			{
				mVanToc.x = mVanTocChayToiDa + mVanTocCongThem;
				Luot();
			}
			else
			{
				mVanToc.x = -(mVanTocChayToiDa + mVanTocCongThem);
				Luot();
			}
		}

		if (!in_Keys[PUSH_BUTTON])
		{
			mChoPhepLuot = true;
		}
		break;
#pragma endregion

#pragma region ROI
	case eTT_Roi:
		if (in_Keys[VK_LEFT] && in_Keys[VK_RIGHT])
		{
			mVanToc.x = 0.0f;
			return;
		}
		if ((!in_Keys[VK_LEFT] && mLatHinh) ||
			(!in_Keys[VK_RIGHT] && !mLatHinh))
		{
			mVanToc.x = 0.0f;
		}
		if (in_Keys[VK_LEFT])
		{
			mLatHinh = true;
			mVanToc.x = -(mVanTocChayToiDa + mDuocTangTocLucDangBay * mVanTocCongThem);
			if (mCoChuongNgaiVatTrai)
			{
				Truot();
			}
		}
		if (in_Keys[VK_RIGHT])
		{
			mLatHinh = false;
			mVanToc.x = (mVanTocChayToiDa + mDuocTangTocLucDangBay * mVanTocCongThem);
			if (mCoChuongNgaiVatPhai)
			{
				Truot();
			}
		}
		break;
#pragma endregion

#pragma region TIEP DAT
	case eTT_TiepDat:
		if (in_Keys[VK_LEFT] && in_Keys[VK_RIGHT])
		{
			mVanToc.x = 0.0f;
			return;
		}
		if ((!in_Keys[VK_LEFT] && mLatHinh) ||
			(!in_Keys[VK_RIGHT] && !mLatHinh))
		{
			mVanToc.x = 0.0f;
		}
		if (in_Keys[VK_LEFT])
		{
			mLatHinh = true;
			mVanToc.x = -mVanTocChayToiDa;
		}
		if (in_Keys[VK_RIGHT])
		{
			mLatHinh = false;
			mVanToc.x = mVanTocChayToiDa;
		}

		if (in_Keys[JUMP_BUTTON] && mChoPhepNhay)
		{
			Nhay();
		}
		if (!in_Keys[JUMP_BUTTON])
		{
			mChoPhepNhay = true;
		}

		if (in_Keys[PUSH_BUTTON] && mChoPhepLuot)
		{
			if (!mLatHinh)
			{
				mVanToc.x = mVanTocChayToiDa + mVanTocCongThem;
				Luot();
			}
			else
			{
				mVanToc.x = - (mVanTocChayToiDa + mVanTocCongThem);
				Luot();
			}
		}
		if (!in_Keys[PUSH_BUTTON])
		{
			mChoPhepLuot = true;
		}
		break;
#pragma endregion

#pragma region CHUAN BI CHAY
	case eTT_ChuanBiChay:
		if (in_Keys[VK_LEFT] && in_Keys[VK_RIGHT])
		{
			mVanToc.x = 0.0f;
			return;
		}
		if ((!in_Keys[VK_LEFT] && mLatHinh) ||
			(!in_Keys[VK_RIGHT] && !mLatHinh))
		{
			mVanToc.x = 0.0f;
		}
		if (in_Keys[VK_LEFT])
		{
			mLatHinh = true;
			mVanToc.x = -mVanTocChayToiDa;
		}
		if (in_Keys[VK_RIGHT])
		{
			mLatHinh = false;
			mVanToc.x = mVanTocChayToiDa;
		}
		if (in_Keys[JUMP_BUTTON] && mChoPhepNhay)
		{
			Nhay();
		}
		if (!in_Keys[JUMP_BUTTON])
		{
			mChoPhepNhay = true;
		}
		if (in_Keys[PUSH_BUTTON] && mChoPhepLuot)
		{
			if (!mLatHinh)
			{
				mVanToc.x = mVanTocChayToiDa + mVanTocCongThem;
				Luot();
			}
			else
			{
				mVanToc.x = - (mVanTocChayToiDa + mVanTocCongThem);
				Luot();
			}
		}
		if (!in_Keys[PUSH_BUTTON])
		{
			mChoPhepLuot = true;
		}
		break;
#pragma endregion

#pragma region NHAY
	case eTT_Nhay:
		if (in_Keys[VK_LEFT] && in_Keys[VK_RIGHT])
		{
			mVanToc.x = 0.0f;
			return;
		}
		if ((!in_Keys[VK_LEFT] && mLatHinh) ||
			(!in_Keys[VK_RIGHT] && !mLatHinh))
		{
			mVanToc.x = 0.0f;
		}
		if (in_Keys[VK_LEFT])
		{
			mLatHinh = true;
			mVanToc.x = -(mVanTocChayToiDa + mDuocTangTocLucDangBay * mVanTocCongThem);
		}
		if (in_Keys[VK_RIGHT])
		{
			mLatHinh = false;
			mVanToc.x = mVanTocChayToiDa + mDuocTangTocLucDangBay * mVanTocCongThem;
		}
		break;
#pragma endregion

#pragma region LUOT
	case eTT_Luot:
		if (!in_Keys[PUSH_BUTTON])
		{
			DungIm();
		}
		if (mDangDungTuNhienRoi)
		{
			Roi();
		}
		if (in_Keys[JUMP_BUTTON])
		{
			Nhay();
		}
		break;
#pragma endregion

#pragma region TRUOT
	case eTT_Truot:
		if (!in_Keys[VK_RIGHT] && !mLatHinh)
		{
			mLatHinh = true;
			mToaDo.x -= 2.0f;
			Roi();
			mVanToc.y = mVanTocTruot;
		}
		else 
		if (!in_Keys[VK_LEFT] && mLatHinh)
		{
			mLatHinh = false;
			Roi();
			mVanToc.y = mVanTocTruot;
		}
		if (!in_Keys[JUMP_BUTTON])
		{
			mChoPhepNhay = true;
		}
		if ((in_Keys[JUMP_BUTTON]) && !mLatHinh && mChoPhepNhay) // XMan nhìn sang Trái
		{
			if (in_Keys[PUSH_BUTTON])
			{
				mDuocTangTocLucDangBay = true;
			}
			mChoPhepNhay = false;
			BatRa();
			mVanToc.x = -(mVanTocChayToiDa + mDuocTangTocLucDangBay * mVanTocCongThem);
		}
		if ((in_Keys[JUMP_BUTTON]) && mLatHinh && mChoPhepNhay) // XMan nhìn sang Phải
		{
			if (in_Keys[PUSH_BUTTON])
			{
				mDuocTangTocLucDangBay = true;
			}
			mChoPhepNhay = false;
			BatRa();
			mVanToc.x = (mVanTocChayToiDa + mDuocTangTocLucDangBay * mVanTocCongThem);
		}
		break;

#pragma endregion

	default:
		break;
	}
}

void XMan::LoadHinhAnhVao()
{
	std::vector<ThongTinFrame> lDSTTFrame;

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(Vec2(226.0f, 29.0f), 30, 34, 3.5f));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(261.0f, 29.0f), 30, 34, 0.25f));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(295.0f, 29.0f), 30, 34, 0.25f));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(261.0f, 29.0f), 30, 34, 0.25f));
	mHH_DungIm = new HoatHinh("Resources_X3/XMan/XMan_1.png", lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(Vec2(106.0f, 106.0f), 30, 36, 999.9f));
	mHH_ChuanBiChay = new HoatHinh("Resources_X3/XMan/XMan.png", lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(Vec2(137.0f, 105.0f), 20, 36, 0.045f));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(157.0f, 105.0f), 24, 36, 0.045f));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(181.0f,	105.0f), 32, 36, 0.045f));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(213.0f,	105.0f), 34, 36, 0.045f));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(247.0f,	105.0f), 28, 36, 0.045f));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(276.0f,	105.0f), 22, 36, 0.045f));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(298.0f,	105.0f), 28, 36, 0.045f));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(327.0f,	105.0f), 30, 36, 0.045f));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(357.0f,	105.0f), 34, 36, 0.045f));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(391.0f,	105.0f), 30, 36, 0.045f));
	mHH_Chay = new HoatHinh("Resources_X3/XMan/XMan.png", lDSTTFrame);

	lDSTTFrame.clear();
	//lDSTTFrame.push_back(ThongTinFrame(Vec2(202.0f, 63.0f), 24, 38, 0.05f));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(230.0f, 59.0f), 16, 42, 0.15f));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(252.0f, 52.0f), 20, 48, 999.9f));
	mHH_Nhay = new HoatHinh("Resources_X3/XMan/XMan.png", lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(Vec2(274.0f, 59.0f), 24, 42, 0.1f));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(299.0f, 58.0f), 28, 42, 999.9f));
	mHH_Roi = new HoatHinh("Resources_X3/XMan/XMan.png", lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(Vec2(331.0f, 62.0f), 24, 38, 0.05f));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(356.0f, 68.0f), 30, 32, 999.9f));
	mHH_TiepDat = new HoatHinh("Resources_X3/XMan/XMan.png", lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(Vec2(285.0f, 154.0f), 28, 36, 0.05f));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(317.0f, 155.0f), 44, 34, 999.9f));
	mHH_Luot = new HoatHinh("Resources_X3/XMan/XMan.png", lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(Vec2(115.0f, 526.0f), 28, 44, 0.1f));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(144.0f, 527.0f), 28, 48, 999.9f));
	mHH_Truot = new HoatHinh("Resources_X3/XMan/XMan.png", lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(Vec2(88.0f, 527.0f), 26, 42, 0.03f));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(177.0f, 530.0f), 30, 40, 0.03f));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(207.0f, 525.0f), 28, 48, 999.9f));
	mHH_BatRa = new HoatHinh("Resources_X3/XMan/XMan.png", lDSTTFrame);
}

void XMan::DungIm()
{
	mTrangThai = eTT_DungIm;
	mHH_HienTai = mHH_DungIm;
	mHH_HienTai->Remake();
	mVanToc = Vec2(0.0f, 0.0f);
	mDuocTangTocLucDangBay = false;
}

void XMan::ChuanBiChay()
{
	mTrangThai = eTT_ChuanBiChay;
	mHH_HienTai = mHH_ChuanBiChay;
	mHH_HienTai->Remake();
	mTG_DemChuanBiChay = 0.0f;
}


void XMan::Chay()
{
	mTrangThai = eTT_Chay;
	mHH_HienTai = mHH_Chay;
	mHH_HienTai->Remake();
}

void XMan::Nhay()
{
	mVanToc.y = -mVanTocRoiToiDa;
	mTrangThai = eTT_Nhay;
	mHH_HienTai = mHH_Nhay;
	mHH_HienTai->Remake();
	mChoPhepNhay = false;
}

void XMan::Roi()
{
	mVanToc.y = 0;
	mTrangThai = eTT_Roi;
	mHH_HienTai = mHH_Roi;
	mHH_HienTai->Remake();
	GAMELOG("ROI");
}

void XMan::TiepDat()
{
	mTrangThai = eTT_TiepDat;
	mHH_HienTai = mHH_TiepDat;
	mHH_HienTai->Remake();
	mTG_DemTiepDat = 0.0f;
	mDuocTangTocLucDangBay = false;
}

void XMan::Luot()
{
	mTrangThai = eTT_Luot;
	mHH_HienTai = mHH_Luot;
	mHH_HienTai->Remake();
	mTG_DemLuot = 0.0f;
	mChoPhepLuot = false;
	mDuocTangTocLucDangBay = true;
}

void XMan::Truot()
{
	mVanToc = Vec2(0.0f, mVanTocTruot);
	mTrangThai = eTT_Truot;
	mHH_HienTai = mHH_Truot;
	mHH_HienTai->Remake();
	mDuocTangTocLucDangBay = false;
}

void XMan::BatRa()
{
	mVanToc.y = -mVanTocRoiToiDa;
	mTrangThai = eTT_BatRa;
	mHH_HienTai = mHH_BatRa;
	mHH_HienTai->Remake();
	mTG_DemBatRa = 0.0f;
}



