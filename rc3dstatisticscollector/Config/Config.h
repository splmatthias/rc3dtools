/**
 * @file Config.h
 * Contains the Config class.
 * 
 * @author Andreas Seekircher <aseek@cs.miami.edu>
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <string>
class CfgValueMap;

/**
 * The config class.
 * 
 * Every module has an instance of this class to load and save configuration
 * values to a config file. It is declared in the base class.
 * 
 * The code example below reads an integer value from a config file.
 * @code
 *   int x = config.getValue("valuename", 10);
 * @endcode
 * 
 * This method returns the value of the config value with the name "valuename".
 * If the config file or only the value does not exist, it returns the default
 * value (in this case 10).
 * The config objects in the modules are using the module name for the filename.
 * A module MyModule would get the config file config/MyModule.cfg. It is
 * created automatically the first time a config value is used. New values are
 * also added to the file.
 * 
 * For the example above the content of the config file would be:
 * @code
 *   valuename=10
 * @endcode
 * 
 * @author Andreas <aseek@cs.miami.edu>
 */
class Config
{
  public:
  
    /** 
     * Constructor.
     * @param configname The config files name will be [configname].cfg. In the
     *                   modules this is automatically set to the module name.
     */
    Config(const char* configname);
    /** 
     * Constructor.
     * @param configname The config files name will be [configname].cfg. In the
     *                   modules this is automatically set to the module name.
     * @param configpath The config path of the agent.
     */
    Config(const char* configname, const char* configpath);
    /**
     * Destructor. If values have been modified, it calls teh  method save.
     */
    ~Config();
    
    /**
     * Writes all values to the config file.
     */
    void save();
            
    /** Returns a bool parameter. */
    bool   getValue(const char* name, bool   defaultValue);
    /** Returns an int parameter. */
    int    getValue(const char* name, int    defaultValue);
    /** Returns a long parameter. */
    //long   getValue(const char* name, long   defaultValue);
    /** Returns a float parameter. */
    float  getValue(const char* name, float  defaultValue);
    /** Returns a double parameter. */
    double getValue(const char* name, double defaultValue);
    /** Returns a string parameter. */
    std::string getValue(const char* name, std::string defaultValue);

    /** Returns a bool parameter. */
    bool   getValue(std::string name, bool   defaultValue);
    /** Returns an int parameter. */
    int    getValue(std::string name, int    defaultValue);
    /** Returns a long parameter. */
    //long   getValue(std::string name, long   defaultValue);
    /** Returns a float parameter. */
    float  getValue(std::string name, float  defaultValue);
    /** Returns a double parameter. */
    double getValue(std::string name, double defaultValue);
    /** Returns a string parameter. */
    std::string getValue(std::string name, std::string defaultValue);

    /** Sets a bool value. */
    void setValue(const char* name, bool   value);
    /** Sets an int parameter. */
    void setValue(const char* name, int    value);
    /** Sets a long parameter. */
    void setValue(const char* name, long   value);
    /** Sets a float parameter. */
    void setValue(const char* name, float  value);
    /** Sets a double parameter. */
    void setValue(const char* name, double value);
    /** Sets a string parameter. */
    void setValue(const char* name, std::string value);
        
  private:

    /** The path of the config files. */
    std::string configpath;
    /** The name for the config file. Set by the constructor. */
    std::string configname;
    /** 
     * Flag whether the config file has been read already. The first call
     * of one of the get methods loads all values and sets this to true.
     */
    bool loaded;
    /**
     * A map containing all values from the config file as strings. They are
     * converted to the correct type in the get methods.
     */
    CfgValueMap *values;

    /** This method loads all values from the config file to the values map. */
    void load();

};






#endif

