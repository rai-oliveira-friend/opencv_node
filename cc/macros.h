#include "matUtils.h"
#include <iostream>

#ifndef FF_MACROS_H_
#define FF_MACROS_H_

#define FF_V8STRING(s) \
	Nan::New(s).ToLocalChecked()

#define FF_JS_VAL_TO_STRING(s) \
	std::string(*Nan::Utf8String(s->ToString()))

#define FF_GETTER(clazz, name, value)	\
	NAN_GETTER(name) { info.GetReturnValue().Set(Nan::ObjectWrap::Unwrap<clazz>(info.This())->value); }

#define FF_SET_JS_PROP(obj, prop, val) \
	Nan::Set(obj, FF_V8STRING(#prop), val)

#define FF_HAS_JS_PROP(obj, prop) \
	Nan::HasOwnProperty(obj, FF_V8STRING(#prop)).FromJust()

/* unchecked js prop getters */

#define FF_GET_JSPROP(obj, prop) \
	Nan::Get(obj, FF_V8STRING(#prop)).ToLocalChecked()

#define FF_GET_JSPROP_NUMBER(obj, prop) \
	FF_GET_JSPROP(obj, prop)->NumberValue()

#define FF_GET_JSPROP_OBJECT(obj, prop) \
	FF_GET_JSPROP(obj, prop)->ToObject()

#define FF_GET_JSPROP_FLOAT(obj, prop) \
	(float)FF_GET_JSPROP_NUMBER(obj, prop)

#define FF_GET_JSPROP_DOUBLE(obj, prop) \
	(double)FF_GET_JSPROP_NUMBER(obj, prop)

#define FF_GET_JSPROP_INT(obj, prop) \
	(int)FF_GET_JSPROP(obj, prop)->IntegerValue()

#define FF_GET_JSPROP_UINT(obj, prop) \
	(uint)FF_GET_JSPROP(obj, prop)->Uint32Value()

#define FF_GET_JSPROP_STRING(obj, prop) \
	FF_JS_VAL_TO_STRING(FF_GET_JSPROP(obj, prop)->ToString())


/* checked js prop getters */

#define FF_GET_JSPROP_IFDEF(obj, var, prop, castType)	\
	if (FF_HAS_JS_PROP(obj, prop)) {										\
		FF_GET_JSPROP(obj, var, prop, castType)						\
	}

#define FF_DESTRUCTURE_JSPROP_IFDEF(obj, prop, castType)	\
	FF_GET_JSPROP_IFDEF(obj, prop, prop, castType)

#define FF_GET_JSPROP_REQUIRED(obj, var, prop, castType)																	\
	if (!FF_HAS_JS_PROP(obj, prop)) {																												\
		return Nan::ThrowError(FF_V8STRING("Object has no property: " + std::string(#prop)));	\
	}																																												\
	var = FF_GET_JSPROP(obj, prop)->castType();																																										

#define FF_DESTRUCTURE_JSPROP_REQUIRED(obj, prop, castType)	\
	FF_GET_JSPROP_REQUIRED(obj, prop, prop, castType)

#define FF_GET_TYPECHECKED_JSPROP(obj, var, prop, assertType, castType)			\
	if (!FF_GET_JSPROP(obj, prop)->assertType()) {														\
		return Nan::ThrowError(FF_V8STRING(																			\
			"Invalid type for " + std::string(#prop) + " :"												\
			+ FF_GET_JSPROP_STRING(obj, prop)																			\
			+ ", expected: " + #assertType																				\
		));																																			\
	}																																					\
	var = FF_GET_JSPROP(obj, prop)->castType();															

#define FF_GET_TYPECHECKED_JSPROP_REQUIRED(obj, var, prop, assertType, castType)					\
	if (!FF_HAS_JS_PROP(obj, prop)) {																												\
		return Nan::ThrowError(FF_V8STRING("Object has no property: " + std::string(#prop)));	\
	}																																												\
	FF_GET_TYPECHECKED_JSPROP(obj, var, prop, assertType, castType)

#define FF_DESTRUCTURE_TYPECHECKED_JSPROP_REQUIRED(obj, prop, assertType, castType)	\
	FF_GET_TYPECHECKED_JSPROP_REQUIRED(obj, prop, prop, assertType, castType)

#define FF_GET_TYPECHECKED_JSPROP_IFDEF(obj, var, prop, assertType, castType)	\
	if (FF_HAS_JS_PROP(obj, prop)) {																						\
		FF_GET_TYPECHECKED_JSPROP(obj, var, prop, assertType, castType)						\
	}

#define FF_DESTRUCTURE_TYPECHECKED_JSPROP_IFDEF(obj, prop, assertType, castType)	\
	FF_GET_TYPECHECKED_JSPROP_IFDEF(obj, prop, prop, assertType, castType)


#define FF_TRY(work)																					\
	try {																												\
		work																											\
	} catch (std::exception &e) {																\
		return info.GetReturnValue().Set(Nan::Error(e.what()));		\
	} catch (...) {																							\
		return info.GetReturnValue().Set(Nan::Error("SEGFAULT"));	\
	}

#define FF_TRY_CATCH(work)					\
	try {															\
		work														\
	} catch (std::exception &e) {			\
		Nan::ThrowError(e.what());			\
	} catch (...) {										\
		Nan::ThrowError("SEGFAULT");		\
	}	

#define FF_REQUIRE_ARGS_OBJ(methodName)																												\
	if (!info[0]->IsObject()) {																																	\
		return Nan::ThrowError(FF_V8STRING(std::string(methodName) + " - args object required"));	\
	}																																														\
	v8::Local<v8::Object> args = info[0]->ToObject()

#endif