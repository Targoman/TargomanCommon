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

TLog::TLog(const char *_function,
           const char *_file,
           quint16 _line,
           enuLogType::Type _type,
           quint8 _level
) :
    QDebug(&this->Buffer),
    Function(_function),
    File(_file),
    Line(_line),
    Type(_type),
    Level(_level),
    LogToFile(true),
    ShowLabel(true)
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
    if (this->LogToFile) {
        Targoman::Common::Logger::instance().write(QString("%1 %2:%3").arg(this->Function).arg(this->File).arg(this->Line),
                                                   this->Type,
                                                   this->Level,
                                                   this->Buffer,
                                                   this->ShowLabel);
    } else {
        clsOutputSettings *OutputSettings = &TARGOMAN_IO_SETTINGS.Info;
        QString color = TARGOMAN_COLOR_INFO;

        switch (this->Type) {
//            case enuLogType::Info:
//                OutputSettings = &TARGOMAN_IO_SETTINGS.Info;
//                color = TARGOMAN_COLOR_INFO;
//                break;
            case enuLogType::Warning:
                OutputSettings = &TARGOMAN_IO_SETTINGS.Warning;
                color = TARGOMAN_COLOR_WARNING;
                break;
            case enuLogType::Error:
                OutputSettings = &TARGOMAN_IO_SETTINGS.Error;
                color = TARGOMAN_COLOR_ERROR;
                break;
            case enuLogType::Debug:
                OutputSettings = &TARGOMAN_IO_SETTINGS.Debug;
                color = TARGOMAN_COLOR_DEBUG;
                break;
            case enuLogType::Happy:
                OutputSettings = &TARGOMAN_IO_SETTINGS.Happy;
                color = TARGOMAN_COLOR_HAPPY;
                break;
            default:
                break;
        }

        QString Out = color;

        if (this->ShowLabel)
            Out += QString("%1[%2][%3] ")
                   .arg(OutputSettings->details(this->Function.toStdString().c_str(), this->File.toStdString().c_str(), this->Line))
                   .arg(enuLogType::toStr(this->Type))
                   .arg(this->Level);

        Out += this->Buffer.trimmed();

        Out += TARGOMAN_COLOR_NORMAL;

        fprintf(stderr, "%s\n", Out.toStdString().c_str());
    }
}

TLog& TLog::noLog() {
    this->LogToFile = false;
    return *this;
}

TLog& TLog::noLabel() {
    this->ShowLabel = false;
    return *this;
}

} // namespace Targoman::Common
