#include "DownloadFile.h"
#ifdef __unix
#include "curl/curl.h"

#define fopen_s(pFile,filename,mode) ((*(pFile))=fopen((filename),  (mode)))==NULL
#else
#include "curl-mfc/curl.h"
#endif

DownloadFile::DownloadFile(string url ,string savePath)
:HttpClient(url,nullptr)
,outfile(nullptr)
,fileSavedPath(savePath)
{
    //ctor
}

DownloadFile::~DownloadFile()
{
    //dtor
}
size_t DownloadFile::DownloadCallback(void* pBuffer, size_t nSize, size_t nMemByte, void *stream)
{
    DownloadFile * pThis = (DownloadFile*)stream;
    FILE * pp = pThis->getWriteFile();
    size_t nWrite = fwrite(pBuffer, nSize, nMemByte, pp);
    return nWrite;
}

int DownloadFile::ProgressCallback(char *progress_data,
                     double t, /* dltotal */
                     double d, /* dlnow */
                     double ultotal,
                     double ulnow)
{
  printf("%s %g / %g (%g %%)\n", progress_data, d, t, d*100.0/t);
  return 0;
}

int DownloadFile::Get(JsonCoversion* pJsonBack)
{	
	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
    fopen_s(&outfile,fileSavedPath.c_str(), "wb");  
    curl_easy_setopt((CURL*)curl, CURLOPT_URL, strUrl.c_str());
    curl_easy_setopt((CURL*)curl, CURLOPT_WRITEFUNCTION, DownloadCallback);
    //curl_easy_setopt((CURL*)curl, CURLOPT_MAXREDIRS, 5);
    //// 设置301、302跳转跟随location
    curl_easy_setopt((CURL*)curl, CURLOPT_FOLLOWLOCATION, 1);
    curl_easy_setopt((CURL*)curl, CURLOPT_PROGRESSFUNCTION, ProgressCallback);

    curl_easy_setopt((CURL*)curl, CURLOPT_WRITEDATA, this);
	res = curl_easy_perform(curl);

    const char* pError = curl_easy_strerror(CURLcode(res));
	long http_code = 0;
	curl_easy_getinfo((CURL*)curl, CURLINFO_RESPONSE_CODE, &http_code);
	if (200 == http_code) {

	}
    fclose(outfile);
    outfile = NULL;
    bool bResult(false);
    if(CURLE_OK == res)
    {
        bResult = true;
    }
    return bResult;
}
