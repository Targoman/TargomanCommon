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

#include "TLogger.h"

namespace Targoman::Common {

TLog::TLog(const char *_funcName, enuLogType::Type _type, quint8 _level) :
    QDebug(&this->Buffer),
    FuncName(_funcName),
    Type(_type),
    Level(_level),
    Log(true)
{
    this->quote().space();
}
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
TLog::~TLog() {
    if (this->Log) {
        Targoman::Common::Logger::instance().write(this->FuncName,
                                                   this->Type,
                                                   this->Level,
                                                   this->Buffer);
    } else {
        std::string color = TARGOMAN_COLOR_INFO;

        switch (this->Type) {
            case enuLogType::Info:
                color = TARGOMAN_COLOR_INFO;
                break;
            case enuLogType::Warning:
                color = TARGOMAN_COLOR_WARNING;
                break;
            case enuLogType::Error:
                color = TARGOMAN_COLOR_ERROR;
                break;
            case enuLogType::Debug:
                color = TARGOMAN_COLOR_DEBUG;
                break;
            case enuLogType::Happy:
                color = TARGOMAN_COLOR_HAPPY;
                break;
            default:
                break;
        }

        fprintf(stderr,
                "%s%s[%s][%d] %s%s\n",
                color.c_str(),
                this->FuncName.toStdString().c_str(),
                enuLogType::toStr(this->Type),
                this->Level,
                TARGOMAN_COLOR_NORMAL,
                this->Buffer.toStdString().c_str()
                );
    }
}

TLog& TLog::nolog() {
    this->Log = false;
    return *this;
}

} // namespace Targoman::Common
