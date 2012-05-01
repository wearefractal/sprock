#include "Sprock.h"
#include <stdio.h>

using namespace v8;
using namespace node;

Persistent<FunctionTemplate> Sprock::s_ct;

void Sprock::Initialize(Handle<Object> target)
{
    HandleScope scope;
    s_ct = Persistent<FunctionTemplate>::New(FunctionTemplate::New(New));
    s_ct->SetClassName(NODE_SYMBOL("Sprock"));

    Local<ObjectTemplate> proto = s_ct->PrototypeTemplate();

    Local<ObjectTemplate> instance = s_ct->InstanceTemplate();
    instance->SetInternalFieldCount(1);
    instance->SetNamedPropertyHandler(GetNamedProperty, SetNamedProperty, QueryNamedProperty);

    target->ForceSet(NODE_SYMBOL("Sprock"), s_ct->GetFunction());
}

Handle<Value> Sprock::New (const Arguments &args)
{
    HandleScope scope;
    if (!args.IsConstructCall())
    {
        return ThrowException(Exception::TypeError(NODE_SYMBOL("Use the new operator to create instances of this object.")));
    }
    ARG_CHECK_OBJECT(0, target);
    ARG_CHECK_FUNCTION(1, trap);
    Persistent<Object> target = Persistent<Object>::New(Handle<Object>::Cast(args[0]->ToObject()));
    Persistent<Function> trap = Persistent<Function>::New(Handle<Function>::Cast(args[1]));
    Sprock *inst = new Sprock();
    inst->target = target;
    inst->trap = trap;
    inst->Wrap(args.This());

    return scope.Close(args.This());
}

/* FUNCTIONS */
Handle<Value> Sprock::GetNamedProperty(Local<String> name, const AccessorInfo &info) {
    HandleScope scope;
    Sprock *inst = ObjectWrap::Unwrap<Sprock>(info.This());
    assert(inst);
    assert(inst->trap->IsFunction());
    assert(inst->target->IsObject());
    
    Handle<Object> obj = Object::New();
    obj->Set(NODE_SYMBOL("type"), NODE_SYMBOL("get"));
    obj->Set(NODE_SYMBOL("property"), name);
    Handle<Value> fnargs[1];
    fnargs[0] = obj;

    return scope.Close(inst->trap->Call(inst->target, 1, fnargs));
}
Handle<Value> Sprock::SetNamedProperty(Local<String> name, Local<Value> value, const AccessorInfo &info) {
    HandleScope scope;
    Sprock *inst = ObjectWrap::Unwrap<Sprock>(info.This());
    assert(inst);
    assert(inst->trap->IsFunction());
    assert(inst->target->IsObject());

    Handle<Object> obj = Object::New();
    obj->Set(NODE_SYMBOL("type"), NODE_SYMBOL("set"));
    obj->Set(NODE_SYMBOL("property"), name);
    obj->Set(NODE_SYMBOL("value"), value);
    Handle<Value> fnargs[1];
    fnargs[0] = obj;

    return scope.Close(inst->trap->Call(inst->target, 1, fnargs));
}
Handle<Integer> Sprock::QueryNamedProperty(Local<String> name, const AccessorInfo &info) {
    HandleScope scope;
    Sprock *inst = ObjectWrap::Unwrap<Sprock>(info.This());
    assert(inst);
    assert(inst->trap->IsFunction());
    assert(inst->target->IsObject());

    return scope.Close(NODE_CONSTANT(None));
}

extern "C" {
    static void init (Handle<Object> target)
    {
        HandleScope scope;
        Sprock::Initialize(target);
    }

    NODE_MODULE(Sprock, init);
}
