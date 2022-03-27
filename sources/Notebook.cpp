#include <iostream>
#include "Notebook.hpp"
//#include "sources/Direction.hpp"
#include "Direction.hpp"

#include <string>
#include <algorithm>
#include <map>
#include <stdexcept>
#define ROW_LENGTH 100
#define MAX_CHAR 126
#define MIN_CHAR 33

using namespace ariel;
using namespace std;
namespace ariel{
    std::string newLine(){
        std::string ans = "";
        for(int i=0;i<ROW_LENGTH;i++){
            ans += "_";
        }
        return ans;
    }

//    Notebook::Notebook() {}

    void Notebook::write(int page,int row,int col,Direction d,std::string text){
        if (page<0 || row<0 || col<0){
            throw  std::invalid_argument("Page,Row,Column MUST be an unsigned integer (above 0)");
        }
        if (col >= ROW_LENGTH || ((int)text.length() + col > ROW_LENGTH && d == Direction::Horizontal )){
            throw  std::invalid_argument("Trying to write in an invalid location");
        }
        int stringLen = text.length();

        if(d == Direction::Horizontal){
            pair<int, int> pair = make_pair(page,row);
            if (notebook[pair] == ""){
                notebook[pair] = newLine();
//                std::cout<< "Made a new line "<< page<<","<<row <<std::endl;
            }
            else{
                for (int i = col; i < col+stringLen; ++i) {
                    if (notebook.at(pair).at((unsigned int)i) != '_'){
                        throw  std::invalid_argument("Trying to overwrite an existing character");
                    }
                }
            }
        }
        else{
            for (int i = row; i < row+stringLen; ++i) {
                pair<int, int> pair = make_pair(page,i);
                if(notebook[pair] == ""){
                    notebook[pair] = newLine();
//                    std::cout<< "Made a new line "<< page<<","<<i <<std::endl;
                }
                else{
                    if(notebook[pair][(unsigned int)col] != '_'){
                        throw  std::invalid_argument("Trying to overwrite an existing character");
                    }
                }
            }
        }
        if(d == Direction::Horizontal){
            pair<int, int> pair = make_pair(page,row);
            for (int i = 0; i < stringLen; ++i) {
                notebook[pair][(unsigned int)(col+i)] = text[(unsigned int)i];
//                std::cout<< "Wrote "<< text[(unsigned int) i] <<" at "<< page << "," << row << "," << col+i <<std::endl;
            }
        }
        else{
            for (int i = 0; i < stringLen; ++i) {
                pair<int, int> pair = make_pair(page,row+i);
                notebook[pair][(unsigned int)col] = text[(unsigned int)i];
//                std::cout<< "Wrote "<< text[(unsigned int) i] <<" at "<< page << "," << row+i << "," << col <<std::endl;
            }
        }
    }
    std::string Notebook::read(int page,int row,int col,Direction d,int readSize){
        if (page<0 || row<0 || col<0){
            throw  std::invalid_argument("Page,Row,Column MUST be an unsigned integer (above 0)");
        }
        if (col >= 100 || (readSize + col > 100 && d == Direction::Horizontal )){
            throw  std::invalid_argument("Trying to read in an invalid location");
        }
        if(d == Direction::Horizontal){
            pair<int, int> pair = make_pair(page,row);
            if (notebook[pair] == ""){
                notebook[pair] = newLine();
            }
        }
        else{
            for (int i = row; i < row+readSize; ++i) {
                pair<int, int> pair = make_pair(page,i);
                if(notebook[pair] == ""){
                    notebook[pair] = newLine();
                }
            }
        }
        string ans = "";
        if(d == Direction::Horizontal){
            pair<int, int> pair = make_pair(page,row);
            for (int i = 0; i < readSize; ++i) {
                ans += notebook[pair][(unsigned int)(col+i)];
            }
        }
        else{
            for (int i = 0; i < readSize; ++i) {
                pair<int, int> pair = make_pair(page,row+i);
                ans += notebook[pair][(unsigned int)col];
            }
        }
        return ans;
    }
    void Notebook::erase(int page,int row,int col,Direction d,int eraseSize){
        if (page<0 || row<0 || col<0){
            throw  std::invalid_argument("Page,Row,Column MUST be an unsigned integer (above 0)");
        }
        if (col >= 100 || (eraseSize + col > 100 && d == Direction::Horizontal )){
            throw  std::invalid_argument("Trying to erase in an invalid location");
        }
        if(d == Direction::Horizontal){
            pair<int, int> pair = make_pair(page,row);
            if (notebook[pair] == ""){
                notebook[pair] = newLine();
            }
        }
        else{
            for (int i = row; i < row+eraseSize; ++i) {
                pair<int, int> pair = make_pair(page,i);
                if(notebook[pair] == ""){
                    notebook[pair] = newLine();
                }
            }
        }
        if(d == Direction::Horizontal){
            pair<int, int> pair = make_pair(page,row);
            for (int i = 0; i < eraseSize; ++i) {
                notebook[pair][(unsigned int)(col+i)] = '~';
            }
        }
        else{
            for (int i = 0; i < eraseSize; ++i) {
                pair<int, int> pair = make_pair(page,row+i);
                notebook[pair][(unsigned int)col] = '~';
            }
        }
    }
    std::string Notebook::show(int page){
        return "Hi";
    }
}

