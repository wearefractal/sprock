#ifndef Sprock_H_
#define Sprock_H_

#include <v8.h>
#include <node.h>
#include "node_defs.h"

#include <stdlib.h>
#include <assert.h>

using namespace v8;
using namespace node;

class Sprock : public ObjectWrap
{
public:
    static Handle<Value> New(const Arguments &args);
    static void Initialize(Handle<Object> target);
    static Handle<Value> GetNamedProperty(Local<String> name, const AccessorInfo &info);
private:
    Sprock() : ObjectWrap() {};
    ~Sprock() {};
    Persistent<Function> trap;
    Persistent<Object> target;
    static Persistent<FunctionTemplate> s_ct;
};

#endif  // Sprock_H_
