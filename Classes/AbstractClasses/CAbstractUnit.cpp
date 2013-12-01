//
//  CAbstractUnit.cpp
//  TowerDefense
//
//  Created by Daniel on 31.10.13.
//
//

#include "CAbstractUnit.h"
#include "CLandscape.h"

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
    _landscape = NULL;
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
 *  Возвращает указатель на ландшафт, на котором расположен юнит
 */
CLandscape* CAbstractUnit::getLandscape()
{
    return _landscape;
}

/*
 *  Возвращает имя объекта
 */
Sprite* CAbstractUnit::getSprite()
{
    return _sprite;
}

/*
 *  Возвращает спрайт слоя здоровья
 */
Sprite* CAbstractUnit::getUnitHealthSprite()
{
    return _unitHealthSprite;
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
 *  Устанавливает ландшафт для объекта
 */
CAbstractUnit& CAbstractUnit::setLandscape(CLandscape *new_landscape)
{
    if (!new_landscape) throw "Landscape is NULL ptr";
    _landscape = new_landscape;
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
    if (this->getParent()) {
        Point touchCoord = touch->getLocation() - this->getParent()->getBoundingBox().origin;
        touchCoord = this->getParent()->convertToNodeSpace(touchCoord);
        Rect spriteRect = this->getBoundingBox();
        spriteRect.origin.x -= spriteRect.size.width / 2;
        spriteRect.origin.y -= spriteRect.size.height / 2;
        return (spriteRect.containsPoint(touchCoord));
    } else return false;
}

#pragma mark - PUBLIC

/*
 *  Преобразует экранные координаты в координаты карты
 */
Point CAbstractUnit::getTiledCoord()
{
    return Point((this->getPositionX() - TileSize / 2) / TileSize,
                 this->getLandscape()->getMapSize().height - (this->getPositionY() - TileSize / 2) / TileSize - 1);
}

/*
 *  Преобразует координаты карты в экранные координаты
 */
Point CAbstractUnit::getPositionWithTiledCoord(Point tileCoord)
{
    return Point(tileCoord.x * TileSize + TileSize / 2,
                 (this->getParent()->getContentSize().height / 32 - tileCoord.y - 1) * TileSize + TileSize / 2);
}

/*
 *  Создание анимации
 */
Animate* CAbstractUnit::createAnimate(const char *filename, Rect startFrame, int count, float delayTime)
{
    Animation* animation = Animation::create();
    for(int i = 0; i < count; i++) {
        SpriteFrame* frame = SpriteFrame::create(filename, startFrame);
        startFrame.origin.x += startFrame.size.width;
        animation->addSpriteFrame(frame);
    }
    animation->setDelayPerUnit(delayTime);
    Animate* new_animate = Animate::create(animation);
    new_animate->retain();
    return new_animate;
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



