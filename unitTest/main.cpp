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
 * @author Behrooz Vedadian <vedadian@targoman.com>
 * @author Saeed Torabzadeh <saeed.torabzadeh@targoman.com>
 * @author Kambiz Zandi <kambizzandi@gmail.com>
 */

//#include "UnitTest.h"
//QTEST_MAIN(UnitTest)

#include <QtTest>
#include "testNullable.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication App(argc, argv);
    App.setAttribute(Qt::AA_Use96Dpi, true);

    bool BreakOnFirstFail = true;
    int FailedTests = 0;

    try {
        if (BreakOnFirstFail && !FailedTests) FailedTests += QTest::qExec(new testNullable, argc, argv);
    }
    catch (std::exception &e) {
        qDebug()<<e.what();
    }

    if (FailedTests > 0) {
        qDebug() << "total number of failed tests: " << FailedTests;
    }
    else {
        qDebug() << "all tests passed :)";
    }

    return FailedTests;
}
