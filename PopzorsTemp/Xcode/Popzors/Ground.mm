#include "Ground.h"

Ground::Ground(Vector3 pos, Color baseColor,
               Color blinkColor, Number blinktime)
    : Blinkable(baseColor, blinkColor, blinktime), pos(pos)
{
	//Make Ground
	body = new ScenePrimitive(ScenePrimitive::TYPE_PLANE, 15, 15);
	body->setPosition(pos);
    this->setColor(baseColor);
    //body->setMaterialByName("PodBlackMat");
}

Ground::~Ground()
{
}

void Ground::setColor(int r, int g, int b, int a)
{
	body->setColor(r,g,b,a);
    currentColor = Color(r, g, b, a);
}

void Ground::setColor(Color color)
{
	body->setColor(color);
    currentColor = color;
}

void Ground::addToCollisionScene(CollisionScene * scene)
{
    scene->addCollisionChild(body, CollisionSceneEntity::SHAPE_PLANE);
}

void Ground::removeFromCollisionScene(CollisionScene * scene)
{
    scene->removeEntity(body);
    delete body;
}

void Ground::reset()
{
    Blinkable::reset();
    body->setPosition(pos);
}

void Ground::update(Number elapsed)
{
    Blinkable::update(elapsed);
}
