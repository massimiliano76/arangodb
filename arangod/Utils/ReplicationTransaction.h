////////////////////////////////////////////////////////////////////////////////
/// DISCLAIMER
///
/// Copyright 2014-2016 ArangoDB GmbH, Cologne, Germany
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
/// @author Jan Steemann
////////////////////////////////////////////////////////////////////////////////

#ifndef ARANGOD_UTILS_REPLICATION_TRANSACTION_H
#define ARANGOD_UTILS_REPLICATION_TRANSACTION_H 1

#include "Basics/Common.h"
#include "StorageEngine/TransactionState.h"
#include "Utils/StandaloneTransactionContext.h"
#include "Utils/Transaction.h"

struct TRI_vocbase_t;

namespace arangodb {

class ReplicationTransaction : public Transaction {
 public:
  /// @brief create the transaction
  ReplicationTransaction(TRI_vocbase_t* vocbase)
      : Transaction(StandaloneTransactionContext::Create(vocbase)) {

    _vocbase->use();
  }

  /// @brief end the transaction
  ~ReplicationTransaction() { _vocbase->release(); }

 public:

  //////////////////////////////////////////////////////////////////////////////
  /// @brief get a collection by id
  /// this will automatically add the collection to the transaction
  //////////////////////////////////////////////////////////////////////////////

  inline TransactionCollection* trxCollection(TRI_voc_cid_t cid) {
    TRI_ASSERT(cid > 0);

    TransactionCollection* trxCollection = _state->collection(cid, AccessMode::Type::WRITE);

    if (trxCollection == nullptr) {
      int res = _state->addCollection(cid, AccessMode::Type::WRITE, 0, true, true);

      if (res == TRI_ERROR_NO_ERROR) {
        res = _state->ensureCollections();
      }

      if (res != TRI_ERROR_NO_ERROR) {
        return nullptr;
      }

      trxCollection = _state->collection(cid, AccessMode::Type::WRITE);
    }

    return trxCollection;
  }
};
}

#endif
