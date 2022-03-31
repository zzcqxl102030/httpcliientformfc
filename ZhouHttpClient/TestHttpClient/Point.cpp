#include "Point.h"
Json::Value MyPoint::toJsonValue()
{
    root["x"] =  x;//x坐标
    root["y"] =  y;//y坐标
    return  root;
}
void MyPoint::LoadMapData() {
	 
	mapData["x"] = std::to_string(x);
	mapData["y"] = std::to_string(y);

}
void MyPoint::toObjectFromValue(Json::Value root)
{  
     x = root["x"].asInt();
     y = root["y"].asInt();
 
}

Json::Value RespTest::toJsonValue()
{
    root["status"] = status;//x坐标
    root["message"] = message;//y坐标
    root["data"] = data.toJsonValue();
    return  root;
}

void RespTest::toObjectFromValue(Json::Value root)
{
    data.toObjectFromValue(root["data"]);
    status = root["status"].asInt();
    message = root["message"].asString();



}