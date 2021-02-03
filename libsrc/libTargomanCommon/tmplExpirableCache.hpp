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
 */

#ifndef TARGOMAN_COMMON_TMPLEXPIRABLECACHE_H
#define TARGOMAN_COMMON_TMPLEXPIRABLECACHE_H

#include "libTargomanCommon/tmplBoundedCache.hpp"

namespace Targoman {
namespace Common {

template  <class itmplType>
struct tmplExpirableCacheItem{
    itmplType Value;
    QTime TTL;
    tmplExpirableCacheItem(const itmplType& _value = itmplType(), QTime _ttl = QTime()) :
        Value(_value),
        TTL(_ttl)
    {;}
    tmplExpirableCacheItem(const tmplExpirableCacheItem<itmplType>& _other):
        Value(_other.Value),
        TTL(_other.TTL)
    {;}
};

template <template <class itmplKey, class itmplVal> class BaseContainer_t, class itmplKey, class itmplVal, quint32 itmplMaxItems = 10000>
    /**
     * @brief The tmplExpirableCache template is a derivation of tmplBoundedCache with two new methods for limiting each cached item life time
     */
    class tmplExpirableCache : public tmplBoundedCache<BaseContainer_t, itmplKey, tmplExpirableCacheItem<itmplVal>, itmplMaxItems>
    {
    public:
        tmplExpirableCache() :
            tmplBoundedCache<BaseContainer_t, itmplKey, tmplExpirableCacheItem<itmplVal>, itmplMaxItems>()
        {;}

        typedef typename BaseContainer_t<itmplKey, tmplExpirableCacheItem<itmplVal>>::iterator   Iterator_t;
        typedef tmplBoundedCache<BaseContainer_t, itmplKey, tmplExpirableCacheItem<itmplVal>, itmplMaxItems> BaseCacheClass_t;
        typedef tmplExpirableCacheItem<itmplVal> ExpirableCacheItem_t;

        inline Iterator_t insert(quint32 _ttl, itmplKey _key, itmplVal _val){
            return BaseCacheClass_t::insert(_key, ExpirableCacheItem_t(_val, QTime::currentTime().addSecs(_ttl)));
        }

        inline bool contains(const itmplKey& _key){
            itmplVal Value = this->value(_key, false);
            return Value != itmplVal();
        }

        inline itmplVal value(const itmplKey& _key,
                              bool _updateAccessTime = true,
                              const itmplVal& _defaultValue = itmplVal()){
            QMutexLocker Locker(&this->Lock);
            if (BaseContainer_t<itmplKey, ExpirableCacheItem_t>::contains(_key) == false)
                return _defaultValue;
            QTime CurrTime = QTime::currentTime();

            ExpirableCacheItem_t CachedItem(this->baseValue(_key));

            if(CurrTime.secsTo(CachedItem.TTL)<=0){
                Locker.unlock();
                this->remove(_key);
                return _defaultValue;
            }

            if (_updateAccessTime)
                this->KeyAccessDateTime.insert(_key, CurrTime);
            return CachedItem.Value;
        }

        /*inline itmplVal& operator[] (const itmplKey &){
            Q_ASSERT_X (false, "Expirable cache", "Using [] operator on expirable chache is not allowed");
        }*/
    };
}
}
#endif // TARGOMAN_COMMON_TMPLEXPIRABLECACHE_H
