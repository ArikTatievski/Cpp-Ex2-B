
/**
 * Notebook header file
 * classes declared:Notebook
 */
#include <string>
#include "Direction.hpp"
#include <vector>
#include <iterator>
#include <map>
#include <cassert>
#include <string>

using namespace std;
namespace ariel {
    class Notebook {
        std::map<int, std::map<int, string> > notebook;
    public:
        Notebook();

        void write(int page, int row, int col, Direction d, string text);

        string read(int page, int row, int col, Direction d, int readSize);

        void erase(int page, int row, int col, Direction d, int eraseSize);

        void show(int page);

        ~Notebook();
    };
}