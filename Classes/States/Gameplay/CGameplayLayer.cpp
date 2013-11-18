//
//  CGameplayLayer.cpp
//  HelloCpp
//
//  Created by Daniel on 02.11.13.
//
//

#include "CGameplayLayer.h"

USING_NS_CC;

#pragma mark - Инициализация

/*
 *  Создание сцены с объектами
 */
Layer* CGameplayLayer::createLayer()
{
    auto layer = CGameplayLayer::create();
    
    return layer;
}

/*
 *  Инициализация объекта
 */
bool CGameplayLayer::init()
{
    // Super инициализация слоя
    if ( !Layer::init() )
    {
        return false;
    }
    
    _landscape = CLandscape::create();
    this->addChild(_landscape, -1);
    
    // Отлавливание касания экрана
    auto listener = EventListenerTouch::create(Touch::DispatchMode::ONE_BY_ONE);
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(CGameplayLayer::onTouchBegan, this);
    EventDispatcher::getInstance()->addEventListenerWithSceneGraphPriority(listener, this);
    this->setTouchEnabled(true);
    
    return true;
}

#pragma mark - Пользовательский ввод

/*
 *  Делегированный метод для обработки начала касания экрана
 */
bool CGameplayLayer::onTouchBegan(Touch *touch, Event *event)
{
    Point tileCoord = _landscape->tileCoordForPosition(touch->getLocation());
    if (_landscape->isClickedTowerPlace(tileCoord)) {
        _landscape->addTowerToMapWithPosition(tileCoord);
        //_towersPlaces->removeTileAt(tileCoord);
    }
    if (_landscape->isClickedWallPlace(tileCoord)) {
        _landscape->addWallToMapWithPosition(tileCoord);
        //_wallsPlaces->removeTileAt(tileCoord);
    }
    return false;
}

/*
 *  Делегированный метод для обработки конца касания экрана
 */
void CGameplayLayer::onTouchEnded(Touch *touch, Event *event)
{
    Point touchLocation = touch->getLocationInView();
    touchLocation = Director::getInstance()->convertToGL(touchLocation);
    touchLocation = this->convertToNodeSpace(touchLocation);
}
