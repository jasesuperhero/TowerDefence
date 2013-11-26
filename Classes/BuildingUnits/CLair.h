//
//  CLair.h
//  HelloCpp
//
//  Created by Daniel on 24.11.13.
//
//

#ifndef __HelloCpp__CLair__
#define __HelloCpp__CLair__

// Библиотеки
#include <cocos2d.h>
// Кастомные
#include "CAbstractEnemy.h"

class CLandscape;

using namespace std;

class CLair : public CAbstractUnit {
protected:
    int _waveTime;
    
    CRoad* _road;
    
    // Графика
    Animate* _makeEnemyAnimate;
    
    // Контейнер врагов для создания
    vector<CAbstractEnemy*> _enemies;
    
    /** Дополнительные методы */
    void spawnWave();
    void spawnUnit();
    
public:
    /** Конструкторы */
    CLair();
    
    /** GET методы */
    int getWaveTime();
    CRoad* getRoad();
    Animate* getMakeEnemyAnimate();
    vector<CAbstractEnemy*> getEnemyContainer();
    
    /** SET методы */
    CLair& setWaveTime(int new_wave_time);
    CLair& setRoad(CRoad* new_road);
    CLair& setMakeEnemyAnimate(Animate* new_make_animate);
    CLair& setEneimyContainer(vector<CAbstractEnemy*> new_enemy_container);
    
    /** Пользовательский ввод */
    bool onTouchBegan(Touch *touch, Event *event);
    
    /** Инициализация */
    virtual bool init();
    static CLair* createLairWithLandscape(CLandscape *landscape);
    
    // Метод create создается вручную (COCOS2D-X)
    CREATE_FUNC(CLair);
};

#endif /* defined(__HelloCpp__CLair__) */
