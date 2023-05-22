#include "Enemy.h"
#include "assert.h"

void Enemy::Initialize(Model* model, const Vector3& pos) {
	// NULLチェック
	assert(model);

	// 受け渡し
	model_ = model;

	// テクスチャ読み込み
	textureHandle_ = TextureManager::Load("cube.jpg");

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();

	// 初期座標の設定
	worldTransform_.translation_.x = pos.x;
	worldTransform_.translation_.y = pos.y;
	worldTransform_.translation_.z = pos.z;
}

void Enemy::Update() {
	
	switch (phase_) {
	case Enemy::Phase::Approch:
	default:
		//移動(ベクトル加算)
		worldTransform_.translation_.z -= 0.20f;
		//規定の位置に到達したら離脱
		if (worldTransform_.translation_.z < 0.0f) {
			phase_ = Enemy::Phase::Leave;
		}
		break;

	case Enemy::Phase::Leave:
		//移動(ベクトル加算)
		worldTransform_.translation_.x -= 0.20f;
		worldTransform_.translation_.y += 0.20f;
		break;
	}

	// 行列の更新
	worldTransform_.UpdateMatrix();
}

void Enemy::Draw(ViewProjection& viewProjection) {
	// 3Dモデルの描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
