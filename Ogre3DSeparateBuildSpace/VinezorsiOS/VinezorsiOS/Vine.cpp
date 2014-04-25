//
//  Vine.cpp
//  Testing
//
//  Created by Calvin Phung on 9/13/13.
//
//
#include "Vine.h"

extern Util::ConfigGlobal globals;

static int vineID = 0;

Vine::Vine()
: parentNode(NULL), meshType(VINE_FLOWER_SHIP), entireVine(NULL), tip(NULL), base(NULL), shockwaveEffect(NULL), boostEffect(NULL), radius(0.0), loc(NO_DIRECTION), dest(NO_DIRECTION), transition(0.0), previoust(0.0), previousID(0), aftert(0.0), afterID(0)
{}

Vine::Vine(Ogre::SceneNode* parentNode, Vector3 pos, float radius)
: parentNode(parentNode), meshType(VINE_FLOWER_SHIP), entireVine(NULL), tip(NULL), base(NULL), shockwaveEffect(NULL), boostEffect(NULL), forward(), radius(radius), loc(NO_DIRECTION), dest(NO_DIRECTION), transition(0.0), totalElapsed(0.0), wobbleSpeed(0.0), wobbling(false)
{
    loadShip();
}

Vine::~Vine()
{
    removeFromScene();
}

void Vine::reloadIfNecessary(VineMeshType newMeshType)
{
    if (meshType != newMeshType)
    {
        meshType = newMeshType;
        loadShip();
    }
}

void Vine::loadShip()
{
    switch (meshType)
    {
        case VINE_BASIC_SHIP:
            loadBasicShip();
            break;
        case VINE_RUNNER_SHIP:
            loadRunnerShip();
            break;
        default:
            loadFlowerShip();
            break;
    }
    ++vineID;
}

void Vine::loadBasicShip()
{
    removeFromScene();
    entireVine = parentNode->createChildSceneNode("entireVineNode" + Util::toStringInt(vineID));
    
    tip = entireVine->createChildSceneNode("vineTipNode" + Util::toStringInt(vineID));
    
    Entity* tipEntity = tip->getCreator()->createEntity("vineTipEntity" + Util::toStringInt(vineID), "sphereMesh");
    tipEntity->setMaterialName("General/VineTop");
    tip->attachObject(tipEntity);
    tip->scale(radius,radius,radius);
    
    base = entireVine->createChildSceneNode("vineBaseNode" + Util::toStringInt(vineID));
     
    Entity* baseEntity = base->getCreator()->createEntity("vineBaseEntity" + Util::toStringInt(vineID), "cylinderMesh");
    baseEntity->setMaterialName("General/VineBase");
    base->attachObject(baseEntity);
    base->translate(0, -radius / 3.0, 0);
    base->scale(radius * 1.5, radius / 1.5, radius * 1.5);
}

void Vine::loadRunnerShip()
{
    removeFromScene();
    entireVine = parentNode->createChildSceneNode("entireVineNode" + Util::toStringInt(vineID));
    
    tip = entireVine->createChildSceneNode("vineTipNode" + Util::toStringInt(vineID));
    
    Entity* tipEntity = tip->getCreator()->createEntity("vineTipEntity" + Util::toStringInt(vineID), "Ships/new_ship_mesh.mesh");
    tip->attachObject(tipEntity);
    tip->scale(radius / 1.5, radius / 1.5, radius / 1.5);
    tip->yaw(Degree(180.0));
    tipEntity->getSubEntity(3)->setMaterialName("General/WallBindingC");
    tipEntity->getSubEntity(7)->setMaterialName("General/WallBindingC");
}

void Vine::loadFlowerShip()
{
    removeFromScene();
    entireVine = parentNode->createChildSceneNode("entireVineNode" + Util::toStringInt(vineID));
    
    tip = entireVine->createChildSceneNode("vineTipNode" + Util::toStringInt(vineID));
    
    Entity* tipEntity = tip->getCreator()->createEntity("vineTipEntity" + Util::toStringInt(vineID), "Ships/flowerVehicle.mesh");
    tip->attachObject(tipEntity);
    tip->yaw(Degree(180.0));
    tip->scale(0.5, 0.5, 0.5);
    
    // Problem with transparency not carrying over... assign custom material
    tipEntity->getSubEntity(0)->setMaterialName("General/VineShellActive");
}

VineMeshType Vine::getMeshType() const
{
    return meshType;
}

SceneNode* Vine::getEntireVine() const
{
	return entireVine;
}

SceneNode* Vine::getTip() const
{
	return tip;
}

SceneNode* Vine::getBase() const
{
	return base;
}

Vector3 Vine::getPos() const
{
	return entireVine->getPosition();
}

void Vine::setPos(Vector3 value)
{
	entireVine->setPosition(value);
}

Vector3 Vine::getForward() const
{
	return forward;
}

void Vine::setForward(Vector3 value)
{
	forward = value;
}

float Vine::getRadius() const
{
    return radius;
}

void Vine::setQuaternion(Quaternion rot)
{
    entireVine->setOrientation(rot);
}

void Vine::setVisible(bool value)
{
    entireVine->setVisible(value);
}

void Vine::setWobble(bool value)
{
    wobbling = value;
    totalElapsed = 0.0;
    wobbleSpeed = 0.0;
}

void Vine::setShockwave()
{
    if (!shockwaveEffect)
    {
        shockwaveEffect = parentNode->getCreator()->createParticleSystem("StarShockwave", "General/StarShockwave");
        entireVine->attachObject(shockwaveEffect);
    }
}

void Vine::setBoost()
{
    if (!boostEffect)
    {
        boostEffect = parentNode->getCreator()->createParticleSystem("StarBoost", "General/StarBoost");
        tip->attachObject(boostEffect);
    }
}

void Vine::move(Vector3 delta)
{
	entireVine->translate(delta);
}

float length = 1.0f;
float originalHeight = 0.0f;

void Vine::update(float elapsed)
{
    tip->resetOrientation();
    tip->yaw(Degree(180.0));
    if (wobbling)
    {
        totalElapsed += elapsed;
        wobbleSpeed += elapsed;
        if (wobbleSpeed > 2.0)
            wobbleSpeed = 2.0;
        
        tip->pitch(-8 * Degree(sin(8 * (2.2-wobbleSpeed) * totalElapsed)));
        tip->roll(16 * Degree(sin(8 * (2.2-wobbleSpeed) * totalElapsed)));
        tip->translate(0.0,-0.1*sin(4*(2.1-wobbleSpeed) * totalElapsed),0.0);
        
        if (totalElapsed >= length) {
            setWobble(false);
            Vector3 fixHeight = tip->getPosition();
            fixHeight.y = originalHeight;
            tip->setPosition(fixHeight);
        }
    }
    else {
        Vector3 pos = tip->getPosition();
        originalHeight = pos.y;
    }
}

void Vine::removeShockwave()
{
    if (shockwaveEffect)
    {
        entireVine->detachObject(shockwaveEffect);
        entireVine->getCreator()->destroyParticleSystem(shockwaveEffect);
        shockwaveEffect = NULL;
    }
}

void Vine::removeBoost()
{
    if (boostEffect)
    {
        tip->detachObject(boostEffect);
        tip->getCreator()->destroyParticleSystem(boostEffect);
        boostEffect = NULL;
    }
}

void Vine::removeFromScene()
{
    if (base)
    {
        base->getCreator()->destroyMovableObject(base->getAttachedObject(0)); // Assuming only one entity
        base->removeAndDestroyAllChildren();
        base->getCreator()->destroySceneNode(base);
        base = NULL;
    }
    if (tip)
    {
        removeBoost();
        tip->getCreator()->destroyMovableObject(tip->getAttachedObject(0)); // Assuming only one entity
        tip->removeAndDestroyAllChildren();
        tip->getCreator()->destroySceneNode(tip);
        tip = NULL;
    }
    if (entireVine)
    {
        removeShockwave();
        entireVine->removeAndDestroyAllChildren();
        entireVine->getCreator()->destroySceneNode(entireVine);
        entireVine = NULL;
    }
}
