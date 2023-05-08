#include "Player.h"
#include "ImGuiManager.h"
#include "assert.h"

void Player::Initialize(Model* model, uint32_t textureHandle) {
	// NULL�`�F�b�N
	assert(model);

	// �󂯓n��
	model_ = model;
	textureHandle_ = textureHandle;

	// ���[���h������
	worldTransform_.Initialize();

	// �V���O���C���X�^���X���擾
	input_ = Input::GetInstance();
}

void Player::Update() {
	// �ړ��x�N�g��
	Vector3 move = {0, 0, 0};
	// �ړ��̑���
	const float kCharacterSpeed = 0.2f;

	// �㉺���E�̈ړ�
	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}
	if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed;
	}

	// ����(��])�̑���
	const float kRotSpeed = 0.02f;
	// �����������ňړ��x�N�g����ύX
	if (input_->PushKey(DIK_A)) {
		worldTransform_.rotation_.y -= kRotSpeed;
	} else {
		worldTransform_.rotation_.y += kRotSpeed;
	}

	// �U������
	Attack();

	// �e�̍X�V
	if (bullet_) {
		bullet_->Update();
	}

	// �ړ����E���W
	const float kMoveLimitX = 30.0f;
	const float kMoveLimitY = 15.0f;

	// �͈͂𒴂��Ȃ�����
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

	// ���W�ړ�
	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z += move.z;

	// �s��X�V
	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	// �s��]��
	worldTransform_.TransferMatrix();

	// ImGui
	// �E�B���h�E�̃T�C�Y�A���W�̎w��
	ImGui::SetNextWindowPos({0, 0});
	ImGui::SetNextWindowSize({300, 100});

	ImGui::Begin("Debug");
	// ���W�ݒ�
	float sliderValue3[3] = {
	    worldTransform_.translation_.x, worldTransform_.translation_.y,
	    worldTransform_.translation_.z};
	ImGui::SliderFloat3("Player", sliderValue3, -20.0f, 20.0f);
	worldTransform_.translation_ = {sliderValue3[0], sliderValue3[1], sliderValue3[2]};

	ImGui::End();
}

void Player::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	// �e�̕`��
	if (bullet_) {
		bullet_->Draw(viewProjection);
	}
}

void Player::Attack() {
	if (input_->TriggerKey(DIK_SPACE)) {
		// �e�̐����Ə�����
		PlayerBullet* newBullet = new PlayerBullet;
		newBullet->Initialize(model_, worldTransform_.translation_);

		bullet_ = newBullet;
	}
}
