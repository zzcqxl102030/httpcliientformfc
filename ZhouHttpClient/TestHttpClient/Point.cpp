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
