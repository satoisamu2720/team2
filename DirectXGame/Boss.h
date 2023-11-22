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
	// 衝突を検出したら呼び出されるコールバック関数
	//アイテム
	void ItemOnColision();


	//小さい敵
	const std::list<LotEnemy*>& GetLotEnemys() const { return enemyNums_; }

		const WorldTransform& GetWorldTransform() { return worldTransform_; }
	 // ボスのライフ
	void SetLife(int32_t Life) { Life_ = Life; };
	int32_t GetLife() { return Life_; };

	private:
	Input* input_ = nullptr;
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

	// ライフ
	int32_t Life_ = 0;
	
	// 行動フェーズ
	enum class Phase {
		Attack, // 攻撃する
		noAttack,    // 攻撃しない
	};
	// フェーズ　
	Phase phase_;

//小さい敵を消した後に生き返らせる
	int RespawnTime=600;

};
