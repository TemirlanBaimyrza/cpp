#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include "mainscene.hpp"

mainScene::mainScene()
{
  setItemIndexMethod(QGraphicsScene::NoIndex);

  _init_main_field();
  _init_primary_field();
}
//------------------------------------------------------------------------------
void mainScene::_init_main_field()
{
  mMainField.boundingRectOnSceneCalc();
  addItem(&mMainField);
}
//------------------------------------------------------------------------------
void mainScene::_init_primary_field()
{
  mPrimaryField.setPos(710, 490);
  mPrimaryField.boundingRectOnSceneCalc();
  addItem(&mPrimaryField);
}
//------------------------------------------------------------------------------
void mainScene::mousePressEvent(QGraphicsSceneMouseEvent *apEvent)
{
  if(apEvent->button() == Qt::LeftButton)
  {
    const QPointF &pos  = apEvent->scenePos();

    if(_is_moving_hover_main_field(pos))
    {
      if(!mMainField.fieldIsEmpty(pos))
      {
        qWarning() << "Not empty MAIN";
      }
    }
    else if(_is_moving_hover_primary_field(pos))
    {
      if(!mPrimaryField.fieldIsEmpty(pos))
      {
        qWarning() << "Not empty Primary";
      }
    }
  }
}
//------------------------------------------------------------------------------
void mainScene::mouseMoveEvent(QGraphicsSceneMouseEvent *apEvent)
{
  bool mainHover    = _is_moving_hover_main_field(apEvent->scenePos());
  bool primaryHover = _is_moving_hover_primary_field(apEvent->scenePos());

  if(!mainHover && !primaryHover)
    return;

  if(mainHover)
    mMainField.enableHoverPos(apEvent->scenePos());

  if(primaryHover)
    mPrimaryField.enableHoverPos(apEvent->scenePos());
}
//------------------------------------------------------------------------------
bool mainScene::_is_moving_hover_main_field(const QPointF &aPos)
{
  return (aPos.x() >= mMainField.xtl())
      && (aPos.x() <= mMainField.xbr())
      && (aPos.y() >= mMainField.ytl())
      && (aPos.y() <= mMainField.ybr());
}
//------------------------------------------------------------------------------
bool mainScene::_is_moving_hover_primary_field(const QPointF &aPos)
{
  return (aPos.x() >= mPrimaryField.xtl())
      && (aPos.x() <= mPrimaryField.xbr())
      && (aPos.y() >= mPrimaryField.ytl())
      && (aPos.y() <= mPrimaryField.ybr());
}
//------------------------------------------------------------------------------
void mainScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
}
