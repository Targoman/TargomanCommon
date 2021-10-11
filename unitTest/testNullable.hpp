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
 * @author Kambiz Zandi <kambizzandi@gmail.com>
 */

#ifndef TESTNULLABLE_HPP
#define TESTNULLABLE_HPP

#include <QtTest/QtTest>
#include "libTargomanCommon/Macros.h"

class testNullable : public QObject
{
    Q_OBJECT

private slots:
    void test_type()
    {
        TARGOMAN_NULLABLE_TYPE(int) a;

        //------------------------
        QVERIFY(TARGOMAN_NULLABLE_IS_NULL(a));
        QVERIFY(TARGOMAN_NULLABLE_GET_OR_DEFAULT(a, 456) == 456);

        //------------------------
        TARGOMAN_NULLABLE_SET(a, 123);
        QVERIFY(TARGOMAN_NULLABLE_HAS_VALUE(a));
        QVERIFY(TARGOMAN_NULLABLE_GET(a) == 123);
        QVERIFY(TARGOMAN_NULLABLE_GET_OR_DEFAULT(a, 456) == 123);

        //------------------------
        TARGOMAN_NULLABLE_RESET(a);
        QVERIFY(TARGOMAN_NULLABLE_IS_NULL(a));
        QVERIFY(TARGOMAN_NULLABLE_GET_OR_DEFAULT(a, 456) == 456);
    }

    void test_var()
    {
        TARGOMAN_NULLABLE_VAR(int, a);

        //------------------------
        QVERIFY(TARGOMAN_NULLABLE_IS_NULL(a));
        QVERIFY(TARGOMAN_NULLABLE_GET_OR_DEFAULT(a, 456) == 456);

        //------------------------
        TARGOMAN_NULLABLE_SET(a, 123);
        QVERIFY(TARGOMAN_NULLABLE_HAS_VALUE(a));
        QVERIFY(TARGOMAN_NULLABLE_GET(a) == 123);
        QVERIFY(TARGOMAN_NULLABLE_GET_OR_DEFAULT(a, 456) == 123);

        //------------------------
        TARGOMAN_NULLABLE_RESET(a);
        QVERIFY(TARGOMAN_NULLABLE_IS_NULL(a));
        QVERIFY(TARGOMAN_NULLABLE_GET_OR_DEFAULT(a, 456) == 456);
    }

};

#endif // TESTNULLABLE_HPP
