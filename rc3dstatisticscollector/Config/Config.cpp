/**
 * @file Config.cpp
 * Implementation the Config class.
 * 
 * @author Andreas <aseek@cs.miami.edu>
 */
#include "Config.h"

#include <cstdio>
#include <cstring>
#include <map>
#include "CfgValueMap.h"


Config::Config(const char* configname)
{
  this->configname = configname;
  this->configpath = "";
  loaded = false;
  values = NULL;
}

Config::Config(const char* configname, const char* configpath)
{
  this->configname = configname;
  this->configpath = configpath;
  loaded = false;
  values = NULL;
}

Config::~Config()
{
  if(values != NULL)
  {
    if(values->modified)
      save();
    delete values;
  }
}


void Config::load()
{
  loaded = true;
  values = new CfgValueMap(configname);
  
  char filename[128];
  const char* a = "";

  if(strcmp(configpath.c_str(),a))
	  sprintf(filename, "%s.cfg", configname.c_str());
  else
	  sprintf(filename, "%s/%s.cfg", configpath.c_str(), configname.c_str());

  FILE *f = fopen(filename, "r");
  if(f == NULL)
    return;
  
  char line[10000];
  line[9999] = 0;
  while(fgets(line, 9999, f))
  {
    line[strlen(line)-1] = 0;
    char *p = strstr(line, "=");
    if(p != NULL && line[0] != '#')
    {
      *p = 0;
      p++;
      values->insert(std::make_pair(std::string(line),std::string(p))); 
    }
  }
  
  fclose(f);
}


void Config::save()
{
  char filename[128];
  sprintf(filename, "config/%s.cfg", configname.c_str());
  FILE *f = fopen(filename, "w");
  if(f == NULL)
    return;

  std::map<std::string, std::string> sortedMap;
  
  //insert all values in sortedMap
  CfgMapType<std::string, std::string>::iterator iter = values->begin();
  while(iter != values->end())
  {
    sortedMap.insert(*iter);
    iter++;
  }

  //write all values to file
  std::map<std::string, std::string>::iterator iterSorted = sortedMap.begin();
  while(iterSorted != sortedMap.end())
  {
    fprintf(f, "%s=%s\n",
            iterSorted->first.c_str(), iterSorted->second.c_str()); 
    iterSorted++;
  }
  fclose(f);
}



//------------------------
//getValue methods
bool   Config::getValue(const char* name, bool   defaultValue)
{
  if(!loaded) load();
  return values->getConfigValue(name, defaultValue);
};
int    Config::getValue(const char* name, int    defaultValue)
{
  if(!loaded) load();
  return values->getConfigValue(name, defaultValue);
};
/*long   Config::getValue(const char* name, long   defaultValue)
{
  if(!loaded) load();
  return values->getConfigValue(name, defaultValue);
};*/
float  Config::getValue(const char* name, float  defaultValue)
{
  if(!loaded) load();
  return values->getConfigValue(name, defaultValue);
};
double Config::getValue(const char* name, double defaultValue)
{
  if(!loaded) load();
  return values->getConfigValue(name, defaultValue);
};
std::string Config::getValue(const char* name, std::string defaultValue)
{
  if(!loaded) load();
  return values->getConfigValue(name, defaultValue);
};

bool   Config::getValue(std::string name, bool   defaultValue)
{
  if(!loaded) load();
  return getValue(name.c_str(), defaultValue);
};
int    Config::getValue(std::string name, int    defaultValue)
{
  if(!loaded) load();
  return getValue(name.c_str(), defaultValue);
};
/*long   Config::getValue(std::string name, long   defaultValue)
{
  return getValue(name.c_str(), defaultValue);
};*/
float  Config::getValue(std::string name, float  defaultValue)
{
  if(!loaded) load();
  return getValue(name.c_str(), defaultValue);
};
double Config::getValue(std::string name, double defaultValue)
{
  if(!loaded) load();
  return getValue(name.c_str(), defaultValue);
};
std::string Config::getValue(std::string name, std::string defaultValue)
{
  if(!loaded) load();
  return getValue(name.c_str(), defaultValue);
};

//------------------------
//setValue methods
void Config::setValue(const char* name, bool   value)
{ if(!loaded) load(); values->setConfigValue(name, value); }
void Config::setValue(const char* name, int    value)
{ if(!loaded) load(); values->setConfigValue(name, value); }
void Config::setValue(const char* name, long   value)
{ if(!loaded) load(); values->setConfigValue(name, value); }
void Config::setValue(const char* name, float  value)
{ if(!loaded) load(); values->setConfigValue(name, value); }
void Config::setValue(const char* name, double value)
{ if(!loaded) load(); values->setConfigValue(name, value); }
void Config::setValue(const char* name, std::string value)
{ if(!loaded) load(); values->setConfigValue(name, value); }

