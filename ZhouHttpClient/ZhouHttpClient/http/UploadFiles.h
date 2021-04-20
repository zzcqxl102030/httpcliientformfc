#ifndef UPLOADFILES_H
#define UPLOADFILES_H
#include <iostream>
#include <string.h>
#include <vector>

#include "HttpClient.h"
using namespace std;
class FilesVec {
public:
	string key;
	string fileName;
	void * pBuf;
	long lengh;

};
class JsonCoversion;
class UploadFiles :public HttpClient
{
public:
	UploadFiles(string url, JsonCoversion* pData, vector<FilesVec*> vecFiles, bool bLocalFile = true, int timeDuring = 10);
	virtual ~UploadFiles();
protected:
	virtual void InitTransData();
protected:
	vector<FilesVec*> vecFileData;
	bool bLocal;
private:
	void InitLocalFileData();
	void InitMemFileData();
};

#endif // UPLOADFILES_H
