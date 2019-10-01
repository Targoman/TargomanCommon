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
 * @author Behrooz Vedadian <vedadian@targoman.com>
 */

#include "tmplConfigurable.h"
#include "libTargomanCommon/CmdIO.h"
#include "../Private/clsConfigManager_p.h"

namespace Targoman {
namespace Common {
namespace Configuration {

/***************************************************************************************/
#define _NUMERIC_CONFIGURABLE_IMPL(_name, _variantType, _type, _nextType, _min, _max) \
    template <> \
    bool tmplConfigurable<_type>::validate(const QVariant& _value, QString& _errorMessage) const{ \
        if (_value.canConvert(_variantType) == false) {\
            _errorMessage = "Unable to convert " + _value.toString() + " to numeric."; \
            return false;\
        }else if (_value.value<_nextType>() > _max || _value.value<_nextType>() < _min ){ \
            _errorMessage = QString("%1 values must be between (%2 : %3)").arg(_name).arg(_min).arg(_max); \
            return false; \
        }else return true; \
    } \
    template <> \
    void tmplConfigurable<_type>::setFromVariant(const QVariant& _value) { \
        QString ErrorMessage; \
        if (this->validate(_value, ErrorMessage)) this->Value = _value.value<_type>(); \
        else throw exConfiguration(this->ConfigPath + ": " + ErrorMessage);\
    }\
    template <> \
    QString tmplConfigurable<_type>::validValues() const { return QString("%1 to %2").arg(_min).arg(_max); }


/***************************************************************************************/
_NUMERIC_CONFIGURABLE_IMPL("qint8",QVariant::Int,qint8,qint16, CHAR_MIN,CHAR_MAX)
_NUMERIC_CONFIGURABLE_IMPL("qint16",QVariant::Int,qint16,qint32, SHRT_MIN,SHRT_MAX)
#ifdef TARGOMAN_ARCHITECTURE_64
_NUMERIC_CONFIGURABLE_IMPL("qint32",QVariant::Int,qint32,qint64, INT_MIN, INT_MAX)
_NUMERIC_CONFIGURABLE_IMPL("qint64",QVariant::Int,qint64,qint64, LONG_MIN,LONG_MAX)
#else
_NUMERIC_CONFIGURABLE_IMPL("qint32",QVariant::LongLong,qint32,qint64, LONG_MIN, LONG_MAX);
_NUMERIC_CONFIGURABLE_IMPL("qint64",QVariant::LongLong,qint64,qint64, LONG_LONG_MIN,LONG_LONG_MAX);
#endif

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtype-limits"
_NUMERIC_CONFIGURABLE_IMPL("quint8",QVariant::UInt,quint8,quint16, 0,UCHAR_MAX)
_NUMERIC_CONFIGURABLE_IMPL("quint16",QVariant::UInt,quint16,quint32, 0,USHRT_MAX)
#ifdef TARGOMAN_ARCHITECTURE_64
_NUMERIC_CONFIGURABLE_IMPL("quint32",QVariant::ULongLong,quint32,quint64, 0, UINT_MAX)
_NUMERIC_CONFIGURABLE_IMPL("quint64",QVariant::ULongLong,quint64,quint64, 0,ULONG_MAX)
#else
_NUMERIC_CONFIGURABLE_IMPL("quint32",QVariant::ULongLong,quint32,quint64, 0, ULONG_MAX)
_NUMERIC_CONFIGURABLE_IMPL("quint64",QVariant::ULongLong,quint64,quint64, 0,ULONG_LONG_MAX)
#endif

_NUMERIC_CONFIGURABLE_IMPL("double",QVariant::Double,double,double, -DBL_MAX, DBL_MAX)
_NUMERIC_CONFIGURABLE_IMPL("float",QVariant::Double, float,double, -FLT_MAX,FLT_MAX)
#pragma GCC diagnostic pop

//////QString
template <>
bool tmplConfigurable<QString>::validate(const QVariant&, QString& )const { return true; }
template <>
void tmplConfigurable<QString>::setFromVariant(const QVariant& _value){ this->Value = _value.toString(); }
template <>
QString tmplConfigurable<QString>::validValues() const { return ""; }

//////QUrl
template <>
bool tmplConfigurable<QUrl>::validate(const QVariant& _value, QString& _error)const {
    QUrl URL(_value.toString());
    if(URL.isValid())
        return true;

    _error = "Invalid URL provided";
    return false;
}
template <>
void tmplConfigurable<QUrl>::setFromVariant(const QVariant& _value){ this->Value = QUrl(_value.toString()); }
template <>
QString tmplConfigurable<QUrl>::validValues() const { return "A Valid URL"; }

//////FilePath_t
template <>
bool tmplConfigurable<FilePath_t>::validate(const QVariant&, QString& )const { return true; }
template <>
void tmplConfigurable<FilePath_t>::setFromVariant(const QVariant& _value){
    this->Value = ConfigManager::instance().getAbsolutePath(_value.toString());
}
template <>
QString tmplConfigurable<FilePath_t>::validValues() const { return "valid path according to description"; }

//////QStringList
template <>
bool tmplConfigurable<QStringList>::validate(const QVariant& , QString&  )const {
    return true;
}
template <>
void tmplConfigurable<QStringList>::setFromVariant(const QVariant& _value){
    QString ErrorMessage;
    if (this->validate(_value, ErrorMessage)){
        if (_value.canConvert(QVariant::StringList))
            this->Value = _value.toStringList();
        else
            this->Value = _value.toString().split(',');
    }
    else
        throw exConfiguration(this->ConfigPath + ": " + ErrorMessage);
}
template <>
QVariant tmplConfigurable<QStringList>::toVariant() const{
    return this->Value.join(",");
}
template <>
QString tmplConfigurable<QStringList>::validValues() const { return "Comma separated strings according to description"; }


//////bool
template <>
bool tmplConfigurable<bool>::validate(const QVariant& _value, QString& _errorMessage) const{
    if (_value.canConvert(QVariant::Bool) == false) {
        _errorMessage = "Unable to convert " + _value.toString() + " to bool.";
        return false;
    }else
        return true;
}
template <>
void tmplConfigurable<bool>::setFromVariant(const QVariant& _value){
    QString ErrorMessage;
    if (this->validate(_value, ErrorMessage)) this->Value = _value.value<bool>();
    else throw exConfiguration(this->ConfigPath + ": " + ErrorMessage);
}
template <>
QString tmplConfigurable<bool>::validValues() const { return "true|false|0|1"; }

//////QRegExp
template <>
bool tmplConfigurable<QRegExp>::validate(const QVariant& _value, QString& _errorMessage) const{
    _errorMessage = "As QRegExp is not Thread safe we must change some of its methods to be thread safe. Use it at your own risk.";
    return false;

    if (_value.toString().size()){
        QRegExp TempRegex(_value.toString(), Qt::CaseSensitive, QRegExp::RegExp);
        if (TempRegex.isValid() == false){
            _errorMessage = "Invalid RegEx pattern: " + TempRegex.errorString();
            return false;
        }
    }
    return true;
}
template <>
void tmplConfigurable<QRegExp>::setFromVariant(const QVariant& _value){
    QString ErrorMessage;
    if (this->validate(_value, ErrorMessage)) this->Value = QRegExp(_value.value<QString>(),
                                                                    Qt::CaseSensitive,
                                                                    QRegExp::RegExp);
    else throw exConfiguration(this->ConfigPath + ": " + ErrorMessage);
}

template <>
QVariant tmplConfigurable<QRegExp>::toVariant() const{
    return this->Value.pattern();
}
template <>
QString tmplConfigurable<QRegExp>::validValues() const { return "Valid regular expression"; }

/////////////////////////////////////////////////////////////////////////////////////
template <>
bool tmplConfigurable<QWildCard>::validate(const QVariant& _value, QString& _errorMessage) const{
    if (_value.toString().size()){
        QWildCard TempRegex(_value.toString(), Qt::CaseSensitive, QRegExp::WildcardUnix);
        if (TempRegex.isValid() == false){
            _errorMessage = "Invalid wildcard pattern: " + TempRegex.errorString();
            return false;
        }
    }
    return true;
}
template <>
void tmplConfigurable<QWildCard>::setFromVariant(const QVariant& _value){
    QString ErrorMessage;
    if (this->validate(_value, ErrorMessage))this->Value = QWildCard(_value.value<QString>(),
                                                                   Qt::CaseSensitive,
                                                                   QRegExp::WildcardUnix);
    else throw exConfiguration(this->ConfigPath + ": " + ErrorMessage);
}

template <>
QVariant tmplConfigurable<QWildCard>::toVariant() const{
    return this->Value.pattern();
}
template <>
QString tmplConfigurable<QWildCard>::validValues() const { return "Valid wildcard expression"; }

/***********************************************************************************************/
namespace Private {

class intfConfigurablePrivate{
public:
    /**
     * @brief  updateConfig Finds location which _old configurable pointer is located in Configs hash map and changes its value with _new configurable pointer.
     * @param _old          old configurable pointer.
     * @param _new          new configurable pointer.
     */
    void updateConfig(const intfConfigurable* _old, intfConfigurable* _new){
        ConfigManager::instance().pPrivate->Configs[
                ConfigManager::instance().pPrivate->Configs.key((intfConfigurable*)_old)] = _new;
    }

    std::function<void(const intfConfigurable& _item)> Finalizer;
};

}

/**
 * @brief constructor of intfConfigurable. this is where each configurable inserts itself to Configs hash map of pPrivate member of ConfigManager class.
 */
intfConfigurable::intfConfigurable(enuConfigType::Type _configType,
                                   const clsConfigPath& _configPath,
                                   const QString &_description,
                                   const QString &_shortSwitch,
                                   const QString &_shortHelp,
                                   const QString &_longSwitch,
                                   QFlags<enuConfigSource::Type> _configSources,
                                   bool _remoteView,
                                   const std::function<void(const intfConfigurable& _item)> &_finalizer) :
    pPrivate(new Private::intfConfigurablePrivate)
{
    try{
        this->ConfigType  = _configType;
        this->Description = _description;
        this->ShortSwitch = _shortSwitch;
        this->LongSwitch = _longSwitch.toLower();
        this->ShortHelp = _shortHelp;
        this->pPrivate->Finalizer = _finalizer;

        this->ConfigPath = _configPath.Path;
        this->ConfigPath.replace("//", "/");
        this->ConfigPath.replace("//", "/");

        if (this->ConfigPath.startsWith('/'))
            this->ConfigPath = this->ConfigPath.mid(1);

        if (_configType == enuConfigType::Array ||
            _configType == enuConfigType::FileBased ||
            _configType == enuConfigType::MultiMap)
            if (this->ConfigPath.endsWith("/") == false)
                this->ConfigPath.append("/");

        if (_configSources.testFlag(enuConfigSource::Arg) && _shortSwitch == "" && _longSwitch == "")
            throw exConfiguration(this->configPath() + " defined to be configured by argument but no switch provided");

        if (_shortSwitch.size() || _longSwitch.size())
            _configSources = _configSources | enuConfigSource::Arg;

        this->ArgCount = static_cast<qint8>(this->shortHelp().size() ? this->ShortHelp.split(" ").size() : 0);
        this->WasConfigured = false;
        this->ConfigSources = _configSources;
        this->RemoteViewAllowed = _remoteView;


        ConfigManager::instance().addConfig(this->ConfigPath, this);
    }catch(exTargomanBase &e){
        TargomanError(e.what());
        throw;
    }
}
/**
 * @brief intfConfigurable::intfConfigurable Copy constructor of intfConfigurable class.
 *
 * This function is defined to call updateConfig function of #pPrivate.
 * Usage of this function is when we have QList of Configurables and we want to insert a new configurable to it.
 * When a temporary configurable is instantiated to be inserted into QList, its pointer will be added into Configs hash map, but that pointer will be deleted soon because it is temporary.
 * This copy constructor will be called when the temporary configurable is inserted into QList.
 * Calling updateConfig in this copy constructor, helps us to change the deleted pointer with the valid pointer of configurable which is in the QList.
 */
intfConfigurable::intfConfigurable(const intfConfigurable &_other):
    pPrivate(new Private::intfConfigurablePrivate)
{
    *this = _other;
}

intfConfigurable &intfConfigurable::operator =(const intfConfigurable &_other)
{
    this->Description = _other.Description;
    this->ShortSwitch = _other.ShortSwitch;
    this->LongSwitch = _other.LongSwitch;
    this->ShortHelp = _other.ShortHelp;
    this->ConfigPath = _other.ConfigPath;
    this->WasConfigured  = _other.WasConfigured;
    this->ConfigSources = _other.ConfigSources;
    this->ArgCount = _other.ArgCount;
    this->ConfigType = _other.ConfigType;
    this->RemoteViewAllowed = _other.RemoteViewAllowed;

    //To replace pointer of old registered config with the new copied config
    this->pPrivate->updateConfig(&_other, this);
    this->pPrivate->Finalizer = _other.pPrivate->Finalizer;
    return *this;
}

intfConfigurable::~intfConfigurable()
{
    //Just to suppress compiler error on QSopedPointer
}

void intfConfigurable::finalizeConfig()
{
    this->pPrivate->Finalizer(*this);
}

}
}
}
