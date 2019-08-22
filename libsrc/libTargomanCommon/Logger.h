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

#ifndef TARGOMAN_COMMON_LOGGER_H
#define TARGOMAN_COMMON_LOGGER_H

#include <QObject>
#include <QTime>
#include <QMap>
#include <QMetaType>

#include "libTargomanCommon/exTargomanBase.h"

namespace Targoman {
namespace Common {

TARGOMAN_ADD_EXCEPTION_HANDLER(exLogger, Targoman::Common::exTargomanBase);



/** @brief These are helper macros to ease usage of Logger */
#define TargomanLogWarn(_level, _message) {\
    QString Buffer; \
    Targoman::Common::Logger::instance().write(Q_FUNC_INFO, \
                                               Targoman::Common::enuLogType::Warning, \
                                               _level,\
                                               *(QTextStream(&Buffer)<<_message).string());\
}

#define TargomanLogInfo( _level, _message) {\
    QString Buffer; \
    Targoman::Common::Logger::instance().write(Q_FUNC_INFO, \
                                               Targoman::Common::enuLogType::Info, \
                                               _level,\
                                               *(QTextStream(&Buffer)<<_message).string());\
}

#define TargomanLogError( _message) {\
    QString Buffer; \
    Targoman::Common::Logger::instance().write(Q_FUNC_INFO, \
                                               Targoman::Common::enuLogType::Error, \
                                               1,\
                                               *(QTextStream(&Buffer)<<_message).string());\
}

#if TARGOMAN_SHOW_DEBUG
    #define TargomanLogDebug(_level, _message) {\
        QString Buffer; \
        Targoman::Common::Logger::instance().write(Q_FUNC_INFO, \
                                                   Targoman::Common::enuLogType::Debug, \
                                                   _level,\
                                                   *(QTextStream(&Buffer)<<_message).string());\
    }
#else
    #define TargomanLogDebug(_level, _message) {}
#endif //TARGOMAN_SHOW_DEBUG

#define TargomanLogHappy(_level, _message) {\
    QString Buffer; \
    Targoman::Common::Logger::instance().write(Q_FUNC_INFO, \
                                               Targoman::Common::enuLogType::Happy, \
                                               _level,\
                                               *(QTextStream(&Buffer)<<_message).string());\
}

namespace Private {
class LoggerPrivate;
}

/**
 * @enum   enuLogType An enum defining all the valid Log Types
 * @value  Info
 * @value  Warning
 * @value  Error
 * @value  Debug
 * @value  Happy
 **/
TARGOMAN_DEFINE_ENHANCED_ENUM(enuLogType,
                              Info,
                              Warning,
                              Error,
                              Debug,
                              Happy
                              );

/**
 * @class clsLogSettings
 * This class is used for defining and checking options for log files.
 * Pointer of this class is used in LoggerPrivate class as a data member.
 */
class clsLogSettings
{
    public:
    /**
     * @brief Constructor sets level of details at highest level.
     */
    clsLogSettings(){
        this->Details = 0xFF;
    }
    /**
     * @brief validateLevel
     * @exception throws exceptions if input level is equal or greater than 10
     */
    inline bool validateLevel(quint8 _level){
        Q_ASSERT_X(_level < 10, "LogSettings",  "Level must be between 0 to 9");
        if (_level > 9)
            throw exLogger("Logger log Level must be between 0 to 9");
        return true;
    }
    /**
     * @brief canBeShown
     * @return Returns true if #Details is greater than _level
     */
    inline bool canBeShown(quint8 _level){
        return (this->Details & 0x0F) >= _level;
    }

    inline void setDetails(bool _time = false, bool _actor = false) {
        this->Details &= 0x0F;
        if(_time)
            this->Details |= 0x10;
        if(_actor)
            this->Details |= 0x40;
    }

    inline QString details(const QString& _callerFuncName){
        QString OutStr;
        OutStr +=  (this->Details & 0x10 ?
                    QString("[" + QDateTime().currentDateTime().toString("dd-MM-yyyy hh:mm:ss.zzz") + "]") :
                    QString(""));
        if (this->Details & 0x40)
                OutStr +=   "[" + this->getPrettyModuleName(_callerFuncName) + "]";

        return OutStr;
    }

    /**
     * @brief getPrettyModuleName
     * @param _callerFuncName
     * @return
     */
    QString getPrettyModuleName(const QString& _callerFuncName);

    /**
     * @brief sets level of details.
     */
    inline void setLevel(quint8 _level){
        this->validateLevel(_level);
        this->Details = (this->Details & 0xF0) + _level;
    }

    private:
    quint8 Details; /**< This variable is used for setting level of details in log file. Just higher bits of this variable is used*/
};

/**
 * @brief The stuLogMessage struct is used to add new Log to Logger engine.
 */
struct stuLogMessage
{
    QDateTime DateTime;
    QString   PrettyModuleName;
    enuLogType::Type Type;
    quint8 Level;
    QString Message;

    /**
   * @brief stuLogMessage Helper method/constructor of stuLogMessage to be used to create new Log Struct
   * @param _callerFuncName function who has called logger
   * @param _type Type of the Log baesed on \a enuLogType enumeration
   * @param _level Level of the log. used to ignore or filter some log levels
   * @param _message Message of the log
   * @param _dateTime Date and time of the generated Log. This will be stored to File/DB instead of the write time
   */
    stuLogMessage(QString   _callerFuncName,
                  enuLogType::Type _type,
                  quint8 _level,
                  QString _message,
                  QDateTime _dateTime = QDateTime::currentDateTime())
    {
        this->DateTime = _dateTime;
        this->PrettyModuleName = _callerFuncName;
        this->Type = _type;
        this->Level = _level;
        this->Message = _message;
    }
};

/**
 * @class Logger
 * @inmodule Targoman::Common
 * @brief The Logger class is a single instance class shared among all the modules. This class is mostly used by
 * macros instead of accesing its methods directly
 */
class Logger : public QObject
{
    Q_OBJECT
public:
    static inline Logger& instance(){
        static Logger* Instance = nullptr;
        return *(Q_LIKELY(Instance) ? Instance : (Instance = new Logger));
    }
    ~Logger();
    static inline QString moduleName(){ return "Logger";}

    bool init();
    /**
     * @brief Initialization method. If Logger is not initialized then no other function will work
     *
     * @param _fileName Output file where save logs Defaults to "stderr".
     * @param _maxSize Maximum file size before rotate in MegaBytes Defaults to 10.
     * @return bool true if successful else false
     **/
    bool   init(const QString& _fileName,
                quint64 _maxSize = 10,
                bool _show = true);
    /**
     * @brief Base Log Write function. This function is better called via Macros. @see Macros
     *
     * @param _actorID UUID of the actor who is logging
     * @param _type Log Type from enuLogType
     * @param _level An integer below or equal 10 specifiying Log priority
     * @param _message Message to be written as Log
     * @return void in case of any error it will rais an exception
     * @param _newLine if this is true, newline character will be added after printing message in log file.
     * @exception throws exception if _actorID and value of _actorID in LoggerPrivate#Actor is empty.
     */
    void   write(const QString&     _callerFuncName,
                 enuLogType::Type   _type,
                 quint8             _level,
                 const QString&     _message,
                 bool _newLine = true);


    /**
     * @brief setActive Activates and deactivates logging
     * @param _state
     */
    void setActive(bool _state = true);

    bool isActive();

    /**
     * @brief setVisible if set to active logs will be shown in stdout/sterr while saving
     * @param _state
     */
    void setVisible(bool _state = true);

    bool isVisible();
private:
    /**
     * @brief sets all kinds logSettings levels to lowest level.
     */
    Logger(QObject *parent=nullptr);

signals:
    void sigLogAdded(const QDateTime& _time,
                     QString          _callerFuncName,
                     enuLogType::Type _type,
                     quint8           _level,
                     const QString& _message);

private:
    static Logger* Instance;
    QScopedPointer<Targoman::Common::Private::LoggerPrivate> pPrivate;

    friend class Targoman::Common::Private::LoggerPrivate;
};

}
}

/* Below line will register enuLogType as a MetaType to be used in signals and slots */
Q_DECLARE_METATYPE(Targoman::Common::enuLogType::Type)

#endif // TARGOMAN_COMMON_LOGGER_H
