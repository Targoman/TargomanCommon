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

#ifndef TARGOMAN_COMMON_MACROSPRIVATE_HPP
#define TARGOMAN_COMMON_MACROSPRIVATE_HPP

#include <QString>

//78-135: moved from non-private
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

#define TARGOMANINTERNAL_MACRO_ARG_COUNT_HELPER_EMPTY(...) 0
#define TARGOMANINTERNAL_MACRO_ARG_COUNT_HELPER_MULTI(...) TARGOMANINTERNAL_MACRO_ARG_COUNT(__VA_ARGS__)

//140-207: moved from non-private
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

//---------------------------------------------
#define TARGOMANINTERNAL_NULLABLE_UNDERLAYER_CLASS      std::optional
#define TARGOMANINTERNAL_NULLABLE_UNDERLAYER_CLASS_NAME #TARGOMANINTERNAL_NULLABLE_UNDERLAYER_CLASS
#define TARGOMANINTERNAL_NULLABLE_PREFIX                TARGOMANINTERNAL_NULLABLE_UNDERLAYER_CLASS_NAME"<"
#define TARGOMANINTERNAL_NULLABLE_POSTFIX               ">"
#define TARGOMANINTERNAL_NULLABLE_HAS_VALUE(_nullable)  _nullable.has_value()
#define TARGOMANINTERNAL_NULLABLE_IS_NULL(_nullable)    (_nullable.has_value() == false)
#define TARGOMANINTERNAL_NULLABLE_NULL_VALUE            std::nullopt

#endif // TARGOMAN_COMMON_MACROSPRIVATE_HPP
