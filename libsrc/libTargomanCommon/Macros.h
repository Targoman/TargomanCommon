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

#ifndef TARGOMAN_COMMON_MACROS_H_
#define TARGOMAN_COMMON_MACROS_H_

#include <string>
#include <QString>
#include <QStringList>
#include <cstring>
#include <functional>
#include <QDebug>

/********************************************************************************************
  Environmet detection macros
 ********************************************************************************************/
// Check and recognize arechitecture
#if __GNUC__
  #if __x86_64__ || __ppc64__
    #define TARGOMAN_ARCHITECTURE_64
  #else
    #define TARGOMAN_ARCHITECTURE_32
  #endif
#elif _WIN32 || _WIN64
  #if _WIN64
    #define TARGOMAN_ARCHITECTURE_64
  #else
    #define TARGOMAN_ARCHITECTURE_32
  #endif
#endif

/********************************************************************************************
 * Helper Macros (Macro in Macro) These macros must be used jusrt in other macros
 ********************************************************************************************/

#define TARGOMAN_M2CONCAT(_Arg1, _Arg2) _Arg1##_Arg2
#define TARGOMAN_M3CONCAT(_Arg1, _Arg2, _Arg3) _Arg1##_Arg2##_Arg3
#define TARGOMAN_M4CONCAT(_Arg1, _Arg2, _Arg3, _Arg4) _Arg1##_Arg2##_Arg3##_Arg4
#define TARGOMAN_M7CONCAT(_Arg1, _Arg2, _Arg3, _Arg4, _Arg5, _Arg6, _Arg7) _Arg1##_Arg2##_Arg3##_Arg4##_Arg5##_Arg6##_Arg7

#define TARGOMAN_STR_VALUE(_arg)      #_arg
#define TARGOMAN_M2STR(_Macro) TARGOMAN_STR_VALUE(_Macro)
#define TARGOMAN_M2STR_WITHCOMMA(_Macro) TARGOMAN_STR_VALUE(_Macro),

#define TARGOMAN_MACRO_ARG_COUNT_HELPER( \
    _1,_2,_3,_4,_5,_6,_7,_8,_9,  \
    _10,_11,_12,_13,_14,_15,_16,_17,_18,_19,  \
    _20,_21,_22,_23,_24,_25,_26,_27,_28,_29,  \
    _30,_31,_32,_33,_34,_35,_36,_37,_38,_39,  \
    _40,_41,_42,_43,_44,_45,_46,_47,_48,_49,  \
    _50,_51,_52,_53,_54,_55,_56,_57,_58,_59,  \
    N,...) N

#define TARGOMAN_MACRO_ARG_COUNT(...) \
    TARGOMAN_MACRO_ARG_COUNT_HELPER(__VA_ARGS__,\
    59,58,57,56,55,54,53,52,51,50,  \
    49,48,47,46,45,44,43,42,41,40,  \
    39,38,37,36,35,34,33,32,31,30,  \
    29,28,27,26,25,24,23,22,21,20,  \
    19,18,17,16,15,14,13,12,11,10,  \
    9,8,7,6,5,4,3,2,1,0)

#define TARGOMAN_MACRO_ARG_BASED_FUNC(_fn,...) TARGOMAN_MACRO_ARG_COUNT_HELPER(__VA_ARGS__,\
    _fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,  \
    _fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,  \
    _fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,  \
    _fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,  \
    _fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,  \
    _fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Single, None)

// Following definition is used in complex templates where a template is instantiating other templates which needs comma
#define TARGOMAN_VIRTUAL_COMMA() ,

#define PRIV_TMFE_1(_do, X) _do(X)
#define PRIV_TMFE_2(_do, X, ...) _do(X)PRIV_TMFE_1(_do, __VA_ARGS__)
#define PRIV_TMFE_3(_do, X, ...) _do(X)PRIV_TMFE_2(_do, __VA_ARGS__)
#define PRIV_TMFE_4(_do, X, ...) _do(X)PRIV_TMFE_3(_do, __VA_ARGS__)
#define PRIV_TMFE_5(_do, X, ...) _do(X)PRIV_TMFE_4(_do, __VA_ARGS__)
#define PRIV_TMFE_6(_do, X, ...) _do(X)PRIV_TMFE_5(_do, __VA_ARGS__)
#define PRIV_TMFE_7(_do, X, ...) _do(X)PRIV_TMFE_6(_do, __VA_ARGS__)
#define PRIV_TMFE_8(_do, X, ...) _do(X)PRIV_TMFE_7(_do, __VA_ARGS__)
#define PRIV_TMFE_9(_do, X, ...) _do(X)PRIV_TMFE_8(_do, __VA_ARGS__)
#define PRIV_TMFE_10(_do, X, ...) _do(X)PRIV_TMFE_9(_do, __VA_ARGS__)
#define PRIV_TMFE_11(_do, X, ...) _do(X)PRIV_TMFE_10(_do, __VA_ARGS__)
#define PRIV_TMFE_12(_do, X, ...) _do(X)PRIV_TMFE_11(_do, __VA_ARGS__)
#define PRIV_TMFE_13(_do, X, ...) _do(X)PRIV_TMFE_12(_do, __VA_ARGS__)
#define PRIV_TMFE_14(_do, X, ...) _do(X)PRIV_TMFE_13(_do, __VA_ARGS__)
#define PRIV_TMFE_15(_do, X, ...) _do(X)PRIV_TMFE_14(_do, __VA_ARGS__)
#define PRIV_TMFE_16(_do, X, ...) _do(X)PRIV_TMFE_15(_do, __VA_ARGS__)
#define PRIV_TMFE_17(_do, X, ...) _do(X)PRIV_TMFE_16(_do, __VA_ARGS__)
#define PRIV_TMFE_18(_do, X, ...) _do(X)PRIV_TMFE_17(_do, __VA_ARGS__)
#define PRIV_TMFE_19(_do, X, ...) _do(X)PRIV_TMFE_18(_do, __VA_ARGS__)
#define PRIV_TMFE_20(_do, X, ...) _do(X)PRIV_TMFE_19(_do, __VA_ARGS__)
#define PRIV_TMFE_21(_do, X, ...) _do(X)PRIV_TMFE_20(_do, __VA_ARGS__)
#define PRIV_TMFE_22(_do, X, ...) _do(X)PRIV_TMFE_21(_do, __VA_ARGS__)
#define PRIV_TMFE_23(_do, X, ...) _do(X)PRIV_TMFE_22(_do, __VA_ARGS__)
#define PRIV_TMFE_24(_do, X, ...) _do(X)PRIV_TMFE_23(_do, __VA_ARGS__)
#define PRIV_TMFE_25(_do, X, ...) _do(X)PRIV_TMFE_24(_do, __VA_ARGS__)
#define PRIV_TMFE_26(_do, X, ...) _do(X)PRIV_TMFE_25(_do, __VA_ARGS__)
#define PRIV_TMFE_27(_do, X, ...) _do(X)PRIV_TMFE_26(_do, __VA_ARGS__)
#define PRIV_TMFE_28(_do, X, ...) _do(X)PRIV_TMFE_27(_do, __VA_ARGS__)
#define PRIV_TMFE_29(_do, X, ...) _do(X)PRIV_TMFE_28(_do, __VA_ARGS__)
#define PRIV_TMFE_30(_do, X, ...) _do(X)PRIV_TMFE_29(_do, __VA_ARGS__)
#define PRIV_TMFE_31(_do, X, ...) _do(X)PRIV_TMFE_30(_do, __VA_ARGS__)
#define PRIV_TMFE_32(_do, X, ...) _do(X)PRIV_TMFE_31(_do, __VA_ARGS__)
#define PRIV_TMFE_33(_do, X, ...) _do(X)PRIV_TMFE_32(_do, __VA_ARGS__)
#define PRIV_TMFE_34(_do, X, ...) _do(X)PRIV_TMFE_33(_do, __VA_ARGS__)
#define PRIV_TMFE_35(_do, X, ...) _do(X)PRIV_TMFE_34(_do, __VA_ARGS__)
#define PRIV_TMFE_36(_do, X, ...) _do(X)PRIV_TMFE_35(_do, __VA_ARGS__)
#define PRIV_TMFE_37(_do, X, ...) _do(X)PRIV_TMFE_36(_do, __VA_ARGS__)
#define PRIV_TMFE_38(_do, X, ...) _do(X)PRIV_TMFE_37(_do, __VA_ARGS__)
#define PRIV_TMFE_39(_do, X, ...) _do(X)PRIV_TMFE_38(_do, __VA_ARGS__)
#define PRIV_TMFE_40(_do, X, ...) _do(X)PRIV_TMFE_39(_do, __VA_ARGS__)
#define PRIV_TMFE_41(_do, X, ...) _do(X)PRIV_TMFE_40(_do, __VA_ARGS__)
#define PRIV_TMFE_42(_do, X, ...) _do(X)PRIV_TMFE_41(_do, __VA_ARGS__)
#define PRIV_TMFE_43(_do, X, ...) _do(X)PRIV_TMFE_42(_do, __VA_ARGS__)
#define PRIV_TMFE_44(_do, X, ...) _do(X)PRIV_TMFE_43(_do, __VA_ARGS__)
#define PRIV_TMFE_45(_do, X, ...) _do(X)PRIV_TMFE_44(_do, __VA_ARGS__)
#define PRIV_TMFE_46(_do, X, ...) _do(X)PRIV_TMFE_45(_do, __VA_ARGS__)
#define PRIV_TMFE_47(_do, X, ...) _do(X)PRIV_TMFE_46(_do, __VA_ARGS__)
#define PRIV_TMFE_48(_do, X, ...) _do(X)PRIV_TMFE_47(_do, __VA_ARGS__)
#define PRIV_TMFE_49(_do, X, ...) _do(X)PRIV_TMFE_48(_do, __VA_ARGS__)
#define PRIV_TMFE_50(_do, X, ...) _do(X)PRIV_TMFE_49(_do, __VA_ARGS__)
#define PRIV_TMFE_51(_do, X, ...) _do(X)PRIV_TMFE_50(_do, __VA_ARGS__)
#define PRIV_TMFE_52(_do, X, ...) _do(X)PRIV_TMFE_51(_do, __VA_ARGS__)
#define PRIV_TMFE_53(_do, X, ...) _do(X)PRIV_TMFE_52(_do, __VA_ARGS__)
#define PRIV_TMFE_54(_do, X, ...) _do(X)PRIV_TMFE_53(_do, __VA_ARGS__)
#define PRIV_TMFE_55(_do, X, ...) _do(X)PRIV_TMFE_54(_do, __VA_ARGS__)
#define PRIV_TMFE_56(_do, X, ...) _do(X)PRIV_TMFE_55(_do, __VA_ARGS__)
#define PRIV_TMFE_57(_do, X, ...) _do(X)PRIV_TMFE_56(_do, __VA_ARGS__)
#define PRIV_TMFE_58(_do, X, ...) _do(X)PRIV_TMFE_57(_do, __VA_ARGS__)
#define PRIV_TMFE_59(_do, X, ...) _do(X)PRIV_TMFE_58(_do, __VA_ARGS__)

#define TARGOMAN_MACRO_FOREACH(action,...) \
  TARGOMAN_MACRO_ARG_COUNT_HELPER(__VA_ARGS__,\
    PRIV_TMFE_59,PRIV_TMFE_58,PRIV_TMFE_57,PRIV_TMFE_56,PRIV_TMFE_55,PRIV_TMFE_54,PRIV_TMFE_53,PRIV_TMFE_52,PRIV_TMFE_51,PRIV_TMFE_50, \
    PRIV_TMFE_49,PRIV_TMFE_48,PRIV_TMFE_47,PRIV_TMFE_46,PRIV_TMFE_45,PRIV_TMFE_44,PRIV_TMFE_43,PRIV_TMFE_42,PRIV_TMFE_41,PRIV_TMFE_40, \
    PRIV_TMFE_39,PRIV_TMFE_38,PRIV_TMFE_37,PRIV_TMFE_36,PRIV_TMFE_35,PRIV_TMFE_34,PRIV_TMFE_33,PRIV_TMFE_32,PRIV_TMFE_31,PRIV_TMFE_30, \
    PRIV_TMFE_29,PRIV_TMFE_28,PRIV_TMFE_27,PRIV_TMFE_26,PRIV_TMFE_25,PRIV_TMFE_24,PRIV_TMFE_23,PRIV_TMFE_22,PRIV_TMFE_21,PRIV_TMFE_20, \
    PRIV_TMFE_19,PRIV_TMFE_18,PRIV_TMFE_17,PRIV_TMFE_16,PRIV_TMFE_15,PRIV_TMFE_14,PRIV_TMFE_13,PRIV_TMFE_12,PRIV_TMFE_11,PRIV_TMFE_10, \
    PRIV_TMFE_9,PRIV_TMFE_8,PRIV_TMFE_7,PRIV_TMFE_6,PRIV_TMFE_5,PRIV_TMFE_4,PRIV_TMFE_3,PRIV_TMFE_2,PRIV_TMFE_1)(action,__VA_ARGS__)

/********************************************************************************************
 * Predefined functions. This macro must be included in all libraries.
 ********************************************************************************************/
#ifdef TARGOMAN_SHOW_DEBUG
    #define TARGOMAN_LIBRARY_VERSION \
    extern "C" std::string getTargomanLibVersion() { \
      return std::string("Version: ") + \
             std::string(TARGOMAN_M2STR(PROJ_VERSION)) + \
             std::string(" [DEBUG] Last Build: ") + \
             std::string(__DATE__);}
#else
    #define TARGOMAN_LIBRARY_VERSION \
    extern "C" std::string getTargomanLibVersion() { \
      return std::string("Version: ") + \
             std::string(TARGOMAN_M2STR(PROJ_VERSION)) + \
             std::string(" [RELEASE] Last Build: ") + \
             std::string(__DATE__);}
#endif

/********************************************************************************************
 * Base Macros.
 ********************************************************************************************/
/** @brief A Macro to define a property with it's getters and setters */
#define TARGOMAN_DEFINE_PROPERTY(_type,_name) \
  public: inline _type& _name()  {return this->m_##_name;} \
  inline void set##_name(_type _value)  {this->m_##_name = _value;} \
  protected: _type m_##_name;

#define TARGOMAN_CREATE_CONSTEXPR(_name) constexpr char _name[] = #_name

/** @brief A macro to define Enum in a semi-enhanced method in which Enums will reside in a namespace */
#define TARGOMAN_DEFINE_ENUM(_name, ...) \
    namespace _name{ enum Type { \
        __VA_ARGS__ \
      }; \
      inline int getCount(){ return TARGOMAN_MACRO_ARG_COUNT(__VA_ARGS__); } \
      static const char* Strings[] ={ \
          TARGOMAN_MACRO_FOREACH(TARGOMAN_M2STR_WITHCOMMA, __VA_ARGS__) \
      }; \
      static QStringList options(enuEnumPart::Type _part = enuEnumPart::Keys){ \
       (void)options; QStringList Options; \
       int EnumSize = getCount(); \
       qint64 LastID = 0;\
       for(int i=0; i< EnumSize; ++i) { \
          QString Option = Strings[i]; \
          switch(_part){ \
            case enuEnumPart::Keys: Option = Option.split('=').first();break; \
            case enuEnumPart::Values:  \
                 if(Option.contains('=')){ \
                    Option = Option.split('=').last(); \
                    bool Ok; LastID = Option.toLongLong(&Ok); \
                    if(!Ok) LastID = Option.toLatin1()[0]; \
                 } else {Option = QString("%1").arg(++LastID);};\
                 break;  \
            default: break;\
          }\
          Options.append( Option.trimmed() ); \
       }return Options; \
     } \
     static QString toStr(Type _value){ \
        (void)toStr; int EnumSize = getCount(); int LastID = 0; \
        for(int i=0; i< EnumSize; i++) { \
           QString Option = Strings[i]; \
           if(Option.contains('=')){ \
              Option = Option.split('=').last().trimmed(); \
              if(Option.startsWith('\'')) LastID = Option.mid(1).toLatin1().at(0); \
              else LastID = Option.toInt(); \
           } else ++LastID; \
           if (_value == LastID) return QString(Strings[i]).split('=').first().trimmed(); \
        } \
        return "Unknown"; \
     } \
     inline QString toStr(const QString& _value){return toStr(static_cast<Type>(static_cast<char>(_value.toLatin1()[0])));} \
     static Type toEnum(const QString& _value, bool _byValue = false){ \
          int EnumSize = getCount(); int LastID = 0; \
          for(int i=0; i< EnumSize; i++) { \
             QString Option = Strings[i]; \
             if(Option.contains('=')){ \
                Option = Option.split('=').last().trimmed(); \
                if(Option.startsWith('\'')) LastID = Option.mid(1).toLatin1().at(0); \
                else LastID = Option.toInt(); \
             } else ++LastID;\
             if((_byValue && _value.toInt() == LastID) || \
                (!_byValue && _value == QString(Strings[i]).split('=').first().trimmed())) \
                return static_cast<Type>(LastID); \
          }  \
          throw std::exception();\
      } \
      Q_DECLARE_FLAGS(Type##s, Type)\
      inline void dummy(){Q_UNUSED(toEnum);Q_UNUSED(options)} \
      Q_DECLARE_OPERATORS_FOR_FLAGS(_name::Type##s) \
    }

TARGOMAN_DEFINE_ENUM(enuEnumPart,
                     Full,
                     Keys,
                     Values
                     )
/**
 * @brief A macro to define Enum in an enhanced method in which Enums will reside in a namespace and can have string
          definitions
 *
 * Use below enumeration definition macro to enable string manipulation of enums.
 * !!! IMPORTANT !!!
 *     All the enumerations defined by this macro will have a default member named Unknown numbered -1.
 *     You must not set default values for enumerations. Enumeration will start from 0.
 */
#define TARGOMAN_DEFINE_ENHANCED_ENUM(_name, ...) \
    namespace _name { enum Type { Unknown = -1, \
        __VA_ARGS__ \
    }; static const char* Strings[] ={ \
        TARGOMAN_MACRO_FOREACH(TARGOMAN_M2STR_WITHCOMMA, __VA_ARGS__) \
    }; \
    inline int getCount() { return sizeof(Strings)/sizeof(char*); } \
    inline const char* toStr(Type _type) { \
      if (static_cast<int>(_type) <= Unknown || static_cast<int>(_type) > getCount()) return "Unknown";\
      return Strings[_type]; \
      toStr(Unknown);  \
    } \
    inline Type toEnum(const QString& _name, bool _byValue = false) { \
      if (_name.isEmpty() || _byValue) \
        return Unknown; \
      int EnumSize = getCount(); \
      for(int i=0; i< EnumSize; i++) { \
        if (_name.toLower() == QString(Strings[i]).toLower()) \
          return static_cast<Type>(i); \
      } \
      return Unknown; \
      toEnum(""); \
    } \
    inline QString toStr(const QString& _value){return toStr(static_cast<Type>(static_cast<char>(_value.toLatin1()[0])));}\
    inline QStringList options(){ \
      QStringList Options; \
      int EnumSize = getCount(); \
      for(int i=0; i< EnumSize; i++) \
          Options.append(Strings[i]); \
      return Options; \
    } \
    Q_DECLARE_FLAGS(Type##s, Type)\
    } \
    Q_DECLARE_OPERATORS_FOR_FLAGS(_name::Type##s)


/********************************************************************************************
 * Usefull Macros.
 ********************************************************************************************/
#define fastToLower(c)  ((c >= 'A' && c <= 'Z') ? c + 0x20 : c)
#define fastToUpper(c)  ((c >= 'a' && c <= 'z') ? c - 0x20 : c)
#define BIG_CONSTANT(x) (x##LLU)
#define MACRO_SAFE_COMMA ,
#define OUTPUT
#define INOUT

#define instanceGetter(_class) static _class& instance(){static _class* Instance = nullptr; return *(Q_LIKELY(Instance) ? Instance : (Instance = new _class));}
#define FORWARD_DECLARE_PRIVATE(_class) namespace Private{class _class##Private;}

// Unfortunately, some compilers will default to bool/int before it assumes
// QString.  For these cases we'll resort to this ugly MACRO.
#ifndef QSTR
#  ifdef USE_QSTRING_LITERAL
#    define QSTR(X) QStringLiteral(X)
#  else
#    define QSTR(X) X
#  endif
#endif

#ifndef QStringPair
    typedef std::pair<QString, QString> QStringPair;
#endif

#ifdef TARGOMAN_OMIT_ASSERTIONS
#  define TARGOMAN_DECLARE_ASSERT_MEMBER(X)
#  define TARGOMAN_INIT_ASSERT_MEMBER(X)
#else
#  define TARGOMAN_DECLARE_ASSERT_MEMBER(X) Assert< X > Assertion;
#  define TARGOMAN_INIT_ASSERT_MEMBER(X) Assertion( X ),
#endif

/********************************************************************************************
 * Library macros
 ********************************************************************************************/
//! Turn all private and protected members into PUBLIC members to help with
//! unit testing.
#ifdef TARGOMAN_ALL_MEMBERS_PUBLIC
  #define TARGOMAN_PRIVATE public
  #define TARGOMAN_PROTECTED public
#else
  #define TARGOMAN_PRIVATE private
  #define TARGOMAN_PROTECTED protected
#endif

#ifdef TARGOMAN_LIBRARY
#  if defined(TARGOMAN_EXPORT)
#    define TARGOMANSHARED_EXPORT Q_DECL_EXPORT
#  else
#    define TARGOMANSHARED_EXPORT Q_DECL_IMPORT
#  endif
#else
#  define TARGOMANSHARED_EXPORT
#endif

#endif /* TARGOMAN_COMMON_MACROS_H_ */

