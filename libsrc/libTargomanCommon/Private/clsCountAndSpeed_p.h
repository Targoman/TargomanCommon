/******************************************************************************
 * Targoman: A robust Machine Translation framework               *
 *                                                                            *
 * Copyright 2014-2018 by ITRC <http://itrc.ac.ir>                            *
 *                                                                            *
 * This file is part of Targoman.                                             *
 *                                                                            *
 * Targoman is free software: you can redistribute it and/or modify           *
 * it under the terms of the GNU Lesser General Public License as published   *
 * by the Free Software Foundation, either version 3 of the License, or       *
 * (at your option) any later version.                                        *
 *                                                                            *
 * Targoman is distributed in the hope that it will be useful,                *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * GNU Lesser General Public License for more details.                        *
 * You should have received a copy of the GNU Lesser General Public License   *
 * along with Targoman. If not, see <http://www.gnu.org/licenses/>.           *
 *                                                                            *
 ******************************************************************************/
/**
 * @author S. Mohammad M. Ziabary <ziabary@targoman.com>
 */

#include <QScopedPointer>
#include <QSharedData>
#include <QTime>
#include <QQueue>
#include "libTargomanCommon/Macros.h"

#ifndef TARGOMAN_COMMON_PRIVATE_CLSCOUNTANDSPEEDPRIVATE_H
#define TARGOMAN_COMMON_PRIVATE_CLSCOUNTANDSPEEDPRIVATE_H

namespace Targoman{
namespace Common {
namespace Private {

class clsCountAndSpeedPrivate : public QSharedData
{
public:
    clsCountAndSpeedPrivate(quint16 _maxSnapshots):
        LastSpeed(0),
        LastIndex(0),
        Snapshots(new quint64[_maxSnapshots]())
    {}

public:
    quint64 LastSpeed;
    quint64 LastValue;
    quint16 LastIndex;
    quint16 MaxSnapshots;

    QScopedArrayPointer<quint64> Snapshots;
};

}
}
}
#endif // TARGOMAN_COMMON_PRIVATE_CLSCOUNTANDSPEEDPRIVATE_H
