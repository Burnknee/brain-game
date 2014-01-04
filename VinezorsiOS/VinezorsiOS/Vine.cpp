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
: parentNode(NULL), entireVine(NULL), tip(NULL), base(NULL), shell(NULL), radius(0.0), loc(NO_DIRECTION), dest(NO_DIRECTION), transition(0.0), previoust(0.0), previousID(0), aftert(0.0), afterID(0)
{}

Vine::Vine(Ogre::SceneNode* parentNode, Vector3 pos, float radius)
: parentNode(parentNode), entireVine(NULL), tip(NULL), base(NULL), shell(NULL), forward(), radius(radius), loc(NO_DIRECTION), dest(NO_DIRECTION), transition(0.0), totalElapsed(0.0), wobbleSpeed(0.0), wobbling(false)
{
    switch (globals.setVineShip)
    {
        case 0:
            loadBasicShip();
            break;
        case 1:
            loadFlowerShip();
            break;
        default:
            loadRunnerShip();
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
    
    Entity* tipEntity = tip->getCreator()->createEntity("vineTipEntity" + Util::toStringInt(vineID), "runnerShip.mesh");
    tip->attachObject(tipEntity);
    tip->scale(radius / 1.5, radius / 1.5, radius / 1.5);
    tip->yaw(Degree(180.0));
    
    /*
    shell = entireVine->createChildSceneNode("shellNode" + Util::toStringInt(vineID));
    Entity* shellEntity = shell->getCreator()->createEntity("vineShellEntity" + Util::toStringInt(vineID), "sphereMesh");
    shellEntity->setMaterialName("General/VineShell");
    shell->attachObject(shellEntity);
    shell->scale(
        globals.podAppearance * (globals.tunnelSegmentDepth + globals.tunnelSegmentBuffer),
        globals.podAppearance * (globals.tunnelSegmentDepth + globals.tunnelSegmentBuffer),
        globals.podAppearance * (globals.tunnelSegmentDepth + globals.tunnelSegmentBuffer));
    shell->setScale(radius * 2.5, radius * 2.5, radius * 2.5);
    */
    
//    tipEntity->getSubEntity(0)->setMaterialName("General/PodYellow");
//    tipEntity->getSubEntity(1)->setMaterialName("General/PodRed");
//    tipEntity->getSubEntity(2)->setMaterialName("General/PodBlue");
//    tipEntity->getSubEntity(3)->setMaterialName("General/PodGreen");
}

void Vine::loadFlowerShip()
{
    removeFromScene();
    entireVine = parentNode->createChildSceneNode("entireVineNode" + Util::toStringInt(vineID));
    
    tip = entireVine->createChildSceneNode("vineTipNode" + Util::toStringInt(vineID));
    
    Entity* tipEntity = tip->getCreator()->createEntity("vineTipEntity" + Util::toStringInt(vineID), "flowerVehicle.mesh");
    tip->attachObject(tipEntity);
    tip->yaw(Degree(180.0));
    tip->scale(0.5, 0.5, 0.5);
}

SceneNode* Vine::getTip() const
{
	return tip;
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

void Vine::setWobble(bool value)
{
    wobbling = value;
    totalElapsed = 0.0;
    wobbleSpeed = 0.0;
}

void Vine::move(Vector3 delta)
{
	entireVine->translate(delta);
}

void Vine::update(float elapsed)
{
    if (wobbling)
    {
        totalElapsed += elapsed;
        wobbleSpeed += elapsed;
        if (wobbleSpeed > 2.0)
            wobbleSpeed = 2.0;
        entireVine->roll(15 * Degree(sin(32 * wobbleSpeed * totalElapsed)));
        if (totalElapsed >= 0.5)
            setWobble(false);
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
        tip->getCreator()->destroyMovableObject(tip->getAttachedObject(0)); // Assuming only one entity
        tip->removeAndDestroyAllChildren();
        tip->getCreator()->destroySceneNode(tip);
        tip = NULL;
    }
    if (shell)
    {
        shell->getCreator()->destroyMovableObject(tip->getAttachedObject(0)); // Assuming only one entity
        shell->removeAndDestroyAllChildren();
        shell->getCreator()->destroySceneNode(shell);
        shell = NULL;
    }
    
    if (entireVine)
    {
        entireVine->removeAndDestroyAllChildren();
        entireVine->getCreator()->destroySceneNode(base);
        entireVine = NULL;
    }
}
