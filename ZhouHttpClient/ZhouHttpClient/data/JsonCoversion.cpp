#include "JsonCoversion.h"


JsonCoversion::JsonCoversion()
{
    //ctor
}

JsonCoversion::~JsonCoversion()
{
    //dtor
}
string JsonCoversion::toJson()
{
	toJsonValue();
	
	std::unique_ptr<Json::StreamWriter> jsonWriter(writerBuilder.newStreamWriter());

	//writerBuilder.settings_["indentation"] = "";
	std::ostringstream os;
	std::string jsonStr;
	jsonWriter->write(root,&os);
	jsonStr = os.str();
    return jsonStr;
}

string JsonCoversion::toJson(Json::Value &val)
{
    root = val;
    return toJson();
}

void JsonCoversion::toObject(string & strBuf)
{
	std::unique_ptr<Json::CharReader> const jsonReader(readerBuilder.newCharReader());
	
	JSONCPP_STRING errs;
	bool res = jsonReader->parse(strBuf.c_str(), strBuf.c_str()+strBuf.length(), &root, &errs);
	if (!res || !errs.empty())
	{
        std::cout << "parseJson err. " << errs << std::endl;
	}
	toObjectFromValue(root);
}
