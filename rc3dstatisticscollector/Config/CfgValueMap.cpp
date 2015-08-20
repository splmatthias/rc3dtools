/**
 * @file CfgValueMap.cpp
 * 
 * @author Andreas <aseek@cs.miami.edu>
 */

#include "CfgValueMap.h"


CfgMapType<std::string, CfgMapType<std::string, std::string> >
  CfgValueMap::overwriteValues;


CfgValueMap::CfgValueMap(std::string name) : name(name), modified(false)
{
  overwriteMap = overwriteValues[name];
}

CfgValueMap::~CfgValueMap()
{
  //free memory used to store values in cache
  for(CacheType::iterator iter = cache.begin(); iter != cache.end(); iter++)
    if(iter->second.data != NULL)
    {
      if(iter->second.dataIsString)
        delete (std::string*)(iter->second.data);
      else
        delete[] (char*)(iter->second.data);
    }
  cache.clear();
}
