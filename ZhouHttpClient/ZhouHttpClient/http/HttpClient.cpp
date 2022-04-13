#include "HttpClient.h"
#include "../data/JsonCoversion.h"
#include <codecvt>
#ifdef __unix
#include "curl/curl.h"

#define fopen_s(pFile,filename,mode) ((*(pFile))=fopen((filename),  (mode)))==NULL
#else
#include "curl-mfc/curl.h"
#endif
#include "FuncTool.h"
HttpClient::HttpEnv::HttpEnv() {
	curl_global_init(CURL_GLOBAL_ALL);
}
HttpClient::HttpEnv::~HttpEnv() {
	curl_global_cleanup();
}
HttpClient::HttpClient(string url, JsonCoversion* pData, int timeDuring /*= 10*/)
	:strUrl(url)
	, pDataTrans(pData)
	, timeOut(timeDuring)
{
	headerlist = nullptr;
	forms = nullptr;
	formpost = nullptr;
	lastptr = nullptr;
	curl = curl_easy_init();
	//ctor
}

HttpClient::~HttpClient()
{
	/* always cleanup */
	curl_easy_cleanup((CURL*)curl);
}
int HttpClient::Send(JsonCoversion *pJsonBack, bool bPost/* = TRUE*/) {
	long http_code = 0;
	try
	{
		if (NULL != curl)
		{
			curl_easy_setopt((CURL*)curl, CURLOPT_TIMEOUT, timeOut);
			curl_easy_setopt((CURL*)curl, CURLOPT_URL, strUrl.c_str());
			if (bPost)
			{
				InitTransData();
			}
			InitCallBackData();
			res = curl_easy_perform((CURL*)curl);
			if (res != CURLE_OK)
			{
				printf("curl_easy_perform() failed:%s\n", curl_easy_strerror(CURLcode(res)));
			}
			curl_easy_getinfo((CURL*)curl, CURLINFO_RESPONSE_CODE, &http_code);
			if (200 == http_code)
			{
				GetResponse(pJsonBack);
			}
			curl_slist_free_all(headerlist);
			if (nullptr != formpost)
			{
				curl_formfree(formpost);
			}
		}
	}
	catch (std::exception &ex)
	{
		printf("curl exception %s.\n", ex.what());
	}
	return http_code;
}
int HttpClient::Post(JsonCoversion* pJsonBack)
{
	return Send(pJsonBack);
}
void HttpClient::InitCallBackData() {
	// 设置回调函数
	curl_easy_setopt((CURL*)curl, CURLOPT_WRITEFUNCTION, WriteToStrResponse);
	//设置写数据
	HttpClient * ppp = this;
	curl_easy_setopt(curl, CURLOPT_WRITEDATA,this);
}
void HttpClient::GetResponse(JsonCoversion* pJsonBack) {
	if (nullptr != pJsonBack)
	{
		string str_json = out;//返回请求值 
		pJsonBack->toObject(str_json);
	}
}
size_t HttpClient::WriteToStrResponse(void* data, size_t size, size_t nmemb, void* content)
{
	//string* psResponse = (string*)content;
	HttpClient* pthis = (HttpClient*)content;
	string &outTmp = pthis->out;
	outTmp.append((char*)data, size * nmemb);
	return size * nmemb; 
}
void HttpClient::AddHeader(string strHeaderInfo) {
	headerlist = curl_slist_append(headerlist,strHeaderInfo.c_str());
}
void HttpClient::InitTransData() {
	// 设置http发送的内容类型为JSON
	AddHeader("Content-Type:application/json;charset=UTF-8");
	curl_easy_setopt((CURL*)curl, CURLOPT_HTTPHEADER, headerlist);
	// 设置要POST的JSON数据
#ifdef _WIN32
		// Windows系统
	jsonTrans = AsciiToUtf8(pDataTrans->toJson());
#else
	jsonTrans = pDataTrans->toJson();
#endif	
	curl_easy_setopt((CURL*)curl, CURLOPT_POSTFIELDS, jsonTrans.c_str());

}
int HttpClient::Get(JsonCoversion* pJsonBack) {
	return 	 Send(pJsonBack, false);
}
string HttpClient::AsciiToUtf8(const string &str) {
	std::string result("");
	#if defined(__linux__)
	// Linux系统
	 result = FuncTool::UnicodeToUTF8(FuncTool::ANSIToUnicode(str));
	#elif defined(_WIN32)
		// Windows系统
		int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
		wchar_t * pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴 
		ZeroMemory(pwBuf, nwLen * 2 + 2);
		::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);
		int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);
		char * pBuf = new char[nLen + 1];
		ZeroMemory(pBuf, nLen + 1);
		::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);
		std::string retStr(pBuf);
		result = retStr;
		delete[]pwBuf;
		delete[]pBuf;
		pwBuf = NULL;
		pBuf = NULL;
	#endif	
	return result;
}
