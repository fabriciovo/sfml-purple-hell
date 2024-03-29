#include "Hero.h"



Hero::Hero()
{
}

Hero::Hero(float x, float y, std::string name, std::string job, int hp, int power, int special, sf::Texture* texture)
{
	this->name = name;
	this->job = job;
	this->hp = hp;
	this->power = power;
	this->special = special;
	this->canUseSpecial = true;
	this->CreateSprite(texture);
	this->createAnimationComponent(*texture);
	this->SetPosition(x, y);
	this->selected = false;
	this->played = false;

	this->originalX = x;
	this->originalY = y;

	this->actionEffect = new Especial("slash");
	this->spell = new Especial(special, this->job);
	this->animationComponent->addAnimation("IDLE", 90.f, 0, 0, 1, 0, 18, 18);
}

Hero::Hero(std::string name, std::string job, int hp, int power, int special)
{
	this->selected = false;
	this->played = false;
	this->name = name;
	this->hp = hp;
	this->power = power;
	this->special = special;
	this->canUseSpecial = true;
}

Hero::Hero(Entity* hero)
{
	this->selected = false;
	this->played = false;
	this->name = hero->getName();
	this->hp = hero->getHp();
	this->power = hero->getPower();
	this->canUseSpecial = true;
}


Hero::~Hero()
{
	delete this->spell;
}
void Hero::Special(Entity* entity)
{
	this->spell->SetIsPlaying(true);
	this->spell->SetPosition(entity->getPosition().x, entity->getPosition().y + this->spell->GetOffsetY());
	entity->setDamage(this->power * 2);
	this->setCanUseSpecial(false);
	this->setPlayed(true);
	this->setSelected(false);
}

void Hero::Action(Entity* entity)
{
	this->actionEffect->SetIsPlaying(true);
	this->actionEffect->SetPosition(entity->getPosition().x, entity->getPosition().y);
	entity->setDamage(this->getPower());
	this->setPlayed(true);
	this->setSelected(false);
}

Especial* Hero::GetSpell()
{
	return this->spell;
}
Especial* Hero::GetAction()
{
	return this->actionEffect;
}


void Hero::UpdateAnimation(const float& dt)
{
	if (this->getHp() > 0) {
		this->animationComponent->play("IDLE", dt);
	}
}

void Hero::SetViewStatus(bool value)
{
	this->viewStatus = value;
}

bool Hero::GetViewStatus()
{
	return this->viewStatus;
}



