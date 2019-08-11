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

#define _TMFE_1(_do, X) _do(X)
#define _TMFE_2(_do, X, ...) _do(X)_TMFE_1(_do, __VA_ARGS__)
#define _TMFE_3(_do, X, ...) _do(X)_TMFE_2(_do, __VA_ARGS__)
#define _TMFE_4(_do, X, ...) _do(X)_TMFE_3(_do, __VA_ARGS__)
#define _TMFE_5(_do, X, ...) _do(X)_TMFE_4(_do, __VA_ARGS__)
#define _TMFE_6(_do, X, ...) _do(X)_TMFE_5(_do, __VA_ARGS__)
#define _TMFE_7(_do, X, ...) _do(X)_TMFE_6(_do, __VA_ARGS__)
#define _TMFE_8(_do, X, ...) _do(X)_TMFE_7(_do, __VA_ARGS__)
#define _TMFE_9(_do, X, ...) _do(X)_TMFE_8(_do, __VA_ARGS__)
#define _TMFE_10(_do, X, ...) _do(X)_TMFE_9(_do, __VA_ARGS__)
#define _TMFE_11(_do, X, ...) _do(X)_TMFE_10(_do, __VA_ARGS__)
#define _TMFE_12(_do, X, ...) _do(X)_TMFE_11(_do, __VA_ARGS__)
#define _TMFE_13(_do, X, ...) _do(X)_TMFE_12(_do, __VA_ARGS__)
#define _TMFE_14(_do, X, ...) _do(X)_TMFE_13(_do, __VA_ARGS__)
#define _TMFE_15(_do, X, ...) _do(X)_TMFE_14(_do, __VA_ARGS__)
#define _TMFE_16(_do, X, ...) _do(X)_TMFE_15(_do, __VA_ARGS__)
#define _TMFE_17(_do, X, ...) _do(X)_TMFE_16(_do, __VA_ARGS__)
#define _TMFE_18(_do, X, ...) _do(X)_TMFE_17(_do, __VA_ARGS__)
#define _TMFE_19(_do, X, ...) _do(X)_TMFE_18(_do, __VA_ARGS__)
#define _TMFE_20(_do, X, ...) _do(X)_TMFE_19(_do, __VA_ARGS__)
#define _TMFE_21(_do, X, ...) _do(X)_TMFE_20(_do, __VA_ARGS__)
#define _TMFE_22(_do, X, ...) _do(X)_TMFE_21(_do, __VA_ARGS__)
#define _TMFE_23(_do, X, ...) _do(X)_TMFE_22(_do, __VA_ARGS__)
#define _TMFE_24(_do, X, ...) _do(X)_TMFE_23(_do, __VA_ARGS__)
#define _TMFE_25(_do, X, ...) _do(X)_TMFE_24(_do, __VA_ARGS__)
#define _TMFE_26(_do, X, ...) _do(X)_TMFE_25(_do, __VA_ARGS__)
#define _TMFE_27(_do, X, ...) _do(X)_TMFE_26(_do, __VA_ARGS__)
#define _TMFE_28(_do, X, ...) _do(X)_TMFE_27(_do, __VA_ARGS__)
#define _TMFE_29(_do, X, ...) _do(X)_TMFE_28(_do, __VA_ARGS__)
#define _TMFE_30(_do, X, ...) _do(X)_TMFE_29(_do, __VA_ARGS__)
#define _TMFE_31(_do, X, ...) _do(X)_TMFE_30(_do, __VA_ARGS__)
#define _TMFE_32(_do, X, ...) _do(X)_TMFE_31(_do, __VA_ARGS__)
#define _TMFE_33(_do, X, ...) _do(X)_TMFE_32(_do, __VA_ARGS__)
#define _TMFE_34(_do, X, ...) _do(X)_TMFE_33(_do, __VA_ARGS__)
#define _TMFE_35(_do, X, ...) _do(X)_TMFE_34(_do, __VA_ARGS__)
#define _TMFE_36(_do, X, ...) _do(X)_TMFE_35(_do, __VA_ARGS__)
#define _TMFE_37(_do, X, ...) _do(X)_TMFE_36(_do, __VA_ARGS__)
#define _TMFE_38(_do, X, ...) _do(X)_TMFE_37(_do, __VA_ARGS__)
#define _TMFE_39(_do, X, ...) _do(X)_TMFE_38(_do, __VA_ARGS__)
#define _TMFE_40(_do, X, ...) _do(X)_TMFE_39(_do, __VA_ARGS__)
#define _TMFE_41(_do, X, ...) _do(X)_TMFE_40(_do, __VA_ARGS__)
#define _TMFE_42(_do, X, ...) _do(X)_TMFE_41(_do, __VA_ARGS__)
#define _TMFE_43(_do, X, ...) _do(X)_TMFE_42(_do, __VA_ARGS__)
#define _TMFE_44(_do, X, ...) _do(X)_TMFE_43(_do, __VA_ARGS__)
#define _TMFE_45(_do, X, ...) _do(X)_TMFE_44(_do, __VA_ARGS__)
#define _TMFE_46(_do, X, ...) _do(X)_TMFE_45(_do, __VA_ARGS__)
#define _TMFE_47(_do, X, ...) _do(X)_TMFE_46(_do, __VA_ARGS__)
#define _TMFE_48(_do, X, ...) _do(X)_TMFE_47(_do, __VA_ARGS__)
#define _TMFE_49(_do, X, ...) _do(X)_TMFE_48(_do, __VA_ARGS__)
#define _TMFE_50(_do, X, ...) _do(X)_TMFE_49(_do, __VA_ARGS__)
#define _TMFE_51(_do, X, ...) _do(X)_TMFE_50(_do, __VA_ARGS__)
#define _TMFE_52(_do, X, ...) _do(X)_TMFE_51(_do, __VA_ARGS__)
#define _TMFE_53(_do, X, ...) _do(X)_TMFE_52(_do, __VA_ARGS__)
#define _TMFE_54(_do, X, ...) _do(X)_TMFE_53(_do, __VA_ARGS__)
#define _TMFE_55(_do, X, ...) _do(X)_TMFE_54(_do, __VA_ARGS__)
#define _TMFE_56(_do, X, ...) _do(X)_TMFE_55(_do, __VA_ARGS__)
#define _TMFE_57(_do, X, ...) _do(X)_TMFE_56(_do, __VA_ARGS__)
#define _TMFE_58(_do, X, ...) _do(X)_TMFE_57(_do, __VA_ARGS__)
#define _TMFE_59(_do, X, ...) _do(X)_TMFE_58(_do, __VA_ARGS__)

#define TARGOMAN_MACRO_FOREACH(action,...) \
  TARGOMAN_MACRO_ARG_COUNT_HELPER(__VA_ARGS__,\
    _TMFE_59,_TMFE_58,_TMFE_57,_TMFE_56,_TMFE_55,_TMFE_54,_TMFE_53,_TMFE_52,_TMFE_51,_TMFE_50, \
    _TMFE_49,_TMFE_48,_TMFE_47,_TMFE_46,_TMFE_45,_TMFE_44,_TMFE_43,_TMFE_42,_TMFE_41,_TMFE_40, \
    _TMFE_39,_TMFE_38,_TMFE_37,_TMFE_36,_TMFE_35,_TMFE_34,_TMFE_33,_TMFE_32,_TMFE_31,_TMFE_30, \
    _TMFE_29,_TMFE_28,_TMFE_27,_TMFE_26,_TMFE_25,_TMFE_24,_TMFE_23,_TMFE_22,_TMFE_21,_TMFE_20, \
    _TMFE_19,_TMFE_18,_TMFE_17,_TMFE_16,_TMFE_15,_TMFE_14,_TMFE_13,_TMFE_12,_TMFE_11,_TMFE_10, \
    _TMFE_9,_TMFE_8,_TMFE_7,_TMFE_6,_TMFE_5,_TMFE_4,_TMFE_3,_TMFE_2,_TMFE_1)(action,__VA_ARGS__)

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

/** @brief A macro to define Enum in a semi-enhanced method in which Enums will reside in a namespace */
#define TARGOMAN_DEFINE_ENUM(_name, ...) \
    namespace _name{ enum Type { \
        __VA_ARGS__ \
      }; \
      inline static int getCount(){ return TARGOMAN_MACRO_ARG_COUNT(__VA_ARGS__); } \
      static const char* Strings[] ={ \
          TARGOMAN_MACRO_FOREACH(TARGOMAN_M2STR_WITHCOMMA, __VA_ARGS__) \
      }; \
     inline static QStringList options(enuEnumPart::Type _part = enuEnumPart::Keys){ \
       QStringList Options; \
       int EnumSize = getCount(); \
       qint64 LastID = 0;\
       for(int i=0; i< EnumSize; i++) { \
          QString Option = Strings[i]; \
          switch(_part){ \
            case enuEnumPart::Keys: Option = Option.split('=').first();break; \
            case enuEnumPart::Values:  \
                 if(Option.contains('=')){ \
                    Option = Option.split('=').last(); \
                    bool Ok; LastID = Option.toLongLong(&Ok); \
                    if(!Ok) LastID = Option.toLatin1().at(0); \
                 } else {Option = QString("%1").arg(++LastID);};\
                 break;  \
            default: break;\
          }\
          Options.append( Option.trimmed() ); \
       }return Options; \
     } \
    }\
    inline bool testFlag(_name::Type _key, _name::Type _check)  {return (_key & _check) == _check;}

TARGOMAN_DEFINE_ENUM(enuEnumPart,
                     Full,
                     Keys,
                     Values
                     )
/*
inline constexpr _name::Type operator | (const _name::Type _first, const _name::Type _second) {return (_name::Type)(_first | _second);}\
inline constexpr _name::Type operator & (const _name::Type _first, const _name::Type _second) {return (_name::Type)(_first & _second);}\
*/

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
    inline static int getCount() { return sizeof(Strings)/sizeof(char*); } \
    inline static const char* toStr(Type _type) { \
      if ((int)_type <= Unknown || (int)_type > getCount()) return "Unknown";\
      return Strings[_type]; \
      toStr(Unknown);  \
    } \
    inline static Type toEnum(const QString& _name) { \
      if (_name.isEmpty()) \
        return Unknown; \
      int EnumSize = getCount(); \
      for(int i=0; i< EnumSize; i++) { \
        if (_name.toLower() == QString(Strings[i]).toLower()) \
          return (Type) i; \
      } \
      return Unknown; \
      toEnum(""); \
    } \
    inline static QStringList options(){ \
      QStringList Options; \
      int EnumSize = getCount(); \
      for(int i=0; i< EnumSize; i++) \
          Options.append(Strings[i]); \
      return Options; \
    } \
    }

/********************************************************************************************
 * Usefull Macros.
 ********************************************************************************************/
#define fastToLower(c)  ((c >= 'A' && c <= 'Z') ? c + 0x20 : c)
#define fastToUpper(c)  ((c >= 'a' && c <= 'z') ? c - 0x20 : c)
#define BIG_CONSTANT(x) (x##LLU)
#define MACRO_SAFE_COMMA ,
#define OUTPUT
#define INOUT

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
