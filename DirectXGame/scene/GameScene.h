#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Player.h"
#include "DebugCamera.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Skydome.h"
#include "RailCamera.h"
#include "FollowCamera.h"
#include "Ground.h"
#include "AreaItem.h"
#include "EnemyBossOne.h"
#include <memory>
#include <Boss.h>
#include<LotEnemy.h>
#include<list>

    /// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

	

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ

	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// アイテムとプレイヤー
	/// </summary>
	void ItemOnCollision();

	void GamePlayUpdate();
	void TitleUpdate();
	void GameOverUpdate();
	void GameClearUpdate();

	void Reset();
	//void TitleDraw2DNear();
	//void GameOverDraw2DNear(); // ゲームオーバー
private: // メンバ変数
	// テクスチャハンドル

	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	uint32_t textureHandle_ = 0;
	Sprite* sprite_ = nullptr;

	std::unique_ptr<Model> modelFighterBody_;
	std::unique_ptr<Model> modelFighterHead_;
	std::unique_ptr<Model> modelFighterL_arm_;
	std::unique_ptr<Model> modelFighterR_arm_;
	
	std::unique_ptr<Model> modelBossBody_;
	std::unique_ptr<Model> modelBossArm_;
	std::unique_ptr<Model> modelLotEnemy_;
	
	std::unique_ptr<Model> modelFighterL_feet_;
	std::unique_ptr<Model> modelFighterR_feet_;
	std::unique_ptr<Model> modelAreaItem_;
	std::unique_ptr<Model> modelEnemyBossOne_;
	std::unique_ptr<Model> modelPlayerAttack_;

	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	uint32_t soundDataHandle_ = 0;
	uint32_t voiceHandle_ = 0;

	float inputFloat3[3] = {0, 0, 0};

	std::unique_ptr<DebugCamera> debugCamera_;
	std::unique_ptr<Player> player_;
	std::unique_ptr<Boss> boss_;
	std::unique_ptr<LotEnemy> lotenemy_;
	std::unique_ptr<Skydome>skydome_;
	std::unique_ptr<AreaItem> areaItem_;
	std::unique_ptr<EnemyBossOne> enemyBossOne_;
	

	Model* modelSkydome_ = nullptr;
	std::unique_ptr<Ground> ground_;
	Model* modelGround_ = nullptr;
	

	Vector3 velocity_;

	//サウンド
	uint32_t BGMSound_=0;
	uint32_t LotDanageSound_ = 0;
	uint32_t BossDamageSound_ = 0;
	uint32_t ItemSound_ = 0;
	uint32_t SystemSound_ = 0;
	
	//const WorldTransform& GetWorldTransform() { return matProjection; }

	bool isDebugCameraActive_ = false;
	std::unique_ptr<RailCamera> railCamera_;
	std::unique_ptr<FollowCamera> followCamera_;
	    int CollisionFlag = 0;
		int areaItemCollisionFlag = 1;
	    int enemyAttackCollisionFlag = 0;
	    int enemyAttackFlag = 0;
		int areaItemCollisionTimeFlag = 0;
	    int areaItemCollisionTime = 0;
	    int areaItemCollisionTimeCount = 60*5;


		
		// シーン切り替え
	    int sceneMode_ = 1;
		
		int playerLife_ = 6;
	    int bossLife_ = 20;
	    int flag;
	/// <summary>
	/// ゲームシーン用
	/// </summary>
};