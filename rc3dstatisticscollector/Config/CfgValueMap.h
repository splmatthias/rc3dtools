/**
 * @file CfgValueMap.h
 * CfgValueMap class for storing config values.
 * 
 * @author Andreas <aseek@cs.miami.edu>
 */

#ifndef CFGVALUEMAP_H
#define CFGVALUEMAP_H

#define CfgMapType unordered_map
#include "StringHashMap.h"

#include <map>
#include <iostream>
#include <sstream>


/** 
 * Stores config values as strings.
 */
class CfgValueMap : public CfgMapType<std::string, std::string>
{
  private:
  
    std::string name;
    CfgMapType<std::string, std::string> overwriteMap;
    
    //Cache is used for faster reading, getConfigValue is called very often
    class CacheEntry
    {
      public:
        CacheEntry() : data(NULL), dataIsString(false), modifyName("") {}
        CacheEntry(void *d, bool isStr) 
          : data(d), dataIsString(isStr), modifyName("") {}
        CacheEntry(void *d, bool isStr, const std::string &str) 
          : data(d), dataIsString(isStr), modifyName(str) {}
        void* data;
        bool dataIsString;
        std::string modifyName;
    };
    //typedef std::map<std::string, CacheEntry> CacheType;
    typedef CStringHashMap<CacheEntry> CacheType;
    CacheType cache;

  public:
  
    CfgValueMap(std::string name);
    ~CfgValueMap();
  
    static CfgMapType<std::string, CfgMapType<std::string, std::string> >
      overwriteValues;

    bool modified;

    /** Template method to read a value. */
    template<class T> T getConfigValue(const char* name, const T& defaultValue)
    {
      //check cache first
      CacheType::iterator cacheIter = cache.find(name);
      if(cacheIter != cache.end())
      {
        T& value = *((T*)(cacheIter->second.data));
        return value;
      }
      //if not in cache, get value from map
      CacheEntry *cacheEntry = moveValueToCache(name, defaultValue);
      cacheEntry->modifyName = std::string("config:") + this->name + ":" + name;
      return *((T*)(cacheEntry->data));
    }
  
    /** Template method to set a value. */
    template<class T> void setConfigValue(const char* name, const T& value)
    {
      //set value in cache, if it exists
      CacheType::iterator cacheIter = cache.find(name);
      if(cacheIter != cache.end())
        *((T*)(cacheIter->second.data)) = value;
      //set value in map 
      std::ostringstream s;
      s << value;
      (*this)[name] = s.str();
      modified = true;
    }
    
  private:
  
    /**
     * Method to read and convert strings from the config value map.
     */
    template<class T> 
    CacheEntry* moveValueToCache(const char* name, const T& defaultValue)
    {
      std::string valueString = "";
      valueString = overwriteMap[name];
      if(valueString == "")
        valueString = (*this)[name];
      T *value = (T*)(new char[sizeof(T)]);
      if(valueString != "")
      {
        std::stringstream stream(valueString);
        stream >> *value;
      }
      else
      {
        setConfigValue(name, defaultValue);
        *value = defaultValue;
      }
      return &(cache[name] = CacheEntry(value, false));
    }

    /** 
     * Specialized method for std::string.
     * The stringstream in the generic method would split strings at spaces.
     */
    CacheEntry* moveValueToCache(const char* name, const std::string& defaultValue)
    {
      std::string valueString = "";
      valueString = overwriteMap[name];
      if(valueString == "")
        valueString = (*this)[name];
      std::string *value = new std::string();
      if(valueString != "")
      {
        *value = valueString;
      }
      else
      {
        setConfigValue(name, defaultValue);
        *value = defaultValue;
      }
      return &(cache[name] = CacheEntry(value, true));
    }
    
};


#endif
