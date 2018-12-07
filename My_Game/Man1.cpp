#include "Man1.h"
#include "Camera.h"
#include "KieuDuLieu.h"
#include "VaChamGame.h"
#include "ToanCauGame.h"
#include "GameLog.h"
#include "ThangMay.h"

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

	Camera::set_ToaDo(Vec2(
		ToanCauGame::mChieuRong / 2.0f,
		896.0f));
#pragma endregion


	// lấy hình ảnh bản đồ map
	// Chiếm 61.3MB RAM
	mBanDoMap1 = new HinhAnh("Map1.png");
	mBanDoMap1->set_ToaDo(Vec2(3968.0f, 1024.0f));

	// tạo cây quad tree
	mQuadTree = new QuadTree(0, HCN(0, 3968 * 2, 0, 1024 * 2));

	// tạo 1 XMan
	mXMan = new XMan(Vec2(50.0f, 800.0f));

	//float k[3][2] = { (800.0f, 850.0f), (900.0f, 400.0f), (0.0f, 0.0f) };
	//for (int i = 0; i < 2; i++)
	//{
	//	Camera::set_ToaDo(Vec2(k[i][0], k[i][1]));
	//}
	//mXMan->XuatHien(Vec2(1655.0f, 220.0f));
	//Camera::CheckPoint = 2;

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

				mQuadTree->ThemDoiTuong(lDoiTuongTinh);
			}
		
			else if (lNhomObject->GetName() == "Ech")
			{	// đối tượng tĩnh sẽ có Tọa Độ khác với các Đối Tượng khác, vì phần mềm Tiled nó như vậy

				Ech *lEch = new Ech(lToaDoDoiTuong, Vec2(), mDS_DanNo1_Quai, mDS_Bui_Quai,
					lObject->GetWidth(), lObject->GetHeight());

				mQuadTree->ThemDoiTuong(lEch);
			}
		
			else if (lNhomObject->GetName() == "EchKhongNhay")
			{	// đối tượng tĩnh sẽ có Tọa Độ khác với các Đối Tượng khác, vì phần mềm Tiled nó như vậy

				Ech *lEch = new Ech(lToaDoDoiTuong, Vec2(), mDS_DanNo1_Quai, mDS_Bui_Quai,
					lObject->GetWidth(), lObject->GetHeight(), true);

				mQuadTree->ThemDoiTuong(lEch);
			}
			
			else if (lNhomObject->GetName() == "XacUop")
			{	// đối tượng tĩnh sẽ có Tọa Độ khác với các Đối Tượng khác, vì phần mềm Tiled nó như vậy

				mXacUop = new XacUop(lToaDoDoiTuong, Vec2());
			}
			
			else if (lNhomObject->GetName() == "LoCot")
			{	// đối tượng tĩnh sẽ có Tọa Độ khác với các Đối Tượng khác, vì phần mềm Tiled nó như vậy

				LoCot *lLoCot = new LoCot(lToaDoDoiTuong, mDS_DanNo1_Quai, mDS_TenLua_Quai);

				mQuadTree->ThemDoiTuong(lLoCot);
			}
			else if (lNhomObject->GetName() == "ThangMay")
			{
				ThangMay *lThangMay = new ThangMay(lToaDoDoiTuong);

				mQuadTree->ThemDoiTuong(lThangMay);
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


	mDS_DoiTuong.clear();
	mQuadTree->get_CacDoiTuongCoTheVaCham(mDS_DoiTuong, Camera::get_HCNGioiHan_MoRong());

#pragma region CAP NHAT


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

	for (auto DT : mDS_DoiTuong)
	{
		DT->CapNhat(in_tg, mXMan);
	}



#pragma endregion

#pragma region VA CHAM


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
		}
	}

	for (auto DT : mDS_DoiTuong)
	{
		mXMan->XuLyVaCham(DT);

		for (auto DT2 : mDS_DoiTuong)
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

	mXMan->Ve(lDoDoi);

	for (auto DT : mDS_DoiTuong)
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



	//if (mQuadTree->get_Nodes())
	//{
	//	for (size_t i = 0; i < 4; i++)
	//	{
	//		mGameDebugDraw->DrawRect(mQuadTree->get_Nodes()[i]->get_RECT());
	//	}
	//}
}

void Man1::DrawCollidable()
{
	//for (auto child : mDS_DoiTuongTinh)
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
