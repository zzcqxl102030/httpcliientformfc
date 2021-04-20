#include "pch.h"
#include "HttpClientUtils.h"
#include "data/JsonCoversion.h"
#include "http/DownloadFile.h"
#include "http/HttpClient.h"
#include "http/UploadFiles.h"
HttpClientUtils::HttpClientUtils(UtilsType type) {
	httpType = type;
	pTransData = nullptr;
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
