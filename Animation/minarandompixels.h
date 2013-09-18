/*
 * Copyright 2012, 2013 Gauthier Legrand
 * Copyright 2012, 2013 Romuald Conty
 * 
 * This file is part of Minotor.
 * 
 * Minotor is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Minotor is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Minotor.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MINARANDOMPIXELS_H
#define MINARANDOMPIXELS_H

#include "minoanimation.h"

#include "minopropertyreal.h"
#include "easingcurvedreal.h"
#include "minopropertyeasingcurve.h"
#include "minoitemizedproperty.h"

class MinaRandomPixels : public MinoAnimation
{
    Q_OBJECT
public:
    explicit MinaRandomPixels(QObject *object);
    void animate(const unsigned int uppqn, const unsigned int gppqn, const unsigned int , const unsigned int );

    static const MinoAnimationDescription getDescription() {
        return MinoAnimationDescription("Random pixels", "Beat-synced randomly placed pixels", QPixmap(":/images/randompixels.png"), MinaRandomPixels::staticMetaObject.className());
    }
    const MinoAnimationDescription description() const { return getDescription(); }

    void setDensity(qreal density) { _density->setValue(density); }
    QGraphicsItem* graphicItem() { return &_itemGroup; }

signals:
    
public slots:

private:
    MinoItemizedProperty *_beatDuration;
    MinoPropertyReal *_density;
    MinoPropertyEasingCurve *_generatorCurve;
    QGraphicsItemGroup _itemGroup;
    EasingCurvedReal _ecrAlpha;
    MinoAnimatedItems _animatedItems;

    void createPixels(const unsigned int uppqn, const unsigned duration);
};

#endif // MINARANDOMPIXELS_H
