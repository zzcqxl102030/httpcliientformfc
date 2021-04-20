#ifndef DOWNLOADFILE_H
#define DOWNLOADFILE_H
#include <iostream>
#include <string.h>
#include <vector>
#include "HttpClient.h"

class DownloadFile  : public HttpClient
{
    public:
        DownloadFile(string url ,string savePath);
        virtual ~DownloadFile();
    public:
        virtual int Get(JsonCoversion* pJsonBack = nullptr);
        static  int ProgressCallback(char *progress_data,
                     double t, /* dltotal */
                     double d, /* dlnow */
                     double ultotal,
                     double ulnow);
        static size_t DownloadCallback(void* pBuffer, size_t nSize, size_t nMemByte, void *stream);
        FILE *getWriteFile(){return outfile;}
    protected:
    private:
        string fileSavedPath;
        FILE *outfile;
};

#endif // DOWNLOADFILE_H
