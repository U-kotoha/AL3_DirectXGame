#include "Enemy.h"
#include "assert.h"

void Enemy::Initialize(Model* model, const Vector3& pos) {
	//NULLチェック
	assert(model);

	//受け渡し
	model_ = model;

	//テクスチャ読み込み
	textureHandle_ = TextureManager::Load("cube.jpg");

	//ワールド初期化
	worldTransform_.Initialize();

	//初期座標の設定
	worldTransform_.translation_ = pos;
}

void Enemy::Update() {

	//座標移動
	worldTransform_.translation_.x += 1.0f;
	worldTransform_.translation_.y += 1.0f;
	worldTransform_.translation_.z += 1.0f;

	//更新
	worldTransform_.UpdateMatrix();

	//行列更新
	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
}

void Enemy::Draw(ViewProjection& viewProjection) {
	//3Dモデルの描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
