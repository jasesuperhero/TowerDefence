//
//  CLair.cpp
//  HelloCpp
//
//  Created by Daniel on 24.11.13.
//
//

#include "CLair.h"

#include "CLightEnemy.h"
#include "CLandscape.h"

#define STANDART_NAME (char*)"Lair"
#define STANDART_WAVE_TIME 100

#pragma mark - Конструктор

/*
 *  Пустой конструктор
 */
CLair::CLair()
{
    _enemies.clear();
}

#pragma mark - GET методы

/*
 *  Возвращает время запуска волны
 */
int CLair::getWaveTime()
{
    return _waveTime;
}

/*
 *  Возвращает указатель на дорогу для юнитов
 */
CRoad* CLair::getRoad()
{
    return _road;
}

/*
 *  Возвращает указатель на анимацию выпуска врага
 */
Animate* CLair::getMakeEnemyAnimate()
{
    return _makeEnemyAnimate;
}

/*
 *  Возврашает контейнер врагов
 */
vector<CAbstractEnemy*> CLair::getEnemyContainer()
{
    return _enemies;
}

#pragma mark - SET методы

/*
 *  Устаналвиает новое значение времени волны
 */
CLair& CLair::setWaveTime(int new_wave_time)
{
    if (new_wave_time <= 0) throw "New wave time is less or equal 0";
    _waveTime = new_wave_time;
    return *this;
}

/*
 *  Устанавливает новую дорогу для юнитов
 */
CLair& CLair::setRoad(CRoad *new_road)
{
    if (new_road == NULL) throw "New road is NULL ptr";
    _road = new_road;
    return *this;
}

/*
 *  Устаналвиает новую анимацию для спауна юнитов
 */
CLair& CLair::setMakeEnemyAnimate(Animate *new_make_animate)
{
    if (new_make_animate == NULL) throw "New animate is NULL ptr";
    _makeEnemyAnimate = new_make_animate;
    return *this;
}

/*
 *  Устанавливает контейнер врагов
 */
CLair& CLair::setEneimyContainer(vector<CAbstractEnemy*> new_enemy_container)
{
    _enemies = new_enemy_container;
    return *this;
}

/*
 *  Делегированный метод для обработки начала касания экрана
 */
bool CLair::onTouchBegan(Touch *touch, Event *event)
{
    if (isClicked(touch)) {
        printf("Lair was touch\n");
        return true;
    }
    return false;
}

#pragma mark - Инициализация

/*
 *  Инициализация объекта
 */
bool CLair::init()
{
    if (!CAbstractUnit::init())
    {
        return false;
    }
    
    setSpriteWithRect("lair.png", Rect(0, 0, 32, 56));
    // Анимация
    _makeEnemyAnimate = createAnimate("lair.png", Rect(0, 0, 32, 56), 9, 0.1);
    _waveTime = STANDART_WAVE_TIME;
    
    return true;
}

/*
 *  Создание логова с указателем на дорогу
 */
CLair* CLair::createLairWithLandscape(CLandscape *landscape)
{
    CLair* lair = CLair::create();
    lair->setLandscape(landscape);
    lair->setRoad(CRoad::createWithLayerAndCastleCoord(landscape->getLayer("Road"), landscape->getCastleCoord()));
    lair->spawnWave();
    return lair;
}

#pragma mark - Дополнительные методы

/*
 *  Метод создания волны и запуска спауна юнитов
 */
void CLair::spawnWave()
{
    for (int i = 0; i < 10; i++) {
        CLightEnemy* enemy = CLightEnemy::createEnemy(this->getLandscape());
        enemy->setPosition(getPosition());
        _enemies.push_back(enemy);
    }
    
    FiniteTimeAction* spawnUnit = Sequence::create(DelayTime::create(rand() % 3 + CCRANDOM_0_1()),
                                                   _makeEnemyAnimate,
                                                   CallFunc::create(this, callfunc_selector(CLair::spawnUnit)),
                                                   NULL);
    spawnUnit->retain();
    this->_sprite->runAction(spawnUnit);
    
    FiniteTimeAction* makeWave = Sequence::create(DelayTime::create(_waveTime),
                                                  CallFunc::create(this, callfunc_selector(CLair::spawnWave)),
                                                  NULL);
    makeWave->retain();
    this->runAction(makeWave);
}

/*
 *  Метод спауна юнита
 */
void CLair::spawnUnit()
{
    if (!_enemies.empty()) {
        CAbstractEnemy* enemy = _enemies[_enemies.size() - 1];
        printf("Spawn %s\n", enemy->getName());
        _enemies.pop_back();
        getLandscape()->addEnemyToMapWithPosition(getTiledCoord(), enemy);
        FiniteTimeAction* makeUnit = Sequence::create(DelayTime::create(rand() % 3 + CCRANDOM_0_1()),
                                                      _makeEnemyAnimate,
                                                      CallFunc::create(this, callfunc_selector(CLair::spawnUnit)),
                                                      NULL);
        makeUnit->retain();
        this->_sprite->runAction(makeUnit);
    }
}
