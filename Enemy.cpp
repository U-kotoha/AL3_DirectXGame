#include "Enemy.h"

void Enemy::Initialize() {

}

void Enemy::Update() {


	switch (phase_) {
	case Approch:
	default:
		worldTransform_.translation_ += 接近フェーズの速度;

		    if (worldTransform_.translation_.z < 0.0f) {
			phase_ = Leave;
		}
		break;
	case Leave:
		worldTransform_.translation_ += 離脱フェーズの速度 break;
	}
}

void Enemy::Draw(ViewProjection& viewProjection) {

}
