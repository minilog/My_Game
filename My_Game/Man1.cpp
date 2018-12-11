#include "Man1.h"
#include "Camera.h"
#include "KieuDuLieu.h"
#include "VaChamGame.h"
#include "ToanCauGame.h"
#include "GameLog.h"

#include "TrucXoay.h"
#include "MayBay.h"

#include "Sound.h"
#include <vector>

Man1::Man1()
{
	TaiDuLieu();

	//Sound::getInstance()->loadSound("Resources/man1.wav", "man1");
	//Sound::getInstance()->play("man1", true, 0);
}


Man1::~Man1()
{
	delete mXMan;
	delete mBanDoMap1;
}

void Man1::TaiDuLieu()
{
	mGameDebugDraw = new GameDebugDraw();
	mGameDebugDraw->setLineSize(2.0f);

	ManGame::mMauNen = D3DCOLOR_XRGB(0, 0, 0);

#pragma region TAO BAN DO VA CAMERA
	ManGame::mBanDo = new Tmx::Map();
	ManGame::mBanDo->ParseFile("Map1.tmx");
	ManGame::mChieuRong = ManGame::mBanDo->GetWidth() * ManGame::mBanDo->GetTileWidth();
	ManGame::mChieuCao = ManGame::mBanDo->GetHeight() * ManGame::mBanDo->GetTileHeight();
	// TAO_CAMERA
	Camera::set_KichThuoc(ToanCauGame::mChieuRong, ToanCauGame::mChieuCao);
	//Camera::CheckPoint = -1;
	//Camera::CheckPoint = 6;
	Camera::set_ToaDo(Vec2(
		ToanCauGame::mChieuRong / 2.0f,
		896.0f));
#pragma endregion

	// lấy hình ảnh bản đồ map
	// Chiếm 61.3MB RAM
	mBanDoMap1 = new HinhAnh("Map1.png");
	mBanDoMap1->set_ToaDo(Vec2(3968.0f, 1024.0f));

	// tạo cây quad tree
	mQuadTree_Tinh = new QuadTree(0, HCN(0, 3968 * 2, 0, 1024 * 2));
	mQuadTree_Dong = new QuadTree(0, HCN(0, 3968 * 2, 0, 1024 * 2));

	// tạo 1 XMan
	mXMan = new XMan(Vec2(4800.0f, 1000.0f)/*Vec2(100.0f, 730.0f)*/);

	// đưa đạn của XMan vào danh sách con trỏ
	mXMan->get_DS_Dan(mDS_DanLv);

	// tạo thanh máu XMan
	mThanhMauXMan = new ThanhMau();

	// tạo DS Đạn Nổ để đưa cho các Quái sử dụng
	for (int i = 0; i < 6; i++)
	{
		DanNo1 *lD = new DanNo1();
		mDS_DanNo1_Quai.push_back(lD);
	}

	// tạo DS Bụi cho quái xài
	for (int i = 0; i < 2; i++)
	{
		Bui* lB = new Bui(Vec2(), Vec2());
		mDS_Bui_Quai.push_back(lB);
	}

	// tạo DS Tên Lửa cho quái xài
	for (int i = 0; i < 4; i++)
	{
		TenLua* lTL = new TenLua();
		mDS_TenLua_Quai.push_back(lTL);
	}

	// tạo 3 Cửa đánh boss
	DS_CuaDanhBoss[0] = new CuaDanhBoss(Vec2(2312.0f, 1176.0f));
	DS_CuaDanhBoss[1] = new CuaDanhBoss(Vec2(2552.0f, 1176.0f));
	mBOSS1 = new BOSS1(Vec2(2517.0f, 1155.0f + 23.0f), DS_CuaDanhBoss[1]);
	mBOSS2 = new BOSS2(Vec2(5028.0f, 1114.0f));

#pragma region TAO DS QUAI
	for (int i = 0; i < ManGame::mBanDo->GetNumObjectGroups(); i++)
	{
		const Tmx::ObjectGroup *lNhomObject = mBanDo->GetObjectGroup(i);

		// đưa các Object trong Bản Đồ vào trong các danh sách
		for (int j = 0; j < lNhomObject->GetNumObjects(); j++)
		{
			// lấy Object trong Bản Đồ
			const Tmx::Object *lObject = lNhomObject->GetObjects().at(j);

			const Vec2 lToaDoDoiTuong(
				lObject->GetX() + lObject->GetWidth() / 2.0f,
				lObject->GetY() + lObject->GetHeight() / 2.0f);

			if (lNhomObject->GetName() == "DoiTuongTinh")
			{	// đối tượng tĩnh sẽ có Tọa Độ khác với các Đối Tượng khác, vì phần mềm Tiled nó như vậy


				DoiTuongTinh *lDoiTuongTinh = new DoiTuongTinh(lToaDoDoiTuong,
					lObject->GetWidth(), lObject->GetHeight());

				mQuadTree_Tinh->ThemDoiTuong(lDoiTuongTinh);
			}
			else if (lNhomObject->GetName() == "DoiTuongTinh2")
			{	// đối tượng tĩnh sẽ có Tọa Độ khác với các Đối Tượng khác, vì phần mềm Tiled nó như vậy


				DoiTuongTinh *lDoiTuongTinh2 = new DoiTuongTinh(lToaDoDoiTuong,
					lObject->GetWidth(), lObject->GetHeight(), 2);

				mQuadTree_Tinh->ThemDoiTuong(lDoiTuongTinh2);
			}
			else if (lNhomObject->GetName() == "DoiTuongTinh3")
			{	// đối tượng tĩnh sẽ có Tọa Độ khác với các Đối Tượng khác, vì phần mềm Tiled nó như vậy


				DoiTuongTinh *lDoiTuongTinh3 = new DoiTuongTinh(lToaDoDoiTuong,
					lObject->GetWidth(), lObject->GetHeight(), 3);

				mQuadTree_Tinh->ThemDoiTuong(lDoiTuongTinh3);
			}
			else if (lNhomObject->GetName() == "Gai")
			{	// đối tượng tĩnh sẽ có Tọa Độ khác với các Đối Tượng khác, vì phần mềm Tiled nó như vậy


				DoiTuongTinh *lDoiTuongTinh = new DoiTuongTinh(lToaDoDoiTuong,
					lObject->GetWidth(), lObject->GetHeight(), -1);

				mQuadTree_Tinh->ThemDoiTuong(lDoiTuongTinh);
			}
		
			else if (lNhomObject->GetName() == "Ech")
			{	// đối tượng tĩnh sẽ có Tọa Độ khác với các Đối Tượng khác, vì phần mềm Tiled nó như vậy

				Ech *lEch = new Ech(lToaDoDoiTuong, Vec2(), mDS_DanNo1_Quai, mDS_Bui_Quai,
					lObject->GetWidth(), lObject->GetHeight());

				mQuadTree_Dong->ThemDoiTuong(lEch);
			}
		
			else if (lNhomObject->GetName() == "EchKhongNhay")
			{	// đối tượng tĩnh sẽ có Tọa Độ khác với các Đối Tượng khác, vì phần mềm Tiled nó như vậy

				Ech *lEch = new Ech(lToaDoDoiTuong, Vec2(), mDS_DanNo1_Quai, mDS_Bui_Quai,
					lObject->GetWidth(), lObject->GetHeight(), true);

				mQuadTree_Dong->ThemDoiTuong(lEch);
			}
			
			else if (lNhomObject->GetName() == "XacUop")
			{	// đối tượng tĩnh sẽ có Tọa Độ khác với các Đối Tượng khác, vì phần mềm Tiled nó như vậy

				mXacUop = new XacUop(lToaDoDoiTuong, Vec2());
			}
			
			else if (lNhomObject->GetName() == "LoCot")
			{	// đối tượng tĩnh sẽ có Tọa Độ khác với các Đối Tượng khác, vì phần mềm Tiled nó như vậy

				LoCot *lLoCot = new LoCot(lToaDoDoiTuong, mDS_DanNo1_Quai, mDS_TenLua_Quai, mDS_Bui_Quai);

				mQuadTree_Tinh->ThemDoiTuong(lLoCot);
			}
			else if (lNhomObject->GetName() == "ThangMay")
			{
				ThangMay *lThangMay =  new ThangMay(lToaDoDoiTuong);

				mQuadTree_Dong->ThemDoiTuong(lThangMay);
			}
			else if (lNhomObject->GetName() == "TrucXoay1")
			{
				TrucXoay *lTrucXoay = new TrucXoay(lToaDoDoiTuong,
					lObject->GetWidth(), lObject->GetHeight(), 1);

				mQuadTree_Tinh->ThemDoiTuong(lTrucXoay);
			}
			else if (lNhomObject->GetName() == "TrucXoay2")
			{
				TrucXoay *lTrucXoay = new TrucXoay(lToaDoDoiTuong,
					lObject->GetWidth(), lObject->GetHeight(), 2);

				mQuadTree_Tinh->ThemDoiTuong(lTrucXoay);
			}
			else if (lNhomObject->GetName() == "TrucXoay_1")
			{
				TrucXoay *lTrucXoay = new TrucXoay(lToaDoDoiTuong,
					lObject->GetWidth(), lObject->GetHeight(), -1);

				mQuadTree_Tinh->ThemDoiTuong(lTrucXoay);
			}
			else if (lNhomObject->GetName() == "TrucXoay_2")
			{
				TrucXoay *lTrucXoay = new TrucXoay(lToaDoDoiTuong,
					lObject->GetWidth(), lObject->GetHeight(), -2);

				mQuadTree_Tinh->ThemDoiTuong(lTrucXoay);
			}
			else if (lNhomObject->GetName() == "MayBay")
			{
				MayBay* lMayBay = new MayBay(lToaDoDoiTuong, mDS_TenLua_Quai, mDS_Bui_Quai);

				mQuadTree_Dong->ThemDoiTuong(lMayBay);
			}
		}
	}
#pragma endregion



// TEST INFO
	font = NULL;
	D3DXCreateFont(ToanCauGame::mThietBi, 12, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE, L"Arial", &font);

	SetRect(&fRectangle, 0, 0, Camera::get_ChieuRong(), Camera::get_ChieuCao());
}


void Man1::CapNhat(float in_tg)
{
	// khi trắng màn hình thì reset lại XMan
	if (Color == 255)
	{
	// CHECK_1
		if (Camera::CheckPoint < 6)
		{
		//	//set Camera trước khi set XMan
			Camera::CheckPoint = -1;
			Camera::set_ToaDo(Vec2(100.0f, 730.0f));
			mXMan->XuatHien(Vec2(100.0f, 730.0f));
			mBOSS1->BienMat();

		}
	// CHECK_2
		if (Camera::CheckPoint >= 6)
		{
			//set Camera trước khi set XMan
			Camera::CheckPoint = 6;
			Camera::set_ToaDo(Vec2(2960.0f, 1000.0f));
			mXMan->XuatHien(Vec2(2960.0f, 1000.0f));
			mBOSS1->BienMat();
		}
	}

	mDS_DoiTuong_Tinh.clear();
	mQuadTree_Tinh->get_CacDoiTuongCoTheVaCham(mDS_DoiTuong_Tinh, Camera::get_HCNGioiHan());

	mDS_DoiTuong_Dong.clear();
	mQuadTree_Dong->get_CacDoiTuongCoTheVaCham(mDS_DoiTuong_Dong, Camera::get_HCNGioiHan_MoRong());

#pragma region CAP NHAT
	DS_CuaDanhBoss[0]->CapNhat(in_tg, mXMan);
	DS_CuaDanhBoss[1]->CapNhat(in_tg, mXMan);
	mBOSS1->CapNhat(in_tg, mXMan);
	mBOSS2->CapNhat(in_tg, mXMan);

	mXMan->CapNhat(in_tg);

	for (auto DanLv : mDS_DanLv)
	{
		DanLv->CapNhat(in_tg);
	}

	mXacUop->CapNhat(in_tg, mXMan);

	for (auto DanNo : mDS_DanNo1_Quai)
	{
		DanNo->CapNhat(in_tg);
	}

	for (auto TenLua : mDS_TenLua_Quai)
	{
		TenLua->CapNhat(in_tg, mXMan);
	}

	for (auto Bui : mDS_Bui_Quai)
	{
		Bui->CapNhat(in_tg);
	}

	for (auto DT1 : mDS_DoiTuong_Tinh)
	{
		DT1->CapNhat(in_tg, mXMan);
	}

	for (auto DT2 : mDS_DoiTuong_Dong)
	{
		DT2->CapNhat(in_tg, mXMan);
	}



#pragma endregion

#pragma region VA CHAM
	DS_CuaDanhBoss[0]->XuLyVaCham(mXMan);
	DS_CuaDanhBoss[1]->XuLyVaCham(mXMan);
	mXMan->XuLyVaCham(DS_CuaDanhBoss[0]);
	mXMan->XuLyVaCham(DS_CuaDanhBoss[1]);
	mXMan->XuLyVaCham(mBOSS1);

	for (auto DanLv : mDS_DanLv)
	{
		mBOSS1->XuLyVaCham(DanLv);
		DanLv->XuLyVaCham(mBOSS1);
	}

	for (auto DanNo : mDS_DanNo1_Quai)
	{
		if (DanNo->get_TrangThai() != eTT_DanNo1_BienMat)
		{
			mXMan->XuLyVaCham(DanNo);
		}
		DanNo->XuLyVaCham(mXMan);

		for (auto DanLv : mDS_DanLv)
		{
			DanNo->XuLyVaCham(DanLv);
		}
	}

	for (auto TenLua : mDS_TenLua_Quai)
	{
		mXMan->XuLyVaCham(TenLua);
		TenLua->XuLyVaCham(mXMan);

		for (auto DanLv : mDS_DanLv)
		{
			TenLua->XuLyVaCham(DanLv);
			DanLv->XuLyVaCham(TenLua);
		}
	}

	for (auto DT : mDS_DoiTuong_Tinh)
	{
		mXMan->XuLyVaCham(DT);

		for (auto DT2 : mDS_DoiTuong_Dong)
		{
			DT2->XuLyVaCham(DT);
		}

		for (auto DanLv : mDS_DanLv)
		{
			DT->XuLyVaCham(DanLv);
			DanLv->XuLyVaCham(DT);
		}

		for (auto DanNo : mDS_DanNo1_Quai)
		{
			DanNo->XuLyVaCham(DT);
		}

		for (auto TenLua : mDS_TenLua_Quai)
		{
			TenLua->XuLyVaCham(DT);
		}
	}

	for (auto DT : mDS_DoiTuong_Dong)
	{
		mXMan->XuLyVaCham(DT);

		for (auto DanLv : mDS_DanLv)
		{
			DT->XuLyVaCham(DanLv);
			DanLv->XuLyVaCham(DT);
		}
	}
#pragma endregion

	Camera::set_ToaDo(mXMan->get_ToaDo());

	// nơi xử lý bàn phím
	mXMan->XuLyBanPhim(mKeys);

}

void Man1::Ve()
{

	// lấy độ dời từ Camera
	Vec2 lDoDoi(ToanCauGame::mChieuRong / 2 - Camera::get_ToaDo().x,
		ToanCauGame::mChieuCao / 2 - Camera::get_ToaDo().y);

	// vẽ hình ảnh bản đồ
	mBanDoMap1->set_DoDoi(lDoDoi);
	mBanDoMap1->Ve();
	
	DS_CuaDanhBoss[0]->Ve(lDoDoi);
	DS_CuaDanhBoss[1]->Ve(lDoDoi);
	mBOSS1->Ve(lDoDoi);
	mBOSS2->Ve(lDoDoi);

	mXMan->Ve(lDoDoi);

	for (auto DT : mDS_DoiTuong_Tinh)
	{
		DT->Ve(lDoDoi);
	}


	for (auto DT : mDS_DoiTuong_Dong)
	{
		DT->Ve(lDoDoi);
	}

	for (auto DanLv : mDS_DanLv)
	{
		DanLv->Ve(lDoDoi);
	}

	for (auto TenLua : mDS_TenLua_Quai)
	{
		TenLua->Ve(lDoDoi);
	}

	mThanhMauXMan->Ve(mXMan->get_HP());

	mXacUop->Ve(lDoDoi);

	for (auto D : mDS_DanNo1_Quai)
	{
		D->Ve(lDoDoi);
	}

	for (auto Bui : mDS_Bui_Quai)
	{
		Bui->Ve(lDoDoi);
	}

	// tô màu trắng trước khi Reset game
	if (mXMan->get_TrangThai() == eTT_XMan_PhatNo)
	{
		Color += 3;
		if (Color > 255)
		{
			Color = 255;
		}

	}
	else if (Color != 0)
	{
		Color -= 15;
		if (Color < 0)
		{
			Color = 0;
		}
	}
	DS_HinhAnh::get_TH()->Rong_png->set_ToaDo(Vec2(ToanCauGame::mChieuRong / 2.0f,
		ToanCauGame::mChieuCao / 2.0f));
	DS_HinhAnh::get_TH()->Rong_png->Ve(D3DCOLOR_ARGB(Color, 255, 255, 255));
}

void Man1::OnKeyDown(int in_KeyCode)
{
	mKeys[in_KeyCode] = true;
}

void Man1::OnKeyUp(int in_KeyCode)
{
	mKeys[in_KeyCode] = false;
}


void Man1::TaoBanDoVaCamera()
{

}

void Man1::TaoDanhSachDoiTuongVaQuai()
{

}



void Man1::DrawQuadTree(QuadTree * in_QuadTree)
{
	//mGameDebugDraw->DrawRect(in_QuadTree->get_RECT());

	//if (in_QuadTree->get_Nodes())
	//{
	//	for (size_t i = 0; i < 4; i++)
	//	{
	//		DrawQuadTree(in_QuadTree->get_Nodes()[i]);
	//	}
	//}



	//if (in_QuadTree->get_Nodes())
	//{
	//	for (size_t i = 0; i < 4; i++)
	//	{
	//		mGameDebugDraw->DrawRect(in_QuadTree->get_Nodes()[i]->get_RECT());
	//	}
	//}
}

void Man1::DrawCollidable()
{
	//for (auto child : mDS_DoiTuong_Tinh)
	//{
	//	mGameDebugDraw->DrawRect(child->get_RECT());
	//}

	//for (auto child : mDS_DoiTuong_Dong)
	//{
	//	mGameDebugDraw->DrawRect(child->get_RECT());
	//}
	//mGameDebugDraw->DrawRect(mXMan->get_RECT());

	//for (int i = 0; i < (int)mDS_Ech.size(); i++)
	//{
	//	mGameDebugDraw->DrawRect(mDS_Ech[i]->get_RECT());
	//}

	//for (int i = 0; i < (int)mDS_DanLv.size(); i++)
	//{
	//	mGameDebugDraw->DrawRect(mDS_DanLv[i]->get_RECT());
	//}

	//mGameDebugDraw->DrawRect(mDanNo1->get_RECT());

	//mGameDebugDraw->DrawRect(mXacUop->get_RECT());
	//for (auto DoiTuong : mDS_DoiTuong)
	//{
	//	mGameDebugDraw->DrawRect(DoiTuong->get_RECT());
	//}
}
