//
//  CWall.cpp
//  HelloCpp
//
//  Created by Daniel on 05.11.13.
//
//

#include "CWall.h"
#include "CLandscape.h"

#define STANDART_REPAIR_VALUE 5
#define STANDART_MAX_HEALTH 110
#define STANDART_COST 300
#define STANDART_NAME (char*)"Wall"

#pragma mark - PRIVAT
#pragma mark - Дополнительные методы

/*
 *  Автовосстановление
 */
void CWall::autoRepairWall()
{
    if (_canRepair)
        setHealth((getHealth() + _autoRepairValue) % getMaxHealth());
}

/*
 *  Обновление объекта со временем
 */
void CWall::update(float dt)
{
    //printf("Update %s \n", getName());
}

#pragma mark - PUBLIC
#pragma mark - Конструкторы

/*
 *  Пустой конструктор
 */
CWall::CWall()
{
    _canRepair = true;
    _autoRepairValue = 5;
}

#pragma mark - GET методы

/*
 *  Возвращает возможность починки стены
 */
bool CWall::getCanRepair()
{
    return _canRepair;
}

/*
 *  Возвращает значение восстановления
 */
int CWall::getAutoRepairValue()
{
    return _autoRepairValue;
}

#pragma mark - SET методы

/*
 *  Устанавливаем значение canRepair
 */
CWall& CWall::setCanRepair(bool new_value)
{
    _canRepair = new_value;
    return *this;
}

/*
 *  Устанавливаем значение для автоматического восстановление стены
 */
CWall& CWall::setAutoRepairValue(int new_repair_value)
{
    _autoRepairValue = new_repair_value;
    return *this;
}

#pragma mark - Инициализация

/*
 *  Метод для инициализации полей класса
 */
bool CWall::init()
{
    if ( !CAbstractUnit::init() )
    {
        return false;
    }
    
    // Настройка объекта
    setName(STANDART_NAME);
    setMaxHealth(STANDART_MAX_HEALTH);
    setHealth(STANDART_MAX_HEALTH);
    setAutoRepairValue(STANDART_REPAIR_VALUE);
    setCost(STANDART_COST);
    
    // настройка спрайта
    setSpriteWithRect("tmw_desert_spacing.png", Rect(1, 4 * 32 + 5, 32, 32));
    
    // Загрузка анимации смерти
    setDeadAnimation(CAbstractUnit::createAnimate("fx_enemydie_tiny_32.png", Rect(0, 0, 32, 32), 8, 0.1));
    
    // Создаем игровой цикл для объекта
    //this->getScheduler()->scheduleSelector(schedule_selector(CWall::update), this, 10, false);
    this->getScheduler()->scheduleUpdateForTarget(this, this->getZOrder(), false);
    
    //setVisible(false);
    
    return true;
}

/*
 *  Метод создания юнита с привязкой к ландшафту
 */
CWall* CWall::createWall(CLandscape *landscape)
{
    CWall* wall = CWall::create();
    wall->setLandscape(landscape);
    return wall;
}

#pragma mark - Пользовательский ввод

/*
 *  Делегированный метод для обработки начала касания экрана
 */
bool CWall::onTouchBegan(Touch *touch, Event *event)
{
    if (isClicked(touch)) {
        printf("Wall was touch\n");
        return true;
    }
    return false;
}

