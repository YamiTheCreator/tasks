#pragma once

#include <iostream>
#include <string>
#include <map>

using Dictionary = std::map<std::string, std::string>;
std::string ToLowerCase(const std::string& str);
void LoadDictionary(Dictionary& dict);
bool SaveDictionary(const Dictionary& dict);
bool ProcessInput(const std::string& input, Dictionary& dict);
void HandleExit(bool modified, const Dictionary& dict);
void RunDictionaryLoop(Dictionary& dictionary);
