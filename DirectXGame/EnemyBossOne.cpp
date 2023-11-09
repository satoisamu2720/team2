#include "EnemyBossOne.h"

void EnemyBossOne::Initialize(Model* model, const Vector3& position) {

	assert(model);
	modelEnemyBossOne_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	
	
}

void EnemyBossOne::Update() {

	Vector3 move_ = {0, 0, 0};
	move_.y -= 0.5f; 
	// 行列更新
	worldTransform_.UpdateMatrix();
	worldTransform_.translation_ = Add(worldTransform_.translation_, move_);

	if (worldTransform_.translation_.y == -20.0f) {
		worldTransform_.translation_.y = 10.0f;
	}
}

void EnemyBossOne::Draw(ViewProjection view, int t) {

	if (t == 0) {
		modelEnemyBossOne_->Draw(worldTransform_, view);
	}
	
}
