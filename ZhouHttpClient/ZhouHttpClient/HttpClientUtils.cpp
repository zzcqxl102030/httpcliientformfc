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
	timeDuring = 10;
}
HttpClientUtils::~HttpClientUtils() {

}
HttpClient * HttpClientUtils::GetHttpUtils() {
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
	return pHttpClient;
}
