#include "Enemy.h"
#include "MathUtility.h"
#include "assert.h"

Enemy::~Enemy() {
	// 弾の解放
	for (EnemyBullet* bullet : bullets_) {
		delete bullet;
	}
}

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

	// 接近フェーズ初期化
	Approch_();
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
		worldTransform_.translation_.z = 40.0f;
		phase_ = Enemy::Phase::Approch;
		break;
	}

	// 弾の更新
	for (EnemyBullet* bullet : bullets_) {
		bullet->Update();
	}

	// 行列更新
	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	// 行列転送
	worldTransform_.TransferMatrix();
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

void Enemy::Approch_() {
	// 発射タイマーカウントダウン
	fireTimer--;

	//指定時間に達した
	if (fireTimer <= 60) {
		Fire();
		// 発射タイマーを初期化
		fireTimer = kFireInterval;
	}
}
