#include "XMan.h"
#include <vector>
#include "VaChamGame.h"
#include "GameLog.h"
#include "Camera.h"

XMan::XMan(const Vec2& in_ToaDo)
	:DoiTuong(in_ToaDo, Vec2(), 18, 32)
{
	DoiTuong::mLoaiDoiTuong = eLDT_XMan;

	for (int i = 0; i < mSoLuongBui; i++)
	{
		mDS_BuiKhiLuot[i] = new BuiKhiLuot(Vec2());
	}

	mHieuUngLuot = new HieuUngLuot();
	mHieuUngBatRa = new HieuUngBatRa();

	for (int i = 0; i < mSoLuongDanLv1; i++)
	{
		mDS_DanLv1[i] = new DanLv1();
	}

	mDanLv2 = new DanLv2();

	LoadHinhAnhVao();

	Roi();
}


XMan::~XMan()
{

	for (int i = 0; i < mSoLuongDanLv1; i++)
	{
		if (mDS_DanLv1[i])
			delete mDS_DanLv1[i];
	}

	if (mHH_DungIm)
	{
		delete mHH_DungIm;
	}
	if (mHH_DungIm_Ban)
	{
		delete mHH_DungIm_Ban;
	}

	if (mHH_ChuanBiChay)
	{
		delete mHH_ChuanBiChay;
	}
	if (mHH_ChuanBiChay_Ban)
	{
		delete mHH_ChuanBiChay_Ban;
	}

	if (mHH_Chay)
	{
		delete mHH_Chay;
	}
	if (mHH_Chay_Ban)
	{
		delete mHH_Chay_Ban;
	}

	if (mHH_Nhay)
	{
		delete mHH_Nhay;
	}
	if (mHH_Nhay_Ban)
	{
		delete mHH_Nhay_Ban;
	}
	
	if (mHH_TiepDat)
	{
		delete mHH_TiepDat;
	}
	if (mHH_TiepDat_Ban)
	{
		delete mHH_TiepDat_Ban;
	}

	if (mHH_Roi)
	{
		delete mHH_Roi;
	}
	if (mHH_Roi_Ban)
	{
		delete mHH_Roi_Ban;
	}

	if (mHH_Luot)
	{
		delete mHH_Luot;
	}
	if (mHH_Luot_Ban)
	{
		delete mHH_Luot_Ban;
	}

	if (mHH_Truot)
	{
		delete mHH_Truot;
	}
	if (mHH_Truot_Ban)
	{
		delete mHH_Truot_Ban;
	}

	if (mHH_BatRa)
	{
		delete mHH_BatRa;
	}
	if (mHH_BatRa_Ban)
	{
		delete mHH_BatRa_Ban;
	}

	for (int i = 0; i < mSoLuongBui; i++)
	{
		if (mDS_BuiKhiLuot[i])
		{
			delete mDS_BuiKhiLuot[i];
		}
	}
	if (mHieuUngBatRa)
		delete mHieuUngBatRa;
	if (mHieuUngLuot)
		delete mHieuUngLuot;
}

void XMan::CapNhat(float in_tg)
{

	if (mTG_DemTichDan > mTG_TichDanLv2)
	{
		mTimeCount_ChangeShining += in_tg;
		if (mIsShining)
		{
			if (mTimeCount_ChangeShining > mTimeChangeShining)
			{
				mTimeCount_ChangeShining = 0.0f;

				mIsShining = false;
			}
		}

		if (!mIsShining)
		{
			if (mTimeCount_ChangeShining > 1.5f * mTimeChangeShining)
			{
				mTimeCount_ChangeShining = 0.0f;

				mIsShining = true;
			}
		}
	}
	else
	{
		mIsShining = false;
	}

	if (mToaDo.x < Camera::mGioiHanTrai + float(mChieuRong / 2))
		mToaDo.x = Camera::mGioiHanTrai + float(mChieuRong / 2);

	if (mToaDo.x > Camera::mGioiHanPhai - float(mChieuRong / 2))
		mToaDo.x = Camera::mGioiHanPhai - float(mChieuRong / 2);

	mTimes = in_tg;
	mHH_HienTai->CapNhat(in_tg);
	mToaDo.x += mVanToc.x * in_tg;
	mToaDo.y += mVanToc.y * in_tg;

	switch (mTrangThai)
	{
	case eTT_DungIm:
		CapNhat_DungIm();
		break;

	case eTT_ChuanBiChay:
		CapNhat_ChuanBiChay(in_tg);
		break;

	case eTT_Chay:
		CapNhat_Chay();
		break;

	case eTT_TiepDat:
		CapNhat_TiepDat(in_tg);
		break;

	case eTT_Nhay:
		CapNhat_Nhay(in_tg);
		break;

	case eTT_Roi:
		CapNhat_Roi(in_tg);
		break;

	case eTT_Luot:
		CapNhat_Luot(in_tg);
		break;

	case eTT_BatRa:
		CapNhat_BatRa(in_tg);
		break;

	case eTT_Truot:
		CapNhat_Truot(in_tg);
		break;

	default:
		break;
	}

	mDangDungTuNhienRoi = true;
	mCoChuongNgaiVatTrai = mCoChuongNgaiVatPhai = false;

	//Cap Nhat Bui
	for (int i = 0; i < mSoLuongBui; i++)
	{
		mDS_BuiKhiLuot[i]->CapNhat(in_tg);
	}
	mHieuUngLuot->CapNhat(in_tg);

	if (mTrangThai != eTT_Luot)
	{
		mHieuUngLuot->BienMat();
	}

	for (int i = 0; i < mSoLuongDanLv1; i++)
	{
		mDS_DanLv1[i]->CapNhat(in_tg);
	}

	mHieuUngBatRa->CapNhat(in_tg);

	mDanLv2->CapNhat(in_tg);
}

void XMan::Ve(const Vec2 & in_DoDoi)
{
	mHH_HienTai->set_LatTheoChieuNgang(mLatHinh);
	mHH_HienTai->set_ToaDo(mToaDo);
	mHH_HienTai->set_DoDoi(in_DoDoi);
	mHH_HienTai->Ve();

	if (mIsShining)
	{
		DrawAnimationShining(in_DoDoi);
	}
	//Vẽ đối tượng Bụi, LayDa
	for (int i = 0; i < mSoLuongBui; i++)
	{
		mDS_BuiKhiLuot[i]->Ve(in_DoDoi);
	}

	mHieuUngLuot->Ve(in_DoDoi);

	mHieuUngBatRa->Ve(in_DoDoi);

	for (int i = 0; i < mSoLuongDanLv1; i++)
	{
		mDS_DanLv1[i]->Ve(in_DoDoi);
	}


	mDanLv2->Ve(in_DoDoi);

}

void XMan::XuLyVaCham(DoiTuong * in_DoiTuong)
{
	if (in_DoiTuong->get_LoaiDoiTuong() == eLDT_DoiTuongTinh)
	{
		eKetQuaVaCham lKQVC = VaChamGame::get_KetQuaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan());

		if (lKQVC.eKQVC_DaVaCham)
		{
			ePhiaVaCham lPVC = VaChamGame::get_PhiaVaCham(this, lKQVC);
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
				if (mTrangThai == eTT_Nhay || mTrangThai == eTT_BatRa)
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

		for (int i = 0; i < mSoLuongDanLv1; i++)
		{
			if (mDS_DanLv1[i]->get_TrangThai() != eTTDan_DaBiPhaHuy)
				mDS_DanLv1[i]->XuLyVaCham(in_DoiTuong);
		}

		mDanLv2->XuLyVaCham(in_DoiTuong);
	}

#pragma region XỬ LÝ BIẾN mDangDungTuNhienRoi
	if (mDangDungTuNhienRoi == true)
	{
		if (in_DoiTuong->get_LoaiDoiTuong() == eLDT_DoiTuongTinh)
		{
			HCN lHCNGioiHanMoRongDay = get_HCNGioiHan();
			lHCNGioiHanMoRongDay.Duoi += 2;

			eKetQuaVaCham lKQVC = VaChamGame::get_KetQuaVaCham(lHCNGioiHanMoRongDay, in_DoiTuong->get_HCNGioiHan());


			if (lKQVC.eKQVC_DaVaCham == true)
			{
				ePhiaVaCham lPVC = VaChamGame::get_PhiaVaCham(this, lKQVC);

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
#pragma endregion
}

void XMan::XuLyBanPhim(std::map<int, bool> in_Keys)
{
	mKeys = in_Keys;

	switch (mTrangThai)
	{
	case eTT_DungIm:
		XuLyBanPhim_DungIm(in_Keys);
		break;

	case eTT_Chay:
		XuLyBanPhim_Chay(in_Keys);
		break;

	case eTT_Roi:
		XuLyBanPhim_Roi(in_Keys);
		break;

	case eTT_TiepDat:
		XuLyBanPhim_TiepDat(in_Keys);
		break;

	case eTT_ChuanBiChay:
		XuLyBanPhim_ChuanBiChay(in_Keys);
		break;

	case eTT_Nhay:
		XuLyBanPhim_Nhay(in_Keys);
		break;

	case eTT_Luot:
		XuLyBanPhim_Luot(in_Keys);
		break;

	case eTT_Truot:
		XuLyBanPhim_Truot(in_Keys);
		break;

	default:
		break;
	}

	XuLyBanPhim_BanDan(in_Keys);
}

void XMan::LoadHinhAnhVao()
{
	std::vector<ThongTinFrame> lDSTTFrame;

#pragma region DUNG_IM
	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(Vec2(323.0f, 17.0f), 30, 34, 3.5f));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(357.0f, 17.0f), 30, 34, 0.25f));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(391.0f, 17.0f), 30, 34, 0.25f));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(357.0f, 17.0f), 30, 34, 0.25f));
	mHH_DungIm = new HoatHinh("Resources_X3/XMan/XMan.png", lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 30, 34, 0.15f, HCN(133, 163, 66, 100)));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 30, 34, 0.15f, HCN(168, 197, 66, 100)));
	mHH_DungIm_Ban = new HoatHinh("Resources_X3/XMan/XMan.png", lDSTTFrame);
#pragma endregion

#pragma region CHUAN_BI_CHAY
	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(Vec2(106.0f, 106.0f), 30, 36, 999.9f));
	mHH_ChuanBiChay = new HoatHinh("Resources_X3/XMan/XMan.png", lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(Vec2(61.0f, 192.0f), 30, 34, 999.9f, HCN(61, 96, 192, 226)));
	mHH_ChuanBiChay_Ban = new HoatHinh("Resources_X3/XMan/XMan.png", lDSTTFrame);
#pragma endregion

#pragma region CHAY
	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 18, 38, 0.05f, HCN(137, 157, 105, 141))); //1 
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 26, 38, 0.05f, HCN(157, 181, 105, 141))); //2
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 32, 38, 0.05f, HCN(181, 212, 105, 141))); //3 
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 36, 38, 0.05f, HCN(213, 247, 105, 141))); //4
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 28, 38, 0.05f, HCN(247, 275, 105, 143))); //5
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 22, 38, 0.05f, HCN(276, 298, 105, 141))); //6
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 26, 38, 0.05f, HCN(298, 326, 105, 141))); //7
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 26, 38, 0.05f, HCN(327, 357, 105, 141))); //8
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 34, 38, 0.05f, HCN(357, 391, 105, 141))); //9
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 30, 38, 0.05f, HCN(391, 421, 105, 141))); //10
	mHH_Chay = new HoatHinh("Resources_X3/XMan/XMan.png", lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 18, 34, 0.05f, HCN(97, 126, 193, 227))); //1 
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 24, 34, 0.05f, HCN(126, 158, 192, 227))); //2
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 30, 34, 0.05f, HCN(158, 193, 193, 227))); //3 
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 36, 32, 0.05f, HCN(194, 232, 194, 227))); //4
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 28, 32, 0.05f, HCN(233, 267, 194, 227))); //5
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 22, 34, 0.05f, HCN(267, 298, 193, 227))); //6
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 26, 34, 0.05f, HCN(298, 331, 192, 227))); //7
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 30, 34, 0.05f, HCN(331, 366, 193, 227))); //8
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 34, 32, 0.05f, HCN(367, 404, 194, 227))); //9
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 30, 32, 0.05f, HCN(404, 439, 194, 227))); //10
	mHH_Chay_Ban = new HoatHinh("Resources_X3/XMan/XMan.png", lDSTTFrame);
#pragma endregion

#pragma region NHAY
	lDSTTFrame.clear();
	//lDSTTFrame.push_back(ThongTinFrame(Vec2(202.0f, 63.0f), 24, 36, 0.04f, HCN(202, 226, 63, 101)));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(230.0f, 59.0f), 12, 38, 0.08f /*0.9f*/, HCN(230, 246, 59, 101)));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(252.0f, 52.0f), 16, 48, 999.9f, HCN(252, 272, 52, 100)));
	mHH_Nhay = new HoatHinh("Resources_X3/XMan/XMan.png", lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 10, 38, 0.08f/*0.9f*/, HCN(97, 121, 148, 189)));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 16, 44, 999.9f, HCN(121, 148, 143, 189)));
	mHH_Nhay_Ban = new HoatHinh("Resources_X3/XMan/XMan.png", lDSTTFrame);
#pragma endregion

#pragma region ROI
	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 26, 36, 0.08f, HCN(274, 298, 59, 101)));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 30, 36, 999.9f, HCN(299, 327, 58, 100)));
	mHH_Roi = new HoatHinh("Resources_X3/XMan/XMan.png", lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 26, 36, 0.08f, HCN(149, 180, 148, 189)));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 24, 36, 999.0f, HCN(181, 212, 147, 189)));
	mHH_Roi_Ban = new HoatHinh("Resources_X3/XMan/XMan.png", lDSTTFrame);
#pragma endregion

#pragma region TIEP_DAT
	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(Vec2(331.0f, 62.0f), 20, 32, 0.06f, HCN(331, 355, 62, 100)));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(356.0f, 68.0f), 30, 30, 999.9f, HCN(356, 386, 68, 100)));
	mHH_TiepDat = new HoatHinh("Resources_X3/XMan/XMan.png", lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 20, 32, 0.06f, HCN(213, 243, 151, 189)));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 30, 30, 999.9f, HCN(243, 279, 157, 189)));
	mHH_TiepDat_Ban = new HoatHinh("Resources_X3/XMan/XMan.png", lDSTTFrame);
#pragma endregion

#pragma region LUOT
	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 28, 36, 0.05f, HCN(285, 313, 154, 190)));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 44, 38, 999.9f, HCN(317, 361, 153, 189)));
	mHH_Luot = new HoatHinh("Resources_X3/XMan/XMan.png", lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 28, 28, 0.05f, HCN(361, 399, 158, 189)));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 44, 18, 999.9f, HCN(404, 453, 163, 189)));
	mHH_Luot_Ban = new HoatHinh("Resources_X3/XMan/XMan.png", lDSTTFrame);
#pragma endregion

#pragma region TRUOT
	lDSTTFrame.clear();
	//lDSTTFrame.push_back(ThongTinFrame(Vec2(115.0f, 526.0f), 28, 44, 0.11f));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(144.0f, 527.0f), 28, 48, 999.9f));
	mHH_Truot = new HoatHinh("Resources_X3/XMan/XMan.png", lDSTTFrame);

	lDSTTFrame.clear();
	//lDSTTFrame.push_back(ThongTinFrame(Vec2(), 38, 44, 0.11f, HCN(272, 304, 527, 570)));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 36, 48, 999.9f, HCN(310, 342, 526, 568)));
	mHH_Truot_Ban = new HoatHinh("Resources_X3/XMan/XMan.png", lDSTTFrame);
#pragma endregion

#pragma region BAT_RA
	lDSTTFrame.clear();
	//lDSTTFrame.push_back(ThongTinFrame(Vec2(88.0f, 527.0f), 26, 42, 0.03f));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(177.0f, 530.0f), 30, 42, 0.05f));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(207.0f, 525.0f), 28, 50, 999.9f));
	mHH_BatRa = new HoatHinh("Resources_X3/XMan/XMan.png", lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 30, 40, 0.06f, HCN(237, 268, 531, 569)));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 28, 40, 999.9f, HCN(379, 412, 529, 568)));
	mHH_BatRa_Ban = new HoatHinh("Resources_X3/XMan/XMan.png", lDSTTFrame);
#pragma endregion

	mAnimationShining = new HoatHinh("Resources_X3/XMan/XMan_1.png", lDSTTFrame, D3DCOLOR_XRGB(255, 255, 255));

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 2, 2, 0.2f, HCN(9, 10, 16, 17)));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 2, 2, 0.2f, HCN(5, 7, 5, 7)));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 2, 2, 0.2f, HCN(14, 16, 15, 17)));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 2, 2, 0.2f, HCN(5, 7, 5, 7)));
	lDSTTFrame.push_back(ThongTinFrame(Vec2(), 2, 2, 0.2f, HCN(5, 7, 5, 7)));
}

void XMan::DungIm()
{
	mTrangThai = eTT_DungIm;
	if (!mBanDan)
	{
		mHH_HienTai = mHH_DungIm;
	}
	else
	{
		mHH_HienTai = mHH_DungIm_Ban;
	}
	mHH_HienTai->Remake();
	mVanToc = Vec2(0.0f, 0.0f);
	mDuocTangTocLucDangBay = false;
}

void XMan::ChuanBiChay()
{
	mTrangThai = eTT_ChuanBiChay;
	if (mBanDan)
	{
		mHH_HienTai = mHH_ChuanBiChay_Ban;
	}
	else
	{
		mHH_HienTai = mHH_ChuanBiChay;
	}
	mHH_HienTai->Remake();
	mTG_DemChuanBiChay = 0.0f;
}

void XMan::Chay()
{
	mTrangThai = eTT_Chay;
	if (!mBanDan)
	{
		mHH_HienTai = mHH_Chay;
	}
	else
	{
		mHH_HienTai = mHH_Chay_Ban;
	}
	mHH_HienTai->Remake();
}

void XMan::Nhay()
{
	mVanToc.y = -mVanTocRoiToiDa;
	mTrangThai = eTT_Nhay;
	if (!mBanDan)
	{
		mHH_HienTai = mHH_Nhay;
	}
	else
	{
		mHH_HienTai = mHH_Nhay_Ban;
	}
	mHH_HienTai->Remake();
	mChoPhepNhay = false;
}

void XMan::Roi()
{
	mVanToc.y = 0;
	mTrangThai = eTT_Roi;
	if (!mBanDan)
	{
		mHH_HienTai = mHH_Roi;
	}
	else
	{
		mHH_HienTai = mHH_Roi_Ban;
	}
	mHH_HienTai->Remake();
	//GAMELOG("ROI");
}

void XMan::TiepDat()
{
	mTrangThai = eTT_TiepDat;
	if (!mBanDan)
	{
		mHH_HienTai = mHH_TiepDat;
	}
	else
	{
		mHH_HienTai = mHH_TiepDat_Ban;
	}
	mHH_HienTai->Remake();
	mTG_DemTiepDat = 0.0f;
	mDuocTangTocLucDangBay = false;
}

void XMan::Luot()
{
	mTrangThai = eTT_Luot;
	if (!mBanDan)
	{
		mHH_HienTai = mHH_Luot;
	}
	else
	{
		mHH_HienTai = mHH_Luot_Ban;
	}
	mHH_HienTai->Remake();
	mTG_DemLuot = 0.0f;
	mChoPhepLuot = false;
	mDuocTangTocLucDangBay = true;
	mTG_DemBui = mTG_Bui;

	if (!mLatHinh)
	{
		mHieuUngLuot->LatHinh(true);
		mHieuUngLuot->set_ToaDo(mToaDo + Vec2(-14.0f, 2.0f));
	}
	else
	{
		mHieuUngLuot->LatHinh(false);
		mHieuUngLuot->set_ToaDo(mToaDo + Vec2(14.0f, 2.0f));
	}

	mHieuUngLuot->Remake();
}

void XMan::Truot()
{
	mVanToc = Vec2(0.0f, 0.0f);
	mTrangThai = eTT_Truot;
	if (!mBanDan)
	{
		mHH_HienTai = mHH_Truot;
	}
	else
	{
		mHH_HienTai = mHH_Truot_Ban;
	}
	mHH_HienTai->Remake();
	mDuocTangTocLucDangBay = false;
	mTG_DemBamTuong = 0.0f;
	mTG_DemBui = 0.0f;
}

void XMan::BatRa()
{
	mVanToc.y = -mVanTocRoiToiDa;
	mTrangThai = eTT_BatRa;
	if (!mBanDan)
	{
		mHH_HienTai = mHH_BatRa;
	}
	else
	{
		mHH_HienTai = mHH_BatRa_Ban;
	}
	mHH_HienTai->Remake();
	mTG_DemBatRa = 0.0f;

	mHieuUngBatRa->LatHinh(mLatHinh);
	mHieuUngBatRa->set_ToaDo(mToaDo);
	mHieuUngBatRa->Remake();
}

void XMan::ChuyenHH_BanDan()
{
	int lViTri_Tam = mHH_HienTai->get_ViTri();
	float lThoiGian_Tam = mHH_HienTai->get_ThoiGian();

	switch (mTrangThai)
	{
	case eTT_ChuanBiChay:
		mHH_HienTai = mHH_ChuanBiChay_Ban;
		mHH_HienTai->Remake(lViTri_Tam, lThoiGian_Tam);
		break;

	case eTT_Chay:
		mHH_HienTai = mHH_Chay_Ban;
		mHH_HienTai->Remake(lViTri_Tam, lThoiGian_Tam);
		break;

	case eTT_Nhay:
		mHH_HienTai = mHH_Nhay_Ban;
		mHH_HienTai->Remake(lViTri_Tam, lThoiGian_Tam);
		break;

	case eTT_Roi:
		mHH_HienTai = mHH_Roi_Ban;
		mHH_HienTai->Remake(lViTri_Tam, lThoiGian_Tam);
		break;

	case eTT_TiepDat:
		mHH_HienTai = mHH_TiepDat_Ban;
		mHH_HienTai->Remake(lViTri_Tam, lThoiGian_Tam);
		break;

	case eTT_DungIm:
		mHH_HienTai = mHH_DungIm_Ban;
		mHH_HienTai->Remake();
		break;

	case eTT_Luot:
		mHH_HienTai = mHH_Luot_Ban;
		mHH_HienTai->Remake(lViTri_Tam, lThoiGian_Tam);
		break;

	case eTT_Truot:
		mHH_HienTai = mHH_Truot_Ban;
		mHH_HienTai->Remake(lViTri_Tam, lThoiGian_Tam);
		break;

	case eTT_BatRa:
		mHH_HienTai = mHH_BatRa_Ban;
		mHH_HienTai->Remake(lViTri_Tam, lThoiGian_Tam);
		break;

	default:
		break;
	}
}

void XMan::ChuyenHH_KoBanDan()
{
	int lViTri_Tam = mHH_HienTai->get_ViTri();
	float lThoiGian_Tam = mHH_HienTai->get_ThoiGian();

	switch (mTrangThai)
	{
	case eTT_ChuanBiChay:
		mHH_HienTai = mHH_ChuanBiChay;
		mHH_HienTai->Remake(lViTri_Tam, lThoiGian_Tam);
		break;

	case eTT_Chay:
		mHH_HienTai = mHH_Chay;
		mHH_HienTai->Remake(lViTri_Tam, lThoiGian_Tam);
		break;

	case eTT_Nhay:
		mHH_HienTai = mHH_Nhay;
		mHH_HienTai->Remake(lViTri_Tam, lThoiGian_Tam);
		break;

	case eTT_Roi:
		mHH_HienTai = mHH_Roi;
		mHH_HienTai->Remake(lViTri_Tam, lThoiGian_Tam);
		break;

	case eTT_TiepDat:
		mHH_HienTai = mHH_TiepDat;
		mHH_HienTai->Remake(lViTri_Tam, lThoiGian_Tam);
		break;

	case eTT_DungIm:
		mHH_HienTai = mHH_DungIm;
		mHH_HienTai->Remake();
		break;

	case eTT_Luot:
		mHH_HienTai = mHH_Luot;
		mHH_HienTai->Remake(lViTri_Tam, lThoiGian_Tam);
		break;

	case eTT_Truot:
		mHH_HienTai = mHH_Truot;
		mHH_HienTai->Remake(lViTri_Tam, lThoiGian_Tam);
		break;

	case eTT_BatRa:
		mHH_HienTai = mHH_BatRa;
		mHH_HienTai->Remake(lViTri_Tam, lThoiGian_Tam);
		break;

	default:
		break;
	}
}

void XMan::CapNhat_DungIm()
{
	if (mDangDungTuNhienRoi == true)
	{
		Roi();
	}
}

void XMan::CapNhat_ChuanBiChay(float in_tg)
{
	mTG_DemChuanBiChay += in_tg;
	if (mTG_DemChuanBiChay >= mTG_ChuanBiChay)
	{
		Chay();
	}
	if (mDangDungTuNhienRoi == true)
	{
		Roi();
	}
}

void XMan::CapNhat_Chay()
{
	if (mDangDungTuNhienRoi == true)
	{
		Roi();
	}
}

void XMan::CapNhat_TiepDat(float in_tg)
{
	mTG_DemTiepDat += in_tg;
	if (mTG_DemTiepDat >= mTG_TiepDat)
	{
		DungIm();
	}
}

void XMan::CapNhat_Nhay(float in_tg)
{
	mVanToc.y += mGiaTocTrongTruong * in_tg;
	if (!mKeys['C'])
	{
		mVanToc.y += mGiaTocTrongTruong * in_tg * 10;
	}
	if (mVanToc.y >= 0.0f)
	{
		Roi();
	}
}

void XMan::CapNhat_Roi(float in_tg)
{
	mVanToc.y += mGiaTocTrongTruong * in_tg;
	if (mVanToc.y > mVanTocRoiToiDa)
	{
		mVanToc.y = mVanTocRoiToiDa;
	}
}

void XMan::CapNhat_Luot(float in_tg)
{
	mTG_DemLuot += in_tg;
	mTG_DemBui += in_tg;
	if (mTG_DemBui >= mTG_Bui)
	{
		mTG_DemBui = 0.0f;
		for (int i = 0; i < mSoLuongBui; i++)
		{
			if (mDS_BuiKhiLuot[i]->get_BienMat())
			{
				if (!mLatHinh)
				{
					mDS_BuiKhiLuot[i]->set_ToaDo(mToaDo + Vec2(- float(mChieuRong / 2 + 3.0f), float(mChieuCao / 2) + 2.0f));
				}
				else
				{
					mDS_BuiKhiLuot[i]->set_ToaDo(mToaDo + Vec2(float(mChieuRong / 2 + 3.0f), float(mChieuCao / 2) + 2.0f));
				}
				mDS_BuiKhiLuot[i]->Remake();
				break;
			}
		}
	}

	if (mTG_DemLuot >= mTG_Luot)
	{
		DungIm();
	}
}

void XMan::CapNhat_BatRa(float in_tg)
{
	mVanToc.y += mGiaTocTrongTruong * in_tg;
	mTG_DemBatRa += in_tg;
	if (mTG_DemBatRa >= mTG_BatRa)
	{
		float lVanTocHienTai = mVanToc.y;
		Nhay();
		mHH_HienTai->Remake(1, 0.0f);
		mVanToc.y = lVanTocHienTai;
	}

}

void XMan::CapNhat_Truot(float in_tg)
{
	mVanToc.y += mGiaTocTrongTruong * in_tg / 2.0f;
	if (mVanToc.y > mVanTocTruotToiDa)
	{
		mVanToc.y = mVanTocTruotToiDa;
	}
	if (!mCoChuongNgaiVatTrai && mLatHinh)
	{
		Roi();
	}
	if (!mCoChuongNgaiVatPhai && !mLatHinh)
	{
		Roi();
	}
	mTG_DemBui += in_tg;
	if (mTG_DemBui >= mTG_Bui)
	{
		mTG_DemBui = 0.0f;
		for (int i = 0; i < mSoLuongBui; i++)
		{
			if (mDS_BuiKhiLuot[i]->get_BienMat())
			{
				if (mLatHinh)
				{
					mDS_BuiKhiLuot[i]->set_ToaDo(mToaDo + Vec2(- float(mChieuRong / 2 + 5.0f), float(mChieuCao / 2) - 5.0f));
				}
				else
				{
					mDS_BuiKhiLuot[i]->set_ToaDo(mToaDo + Vec2(float(mChieuRong / 2 + 5.0f), float(mChieuCao / 2) - 5.0f));
				}
				mDS_BuiKhiLuot[i]->Remake();
				break;
			}
		}
	}
}

void XMan::XuLyBanPhim_DungIm(std::map<int, bool> in_Keys)
{
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
			if (!mCoChuongNgaiVatPhai)
			{
				mVanToc.x = mVanTocChayToiDa + mVanTocCongThem;
				Luot();
			}
		}
		else
		{
			if (!mCoChuongNgaiVatTrai)
			{
				mVanToc.x = -(mVanTocChayToiDa + mVanTocCongThem);
				Luot();
			}
		}
	}
	if (!in_Keys[PUSH_BUTTON])
	{
		mChoPhepLuot = true;
	}
}

void XMan::XuLyBanPhim_Chay(std::map<int, bool> in_Keys)
{
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
}

void XMan::XuLyBanPhim_Roi(std::map<int, bool> in_Keys)
{
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
}

void XMan::XuLyBanPhim_TiepDat(std::map<int, bool> in_Keys)
{
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
		Chay();
	}
	if (in_Keys[VK_RIGHT])
	{
		mLatHinh = false;
		mVanToc.x = mVanTocChayToiDa;
		Chay();
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
}

void XMan::XuLyBanPhim_ChuanBiChay(std::map<int, bool> in_Keys)
{
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
			mVanToc.x = -(mVanTocChayToiDa + mVanTocCongThem);
			Luot();
		}
	}
	if (!in_Keys[PUSH_BUTTON])
	{
		mChoPhepLuot = true;
	}
}

void XMan::XuLyBanPhim_Nhay(std::map<int, bool> in_Keys)
{
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
}

void XMan::XuLyBanPhim_Luot(std::map<int, bool> in_Keys)
{
	if (!in_Keys[PUSH_BUTTON])
	{
		DungIm();
	}
	if (mDangDungTuNhienRoi)
	{
		mDuocTangTocLucDangBay = false;
		Roi();
	}
	if (in_Keys[JUMP_BUTTON])
	{
		Nhay();
	}
	if (in_Keys[VK_LEFT] && !mLatHinh ||
		in_Keys[VK_RIGHT] && mLatHinh)
	{
		Chay();
	}
}

void XMan::XuLyBanPhim_Truot(std::map<int, bool> in_Keys)
{
	if (!in_Keys[VK_RIGHT] && !mLatHinh)
	{
		mTG_DemBamTuong += mTimes;
		if (mTG_DemBamTuong >= mTG_BamTuong)
		{
			Roi();
			mLatHinh = true;
		}
	}
	if (!in_Keys[VK_LEFT] && mLatHinh)
	{
		mTG_DemBamTuong += mTimes;
		if (mTG_DemBamTuong >= mTG_BamTuong)
		{
			Roi();
			mLatHinh = false;
		}
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
}

void XMan::XuLyBanPhim_BanDan(std::map<int, bool> in_Keys)
{
	bool lBanDan_Tam = mBanDan;



	if (mBanDan)
	{
		mTG_DemBanDan += mTimes;
		if (mTG_DemBanDan >= mTG_BanDan)
		{
			mBanDan = false;
		}
	}
	if (in_Keys[FIRE_BUTTON] && mChoPhepBan)
	{
		mTG_DemBanDan = 0.0f;
		mBanDan = true;
		mChoPhepBan = false;

		// các đối tượng đạn bay ra
		BanRaVienDan();
	}

	if (in_Keys[FIRE_BUTTON])
	{
		mTG_DemTichDan += mTimes;
	}
	if (!in_Keys[FIRE_BUTTON])
	{
		mChoPhepBan = true;

		if (mTG_DemTichDan >= mTG_TichDanLv2)
		{
			mTG_DemBanDan = 0.0f;
			mBanDan = true;
			mChoPhepBan = false;

			BanDanLv2();
		}

		mTG_DemTichDan = 0.0f;


	}

	if (mBanDan && (lBanDan_Tam != mBanDan))
	{
		ChuyenHH_BanDan();
	}
	if (!mBanDan && (lBanDan_Tam != mBanDan))
	{
		ChuyenHH_KoBanDan();
	}
}

void XMan::BanRaVienDan()
{
	for (int i = 0; i < mSoLuongDanLv1; i++)
	{
		if (mDS_DanLv1[i]->get_TrangThai() == eTTDan_DaBiPhaHuy)
		{
			Vec2 lDoDoiDan = DoDoiDan();

			mDS_DanLv1[i]->set_ToaDo(mToaDo + lDoDoiDan);

			if (!mLatHinh)
			{
				mDS_DanLv1[i]->set_VanToc(Vec2(DanLv1::mVanTocDan, 0.0f));
			}
			else
			{
				mDS_DanLv1[i]->set_VanToc(Vec2(-DanLv1::mVanTocDan, 0.0f));
			}

			if (mTrangThai == eTT_Truot)
			{
				if (mLatHinh)
				{
					mDS_DanLv1[i]->set_VanToc(Vec2(DanLv1::mVanTocDan, 0.0f));
				}
				else
				{
					mDS_DanLv1[i]->set_VanToc(Vec2(-DanLv1::mVanTocDan, 0.0f));
				}
			}

			mDS_DanLv1[i]-> Remake();
			break;
		}
	}
}

Vec2 XMan::DoDoiDan() const
{
	Vec2 lDoDoi;

	if (mTrangThai == eTT_DungIm)
	{
		if (!mLatHinh)
		{
			lDoDoi = Vec2(16.0f, -1.0f);
		}
		else
		{
			lDoDoi = Vec2(-16.0f, -1.0f);
		}
	}
	else
	if (mTrangThai == eTT_Chay || mTrangThai == eTT_ChuanBiChay || mTrangThai ==  eTT_TiepDat)
	{
		if (!mLatHinh)
			lDoDoi = Vec2(21.0f, -3.0f);
		else
			lDoDoi = Vec2(-21.0f, -3.0f);
	}
	else
	if (mTrangThai == eTT_Luot)
	{
		if (!mLatHinh)
			lDoDoi = Vec2(28.0f, 2.0f);
		else
			lDoDoi = Vec2(-28.0f, 2.0f);
	}
	else
	if (mTrangThai == eTT_Nhay || mTrangThai == eTT_Roi)
	{
		if (!mLatHinh)
			lDoDoi = Vec2(20.0f, -6.0f);
		else
			lDoDoi = Vec2(-20.0f, -6.0f);
	}
	else
	if (mTrangThai == eTT_Truot)
	{
		if (mLatHinh)
		{
			lDoDoi = Vec2(20.0f, -4.0f);
		}
		else
		{
			lDoDoi = Vec2(-20.0f, -4.0f);
		}
	}
	else
	if (mTrangThai == eTT_BatRa)
	{
		if (!mLatHinh)
			lDoDoi = Vec2(21.0f, -8.0f);
		else
			lDoDoi = Vec2(-21.0f, -8.0f);
	}

	return lDoDoi;
}

void XMan::BanDanLv2()
{
	if (mDanLv2->get_TrangThai() == eTTDan_DaBiPhaHuy)
	{
		Vec2 lDoDoiDan = DoDoiDanLv2();

		mDanLv2->set_ToaDo(mToaDo + lDoDoiDan);

		if (!mLatHinh)
		{
			mDanLv2->set_VanToc(Vec2(DanLv2::mVanTocDan, 0.0f));
		}
		else
		{
			mDanLv2->set_VanToc(Vec2(-DanLv2::mVanTocDan, 0.0f));
		}
		mDanLv2->set_LatHinh(mLatHinh);

		if (mTrangThai == eTT_Truot)
		{
			if (mLatHinh)
			{
				mDanLv2->set_VanToc(Vec2(DanLv2::mVanTocDan, 0.0f));
			}
			else
			{
				mDanLv2->set_VanToc(Vec2(-DanLv2::mVanTocDan, 0.0f));
			}
			mDanLv2->set_LatHinh(!mLatHinh);
		}

		mDanLv2->Remake();
	}
}

Vec2 XMan::DoDoiDanLv2() const
{
	Vec2 lDoDoi;

	if (mTrangThai == eTT_DungIm)
	{
		if (!mLatHinh)
		{
			lDoDoi = Vec2(24.0f, -1.0f);
		}
		else
		{
			lDoDoi = Vec2(-24.0f, -1.0f);
		}
	}
	else
	if (mTrangThai == eTT_Chay || mTrangThai == eTT_ChuanBiChay || mTrangThai == eTT_TiepDat)
	{
		if (!mLatHinh)
			lDoDoi = Vec2(29.0f, -3.0f);
		else
			lDoDoi = Vec2(-29.0f, -3.0f);
	}
	else
	if (mTrangThai == eTT_Luot)
	{
		if (!mLatHinh)
			lDoDoi = Vec2(37.0f, 2.0f);
		else
			lDoDoi = Vec2(-37.0f, 2.0f);
	}
	else
	if (mTrangThai == eTT_Nhay || mTrangThai == eTT_Roi)
	{
		if (!mLatHinh)
			lDoDoi = Vec2(28.0f, -6.0f);
		else
			lDoDoi = Vec2(-28.0f, -6.0f);
	}
	else
	if (mTrangThai == eTT_Truot)
	{
		if (mLatHinh)
		{
			lDoDoi = Vec2(28.0f, 0.0f);
		}
		else
		{
			lDoDoi = Vec2(-28.0f, 0.0f);
		}
	}
	else
	if (mTrangThai == eTT_BatRa)
	{
		if (!mLatHinh)
			lDoDoi = Vec2(29.0f, -8.0f);
		else
			lDoDoi = Vec2(-29.0f, -8.0f);
	}

	return lDoDoi;
}

void XMan::DrawAnimationShining(const Vec2 & in_DoDoi)
{
	mAnimationShining->set_LatTheoChieuNgang(mLatHinh);
	mAnimationShining->set_ToaDo(mToaDo);
	mAnimationShining->set_DoDoi(in_DoDoi);
	mAnimationShining->Ve(mHH_HienTai->get_ThongTinFrameHienTai(), D3DCOLOR_ARGB(185, 255, 255, 255));
}



