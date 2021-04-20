#ifndef JsonCoversion_H
#define JsonCoversion_H
#include<iostream>
#include<memory>
#include<string>
#include "../json/json.h"

using namespace std;

class JsonCoversion
{
    protected:	
        Json::Value root;
		
        // Json::FastWriter writer;				//弃用 改用StreamWriterBuilder
        Json::StreamWriterBuilder writerBuilder;
		
		// Json::Reader reader;		//弃用	改用CharReaderBuilder
		Json::CharReaderBuilder readerBuilder;
		map<string, string> mapData;
    public:
        JsonCoversion();
        virtual ~JsonCoversion();
		map<string, string> &ToMapData() { LoadMapData(); return mapData; }
    protected:
    public:
        string toJson();
        string toJson(Json::Value &root);
		void toObject(string & strBuf);
		/*virtual map<string,*/
    protected:
		virtual void LoadMapData() {}
        virtual Json::Value  toJsonValue() = 0;
		virtual void toObjectFromValue(Json::Value root) = 0;
};

#endif // JsonCoversion_H
