/**
 * @file StringWrapper.h
 * 
 * @author Andreas Seekircher <aseek@cs.miami.edu>
 * 
 */
#pragma once

#include <string>

class StringWrapper
{
  private:
    const char *s;
    bool copied;   //if true, memory has to be freed in the end
  public:

    //constructors/destructor
    StringWrapper(const char* s);
    StringWrapper(const char* s, bool createCopy);
    StringWrapper(const StringWrapper& other);
    ~StringWrapper();

    //conversion to const char*
    operator const char*() const { return s; }

    //allocate own memory and copy content, this is called by copy constructor
    void copy();
};
