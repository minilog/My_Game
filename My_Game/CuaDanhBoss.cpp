#include "CuaDanhBoss.h"
#include "XMan.h"



CuaDanhBoss::CuaDanhBoss(const Vec2& in_ToaDo)
	:
	DoiTuong(in_ToaDo, Vec2(), 16, 1000)
{
	mLoaiDoiTuong = eLDT_CuaDanhBoss;

	LoadThongTinHoatHinh();
	HH_HienTai = HH_MoCua;
	KhoaCua();
}

void CuaDanhBoss::CapNhat(float in_tg, const DoiTuong * in_DoiTuong)
{
	if (mTrangThai != eTT_CuaDanhBoss_KhoaCua)
	{
		HH_HienTai->CapNhat(in_tg);
	}

	switch (mTrangThai)
	{
	case eTT_CuaDanhBoss_MoCua:
		TGDem += in_tg;
		if (TGDem > TG_MoCua)
		{
			DongCua();
		}
		break;

	case eTT_CuaDanhBoss_DongCua:
		TGDem += in_tg;
		if (TGDem > TG_DongCua)
		{
			KhoaCua();
		}
		break;

	default:
		break;
	}


}

// GỌI: xử lý va chạm với XMan
void CuaDanhBoss::XuLyVaCham(const DoiTuong * in_DoiTuong)
{
	if (!ChoPhepMoCua ||
		mTrangThai == eTT_CuaDanhBoss_MoCua || 
		mTrangThai == eTT_CuaDanhBoss_DongCua)
	{
		return;
	}

	eKetQuaVaCham lKQVC = VaChamGame::get_KetQuaVaCham(get_HCNGioiHan(), in_DoiTuong->get_HCNGioiHan());

	if (!lKQVC.eKQVC_DaVaCham)
	{
		return;
	}

	//if (((XMan*)in_DoiTuong)->get_TrangThai() != eTT_XMan_Chay ||
	//	((XMan*)in_DoiTuong)->get_VanToc().x <= 0.0f)
	//{
	//	return;
	//}


	ePhiaVaCham lPVC = VaChamGame::get_PhiaVaCham(this, lKQVC);

	if (lPVC == ePVC_Trai || lPVC == ePVC_TraiTren || lPVC == ePVC_TraiDuoi)
	{
		MoCua();
	}


}

void CuaDanhBoss::Ve(const Vec2 & in_DoDoi)
{
	HH_HienTai->Ve(DS_HinhAnh::get_TH()->CuaDanhBoss_png, false, mToaDo, in_DoDoi);
}


void CuaDanhBoss::MoCua()
{
	mTrangThai = eTT_CuaDanhBoss_MoCua;
	HH_HienTai = HH_MoCua;
	HH_HienTai->Remake();
	TGDem = 0.0f;
	mLoaiDoiTuong = eLDT_CuaDanhBoss;
}

void CuaDanhBoss::DongCua()
{
	mTrangThai = eTT_CuaDanhBoss_DongCua;
	HH_HienTai = HH_DongCua;
	HH_HienTai->Remake();
	TGDem = 0.0f;



}

void CuaDanhBoss::KhoaCua()
{
	mTrangThai = eTT_CuaDanhBoss_KhoaCua;
	TGDem = 0.0f;
	mLoaiDoiTuong = eLDT_DoiTuongTinh; // khi đóng cửa thì sét thành Đối Tượng Tĩnh để set va chạm
}

void CuaDanhBoss::LoadThongTinHoatHinh()
{
	std::vector<ThongTinFrame> lDSTTFrame;

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(16, 48, HCN(2, 2 + 16, 59, 59 + 48), 1.0f)); // 1
	lDSTTFrame.push_back(ThongTinFrame(16, 48, HCN(2 + 18 * 1, 2 + 18 * 1 + 16, 59, 59 + 48),   0.13f));	 // 2
	lDSTTFrame.push_back(ThongTinFrame(16, 48, HCN(2 + 18 * 2, 2 + 18 * 2 + 16, 59, 59 + 48),   0.13f));	 // 3
	lDSTTFrame.push_back(ThongTinFrame(16, 48, HCN(2 + 18 * 3, 2 + 18 * 3 + 16, 59, 59 + 48),   0.13f));	 // 4
	lDSTTFrame.push_back(ThongTinFrame(16, 48, HCN(2 + 18 * 4, 2 + 18 * 4 + 16, 59, 59 + 48),   0.13f));	 // 5
	lDSTTFrame.push_back(ThongTinFrame(16, 48, HCN(2 + 18 * 5, 2 + 18 * 5 + 16, 59, 59 + 48),   0.13f));	 // 6
	lDSTTFrame.push_back(ThongTinFrame(16, 48, HCN(2 + 18 * 6, 2 + 18 * 6 + 16, 59, 59 + 48),   0.13f));	 // 7
	lDSTTFrame.push_back(ThongTinFrame(16, 48, HCN(2 + 18 * 7, 2 + 18 * 7 + 16, 59, 59 + 48),   0.13f));	 // 8
	lDSTTFrame.push_back(ThongTinFrame(16, 48, HCN(2 + 18 * 8, 2 + 18 * 8 + 16, 59, 59 + 48),   0.13f));	 // 9
	lDSTTFrame.push_back(ThongTinFrame(16, 48, HCN(2 + 18 * 9, 2 + 18 * 9 + 16, 59, 59 + 48),   0.13f));	 // 10
	lDSTTFrame.push_back(ThongTinFrame(16, 48, HCN(2 + 18 * 10, 2 + 18 * 10 + 16, 59, 59 + 48), 0.13f)); // 11
	lDSTTFrame.push_back(ThongTinFrame(16, 48, HCN(2 + 18 * 11, 2 + 18 * 11 + 16, 59, 59 + 48), 0.13f)); // 12
	lDSTTFrame.push_back(ThongTinFrame(16, 48, HCN(2 + 18 * 12, 2 + 18 * 12 + 16, 59, 59 + 48), 0.13f)); // 13
	lDSTTFrame.push_back(ThongTinFrame(16, 48, HCN(2 + 18 * 13, 2 + 18 * 13 + 16, 59, 59 + 48), 0.13f)); // 14
	lDSTTFrame.push_back(ThongTinFrame(16, 48, HCN(2 + 18 * 14, 2 + 18 * 14 + 16, 59, 59 + 48), 0.13f)); // 15
	lDSTTFrame.push_back(ThongTinFrame(16, 48, HCN(2 + 18 * 15, 2 + 18 * 15 + 16, 59, 59 + 48), 0.13f)); // 16
	lDSTTFrame.push_back(ThongTinFrame(16, 48, HCN(2 + 18 * 16, 2 + 18 * 16 + 16, 59, 59 + 48), 99.9f)); // 17
	HH_DongCua = new HoatHinh(lDSTTFrame);

	lDSTTFrame.clear();
	lDSTTFrame.push_back(ThongTinFrame(16, 48, HCN(2 + 18 * 16, 2 + 18 * 16 + 16, 59, 59 + 48), 0.13f)); // 17
	lDSTTFrame.push_back(ThongTinFrame(16, 48, HCN(2 + 18 * 15, 2 + 18 * 15 + 16, 59, 59 + 48), 0.13f)); // 16
	lDSTTFrame.push_back(ThongTinFrame(16, 48, HCN(2 + 18 * 14, 2 + 18 * 14 + 16, 59, 59 + 48), 0.13f)); // 15
	lDSTTFrame.push_back(ThongTinFrame(16, 48, HCN(2 + 18 * 13, 2 + 18 * 13 + 16, 59, 59 + 48), 0.13f)); // 14
	lDSTTFrame.push_back(ThongTinFrame(16, 48, HCN(2 + 18 * 12, 2 + 18 * 12 + 16, 59, 59 + 48), 0.13f)); // 13
	lDSTTFrame.push_back(ThongTinFrame(16, 48, HCN(2 + 18 * 11, 2 + 18 * 11 + 16, 59, 59 + 48), 0.13f)); // 12
	lDSTTFrame.push_back(ThongTinFrame(16, 48, HCN(2 + 18 * 10, 2 + 18 * 10 + 16, 59, 59 + 48), 0.13f)); // 11
	lDSTTFrame.push_back(ThongTinFrame(16, 48, HCN(2 + 18 * 9, 2 + 18 * 9 + 16, 59, 59 + 48),   0.13f));	 // 10
	lDSTTFrame.push_back(ThongTinFrame(16, 48, HCN(2 + 18 * 8, 2 + 18 * 8 + 16, 59, 59 + 48),   0.13f));	 // 9
	lDSTTFrame.push_back(ThongTinFrame(16, 48, HCN(2 + 18 * 7, 2 + 18 * 7 + 16, 59, 59 + 48),   0.13f));	 // 8
	lDSTTFrame.push_back(ThongTinFrame(16, 48, HCN(2 + 18 * 6, 2 + 18 * 6 + 16, 59, 59 + 48),   0.13f));	 // 7
	lDSTTFrame.push_back(ThongTinFrame(16, 48, HCN(2 + 18 * 5, 2 + 18 * 5 + 16, 59, 59 + 48),   0.13f));	 // 6
	lDSTTFrame.push_back(ThongTinFrame(16, 48, HCN(2 + 18 * 4, 2 + 18 * 4 + 16, 59, 59 + 48),   0.13f));	 // 5
	lDSTTFrame.push_back(ThongTinFrame(16, 48, HCN(2 + 18 * 3, 2 + 18 * 3 + 16, 59, 59 + 48),   0.13f));	 // 4
	lDSTTFrame.push_back(ThongTinFrame(16, 48, HCN(2 + 18 * 2, 2 + 18 * 2 + 16, 59, 59 + 48),   0.13f));	 // 3
	lDSTTFrame.push_back(ThongTinFrame(16, 48, HCN(2 + 18 * 1, 2 + 18 * 1 + 16, 59, 59 + 48),   0.13f));	 // 2
	lDSTTFrame.push_back(ThongTinFrame(16, 48, HCN(2, 2 + 16, 59, 59 + 48),                     99.9f)); // 1
	HH_MoCua = new HoatHinh(lDSTTFrame);
}

CuaDanhBoss::~CuaDanhBoss()
{
}
