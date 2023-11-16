#include "FollowCamera.h"

void FollowCamera::Initialize(const Vector3& position, const Vector3& rotation) {
	
	viewProjection_.Initialize();
	viewProjection_.translation_ = position;
	viewProjection_.rotation_ = rotation;

	input_ = Input::GetInstance();
}

void FollowCamera::Update() {

	
	// 追従対象からカメラまでのオフセット
	Vector3 offset_ = {0.0f, 10.0f, -20.0f};
	if (target_) {
		

		 float kRotSpeed = 0.05f;

		if (input_->PushKey(DIK_LEFT)) {
			viewProjection_.rotation_.y -= kRotSpeed;
		} else if (input_->PushKey(DIK_RIGHT)) {
			viewProjection_.rotation_.y += kRotSpeed;
		}
		// 押した方向で移動ベクトルを変更（上下）
		if (input_->PushKey(DIK_UP)) {
			viewProjection_.rotation_.x += kRotSpeed;
		} else if (input_->PushKey(DIK_DOWN)) {
			viewProjection_.rotation_.x -= kRotSpeed;
		}
		 rotateYMatrix_ = MakeRotateYMatrix(viewProjection_.rotation_.y);
		offset_ = TransformNormal(offset_, rotateYMatrix_);


		// 座標をコピーしてオフセット分ずらす
		viewProjection_.translation_ = Add(target_->translation_, offset_);
		
	}

	viewProjection_.UpdateMatrix();

	
	float translation_[3] = {
	    worldTransform_.translation_.x, worldTransform_.translation_.y,
	    worldTransform_.translation_.z
	};
	float rotation_[3] = {
	    viewProjection_.rotation_.x, viewProjection_.rotation_.y, viewProjection_.rotation_.z
	};
	
	ImGui::Begin("offset Camera");
	ImGui::DragFloat3("Camera Translation_", translation_, 0.01f,30.0f);
	ImGui::DragFloat3("Camera Rotation", rotation_, 0.01f, 30.0f);
	ImGui::End();

	/*viewProjection_.translation_.x = translation_[0];
	viewProjection_.translation_.y = translation_[1];
	viewProjection_.translation_.z = translation_[2];*/

	viewProjection_.rotation_.x = rotation_[0];
	viewProjection_.rotation_.y = rotation_[1];
	viewProjection_.rotation_.z = rotation_[2];
}