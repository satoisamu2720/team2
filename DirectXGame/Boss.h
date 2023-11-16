#pragma once
#include <Model.h>
#include <cassert>
#include<WorldTransform.h>
#include <LotEnemy.h>
#include<Input.h>
#include<list>
#include <VectraCalculation.h>

class Boss {
public:
	void Initialize(Model* modelB,Model*modelE);
	void Update();
	void Draw(const ViewProjection& viewProjection_);
	// 敵が出るタイミング
	void Timing();


	private:
	// ワールド変換データ
	    WorldTransform worldTransform_;
	// モデル
	Model* modelB_ = nullptr;
	    Model* modelE_ = nullptr;
	//ボスの回るスピード
	float RotateSpeed;


	// 小さい敵を複数にする
	std ::list<LotEnemy*> enemyNums_;
	//
	int TimingTimer=60;
};
