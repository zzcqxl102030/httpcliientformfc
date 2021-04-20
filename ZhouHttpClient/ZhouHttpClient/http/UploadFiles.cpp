
#include "UploadFiles.h"
#include "../data/JsonCoversion.h"
#include "curl/curl.h"

UploadFiles::UploadFiles(string url, JsonCoversion* pData,vector<FilesVec*> vecFiles,bool bLocalFile,int timeDuring)
:HttpClient(url, pData, timeDuring)
,vecFileData(vecFiles)
,bLocal(bLocalFile)
{
    //ctor
}

UploadFiles::~UploadFiles()
{
    //dtor
}
void UploadFiles::InitLocalFileData() {
	if (nullptr != forms)
	{
		delete forms;
	}
	vector<FilesVec*> vecFilesWithoutKey;
	for (int i = 0; i < vecFileData.size(); i++)
	{
		if (vecFileData[i]->key.empty())
		{
			vecFilesWithoutKey.push_back(vecFileData[i]);
		}
		else {
			curl_formadd(&formpost,
				&lastptr,
				CURLFORM_PTRNAME, vecFileData[i]->key.c_str(),
				CURLFORM_FILE, vecFileData[i]->fileName.c_str(),
				CURLFORM_END);

		}
	}
	if (NULL < vecFilesWithoutKey.size())
	{
		forms = new curl_forms[vecFilesWithoutKey.size() + 1];
		for (int i = 0; i < vecFilesWithoutKey.size(); i++)
		{
			forms[i].option = CURLFORM_FILE;
			forms[i].value = vecFilesWithoutKey[i]->fileName.c_str();
		}
		forms[vecFilesWithoutKey.size()].option = CURLFORM_END;
		/* Fill in the file upload field */
		curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "files",
			CURLFORM_ARRAY, forms, CURLFORM_END);
	}
}
void UploadFiles::InitMemFileData() {
	if (nullptr != forms)
	{
		delete forms;
	}
	vector<FilesVec*> vecFilesWithoutKey;
	for (int i = 0; i < vecFileData.size(); i++)
	{
		if (vecFileData[i]->key.empty())
		{
			vecFilesWithoutKey.push_back(vecFileData[i]);
		}
		else {
			curl_formadd(&formpost, &lastptr,
				CURLFORM_PTRNAME, vecFileData[i]->key.c_str(),
				CURLFORM_BUFFER, vecFileData[i]->fileName.c_str(),
				CURLFORM_BUFFERPTR, vecFileData[i]->pBuf,
				CURLFORM_BUFFERLENGTH, vecFileData[i]->lengh,
				CURLFORM_END);
		}
	}
	if (NULL < vecFilesWithoutKey.size())
	{
		forms = new curl_forms[vecFilesWithoutKey.size() + 1];
		for (int i = 0; i < vecFilesWithoutKey.size(); i++)
		{
			forms[i].option = CURLFORM_BUFFER;
			forms[i].value = (char*)vecFilesWithoutKey[i]->pBuf;
		}
		forms[vecFilesWithoutKey.size()].option = CURLFORM_END;
		/* Fill in the file upload field */
		curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "files",
			CURLFORM_ARRAY, forms, CURLFORM_END);
	}
}
void UploadFiles::InitTransData()
{
	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
	
     if(bLocal)
     {
		 InitLocalFileData();
     }
     else
     {
		 InitMemFileData();
     }
	 map<string, string> &mapData = pDataTrans->ToMapData();
	 map<string, string>::iterator iter = mapData.begin();
	 while (iter != mapData.end())
	 {
		 curl_formadd(&formpost,
			 &lastptr,
			 CURLFORM_COPYNAME, iter->first.c_str(),
			 CURLFORM_COPYCONTENTS, iter->second.c_str(),
			 CURLFORM_END);
		 iter++;
	 }
	 curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
	 static const char buf[] = "Expect:";
	headerlist = curl_slist_append(headerlist, buf);
	 curl_easy_setopt((CURL*)curl, CURLOPT_HTTPHEADER, headerlist);
}
