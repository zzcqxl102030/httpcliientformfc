#ifndef HttpClientUtils_H
#define HttpClientUtils_H
#pragma once
#ifdef __unix	
	#define  HttpClientUtilsApi
#else
	#ifdef HTTP_CLIENT_UTILS_EXPORT
	#define HttpClientUtilsApi __declspec(dllexport)
	#else
	#define HttpClientUtilsApi __declspec(dllimport)
	#endif // ExportImageView
#endif
#include <iostream>
#include <string.h>
#include <vector>
enum UtilsType {
	JSON_HTTP,
	UPLOADFILE_HTTP,
	DOWNLOAD_HTTP
};
using namespace std;
class JsonCoversion;
class FilesVec;
class HttpClient;
class HttpClientUtilsApi  HttpClientUtils
{
public:
	HttpClientUtils(UtilsType type);
	~HttpClientUtils();
public:
	HttpClient * GetHttpUtils();
private:
	HttpClient * pHttpClient;
	UtilsType httpType;
public:
	//public data all use
	string url;
	int timeDuring;
	//only dowload file use
	string savePath;
	//both uplodad and normal(HttpClient) use
	JsonCoversion* pTransData;
	//only uplodad used and normal(HttpClient) json data use
	vector<FilesVec*> vecFiles;
	bool bLocalFile;
};
#endif // HttpClientUtils_H
