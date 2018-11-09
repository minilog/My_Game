#include "Mario.h"
#include "Camera.h"

Mario::Mario() :
	DoiTuong(Vec2(200, 800), Vec2(), 28, 32)
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
		mGiaTocTrongTruongHienTai += mGiaTocTrongTruong;
		if (mGiaTocTrongTruongHienTai >= 1.0f)
		{
			mGiaTocTrongTruongHienTai -= 1.0f;
			mVanToc.y += 1;
		}
		if (mVanToc.y >= 0)
		{
			Roi();
		}
		break;
	case eTT_Roi:
		mGiaTocTrongTruongHienTai += mGiaTocTrongTruong;
		if (mGiaTocTrongTruongHienTai >= 1.0f)
		{
			mGiaTocTrongTruongHienTai -= 1.0f;
			mVanToc.y += 1;
		}
		if (mVanToc.y > mVanTocNhayCaoNhat)
		{
			mVanToc.y = mVanTocNhayCaoNhat;
		}
		break;
	}
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
	eKetQuaVaCham lKQVC = VaChamGame::get_KetQuaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan());
	ePhiaVaCham lPVC = VaChamGame::get_PhiaVaCham(this, lKQVC);

	switch (in_DoiTuong->get_LoaiDoiTuong())
	{
	case eLDT_DoiTuongTinh:
		if (lKQVC.eKQVC_DaVaCham == true)
		{
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
		}
		break;
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
		if (in_Keys[VK_SPACE])
		{
			Nhay();
		}
		break;
	case eTT_ChaySangPhai:
		if (!in_Keys[VK_RIGHT])
		{
			DungIm();
		}
		if (in_Keys[VK_SPACE])
		{
			Nhay();
		}
		break;
	case eTT_ChaySangTrai:
		if (!in_Keys[VK_LEFT])
		{
			DungIm();
		}
		if (in_Keys[VK_SPACE])
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

