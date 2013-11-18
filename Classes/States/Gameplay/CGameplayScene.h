//
//  CGameplayScene.h
//  HelloCpp
//
//  Created by Daniel on 02.11.13.
//
//

#ifndef __HelloCpp__CGameplayScene__
#define __HelloCpp__CGameplayScene__

// Библиотеки
#include <cocos2d.h>
// Кастомные
#include "CGameplayLayer.h"

using namespace cocos2d;

class CGameplayScene : public Scene {
private:
    CGameplayLayer* gameplayLayer;
    
public:
    /** Конструкторы */
    CGameplayScene();
    
    /** Деструктор */
    virtual ~CGameplayScene();
    
    /** GET методы */
    CGameplayLayer* getGameplayLayer();
    
    /** SET методы */
    CGameplayLayer& setGameplayLayer(CGameplayLayer* new_gameplayLayer);
    
    /** Методы создания и инициализации */
    static Scene* createScene();
    virtual bool init();
    
    // Метод create создается вручную (COCOS2D-X)
    CREATE_FUNC(CGameplayScene);
};

#endif /* defined(__HelloCpp__CGameplayScene__) */
