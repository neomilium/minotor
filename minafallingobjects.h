#ifndef MINAFALLINGOBJECTS_H
#define MINAFALLINGOBJECTS_H
#include "minoanimation.h"

class MinaFallingObjects : public MinoAnimation
{
    Q_OBJECT
public:
    explicit MinaFallingObjects(QObject *object);
    void animate(const unsigned int uppqn, const unsigned int gppqn, const unsigned int ppqn, const unsigned int qn);

    static const MinoAnimationDescription getDescription() {
        return MinoAnimationDescription("falling", "Falling Objects", QPixmap(":/images/falling.png"), MinaFallingObjects::staticMetaObject.className());
    }
    const MinoAnimationDescription description() const { return getDescription(); }

    void setDuration(const unsigned int duration) { _beatDuration->setCurrentItem(QString::number(duration)); }
    void setDensity(const unsigned int density) { _generatorDensity->setCurrentItem(QString::number(density)); }
    void setLength(const unsigned int length) { _generatorLength->setCurrentItem(QString::number(length)); }
    void setDirection(QString direction) { _generatorDirection->setCurrentItem(direction); }

    QGraphicsItem* graphicItem() { return &_itemGroup; }
    
signals:
    
public slots:

protected:
    MinoItemizedProperty *_beatDuration;
    MinoItemizedProperty *_generatorDirection;
    MinoItemizedProperty *_generatorLength;
    MinoItemizedProperty *_generatorDensity;
    QGraphicsItemGroup _itemGroup;
    MinoAnimatedItems _animatedItems;

};
#endif // MINAFALLINGOBJECTS_H
