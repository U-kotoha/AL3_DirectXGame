#include "Enemy.h"
#include "assert.h"

void Enemy::Initialize(Model* model, const Vector3& pos) {
	//NULLチェック
	assert(model);

	//受け渡し
	model_ = model;

	//テクスチャ読み込み
	textureHandle_ = TextureManager::Load("cube.jpg");

	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();

	//初期座標の設定
	worldTransform_.translation_.x = pos.x;
	worldTransform_.translation_.y = pos.y;
	worldTransform_.translation_.z = pos.z;
}

void Enemy::Update() {

	//座標移動
	worldTransform_.translation_.z -= 0.20f;

	//行列の更新
	worldTransform_.UpdateMatrix();
}

void Enemy::Draw(ViewProjection& viewProjection) {
	//3Dモデルの描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
