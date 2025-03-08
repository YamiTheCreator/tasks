#include "map.h"
#include <fstream>
#include <algorithm>
#include <cctype>

std::string ToLowerCase(const std::string& str)
{
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c){ return std::tolower(c); });
    return result;
}

void LoadDictionary(Dictionary& dict)
{
    const std::string dictFile = "dictionary.txt";
    std::ifstream file(dictFile);
    
    if (!file.is_open())
    {
        return;
    }

    std::string line;
    
    while (std::getline(file, line))
    {
        size_t pos = line.find('\t');
        if (pos != std::string::npos)
        {
            std::string key = ToLowerCase(line.substr(0, pos));
            std::string value = line.substr(pos + 1);
            dict[key] = value;
        }
    }
}

bool SaveDictionary(const Dictionary& dict)
{
    const std::string dictFile = "dictionary.txt";
    std::ofstream file(dictFile);
    
    if (!file.is_open())
    {
        return false;
    }

    for (const std::pair<const std::string, std::string>& pair : dict)
    {
        file << pair.first << '\t' << pair.second << '\n';
    }
    
    return true;
}

bool ProcessInput(const std::string& input, Dictionary& dict)
{
    if (input.empty())
    {
        return false;
    }

    std::string lowerKey = ToLowerCase(input);
    Dictionary::iterator it = dict.find(lowerKey);
    
    if (it != dict.end())
    {
        std::cout << it->second << '\n';
        return false;
    }

    std::cout << "Неизвестное слово \"" << input << "\". Введите перевод или пустую строку для отказа.\n>";
    std::string translation;
    std::getline(std::cin, translation);

    if (translation.empty())
    {
        std::cout << "Слово \"" << input << "\" проигнорировано.\n";
        return false;
    }

    dict[lowerKey] = translation;
    std::cout << "Слово \"" << input << "\" сохранено в словаре как \"" << translation << "\".\n";
    return true;
}

void HandleExit(bool modified, const Dictionary& dict)
{
    if (!modified)
    {
        std::cout << "До свидания.\n";
        return;
    }

    std::cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом.\n>";
    std::string answer;
    std::getline(std::cin, answer);

    if (answer == "Y" || answer == "y")
    {
        if (SaveDictionary(dict))
        {
            std::cout << "Изменения сохранены. До свидания.\n";
        }
        else
        {
            std::cerr << "Ошибка сохранения файла!\n";
        }
    }
    else
    {
        std::cout << "Изменения не сохранены. До свидания.\n";
    }
}

void RunDictionaryLoop(Dictionary& dictionary)
{
    bool modified = false;
    LoadDictionary(dictionary);
    
    std::string input;
    while (true)
    {
        std::cout << ">";
        std::getline(std::cin, input);
        
        if (input.empty())
        {
            continue;
        }
        
        if (input == "...")
        {
            break;
        }
        
        if (ProcessInput(input, dictionary))
        {
            modified = true;
        }
    }
    
    HandleExit(modified, dictionary);
}
