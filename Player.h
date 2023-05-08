#pragma once

#include "Input.h"
#include "Model.h"
#include "PlayerBullet.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

/// <summary>
/// ���L����
/// </summary>
class Player {
public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(Model* model, uint32_t textureHandle);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(ViewProjection& viewProjection);

	/// <summary>
	/// �U��
	/// </summary>
	void Attack();

private:
	// ���[���h
	WorldTransform worldTransform_;
	// ���f��
	Model* model_ = nullptr;
	// �e�N�X�`��
	uint32_t textureHandle_ = 0;

	// �L�[�{�[�h����
	Input* input_ = nullptr;

	// �e
	PlayerBullet* bullet_ = nullptr;
};