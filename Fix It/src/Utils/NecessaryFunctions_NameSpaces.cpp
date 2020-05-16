
#include "NecessaryFunctions_NameSpaces.h"

#include <string>
#include <chrono>

namespace verifyInputs
{
    bool verifyString(std::string auxStr)
    {
        if (auxStr.empty() || std::cin.eof())
        {
            std::cout << "Invalid Option! Please enter a valid input." << std::endl;
            return true;
        }
        return false;
    }

    bool verifyStringRole(std::string role) {
        if (role.empty() || std::cin.eof() ||
            (role != "Eletricista" && role != "Canalizador" && role != "Tecnico Informatico"
                && role != "Trolha" && role != "Picheleiro"))
        {
            std::cout << "Invalid Role! Please enter a valid role." << std::endl;
            return true;
        }
        return false;
    }

    bool verifyNumber()
    {
        if (std::cin.fail() || std::cin.eof())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid Option! Please enter a valid input." << std::endl;
            return true;
        }
        return false;
    }
}

namespace readOperations {
    std::string readString(std::string parameter) {
        std::string auxStr;
        do
        {
            std::cout << parameter;
            getline(std::cin, auxStr);
        } while(verifyInputs::verifyString(auxStr));
        return auxStr;
    }

    std::string readRole(std::string parameter) {
        std::string auxStr;
        do
        {
            std::cout << parameter;
            getline(std::cin, auxStr);
        } while(verifyInputs::verifyStringRole(auxStr));
        return auxStr;
    }

    std::vector<std::string> readVectorString(std::string parameter) {
        std::string auxStr;
        std::vector<std::string> resultVector;
        int itr = 0;
        do {
            while (true) {
                std::cout << ++itr << ". " << parameter;
                getline(std::cin, auxStr);
                if (auxStr == "exit" || verifyInputs::verifyStringRole(auxStr))
                    break;
                resultVector.push_back(auxStr);
            }

        } while(auxStr != "exit");

        return resultVector;
    }

    std::string confirmAnswer()
    {
        std::string answer;
        while(true)
        {
            getline(std::cin, answer);
            if(answer == "Y" || answer == "y" || answer == "N" || answer == "n")
                break;
            std::cout << "Invalid Option! Please enter a valid input." << std::endl;
        }
        return answer;
    }

}

namespace generalFunctions {
    std::string coutVectorString(const std::vector<std::string> &v) {
        std::string str = "";
        for (auto it = v.begin(); it != v.end() - 1; it++) {
            str += *it + ", ";
        }
        str += v.at(v.size() - 1);
        return str;
    }

    void trim(std::string &str) {
        size_t pos = str.find_first_not_of(' ');
        str.erase(0, pos);
        pos = str.find_last_not_of(' ');
        if (std::string::npos != pos)
            str.erase(pos + 1);
    }

    std::vector<std::string> separate_string(std::string str, char separator) {
        std::vector<std::string> str_fields;
        std::string temp = "";
        str += separator;

        for(size_t i = 0; i < str.size(); i++){
            if (str[i] == separator){
                trim(temp);
                str_fields.push_back(temp);
                temp = "";
            } else {
                temp += str[i];
            }
        }

        return str_fields;
    }

    std::vector<int> convert_vector_str_to_int(std::vector<std::string> v) {
        std::vector<int> vec;
        std::string temp;
        for (size_t i = 0; i < v.size(); i++){
            temp = "";
            temp = v.at(i);
            trim(temp);
            vec.push_back(stoi(temp));
        }
        return vec;
    }

    void processCoordinates(double x, double y, double &minX, double &minY, double &maxX, double &maxY) {
        if(x > maxX)
            maxX = x;
        else if(x < minX)
            minX = x;

        if(y > maxY)
            maxY = y;
        else if(y < minY)
            minY = y;

    }
}