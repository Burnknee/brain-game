//
//  Util.cpp
//  Testing
//
//  Created by Calvin Phung on 8/27/13.
//
//

#include "Util.h"

#include <vector>
#include <cstdlib>
#include <sstream>
#include <iomanip>

Util::ConfigGlobal::ConfigGlobal()
{
    const Vector3 TUNNEL_REFERENCE_FORWARD = Vector3(0, 0, -1);
    const Vector3 TUNNEL_REFERENCE_UPWARD = Vector3(0, 1, 0);
    const Vector3 TUNNEL_REFERENCE_RIGHT = Vector3(1, 0, 0);
    const int TUNNEL_MIN_ANGLE_TURN = 0; //Configurable
    const int TUNNEL_MAX_ANGLE_TURN = 3; //Configurable
    const double TUNNEL_SEGMENT_WIDTH = 25.0; //Configurable
    const double TUNNEL_SEGMENT_DEPTH = 25.0; //Configurable
    const double TUNNEL_SEGMENT_BUFFER = 25;
    const double TUNNEL_WALL_LENGTH = TUNNEL_SEGMENT_WIDTH / (2 * Math::Cos(Ogre::Radian(Math::PI) / 4) + 1);
    const int TUNNEL_SEGMENTS_PER_SECTION = 5;
    const int TUNNEL_SEGMENTS_PER_POD = 3;
    const int TUNNEL_SEGMENTS_BEFORE_REFRESH = TUNNEL_SEGMENTS_PER_SECTION * 2;
    const int INITIATION_SECTIONS = 1;
    const double VINE_T_OFFSET = 1.5;
    const double VINE_RADIUS = 1.5;
    const int POD_APPEARANCE = 2;
    const double POD_HEAD_RADIUS = TUNNEL_SEGMENT_WIDTH / 25;
    const double POD_STEM_RADIUS = TUNNEL_SEGMENT_WIDTH / 100;
    const double POD_STEM_LENGTH = TUNNEL_WALL_LENGTH / 2;
    const int POD_NBACK_CHANCE = 33;
    const double SEAT_LENGTH = POD_HEAD_RADIUS * 2;
    
    const int TUNNEL_SECTIONS = 5;
    const int NBACK = 2; //Configurable
    const int CONTROL = 1; //Configurable
    const int HISTORY_MODE = -1; //Confiugrable
    
    const int STARTING_HP = 0;
    const int HP_NEGATIVE_LIMIT = -6;
    const int HP_POSITIVE_LIMIT = 6;
    const int HP_NEGATIVE_CORRECT_ANSWER = 2;
    const int HP_NEGATIVE_WRONG_ANSWER = -1;
    const int HP_POSITIVE_CORRECT_ANSWER = 1;
    const int HP_POSITIVE_WRONG_ANSWER = -2;
    const double DRAIN_SPEED = 2;
    const double INIT_CAM_SPEED = 15.0;
    const double MODIFIER_CAM_SPEED = 5.0;
    const double MIN_CAM_SPEED = 5.0;
    const double MAX_CAM_SPEED = 25.0;
    const double NLEVEL_SPEED_MODIFIER = 0.8;

    const int NUM_TO_SPEED_UP = 3;
    const int NUM_TO_SPEED_DOWN = 1;
    const double STEPSIZE_SPEED_UP = 3.0;
    const double STEPSIZE_SPEED_DOWN = -3.0;
    
    const double HP_BAR_XREF = 0.05;
    const double HP_BAR_YREF = 0.05;
    const double HP_BAR_WIDTH = 0.9;
    const double HP_BAR_HEIGHT = 0.05;
    
    const int SCREEN_WIDTH = 1024;
    const int SCREEN_HEIGHT = 800;
    
    const double TIMED_RUN_TIMER = 120.0;
    const double TIMED_RUN_CONTROL_UP_DIST1 = 3000.0;
    const double TIMED_RUN_CONTROL_UP_DIST2 = 7500.0;
    const double TIMED_RUN_CONTROL_UP_DIST3 = 20000.0;
    
    progressionMode = 2;
    gameMode = 1;
    tunnelReferenceForward = TUNNEL_REFERENCE_FORWARD;
    tunnelReferenceUpward = TUNNEL_REFERENCE_UPWARD;
    tunnelReferenceRight = TUNNEL_REFERENCE_RIGHT;
    tunnelMinAngleTurn = TUNNEL_MIN_ANGLE_TURN;
    tunnelMaxAngleTurn = TUNNEL_MAX_ANGLE_TURN;
    tunnelSegmentWidth = TUNNEL_SEGMENT_WIDTH;
    tunnelSegmentDepth = TUNNEL_SEGMENT_DEPTH;
    tunnelSegmentBuffer = TUNNEL_SEGMENT_BUFFER;
    tunnelWallLength = TUNNEL_WALL_LENGTH;
    tunnelSegmentsPerSection = TUNNEL_SEGMENTS_PER_SECTION;
    tunnelSegmentsPerPod = TUNNEL_SEGMENTS_PER_POD;
    tunnelSegmentsBeforeRefresh = TUNNEL_SEGMENTS_BEFORE_REFRESH;
    initiationSections = INITIATION_SECTIONS;
    vineTOffset = VINE_T_OFFSET;
    vineRadius = VINE_RADIUS;
    podAppearance = POD_APPEARANCE;
    podHeadRadius = POD_HEAD_RADIUS;
    podStemRadius = POD_STEM_RADIUS;
    podStemLength = POD_STEM_LENGTH;
    podNBackChance = POD_NBACK_CHANCE;
    seatLength = SEAT_LENGTH;
    tunnelSections = TUNNEL_SECTIONS;
    nback = NBACK;
    control = CONTROL;
    historyMode = HISTORY_MODE;
    startingHP = STARTING_HP;
    HPNegativeLimit = HP_NEGATIVE_LIMIT;
    HPPositiveLimit = HP_POSITIVE_LIMIT;
    HPNegativeCorrectAnswer = HP_NEGATIVE_CORRECT_ANSWER;
    HPNegativeWrongAnswer = HP_NEGATIVE_WRONG_ANSWER;
    HPPositiveCorrectAnswer = HP_POSITIVE_CORRECT_ANSWER;
    HPPositiveWrongAnswer = HP_POSITIVE_WRONG_ANSWER;
    drainSpeed = DRAIN_SPEED;
    initCamSpeed = INIT_CAM_SPEED;
    modifierCamSpeed = MODIFIER_CAM_SPEED;
    minCamSpeed = MIN_CAM_SPEED;
    maxCamSpeed = MAX_CAM_SPEED;
    nlevelSpeedModifier = NLEVEL_SPEED_MODIFIER;
    numToSpeedUp = NUM_TO_SPEED_UP;
    numToSpeedDown = NUM_TO_SPEED_DOWN;
    stepsizeSpeedUp = STEPSIZE_SPEED_UP;
    stepsizeSpeedDown = STEPSIZE_SPEED_DOWN;
    HPBarXRef = HP_BAR_XREF;
    HPBarYRef = HP_BAR_YREF;
    HPBarWidth = HP_BAR_WIDTH;
    HPBarHeight = HP_BAR_HEIGHT;
    screenWidth = SCREEN_WIDTH;
    screenHeight = SCREEN_HEIGHT;
    timedRunTimer = TIMED_RUN_TIMER;
    timedRunControlUpDist1 = TIMED_RUN_CONTROL_UP_DIST1;
    timedRunControlUpDist2 = TIMED_RUN_CONTROL_UP_DIST2;
    timedRunControlUpDist3 = TIMED_RUN_CONTROL_UP_DIST3;
}

// Updates variables that depend on other globals, should call this if a global has changed
void Util::ConfigGlobal::set()
{
    viewportMainWidth_modeRight = screenWidth - 224;
    viewportMainHeight_modeRight = screenHeight;
    viewportSideWidth_modeRight = 224;
    viewportSideHeight_modeRight = screenHeight;
    
    viewportMainWidth_modeBottom = screenWidth;
    viewportMainHeight_modeBottom = screenHeight - 100;
    viewportSideWidth_modeBottom = screenWidth;
    viewportSideHeight_modeBottom = 100;
    
    viewportMainWidth_modeNone = screenWidth;
    viewportMainHeight_modeNone = screenHeight;
    viewportSideWidth_modeNone = 0;
    viewportSideHeight_modeNone = 0;

    label1_posX = screenWidth / 2;
    label1_posY = 3 * screenHeight / 40;
    label2_posX = screenWidth / 80;
    label2_posY = 5 * screenHeight / 40;
    label3_posX = 11 * screenWidth / 15;
    label3_posY = 5 * screenHeight / 40;
    label4_posX = screenWidth / 80;
    label4_posY = 7 * screenHeight / 40;
}

// Returns the degrees from 0-359 for a direction where SOUTH is 0
int Util::getDegrees(Direction dir)
{
	switch (dir)
	{
        case NORTHWEST:
            return 225;
        case NORTH:
            return 180;
        case NORTHEAST:
            return 135;
        case EAST:
            return 90;
        case SOUTHEAST:
            return 45;
        case SOUTH:
            return 0;
        case SOUTHWEST:
            return 270;
        case WEST:
            return 315;
        default:
            return 0;
	}
}

Direction Util::leftOf(Direction dir)
{
	switch (dir)
	{
        case NORTHWEST:
            return WEST;
        case NORTH:
            return NORTHWEST;
        case NORTHEAST:
            return NORTH;
        case EAST:
            return NORTHEAST;
        case SOUTHEAST:
            return EAST;
        case SOUTH:
            return SOUTHEAST;
        case SOUTHWEST:
            return SOUTH;
        case WEST:
            return SOUTHWEST;
        default:
            return NO_DIRECTION;
	}
}

Direction Util::rightOf(Direction dir)
{
	switch (dir)
	{
        case NORTHWEST:
            return NORTH;
        case NORTH:
            return NORTHEAST;
        case NORTHEAST:
            return EAST;
        case EAST:
            return SOUTHEAST;
        case SOUTHEAST:
            return SOUTH;
        case SOUTH:
            return SOUTHWEST;
        case SOUTHWEST:
            return WEST;
        case WEST:
            return NORTHWEST;
        default:
            return NO_DIRECTION;
	}
}

Direction Util::oppositeOf(Direction dir)
{
	switch (dir)
	{
        case NORTHWEST:
            return SOUTHEAST;
        case NORTH:
            return SOUTH;
        case NORTHEAST:
            return SOUTHWEST;
        case EAST:
            return WEST;
        case SOUTHEAST:
            return NORTHWEST;
        case SOUTH:
            return NORTH;
        case SOUTHWEST:
            return NORTHEAST;
        case WEST:
            return EAST;
        default:
            return NO_DIRECTION;
	}
}

void Util::setSides(bool sides[NUM_DIRECTIONS], int level, Direction dir)
{
    for (int i = 0; i < NUM_DIRECTIONS; ++i)
        sides[i] = false;
    switch (level)
    {
        case 1:
            sides[leftOf(dir)] = true;
            sides[dir] = true;
            sides[rightOf(dir)] = true;
            break;
        case 2:
            sides[leftOf(leftOf(dir))] = true;
            sides[leftOf(dir)] = true;
            sides[dir] = true;
            sides[rightOf(dir)] = true;
            sides[rightOf(rightOf(dir))] = true;
            break;
        case 3:
            sides[leftOf(leftOf(leftOf(dir)))] = true;
            sides[leftOf(leftOf(dir))] = true;
            sides[leftOf(dir)] = true;
            sides[dir] = true;
            sides[rightOf(dir)] = true;
            sides[rightOf(rightOf(dir))] = true;
            sides[rightOf(rightOf(rightOf(dir)))] = true;
            break;
        default:
            sides[NORTHWEST] = true;
            sides[WEST] = true;
            sides[SOUTHWEST] = true;
            sides[SOUTH] = true;
            sides[SOUTHEAST] = true;
            sides[EAST] = true;
            sides[NORTHEAST] = true;
            sides[NORTH] = true;
            break;
    }
    
}

Direction Util::randDirection()
{
    return (Direction)(rand() % NUM_DIRECTIONS);
}

Direction Util::randDirection(const bool sides[NUM_DIRECTIONS])
{
    std::vector<Direction> dirs;
    if (sides[NORTHWEST])
        dirs.push_back(NORTHWEST);
    if (sides[NORTH])
        dirs.push_back(NORTH);
    if (sides[NORTHEAST])
        dirs.push_back(NORTHEAST);
    if (sides[EAST])
        dirs.push_back(EAST);
    if (sides[SOUTHEAST])
        dirs.push_back(SOUTHEAST);
    if (sides[SOUTH])
        dirs.push_back(SOUTH);
    if (sides[SOUTHWEST])
        dirs.push_back(SOUTHWEST);
    if (sides[WEST])
        dirs.push_back(WEST);
    
    int randDirIndex = rand() % dirs.size();
    
    return dirs[randDirIndex];
}

int Util::randRangeInt(int min, int max)
{
    return min + rand () % (max - min + 1);
}

double Util::randRangeDouble(double min, double max)
{
    return min + static_cast<double>(rand()) / RAND_MAX * (max - min);
}

std::string Util::toStringInt(int value)
{
    std::stringstream ss;
	ss << value;
	return ss.str();
}

std::string Util::toStringDouble(double value)
{
    std::stringstream ss;
    ss << std::setprecision(3) << std::fixed;
	ss << value;
	return ss.str();
}

std::string Util::getSaveDir()
{
    char * dir = getenv("HOME");
    std::string result = "";
    if (dir)
        result = std::string(dir) + "/braingame/";
    else
        return "";
    
    mkdir(result.c_str(), 0777);
    return result;
}

std::string Util::getIOSDir()
{
    
//    char * dir = getenv("HOME");
    const char* dir = OgreFramework::getSingletonPtr()->getMacBundlePath().c_str();
    std::string result = "";
    if (dir)
        result = std::string(dir) + "/../Documents";
    else
        return "";
    
    mkdir(result.c_str(), 0777);
    return result;
}

void Util::drawRect(ManualObject* obj, double x, double y, double width, double height, const ColourValue & col, bool filled)
{
    double left = x;
    double right = x + width;
    double top = -y;
    double bottom = -(y + height);
    
    obj->clear();
    // Range is from x [-1, 1], y [-1, 1]
    obj->setUseIdentityProjection(true);
    obj->setUseIdentityView(true);
    obj->setQueryFlags(0);
    if (filled)
    {
        obj->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_TRIANGLE_LIST);
        obj->position(left, top, -1);
        obj->colour(col);
        obj->position(right, top, -1);
        obj->colour(col);
        obj->position(right, bottom, -1);
        obj->colour(col);
        obj->position(left, bottom, -1);
        obj->colour(col);
        obj->quad(3, 2, 1, 0);
        obj->end();
    }
    else
    {
        obj->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_STRIP);
        obj->position(left, top, -1);
        obj->colour(col);
        obj->position(right, top, -1);
        obj->colour(col);
        obj->position(right, bottom, -1);
        obj->colour(col);
        obj->position(left, bottom, -1);
        obj->colour(col);
        obj->position(left, top, -1);
        obj->colour(col);
        obj->end();
    }
    obj->setBoundingBox(Ogre::AxisAlignedBox::BOX_INFINITE);
}

// http://www.ogre3d.org/tikiwiki/tiki-index.php?page=manualspheremeshes
void Util::createSphere(Ogre::SceneManager* sceneMgr, const std::string& strName, float r, int nRings, int nSegments)
{
    ManualObject * manual = sceneMgr->createManualObject(strName);
    manual->begin("BaseWhiteNoLighting", RenderOperation::OT_TRIANGLE_LIST);
    
    float fDeltaRingAngle = (Math::PI / nRings);
    float fDeltaSegAngle = (2 * Math::PI / nSegments);
    unsigned short wVerticeIndex = 0 ;
    
    // Generate the group of rings for the sphere
    for( int ring = 0; ring <= nRings; ring++ ) {
        float r0 = r * sinf (ring * fDeltaRingAngle);
        float y0 = r * cosf (ring * fDeltaRingAngle);
        
        // Generate the group of segments for the current ring
        for(int seg = 0; seg <= nSegments; seg++) {
            float x0 = r0 * sinf(seg * fDeltaSegAngle);
            float z0 = r0 * cosf(seg * fDeltaSegAngle);
            
            // Add one vertex to the strip which makes up the sphere
            manual->position( x0, y0, z0);
            
            manual->normal(Vector3(x0, y0, z0).normalisedCopy());
            manual->textureCoord((float) seg / (float) nSegments, (float) ring / (float) nRings);
            
            if (ring != nRings) {
                // each vertex (except the last) has six indicies pointing to it
                manual->index(wVerticeIndex + nSegments + 1);
                manual->index(wVerticeIndex);
                manual->index(wVerticeIndex + nSegments);
                manual->index(wVerticeIndex + nSegments + 1);
                manual->index(wVerticeIndex + 1);
                manual->index(wVerticeIndex);
                wVerticeIndex ++;
            }
        }; // end for seg
    } // end for ring
    manual->end();
    MeshPtr mesh = manual->convertToMesh(strName);
    mesh->_setBounds( AxisAlignedBox( Vector3(-r, -r, -r), Vector3(r, r, r) ), false );
    
    mesh->_setBoundingSphereRadius(r);
    unsigned short src, dest;
    if (!mesh->suggestTangentVectorBuildParams(VES_TANGENT, src, dest))
    {
        mesh->buildTangentVectors(VES_TANGENT, src, dest);
    }
}

void Util::createCylinder(Ogre::SceneManager* sceneMgr, const std::string& strName, float r, float h, int nSegments)
{
    ManualObject * manual = sceneMgr->createManualObject(strName);
    manual->begin("BaseWhiteNoLighting", RenderOperation::OT_TRIANGLE_LIST);
    
    float fDeltaSegAngle = (2 * Math::PI / nSegments);
    
    float x0 = 0;
    float y0 = -h / 2;
    float y1 = h / 2;
    float z0 = 0;
    
    manual->position(x0, y0, z0);
    manual->normal(Vector3(x0, y0, z0).normalisedCopy());
    manual->textureCoord(0.0, 0.0);
    manual->position(x0, y1, z0);
    manual->normal(Vector3(x0, y1, z0).normalisedCopy());
    manual->textureCoord(0.0, 1.0);
    
    unsigned short botVerticeIndex = 0;
    unsigned short topVerticeIndex = 1;
    unsigned short iVerticeIndex = 2;
    unsigned short wVerticeIndex = iVerticeIndex;
    
    for (int seg = 0; seg <= nSegments; ++seg)
    {
        x0 = r * sinf(seg * fDeltaSegAngle);
        z0 = r * cosf(seg * fDeltaSegAngle);
        
        manual->position(x0, y0, z0);
        manual->normal(Vector3(x0, 0, z0).normalisedCopy());
        manual->textureCoord((float) seg / (float) nSegments, 0.5);
        manual->position(x0, y1, z0);
        manual->normal(Vector3(x0, 0, z0).normalisedCopy());
        manual->textureCoord((float) seg / (float) nSegments, 0.5);
        
        if (seg > 1)
        {
            manual->triangle(botVerticeIndex, wVerticeIndex + 2, wVerticeIndex);
            manual->triangle(topVerticeIndex, wVerticeIndex + 1, wVerticeIndex + 3);
            manual->triangle(wVerticeIndex, wVerticeIndex + 2, wVerticeIndex + 1);
            manual->triangle(wVerticeIndex + 2, wVerticeIndex + 3, wVerticeIndex + 1);
            
            wVerticeIndex += 2;
        }
    }
    manual->triangle(botVerticeIndex, iVerticeIndex, wVerticeIndex); // last triangles
    manual->triangle(topVerticeIndex, wVerticeIndex + 1, iVerticeIndex + 1);
    manual->triangle(wVerticeIndex, iVerticeIndex, wVerticeIndex + 1);
    manual->triangle(iVerticeIndex, iVerticeIndex + 1, wVerticeIndex + 1);
    manual->end();
    
    MeshPtr mesh = manual->convertToMesh(strName);
    Vector3 bl = Vector3(-r, -h / 2, -r);
    Vector3 tr = Vector3(r, h / 2, r);
    mesh->_setBounds( AxisAlignedBox( bl, tr ), false );
    
    mesh->_setBoundingSphereRadius((tr - bl).length() / 2);
    unsigned short src, dest;
    if (!mesh->suggestTangentVectorBuildParams(VES_TANGENT, src, dest))
    {
        mesh->buildTangentVectors(VES_TANGENT, src, dest);
    }
}

void Util::createPlane(Ogre::SceneManager* sceneMgr, const std::string& strName, float length, float depth)
{
    ManualObject * manual = sceneMgr->createManualObject(strName);
    manual->begin("BaseWhiteNoLighting", RenderOperation::OT_TRIANGLE_LIST);
    
    length += EPSILON;
    depth += EPSILON;
    
    manual->position(-length / 2, 0, -depth / 2);
    manual->normal(0, 1, 0);
    manual->textureCoord(0, 0);
    manual->position(length / 2, 0, -depth / 2);
    manual->normal(0, 1, 0);
    manual->textureCoord(1, 0);
    manual->position(length / 2, 0, depth / 2);
    manual->normal(0, 1, 0);
    manual->textureCoord(1, 1);
    manual->position(-length / 2, 0, depth / 2);
    manual->normal(0, 1, 0);
    manual->textureCoord(0, 1);
    manual->quad(3, 2, 1, 0);
    manual->end();
    
    MeshPtr mesh = manual->convertToMesh(strName);
    double len = length / 2;
    double dep = depth / 2;
    double diag1 = (Vector3(length, 0, depth) - Vector3(-length, 0, -depth)).length() / 2;
    double diag2 = (Vector3(length, 0, -depth) - Vector3(-length, 0, depth)).length() / 2;
    Vector3 bl = Vector3(-len, 0, -dep);
    Vector3 tr = Vector3(len, 0, dep);
    mesh->_setBounds( AxisAlignedBox( bl, tr ), true );
    
    mesh->_setBoundingSphereRadius(diag1 > diag2 ? diag1 : diag2);
    unsigned short src, dest;
    if (!mesh->suggestTangentVectorBuildParams(VES_TANGENT, src, dest))
    {
        mesh->buildTangentVectors(VES_TANGENT, src, dest);
    }
}

void Util::generateMaterials()
{
    /*
    MaterialPtr mat0 =
    MaterialManager::getSingleton().create("PodUnknownMaterial", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, true);
    mat0->setLightingEnabled(true);
    mat0->setAmbient(0.3, 0.3, 0.3);
    mat0->setDiffuse(0.3, 0.3, 0.3, 1.0);
    mat0->load();
    
    MaterialPtr mat1 =
    MaterialManager::getSingleton().create("PodRedMaterial", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, true);
    mat1->setLightingEnabled(true);
    mat1->setAmbient(0.5, 0.0, 0.0);
    mat1->setDiffuse(0.5, 0.0, 0.0, 1.0);
    mat1->load();
    
    MaterialPtr mat2 =
    MaterialManager::getSingleton().create("PodGreenMaterial", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, true);
    mat2->setLightingEnabled(true);
    mat2->setAmbient(0.0, 0.5, 0.0);
    mat2->setDiffuse(0.0, 0.5, 0.0, 1.0);
    mat2->load();
    
    MaterialPtr mat3 =
    MaterialManager::getSingleton().create("PodBlueMaterial", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, true);
    mat3->setAmbient(0.0, 0.0, 0.5);
    mat3->setDiffuse(0.0, 0.0, 0.5, 1.0);
    mat3->load();
    
    MaterialPtr mat4 =
    MaterialManager::getSingleton().create("PodYellowMaterial", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, true);
    mat4->setLightingEnabled(true);
    mat4->setAmbient(0.5, 0.5, 0.0);
    mat4->setDiffuse(0.5, 0.5, 0.0, 1.0);
    mat4->load();
    
    MaterialPtr mat5 =
    MaterialManager::getSingleton().create("StemMaterial", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, true);
    mat5->setLightingEnabled(true);
    mat5->setAmbient(0.25, 0.5, 0.25);
    mat5->setDiffuse(0.25, 0.5, 0.25, 1.0);
    mat5->load();
    
    MaterialPtr mat6 =
    MaterialManager::getSingleton().create("PodShellMaterial", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, true);
    mat6->setLightingEnabled(true);
    mat6->setAmbient(0.5, 0.0, 0.0);
    mat6->setDiffuse(0.5, 0.0, 0.0, 0.1);
    mat6->load();
    */
    
    /*
     Technique *technique = m->createTechnique();
     Pass *pass = technique->createPass();
     pass->setIlluminationStage(Ogre::IS_PER_LIGHT);
     pass->setVertexColourTracking(Ogre::TVC_DIFFUSE);
     pass->setAmbient(1.0, 0.0, 0.0);
     pass->setLightingEnabled(true);
     */

}