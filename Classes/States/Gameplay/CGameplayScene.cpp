//
//  CGameplayScene.cpp
//  HelloCpp
//
//  Created by Daniel on 02.11.13.
//
//

#include "CGameplayScene.h"
#include <SimpleAudioEngine.h>

/*
 *  Создание сцены с объектами
 */
Scene* CGameplayScene::createScene()
{
    auto scene = Scene::create();
    auto layer = CGameplayLayer::create();
    
    //CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("TileMap.caf");
    
    // Добавление слоев на сцену
    scene->addChild(layer);
    
    return scene;
}

/*
 *  Инициализация объекта
 */
bool CGameplayScene::init()
{
    // Super инициализация сцены
    if (!Scene::init())
    {
        return false;
    }
    
    return true;
}