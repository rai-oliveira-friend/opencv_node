#include <nan.h>
#include <opencv2/core.hpp>
#include "macros.h"
#include "coreUtils.h"

#ifndef __FF_POINT2_H__
#define __FF_POINT2_H__

class Point2 : public Nan::ObjectWrap {
public:
	cv::Point2d pt;

	static void Init(v8::Local<v8::FunctionTemplate> ctor) {
		FF_PROTO_SET_ADD_SUB_OPERATIONS(ctor);
	}

	static NAN_METHOD(New) {
		Point2* self = new Point2();
		self->Wrap(info.Holder());
		info.GetReturnValue().Set(info.Holder());
	};

	static FF_GETTER(Point2, GetX, pt.x);
	static FF_GETTER(Point2, GetY, pt.y);

	FF_INIT_ADD_SUB_OPERATIONS(Point2, FF_UNWRAP_PT2_AND_GET);

	static NAN_METHOD(Norm) {
		info.GetReturnValue().Set(Nan::New(cv::norm(FF_UNWRAP_PT2_AND_GET(info.This()))));
	}

	static NAN_METHOD(At) {
		FF_ASSERT_INDEX_RANGE(info[0]->Int32Value(), 1, "Point2");
		cv::Point2d ptSelf = Nan::ObjectWrap::Unwrap<Point2>(info.This())->pt;
		const double coords[] = { ptSelf.x, ptSelf.y };
		info.GetReturnValue().Set(coords[info[0]->Uint32Value()]);
	}

  static Nan::Persistent<v8::FunctionTemplate> constructor;
};

#endif