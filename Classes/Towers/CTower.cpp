//
//  CTower.cpp
//  HelloCpp
//
//  Created by Daniel on 07.11.13.
//
//

#include "CTower.h"
#include "CFire.h"
#include "CLandscape.h"

// Характеристики башни
#define STANDART_DAMAGE 1000
#define STANDART_RATE 1
#define STANDART_HEALTH 10000
#define STANDART_DAMAGE_RADIUS 150
#define STANDART_COST 300
#define STANDART_NAME (char*)"Tower"
#define STANDART_MAXLEVEL 3

#define MAX_ANIMATION 8

#pragma mark - Конструкторы

/*
 *  Пустой конструктор
 */
CTower::CTower()
{
    _level = 0;
    _experience = 0;
}

#pragma mark - GET методы

/*
 *  Возвращает текущий уровень
 */
int CTower::getLevel()
{
    return _level;
}

/*
 *  Возвращает текущий опыт
 */
int CTower::getExperience()
{
    return _experience;
}

/*
 *  Возвращает вектор врагов
 */
vector<CAbstractEnemy*>* CTower::getEnemiesArray()
{
    return _enemiesArray;
}

#pragma mark - SET методы

/*
 *  Устанавливает текущий уровень
 */
CTower& CTower::setLevel(int new_level)
{
    if (new_level < 0 || new_level > STANDART_MAXLEVEL) throw "New level for unit is less then 0 or > MAXLEVEL";
    _level = new_level;
    return *this;
}

/*
 *  Устанавливает текущий опыт
 */
CTower& CTower::setExperience(int new_experience)
{
    if (new_experience < 0) throw "New experience for unit is less then 0";
    _experience = new_experience;
    return *this;
}

/*
 *  Устанавливает вектор врагов
 */
CTower& CTower::setEnemiesArray(vector<CAbstractEnemy*>* new_enemies_array)
{
    if (new_enemies_array) _enemiesArray = new_enemies_array;
    else throw "New enemies array is empty";
    return *this;
}

#pragma mark - Перегрузка методов

/*
 *  Метод для отрисовки OpenGL
 */
void CTower::draw()
{
    // отрисовка радиуса атаки башни
    glLineWidth(2);
    DrawPrimitives::setDrawColor4B(0, 178, 0, 30);
    DrawPrimitives::drawSolidCircle(Point(0, 0), getDamageRadius(), CC_DEGREES_TO_RADIANS(90), 50);
    CHECK_GL_ERROR_DEBUG();
}

/*
 *  Анимация и экшн атаки
 */
void CTower::attackAnimation()
{
    int angle = floor(CC_RADIANS_TO_DEGREES(atan2l(getAttacedUnit()->getPositionX() - getPositionX(),
    getAttacedUnit()->getPositionY() - getPositionY())) / 22.5) + 8;
    angle = floor((float)angle / 2);
    this->removeChild(getSprite());
    _sprite = _towerAnimation[_level][angle];
    this->addChild(getSprite());
    
    CFire* fire = CFire::create();
    fire->cocos2d::Node::setPosition(this->getPosition());
    FiniteTimeAction* sequence = Sequence::create(MoveTo::create(0.3, getAttacedUnit()->getPosition()),
                                                  CallFunc::create(this, callfunc_selector(CTower::isKillEnemy)),
                                                  CallFunc::create(fire, callfunc_selector(Node::removeFromParent)),
                                                  NULL);
    this->getParent()->addChild(fire, 1);
    fire->runAction(sequence);
}

/*
 *  Убит ли атакуемый юнит
 */
void CTower::isKillEnemy()
{
    CAbstractEnemy* enemy = dynamic_cast<CAbstractEnemy*>(getAttacedUnit());
    if (makeDamageTo()) {
        addExperience(enemy->getExp());
        getLandscape()->getCastle()->addMoney(getAttacedUnit()->getCost());
    }
}

#pragma mark - Инициализация

/*
 *  Метод для инициализации полей класса
 */
bool CTower::init()
{
    if ( !CAbstractUnit::init() )
    {
        return false;
    }
    
    // Настройка объекта
    setName(STANDART_NAME);
    setHealth(STANDART_HEALTH);
    setMaxHealth(STANDART_HEALTH);
    setMaxDamage(STANDART_DAMAGE);
    setDamageRadius(STANDART_DAMAGE_RADIUS);
    setRate(STANDART_RATE);
    setCost(STANDART_COST);
    
    // Настройка спрайта
    setSpriteWithRect("turret1.png", Rect(0, 0, 32, 32));
    
    // Загрузка анимации для башни
    _towerAnimation.resize(STANDART_MAXLEVEL);
    for (int i = 0; i < STANDART_MAXLEVEL; i++)
        for (int j = 0; j < MAX_ANIMATION; j++) {
            char str[30]; sprintf(str, "turret%d.png", i + 1);
            Sprite* sprite = Sprite::create(str, Rect(j * 32, 0, 32, 32));
            _towerAnimation[i].push_back(sprite);
            sprite->retain();
        }
    
    // Запуск основного цикла
    this->getScheduler()->scheduleUpdateForTarget(this, this->getZOrder(), false);
    
    return true;
}

#pragma mark - Пользовательский ввод

/*
 *  Делегированный метод для обработки начала касания экрана
 */
bool CTower::onTouchBegan(Touch *touch, Event *event)
{
    if (isClicked(touch)) {
        levelUp();
        return true;
    }
    return false;
}

#pragma mark - Дополнительные методы
#pragma mark - PRIVAT

/*
 *  Повышение уровня
 */
void CTower::levelUp()
{
    if (_level + 1 < STANDART_MAXLEVEL) {
        _level++;
        _experience = 0;
    }
}

/*
 *  Добавление опыта за башню
 */
void CTower::addExperience(int exp)
{
    _experience += exp;
    if (_experience > 1000) levelUp();
}

/*
 *  Обновление объекта со временем
 */
void CTower::update(float dt)
{
    // Атака, либо поиск атакуемого юнита
    if (!getAttacedUnit())
        for (int i = 0; i < _enemiesArray->size(); i++)
            if (getPosition().getDistance((*_enemiesArray)[i]->getPosition()) < getDamageRadius()) {
                setAttacedUnit((*_enemiesArray)[i]);
                attack();
                return;
            }
}

#pragma mark - PUBLIC
/*
 *  Создание юнита с указателем на вектор всех юнитов на карте
 */
CTower* CTower::createTower(CLandscape *landscape)
{
    CTower* tower = create();
    tower->setLandscape(landscape);
    tower->setEnemiesArray(landscape->getEnemies());
    return tower;
}
