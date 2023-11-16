#pragma once
#include "Player.h"


Player::~Player() {

}


void Player::Initialize(
	Model* modelBody, Model* modelHead, Model* modelL_arm, Model* modelR_arm, Model* modelL_feet,
    Model* modelR_feet, Model* modelAttack, Vector3 BodyPosition, Vector3 HeadPosition,
    Vector3 L_armPosition,
    Vector3 R_armPosition, Vector3 L_feetPosition, Vector3 R_feetPosition, Vector3 AttackPosition) {

	assert(modelBody);
	assert(modelHead);
	assert(modelL_arm);
	assert(modelR_arm);
	assert(modelL_feet);
	assert(modelR_feet);
	assert(modelAttack);

	modelFighterBody_ = modelBody;
	modelFighterHead_ = modelHead;
	modelFighterL_arm_ = modelL_arm;
	modelFighterR_arm_ = modelR_arm;
	modelFighterL_feet_ = modelL_feet;
	modelFighterR_feet_ = modelR_feet;
	modelAttack_ = modelAttack;

	worldTransform_.Initialize();
	worldTransformBody_.Initialize();
	worldTransformHead_.Initialize();
	worldTransformL_arm_.Initialize();
	worldTransformR_arm_.Initialize();
	worldTransformL_feet_.Initialize();
	worldTransformR_feet_.Initialize();
	worldTransformAttack_.Initialize();

	worldTransformBody_.translation_ = BodyPosition;
	worldTransformHead_.translation_ = HeadPosition;
	worldTransformL_arm_.translation_ = L_armPosition;
	worldTransformR_arm_.translation_ = R_armPosition;
	worldTransformL_feet_.translation_ = L_feetPosition;
	worldTransformR_feet_.translation_ = R_feetPosition;

	worldTransformL_arm_.rotation_.x = 3.15f;
	worldTransformR_arm_.rotation_ .x= 3.15f;
	worldTransformR_feet_.rotation_.x = 3.15f;
	worldTransformL_feet_.rotation_.x = 3.15f;
	input_ = Input::GetInstance();
	worldTransformBody_.translation_ = Add(worldTransformBody_.translation_, BodyPosition);
	worldTransformHead_.translation_ = Add(worldTransformHead_.translation_, HeadPosition);
	worldTransformL_arm_.translation_ = Add(worldTransformL_arm_.translation_, L_armPosition);
	worldTransformR_arm_.translation_ = Add(worldTransformR_arm_.translation_, R_armPosition);
	worldTransformL_feet_.translation_ = Add(worldTransformL_feet_.translation_, L_feetPosition);
	worldTransformR_feet_.translation_ = Add(worldTransformR_feet_.translation_, R_feetPosition);
	worldTransformAttack_.translation_ = Add(worldTransformAttack_.translation_, AttackPosition);
};

void Player::Update() {


	//worldTransform_.TransferMatrix();

	Vector3 move_ = { 0, 0, 0 };

	// キャラクターの移動速度
	const float kCharacterSpeed = 0.5f;
	//const float kRotSpeed = 0.05f;
	if (input_->PushKey(DIK_W)) {
		move_.z += kCharacterSpeed;
		walkModelTimeFlag = 1;
	} else if (input_->PushKey(DIK_S)) {
		move_.z -= kCharacterSpeed;
		walkModelTimeFlag = 1;
	} /*else {
		worldTransformR_feet_.rotation_.x = 3.15f;
		worldTransformL_feet_.rotation_.x = 3.15f;
	}*/

	// 押した方向で移動ベクトルを変更（左右）
	if (input_->PushKey(DIK_A)) {
		walkModelTimeFlag = 1;
		move_.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_D)) {
		walkModelTimeFlag = 1;
		move_.x += kCharacterSpeed;
	}
	Attack();
	if (input_->PushKey(DIK_SPACE)) {
		playerJumpFlag = 1;
		
	}
	if (playerJumpFlag == 1) {
		move_.y += kCharacterSpeed*2;
	}
	if (worldTransformHead_.translation_.y >= 10.0f) {
		playerJumpFlag = 0;
	}
	if (playerJumpFlag == 0 && worldTransformHead_.translation_.y >= 0) {
		move_.y -= kCharacterSpeed*2;
	}
	if (walkModelTimeFlag == 1) {
		walkModelTime++;
		if (walkModelTime <= 8) {
			worldTransformL_feet_.rotation_.x += 0.1f;
			worldTransformR_feet_.rotation_.x -= 0.1f;
		}
		if (walkModelTime >= 16 && walkModelTime <= 24) {
			worldTransformL_feet_.rotation_.x -= 0.1f;
			worldTransformR_feet_.rotation_.x += 0.1f;
		} 
		if (walkModelTime >= 24 && walkModelTime <= 32) {
			worldTransformL_feet_.rotation_.x -= 0.1f;
			worldTransformR_feet_.rotation_.x += 0.1f;
		} 
		if (walkModelTime >= 32) {
			worldTransformL_feet_.rotation_.x += 0.1f;
			worldTransformR_feet_.rotation_.x -= 0.1f;
		}
		if (walkModelTime == 40) {
			worldTransformR_feet_.rotation_.x = 3.15f;
			worldTransformL_feet_.rotation_.x = 3.15f;
			walkModelTime = 0;
			walkModelTimeFlag = 0;
		}
	} else {
		walkModelTime = 0;
		walkModelTimeFlag = 0;
	}

	move_ = TransformNormal(move_, MakeRotateYMatrix(viewProjection_->rotation_.y));
	// Y軸周り角度
	worldTransformBody_.rotation_.y = std::atan2(move_.x, move_.z);
	// ベクターの加算
	worldTransformBody_.translation_ = Add(worldTransformBody_.translation_, move_);
	// 行列更新
	worldTransformBody_.UpdateMatrix();


	// Y軸周り角度
	worldTransformHead_.rotation_.y = std::atan2(move_.x, move_.z);
	// ベクターの加算
	worldTransformHead_.translation_ = Add(worldTransformHead_.translation_, move_);
	// 行列更新
	worldTransformHead_.UpdateMatrix();


	// Y軸周り角度
	worldTransformL_arm_.rotation_.y = std::atan2(move_.x, move_.z);
	// ベクターの加算
	worldTransformL_arm_.translation_ = Add(worldTransformL_arm_.translation_, move_);
	// 行列更新
	worldTransformL_arm_.UpdateMatrix();


	// Y軸周り角度
	worldTransformR_arm_.rotation_.y = std::atan2(move_.x, move_.z);
	// ベクターの加算
	worldTransformR_arm_.translation_ = Add(worldTransformR_arm_.translation_, move_);
	// 行列更新
	worldTransformR_arm_.UpdateMatrix();


	// Y軸周り角度
	worldTransformL_feet_.rotation_.y = std::atan2(move_.x, move_.z);
	// ベクターの加算
	worldTransformL_feet_.translation_ = Add(worldTransformL_feet_.translation_, move_);
	// 行列更新
	worldTransformL_feet_.UpdateMatrix();

	// Y軸周り角度
	worldTransformR_feet_.rotation_.y = std::atan2(move_.x, move_.z);
	// ベクターの加算
	worldTransformR_feet_.translation_ = Add(worldTransformR_feet_.translation_, move_);
	// 行列更新
	worldTransformR_feet_.UpdateMatrix();

	// Y軸周り角度
	worldTransformAttack_.rotation_.y = std::atan2(move_.x, move_.z);
	// ベクターの加算
	worldTransformAttack_.translation_ = Add(worldTransformAttack_.translation_, move_);
	// 行列更新
	worldTransformAttack_.UpdateMatrix();


	float imputFloat3[3] = {
	    worldTransformHead_.rotation_.x, worldTransformHead_.rotation_.y,
	    worldTransformHead_.rotation_.z};

	//デバッグ
	ImGui::Begin("Debug");
	ImGui::Text("Toggle Camera Flag :  LEFT SHIFT key");
	ImGui::SliderFloat3("player", imputFloat3, -30.0f, 30.0f);
	ImGui::End();
	worldTransformHead_.rotation_.x = imputFloat3[0];
	worldTransformHead_.rotation_.y = imputFloat3[1];
	worldTransform_.rotation_.z = imputFloat3[2];

	//// 移動限界座標
	//const float kMoveLimitX = 34;
	//const float kMoveLimitY = 18;

	//// 範囲を超えない処理
	//worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	//worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	//worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	//worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

	
}

void Player::Attack() {
	if (input_->PushKey(DIK_L)) {
		playerAttackFlag = 1;
		worldTransformR_arm_.rotation_.x -= 0.1f;
	} else {
		playerAttackFlag = 0;
	}

}

void Player::Draw(ViewProjection view) { 

	modelFighterBody_->Draw(worldTransformBody_, view);
	modelFighterHead_->Draw(worldTransformHead_, view);
	modelFighterL_arm_->Draw(worldTransformL_arm_, view);
	modelFighterR_arm_->Draw(worldTransformR_arm_, view);
	modelFighterL_feet_->Draw(worldTransformL_feet_, view);
	modelFighterR_feet_->Draw(worldTransformR_feet_, view);
	if (playerAttackFlag == 1) {
		modelAttack_->Draw(worldTransformAttack_, view);
	}
	
};
void Player::OnCollision() {  }


Vector3 Player::GetWorldPosition() {

	Vector3 worldPos;

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return  worldPos;
}
	
