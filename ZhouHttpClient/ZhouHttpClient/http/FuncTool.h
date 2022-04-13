#ifndef FUNC_TOOL_H
#define FUNC_TOOL_H
#include <string>
#include <locale>
#include<codecvt>
#include <iostream>
class FuncTool
{
public:
    FuncTool();
    ~FuncTool();
public:
static std::string UnicodeToUTF8(const std::wstring & wstr);
static std::wstring UTF8ToUnicode(const std::string & str);
static std::string UnicodeToANSI(const std::wstring & wstr);
static std::wstring ANSIToUnicode(const std::string & str);
};
#endif