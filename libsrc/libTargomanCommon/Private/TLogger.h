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
//#include "Logger.h"
//#include "CmdIO.h"

#define INTERNAL_tLogLog(_type, _level)  TLog(Q_FUNC_INFO, __FILE__, __LINE__, Targoman::Common::enuLogType::_type, _level)

namespace Targoman::Common::Private {

class TLog : public QDebug {
public:
    TLog(const char *_function,
         const char *_file,
         quint16 _line,
         /*enuLogType::Type*/ quint8 _type,
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

    TLog& noLog();
    TLog& noLabel();

protected:
    QString Function;
    QString File;
    quint16 Line;

    /*enuLogType::Type*/ quint8 Type;
    quint8 Level;
    bool LogToFile;
    bool ShowLabel;

    QString Buffer;
};

} // namespace Targoman::Common::Private

#endif // TARGOMAN_COMMON_TLOGGER_H
