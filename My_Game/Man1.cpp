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
}


Man1::~Man1()
{
	delete mXman;
	delete mBanDoMap1;
}

void Man1::TaiDuLieu()
{

	mGameDebugDraw = new GameDebugDraw();
	mGameDebugDraw->setLineSize(2.0f);

	ManGame::mMauNen = 0x54acd2;

	TaoBanDoVaCamera();

	mBanDoMap1 = new HinhAnh("Map1.png");
	mBanDoMap1->set_ToaDo(Vec2(3968.0f, 1024.0f));

	mQuadTree = new QuadTree(0, HCN(0, 3968 * 2, 0, 1024 * 2));

	TaoDanhSachDoiTuong();

	mXman = new XMan(Vec2(50.0f, 880.0f));

	//mTest = new HinhAnh("Resources_X3/Xman/SNES - Mega Man X3 - Mega Man X.png", D3DCOLOR_XRGB(50, 96, 166));
	//mTest->set_ToaDo(Vec2(200.0f, 864.0f));
}


void Man1::CapNhat(float in_tg)
{
	mXman->CapNhat(in_tg);

	XuLyVaChamChung();



	mXman->XuLyBanPhim(mKeys);

	Camera::set_ToaDo(mXman->get_ToaDo());
}

void Man1::Ve()
{
	Vec2 lDoDoi(ToanCauGame::get_ChieuRong() / 2 - Camera::get_ToaDo().x,
		ToanCauGame::get_ChieuCao() / 2 - Camera::get_ToaDo().y);

	VeHinhAnhBanDoGame(lDoDoi);

	mXman->Ve(lDoDoi);

	//mTest->set_DoDoi(lDoDoi);
	//mTest->Ve();
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
	// TAO_BAN_DO
	ManGame::mBanDo = new Tmx::Map();
	ManGame::mBanDo->ParseFile("Map1.tmx");

	ManGame::mChieuRong = ManGame::mBanDo->GetWidth() * ManGame::mBanDo->GetTileWidth();
	ManGame::mChieuCao = ManGame::mBanDo->GetHeight() * ManGame::mBanDo->GetTileHeight();

	// TAO_CAMERA
	Camera::set_GioiHan(0, ManGame::mChieuRong, 770, 770 + ToanCauGame::get_ChieuCao());
	Camera::set_ToaDo(Vec2(
		ToanCauGame::get_ChieuRong() / 2.0f,
		896.0f));
	Camera::set_KichThuoc(ToanCauGame::get_ChieuRong(), ToanCauGame::get_ChieuCao());
}

void Man1::TaoDanhSachDoiTuong()
{
	for (int i = 0; i < ManGame::mBanDo->GetNumObjectGroups(); i++)
	{
		const Tmx::ObjectGroup *lNhomObject = mBanDo->GetObjectGroup(i);

		// đưa các Object trong Bản Đồ vào trong các danh sách
		for (int j = 0; j < lNhomObject->GetNumObjects(); j++)
		{
			// lấy Object trong Bản Đồ
			const Tmx::Object *lObject = lNhomObject->GetObjects().at(j);

			if (lNhomObject->GetName() == "DoiTuongTinh")
			{	// đối tượng tĩnh sẽ có Tọa Độ khác với các Đối Tượng khác, vì phần mềm Tiled nó như vậy
				const Vec2 lToaDoDoiTuongTinh(
					lObject->GetX() + lObject->GetWidth() / 2.0f  ,
					lObject->GetY() + lObject->GetHeight() / 2.0f);

				DoiTuongTinh *lDoiTuongTinh = new DoiTuongTinh(lToaDoDoiTuongTinh,
					lObject->GetWidth(), lObject->GetHeight());

				//mDanhSachDoiTuongTinh.push_back(lDoiTuongTinh);
				mQuadTree->ThemDoiTuong(lDoiTuongTinh);
			}
		}
	}
}

void Man1::TaoDanhSachTileset()
{
	for (int i = 0; i < /*mBanDo->GetNumTilesets()*/1; i++)
	{
		const Tmx::Tileset *lTileset = mBanDo->GetTileset(i);
		HinhAnh *lHinhAnh = new HinhAnh(lTileset->GetImage()->GetSource().c_str());
		mDanhSachTileset.insert(pair<int, HinhAnh*>(i, lHinhAnh));
	}
}

void Man1::VeHinhAnhBanDoGame(const Vec2& in_DoDoi)
{
	mBanDoMap1->set_DoDoi(in_DoDoi);
	mBanDoMap1->Ve();
}

void Man1::CapNhatDanhSachDoiTuong(float in_tg)
{
}

void Man1::VeDanhSachDoiTuong(const Vec2 & in_DoDoi)
{
}

void Man1::XuLyVaChamChung()
{
	mDS_DoiTuongXetVaCHam.clear();

	mQuadTree->get_CacDoiTuongCoTheVaCham(mDS_DoiTuongXetVaCHam, mXman);

	for (auto lDT_Tinh : mDS_DoiTuongXetVaCHam)
	{
		mXman->XuLyVaCham(lDT_Tinh);
	}
}


void Man1::DrawQuadTree(QuadTree * in_QuadTree)
{
	mGameDebugDraw->DrawRect(in_QuadTree->get_RECT());

	if (in_QuadTree->get_Nodes())
	{
		for (size_t i = 0; i < 4; i++)
		{
			DrawQuadTree(in_QuadTree->get_Nodes()[i]);
		}
	}



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
	//for (auto child : mDS_DoiTuongXetVaCHam)
	//{
	//	mGameDebugDraw->DrawRect(child->get_RECT());
	//}
	mGameDebugDraw->DrawRect(mXman->get_RECT());
}
