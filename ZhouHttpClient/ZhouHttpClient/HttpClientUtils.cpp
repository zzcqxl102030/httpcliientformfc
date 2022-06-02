#include "HttpClientUtils.h"
#include "data/JsonCoversion.h"
#include "http/DownloadFile.h"
#include "http/HttpClient.h"
#include "http/UploadFiles.h"

HttpClientUtils::HttpClientUtils(UtilsType type, string url, JsonCoversion* transData, bool bLocal, vector<FilesVec*> vecFile)
{
	httpType = type;
	this->pTransData = transData;
	this->vecFiles = vecFile;
	this->bLocalFile = bLocal;
	this->url = url;
	timeDuring = 10;
	pHttpClient = nullptr;
}
HttpClientUtils::~HttpClientUtils() {

}
void HttpClientUtils::Init() {
	if (nullptr == pHttpClient)
	{
		switch (httpType)
		{
		case UPLOADFILE_HTTP:
		{
			pHttpClient = new  UploadFiles(url, pTransData, vecFiles,
				bLocalFile, timeDuring);
		}
		break;
		case DOWNLOAD_HTTP:
		{
			pHttpClient = new  DownloadFile(url, savePath);
		}
		break;
		case JSON_HTTP:
		default:
		{
			pHttpClient = new  HttpClient(url, pTransData, timeDuring);
		}
		break;
		}
	}
}
void HttpClientUtils::DoHttp(JsonCoversion* pJsonBack) {
	Init();
	switch (httpType)
	{
		case UPLOADFILE_HTTP:
		case JSON_HTTP:
		{
			pHttpClient->Post(pJsonBack);
			break;
		}
		case DOWNLOAD_HTTP:
		default:
		{
			pHttpClient->Get(pJsonBack);
			break;
		}
	}
}
void HttpClientUtils::AddHeader(string  headerData)
{
	Init();
	if (nullptr != pHttpClient)
	{
		pHttpClient->AddHeader(headerData);
	}
}