//
//  CCastle.cpp
//  HelloCpp
//
//  Created by Daniel on 09.11.13.
//
//

#include "CCastle.h"
#include "CLandscape.h"

#define STANDART_HEALTH 10000
#define STANDART_MONEY 1000 
#define STANDART_NAME (char*)"Castle"

const int castleMap[5][5] = {
    {0, 2, 3, 0, 0},
    {2, 0, 0, 0, 0},
    {0, 0, 1, 0, 0},
    {2, 0, 0, 0, 0},
    {0, 2, 3, 0, 0}
};

#pragma mark - Конструкторы

/*
 *  Пустой конструктор
 */
CCastle::CCastle()
{
    _money = 0;
}

#pragma mark - GET методы

/*
 *  Возвращает текущее количество золота в замке
 */
int CCastle::getMoney()
{
    return _money;
}

#pragma mark - SET методы

/*
 *  Устанавливает текущее количество золота в замке
 */
CCastle& CCastle::setMoney(int new_money)
{
    if (new_money > 0) _money = new_money;
    return *this;
}

#pragma mark - Дополниетльные методы
#pragma mark - PRIVATE

/*
 *  Обновление объекта со временем
 */
void CCastle::update(float dt)
{
    
}

#pragma mark - PUBLIC

/*
 *  Покупка какого-либо здания
 */
bool CCastle::buyBuilding(int cost)
{
    if (_money - cost >= 0) {
        _money -= cost;
        printf("## Castle money: %d \n", _money);
        return true;
    }
    return false;
}

/*
 *  Добавление денег
 */
void CCastle::addMoney(int adding_money)
{
    _money += adding_money;
}

/*
 *  Постройка вспомогательных построек замка
 */
void CCastle::placeTowers()
{
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++) {
            Point p = Point((-2 + j) * 32, (2 - i) * 32);
            switch (castleMap[i][j]) {
                case 2:
                {
                    CTower* tower = CTower::createTower(getLandscape());
                    tower->setPosition(getPositionX() + p.x, getPositionY() + p.y);
                    getLandscape()->addChild(tower);
                }
                    break;
                case 3:
                {
                    CWall* wall = CWall::createWall(getLandscape());
                    wall->setPosition(getPositionX() + p.x, getPositionY() + p.y);
                    getLandscape()->addChild(wall);
                }
                    break;
                    
                default:
                    break;
            }
        }
}


#pragma mark - Инициализация

/*
 *  Метод для инициализации полей класса
 */
bool CCastle::init()
{
    if ( !CAbstractUnit::init() )
    {
        return false;
    }
    
    // Настройка объекта
    setName(STANDART_NAME);
    setHealth(STANDART_HEALTH);
    setMaxHealth(STANDART_HEALTH);
    setMoney(STANDART_MONEY);
    
    // настройка спрайта
    setSpriteWithRect("tmw_desert_spacing.png", Rect(1, 4 * 32 + 5, 32, 32));
    
    // Создаем игровой цикл для объекта
    this->getScheduler()->scheduleSelector(schedule_selector(CCastle::update), this, 10, false);
    this->getScheduler()->scheduleUpdateForTarget(this, this->getZOrder(), false);
    
    return true;
}

/*
 *  Метод создание замка с указателем на CLandscape
 */
CCastle* CCastle::createCastle(CLandscape *landscape)
{
    CCastle* castle = CCastle::create();
    castle->setLandscape(landscape);
    return castle;
}

#pragma mark - Пользовательский ввод

/*
 *  Делегированный метод для обработки начала касания экрана
 */
bool CCastle::onTouchBegan(Touch *touch, Event *event)
{
    if (isClicked(touch)) {
        printf("Castle was touch\n");
        return true;
    }
    return false;
}
