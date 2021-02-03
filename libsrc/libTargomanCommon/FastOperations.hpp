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
 * @author Behrooz Vedadian <vedadian@targoman.com>
 */

#ifndef TARGOMAN_COMMON_FASTOPERATIONS_HPP
#define TARGOMAN_COMMON_FASTOPERATIONS_HPP

#include "libTargomanCommon/Types.h"

namespace Targoman {
namespace Common {

const quint32 INT32_SIGN_BIT  = 0x80000000;

inline bool isNegativeFloat(float _num){
    return (reinterpret_cast<FloatEncoded_t*>(&_num))->AsUInt32 & INT32_SIGN_BIT;
}

inline bool isPositiveFloat(float _num){
    return ! isNegativeFloat(_num);
}

inline quint32 rotl32 ( quint32 x, qint8 r ){return (x << r) | (x >> (32 - r));}
inline quint64 rotl64 ( quint32 x, qint8 r ){ return (x << r) | (x >> (64 - r));}

/**
 * @param _str Input string
 * @return Returns trimmed string
 */
inline std::string& fastTrimStdString(std::string& _str){
    const char* StrPtr = _str.c_str();
    char* EndStr = const_cast<char*>(StrPtr) + _str.size();

    while(*StrPtr){
        if(*StrPtr == ' ' ||
           *StrPtr == '\t' ||
           *StrPtr == '\r' ||
           *StrPtr == '\n')
            StrPtr++;
        else
            break;
    }
    while(*EndStr){
        if(*StrPtr == ' ' ||
           *StrPtr == '\t' ||
           *StrPtr == '\r' ||
           *StrPtr == '\n')
            EndStr--;
        else{
            *(EndStr+1) = '\0';
            break;
        }
    }
    return _str = StrPtr;
}

#define IS_WHITE_SPACE(c) ((c) == ' ' || (c) == '\t')
#define IS_VALID_DIGIT(c) ((c) >= '0' && (c) <= '9')

/**
 * @brief fastASCII2Float converts Char* string to float string.
 * @param[in] pFloatString input string.
 * @param[out] _lastPos last position of float number in the string.
 * @return returns converted float number.
 */
inline float fastASCII2Float (const char *pFloatString, size_t& _lastPos)
{
    qint64 IntValue, Scale = 0;
    //qint16 Sign;
    const char*  StartOfString = pFloatString;
    //const float  Log2Of10 = log2(10);

//    Sign = 1;
    if (*pFloatString == '-') {
  //      Sign = -1;
        ++pFloatString;
    } else if (*pFloatString == '+') {
        ++pFloatString;
    }

    // Get digits before decimal point or exponent, if any.
    for (IntValue = 0; IS_VALID_DIGIT(*pFloatString); ++pFloatString) {
        IntValue = IntValue * 10 + (*pFloatString - '0');
    }

    // Get digits after decimal point, if any.
    if (*pFloatString == '.') {
        ++pFloatString;
        while (IS_VALID_DIGIT(*pFloatString)) {
            if (Scale < 8){
                IntValue = IntValue * 10 + (*pFloatString - '0');
                ++Scale;
            }
            ++pFloatString;
        }
    }

    if (*pFloatString == 'e'){
        ++pFloatString;
        qint16 ExpSign = 1;
        if (*pFloatString == '+')
            ++pFloatString;
        else if (*pFloatString == '-'){
            ExpSign = -1;
            ++pFloatString;
        }
        quint16 Exponent = 0;
        for (IntValue = 0; IS_VALID_DIGIT(*pFloatString); ++pFloatString) {
            Exponent = Exponent * 10 + static_cast<quint16>(*pFloatString - '0');
        }
        Scale += ExpSign * Exponent;
    }

    _lastPos = static_cast<size_t>(pFloatString - StartOfString);
    // Return signed and scaled floating point result.

    char LastChar = *pFloatString;
    *(const_cast<char*>(pFloatString)) = 0;
    float Ret = static_cast<float>(atof(StartOfString));
    *(const_cast<char*>(pFloatString)) = LastChar;
    return Ret;

    //return ((float)(Sign * IntValue))/(float)Scale;
}
/**
 * @param[in, out] _str input and output string.
 * @return returns pointer of first character that is not space.
 */
inline const char* fastSkip2NonSpace(const char*& _str){
    while(*_str)
        if(*_str == ' ' || *_str == '\t' || *_str == '\r' || *_str == '\n')
            _str++;
        else
            return _str;
    return _str;
}

/**
 * @param[in, out] _str input and output string.
 * @return returns pointer of first character that is space.
 */

inline const char* fastSkip2Space(const char*& _str){
    while(*_str)
        if(*_str == ' ' || *_str == '\t' || *_str == '\r' || *_str == '\n')
            return _str;
        else
            _str++;
    return _str;
}

template<typename Container_t, typename Type_t, typename Comparator_t>
/**
 * @brief  findInsertionPosEx finds correct place to insert _element in the _container using _comparator to have a sorted
 *         list and whether the container already contains this element or not
 * @return Returns a pair of bool and int which indicates whether the element was found in the container or not and where
 *         to insert new element for the list to retain its sorted structure
 */
QPair<bool, int> findInsertionPosEx(Container_t _sortedContainer, const Type_t& _element, Comparator_t _comparator)
{
    int Begin = 0;
    int End = _sortedContainer.size();
    while(Begin < End) {
        int Mid = (Begin + End) / 2;
        int ComparisonResult = _comparator(_element, _sortedContainer.at(Mid));
        if(ComparisonResult == 0)
            return QPair<int, bool>(Mid, true);
        else if(ComparisonResult > 0)
            Begin = Mid + 1;
        else
            End = Mid;
    }
    return QPair<int, bool>(Begin, false);
}

template<typename Container_t, typename Type_t, typename Comparator_t>
/**
 * @brief  findInsertionPosEx finds correct place to insert _element in the _container using _comparator to have a sorted
 *         list and whether the container already contains this element or not
 * @return Returns a pair of bool and int which indicates whether the element was found in the container or not and where
 *         to insert new element for the list to retain its sorted structure
 */
QPair<int, bool> findInsertionPosEx(const QList<int>& _index, Container_t _container, const Type_t& _element, Comparator_t _comparator)
{
    Q_ASSERT(_index.size() == _container.size());

    int Begin = 0;
    int End = _container.size();
    while(Begin < End) {
        int Mid = (Begin + End) / 2;
        int ComparisonResult = _comparator(_element, _container.at(_index.at(Mid)));
        if(ComparisonResult == 0)
            return QPair<int, bool>(Mid, true);
        else if(ComparisonResult > 0)
            Begin = Mid + 1;
        else
            End = Mid;
    }
    return QPair<int, bool>(Begin, false);
}

template<class Class_t, class Container_t, typename Functor_t>
/**
 * @brief findInsertionPos finds correct place to insert _element in the _container using _comperator to have a sorted list.
 * @return Returns correct place of insertion.
 */
size_t findInsertionPos(const Container_t& _sortedConatiner, const Class_t& _element, Functor_t _comparator){
    for(size_t i = 0; i< reinterpret_cast<size_t>(_sortedConatiner.size()); ++i){
        if (_comparator(_element, _sortedConatiner.at(i)) > 0)
            return i;
    }
    return _sortedConatiner.size();
}

}
}



#endif // TARGOMAN_COMMON_FASTOPERATIONS_HPP
