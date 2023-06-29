#include "PlayerBullet.h"
#include <cassert>

void PlayerBullet::Initialize(Model* model, const Vector3& pos, const Vector3& velocity) {
	// NULLポインタチェック
	assert(model);

	model_ = model;

	velocity_ = velocity;

	// テクスチャ読み込み
	texturehandle_ = TextureManager::Load("white1x1.png");

	// 初期化
	world_.Initialize();
	world_.translation_ = pos;
}

void PlayerBullet::Update() {

	// 座標を移動させる
	world_.translation_.x += velocity_.x;
	world_.translation_.y += velocity_.y;
	world_.translation_.z += velocity_.z;

	// 更新
	world_.UpdateMatrix();

	// 時間経過でデス
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
}

void PlayerBullet::Draw(ViewProjection& view) {
	// モデルの描画
	model_->Draw(world_, view, texturehandle_);
}

void PlayerBullet::OnCollision() {
	// デスフラグ
	isDead_ = true;
}

Vector3 PlayerBullet::GetWorldPosition() {
	Vector3 worldPos;

	worldPos.x = world_.translation_.x;
	worldPos.y = world_.translation_.y;
	worldPos.z = world_.translation_.z;

	return worldPos;
}
