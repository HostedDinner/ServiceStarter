/* 
 * File:   ConfigParser.cpp
 * Author: Fabian
 * 
 * Created on 12. Februar 2017, 21:37
 */

#ifndef UNICODE
    #define UNICODE
#endif
#ifndef _UNICODE
    #define _UNICODE
#endif

#include "ConfigParser.h"

#include <io.h>
#include <cstdlib>

#include "tinyxml2/tinyxml2.h"


ConfigParser::ConfigParser(std::wstring filename) {
    this->filename = filename;
    this->serviceConfigs = std::list<std::pair<std::wstring, std::wstring>>();
    
    this->parse();
}

ConfigParser::~ConfigParser() {
}

std::list<std::pair<std::wstring, std::wstring>> *ConfigParser::pGetServiceConfigs() {
    return &this->serviceConfigs;
}


void ConfigParser::parse() {
    
    using namespace tinyxml2;
    
    //we have to open the file by ourself, because we want to support _wfopen
    FILE *file = _wfopen(this->filename.c_str(), L"rb");
    
    if(file != NULL){
        
        XMLDocument doc;
        doc.LoadFile(file);
        
        XMLElement *list = doc.FirstChildElement("servicestarter")->FirstChildElement("servicelist");
        
        if(list != NULL){
            XMLElement *element = list->FirstChildElement("service");
            
            while(element != NULL){
                
                const char *mname = element->FirstChildElement("name")->GetText();
                const char *mlabel = element->FirstChildElement("label")->GetText();

                std::wstring name(ConfigParser::MtoW(mname));
                std::wstring label(ConfigParser::MtoW(mlabel));

                this->serviceConfigs.push_back(std::make_pair(name, label));


                element = element->NextSiblingElement("service");
            }
        }
        
        fclose(file);
    }
}

std::wstring ConfigParser::MtoW(std::string input) {
    size_t length = input.length();
    wchar_t *wcstr = new wchar_t[length+1]; //widestring is at most that long
    std::size_t r = mbstowcs(wcstr, input.c_str(), length+1);
    if(r != -1){
        std::wstring result(wcstr);
        delete [] wcstr;
        return result;
    }else{
        delete [] wcstr;
        return L"";
    }
}

