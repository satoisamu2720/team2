#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"
#include "VectraCalculation.h"

GameScene::GameScene() {
}

GameScene::~GameScene() {
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	audio_ = Audio::GetInstance();
	input_ = Input::GetInstance();
	textureHandle_ = TextureManager::Load("Elife.png");

	playerLifeTextureHandle_[0] = TextureManager::Load("Plife/Plife1.png");
	playerLifeTextureHandle_[1] = TextureManager::Load("Plife/Plife2.png");
	playerLifeTextureHandle_[2] = TextureManager::Load("Plife/Plife3.png");
	playerLifeTextureHandle_[3] = TextureManager::Load("Plife/Plife4.png");
	playerLifeTextureHandle_[4] = TextureManager::Load("Plife/Plife5.png");

	/*for (int i = 0; i < 4; i++) {
		playerLifeSprite_[i] = Sprite::Create(playerLifeTextureHandle_[i], {0, 0});
	}*/

	playerLifeSprite_[0] = Sprite::Create(playerLifeTextureHandle_[0], {0, 0});
	playerLifeSprite_[1] = Sprite::Create(playerLifeTextureHandle_[1], {0, 0});
	playerLifeSprite_[2] = Sprite::Create(playerLifeTextureHandle_[2], {0, 0});
	playerLifeSprite_[3] = Sprite::Create(playerLifeTextureHandle_[3], {0, 0});
	playerLifeSprite_[4] = Sprite::Create(playerLifeTextureHandle_[4], {0, 0});


	titleTextureHandle_ = TextureManager::Load("Title2.png");
	gameOverTextureHandle_ = TextureManager::Load("gameover.png");
	gameClearTextureHandle_ = TextureManager::Load("clear.png");

	titleSprite_ = Sprite::Create(titleTextureHandle_, {0, 0});
	gameOverSprite_ = Sprite::Create(gameOverTextureHandle_, {0, 0});
	gameClearSprite_ = Sprite::Create(gameClearTextureHandle_, {0, 0});

	modelFighterBody_.reset(Model::CreateFromOBJ("body", true));
	modelFighterHead_.reset(Model::CreateFromOBJ("head", true));
	modelFighterL_arm_.reset(Model::CreateFromOBJ("arm_left", true));
	modelFighterR_arm_.reset(Model::CreateFromOBJ("arm_right", true));
	modelFighterL_feet_.reset(Model::CreateFromOBJ("feet_left", true));
	modelFighterR_feet_.reset(Model::CreateFromOBJ("feet_right", true));
	modelAreaItem_.reset(Model::CreateFromOBJ("body", true));
	modelEnemyBoss_.reset(Model::CreateFromOBJ("BOSS", true));
	modelEnemyBossOne_[0].reset(Model::CreateFromOBJ("BossAttackArm", true));
	modelEnemyBossOne_[1].reset(Model::CreateFromOBJ("BossAttackArm", true));
	modelPlayerAttack_.reset(Model::CreateFromOBJ("head", true));
	modelenemyLife_.reset(Model::Create());
	modelBossBody_.reset(Model::CreateFromOBJ("Boss_body", true));
	modelBossArm_.reset(Model::CreateFromOBJ("Boss_arm", true));

		modelLotEnemy_.reset(Model::CreateFromOBJ("lotenemy", true));
	

	modelSkydome_ = Model::CreateFromOBJ("sky", true);
	modelGround_ = Model::CreateFromOBJ("ground", true);
	worldTransform_.Initialize();
	
	
	viewProjection_.Initialize();

	player_ = std::make_unique<Player>();
	Vector3 bodyPosition(0, 0, 0);
	Vector3 headPosition(0, 2.5f, 0);
	Vector3 l_amrPosition(-1.5f, 1, 0);
	Vector3 r_amrPosition(1.5f, 1, 0);
	Vector3 l_feetPosition(-0.5f, -2, 0);
	Vector3 r_feetPosition(0.5f, -2, 0);
	Vector3 attackPosition(0.0f ,0.0f ,9.0f);
	// 自キャラの初期化
	player_->Initialize(
		modelFighterBody_.get(), modelFighterHead_.get(), modelFighterL_arm_.get(),
	    modelFighterR_arm_.get(), modelFighterL_feet_.get(), modelFighterR_feet_.get(),
	    modelPlayerAttack_.get(),
	    bodyPosition, headPosition, l_amrPosition, r_amrPosition, l_feetPosition, r_feetPosition, attackPosition);

	boss_ = std::make_unique<Boss>();
	boss_->Initialize(
	    modelAreaItem_.get(), modelBossArm_.get(), modelBossBody_.get(),
	    modelLotEnemy_.get());
	enemyLife_ = std::make_unique<EnemyLife>();
	enemyLife_->Initialize(modelenemyLife_.get(), textureHandle_);


		/*lotenemy_ = std::make_unique<Boss>();
		lotenemy_->Initialize(modelLotEnemy_.get());*/
	

	skydome_ = std::make_unique<Skydome>();
	skydome_->Initialize(modelSkydome_);
	ground_ = std::make_unique<Ground>();
	ground_->Initialize(modelGround_, {0.0f,-0.2f,0.0f});
	
	railCamera_ = std::make_unique<RailCamera>();
	railCamera_->Initialize({0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f});

	followCamera_ = std::make_unique<FollowCamera>();
	followCamera_->Initialize({0.0f, 0.0f, 0.0f}, {0.1f, 0.0f, 0.0f});
	followCamera_->SetTarget(&player_->GetWorldTransform());

	areaItem_ = std::make_unique<AreaItem>();
	areaItem_->Initialize(modelAreaItem_.get(), {0.0f, 0.0f, 0.0f});

	enemyBossOne_ = std::make_unique<EnemyBossOne>();
	enemyBossOne_->Initialize(
	    modelEnemyBossOne_[0].get(), modelEnemyBossOne_[1].get(),
	    {
		areaItem_->GetItemWorldTransform().translation_.x,
		50.0f,
		areaItem_->GetItemWorldTransform().translation_.z
		}
	);
	

	player_->SetViewProjection(&followCamera_->GetViewProjection());
	


	debugCamera_ = std::make_unique<DebugCamera>(1280,720);
	//軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	//軸方向表示が参照するビュープロジェクションを指定する(アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());


	//サウンド
	BGMSound_ = audio_->LoadWave("sound/BGM.wav");
	LotDanageSound_ = audio_->LoadWave("sound/lotdamage.wav");
	BossDamageSound_ = audio_->LoadWave("sound/bossdamage.wav");
	ItemSound_ = audio_->LoadWave("sound/item.wav");
	SystemSound_ = audio_->LoadWave("sound/system.wav");

	audio_->PlayWave(soundDataHandle_,true,0.2f);
	//音は適当に用意したものなので気に入らなければ変更
	// 一応ファイルには他にボスの腕が落ちる音と自機の攻撃の音が入ってる
	//敵からのダメージ音各場所に置く
	// ボスと小さいの
	//audio_->PlayWave(LotDanageSound_);
	audio_->PlayWave(BossDamageSound_);
	//シーン切り替えとかのキーを押したときの音
	audio_->PlayWave(SystemSound_);
}

void GameScene::Update() {

	switch (sceneMode_) {
	case 0:
		GamePlayUpdate();
		break;
	case 1:
		TitleUpdate();
		break;
	case 2:
		GameOverUpdate();
		break;
	case 3:
		GameClearUpdate();
		break;
	}
    

}

void GameScene::GamePlayUpdate() {
	player_->Update();
	boss_->Update();
	enemyLife_->Update();
	skydome_->Update();
	ground_->Update();
	areaItem_->Update();
	enemyBossOne_->Update(enemyAttackFlag);
	debugCamera_->Update();
	// デバックカメラのifdef

#ifdef _DEBUG
	if (input_->TriggerKey(DIK_0) && isDebugCameraActive_ == false) {
		isDebugCameraActive_ = true;
	} else if (input_->TriggerKey(DIK_0) && isDebugCameraActive_ == true) {
		isDebugCameraActive_ = false;
	}
#endif

	// カメラ処理
	if (isDebugCameraActive_ == true) {
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		// ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();
	} else {
		followCamera_->Update();
		// railCamera_->Update();

		viewProjection_.matView = followCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = followCamera_->GetViewProjection().matProjection;

		/*viewProjection_.matView = railCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = railCamera_->GetViewProjection().matProjection;*/
		viewProjection_.TransferMatrix();
	}

	ItemOnCollision();
	if (playerLife_ <= 0) {
		sceneMode_ = 2;
	}
	if (bossLife_ <= 0) {
		sceneMode_ = 3;
	}

	
}



void GameScene::TitleUpdate() {

if (input_->TriggerKey(DIK_SPACE)) {
		// リセット
		sceneMode_ = 0;
		audio_->PlayWave(SystemSound_);
	}
}

void GameScene::GameOverUpdate() {
	if (input_->TriggerKey(DIK_SPACE)) {
		Initialize();
		audio_->PlayWave(SystemSound_);
		sceneMode_ = 1;
		Reset();
	}


}
void GameScene::GameClearUpdate() {
	if (input_->TriggerKey(DIK_SPACE)) {
		Initialize();
		audio_->PlayWave(SystemSound_);
		sceneMode_ = 1;
		Reset();
	}
}



void GameScene::ItemOnCollision() {


	// アイテムとプレイヤーの判定
	if (areaItemCollisionFlag == 1) {
		// 差を求める
		float dx =
		    abs(player_->GetWorldPosition().x - areaItem_->GetItemWorldTransform().translation_.x);
		float dz =
		    abs(player_->GetWorldPosition().z - areaItem_->GetItemWorldTransform().translation_.z);
		// 衝突したら
		float dist = dx * dx + dz * dz;
		dist = sqrtf(dist);
		if (dist <= 3) {
			areaItemCollisionTimeFlag = 1;
			areaItemCollisionFlag = 0;
			enemyAttackFlag = 1;
			boss_->ItemOnCollisions();
			areaItem_->Random();
			audio_->PlayWave(ItemSound_);
		}
	}


	//プレイヤー攻撃と敵の腕判定
	if (player_->GetPlayerAttackFlag() == 1 && enemyAttackFlag == 1) {
		
		// 差を求める
		float dx = abs(player_->GetAttackWorldPosition().x - enemyBossOne_->GetWorldPosition().x);
		float dz = abs(player_->GetAttackWorldPosition().z - enemyBossOne_->GetWorldPosition().z);
		float dy = abs(player_->GetAttackWorldPosition().y - enemyBossOne_->GetWorldPosition().y);
		// 衝突したら
		float dist = dx * dx + dy * dy + dz * dz;
		dist = sqrtf(dist);
		if (dist <= 10) {
			areaItemCollisionTimeFlag = 1;
			bossLife_ -=1;
			boss_->ItemOnCollisions();
			enemyAttackHitFlag = 1;
			audio_->PlayWave(BossDamageSound_);
		}
		
	}
	
	//敵の腕とプレイヤーの判定
	if (enemyAttackCollisionFlag == 1) {
		float dx = player_->GetWorldPosition().x - enemyBossOne_->GetWorldPosition().x;
		float dz = player_->GetWorldPosition().z - enemyBossOne_->GetWorldPosition().z;
		float dy = player_->GetWorldPosition().y - enemyBossOne_->GetWorldPosition().y;
		float dist = dx * dx + dy * dy + dz * dz;
		dist = sqrtf(dist);
		// 10 = 二つの円の半径足したもの
		if (dist <= 10) {
			playerLife_ -= 1;
			enemyAttackCollisionFlag = 0;
			boss_->ItemOnCollisions();
			areaItemCollisionFlag = 0;
			areaItem_->Random();
			audio_->PlayWave(ItemSound_);
		}
	}
	//if (lotCollisionFlag == 1) {
	//	float dx = abs(player_->GetWorldPosition().x - boss_->GetWorldPosition().x);
	//	float dz = abs(player_->GetWorldPosition().z - boss_->GetWorldPosition().z);
	//	// 衝突したら
	//	float dist = dx * dx + dz * dz;
	//	dist = sqrtf(dist);
	//	if (dist <= 10) {
	//		// 衝突したら

	//		areaItemCollisionTimeFlag = 1;
	//		lotCollisionFlag = 0;
	//		playerLife_ -= 1;
	//		boss_->ItemOnCollisions();
	//	}
	//}
     if (areaItemCollisionTimeFlag == 1) {
		areaItemCollisionTime++;
	 }
	 if (areaItemCollisionTime == 60) {
		enemyAttackCollisionFlag = 1;
	 }

	if (areaItemCollisionTime >= areaItemCollisionTimeCount) {
		areaItemCollisionTimeFlag = 0;
		areaItemCollisionTime = 0;
		enemyAttackFlag = 0;
		areaItemCollisionFlag = 1;
		enemyAttackCollisionFlag = 0;
		enemyAttackHitFlag=0;
		lotCollisionFlag = 1;
	}
	
	

#ifdef _DEBUG
	
	ImGui::Begin("Debug");
	ImGui::InputInt("playerLIfe", &playerLife_);
	ImGui::InputInt("bossLife_", &bossLife_);
	ImGui::InputInt("lotCollisionFlag", &lotCollisionFlag);
	ImGui::InputInt("enemyAttackCollisionFlag", &enemyAttackCollisionFlag);
	ImGui::InputInt("areaItemCollisionTimeFlag", &areaItemCollisionTimeFlag);
	ImGui::InputInt("areaItemCollisionTimeCount", &areaItemCollisionTimeCount);
	ImGui::End();



#endif // _DEBUG
}
void GameScene::playerLife2DNear() {
	if (playerLife_ == 5) {
		playerLifeSprite_[4]->Draw();
	}
	if (playerLife_ == 4) {
		playerLifeSprite_[3]->Draw();
	}
	if (playerLife_ == 3) {
		playerLifeSprite_[2]->Draw();
	}
	if (playerLife_ == 2) {
		playerLifeSprite_[1]->Draw();
	}
	if (playerLife_ == 1) {
		playerLifeSprite_[0]->Draw();
	}
}

void GameScene::TitleDraw2DNear() { titleSprite_->Draw(); }

void GameScene::GameOverDraw2DNear() { gameOverSprite_->Draw(); }

void GameScene::GameClearDraw2DNear() { gameClearSprite_->Draw(); }


	void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();


	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();



	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	player_->Draw(viewProjection_,playerLife_);
	boss_->Draw(viewProjection_);
	skydome_->Draw(viewProjection_);
	ground_->Draw(viewProjection_);
	areaItem_->Draw(viewProjection_, areaItemCollisionFlag);
	enemyBossOne_->Draw(viewProjection_, enemyAttackFlag, enemyAttackHitFlag);
	enemyLife_->Draw(viewProjection_,bossLife_);
	Model::PostDraw();



	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);
	if (sceneMode_ == 0) {
		playerLife2DNear();
		
	}
	if (sceneMode_ == 1) {
		TitleDraw2DNear();
		
	}
	if (sceneMode_ == 2) {
		GameOverDraw2DNear();
		
	}
	if (sceneMode_ == 3) {
		GameClearDraw2DNear();
		
	}
	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる

	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();


}

	void GameScene::Reset() {
	CollisionFlag = 0;
	areaItemCollisionFlag = 1;
	enemyAttackCollisionFlag = 0;
	enemyAttackFlag = 0;
	areaItemCollisionTimeFlag = 0;
	areaItemCollisionTime = 0;
	areaItemCollisionTimeCount = 60 * 5;
	// シーン切り替え
	sceneMode_ = 1;
	playerLife_ = 5;
	bossLife_ = 10;
    }

   

    
   