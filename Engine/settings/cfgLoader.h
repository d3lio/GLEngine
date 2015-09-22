#pragma once
#ifndef _CFGLOADER_H_
#define _CFGLOADER_H_
#include <map>
#include <string>
class CfgLoader
{
public:
    CfgLoader();
    ~CfgLoader();
    CfgLoader(const CfgLoader& other);
    CfgLoader& operator=(const CfgLoader& other);
    const char* operator[](const char* key);

    bool init(const char* path);
    const char* get(const char* key);
private:
    std::map<std::string, std::string> cfgData;
};
#endif