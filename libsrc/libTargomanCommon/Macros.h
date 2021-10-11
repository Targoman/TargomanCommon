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

//78-135: moved to private

// Following definition is used in complex templates where a template is instantiating other templates which needs comma
#define TARGOMAN_VIRTUAL_COMMA() ,

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
#define TARGOMAN_MACRO_ARG_COUNT(...) \
    TARGOMAN_M2CONCAT(TARGOMANINTERNAL_MACRO_ARG_COUNT_HELPER_, TARGOMAN_VA_ARGS_MULTI_OR_EMPTY(__VA_ARGS__))(__VA_ARGS__)

#define TARGOMAN_MACRO_ARG_BASED_FUNC(_fn,...) TARGOMAN_MACRO_ARG_COUNT_HELPER(__VA_ARGS__,\
    _fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,  \
    _fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,  \
    _fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,  \
    _fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,  \
    _fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,  \
    _fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Multi,_fn##Single, None)

//140-207: moved to private
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

//---------------------------------------------
#define TARGOMAN_NULLABLE_TYPE(_type)                            TARGOMANINTERNAL_NULLABLE_UNDERLAYER_CLASS<_type>
#define TARGOMAN_NULLABLE_VAR(_type, _name)                      TARGOMAN_NULLABLE_TYPE(_type) _name
#define TARGOMAN_NULLABLE_HAS_VALUE(_nullable)                   TARGOMANINTERNAL_NULLABLE_HAS_VALUE(_nullable)
#define TARGOMAN_NULLABLE_IS_NULL(_nullable)                     TARGOMANINTERNAL_NULLABLE_IS_NULL(_nullable)
#define TARGOMAN_NULLABLE_GET(_value)                            (TARGOMAN_NULLABLE_HAS_VALUE(_value) ? *_value : QVariant())
#define TARGOMAN_NULLABLE_GET_OR_DEFAULT(_value, _def)           (TARGOMAN_NULLABLE_HAS_VALUE(_value) ? *_value : _def)
#define TARGOMAN_NULLABLE_SET(_var, _value)                      (_var = _value)
#define TARGOMAN_NULLABLE_NULL_VALUE                             TARGOMANINTERNAL_NULLABLE_NULL_VALUE
#define TARGOMAN_NULLABLE_RESET(_var)                            (_var = TARGOMAN_NULLABLE_NULL_VALUE)
#define TARGOMAN_NULLABLE_INSTANTIATE_FROM_QVARIANT(_type, _var) (_var.isNull() ? TARGOMAN_NULLABLE_TYPE(_type)() : TARGOMAN_NULLABLE_TYPE(_type)(_var.template value<_type>()))

#endif /* TARGOMAN_COMMON_MACROS_H_ */
