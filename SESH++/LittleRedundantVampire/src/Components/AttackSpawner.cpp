#include "AttackSpawner.h"
#include "SpriteRenderer.h"
#include "../GameWorld.h"
#include "../Enum/ObjectTag.h"
#include <string>
#include "AnimationComponent.h"

using namespace sf;


void AttackSpawner::CreateAttack()
{
	if (canAttack)
	{
		*gameObject->GetIsMovable() = false;

		//TODO: tjek hvis den ryger ud af scope.
		GameObject* go = new GameObject();
		SpriteRenderer* sr = new SpriteRenderer(TextureTag::ATTACK_SHEET);
		//sr->SetSprite(TextureTag::ATTACK_SHEET);
		SpriteRenderer* sr = new SpriteRenderer();
		//Collider* col;


		sr->isSpriteSheet = true;
		sr->currentImage = new Vector2u(1, 1);
		sr->imageCount = new Vector2u(1, 3);


		if (*gameObject->GetObjectTag() == ObjectTag::PLAYER)
		{
			sr->SetSprite(TextureTag::PLAYER_ATTACK_SHEET);
			objectTag = ObjectTag::PLAYERATTACK;
		}
		else if (*gameObject->GetObjectTag() == ObjectTag::ENEMY)
		{
			sr->SetSprite(TextureTag::ENEMY_ATTACK_SHEET);
			objectTag = ObjectTag::ENEMYATTACK;
		}
		go->AddComponent(sr);


		*go->GetPosition() = *gameObject->GetPosition();
		*go->GetDirection() = *gameObject->GetDirection();

		int initialRow = 2;

		switch (*go->GetDirection())
		{
		case 'L':
			initialRow = 0;
			break;
		case 'R':
			initialRow = 0;
			break;
		case 'U':
			initialRow = 1;
			break;
		case 'D':
			initialRow = 2;
			break;
		}


		go->AddComponent(new Attack(objectTag, attackCooldown));

		AnimationComponent* aC = new AnimationComponent(sr, *sr->imageCount, 200.0f, initialRow);
		go->AddComponent(aC);

		SpriteRenderer& srRef = *sr;
		AnimationController* acController = new AnimationController(srRef, "2", "1", "2", "0", "0");
		go->AddComponent(acController);
		acController->ChangeAnimation.Attach(aC);


		//col = new  Collider(Vector2f(sr->GetSprite().getTexture()->getSize().x, sr->GetSprite().getTexture()->getSize().y), *go->GetPosition(), 0.0f, true);
		//go->AddComponent(col);
		//(*GameWorld::GetInstance()->GetColliders()).push_back(col);


		go->Awake();
		go->Start();

		(*GameWorld::GetInstance()->GetGameObjects()).push_back(go);


		attackTimer = 0.0f;
		canAttack = false;
	}
}


AttackSpawner::AttackSpawner(ObjectTag objectTag)
{
	this->objectTag = objectTag;

	attackCooldown = 250.0f;
	attackTimer = 0.0f;

	canAttack = true;
}

AttackSpawner::~AttackSpawner()
{

}


void AttackSpawner::Awake()
{

}

void AttackSpawner::Start()
{
}

void AttackSpawner::Update(Time* timePerFrame)
{
	attackTimer += timePerFrame->asMilliseconds();

	if (attackTimer >= attackCooldown)
	{
		canAttack = true;
		*gameObject->GetIsMovable() = true;
	}
}

void AttackSpawner::Destroy()
{
}

ComponentTag AttackSpawner::ToEnum()
{
	return ComponentTag::ATTACK_SPAWNER;
}
