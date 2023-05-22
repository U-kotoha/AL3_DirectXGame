#include "Enemy.h"
#include "MathUtility.h"
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
	
	// デスフラグの立った弾を削除
	bullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	//switch (phase_) {
	//case Enemy::Phase::Approch:
	//default:
	//	//移動(ベクトル加算)
	//	worldTransform_.translation_.z -= 0.20f;
	//	//規定の位置に到達したら離脱
	//	if (worldTransform_.translation_.z < 0.0f) {
	//		phase_ = Enemy::Phase::Leave;
	//	}
	//	break;

	//case Enemy::Phase::Leave:
	//	//移動(ベクトル加算)
	//	worldTransform_.translation_.x -= 0.20f;
	//	worldTransform_.translation_.y += 0.20f;
	//	break;
	//}

	Fire();

	// 弾の更新
	for (EnemyBullet* bullet : bullets_) {
		bullet->Update();
	}

	// 行列の更新
	worldTransform_.UpdateMatrix();
}

void Enemy::Draw(ViewProjection& viewProjection) {
	// 3Dモデルの描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	// 弾の描画
	for (EnemyBullet* bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}

void Enemy::Fire() {
	// 弾の速度
	const float kBulletSpeed = 1.0f;
	Vector3 velocity(0, 0, kBulletSpeed);

	// 速度ベクトルを自機の向きに合わせて回転させる
	velocity = TransformNormal(velocity, worldTransform_.matWorld_);

	// 弾の生成と初期化
	EnemyBullet* newBullet = new EnemyBullet;
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);

	// 弾の登録
	bullets_.push_back(newBullet);
}
