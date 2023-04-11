#include <list>
#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
using namespace std;
//using namespace mySodukoLib;

namespace mySodukoLib {

    class readfile
    {
    private:
        string mySudoku[9];
        ofstream myfile;
        int readf(string afile);
    public:
        readfile(string afile);
        ~readfile();
        string getRow(int y);
    };
    
    readfile::readfile(string afile)
    {
      int x = readf(afile);
    }

    string readfile::getRow(int y) {
        return mySudoku[y-1];
    }
    
    int readfile::readf(string afile) {
      string line;
      ifstream myfile(afile);
      if (myfile.is_open()) {
        int i = 0;
        while ( getline (myfile,line) ) {
          cout << line << '\n';
          mySudoku[i] = line;
          i++;
          if (i > 8) {
            break;
          }
        }
        myfile.close();
      } else { 
        cout << "Unable to open file";
      } 
      return 0;
    }

    readfile::~readfile()
    {
    }
    
};