#ifndef EX1_MAT_H
#define EX1_MAT_H
#endif //EX1_MAT_H

#include <iostream>
//#include "sources/Direction.hpp"
#include <string>
#include "Direction.hpp"
#include <algorithm>
#include <map>
#include <stdexcept>
#define ROW_LENGTH 100

namespace ariel{
    class Notebook{
    private:
        std::map<std::pair<int,int>,std::string> notebook;
    public:
//        Notebook();
        void write(int page,int row,int col,Direction d,std::string text);
        std::string read(int page,int row,int col,Direction d,int readSize);
        void erase(int page,int row,int col,Direction d,int eraseSize);
        static std::string show(int page);
    };
}

