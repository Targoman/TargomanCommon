/*################################################################################
#   TargomanCommon: Primitive but usefull tools for Targoman
#
#   Copyright 2014-2021 by ITRC <http://itrc.ac.ir>
#
#   This file is part of Targoman.
#
#   Targoman is free software: you can redistribute it and/or modify
#   it under the terms of the GNU Lesser General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   Targoman is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU Lesser General Public License for more details.
#
#   You should have received a copy of the GNU Lesser General Public License
#   along with Targoman. If not, see <http://www.gnu.org/licenses/>.
################################################################################*/
/**
 * @author S. Mohammad M. Ziabary <ziabary@targoman.com>
 */

#include "clsCountAndSpeed.h"
#include "Private/clsCountAndSpeed_p.h"

namespace Targoman{
namespace Common {

using namespace Private;

clsCountAndSpeed::clsCountAndSpeed(quint8 _maxSnapshots, quint64 _initialValue):
    pPrivate(new Private::clsCountAndSpeedPrivate(_maxSnapshots))
{
    this->pPrivate->LastValue = _initialValue;
}

clsCountAndSpeed::~clsCountAndSpeed()
{}

clsCountAndSpeed::clsCountAndSpeed(const clsCountAndSpeed &_other) :
    pPrivate(_other.pPrivate)
{}

quint64 clsCountAndSpeed::inc()
{
    return ++this->pPrivate->LastValue;
}

void clsCountAndSpeed::reset()
{
    this->pPrivate->LastValue = 0;
    this->pPrivate->LastSpeed = 0;
    for(quint16 i=0; i< this->pPrivate->MaxSnapshots; ++i)
        this->pPrivate->Snapshots[i] = 0;
}

quint64 clsCountAndSpeed::count() const
{
    return this->pPrivate->LastValue;
}

double clsCountAndSpeed::countPerSecond() const
{
    return this->pPrivate->LastSpeed;
}

void clsCountAndSpeed::snapshot(quint16 _secsBetween)
{
    this->pPrivate->Snapshots[this->pPrivate->LastIndex] = this->pPrivate->LastValue;
    if(++this->pPrivate->LastIndex == this->pPrivate->MaxSnapshots)
        this->pPrivate->LastIndex = 0;

    quint64 SumValue = 0;
    for(quint16 i=0; i < this->pPrivate->MaxSnapshots; ++i)
        SumValue+=this->pPrivate->Snapshots[i];

    this->pPrivate->LastSpeed = static_cast<quint64>((static_cast<double>(SumValue)) / (_secsBetween * this->pPrivate->MaxSnapshots));
}

}
}
