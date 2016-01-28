/*jshint globalstrict:false, strict:false, unused : false */
/*global assertEqual */

////////////////////////////////////////////////////////////////////////////////
/// @brief tests for dump/reload
///
/// @file
///
/// DISCLAIMER
///
/// Copyright 2010-2012 triagens GmbH, Cologne, Germany
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
/// Copyright holder is triAGENS GmbH, Cologne, Germany
///
/// @author Jan Steemann
/// @author Copyright 2012, triAGENS GmbH, Cologne, Germany
////////////////////////////////////////////////////////////////////////////////

var db = require("@arangodb").db;
var internal = require("internal");
var fs = require("fs");
var jsunity = require("jsunity");


function runSetup () {
  'use strict';
  internal.debugClearFailAt();

  var i, c, paths = [ ];
  for (i = 0; i < 10; ++i) {
    db._drop("UnitTestsRecovery" + i);
    c = db._create("UnitTestsRecovery" + i);
    paths[i] = c.path();
    c.drop();
  }
  db._drop("test");
  c = db._create("test");
  c.save({ _key: "crashme" }, true);

  internal.wait(3, true);
  for (i = 0; i < 10; ++i) {
    var path = paths[i];
    fs.makeDirectory(path);

    if (i < 5) {
      // create a leftover parameter.json.tmp file
      fs.write(fs.join(path, "parameter.json.tmp"), "");
    }
    else {
      // create an empty parameter.json file
      fs.write(fs.join(path, "parameter.json"), "");
      // create some other file
      fs.write(fs.join(path, "foobar"), "foobar");
    }
  }

  internal.debugSegfault("crashing server");
}

////////////////////////////////////////////////////////////////////////////////
/// @brief test suite
////////////////////////////////////////////////////////////////////////////////

function recoverySuite () {
  'use strict';
  jsunity.jsUnity.attachAssertions();

  return {
    setUp: function () {
    },
    tearDown: function () {
    },

////////////////////////////////////////////////////////////////////////////////
/// @brief test whether we can recover the collections even with the
/// leftover directories present
////////////////////////////////////////////////////////////////////////////////
    
    testLeftoverCollectionDirectory : function () {
      var i; 
      for (i = 0; i < 5; ++i) {
        assertEqual(null, db._collection("UnitTestsRecovery" + i));
      }

    }
        
  };
}

////////////////////////////////////////////////////////////////////////////////
/// @brief executes the test suite
////////////////////////////////////////////////////////////////////////////////

function main (argv) {
  'use strict';
  if (argv[1] === "setup") {
    runSetup();
    return 0;
  }
  else {
    jsunity.run(recoverySuite);
    return jsunity.done().status ? 0 : 1;
  }
}

