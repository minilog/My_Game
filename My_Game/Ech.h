#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "DoiTuong.h"
#include "KieuDuLieu.h"
#include "HoatHinh.h"
#include <map>
#include "VaChamGame.h"
#include "Camera.h"
#include "DanLv.h"
#include "XMan.h"

class Ech : public DoiTuong
{
public:
	Ech(const Vec2& in_ToaDo, const Vec2& in_VanToc, int in_Rong = 26, int in_Cao = 30)
		:
		DoiTuong(in_ToaDo, in_VanToc, 22, 30)
	{
		LoadHinhAnhVao();

		ChuanBiNhay();
	}
	~Ech()
	{
		if (mHH_ChuanBiNhay)
			delete mHH_ChuanBiNhay;

		if (mHH_Nhay)
			delete mHH_Nhay;
	}

	void CapNhat(float in_tg) {}

	void CapNhat(float in_tg, const XMan *in_XMan) 
	{
		mToaDo.x += mVanToc.x * in_tg;
		mToaDo.y += mVanToc.y * in_tg;

		mHH_HienTai->CapNhat(in_tg);

		switch (mTrangThai)
		{
		case eTT_ChuanBiNhay:
			mTG_DemChuanBiNhay += in_tg;
			if (mToaDo.x - in_XMan->get_ToaDo().x < 0)
			{
				mLatHinh = true;
			}
			else
			{
				mLatHinh = false;
			}
			if (mTG_DemChuanBiNhay > mTG_ChuanBiNhay)
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
			break;

		case eTT_Nhay:
			mVanToc.y += mGiaTocTrongTruong * in_tg;
			if (mVanToc.y > 0.0f)
			{
				mVanToc.y = 0.0f;
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

		case eTT_TiepDat:
			mTG_DemTiepDat += in_tg;
			if (mTG_DemTiepDat > mTG_TiepDat)
			{
				ChuanBiNhay();
			}
			break;

		default:
			break;
		}
	}
	void Ve(const Vec2& in_DoDoi) 
	{
		mHH_HienTai->set_LatTheoChieuNgang(mLatHinh);
		mHH_HienTai->set_ToaDo(mToaDo);
		mHH_HienTai->set_DoDoi(in_DoDoi);
		mHH_HienTai->Ve();
	}
	void XuLyVaCham(const DoiTuong* in_DoiTuong) 
	{
		if (in_DoiTuong->get_LoaiDoiTuong() == eLDT_DoiTuongTinh)
		{
			// chỉ khi Ếch ở trạng thái Nhảy hoặc Rơi thì mới xét va chạm với DoiTuongTinh
			if (mTrangThai != eTT_Nhay &&
				mTrangThai != eTT_Roi)
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
					if (mTrangThai == eTT_Roi)
					{
						mVanToc.y = 0.0f;
						TiepDat();
					}
					break;

				case ePVC_Tren:
					mToaDo.y += lKQVC.eKQVC_VungVaCham.Duoi - lKQVC.eKQVC_VungVaCham.Tren + 1;
					if (mTrangThai == eTT_Nhay)
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

private:

	void ChuanBiNhay()
	{
		mTrangThai = eTT_ChuanBiNhay;
		mHH_HienTai = mHH_ChuanBiNhay;
		mHH_HienTai->Remake();
		mTG_DemChuanBiNhay = 0.0f;
	}

	void Nhay()
	{
		mTrangThai = eTT_Nhay;
		mHH_HienTai = mHH_Nhay;
		mVanToc.y = -mVanTocRoiToiDa;
	}

	void Roi()
	{
		mTrangThai = eTT_Roi;
		mHH_HienTai = mHH_Nhay;
	}

	void TiepDat()
	{
		mTrangThai = eTT_TiepDat;
		mHH_HienTai = mHH_ChuanBiNhay;
		mHH_HienTai->Remake();
		mTG_DemTiepDat = 0.0f;
		mVanToc.x = mVanToc.y = 0.0f;
	}

	void LoadHinhAnhVao()
	{
		std::vector<ThongTinFrame> lDSTTFrame;

		//lDSTTFrame.clear();
		//lDSTTFrame.push_back(ThongTinFrame(Vec2(), 48, 32, 3.5f, HCN(5, 5 + 40, 6, 38)));
		//mHH_DungIm = new HoatHinh("Resources_X3/Enemies/Ech.png", lDSTTFrame, D3DCOLOR_XRGB(255, 0, 255));

		lDSTTFrame.clear();
		lDSTTFrame.push_back(ThongTinFrame(Vec2(), 48, 32, 0.12f, HCN(5, 5 + 40, 6, 38)));
		lDSTTFrame.push_back(ThongTinFrame(Vec2(), 48, 32, 0.12f, HCN(49, 49 + 40, 6, 38)));
		lDSTTFrame.push_back(ThongTinFrame(Vec2(), 48, 32, 0.12f, HCN(100, 100 + 42, 6, 38)));
		lDSTTFrame.push_back(ThongTinFrame(Vec2(), 48, 32, 0.12f, HCN(49, 49 + 40, 6, 38)));
		lDSTTFrame.push_back(ThongTinFrame(Vec2(), 48, 32, 0.12f, HCN(5, 5 + 40, 6, 38)));
		mHH_ChuanBiNhay = new HoatHinh("Resources_X3/Enemies/Ech.png", lDSTTFrame, D3DCOLOR_XRGB(255, 0, 255));

		lDSTTFrame.clear();
		lDSTTFrame.push_back(ThongTinFrame(Vec2(), 48, 32, 99.9f, HCN(146, 146 + 48, 2, 2 + 42)));
		mHH_Nhay = new HoatHinh("Resources_X3/Enemies/Ech.png", lDSTTFrame, D3DCOLOR_XRGB(255, 0, 255));
	}

private:
	HoatHinh *mHH_ChuanBiNhay,
		*mHH_Nhay,
		*mHH_Roi;
	HoatHinh *mHH_HienTai;	

	float mTG_ChuanBiNhay = 0.12f * 5 - 0.05f;
	float mTG_DemChuanBiNhay = 0.0f;

	float mTG_TiepDat = 0.12f * 5;
	float mTG_DemTiepDat = 0.0f;

	float mGiaTocTrongTruong = 1000.0f;
	float mVanTocRoiToiDa = 300.0f;
	float mVanTocNhay = 120.0f;

	bool mLatHinh = false;

	eTrangThai mTrangThai;
};

