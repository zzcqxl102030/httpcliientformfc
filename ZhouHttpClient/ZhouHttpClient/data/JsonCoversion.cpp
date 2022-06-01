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

bool JsonCoversion::WriteDataToFile(string filePath) {
 bool bResult = true;
 try
 {
  toJsonValue();
  std::string jsonStr;
  std::ostringstream os;
  std::unique_ptr<Json::StreamWriter> jsonWriter(writerBuilder.newStreamWriter());
  jsonWriter->write(root, &os);
  jsonStr = os.str();

  ofstream outfile(filePath);
  outfile << jsonStr;
  outfile.close();
 }
 catch (const std::exception&)
 {
  bResult = false;
 }
 return bResult;

}
bool JsonCoversion::loadDataFromFile(string filePath) {
 std::ifstream is;
 is.open(filePath, std::ios::binary);
 readerBuilder["collectComments"] = true;
 JSONCPP_STRING errs;
 if (!parseFromStream(readerBuilder, is, &root, &errs)) {
  std::cout << errs << std::endl;
  return false;
 }
 toObjectFromValue(root);
 return true;
}
