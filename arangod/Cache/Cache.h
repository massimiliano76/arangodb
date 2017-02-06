////////////////////////////////////////////////////////////////////////////////
/// DISCLAIMER
///
/// Copyright 2014-2017 ArangoDB GmbH, Cologne, Germany
/// Copyright 2004-2014 triAGENS GmbH, Cologne, Germany
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
///     http://www.apache.org/licenses/LICENSE-2.0
///
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
///
/// Copyright holder is ArangoDB GmbH, Cologne, Germany
///
/// @author Daniel H. Larkin
////////////////////////////////////////////////////////////////////////////////

#ifndef ARANGODB_CACHE_CACHE_H
#define ARANGODB_CACHE_CACHE_H

#include "Basics/Common.h"
#include "Cache/CachedValue.h"
#include "Cache/Metadata.h"

#include <stdint.h>
#include <list>

namespace arangodb {
namespace cache {

class Metadata;  // forward declaration

class Cache {
 public:
  class Finding {
   private:
    CachedValue* _value;

   public:
    Finding(CachedValue* v);
    ~Finding();

    bool found();
    CachedValue* value();
    CachedValue* copy();
  };

  virtual Finding lookup(uint32_t keySize, uint8_t* key) = 0;
  virtual bool insert(CachedValue* value) = 0;
  virtual bool remove(uint32_t keySize, uint8_t* key) = 0;

  virtual std::list<Metadata>::iterator& metadata() = 0;
  virtual void freeMemory() = 0;
  virtual void migrate() = 0;
};

};  // end namespace cache
};  // end namespace arangodb

#endif
