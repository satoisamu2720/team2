#include "EnemyBossOne.h"

void EnemyBossOne::Initialize(Model* model, const Vector3& position) {

	assert(model);
	modelEnemyBossOne_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.scale_ = {8.0f, 8.0f, 8.0f};
	
}

void EnemyBossOne::Update() {

	Vector3 move= {0, 0, 0};
	move.y -= 0.5f; 
	// 行列更新
	worldTransform_.UpdateMatrix();
	worldTransform_.translation_ = Add(worldTransform_.translation_, move);

	if (worldTransform_.translation_.y <= 0.0f) {
		worldTransform_.translation_.y = 0.0f;
	}
}

void EnemyBossOne::Draw(ViewProjection view, int t) {

	if (t == 0) {
		modelEnemyBossOne_->Draw(worldTransform_, view);
	}
	
}
Vector3 EnemyBossOne::GetWorldPosition() {

	Vector3 worldPos;

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}