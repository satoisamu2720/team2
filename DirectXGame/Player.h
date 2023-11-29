#pragma once
#include "ImGuiManager.h"
#include "Input.h"
#include "Model.h"
#include "PlayerBullet.h"
#include "RailCamera.h"
#include "TextureManager.h"
#include "VectraCalculation.h"
#include "WorldTransform.h"
#include "math.h"
#include <cassert>
#include <list>

class Player {
public:
	/// <summary>
	///
	/// </summary>
	~Player();
	
	/// <summary>
	/// 
	/// </summary>
	/// <param name="modelBody"></param>
	/// <param name="modelHead"></param>
	/// <param name="modelL_arm"></param>
	/// <param name="modelR_arm"></param>
	/// <param name="modelL_feet"></param>
	/// <param name="modelR_feet"></param>
	/// <param name="modelAttack"></param>
	/// <param name="BodyPosition"></param>
	/// <param name="HeadPosition"></param>
	/// <param name="L_armPosition"></param>
	/// <param name="R_armPosition"></param>
	/// <param name="L_feetPosition"></param>
	/// <param name="R_feetPosition"></param>
	/// <param name="AttackPosition"></param>
	void Initialize(
	    Model* modelBody, Model* modelHead, Model* modelL_arm, Model* modelR_arm,
	    Model* modelL_feet, Model* modelR_feet, Model* modelAttack, Vector3 BodyPosition,
	    Vector3 HeadPosition, Vector3 L_armPosition, Vector3 R_armPosition, Vector3 L_feetPosition,
	    Vector3 R_feetPosition, Vector3 AttackPosition);

	/// <summary>
	/// 
	/// </summary>
	void Update();

	/// <summary>
	/// 
	/// </summary>
	void Attack();
	
	/// <summary>
	/// 
	/// </summary>
	/// <param name="view"></param>
	void Draw(ViewProjection view,int playerLife);
	
	/// <summary>
	/// 
	/// </summary>
	void OnCollision();

	Vector3 GetWorldPosition();

	Vector3 GetAttackWorldPosition();
	
	 // ボスのライフ
	void SetLife(int32_t Life) { Life_ = Life; };
	int32_t GetLife() { return Life_; };


	void SetViewProjection(const ViewProjection* viewProjection) {
		viewProjection_ = viewProjection;
	}
	const WorldTransform& GetWorldTransform() { return worldTransform_; }
	const WorldTransform& GetAttack() { return worldTransformAttack_; }
	const int& GetPlayerAttackFlag() { return playerAttackFlag; }


private:
	WorldTransform worldTransform_;

	WorldTransform worldTransformBody_;
	WorldTransform worldTransformHead_;
	WorldTransform worldTransformL_arm_;
	WorldTransform worldTransformR_arm_;
	WorldTransform worldTransformL_feet_;
	WorldTransform worldTransformR_feet_;
	WorldTransform worldTransformAttack_;

	const ViewProjection* viewProjection_ = nullptr;

	Model* modelFighterBody_;
	Model* modelFighterHead_;
	Model* modelFighterL_arm_;
	Model* modelFighterR_arm_;
	Model* modelFighterL_feet_;
	Model* modelFighterR_feet_;
	Model* modelAttack_;

	Input* input_ = nullptr;
	float inputFloat[3]{0, 0, 0};
	int StopTimer = 0;
	RailCamera* railCamera_;
	FollowCamera* followCamera_;
	int playerJumpFlag = 0;
	int playerAttackFlag = 0;
	// キャラクターの移動ベクトル

	Vector3 velocity_ = {0, 0, 0};
	int walkModelTime = 0;
	int walkModelTimeFlag = 0;

	int playerAttackTimeFlag = 0;
	int playerAttackTime = 0;

	// ライフ
	int32_t Life_ = 6;
};