/* 
 * File:   ConfigPareser.h
 * Author: Fabian
 *
 * Created on 12. Februar 2017, 21:37
 */

#ifndef CONFIGPARESER_H
#define CONFIGPARESER_H

#include <string>
#include <utility>
#include <list>

class ConfigParser {
private:
    std::wstring filename;
    
    std::list<std::pair<std::wstring, std::wstring>> serviceConfigs;
public:
    ConfigParser(std::wstring filename);
    virtual ~ConfigParser();
    
    
    std::list<std::pair<std::wstring, std::wstring>> *pGetServiceConfigs();
    
private:
    void parse();
    
    static std::wstring MtoW(std::string input);
};

#endif /* CONFIGPARESER_H */

