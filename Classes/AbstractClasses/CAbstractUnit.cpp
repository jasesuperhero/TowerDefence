//
//  CAbstractUnit.cpp
//  TowerDefense
//
//  Created by Daniel on 31.10.13.
//
//

#include "CAbstractUnit.h"

// Графические константы
const int LabelTTFMarginY = 5;
const int UnitSize = 32;
const int TileSize = 32;

#pragma mark - Конструкторы

/*
 *  Пустой конструктор
 */
CAbstractUnit::CAbstractUnit()
{
    _name = (char*)"noname";
    _sprite = NULL;
    _unitHealthSprite = Sprite::create();
}

#pragma mark - Деструктор

/*
 * Деструктор
 */
CAbstractUnit::~CAbstractUnit()
{
    if (!_sprite) delete _sprite;
    if (!_unitHealthSprite) delete _unitHealthSprite;
    CC_SAFE_RELEASE(this);
}

#pragma mark - GET методы

/*
 *  Возвращает имя объекта
 */
char* CAbstractUnit::getName()
{
    return this->_name;
}

/*
 *  Возвращает имя объекта
 */
Sprite& CAbstractUnit::getSprite()
{
    return *(this->_sprite);
}

/*
 *  Возвращает спрайт слоя здоровья
 */
Sprite& CAbstractUnit::getUnitHealthSprite()
{
    return *_unitHealthSprite;
}

/*
 *  Возвращает спрайты индикатора здоровья
 */
std::vector<Sprite*> CAbstractUnit::getUnitHealthAnimation()
{
    return _unitHealthAnimation;
}

#pragma mark - SET методы

/*
 *  Устанавливает имя для объекта
 */
CAbstractUnit& CAbstractUnit::setName(char *new_name)
{
    _name = new_name;
    return *this;
}

/*
 *  Устанавливает спрайт для объекта
 */
CAbstractUnit& CAbstractUnit::setSprite(const char* sprite_filename)
{
    if (!_sprite) delete _sprite;
    _sprite = new Sprite;
    _sprite->initWithFile(sprite_filename);
    _sprite->cocos2d::Node::setPosition(0, 0);
    return *this;
}

/*
 *  Устанавливает спрайт для объекта определенной области изображения
 */
CAbstractUnit& CAbstractUnit::setSpriteWithRect(const char *sprite_filename, cocos2d::Rect rect)
{
    if (!_sprite) {
        this->removeChild(_sprite);
        delete _sprite;
    }
    _sprite = Sprite::create();
    _sprite->initWithFile(sprite_filename, rect);
    _sprite->cocos2d::Node::setPosition(0, 0);
    this->addChild(_sprite);
    return *this;
}

#pragma mark - Дополнительные методы
#pragma mark - PRIVAT

/*
 *  Проверка на клик по объекту
 */
bool CAbstractUnit::isClicked(cocos2d::Touch *touch)
{
    Point touchCoord = touch->getLocation() - this->getParent()->getBoundingBox().origin;
    touchCoord = this->getParent()->convertToNodeSpace(touchCoord);
    Rect spriteRect = this->getBoundingBox();
    spriteRect.origin.x -= spriteRect.size.width / 2;
    spriteRect.origin.y -= spriteRect.size.height / 2;
    return (spriteRect.containsPoint(touchCoord));
}

#pragma mark - PUBLIC

/*
 *  Преобразует экранные координаты в координаты карты
 */
Point CAbstractUnit::getTiledCoord()
{
    return Point((this->getPositionX() - TileSize / 2) / TileSize,
                 (this->getPositionY() - TileSize / 2) / TileSize - 1);
}

/*
 *  Преобразует координаты карты в экранные координаты
 */
Point CAbstractUnit::getPositionWithTiledCoord(Point tileCoord)
{
    return Point(tileCoord.x * TileSize + TileSize / 2,
                 (this->getParent()->getContentSize().height / 32 - tileCoord.y - 1) * TileSize + TileSize / 2);
}

#pragma mark - Инициализация

/*
 *  Метод для инициализации полей класса
 */
bool CAbstractUnit::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    // Устанавливаем размер слоя
    this->setContentSize(Size(UnitSize, UnitSize));
    
    // Загрузка индикатора здоровья
    for (int i = 0; i < HEALTH_SIZE; i++) {
        Sprite* frame = Sprite::create("bar_blue.png", Rect(UnitSize * i, 0, UnitSize, 4));
        _unitHealthAnimation.push_back(frame);
        frame->Node::setPosition(0, UnitSize / 2 + LabelTTFMarginY);
        frame->retain();
    }
    
    // настройка индикатора здоровья
    _unitHealthSprite = _unitHealthAnimation[_unitHealthAnimation.size() - 1];
    this->addChild(_unitHealthSprite, -1);
    
    // Отлавливание касания экрана
    auto listener = EventListenerTouch::create(Touch::DispatchMode::ONE_BY_ONE);
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(CAbstractUnit::onTouchBegan, this);
    EventDispatcher::getInstance()->addEventListenerWithSceneGraphPriority(listener, this);
    this->setTouchEnabled(true);
    
    return true;
}



