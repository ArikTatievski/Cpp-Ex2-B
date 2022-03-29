#include <string>
#include "Direction.hpp"
#include <iostream>
#include <vector>
#include <map>
#include "Notebook.hpp"

const int PAGE_PRINT= 99;
const int MAX_COL= 99;
const int maxCharValue=126;
const int mincharValue=32;

namespace ariel {
    Notebook::Notebook(){}
    Notebook::~Notebook(){}
    void Notebook::erase(int page, int row, int col, ariel::Direction direction,int eraseSize) {
        if (page < 0 || row < 0 || col < 0 || eraseSize < 0) {
            throw std::invalid_argument("Negative page/row/col/eraseSize detected");
        }
        if (col > MAX_COL) {
            throw std::invalid_argument("Trying to erase in an invalid location");
        }
        if ((col + eraseSize) > MAX_COL&& direction == Direction::Horizontal) {
            throw std::invalid_argument("Trying to erase in an invalid location");
        }
        if (direction == Direction::Horizontal) {
            if (notebook[page][row].empty()) {
                for (int i = 0; i < MAX_COL; i++) {
                    notebook[page][row].push_back('_');
                }
            }
            string eraseString;
            for (int i = 0; i < eraseSize; ++i) {
                eraseString.push_back('~');
            }
            notebook[page][row].replace((unsigned long) col, (unsigned long) eraseSize, eraseString);
        }
        else {
            for (int i = 0; i < eraseSize; i++) {
                if (notebook[page][row + i].empty()) {
                    for (int k = 0; k < MAX_COL; k++) {
                        notebook[page][row + i].push_back('_');
                    }
                }
                notebook[page][row + i].replace((unsigned long) col, 1, "~");
            }
        }
    }

    std::string Notebook::read(int page, int row, int col, ariel::Direction direction, int readSize) {
        if (page < 0 || row < 0 || col < 0 || readSize < 0) {
            throw std::invalid_argument("Negative page/row/col/eraseSize detected");
        }
        if (col > MAX_COL) {
            throw std::invalid_argument("Trying to read in an invalid location");
        }
        if ((col + readSize) > MAX_COL + 1 && direction == Direction::Horizontal) {
            throw std::invalid_argument("Trying to read in an invalid location");
        }
        if (Direction::Horizontal == direction) {
            if (!notebook[page][row].empty()) {
                if (col == MAX_COL&& readSize== 1) {
                    string s;
                    s.push_back(notebook[page][row].at((unsigned long) MAX_COL- 1));
                    return s;
                }
                string str = notebook[page][row];
                unsigned long start = (unsigned long) (col);
                unsigned long readSizeInLong = (unsigned long) (readSize);
                string r = str.substr(start, readSizeInLong);
                return r;
            }
                string str;
                for (int i = 0; i < readSize; ++i) {
                    str.push_back('_');
                }
                return str;
        }
        string str;
        for (int i = 0; i < readSize; ++i) {
            if (notebook[page][row + i].empty()) {
                str.push_back('_');
            } else {
                str.push_back(notebook[page][row + i].at((unsigned long) col));
            }
        }
        return str;

    }

    void Notebook::show(int page) {
        if (page < 0) {
            throw std::invalid_argument("Negative page detected");
        }
        for (int i = 0; i < PAGE_PRINT; ++i) {
            std::cout << read(page,i,0,Direction::Horizontal,MAX_COL);
        }
    }

    void Notebook::write(int page, int row, int col, ariel::Direction direction, std::string text) {
        string invaild = "~\n";
        for (int i = 0; i < text.size(); ++i) {
            if (text.at((unsigned long) i) < mincharValue || text.at((unsigned long) i) > maxCharValue) {
                throw std::invalid_argument("Bad text input");
            }
            for (int j = 0; j < 2; ++j) {
                if (text.at((unsigned long) i) == invaild.at((unsigned long) j)) {
                    throw std::invalid_argument("Bad text input");
                }
            }
        }
        if (page < 0 || row < 0 || col < 0) {
            throw std::invalid_argument("Negative page/row/col/eraseSize detected");
        }
        if (col > MAX_COL) {
            throw std::invalid_argument("Trying to write in an invalid location");
        }
        if ((col + (int)text.length()) > MAX_COL&& direction == Direction::Horizontal) {
            throw std::invalid_argument("Trying to write in an invalid location");
        }
        if (Direction::Horizontal == direction) {
            if (notebook[page][row].empty()) {
                for (int i = 0; i < MAX_COL; i++) {
                    notebook[page][row].push_back('_');
                }
            }
            for (int i = 0; i < text.length(); i++) {
                int currPos = i + col;
                if (notebook[page][row].at((unsigned long) currPos) != '_') {
                    throw std::invalid_argument("Trying to over-write a written character");
                }
            }
            notebook[page][row].replace((unsigned long) col, text.length(), text);
        }
        else {
            for (int i = 0; i < text.length(); i++) {
                if (notebook[page][row + i].empty()) {
                    for (int k = 0; k < MAX_COL+ 1; k++) {
                        notebook[page][row + i].push_back('_');
                    }
                }
                if (notebook[page][row + i].at((unsigned long) col) == '_') {
                    string currChar;
                    currChar.push_back(text.at((unsigned long) i));
                    notebook[page][row + i].replace((unsigned long) col, 1, currChar);
                }
                else {
                    throw std::invalid_argument("Trying to over-write a written character");
                }
            }
        }
    }
}