#include "Man1.h"
#include "Camera.h"
#include "KieuDuLieu.h"
#include "VaChamGame.h"
#include "ToanCauGame.h"
#include "GameLog.h"

#include "Sound.h"
#include <vector>

Man1::Man1()
{
	TaiDuLieu();

	Sound::getInstance()->loadSound("Resources/man1.wav", "man1");
	Sound::getInstance()->play("man1", true, 0);
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

	ManGame::mMauNen = 0x54acd2;

#pragma region TAO BAN DO VA CAMERA
	ManGame::mBanDo = new Tmx::Map();
	ManGame::mBanDo->ParseFile("Map1.tmx");

	ManGame::mChieuRong = ManGame::mBanDo->GetWidth() * ManGame::mBanDo->GetTileWidth();
	ManGame::mChieuCao = ManGame::mBanDo->GetHeight() * ManGame::mBanDo->GetTileHeight();

	// TAO_CAMERA
	Camera::set_KichThuoc(ToanCauGame::mChieuRong, ToanCauGame::mChieuCao);

	Camera::set_GioiHan(0, 773 - 4 + Camera::get_ChieuRong(), 770, 770 + ToanCauGame::mChieuCao);
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

			if (lNhomObject->GetName() == "Ech")
			{	// đối tượng tĩnh sẽ có Tọa Độ khác với các Đối Tượng khác, vì phần mềm Tiled nó như vậy

				Ech *lEch = new Ech(lToaDoDoiTuong, Vec2(),
					lObject->GetWidth(), lObject->GetHeight());

				mQuadTree->ThemDoiTuong(lEch);
			}

			if (lNhomObject->GetName() == "XacUop")
			{	// đối tượng tĩnh sẽ có Tọa Độ khác với các Đối Tượng khác, vì phần mềm Tiled nó như vậy

				mXacUop = new XacUop(lToaDoDoiTuong, Vec2());
			}
		}
	}
#pragma endregion

	// tạo 1 XMan
	mXMan = new XMan(Vec2(50.0f, 880.0f));
	
	// đưa đạn của XMan vào danh sách con trỏ
	mXMan->get_DS_Dan(mDS_DanLv);

	// tạo thanh máu XMan
	mThanhMauXMan = new ThanhMau();

	mDanNo1 = new DanNo1();
	mDanNo1->BanRa(Vec2(50.0f, 880.0f), Vec2(0.0f, 80.0f));

// TEST INFO
	font = NULL;
	D3DXCreateFont(ToanCauGame::mThietBi, 12, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE, L"Arial", &font);

	SetRect(&fRectangle, 0, 0, Camera::get_ChieuRong(), Camera::get_ChieuCao());
}


void Man1::CapNhat(float in_tg)
{
	mDS_DoiTuong.clear();
	// lấy đối tượng tĩnh trong các QuadTree - so với với Camera
	mQuadTree->get_CacDoiTuongCoTheVaCham(mDS_DoiTuong, Camera::get_HCNGioiHan());
	
	mDS_DoiTuongTinh.clear();
	mDS_Ech.clear();
	// đưa từ từ các đối tượng vào các DS 
	for (int i = 0; i < (int)mDS_DoiTuong.size(); i++)
	{
		if (mDS_DoiTuong[i]->get_LoaiDoiTuong() == eLDT_DoiTuongTinh)
		{
			mDS_DoiTuongTinh.push_back(mDS_DoiTuong[i]);
		}
		else
		{
			mDS_Ech.push_back(mDS_DoiTuong[i]);
		}
	}

#pragma region CAP NHAT

	mXMan->CapNhat(in_tg);

	for (int i = 0; i < (int)mDS_DanLv.size(); i++)
	{
		mDS_DanLv[i]->CapNhat(in_tg);
	}

	for (int i = 0; i < (int)mDS_Ech.size(); i++)
	{
		mDS_Ech[i]->CapNhat(in_tg, mXMan);
	}

	mXacUop->CapNhat(in_tg, mXMan);

	mDanNo1->CapNhat(in_tg);

#pragma endregion

#pragma region VA CHAM
	// chỉ kiểm tra ĐK ở ĐỐI TƯỢNG CONST THAM SỐ

	// các đối tượng va chạm ĐỐI TƯỢNG TĨNH
	for (int i = 0; i < (int)mDS_DoiTuongTinh.size(); i++)
	{
		// xử lý va chạm XMAN-ĐỐI TƯỢNG TĨNH 
		mXMan->XuLyVaCham(mDS_DoiTuongTinh[i]);

		// va chạm với đạn XMAN
		for (int j = 0; j < (int)mDS_DanLv.size(); j++)
		{
			mDS_DanLv[j]->XuLyVaCham(mDS_DoiTuongTinh[i]);
		}

		for (int j = 0; j < (int)mDS_Ech.size(); j++)
		{
			mDS_Ech[j]->XuLyVaCham(mDS_DoiTuongTinh[i]);
		}

		mDanNo1->XuLyVaCham(mDS_DoiTuongTinh[i]);
	}


	//các đối tượng va chạm với ĐẠN XMan
	for (int i = 0; i < (int)mDS_DanLv.size(); i++)
	{
		// nếu ĐẠN đã bị phá hủy hoặc đang tan biến thì bỏ qua
		if (mDS_DanLv[i]->get_TrangThai() == eTT_Dan_BienMat ||
			mDS_DanLv[i]->get_TrangThai() == eTT_Dan_DangTanBien)
		{
			continue;
		}
		for (int j = 0; j < (int)mDS_Ech.size(); j++)
		{
			mDS_Ech[j]->XuLyVaCham(mDS_DanLv[i]);
		}
	}

	// các đối tượng va chạm với Ếch
	for (int i = 0; i < (int)mDS_Ech.size(); i++)
	{
		// nếu Ếch đã bị phá hoặc đang tan biến thì bỏ qua
		if (mDS_Ech[i]->get_TrangThai() == eTT_Ech_BienMat ||
			mDS_Ech[i]->get_TrangThai() == eTT_Ech_DangTanBien)
		{
			continue;
		}
		for (int j = 0; j < (int)mDS_DanLv.size(); j++)
		{
			mDS_DanLv[j]->XuLyVaCham(mDS_Ech[i]);
		}
		mXMan->XuLyVaCham(mDS_Ech[i]);
	}
#pragma endregion

	// nơi xử lý bàn phím
	mXMan->XuLyBanPhim(mKeys);

#pragma region CAMERA
	Camera::set_ToaDo(mXMan->get_ToaDo());

	//if (mXMan->get_ToaDo().x >= 850.0f && Camera::mGioiHanTren == 770)
	//{
	//	Camera::mGioiHanTren = 255;
	//}
	//if (mXMan->get_ToaDo().x >= 900.0f && Camera::mGioiHanTrai == 0)
	//{
	//	Camera::mGioiHanTrai = 773 - 4;
	//}
	//if (mXMan->get_ToaDo().x >= 800.0f &&
	//	mXMan->get_ToaDo().y <= 400.f &&
	//	Camera::mGioiHanPhai >= 773 - 4 + Camera::get_ChieuRong() &&
	//	Camera::mGioiHanPhai < 1500 + Camera::get_ChieuRong())
	//{
	//	Camera::mGioiHanPhai++;
	//}
#pragma endregion
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

	for (int i = 0; i < (int)mDS_DanLv.size(); i++)
	{
		mDS_DanLv[i]->Ve(lDoDoi);
	}

	mThanhMauXMan->Ve(mXMan->get_HP());

	for (int i = 0; i < (int)mDS_Ech.size(); i++)
	{
		mDS_Ech[i]->Ve(lDoDoi);
	}

	mXacUop->Ve(lDoDoi);

	mDanNo1->Ve(lDoDoi);
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
}
