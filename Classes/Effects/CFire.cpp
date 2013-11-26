//
//  CFire.cpp
//  HelloCpp
//
//  Created by Daniel on 20.11.13.
//
//

#include "CFire.h"

// Графические константы
const int FramesNumber = 8;
const char* Filename = "plasmaball.png";
const int FrameSize = 16;

#pragma mark - Конструкторы

/*
 *  Пустой конструктор
 */
CFire::CFire()
{
    _fireAnimation = Animation::create();
}

#pragma mark - Инициализация

/*
 *  Инициализация класса
 */
bool CFire::init()
{
    if (!Sprite::init())
        return false;
    
    this->initWithFile(Filename, Rect(0, 0, FrameSize, FrameSize));
    
    for (int i = 0; i < FramesNumber; i++) {
        SpriteFrame* frame = SpriteFrame::create(Filename, Rect(FrameSize * i, 0, FrameSize, FrameSize));
        _fireAnimation->addSpriteFrame(frame);
    }
    
    _fireAnimation->setDelayPerUnit(0.1);
    RepeatForever* fireAnimate = RepeatForever::create(Animate::create(_fireAnimation));
    this->runAction(fireAnimate);
    
    return true;
}