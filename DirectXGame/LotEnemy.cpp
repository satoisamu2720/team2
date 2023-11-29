﻿#include "LotEnemy.h"


void LotEnemy::Initialize(Model* model,const Vector3&position,const Vector3& velocity) {

	// NULLポインタチェック
	assert(model);
	model_ = model;

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

	 worldTransform_.translation_ = {0.0f, 1.0f, 10.0f};
	
	//引数で受け取った速度をメンバ変数に代入
	velocity_ = velocity;

	deathTimer_ = 60;

	isDead_ = false;


}

void LotEnemy::Update() {

	//座標を移動させる(1フレーム分の移動量を足しこむ)
	/*worldTransform_.translation_.x += velocity_.x;
	worldTransform_.translation_.y += velocity_.y;
	worldTransform_.translation_.z += velocity_.z;*/

	// ワールドトランスフォームの更新　場所動かすときに使える
	worldTransform_.UpdateMatrix();

	//時間経過でデス
	if (--deathTimer_ <= 0) {
		isDead_ = true;
		deathTimer_ = 60;
	}


}

void LotEnemy::Draw(const ViewProjection& viewProjection_) {
	// 3Dモデルを描画
	
		model_->Draw(worldTransform_, viewProjection_);
	
		
	
}

void LotEnemy::OnCollision() {
		isDead_ = true;
}




