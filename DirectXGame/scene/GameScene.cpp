#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"
#include "VectraCalculation.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
	
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	audio_ = Audio::GetInstance();
	input_ = Input::GetInstance();
	textureHandle_ = TextureManager::Load("genshin.png");

	modelFighterBody_.reset(Model::CreateFromOBJ("body", true));
	modelFighterHead_.reset(Model::CreateFromOBJ("head", true));
	modelFighterL_arm_.reset(Model::CreateFromOBJ("arm_left", true));
	modelFighterR_arm_.reset(Model::CreateFromOBJ("arm_right", true));
	modelFighterL_feet_.reset(Model::CreateFromOBJ("feet_left", true));
	modelFighterR_feet_.reset(Model::CreateFromOBJ("feet_right", true));
	modelAreaItem_.reset(Model::CreateFromOBJ("body", true));
	modelEnemyBossOne_.reset(Model::CreateFromOBJ("feet_right", true));
	modelPlayerAttack_.reset(Model::CreateFromOBJ("head", true));
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
	Vector3 attackPosition(0.0f ,-2.0f ,3.0f);
	// 自キャラの初期化
	player_->Initialize(
		modelFighterBody_.get(), modelFighterHead_.get(), modelFighterL_arm_.get(),
	    modelFighterR_arm_.get(), modelFighterL_feet_.get(), modelFighterR_feet_.get(),
	    modelPlayerAttack_.get(),
	    bodyPosition, headPosition, l_amrPosition, r_amrPosition, l_feetPosition, r_feetPosition, attackPosition);

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
	areaItem_->Initialize(modelAreaItem_.get(), {10.0f, 0.0f, 0.0f});

	enemyBossOne_ = std::make_unique<EnemyBossOne>();
	enemyBossOne_->Initialize( modelEnemyBossOne_.get(), {
		areaItem_->GetItemWorldTransform().translation_.x,
		10.0f,
		areaItem_->GetItemWorldTransform().translation_.z
		}
	);

	player_->SetViewProjection(&followCamera_->GetViewProjection());

	debugCamera_ = std::make_unique<DebugCamera>(1280,720);
	//軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	//軸方向表示が参照するビュープロジェクションを指定する(アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());

}

void GameScene::Update() {
	player_->Update(); 
	skydome_->Update();
	ground_->Update();
	areaItem_->Update();
	
	
	debugCamera_->Update();
	//デバックカメラのifdef

	#ifdef _DEBUG
	if (input_->TriggerKey(DIK_0) && isDebugCameraActive_ == false) {
		isDebugCameraActive_ = true;
	} else if (input_->TriggerKey(DIK_0) && isDebugCameraActive_ == true) {
		isDebugCameraActive_ = false;
		
	}
    #endif
	

	
	//カメラ処理
	if (isDebugCameraActive_ == true) {
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		//ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();
	} else {
		followCamera_->Update();
		//railCamera_->Update();

		viewProjection_.matView = followCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = followCamera_->GetViewProjection().matProjection;

		/*viewProjection_.matView = railCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = railCamera_->GetViewProjection().matProjection;*/
		viewProjection_.TransferMatrix();

		

	}
	OnCollision();
}
void GameScene::OnCollision() {
	if (areaItemCollisionFlag == 1 && player_->GetPlayerAttackFlag() == 1) {
		// 差を求める
		float dx =
		    abs(player_->GetAttackWorldPosition().x -
		        areaItem_->GetItemWorldTransform().translation_.x);
		float dz =
		    abs(player_->GetAttackWorldPosition().z -
		        areaItem_->GetItemWorldTransform().translation_.z);
		// 衝突したら
		if (dx < 2 && dz < 2) {
			areaItemCollisionTimeFlag = 1;
			areaItemCollisionFlag = 0;
		}
	}
	
	if (areaItemCollisionFlag == 1) {
		// 差を求める
		float dx = abs(
		    player_->GetWorldTransform().translation_.x - areaItem_->GetItemWorldTransform().translation_.x);
		float dz =
		    abs(player_->GetWorldTransform().translation_.z - areaItem_->GetItemWorldTransform().translation_.z);
		// 衝突したら
		if (dx < 2 && dz < 1) {
			areaItemCollisionTimeFlag = 1;
			areaItemCollisionFlag = 0;
		}
	}
	if (areaItemCollisionTimeFlag == 1) {
		enemyBossOne_->Update();
		areaItemCollisionTime++;
	}
	if (areaItemCollisionTime >= areaItemCollisionTimeCount) {
		areaItemCollisionTimeFlag = 0;
		areaItemCollisionTime = 0;
		areaItemCollisionFlag = 1;
	}
	ImGui::Begin("Debug");
	ImGui::InputInt("areaItemCollisionFlag", &areaItemCollisionFlag);
	ImGui::InputInt("areaItemCollisionTimeFlag", &areaItemCollisionTimeFlag);
	ImGui::InputInt("areaItemCollisionTimeCount", &areaItemCollisionTimeCount);
	ImGui::End();
}
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
	player_->Draw(viewProjection_);
	skydome_->Draw(viewProjection_);
	ground_->Draw(viewProjection_);
	areaItem_->Draw(viewProjection_, areaItemCollisionFlag);
	enemyBossOne_->Draw(viewProjection_, areaItemCollisionFlag);

	Model::PostDraw();



	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる

	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();


}

	