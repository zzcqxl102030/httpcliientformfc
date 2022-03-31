#ifndef POINT_H
#define POINT_H

#include "data/JsonCoversion.h"
#include <iostream>

using namespace std;

class MyPoint :public JsonCoversion
{
    friend class RespTest;
    protected:
		virtual void LoadMapData();
		virtual Json::Value  toJsonValue() ;
		virtual void toObjectFromValue(Json::Value root);
    public:
        int x;//x坐标
        int y;//y坐标
};

class RespTest :public JsonCoversion
{
protected:
    virtual Json::Value  toJsonValue();
    virtual void toObjectFromValue(Json::Value root);
public:
    MyPoint data;
    int  status;
    string message;
};

#endif // POINT_H
