#include "Mario.h"
#include "Camera.h"

Mario::Mario(const Vec2& in_ToaDo) :
	DoiTuong(in_ToaDo, Vec2(), 30, 30)
{
	mLoaiDoiTuong = eLoaiDoiTuong::eLDT_Mario;

	mHH_DungIm = new HoatHinh("Resources/mario/standingright.png", 1, 1, 1, 0);
	mHH_Chay = new HoatHinh("Resources/mario/runningright.png", 2, 1, 2, 0.15f);
	mHH_Nhay = new HoatHinh("Resources/mario/jumpingright.png", 1, 1, 1, 0);

	Roi();
}

Mario::~Mario()
{
	delete mHH_HienTai;
	delete mHH_DungIm;
	delete mHH_Chay;
	delete mHH_Nhay;
}

void Mario::CapNhat(float in_tg) {
	mToaDo += mVanToc;
	mHH_HienTai->CapNhat(in_tg);

	switch (mTT_HienTai)
	{
	case eTT_Nhay:
		mVanToc.y += mGiaTocTrongTruong;
		if (mVanToc.y >= 0)
		{
			Roi();
		}
		break;

	case eTT_Roi:
		mVanToc.y += mGiaTocTrongTruong;
		if (mVanToc.y > mVanTocNhayCaoNhat)
		{
			mVanToc.y = mVanTocNhayCaoNhat;
		}
		break;

	case eTT_ChaySangTrai:
	case eTT_ChaySangPhai:
	case eTT_DungIm:
		if (mDangDungTuNhienRoi == true)
		{
			Roi();
		}
		break;
	}

	mDangDungTuNhienRoi = true;
}

void Mario::Ve(const Vec2& in_DoDoi)
{
	mHH_HienTai->set_ToaDo(mToaDo);
	mHH_HienTai->set_LatTheoChieuNgang(mLatHinh);
	mHH_HienTai->set_DoDoi(in_DoDoi);
	mHH_HienTai->Ve();
}

void Mario::XuLyVaCham(const DoiTuong * in_DoiTuong) 
{
	HinhChuNhat lHCNGioiHanMario = get_HCNGioiHan();

	eKetQuaVaCham lKQVC = VaChamGame::get_KetQuaVaCham(lHCNGioiHanMario, in_DoiTuong->get_HCNGioiHan());
	ePhiaVaCham lPVC = VaChamGame::get_PhiaVaCham(this, lKQVC);
	if (lKQVC.eKQVC_DaVaCham == true)
	{
		switch (in_DoiTuong->get_LoaiDoiTuong())
		{
		case eLDT_DoiTuongTinh:
		case eLDT_VienGachBinhThuong:
			if (lPVC == ePVC_Duoi)
			{
				switch (mTT_HienTai)
				{
				case eTT_Roi:
					mToaDo.y -= lKQVC.eKQVC_VungVaCham.Duoi - lKQVC.eKQVC_VungVaCham.Tren + 1;
					DungIm();
					break;
				}
			}
			if (lPVC == ePVC_Trai || lPVC == ePVC_TraiTren || lPVC == ePVC_TraiDuoi)
			{
				mToaDo.x += lKQVC.eKQVC_VungVaCham.Phai - lKQVC.eKQVC_VungVaCham.Trai + 1;
			}
			if (lPVC == ePVC_Phai || lPVC == ePVC_PhaiTren || lPVC == ePVC_PhaiDuoi)
			{
				mToaDo.x -= lKQVC.eKQVC_VungVaCham.Phai - lKQVC.eKQVC_VungVaCham.Trai + 1;
			}
			if (lPVC == ePVC_Tren)
			{
				mToaDo.y += lKQVC.eKQVC_VungVaCham.Duoi - lKQVC.eKQVC_VungVaCham.Tren + 1;
				Roi();
			}
			break;
		}
	}

// XỬ LÝ BIẾN mDangDungTuNhienRoi
	if (mDangDungTuNhienRoi == true)
	{
		HinhChuNhat lHCNGioiHanMoRongDay = get_HCNGioiHan();
		lHCNGioiHanMoRongDay.Duoi += 2;

		eKetQuaVaCham lKQVC = VaChamGame::get_KetQuaVaCham(lHCNGioiHanMoRongDay, in_DoiTuong->get_HCNGioiHan());
		ePhiaVaCham lPVC = VaChamGame::get_PhiaVaCham(this, lKQVC);

		if (lKQVC.eKQVC_DaVaCham == true)
		{
			switch (in_DoiTuong->get_LoaiDoiTuong())
			{
			case eLDT_DoiTuongTinh:
			case eLDT_VienGachBinhThuong:
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

void Mario::XuLyBanPhim(std::map<int, bool> in_Keys) {
	switch (mTT_HienTai) 
	{
	case eTT_DungIm:
		if (in_Keys[VK_RIGHT])
		{
			ChaySangPhai();
		}
		if (in_Keys[VK_LEFT])
		{
			ChaySangTrai();
		}
		if (in_Keys['C'])
		{
			Nhay();
		}
		break;
	case eTT_ChaySangPhai:
		if (!in_Keys[VK_RIGHT])
		{
			DungIm();
		}
		if (in_Keys['C'])
		{
			Nhay();
		}
		break;
	case eTT_ChaySangTrai:
		if (!in_Keys[VK_LEFT])
		{
			DungIm();
		}
		if (in_Keys['C'])
		{
			Nhay();
		}
		break;
	case eTT_Nhay:
		if (in_Keys[VK_LEFT])
		{
			mLatHinh = true;
			mVanToc.x = -5;
		}
		if (in_Keys[VK_RIGHT])
		{
			mLatHinh = false;
			mVanToc.x = 5;
		}
		if ((!in_Keys[VK_LEFT] && mVanToc.x < 0) || (!in_Keys[VK_RIGHT] && mVanToc.x > 0))
		{
			mVanToc.x = 0;
		}
		if (!in_Keys['C'])
		{
			mVanToc.y += mVanTocNhayCaoNhat / 7.0f;
			if (mVanToc.y > 0)
			{
				mVanToc.y = 0;
			}
		}
	case eTT_Roi:
		if (in_Keys[VK_LEFT])
		{
			mLatHinh = true;
			mVanToc.x = -5;
		}
		if (in_Keys[VK_RIGHT])
		{
			mLatHinh = false;
			mVanToc.x = 5;
		}
		if ((!in_Keys[VK_LEFT] && mVanToc.x < 0) || (!in_Keys[VK_RIGHT] && mVanToc.x > 0))
		{
			mVanToc.x = 0;
		}
		break;
	}
}

void Mario::Roi() {
	mHH_HienTai = mHH_Nhay;
	mTT_HienTai = eTT_Roi;
	mVanToc.y = 0;
}

void Mario::DungIm() {
	mHH_HienTai = mHH_DungIm;
	mTT_HienTai = eTT_DungIm;
	mVanToc = Vec2();
}

void Mario::ChaySangTrai()
{
	mLatHinh = true;
	mHH_HienTai = mHH_Chay;
	mTT_HienTai = eTT_ChaySangTrai;
	mVanToc.x = -5;
}

void Mario::ChaySangPhai()
{
	mLatHinh = false;
	mHH_HienTai = mHH_Chay;
	mTT_HienTai = eTT_ChaySangPhai;
	mVanToc.x = 5;
}

void Mario::Nhay()
{
	mHH_HienTai = mHH_Nhay;
	mTT_HienTai = eTT_Nhay;
	mVanToc.y = -mVanTocNhayCaoNhat;
}

