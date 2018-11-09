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
}

void Mario::Ve(const Vec2& in_DoDoi)
{
	mHH_HienTai->set_ToaDo(mToaDo);
	mHH_HienTai->set_LatTheoChieuNgang(mLatHinh);
	mHH_HienTai->set_DoDoi(in_DoDoi);
	mHH_HienTai->Ve();
}

void Mario::XuLyVaCham(const DoiTuong * in_DoiTuong) {
	switch (mTT_HienTai)
	{
	case eTT_Roi:
		switch (in_DoiTuong->get_LoaiDoiTuong())
		{
		case eLDT_DoiTuongTinh:
			eKetQuaVaCham lKQVC = VaChamGame::get_KetQuaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan());
			if (lKQVC.eKQVC_DaVaCham == true)
			{
				ePhiaVaCham lPVC = VaChamGame::get_PhiaVaCham(this, lKQVC);

				//if (lPVC == ePhiaVaCham::eDuoi)
				{
					mToaDo.y -= lKQVC.eKQVC_VungVaCham.Duoi - lKQVC.eKQVC_VungVaCham.Tren + 1;
					DungIm();
				}
			}
			break;
		}
		break;
	case eTT_ChaySangPhai:
		switch (in_DoiTuong->get_LoaiDoiTuong())
		{
		case eLDT_DoiTuongTinh:
			break;
		}
		break;
	}

}

void Mario::XuLyBanPhim(std::map<int, bool> keys) {
	switch (mTT_HienTai) 
	{
	case eTT_DungIm:
		if (keys[VK_RIGHT]) 
		{
			ChaySangBenPhai();
		}
		if (keys['C']) {
			Roi();
		}
		break;
	case eTT_ChaySangPhai:
		if (!keys[VK_RIGHT]){
			DungIm();
		}
		break;
	}
}

void Mario::Roi() {
	mHH_HienTai = mHH_Nhay;
	mTT_HienTai = eTT_Roi;
	mVanToc = Vec2(0, 5);
}

void Mario::DungIm() {
	mHH_HienTai = mHH_DungIm;
	mTT_HienTai = eTT_DungIm;
	mVanToc = Vec2();
}

void Mario::ChaySangBenPhai()
{
	mHH_HienTai = mHH_Chay;
	mTT_HienTai = eTT_ChaySangPhai;
	mVanToc = Vec2(5, 0);
}

void Mario::ChaySangBenTrai()
{
	mLatHinh = true;
	mHH_HienTai = mHH_Chay;
	mTT_HienTai = eTT_ChaySangPhai;
	mVanToc = Vec2(-5, 0);
}

void Mario::Nhay()
{
}
