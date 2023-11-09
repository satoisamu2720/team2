#include "Boss.h"

void Boss::Initialize(Model* model) {
	// NULLポインタチェック
	assert(model);
	 model_= model;

	worldTransform_.Initialize();
	 RotateSpeed = 0.01f;
	TimingTimer = 60;


}

void Boss::Update() {
	// 行列更新
	worldTransform_.UpdateMatrix();
	//ボスの回転
	worldTransform_.rotation_.y += RotateSpeed;

	// デスフラグの経った敵の削除
	enemyNums_.remove_if([](LotEnemy* enemynum) {
		if (enemynum->IsDead()) {
			delete enemynum;
			return true;
		}
		return false;
	});

	// 小さい敵の更新
	for (LotEnemy* enemynum : enemyNums_) {
		enemynum->Update();
	}

	// 小さい敵の発生
	Timing();
	TimingTimer--;
}

void Boss::Draw(const ViewProjection& viewProjection_) {
	// 3Dモデルを描画
	model_->Draw(worldTransform_, viewProjection_);

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
		Vector3 velocity(0.1f, 0, 0.1f);
		//速度ベクトルを自機に向きに合わせて回転させる
		velocity = TransformNormal(velocity, worldTransform_.matWorld_);
		// 敵の生成
		LotEnemy* newEnemynum = new LotEnemy();
		newEnemynum->Initialize(model_, worldTransform_.translation_,velocity);
		// 敵の登録
		enemyNums_.push_back(newEnemynum);
		TimingTimer = 60;
	}
}

