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
 * @author Saeed Torabzadeh <saeed.torabzadeh@targoman.com>
 */

#ifndef TARGOMAN_COMMON_TMPLBOUNDEDCACHE_H
#define TARGOMAN_COMMON_TMPLBOUNDEDCACHE_H

#include <QHash>
#include <QTime>
#include <QMutex>
#include "libTargomanCommon/exTargomanBase.h"

namespace Targoman {
namespace Common {

template <template <class itmplKey, class itmplVal> class BaseContainer_t, class itmplKey, class itmplVal, quint32 itmplMaxItems = 10000>
    /**
     * @brief The tmplBoundedCache template is a derivation of Map or Hash class (depending on BaseContainer_t) and
     *        it is augmented with QHash for AccessDate.
     *
     * This class removes old items of Cache when itmlMaxItems is reached except when itmplMaxItems is set to zero.
     */
    class tmplBoundedCache : public BaseContainer_t <itmplKey, itmplVal>
    {
    public:

        tmplBoundedCache(){
            if (itmplMaxItems == 0)
                throw exTargomanInvalidParameter("Max cache Items must be greater than zero");
            this->MaxItems = itmplMaxItems;
        }

        tmplBoundedCache(const tmplBoundedCache& _other):
            BaseContainer_t<itmplKey, itmplVal>(_other),
            Lock(_other.Lock),
            KeyAccessDateTime(_other.KeyAccessDateTime),
            MaxItems(_other.MaxItems)
        {}

        typedef typename BaseContainer_t<itmplKey, itmplVal>::iterator   Iterator_t;

        inline Iterator_t insert(itmplKey _key, itmplVal _val){
            QMutexLocker Locker(&this->Lock);
            if(this->MaxItems && BaseContainer_t<itmplKey, itmplVal>::size() >= static_cast<int>(this->MaxItems)){
                QList<QTime> Values = this->KeyAccessDateTime.values();
                std::nth_element(Values.begin(), Values.begin() + this->MaxItems / 2, Values.end());
                QList<itmplKey> ExpiredKeys;
                for(quint32 Index = 0; Index < this->MaxItems / 2; ++Index)
                        ExpiredKeys.append(this->KeyAccessDateTime.keys(Values.at(Index)));

                foreach(itmplKey Key, ExpiredKeys){
                    // Do not use this->remove here as it will cause a deadlock
                    this->KeyAccessDateTime.remove(Key);
                    BaseContainer_t<itmplKey, itmplVal>::remove(Key);
                }
            }

            this->KeyAccessDateTime.insert(_key, QTime::currentTime());
            return BaseContainer_t<itmplKey, itmplVal>::insert(_key, _val);
        }

        inline Iterator_t insertMulti(itmplKey _key, itmplVal _val){
            if(this->MaxItems && BaseContainer_t<itmplKey, itmplVal>::size() >= this->MaxItems){
                QList<QTime> Values = this->KeyAccessDateTime.values();
                QTime Oldest = Values.first();
                for(int i = 0; i < Values.size(); ++i)
                    if(Values.at(i) < Oldest)
                        Oldest = Values.at(i);
                QList<itmplKey> ExpiredKeys = this->KeyAccessDateTime.keys(Oldest);

                foreach(itmplKey Key, ExpiredKeys){
                    this->remove(Key);
                }
            }

            this->KeyAccessDateTime.insertMulti(_key, QTime::currentTime());
            return BaseContainer_t<itmplKey, itmplVal>::insertMulti(_key, _val);
        }

        inline void clear(){
            QMutexLocker Locker(&this->Lock);
            BaseContainer_t<itmplKey, itmplVal>::clear();
            this->KeyAccessDateTime.clear();
        }

        inline itmplVal value(const itmplKey& _key,
                              bool _updateAccessTime = true,
                              const itmplVal& _defaultValue = itmplVal()){
            QMutexLocker Locker(&this->Lock);
            if (BaseContainer_t<itmplKey, itmplVal>::contains(_key) == false)
                return _defaultValue;

            if (_updateAccessTime)
                this->KeyAccessDateTime.insert(_key, QTime::currentTime());
            return this->baseValue (_key);
        }

        inline QList<itmplVal> values(const itmplKey& _key,
                              bool _updateAccessTime = true,
                              const itmplVal& _defaultValue = itmplVal()){
            if (BaseContainer_t<itmplKey, itmplVal>::contains(_key) == false)
                return _defaultValue;


            if (_updateAccessTime) {
                auto Iter = this->KeyAccessDateTime.find(_key);
                QTime Time = QTime::currentTime();
                while(Iter != this->KeyAccessDateTime.end() && Iter.key() == _key) {
                    Iter.value() = Time;
                    ++Iter;
                }
            }
            return BaseContainer_t<itmplKey, itmplVal>::values(_key);
        }

        inline itmplVal& operator[] ( const itmplKey & _key){
            QMutexLocker Locker(&this->Lock);
            if (BaseContainer_t<itmplKey, itmplVal>::contains(_key) == false)
                return  BaseContainer_t<itmplKey, itmplVal>::operator [] (_key);

            QTime AccessTime = QTime::currentTime();
            this->KeyAccessDateTime.insert(_key, AccessTime);

            return BaseContainer_t<itmplKey, itmplVal>::operator [] (_key);
        }

        inline int remove(const itmplKey& _key){
            QMutexLocker Locker(&this->Lock);
            this->KeyAccessDateTime.remove(_key);
            return BaseContainer_t<itmplKey, itmplVal>::remove(_key);
        }

        void setMaxItems(quint32 _maxItems){ this->MaxItems = _maxItems; }

        quint32 maxItems(){ return this->MaxItems; }

    protected:
        inline itmplVal baseValue(const itmplKey& _key){
            return BaseContainer_t<itmplKey, itmplVal>::value(_key);
        }

    protected:
        QMutex                       Lock;
        QHash<itmplKey, QTime >      KeyAccessDateTime;

        quint32 MaxItems;
    };
}
}
#endif // TARGOMAN_COMMON_TMPLBOUNDEDCACHE_H
