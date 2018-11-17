#include "XMan.h"
#include <vector>
#include "VaChamGame.h"
#include "GameLog.h"

XMan::XMan(const Vec2& in_ToaDo)
	:DoiTuong(in_ToaDo, Vec2(), 22, 32)
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
}

void XMan::CapNhat(float in_tg)
{
	mHH_HienTai->CapNhat(in_tg);
	mToaDo.x += mVanToc.x * in_tg;
	mToaDo.y += mVanToc.y * in_tg;

	switch (mTrangThai)
	{
	case eTT_ChuanBiChaySangPhai:
		mTG_DemChuanBiChay += in_tg;
		if (mTG_DemChuanBiChay >= mTG_ChuanBiChay)
		{
			ChaySangPhai();
		}
		if (mDangDungTuNhienRoi == true)
		{
			Roi();
		}
		break;
	case eTT_ChuanBiChaySangTrai:
		mTG_DemChuanBiChay += in_tg;
		if (mTG_DemChuanBiChay >= mTG_ChuanBiChay)
		{
			ChaySangTrai();
		}
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
	case eTT_DungIm:
	case eTT_ChaySangPhai:
	case eTT_ChaySangTrai:
		if (mDangDungTuNhienRoi == true)
		{
			Roi();
		}
		break;
	default:
		break;
	}

	mDangDungTuNhienRoi = true;
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
				GAMELOG("VA CHAM");
				if (mTrangThai == eTT_Roi)
				{
					TiepDat();
					GAMELOG("TIEP DAT");
				}
				break;
			default:
				break;
			}
		}
	}

// XỬ LÝ BIẾN mDangDungTuNhienRoi
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
}

void XMan::XuLyBanPhim(std::map<int, bool> in_Keys)
{
	mKeys = in_Keys;

	switch (mTrangThai)
	{
	case eTT_DungIm:
		if (in_Keys[VK_RIGHT] && in_Keys[VK_LEFT])
		{
			if (mLatHinh)
			{
				ChuanBiChaySangTrai();
			}
			else
			{
				ChuanBiChaySangPhai();
			}
		}
		else
		{
			if (in_Keys[VK_RIGHT])
			{
				ChuanBiChaySangPhai();
			}
			if (in_Keys[VK_LEFT])
			{
				ChuanBiChaySangTrai();
			}
		}
		if (in_Keys['C'] && mChoPhepNhay)
		{
			Nhay();
		}
		break;
	case eTT_ChaySangPhai:
		if (!in_Keys[VK_RIGHT])
		{
			DungIm();
		}
		if (in_Keys['C'] && mChoPhepNhay)
		{
			Nhay();
		}
		break;
	case eTT_ChaySangTrai:
		if (!in_Keys[VK_LEFT])
		{
			DungIm();
		}
		if (in_Keys['C'] && mChoPhepNhay)
		{
			Nhay();
		}
		break;
	case eTT_Nhay:
	case eTT_Roi:
	case eTT_TiepDat:
		if (in_Keys[VK_LEFT] && mVanToc.x == 0.0f)
		{
			mLatHinh = true;
			mVanToc.x = -mVanTocChayToiDa;
		}
		if (!in_Keys[VK_LEFT] && mLatHinh)
		{
			mVanToc.x = 0.0f;
		}
		if (in_Keys[VK_RIGHT] && mVanToc.x == 0.0f)
		{
			mLatHinh = false;
			mVanToc.x = mVanTocChayToiDa;
		}
		if (!in_Keys[VK_RIGHT] && !mLatHinh)
		{
			mVanToc.x = 0.0f;
		}
		break;
	default:
		break;
	}

	switch (mTrangThai)
	{
	case eTT_DungIm:
	case eTT_ChaySangPhai:
	case eTT_ChaySangTrai:
	case eTT_ChuanBiChaySangPhai:
	case eTT_ChuanBiChaySangTrai:
	case eTT_TiepDat:
		if (!in_Keys['C'])
		{
			mChoPhepNhay = true;
		}
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
	lDSTTFrame.push_back(ThongTinFrame(Vec2(252.0f, 54.0f), 20, 46, 999.9f));
	mHH_Nhay = new HoatHinh("Resources_X3/XMan/XMan.png", lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(Vec2(274.0f, 59.0f), 24, 42, 0.1f));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(299.0f, 58.0f), 28, 42, 999.9f));
	mHH_Roi = new HoatHinh("Resources_X3/XMan/XMan.png", lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(Vec2(331.0f, 62.0f), 24, 38, 0.05f));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(356.0f, 68.0f), 30, 32, 999.9f));
	mHH_TiepDat = new HoatHinh("Resources_X3/XMan/XMan.png", lDSTTFrame);
}

void XMan::DungIm()
{
	mTrangThai = eTT_DungIm;
	mHH_HienTai = mHH_DungIm;
	mHH_HienTai->Remake();
	mVanToc = Vec2(0.0f, 0.0f);
}

void XMan::ChuanBiChaySangTrai()
{
	mTrangThai = eTT_ChuanBiChaySangTrai;
	mHH_HienTai = mHH_ChuanBiChay;
	mHH_HienTai->Remake();
	mVanToc = Vec2(-mVanTocChayToiDa, 0.0f);
	mTG_DemChuanBiChay = 0.0f;
	mLatHinh = true;
}

void XMan::ChuanBiChaySangPhai()
{
	mTrangThai = eTT_ChuanBiChaySangPhai;
	mHH_HienTai = mHH_ChuanBiChay;
	mHH_HienTai->Remake();
	mVanToc = Vec2(mVanTocChayToiDa, 0.0f);
	mTG_DemChuanBiChay = 0.0f;
	mLatHinh = false;
}

void XMan::ChaySangTrai()
{
	mLatHinh = true;
	mVanToc = Vec2(-mVanTocChayToiDa, 0.0f);
	mTrangThai = eTT_ChaySangTrai;
	mHH_HienTai = mHH_Chay;
	mHH_HienTai->Remake();
}

void XMan::ChaySangPhai()
{
	mLatHinh = false;
	mVanToc = Vec2(mVanTocChayToiDa, 0.0f);
	mTrangThai = eTT_ChaySangPhai;
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
}



