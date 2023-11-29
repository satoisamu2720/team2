#include "Boss.h"

void Boss::Initialize(Model* model, Model* modelA,Model * modelB, Model* modelE) {
	// NULLポインタチェック
	assert(model);
	model_ = model;
	assert(modelB);
	 modelB_= modelB;
	assert(modelE);
	modelE_ = modelE;
	assert(modelA);
	modelA_ = modelA;
	
	worldTransform_.Initialize();
	worldTransformArm_.Initialize();
	worldTransformBody_.Initialize();
	worldTransformLot_.Initialize();

	 RotateSpeed = 0.01f;
	TimingTimer = 60;
	 worldTransform_.translation_ = {0.0f, 1.0f, 30.0f};
	worldTransform_.scale_ = {8.0f, 8.0f, 8.0f};
	worldTransformArm_.translation_ = {0.0f, 8.0f, 0.0f};
	 worldTransformBody_.translation_ = {0.0f, 8.0f, 0.0f};
	worldTransformLot_.parent_ = &worldTransform_;
	worldTransformArm_.parent_ = &worldTransform_;
	 worldTransformBody_.parent_ = &worldTransform_;

	// ライフ
	Life_ = 20;

	RespawnTime = 600;

	phase_ = Phase::Attack;

}

void Boss::Update() {
	// 行列更新
	worldTransform_.UpdateMatrix();
	worldTransformArm_.UpdateMatrix();
	worldTransformBody_.UpdateMatrix();
	worldTransformLot_.UpdateMatrix();
	//フェーズ
	switch (phase_) { 
	case Phase::Attack:
	default:
		// ボスの回転
		worldTransformLot_.rotation_.y += RotateSpeed;

		// 小さい敵の発生
		Timing();
		TimingTimer--;

		// 小さい敵の更新
		for (LotEnemy* enemynum : enemyNums_) {
			enemynum->Update();
		}

		break;

		case Phase::noAttack:
		// デスフラグの経った敵の削除
		enemyNums_.remove_if([](LotEnemy* enemynum) {
			if (enemynum->IsDead()) {
				delete enemynum;
				return true;
			}
			return false;
		});
		
		//10秒経ったらまた攻撃し始める
		RespawnTime -= 1;
		if (RespawnTime <= 0) {
			phase_ = Phase::Attack;
			RespawnTime = 600;
		}
			break;
	}

}

void Boss::Draw(const ViewProjection& viewProjection_) {
	// 3Dモデルを描画
	modelA_->Draw(worldTransformArm_, viewProjection_);
	modelB_->Draw(worldTransformBody_, viewProjection_);
	//model_->Draw(worldTransform_, viewProjection_);

	// 小さい敵の描画複数
	for (LotEnemy* enemynum : enemyNums_) {
		enemynum->Draw(viewProjection_);
	}
}

// 小さい敵複数
void Boss::Timing() {

	//タイマーが0になったら
	if (TimingTimer<=0) {
		//小さい敵の速度
		Vector3 velocity(0.2f, 0, 0.2f);
		//速度ベクトルを自機に向きに合わせて回転させる
		velocity = TransformNormal(velocity, worldTransformLot_.matWorld_);
		// 敵の生成
		LotEnemy* newEnemynum = new LotEnemy();
		newEnemynum->Initialize(modelE_, worldTransformLot_.translation_, velocity);
		// 敵の登録
		enemyNums_.push_back(newEnemynum);
		TimingTimer = 20;
	}
}

void Boss::ItemOnCollisions() {
	//アイテムとプレイヤーが当たったら小さい敵全員が死ぬ
	for (LotEnemy* enemynum : enemyNums_) {
			enemynum->OnCollision();
	}
	phase_ = Phase::noAttack;
}

