#include "utility.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>

float randomf() {
    float result = (float)rand() / RAND_MAX;
    return result;
}

float randomf(float min, float max) {
    float scale = max - min;
    float result = randomf() * scale + min;
    return result;
}

std::string generateFrameFilename(std::string path, 
                                  std::string extension, 
                                  int max_frames
                                 ) 
{
    static int frame_n = 0;
    if(frame_n > max_frames) 
        return "";
    std::string result = path + std::to_string(frame_n) + extension;
    frame_n++;
    return result;
}


std::vector<std::string> separateString(std::string s) {
    if(s.empty() )
        return std::vector<std::string>();
    
    std::vector<std::string> result;
    std::stringstream ss(s);
    std::string word;
    while(ss >> word)
        result.push_back(word);
    return result;
}


bool settings::load(std::string filename) {
    contents.clear();
    std::ifstream filestream(filename);
    if(filestream.is_open() ) {
        std::string line;
        while(getline(filestream, line)) {
            std::vector<std::string> words = separateString(line);
            
            if(words.size() == 0)
                continue;
            else if (words[0][0] == '#') //exclude comment
                continue;
            else if (words.size() == 1)
                words.push_back("");
            
            this->set(words[0], words[1]);
            std::cout << "read parameter " << words[0] << " : " << words[1] << "\n";
        }
        
        filestream.close();
        return true;
    }
    else {
        std::cout << "file \"" << filename << "\" could not be opened for reading\n";
        return false;
    }
}


bool settings::save(std::string filename) {
    std::ofstream filestream(filename);
    if(filestream.is_open()) {
        std::unordered_map<std::string, std::string>::iterator it;
        for( it = contents.begin(); it != contents.end(); ++it) {
            std::cout << "write \"" << it->first << " " << it->second << "\"\n";
            filestream << it->first << " " << it->second << "\n";
        }

    filestream.close();
    return true;
    }
    else{
        std::cout << "file \"" << filename << "\" could not be opened for writing\n";
        return false;
    }
}


std::string settings::get(std::string parameterName) {
    std::unordered_map<std::string, std::string>::iterator i;
    i = contents.find(parameterName);
    if(i == contents.end()) {
        std::cout << "parameter \"" << parameterName << "\" not found\n";
        return std::string();
    }
    return contents[parameterName];
}


bool settings::exists(std::string parameterName) {
    std::string s = get(parameterName);
    if(s == "")
        return false;
    else
        return true;
}


int settings::get_i(std::string parameterName) {
    std::string s = this->get(parameterName);
    if(!s.empty())
        return std::stoi(s);
    else {
        return 0;
    }
}


float settings::get_f(std::string parameterName) {
    std::string s = this->get(parameterName);
    if(!s.empty())
        return std::stof(s);
    else {
        return 0;
    }
}


bool settings::set(std::string parameterName, std::string newValue) {
    contents[parameterName] = newValue;
    return true;
}
