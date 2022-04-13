#include <iostream>
#include "curl/curl.h"
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "ZhouHttpClient/HttpClientUtils.h"
#include "ZhouHttpClient/json/json.h"
#include "ZhouHttpClient/data/JsonCoversion.h"
#include "ZhouHttpClient/http/HttpClient.h"

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
int main(int argc, char *argv[])
{
    
  MyPoint* pt = new MyPoint();
	pt->x = 2;
	pt->y = 5;
	HttpClientUtils *httpclientUtil = new HttpClientUtils(JSON_HTTP);
	httpclientUtil->url = "http://192.168.31.84:8088/authenticate/test";
	httpclientUtil->pTransData = pt;
	HttpClient* pHttp = httpclientUtil->GetHttpUtils();
	RespTest *rt = new RespTest();
	pHttp->AddHeader("Authorization: Bearer dbd2b0dc-b55e-4fac-b96c-a5222f707bef");
	pHttp->Post(rt);
	std::cout<< rt->toJson().c_str() <<std::endl;
  return 0;
}
