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

#ifndef TARGOMAN_COMMON_MACROS_H_
#define TARGOMAN_COMMON_MACROS_H_

#include <string>
#include <QString>
#include <QStringList>
#include <cstring>
#include <functional>
#include <QDebug>
#include <optional>
#include "MacrosPrivate.hpp"

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

#define TARGOMAN_M2PASTER(_Arg1, _Arg2) _Arg1##_Arg2
#define TARGOMAN_M3PASTER(_Arg1, _Arg2, _Arg3) _Arg1##_Arg2##_Arg3
#define TARGOMAN_M4PASTER(_Arg1, _Arg2, _Arg3, _Arg4) _Arg1##_Arg2##_Arg3##_Arg4
#define TARGOMAN_M5PASTER(_Arg1, _Arg2, _Arg3, _Arg4, _Arg5) _Arg1##_Arg2##_Arg3##_Arg4##_Arg5
#define TARGOMAN_M6PASTER(_Arg1, _Arg2, _Arg3, _Arg4, _Arg5, _Arg6) _Arg1##_Arg2##_Arg3##_Arg4##_Arg5##_Arg6
#define TARGOMAN_M7PASTER(_Arg1, _Arg2, _Arg3, _Arg4, _Arg5, _Arg6, _Arg7) _Arg1##_Arg2##_Arg3##_Arg4##_Arg5##_Arg6##_Arg7

#define TARGOMAN_M2CONCAT(_Arg1, _Arg2) TARGOMAN_M2PASTER(_Arg1, _Arg2)
#define TARGOMAN_M3CONCAT(_Arg1, _Arg2, _Arg3) TARGOMAN_M3PASTER(_Arg1, _Arg2, _Arg3)
#define TARGOMAN_M4CONCAT(_Arg1, _Arg2, _Arg3, _Arg4) TARGOMAN_M4PASTER(_Arg1, _Arg2, _Arg3, _Arg4)
#define TARGOMAN_M5CONCAT(_Arg1, _Arg2, _Arg3, _Arg4, _Arg5) TARGOMAN_M5PASTER(_Arg1, _Arg2, _Arg3, _Arg4, _Arg5)
#define TARGOMAN_M6CONCAT(_Arg1, _Arg2, _Arg3, _Arg4, _Arg5, _Arg6) TARGOMAN_M6PASTER(_Arg1, _Arg2, _Arg3, _Arg4, _Arg5, _Arg6)
#define TARGOMAN_M7CONCAT(_Arg1, _Arg2, _Arg3, _Arg4, _Arg5, _Arg6, _Arg7) TARGOMAN_M7PASTER(_Arg1, _Arg2, _Arg3, _Arg4, _Arg5, _Arg6, _Arg7)

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

#define TARGOMANINTERNAL_MACRO_ARG_COUNT(...) \
    TARGOMAN_MACRO_ARG_COUNT_HELPER(__VA_ARGS__,\
    59,58,57,56,55,54,53,52,51,50,  \
    49,48,47,46,45,44,43,42,41,40,  \
    39,38,37,36,35,34,33,32,31,30,  \
    29,28,27,26,25,24,23,22,21,20,  \
    19,18,17,16,15,14,13,12,11,10,  \
    9,8,7,6,5,4,3,2,1,0)



#define TARGOMANINTERNAL_VA_ARGS_MULTI_OR_EMPTY_HELPER(...) TARGOMAN_MACRO_ARG_COUNT_HELPER(__VA_ARGS__, \
    EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, \
    EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, \
    EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, \
    EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, \
    EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, \
    EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, \
    MULTI)


#define TARGOMANINTERNAL_VA_ARGS_MULTI_OR_EMPTY(_0, _1, _2, _3) TARGOMANINTERNAL_VA_ARGS_MULTI_OR_EMPTY_HELPER(TARGOMAN_M5PASTER(TARGOMANINTERNAL_VA_ARGS_MULTI_OR_EMPTY_HELPER_CASE_, _0, _1, _2, _3))
#define TARGOMANINTERNAL_VA_ARGS_MULTI_OR_EMPTY_HELPER_CASE_MULTIMULTIMULTIEMPTY ,
#define TARGOMANINTERNAL_TRIGGER_PARENTHESIS_(...) ,
#define TARGOMAN_VA_ARGS_MULTI_OR_EMPTY(...) \
    TARGOMANINTERNAL_VA_ARGS_MULTI_OR_EMPTY( \
        /* test if there is just one argument, eventually an empty one */ \
        TARGOMANINTERNAL_VA_ARGS_MULTI_OR_EMPTY_HELPER(__VA_ARGS__), \
        /* test if _TRIGGER_PARENTHESIS_ together with the argument adds a comma */ \
        TARGOMANINTERNAL_VA_ARGS_MULTI_OR_EMPTY_HELPER(TARGOMANINTERNAL_TRIGGER_PARENTHESIS_ __VA_ARGS__), \
        /* test if the argument together with a parenthesis adds a comma */ \
        TARGOMANINTERNAL_VA_ARGS_MULTI_OR_EMPTY_HELPER(__VA_ARGS__ (/*empty*/)), \
        /* test if placing it between _TRIGGER_PARENTHESIS_ and the parenthesis adds a comma */ \
        TARGOMANINTERNAL_VA_ARGS_MULTI_OR_EMPTY_HELPER(TARGOMANINTERNAL_TRIGGER_PARENTHESIS_ __VA_ARGS__ (/*empty*/)) \
    )

#define TARGOMANINTERNAL_MACRO_ARG_COUNT_HELPER_EMPTY(...) 0
#define TARGOMANINTERNAL_MACRO_ARG_COUNT_HELPER_MULTI(...) TARGOMANINTERNAL_MACRO_ARG_COUNT(__VA_ARGS__)
#define TARGOMAN_MACRO_ARG_COUNT(...) \
    TARGOMAN_M2CONCAT(TARGOMANINTERNAL_MACRO_ARG_COUNT_HELPER_, TARGOMAN_VA_ARGS_MULTI_OR_EMPTY(__VA_ARGS__))(__VA_ARGS__)


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
        (void)toStr; int EnumSize = getCount(); int LastID = -1; \
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
          int EnumSize = getCount(); int LastID = -1; \
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

//------------------------------------------------------------
//------------------------------------------------------------
//------------------------------------------------------------
//------------------------------------------------------------
//------------------------------------------------------------

/*
 * moved form tapi private
 */
#define TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_MACRO_ARG_COUNT( \
    _01,_02,_03,_04,_05,_06,\
    _11,_12,_13,_14,_15,_16,\
    _21,_22,_23,_24,_25,_26,\
    _31,_32,_33,_34,_35,_36,\
    _41,_42,_43,_44,_45,_46,\
    _51,_52,_53,_54,_55,_56,\
    _61,_62,_63,_64,_65,_66,\
    _71,_72,_73,_74,_75,_76,\
    _81,_82,_83,_84,_85,_86,\
    _91,_92,_93,_94,_95,_96,\
    _A1,_A2,_A3,_A4,_A5,_A6,\
    _B1,_B2,_B3,_B4,_B5,_B6,\
    _C1,_C2,_C3,_C4,_C5,_C6,\
    _D1,_D2,_D3,_D4,_D5,_D6,\
    _E1,_E2,_E3,_E4,_E5,_E6,\
    _F1,_F2,_F3,_F4,_F5,_F6,\
    _G1,_G2,_G3,_G4,_G5,_G6,\
    _H1,_H2,_H3,_H4,_H5,_H6,\
    _I1,_I2,_I3,_I4,_I5,_I6,\
    _J1,_J2,_J3,_J4,_J5,_J6,\
    _K1,_K2,_K3,_K4,_K5, N,...) N


#define TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_MACRO_SELECTOR(_fn,...) TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_MACRO_ARG_COUNT(__VA_ARGS__,\
    _fn##FAIL01,_fn##FAIL02,_fn##FAIL03,_fn##FAIL04,_fn##FAIL05,_fn##20,  \
    _fn##FAIL11,_fn##FAIL12,_fn##FAIL13,_fn##FAIL14,_fn##FAIL15,_fn##19,  \
    _fn##FAIL21,_fn##FAIL22,_fn##FAIL23,_fn##FAIL24,_fn##FAIL25,_fn##18,  \
    _fn##FAIL31,_fn##FAIL32,_fn##FAIL33,_fn##FAIL34,_fn##FAIL35,_fn##17,  \
    _fn##FAIL41,_fn##FAIL42,_fn##FAIL43,_fn##FAIL44,_fn##FAIL45,_fn##16,  \
    _fn##FAIL51,_fn##FAIL52,_fn##FAIL53,_fn##FAIL54,_fn##FAIL55,_fn##15,  \
    _fn##FAIL61,_fn##FAIL62,_fn##FAIL63,_fn##FAIL64,_fn##FAIL65,_fn##14,  \
    _fn##FAIL71,_fn##FAIL72,_fn##FAIL73,_fn##FAIL74,_fn##FAIL75,_fn##13,  \
    _fn##FAIL81,_fn##FAIL82,_fn##FAIL83,_fn##FAIL84,_fn##FAIL85,_fn##12,  \
    _fn##FAIL91,_fn##FAIL92,_fn##FAIL93,_fn##FAIL94,_fn##FAIL95,_fn##11,  \
    _fn##FAILA1,_fn##FAILA2,_fn##FAILA3,_fn##FAILA4,_fn##FAILA5,_fn##10,  \
    _fn##FAILB1,_fn##FAILB2,_fn##FAILB3,_fn##FAILB4,_fn##FAILB5,_fn##9,   \
    _fn##FAILC1,_fn##FAILC2,_fn##FAILC3,_fn##FAILC4,_fn##FAILC5,_fn##8,   \
    _fn##FAILD1,_fn##FAILD2,_fn##FAILD3,_fn##FAILD4,_fn##FAILD5,_fn##7,   \
    _fn##FAILE1,_fn##FAILE2,_fn##FAILE3,_fn##FAILE4,_fn##FAILE5,_fn##6,   \
    _fn##FAILF1,_fn##FAILF2,_fn##FAILF3,_fn##FAILF4,_fn##FAILF5,_fn##5,   \
    _fn##FAILG1,_fn##FAILG2,_fn##FAILG3,_fn##FAILG4,_fn##FAILG5,_fn##4,   \
    _fn##FAILH1,_fn##FAILH2,_fn##FAILH3,_fn##FAILH4,_fn##FAILH5,_fn##3,   \
    _fn##FAILI1,_fn##FAILI2,_fn##FAILI3,_fn##FAILI4,_fn##FAILI5,_fn##2,   \
    _fn##FAILJ1,_fn##FAILJ2,_fn##FAILJ3,_fn##FAILJ4,_fn##FAILJ5,_fn##1,   \
    _fn##FAILK1,_fn##FAILK2,_fn##FAILK3,_fn##FAILK4,_fn##FAILK5,None)

#define TARGOMAN_HELEPER_VARIANTSTRUCT_PARAMS1(t, n, d, i, to, fr)       t n;
#define TARGOMAN_HELEPER_VARIANTSTRUCT_PARAMS2(t, n, d, i, to, fr, ...)  t n; TARGOMAN_HELEPER_VARIANTSTRUCT_PARAMS1(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_PARAMS3(t, n, d, i, to, fr, ...)  t n; TARGOMAN_HELEPER_VARIANTSTRUCT_PARAMS2(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_PARAMS4(t, n, d, i, to, fr, ...)  t n; TARGOMAN_HELEPER_VARIANTSTRUCT_PARAMS3(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_PARAMS5(t, n, d, i, to, fr, ...)  t n; TARGOMAN_HELEPER_VARIANTSTRUCT_PARAMS4(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_PARAMS6(t, n, d, i, to, fr, ...)  t n; TARGOMAN_HELEPER_VARIANTSTRUCT_PARAMS5(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_PARAMS7(t, n, d, i, to, fr, ...)  t n; TARGOMAN_HELEPER_VARIANTSTRUCT_PARAMS6(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_PARAMS8(t, n, d, i, to, fr, ...)  t n; TARGOMAN_HELEPER_VARIANTSTRUCT_PARAMS7(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_PARAMS9(t, n, d, i, to, fr, ...)  t n; TARGOMAN_HELEPER_VARIANTSTRUCT_PARAMS8(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_PARAMS10(t, n, d, i, to, fr, ...) t n; TARGOMAN_HELEPER_VARIANTSTRUCT_PARAMS9(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_PARAMS11(t, n, d, i, to, fr, ...) t n; TARGOMAN_HELEPER_VARIANTSTRUCT_PARAMS10(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_PARAMS12(t, n, d, i, to, fr, ...) t n; TARGOMAN_HELEPER_VARIANTSTRUCT_PARAMS11(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_PARAMS13(t, n, d, i, to, fr, ...) t n; TARGOMAN_HELEPER_VARIANTSTRUCT_PARAMS12(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_PARAMS14(t, n, d, i, to, fr, ...) t n; TARGOMAN_HELEPER_VARIANTSTRUCT_PARAMS13(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_PARAMS15(t, n, d, i, to, fr, ...) t n; TARGOMAN_HELEPER_VARIANTSTRUCT_PARAMS14(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_PARAMS16(t, n, d, i, to, fr, ...) t n; TARGOMAN_HELEPER_VARIANTSTRUCT_PARAMS15(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_PARAMS17(t, n, d, i, to, fr, ...) t n; TARGOMAN_HELEPER_VARIANTSTRUCT_PARAMS16(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_PARAMS18(t, n, d, i, to, fr, ...) t n; TARGOMAN_HELEPER_VARIANTSTRUCT_PARAMS17(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_PARAMS19(t, n, d, i, to, fr, ...) t n; TARGOMAN_HELEPER_VARIANTSTRUCT_PARAMS18(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_PARAMS20(t, n, d, i, to, fr, ...) t n; TARGOMAN_HELEPER_VARIANTSTRUCT_PARAMS19(__VA_ARGS__)

#define TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INPUT1(t,  n, d, i, to, fr)      const t& _##n=d
#define TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INPUT2(t,  n, d, i, to, fr, ...) const t& _##n=d, TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INPUT1(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INPUT3(t,  n, d, i, to, fr, ...) const t& _##n=d, TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INPUT2(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INPUT4(t,  n, d, i, to, fr, ...) const t& _##n=d, TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INPUT3(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INPUT5(t,  n, d, i, to, fr, ...) const t& _##n=d, TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INPUT4(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INPUT6(t,  n, d, i, to, fr, ...) const t& _##n=d, TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INPUT5(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INPUT7(t,  n, d, i, to, fr, ...) const t& _##n=d, TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INPUT6(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INPUT8(t,  n, d, i, to, fr, ...) const t& _##n=d, TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INPUT7(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INPUT9(t,  n, d, i, to, fr, ...) const t& _##n=d, TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INPUT8(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INPUT10(t, n, d, i, to, fr, ...) const t& _##n=d, TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INPUT9(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INPUT11(t, n, d, i, to, fr, ...) const t& _##n=d, TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INPUT10(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INPUT12(t, n, d, i, to, fr, ...) const t& _##n=d, TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INPUT11(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INPUT13(t, n, d, i, to, fr, ...) const t& _##n=d, TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INPUT12(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INPUT14(t, n, d, i, to, fr, ...) const t& _##n=d, TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INPUT13(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INPUT15(t, n, d, i, to, fr, ...) const t& _##n=d, TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INPUT14(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INPUT16(t, n, d, i, to, fr, ...) const t& _##n=d, TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INPUT15(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INPUT17(t, n, d, i, to, fr, ...) const t& _##n=d, TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INPUT16(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INPUT18(t, n, d, i, to, fr, ...) const t& _##n=d, TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INPUT17(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INPUT19(t, n, d, i, to, fr, ...) const t& _##n=d, TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INPUT18(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INPUT20(t, n, d, i, to, fr, ...) const t& _##n=d, TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INPUT19(__VA_ARGS__)

#define TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INIT1(t, n,d,i,to,fr)      n(_##n)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INIT2(t, n,d,i,to,fr, ...) n(_##n), TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INIT1(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INIT3(t, n,d,i,to,fr, ...) n(_##n), TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INIT2(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INIT4(t, n,d,i,to,fr, ...) n(_##n), TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INIT3(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INIT5(t, n,d,i,to,fr, ...) n(_##n), TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INIT4(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INIT6(t, n,d,i,to,fr, ...) n(_##n), TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INIT5(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INIT7(t, n,d,i,to,fr, ...) n(_##n), TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INIT6(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INIT8(t, n,d,i,to,fr, ...) n(_##n), TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INIT7(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INIT9(t, n,d,i,to,fr, ...) n(_##n), TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INIT8(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INIT10(t,n,d,i,to,fr, ...) n(_##n), TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INIT9(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INIT11(t,n,d,i,to,fr, ...) n(_##n), TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INIT10(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INIT12(t,n,d,i,to,fr, ...) n(_##n), TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INIT11(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INIT13(t,n,d,i,to,fr, ...) n(_##n), TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INIT12(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INIT14(t,n,d,i,to,fr, ...) n(_##n), TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INIT13(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INIT15(t,n,d,i,to,fr, ...) n(_##n), TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INIT14(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INIT16(t,n,d,i,to,fr, ...) n(_##n), TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INIT15(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INIT17(t,n,d,i,to,fr, ...) n(_##n), TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INIT16(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INIT18(t,n,d,i,to,fr, ...) n(_##n), TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INIT17(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INIT19(t,n,d,i,to,fr, ...) n(_##n), TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INIT18(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INIT20(t,n,d,i,to,fr, ...) n(_##n), TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INIT19(__VA_ARGS__)

//extern QString toCammel(const QString& _name);
inline QString toCammel(const QString& _name)
{
    return _name.mid(0,1).toLower() + _name.mid(1);
}

#define TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_TOJSON_METHOD(n, i, to) \
    if ([](auto v)->bool{return i;}(n)) Obj[toCammel(#n)]=[](auto v)->QJsonValue{return to;}(n);
#define TARGOMAN_HELEPER_VARIANTSTRUCT_TOJSON1(t, n,d,i,to,fr)     TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_TOJSON_METHOD(n, i, to);
#define TARGOMAN_HELEPER_VARIANTSTRUCT_TOJSON2(t, n,d,i,to,fr,...) TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_TOJSON_METHOD(n, i, to); TARGOMAN_HELEPER_VARIANTSTRUCT_TOJSON1(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_TOJSON3(t, n,d,i,to,fr,...) TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_TOJSON_METHOD(n, i, to); TARGOMAN_HELEPER_VARIANTSTRUCT_TOJSON2(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_TOJSON4(t, n,d,i,to,fr,...) TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_TOJSON_METHOD(n, i, to); TARGOMAN_HELEPER_VARIANTSTRUCT_TOJSON3(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_TOJSON5(t, n,d,i,to,fr,...) TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_TOJSON_METHOD(n, i, to); TARGOMAN_HELEPER_VARIANTSTRUCT_TOJSON4(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_TOJSON6(t, n,d,i,to,fr,...) TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_TOJSON_METHOD(n, i, to); TARGOMAN_HELEPER_VARIANTSTRUCT_TOJSON5(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_TOJSON7(t, n,d,i,to,fr,...) TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_TOJSON_METHOD(n, i, to); TARGOMAN_HELEPER_VARIANTSTRUCT_TOJSON6(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_TOJSON8(t, n,d,i,to,fr,...) TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_TOJSON_METHOD(n, i, to); TARGOMAN_HELEPER_VARIANTSTRUCT_TOJSON7(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_TOJSON9(t, n,d,i,to,fr,...) TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_TOJSON_METHOD(n, i, to); TARGOMAN_HELEPER_VARIANTSTRUCT_TOJSON8(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_TOJSON10(t,n,d,i,to,fr,...) TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_TOJSON_METHOD(n, i, to); TARGOMAN_HELEPER_VARIANTSTRUCT_TOJSON9(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_TOJSON11(t,n,d,i,to,fr,...) TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_TOJSON_METHOD(n, i, to); TARGOMAN_HELEPER_VARIANTSTRUCT_TOJSON10(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_TOJSON12(t,n,d,i,to,fr,...) TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_TOJSON_METHOD(n, i, to); TARGOMAN_HELEPER_VARIANTSTRUCT_TOJSON11(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_TOJSON13(t,n,d,i,to,fr,...) TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_TOJSON_METHOD(n, i, to); TARGOMAN_HELEPER_VARIANTSTRUCT_TOJSON12(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_TOJSON14(t,n,d,i,to,fr,...) TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_TOJSON_METHOD(n, i, to); TARGOMAN_HELEPER_VARIANTSTRUCT_TOJSON13(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_TOJSON15(t,n,d,i,to,fr,...) TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_TOJSON_METHOD(n, i, to); TARGOMAN_HELEPER_VARIANTSTRUCT_TOJSON14(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_TOJSON16(t,n,d,i,to,fr,...) TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_TOJSON_METHOD(n, i, to); TARGOMAN_HELEPER_VARIANTSTRUCT_TOJSON15(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_TOJSON17(t,n,d,i,to,fr,...) TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_TOJSON_METHOD(n, i, to); TARGOMAN_HELEPER_VARIANTSTRUCT_TOJSON16(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_TOJSON18(t,n,d,i,to,fr,...) TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_TOJSON_METHOD(n, i, to); TARGOMAN_HELEPER_VARIANTSTRUCT_TOJSON17(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_TOJSON19(t,n,d,i,to,fr,...) TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_TOJSON_METHOD(n, i, to); TARGOMAN_HELEPER_VARIANTSTRUCT_TOJSON18(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_TOJSON20(t,n,d,i,to,fr,...) TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_TOJSON_METHOD(n, i, to); TARGOMAN_HELEPER_VARIANTSTRUCT_TOJSON19(__VA_ARGS__)

#define TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_FROMJSON_METHOD(t, n, d, fr) \
    n=_obj.contains(toCammel(#n))?[](auto v)->t{return fr;}(_obj.value(toCammel(#n))):d
#define TARGOMAN_HELEPER_VARIANTSTRUCT_FROMJSON1(t, n,d,i,to,fr)     TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_FROMJSON_METHOD(t, n, d, fr);
#define TARGOMAN_HELEPER_VARIANTSTRUCT_FROMJSON2(t, n,d,i,to,fr,...) TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_FROMJSON_METHOD(t, n, d, fr); TARGOMAN_HELEPER_VARIANTSTRUCT_FROMJSON1(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_FROMJSON3(t, n,d,i,to,fr,...) TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_FROMJSON_METHOD(t, n, d, fr); TARGOMAN_HELEPER_VARIANTSTRUCT_FROMJSON2(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_FROMJSON4(t, n,d,i,to,fr,...) TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_FROMJSON_METHOD(t, n, d, fr); TARGOMAN_HELEPER_VARIANTSTRUCT_FROMJSON3(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_FROMJSON5(t, n,d,i,to,fr,...) TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_FROMJSON_METHOD(t, n, d, fr); TARGOMAN_HELEPER_VARIANTSTRUCT_FROMJSON4(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_FROMJSON6(t, n,d,i,to,fr,...) TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_FROMJSON_METHOD(t, n, d, fr); TARGOMAN_HELEPER_VARIANTSTRUCT_FROMJSON5(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_FROMJSON7(t, n,d,i,to,fr,...) TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_FROMJSON_METHOD(t, n, d, fr); TARGOMAN_HELEPER_VARIANTSTRUCT_FROMJSON6(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_FROMJSON8(t, n,d,i,to,fr,...) TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_FROMJSON_METHOD(t, n, d, fr); TARGOMAN_HELEPER_VARIANTSTRUCT_FROMJSON7(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_FROMJSON9(t, n,d,i,to,fr,...) TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_FROMJSON_METHOD(t, n, d, fr); TARGOMAN_HELEPER_VARIANTSTRUCT_FROMJSON8(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_FROMJSON10(t,n,d,i,to,fr,...) TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_FROMJSON_METHOD(t, n, d, fr); TARGOMAN_HELEPER_VARIANTSTRUCT_FROMJSON9(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_FROMJSON11(t,n,d,i,to,fr,...) TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_FROMJSON_METHOD(t, n, d, fr); TARGOMAN_HELEPER_VARIANTSTRUCT_FROMJSON10(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_FROMJSON12(t,n,d,i,to,fr,...) TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_FROMJSON_METHOD(t, n, d, fr); TARGOMAN_HELEPER_VARIANTSTRUCT_FROMJSON11(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_FROMJSON13(t,n,d,i,to,fr,...) TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_FROMJSON_METHOD(t, n, d, fr); TARGOMAN_HELEPER_VARIANTSTRUCT_FROMJSON12(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_FROMJSON14(t,n,d,i,to,fr,...) TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_FROMJSON_METHOD(t, n, d, fr); TARGOMAN_HELEPER_VARIANTSTRUCT_FROMJSON13(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_FROMJSON15(t,n,d,i,to,fr,...) TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_FROMJSON_METHOD(t, n, d, fr); TARGOMAN_HELEPER_VARIANTSTRUCT_FROMJSON14(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_FROMJSON16(t,n,d,i,to,fr,...) TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_FROMJSON_METHOD(t, n, d, fr); TARGOMAN_HELEPER_VARIANTSTRUCT_FROMJSON15(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_FROMJSON17(t,n,d,i,to,fr,...) TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_FROMJSON_METHOD(t, n, d, fr); TARGOMAN_HELEPER_VARIANTSTRUCT_FROMJSON16(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_FROMJSON18(t,n,d,i,to,fr,...) TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_FROMJSON_METHOD(t, n, d, fr); TARGOMAN_HELEPER_VARIANTSTRUCT_FROMJSON17(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_FROMJSON19(t,n,d,i,to,fr,...) TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_FROMJSON_METHOD(t, n, d, fr); TARGOMAN_HELEPER_VARIANTSTRUCT_FROMJSON18(__VA_ARGS__)
#define TARGOMAN_HELEPER_VARIANTSTRUCT_FROMJSON20(t,n,d,i,to,fr,...) TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_FROMJSON_METHOD(t, n, d, fr); TARGOMAN_HELEPER_VARIANTSTRUCT_FROMJSON19(__VA_ARGS__)

#define TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_PARAMS(...) \
    TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_MACRO_SELECTOR(TARGOMAN_HELEPER_VARIANTSTRUCT_PARAMS, __VA_ARGS__)(__VA_ARGS__)

#define TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_CONS_INPUT(...) \
    TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_MACRO_SELECTOR(TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INPUT, __VA_ARGS__)(__VA_ARGS__)

#define TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_CONS_INIT(...) \
    TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_MACRO_SELECTOR(TARGOMAN_HELEPER_VARIANTSTRUCT_CONS_INIT, __VA_ARGS__)(__VA_ARGS__)

#define TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_TOJSON(...) \
    TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_MACRO_SELECTOR(TARGOMAN_HELEPER_VARIANTSTRUCT_TOJSON, __VA_ARGS__)(__VA_ARGS__)

#define TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_FROMJSON(...) \
    TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_MACRO_SELECTOR( TARGOMAN_HELEPER_VARIANTSTRUCT_FROMJSON, __VA_ARGS__)(__VA_ARGS__)

/*
 * moved form tapi private
 */
//------------------------------------------------------------
#define INTERNAL_TARGOMAN_ADD_TYPE_SPECIALFROMVARIANT(_namespace, _baseType, _typeName, _fromVariant) \
namespace _namespace { \
    class _typeName : public _baseType { \
    public: \
        _typeName() {} \
        _typeName(const _baseType& _other):_baseType(_other) {} \
        void customFromVariant (const QVariant& _value) { _fromVariant; } \
    }; \
} \
namespace COMMON { \
    inline void setFromVariant(_namespace::_typeName& _storage, const QVariant& _val) { \
        _storage.customFromVariant(_val); \
    } \
    inline void setFromVariant(NULLABLE_TYPE(_namespace::_typeName)& _storage, const QVariant& _val) { \
        if (_val.isValid() && _val.isNull() == false) { \
            _namespace::_typeName var; \
            var.customFromVariant(_val); \
            NULLABLE_SET(_storage, var); \
        } \
        else \
            NULLABLE_RESET(_storage); \
    } \
}

/*
 * moved form tapi private
 */
//------------------------------------------------------------
#define INTERNAL_C2DBL(v) static_cast<double>(v)

#define INTERNAL_V2DBL(v) v.toDouble()
//#define INTERNAL_V2double(v) INTERNAL_V2DBL(v)

#define INTERNAL_V2U8(v) static_cast<quint8>(v.toDouble())
#define INTERNAL_V2uint8(v) INTERNAL_V2U8(v)
#define INTERNAL_V2U16(v) static_cast<quint16>(v.toDouble())
#define INTERNAL_V2uint16(v) INTERNAL_V2U16(v)
#define INTERNAL_V2U32(v) static_cast<quint32>(v.toDouble())
#define INTERNAL_V2uint32(v) INTERNAL_V2U32(v)
#define INTERNAL_V2U64(v) static_cast<quint64>(v.toDouble())
#define INTERNAL_V2uint64(v) INTERNAL_V2U64(v)

#define INTERNAL_V2S8(v) static_cast<qint8>(v.toDouble())
#define INTERNAL_V2int8(v) INTERNAL_V2S8(v)
#define INTERNAL_V2S16(v) static_cast<qint16>(v.toDouble())
#define INTERNAL_V2int16(v) INTERNAL_V2S16(v)
#define INTERNAL_V2S32(v) static_cast<qint32>(v.toDouble())
#define INTERNAL_V2int32(v) INTERNAL_V2S32(v)
#define INTERNAL_V2S64(v) static_cast<qint64>(v.toDouble())
#define INTERNAL_V2int64(v) INTERNAL_V2S64(v)

#define INTERNAL_N2J(_value)       [](auto v) { return /*TA PI*/COMMON::toJsonValue(v); } (_value)
#define INTERNAL_N2DBL(_value)     INTERNAL_NULLABLE_FROM_JSONVALUE_TO_TYPE(double,  _value)
#define INTERNAL_N2int8(_value)    INTERNAL_NULLABLE_FROM_JSONVALUE_TO_TYPE(qint8,   _value)
#define INTERNAL_N2int16(_value)   INTERNAL_NULLABLE_FROM_JSONVALUE_TO_TYPE(qint16,  _value)
#define INTERNAL_N2int32(_value)   INTERNAL_NULLABLE_FROM_JSONVALUE_TO_TYPE(qint32,  _value)
#define INTERNAL_N2int64(_value)   INTERNAL_NULLABLE_FROM_JSONVALUE_TO_TYPE(qint64,  _value)
#define INTERNAL_N2uint8(_value)   INTERNAL_NULLABLE_FROM_JSONVALUE_TO_TYPE(quint8,  _value)
#define INTERNAL_N2uint16(_value)  INTERNAL_NULLABLE_FROM_JSONVALUE_TO_TYPE(quint16, _value)
#define INTERNAL_N2uint32(_value)  INTERNAL_NULLABLE_FROM_JSONVALUE_TO_TYPE(quint32, _value)
#define INTERNAL_N2uint64(_value)  INTERNAL_NULLABLE_FROM_JSONVALUE_TO_TYPE(quint64, _value)

//------------------------------------------------------------
//------------------------------------------------------------
//------------------------------------------------------------
#define INTERNAL_SF_STRUCT_1(_validator) _validator
#define INTERNAL_SF_STRUCT_0()           INTERNAL_SF_STRUCT_1(v)

#define INTERNAL_SF_STRUCT(_type, _name, ...) \
    _type, \
    _name, \
    _type(), \
    TARGOMAN_M2CONCAT(INTERNAL_SF_STRUCT_, TARGOMAN_MACRO_ARG_COUNT(__VA_ARGS__))(__VA_ARGS__), \
    v.toJson(), \
    _type().fromJson(v.toObject())

//------------------------------------------------------------
#define INTERNAL_SF_STRING_2(_def, _validator) _def, _validator
#define INTERNAL_SF_STRING_1(_def)             INTERNAL_SF_STRING_2(_def, v.size())
#define INTERNAL_SF_STRING_0()                 INTERNAL_SF_STRING_1(QString())

//------------------------------------------------------------
#define INTERNAL_SF_INTEGRAL_2(_def, _validator) _def, _validator
#define INTERNAL_SF_INTEGRAL_1(_def)             INTERNAL_SF_INTEGRAL_2(_def, v==v)
#define INTERNAL_SF_INTEGRAL_0()                 INTERNAL_SF_INTEGRAL_1(0)

#define INTERNAL_SF_NULLABLE_INTEGRAL_2(_def, _validator) _def, _validator
#define INTERNAL_SF_NULLABLE_INTEGRAL_1(_def)             INTERNAL_SF_NULLABLE_INTEGRAL_2(_def, v==v)
#define INTERNAL_SF_NULLABLE_INTEGRAL_0()                 INTERNAL_SF_NULLABLE_INTEGRAL_1(NULLABLE_NULL_VALUE)

//------------------------------------------------------------
#define INTERNAL_SF(_type, _name, _typeGroup, _fromVariant, _toVariant, ...) \
    _type, \
    _name, \
    TARGOMAN_M2CONCAT(INTERNAL_SF_ ## _typeGroup ## _, TARGOMAN_MACRO_ARG_COUNT(__VA_ARGS__))(__VA_ARGS__), \
    _fromVariant, \
    _toVariant

//------------------------------------------------------------
//------------------------------------------------------------
//------------------------------------------------------------
#define INTERNAL_NULLABLE_FROM_JSONVALUE_TO_TYPE(_type, _value) \
    [](auto v)->NULLABLE_TYPE(_type) { \
        if (v.isNull()) \
            return NULLABLE_NULL_VALUE; \
        auto Storage = NULLABLE_TYPE(_type)(); \
        Storage = v.toDouble(); \
        return Storage; \
    } (_value)
//return v.toDouble();
//        qDebug() << "INTERNAL_NULLABLE_FROM_JSONVALUE_TO_TYPE" << #_type << v;
//        qDebug() << "INTERNAL_ (1)" << v.toDouble();

//------------------------------------------------------------
#define INTERNAL_TARGOMAN_DECLARE_METATYPE_ENUM(_namespace, _enum) \
    TARGOMAN_DECLARE_METATYPE(_namespace::_enum::Type); \
namespace /*TA PI*/COMMON { \
    inline void setFromVariant(_namespace::_enum::Type& _storage, const QVariant& _val) { \
        _storage = _namespace::_enum::toEnum(_val.toString()); \
    } \
    inline void setFromVariant(NULLABLE_TYPE(_namespace::_enum::Type)& _storage, const QVariant& _val) { \
        if (_val.isValid() && _val.isNull() == false) \
            _storage = _namespace::_enum::toEnum(_val.toString()); \
    } \
}

/*
 * moved from tapi
 */
#define TARGOMAN_DISABLE_COPY(Class) \
    Q_DISABLE_COPY(Class)
//    Class &operator=(const Class) Q_DECL_EQ_DELETE;

#define NULLABLE_QSP_M2STR_PREFIX "std::optional<"
#define NULLABLE_QSP_M2STR_POSTFIX ">"
#define NULLABLE_UNDERLAYER_CLASS_NAME "std::optional"
#define NULLABLE_TYPE(_type) std::optional<_type>
#define NULLABLE_VAR(_type, _name) NULLABLE_TYPE(_type) _name
#define NULLABLE_GET(_value) (_value.has_value() ? *_value : QVariant())
#define NULLABLE_GET_OR_DEFAULT(_value, _def) (_value.has_value() ? *_value : _def)
#define NULLABLE_SET(_var, _value) (_var = _value)
#define NULLABLE_NULL_VALUE std::nullopt
#define NULLABLE_RESET(_var) (_var = NULLABLE_NULL_VALUE)
#define NULLABLE_IS_NULL(_nullable) (_nullable.has_value() == false)
#define NULLABLE_HAS_VALUE(_nullable) _nullable.has_value()
#define NULLABLE_INSTANTIATE_FROM_QVARIANT(_type, _val) (_val.isNull() ? NULLABLE_TYPE(_type)() : NULLABLE_TYPE(_type)(_val.template value<_type>()))

/*
 * moved from tapi
 */

//------------------------------------------------------------
#define TARGOMAN_ADD_TYPE_SPECIALFROMVARIANT(_namespace, _baseType, _typeName, _fromVariant) \
    INTERNAL_TARGOMAN_ADD_TYPE_SPECIALFROMVARIANT(_namespace, _baseType, _typeName, _fromVariant)

#define TARGOMAN_ADD_TYPE(_namespace, _baseType, _typeName) \
    TARGOMAN_ADD_TYPE_SPECIALFROMVARIANT(_namespace, _baseType, _typeName, this->fromVariant(_value) )

#define TARGOMAN_ADD_TYPE_STRING(_namespace, _typeName) \
    TARGOMAN_ADD_TYPE_SPECIALFROMVARIANT(_namespace, QString, _typeName, _value.toString() )

//------------------------------------------------------------
#define TARGOMAN_DECLARE_METATYPE(_type) \
    Q_DECLARE_METATYPE(_type) \
    Q_DECLARE_METATYPE(NULLABLE_TYPE(_type))

#define TARGOMAN_DECLARE_METATYPE_ENUM(_namespace, _enum) \
    INTERNAL_TARGOMAN_DECLARE_METATYPE_ENUM(_namespace, _enum)

/*
 * moved from tapi
 */

//------------------------------------------------------------
#define SF_Generic(_type, _name, _def, _validator, _fromVariant, _toVariant) _type, _name, _def, _validator, _fromVariant, _toVariant
#define SF_Enum(_type, _name, _def)     _type::Type, _name, _def, v, v, static_cast<_type::Type>(v.toString().toLatin1().constData()[0])
#define SF_Struct(_type, _name, ...)    INTERNAL_SF_STRUCT(_type, _name, __VA_ARGS__)

//------------------------------------------------- _type,                  _name, _typeGroup,        _fromVariant,      _toVariant,           _def, _validator
#define SF_String(_name, _type, ...)    INTERNAL_SF(_type,                  _name, STRING,            v,                 v.toString(),         __VA_ARGS__)
#define SF_QString(_name, ...)          SF_String(_name,    QString,      __VA_ARGS__)

#define SF_quint8(_name, ...)           INTERNAL_SF(quint8,                 _name, INTEGRAL,          INTERNAL_C2DBL(v), INTERNAL_V2uint8(v),  __VA_ARGS__)
#define SF_NULLABLE_quint8(_name, ...)  INTERNAL_SF(NULLABLE_TYPE(quint8),  _name, NULLABLE_INTEGRAL, INTERNAL_N2J(v),   INTERNAL_N2uint8(v),  __VA_ARGS__)
#define SF_quint16(_name, ...)          INTERNAL_SF(quint16,                _name, INTEGRAL,          INTERNAL_C2DBL(v), INTERNAL_V2uint16(v), __VA_ARGS__)
#define SF_NULLABLE_quint16(_name, ...) INTERNAL_SF(NULLABLE_TYPE(quint16), _name, NULLABLE_INTEGRAL, INTERNAL_N2J(v),   INTERNAL_N2uint16(v), __VA_ARGS__)
#define SF_quint32(_name, ...)          INTERNAL_SF(quint32,                _name, INTEGRAL,          INTERNAL_C2DBL(v), INTERNAL_V2uint32(v), __VA_ARGS__)
#define SF_NULLABLE_quint32(_name, ...) INTERNAL_SF(NULLABLE_TYPE(quint32), _name, NULLABLE_INTEGRAL, INTERNAL_N2J(v),   INTERNAL_N2uint32(v), __VA_ARGS__)
#define SF_quint64(_name, ...)          INTERNAL_SF(quint64,                _name, INTEGRAL,          INTERNAL_C2DBL(v), INTERNAL_V2uint64(v), __VA_ARGS__)
#define SF_NULLABLE_quint64(_name, ...) INTERNAL_SF(NULLABLE_TYPE(quint64), _name, NULLABLE_INTEGRAL, INTERNAL_N2J(v),   INTERNAL_N2uint64(v), __VA_ARGS__)
#define SF_qreal(_name, ...)            INTERNAL_SF(qreal,                  _name, INTEGRAL,          INTERNAL_C2DBL(v), INTERNAL_V2DBL(v),    __VA_ARGS__)
#define SF_NULLABLE_qreal(_name, ...)   INTERNAL_SF(NULLABLE_TYPE(qreal),   _name, NULLABLE_INTEGRAL, INTERNAL_N2J(v),   INTERNAL_N2DBL(v),    __VA_ARGS__)

//------------------------------------------------------------
#define TARGOMAN_DEFINE_VARIANT_ENABLED_STRUCT(_name, ...) struct _name { \
    TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_PARAMS(__VA_ARGS__) \
    _name(TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_CONS_INPUT(__VA_ARGS__)) : \
        TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_CONS_INIT(__VA_ARGS__) \
    {} \
    QJsonObject toJson() const { \
        QJsonObject Obj; \
        TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_TOJSON(__VA_ARGS__); \
        return Obj; \
    } \
    _name& fromJson(const QJsonObject& _obj) { \
        TARGOMAN_HELEPER_DEFINE_VARIANT_STRUCT_FROMJSON(__VA_ARGS__); \
        return *this; \
    } \
};

#define SET_FIELD_FROM_VARIANT_MAP(_varName, _infoRec, _table, _tableFieldName) \
    QT_TRY { \
        /*TA PI*/COMMON::setFromVariant(_varName, _infoRec.value(_table::_tableFieldName)); \
    } \
    QT_CATCH (const std::exception &e) { \
        qDebug() << "fieldName:" << #_tableFieldName << e.what(); \
        QT_RETHROW; \
    }

#define C2DBL(v) INTERNAL_C2DBL(v)
#define C2U64(v) INTERNAL_C2DBL(v)
#define V2U64(v) INTERNAL_V2U64(v)
#define C2U32(v) C2DBL(v)
#define V2U32(v) INTERNAL_V2U32(v)

//------------------------------------------------------------
#define N2J(_value)    [](auto v) { return toJsonValue(v); } (_value)
#define N2S8(_value)   INTERNAL_N2int8(_value)
#define N2S16(_value)  INTERNAL_N2int16(_value)
#define N2S32(_value)  INTERNAL_N2int32(_value)
#define N2S64(_value)  INTERNAL_N2int64(_value)
#define N2U8(_value)   INTERNAL_N2uint8(_value)
#define N2U16(_value)  INTERNAL_N2uint16(_value)
#define N2U32(_value)  INTERNAL_N2uint32(_value)
#define N2U64(_value)  INTERNAL_N2uint64(_value)
#define N2DBL(_value)  INTERNAL_NULLABLE_FROM_JSONVALUE_TO_TYPE(double,  _value)
#define QSP_M2STR(_type) NULLABLE_QSP_M2STR_PREFIX #_type NULLABLE_QSP_M2STR_POSTFIX

#endif /* TARGOMAN_COMMON_MACROS_H_ */
