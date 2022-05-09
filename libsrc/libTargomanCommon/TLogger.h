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

#ifndef TARGOMAN_COMMON_TLOGGER_H
#define TARGOMAN_COMMON_TLOGGER_H

#include <QDebug>
#include "Logger.h"
#include "CmdIO.h"

#define INTERNAL_tLogLog(_type, _level)  TLog(Q_FUNC_INFO, __FILE__, __LINE__, Targoman::Common::enuLogType::_type, _level)

#define tInfoLog(_level)    INTERNAL_tLogLog(Info, _level)
#define tInfo(_level)       tInfoLog(_level).nolog()

#define tDebugLog(_level)   INTERNAL_tLogLog(Debug, _level)
#define tDebug(_level)      tDebugLog(_level).nolog()

#define tWarnLog(_level)    INTERNAL_tLogLog(Warning, _level)
#define tWarn(_level)       tWarnLog(_level).nolog()

#define tHappyLog(_level)   INTERNAL_tLogLog(Happy, _level)
#define tHappy(_level)      tHappyLog(_level).nolog()

#define tErrorLog()         INTERNAL_tLogLog(Error, 0)
#define tError()            tErrorLog().nolog()

namespace Targoman::Common {

class TLog : public QDebug {
public:
    TLog(const char *_function,
         const char *_file,
         quint16 _line,
         enuLogType::Type _type,
         quint8 _level
         );
/*
    inline TLog(TLog &_other) :
        QDebug(&this->Buffer),
        Level(_other.Level),
        Type(_other.Type),
        Log(_other.Log),
        Buffer(_other.Buffer)
    {
        this->quote().space();
    }
*/
    virtual ~TLog();

    TLog& nolog();

protected:
    QString Function;
    QString File;
    quint16 Line;

    enuLogType::Type Type;
    quint8 Level;
    bool Log;
    QString Buffer;
};

} // namespace Targoman::Common

#endif // TARGOMAN_COMMON_TLOGGER_H
