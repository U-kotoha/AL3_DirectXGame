#include "PlayerBullet.h"
#include <cassert>

void PlayerBullet::Initialize(Model* model, const Vector3& pos) {
	// NULL�|�C���^�`�F�b�N
	assert(model);

	model_ = model;

	// �e�N�X�`���ǂݍ���
	texturehandle_ = TextureManager::Load("white1x1.png");

	// ������
	world_.Initialize();
	world_.translation_ = pos;
}

void PlayerBullet::Update() {
	// �X�V
	world_.UpdateMatrix();
}

void PlayerBullet::Draw(ViewProjection& view) {
	// ���f���̕`��
	model_->Draw(world_, view, texturehandle_);
}
