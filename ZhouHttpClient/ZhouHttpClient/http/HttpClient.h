#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H
#include <iostream>
#include <string.h>
#include <sstream>


using namespace std;
class JsonCoversion;
class HttpClient
{
    public:
        HttpClient(string url, JsonCoversion* pData,int timeDuring = 10);
        virtual ~HttpClient();
    public:
       virtual  int Post(JsonCoversion* pJsonBack);
	   virtual  int Get(JsonCoversion* pJsonBack = nullptr);
	   string out;
	public:
	   virtual void AddHeader(string strHeaderInfo);
    protected:
		string jsonTrans;
		JsonCoversion *pDataTrans;
        string strUrl;
        void *curl;
        int res;
		
		struct curl_slist *headerlist;
		int timeOut;
		//when use form data use  the below parameter
		struct curl_forms *forms;
		struct curl_httppost *formpost;
		struct curl_httppost *lastptr;
    protected:
		void InitCallBackData();
		void GetResponse(JsonCoversion* pJsonBack);
		static size_t WriteToStrResponse(void* data, size_t size, size_t nmemb, void* content);
		virtual  void InitTransData();
    private:
		
		string AsciiToUtf8(const string &str);
		int Send(JsonCoversion *pJsonBack,bool bPost = true);
        class HttpEnv
        {
        public:
			HttpEnv();
			~HttpEnv();
        };
        static HttpEnv httpEnv;
};

#endif // HTTPCLIENT_H
