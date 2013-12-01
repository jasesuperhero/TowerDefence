//
//  CAbstractUnit.h
//  TowerDefense
//
//  Created by Daniel on 31.10.13.
//
//

#ifndef __HelloCpp__CAbstractUnit__
#define __HelloCpp__CAbstractUnit__

#define HEALTH_SIZE 21

// Библиотеки
#include <cocos2d.h>

class CLandscape;

using namespace cocos2d;
using namespace std;

class CAbstractUnit : public Layer {
protected:
    char*           _name;
    CLandscape*     _landscape;
    
    // Графика
    Sprite*         _sprite;
    Sprite*         _unitHealthSprite;
    
    /** Дополнительные методы */
    bool isClicked(Touch* touch);
    
private:
    vector<Sprite*> _unitHealthAnimation;

public:
    /** Конструкторы */
    CAbstractUnit();
    
    /** Деструктор */
    virtual ~CAbstractUnit();
    
    /** GET методы */
    char* getName();
    CLandscape* getLandscape();
    Sprite* getSprite();
    Sprite* getUnitHealthSprite();
    vector<Sprite*> getUnitHealthAnimation();
    
    /** SET методы */
    CAbstractUnit& setName(char* new_name);
    CAbstractUnit& setLandscape(CLandscape* new_landscape);
    CAbstractUnit& setSprite(const char* sprite_filename);
    CAbstractUnit& setSpriteWithRect(const char* sprite_filename, Rect rect);
    
    /** Дополнительные методы */
    Point getTiledCoord();
    Point getPositionWithTiledCoord(Point tileCoord);
    
    // Графика
    Animate* createAnimate(const char *filename, Rect startFrame, int count, float delayTime);
    
    /** Инициализация */
    virtual bool init();
};

#endif /* defined(__HelloCpp__CAbstractUnit__) */
