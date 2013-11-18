//
//  CAbstractUnit.h
//  TowerDefense
//
//  Created by Daniel on 31.10.13.
//
//

#ifndef _CAbstractUnit__
#define _CAbstractUnit__

#define HEALTH_SIZE 21

// Библиотеки
#include <cocos2d.h>

using namespace cocos2d;

class CAbstractUnit : public Layer {
protected:
    char*           _name;
    Sprite*         _sprite;
    LabelTTF*       _unit_name;
    Sprite*         _unitHealthSprite;
    
    /** Дополнительные методы */
    bool isClicked(Touch* touch);
    
//private:
    std::vector<Sprite*> _unitHealthAnimation;

public:
    /** Конструкторы */
    CAbstractUnit();
    
    /** Деструктор */
    virtual ~CAbstractUnit();
    
    /** GET методы */
    char* getName();
    Sprite& getSprite();
    Sprite& getUnitHealthSprite();
    
    /** SET методы */
    CAbstractUnit& setName(char* new_name);
    CAbstractUnit& setSprite(const char* sprite_filename);
    CAbstractUnit& setSpriteWithRect(const char* sprite_filename, Rect rect);
    
    /** Дополнительные методы */
    Point getTiledCoord();
    Point getPositionWithTiledCoord(Point tileCoord);
    
    /** Инициализация */
    virtual bool init();
};

#endif /* defined(_CAbstractUnit__) */
