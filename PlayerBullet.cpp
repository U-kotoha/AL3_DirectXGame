#include "PlayerBullet.h"
#include <cassert>

void PlayerBullet::Initialize(Model* model, const Vector3& pos) {
	// NULLポインタチェック
	assert(model);

	model_ = model;

	// テクスチャ読み込み
	texturehandle_ = TextureManager::Load("white1x1.png");

	// 初期化
	world_.Initialize();
	world_.translation_ = pos;
}

void PlayerBullet::Update() {
	// 更新
	world_.UpdateMatrix();
}

void PlayerBullet::Draw(ViewProjection& view) {
	// モデルの描画
	model_->Draw(world_, view, texturehandle_);
}
