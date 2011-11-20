////////////////////////////////////////////////////////////////////////////////
/// @brief json objects
///
/// @file
///
/// DISCLAIMER
///
/// Copyright 2010-2011 triagens GmbH, Cologne, Germany
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
/// @author Dr. Frank Celler
/// @author Copyright 2011, triagens GmbH, Cologne, Germany
////////////////////////////////////////////////////////////////////////////////

#ifndef TRIAGENS_PHILADELPHIA_BASICS_JSON_H
#define TRIAGENS_PHILADELPHIA_BASICS_JSON_H 1

#include <Basics/Common.h>

#include <Basics/associative.h>
#include <Basics/vector.h>

#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
// --SECTION--                                              forward declarations
// -----------------------------------------------------------------------------

struct TRI_string_buffer_s;

// -----------------------------------------------------------------------------
// --SECTION--                                                              JSON
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// --SECTION--                                                      public types
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Json
/// @{
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief json type
////////////////////////////////////////////////////////////////////////////////

typedef enum {
  TRI_JSON_NULL = 1,
  TRI_JSON_BOOLEAN = 2,
  TRI_JSON_NUMBER = 3,
  TRI_JSON_STRING = 4,
  TRI_JSON_ARRAY = 5,
  TRI_JSON_LIST = 6
}
TRI_json_type_e;

////////////////////////////////////////////////////////////////////////////////
/// @brief json object
////////////////////////////////////////////////////////////////////////////////

typedef struct TRI_json_s {
  TRI_json_type_e _type;

  union {
    bool _boolean;
    double _number;
    TRI_blob_t _string;
    TRI_vector_t _objects;
  }
  _value;
}
TRI_json_t;

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                      constructors and destructors
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Json
/// @{
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief creates a null object
////////////////////////////////////////////////////////////////////////////////

TRI_json_t* TRI_CreateNullJson (void);

////////////////////////////////////////////////////////////////////////////////
/// @brief creates a boolean object
////////////////////////////////////////////////////////////////////////////////

TRI_json_t* TRI_CreateBooleanJson (bool value);

////////////////////////////////////////////////////////////////////////////////
/// @brief creates a number object
////////////////////////////////////////////////////////////////////////////////

TRI_json_t* TRI_CreateNumberJson (double value);

////////////////////////////////////////////////////////////////////////////////
/// @brief creates a string object
////////////////////////////////////////////////////////////////////////////////

TRI_json_t* TRI_CreateStringJson (char* value);

////////////////////////////////////////////////////////////////////////////////
/// @brief creates a string object, copying the string
////////////////////////////////////////////////////////////////////////////////

TRI_json_t* TRI_CreateStringCopyJson (char const* value);

////////////////////////////////////////////////////////////////////////////////
/// @brief creates a string object with given length
////////////////////////////////////////////////////////////////////////////////

TRI_json_t* TRI_CreateString2Json (char* value, size_t length);

////////////////////////////////////////////////////////////////////////////////
/// @brief creates a string object with given length, copying the string
////////////////////////////////////////////////////////////////////////////////

TRI_json_t* TRI_CreateString2CopyJson (char const* value, size_t length);

////////////////////////////////////////////////////////////////////////////////
/// @brief creates a list object
////////////////////////////////////////////////////////////////////////////////

TRI_json_t* TRI_CreateListJson (void);

////////////////////////////////////////////////////////////////////////////////
/// @brief creates an array
////////////////////////////////////////////////////////////////////////////////

TRI_json_t* TRI_CreateArrayJson (void);

////////////////////////////////////////////////////////////////////////////////
/// @brief destroys a json object, but does not free the pointer
////////////////////////////////////////////////////////////////////////////////

void TRI_DestroyJson (TRI_json_t*);

////////////////////////////////////////////////////////////////////////////////
/// @brief destroys a json object and frees the pointer
////////////////////////////////////////////////////////////////////////////////

void TRI_FreeJson (TRI_json_t*);

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                                  public functions
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Json
/// @{
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief adds a new sub-object to a list object, copying it
////////////////////////////////////////////////////////////////////////////////

void TRI_PushBackListJson (TRI_json_t* list, TRI_json_t* object);

////////////////////////////////////////////////////////////////////////////////
/// @brief adds a new sub-object to a list object, not copying it
////////////////////////////////////////////////////////////////////////////////

void TRI_PushBack2ListJson (TRI_json_t* list, TRI_json_t* object);

////////////////////////////////////////////////////////////////////////////////
/// @brief adds a new attribute  to an object
////////////////////////////////////////////////////////////////////////////////

void TRI_InsertArrayJson (TRI_json_t* object, char const* name, TRI_json_t* subobject);

////////////////////////////////////////////////////////////////////////////////
/// @brief adds a new attribute  to an object, not copying it
////////////////////////////////////////////////////////////////////////////////

void TRI_Insert2ArrayJson (TRI_json_t* object, char const* name, TRI_json_t* subobject);

////////////////////////////////////////////////////////////////////////////////
/// @brief looks up an attribute in an json array
////////////////////////////////////////////////////////////////////////////////

TRI_json_t* TRI_LookupArrayJson (TRI_json_t* object, char const* name);

////////////////////////////////////////////////////////////////////////////////
/// @brief stringifies a json object
////////////////////////////////////////////////////////////////////////////////

void TRI_StringifyJson (struct TRI_string_buffer_s*, TRI_json_t const* object);

////////////////////////////////////////////////////////////////////////////////
/// @brief stringifies a json object skiping the outer braces
////////////////////////////////////////////////////////////////////////////////

void TRI_Stringify2Json (struct TRI_string_buffer_s*, TRI_json_t const* object);

////////////////////////////////////////////////////////////////////////////////
/// @brief prints a json object
////////////////////////////////////////////////////////////////////////////////

bool TRI_PrintJson (int fd, TRI_json_t const*);

////////////////////////////////////////////////////////////////////////////////
/// @brief saves a json object
////////////////////////////////////////////////////////////////////////////////

bool TRI_SaveJson (char const* filename, TRI_json_t const*);

////////////////////////////////////////////////////////////////////////////////
/// @brief copies a json object into a given buffer
////////////////////////////////////////////////////////////////////////////////

void TRI_CopyToJson (TRI_json_t* dst, TRI_json_t const* src);

////////////////////////////////////////////////////////////////////////////////
/// @brief copies a json object
////////////////////////////////////////////////////////////////////////////////

TRI_json_t* TRI_CopyJson (TRI_json_t*);

////////////////////////////////////////////////////////////////////////////////
/// @brief parses a json string
////////////////////////////////////////////////////////////////////////////////

TRI_json_t* TRI_JsonString (char const* text);

////////////////////////////////////////////////////////////////////////////////
/// @brief parses a json string and returns error message
////////////////////////////////////////////////////////////////////////////////

TRI_json_t* TRI_Json2String (char const* text, char** error);

////////////////////////////////////////////////////////////////////////////////
/// @brief parses a json file and returns error message
////////////////////////////////////////////////////////////////////////////////

TRI_json_t* TRI_JsonFile (char const* path, char** error);

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                                        JSON SHAPE
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// --SECTION--                                                      public types
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Json
/// @{
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief json storage type of a shape identifier
////////////////////////////////////////////////////////////////////////////////

typedef uint64_t TRI_shape_sid_t;

////////////////////////////////////////////////////////////////////////////////
/// @brief json storage type of an attribute identifier
////////////////////////////////////////////////////////////////////////////////

typedef uint64_t TRI_shape_aid_t;

////////////////////////////////////////////////////////////////////////////////
/// @brief json storage type of a size
////////////////////////////////////////////////////////////////////////////////

typedef uint64_t TRI_shape_size_t;

////////////////////////////////////////////////////////////////////////////////
/// @brief json type of a shape
////////////////////////////////////////////////////////////////////////////////

typedef enum {
  TRI_SHAPE_ILLEGAL = 0,
  TRI_SHAPE_NULL = 1,
  TRI_SHAPE_BOOLEAN = 2,
  TRI_SHAPE_NUMBER = 3,
  TRI_SHAPE_SHORT_STRING = 4,
  TRI_SHAPE_LONG_STRING = 5,
  TRI_SHAPE_ARRAY = 6,
  TRI_SHAPE_LIST = 7,
  TRI_SHAPE_HOMOGENEOUS_LIST = 8,
  TRI_SHAPE_HOMOGENEOUS_SIZED_LIST = 9
}
TRI_shape_type_e;

////////////////////////////////////////////////////////////////////////////////
/// @brief json storage type of a TRI_shape_type_e
////////////////////////////////////////////////////////////////////////////////

typedef uint64_t TRI_shape_type_t;

////////////////////////////////////////////////////////////////////////////////
/// @brief json storage type of a boolean
////////////////////////////////////////////////////////////////////////////////

typedef uint32_t TRI_shape_boolean_t;

////////////////////////////////////////////////////////////////////////////////
/// @brief json storage type of a number
////////////////////////////////////////////////////////////////////////////////

typedef double TRI_shape_number_t;

////////////////////////////////////////////////////////////////////////////////
/// @brief json storage type of a length for short strings
////////////////////////////////////////////////////////////////////////////////

typedef uint8_t TRI_shape_length_short_string_t;

////////////////////////////////////////////////////////////////////////////////
/// @brief json storage type of a length for long strings
////////////////////////////////////////////////////////////////////////////////

typedef uint32_t TRI_shape_length_long_string_t;

////////////////////////////////////////////////////////////////////////////////
/// @brief json storage type of a length for lists
////////////////////////////////////////////////////////////////////////////////

typedef uint32_t TRI_shape_length_list_t;

////////////////////////////////////////////////////////////////////////////////
/// @brief base class for json shape
////////////////////////////////////////////////////////////////////////////////

typedef struct TRI_shape_s {
  TRI_shape_sid_t _sid;
  TRI_shape_type_t _type;
  TRI_shape_size_t _size; // total size of the shape
  TRI_shape_size_t _dataSize; // in case of fixed sized shaped or TRI_SHAPE_SIZE_VARIABLE
}
TRI_shape_t;

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                                       SHAPED JSON
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// --SECTION--                                                      public types
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Json
/// @{
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief shaped json
////////////////////////////////////////////////////////////////////////////////

typedef struct TRI_shaped_json_s {
  TRI_shape_sid_t _sid;
  TRI_blob_t _data;
}
TRI_shaped_json_t;

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                                    ATTRIBUTE PATH
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// --SECTION--                                                      public types
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Json
/// @{
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief json storage type of an attribute path
////////////////////////////////////////////////////////////////////////////////

typedef uint64_t TRI_shape_pid_t;

////////////////////////////////////////////////////////////////////////////////
/// @brief json attribute path
////////////////////////////////////////////////////////////////////////////////

typedef struct TRI_shape_path_s {
  TRI_shape_pid_t _pid;
  uint64_t _aidLength;
  uint32_t _nameLength;  // include trailing '\0'
  // TRI_shape_aid_t _aids[];
  // char _name[];
}
TRI_shape_path_t;

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                                       JSON SHAPER
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// --SECTION--                                                      public types
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Json
/// @{
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief json shaper
////////////////////////////////////////////////////////////////////////////////

typedef struct TRI_shaper_s {
  TRI_shape_aid_t (*findAttributeName) (struct TRI_shaper_s*, char const*);
  char const* (*lookupAttributeId) (struct TRI_shaper_s*, TRI_shape_aid_t);
  TRI_shape_t const* (*findShape) (struct TRI_shaper_s*, TRI_shape_t*);
  TRI_shape_t const* (*lookupShapeId) (struct TRI_shaper_s*, TRI_shape_sid_t);

  TRI_shape_path_t const* (*lookupAttributePathByPid) (struct TRI_shaper_s*, TRI_shape_pid_t);
  TRI_shape_pid_t (*findAttributePathByName) (struct TRI_shaper_s*, char const*);

  TRI_associative_synced_t _attributePathsByName;
  TRI_associative_synced_t _attributePathsByPid;

  TRI_shape_pid_t _nextPid;
  TRI_mutex_t _attributePathLock;

  TRI_shape_sid_t _sidNull;
  TRI_shape_sid_t _sidBoolean;
  TRI_shape_sid_t _sidNumber;
  TRI_shape_sid_t _sidShortString;
  TRI_shape_sid_t _sidLongString;
  TRI_shape_sid_t _sidList;
}
TRI_shaper_t;

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                                      SHAPE ACCESS
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// --SECTION--                                                      public types
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Json
/// @{
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief json shape access
////////////////////////////////////////////////////////////////////////////////

typedef struct TRI_shape_access_s {
  TRI_shape_sid_t _sid;                 // shaped identifier of the shape we are looking at
  TRI_shape_pid_t _pid;                 // path identifier of the attribute path

  TRI_shape_t const* _shape;            // resulting shape
  void* const* _code;                   // bytecode
}
TRI_shape_access_t;

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// --SECTION--                                                  public functions
// -----------------------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////////
/// @addtogroup Json
/// @{
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// @brief creates a shape accessor
////////////////////////////////////////////////////////////////////////////////

TRI_shape_access_t* TRI_ShapeAccessor (TRI_shaper_t*,
                                       TRI_shape_sid_t sid,
                                       TRI_shape_pid_t pid);

////////////////////////////////////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
}
#endif

#endif

// Local Variables:
// mode: outline-minor
// outline-regexp: "^\\(/// @brief\\|/// @addtogroup\\|// --SECTION--\\)"
// End:
