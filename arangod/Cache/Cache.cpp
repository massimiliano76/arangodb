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

#include "Cache/Cache.h"
#include "Basics/Common.h"
#include "Cache/CachedValue.h"
#include "Cache/Metadata.h"

#include <stdint.h>
#include <list>

using namespace arangodb::cache;

Cache::Finding::Finding(CachedValue* v) : _value(v) {
  if (_value != nullptr) {
    _value->lease();
  }
}

Cache::Finding::~Finding() {
  if (_value != nullptr) {
    _value->release();
  }
}

bool Cache::Finding::found() const { return (_value != nullptr); }

CachedValue const* Cache::Finding::value() const { return _value; }

CachedValue* Cache::Finding::copy() const {
  return ((_value == nullptr) ? nullptr : _value->copy());
}
