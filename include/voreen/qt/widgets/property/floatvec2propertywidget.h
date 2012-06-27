/**********************************************************************
 *                                                                    *
 * Voreen - The Volume Rendering Engine                               *
 *                                                                    *
 * Copyright (C) 2005-2010 Visualization and Computer Graphics Group, *
 * Department of Computer Science, University of Muenster, Germany.   *
 * <http://viscg.uni-muenster.de>                                     *
 *                                                                    *
 * This file is part of the Voreen software package. Voreen is free   *
 * software: you can redistribute it and/or modify it under the terms *
 * of the GNU General Public License version 2 as published by the    *
 * Free Software Foundation.                                          *
 *                                                                    *
 * Voreen is distributed in the hope that it will be useful,          *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of     *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the       *
 * GNU General Public License for more details.                       *
 *                                                                    *
 * You should have received a copy of the GNU General Public License  *
 * in the file "LICENSE.txt" along with this program.                 *
 * If not, see <http://www.gnu.org/licenses/>.                        *
 *                                                                    *
 * The authors reserve all rights not expressly granted herein. For   *
 * non-commercial academic use see the license exception specified in *
 * the file "LICENSE-academic.txt". To get information about          *
 * commercial licensing please contact the authors.                   *
 *                                                                    *
 **********************************************************************/

#ifndef VRN_FLOATVEC2PROPERTYWIDGET_H
#define VRN_FLOATVEC2PROPERTYWIDGET_H

#include "voreen/core/properties/vectorproperty.h"
#include "voreen/qt/widgets/property/floatpropertywidget.h"
#include "voreen/qt/widgets/property/vecpropertywidget.h"

namespace voreen {

class FloatVec2PropertyWidget : public VecPropertyWidget<DoubleSliderSpinBoxWidget, FloatVec2Property, float> {
Q_OBJECT;
public:
    FloatVec2PropertyWidget(FloatVec2Property* prop, QWidget* parent = 0);

protected:
    void mousePressEvent(QMouseEvent*);

public slots:
    void setProperty(double value);

signals:
    void valueChanged(IntVec2Property::ElemType);
};

} // namespace voreen

#endif // VRN_COMPACTFLOATVEC2PROPERTYWIDGET_H