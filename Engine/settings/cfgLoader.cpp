#include "cfgLoader.h"
#include <fstream>

CfgLoader::CfgLoader()
{

}

CfgLoader::~CfgLoader()
{

}

CfgLoader::CfgLoader(const CfgLoader& other)
{
    *this = other;
}

CfgLoader& CfgLoader::operator=(const CfgLoader& other)
{
    cfgData = other.cfgData;

    return *this;
}

const char* CfgLoader::operator[] (const char* key)
{
    return get(key);
}

//--------------------------------------------------------------------------
int countChar(const char* str, const char ch, int* firstOccurance)
{
   int count;

   count = 0;
   for(int i = 0 ; *str ; i++, str++)
   {
       if(*str == ch)
       {
           count++;
           *firstOccurance = i;
       }
   }

   return count;
}

bool CfgLoader::init(const char* path)
{
    std::ifstream cfgFile(path);
    if(!cfgFile.is_open())
        return false;

    std::string temp;
    int valPosition = 0;
    while(std::getline(cfgFile, temp))
    {
        if(temp[0] == '#' || temp[0] == '\0')
            continue;
        if(countChar(temp.c_str(), '=', &valPosition) != 1 || temp[0] == '=')
            return false;

        cfgData.insert(std::pair<std::string, std::string>(temp.substr(0, valPosition), temp.substr(valPosition + 1)));
    }

    cfgFile.close();
    return true;
}

const char* CfgLoader::get(const char* key)
{
    return cfgData[key].c_str();
}