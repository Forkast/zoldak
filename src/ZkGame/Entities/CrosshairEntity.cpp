#include <SFML/Graphics.hpp>

#include <QtGui>
#include <QDebug>

#include <memory>

#include "../../ZkCommon/Constants.h"
#include "../../ZkCommon/LibraryCast.h"

#include "../Renderables/Renderable.h"
#include "../Renderables/CrosshairRenderable.h"

#include "Entity.h"
#include "CrosshairEntity.h"
#include "PlayerEntity.h"
#include "../GameSystem.h"
#include "../InputSystem.h"

using namespace Zk::Common;
using namespace Zk::Game;

CrosshairEntity::CrosshairEntity(
	std::weak_ptr<PlayerEntity> owner,
	MouseDeviceHandle mdh
) :
	Entity(nullptr, nullptr),
	std::enable_shared_from_this<CrosshairEntity>()
{
	this->owner = owner;
	this->mouseDevice = mdh;
}

CrosshairEntity::~CrosshairEntity()
{
	
}

void CrosshairEntity::registerMe()
{
	setRenderable(new CrosshairRenderable(shared_from_this(), owner));
}

void CrosshairEntity::update(double step)
{
	auto ptr = owner.lock();
	
	if (ptr != nullptr)
	{
		sf::Vector2f radius =
			GameSystem::getInstance()->getViewportDimensions();
		sf::Vector3i mouseDelta = mouseDevice.getRelativePosition();
		sf::Vector2f delta =
			sf::Vector2f((float)mouseDelta.x, (float)mouseDelta.y)
			* (float)Constants::METERS_PER_PIXEL;
		
		relativePos += delta;
		
		//Może wyekstraktować to do jakiejś części odpowiedzialnej za majzę?
		if (relativePos.x >  radius.x)
			relativePos.x =  radius.x;
		if (relativePos.x < -radius.x)
			relativePos.x = -radius.x;
		
		if (relativePos.y >  radius.y)
			relativePos.y =  radius.y;
		if (relativePos.y < -radius.y)
			relativePos.y = -radius.y;
		
		//qDebug() << lib_cast<QPointF>(relativePos);
	}
	else
		markForDeletion();
}

sf::Vector2f CrosshairEntity::getCenterPosition() const
{
	auto ptr = owner.lock();
	
	if (ptr != nullptr)
		return ptr->getCenterPosition() + relativePos;
	else
		return sf::Vector2f();
}

EntityType CrosshairEntity::getType() const
{
	return EntityType::CrosshairEntity;
}
