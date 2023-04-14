#include <stdio.h>
#include <list>
#include <iostream>
#include "SquareInfo.cpp"
using namespace std;

namespace mySodukoLib {
    
class BoxItem {
  private:
    int value = 0;
    list<int> canHave; 
    int xPos;
    int yPos;
    int inRuta;
    bool filled = false;
  
  
  public :BoxItem(int x, int y) {
     //canHave = new list();
	 for(int i = 1; i<=9; i++) {
	   canHave.push_back(i);
     }
	 xPos = x;
	 yPos = y;
	 SquareInfo squareInfo;
	 inRuta = squareInfo.GetRutaForPos(x, y);
	 filled = false;
	 
  }
  
  public :~BoxItem() {
	//Free
  }
  
  public :int getX() { return xPos; };
  public :int getY() { return yPos; };
  
  public :void setValue(int aValue) {
    value = aValue;
	filled = aValue != 0;
  }
  
  public :int getValue() { return value; }
  public :bool getFilled() { return filled; }
  public :int getRuta() { return inRuta; }
  
  public :std::list<int> getCanHave() {
     std::list<int> res; // = new List<int>();
	 for(int v : canHave) {
	   res.push_back(v);
	 }
	 return res;
  }
  
  public :bool validateCanHave(int &tmpValue) {
	int aSize = canHave.size(); 
    if (aSize == 1) {
	  int aValue = 0;
	  list<int>::iterator it = canHave.begin();
	  advance(it, 0);
	  aValue = *it;
	  
	  setValue(aValue);
	  tmpValue = aValue;
	  return true;
	} else {
	  return false;
	}
  }
  
  public :bool addCanHave(int aValue) {
	 for(int v : canHave) {
	   if (aValue == v) {
	     return false;
	   };
	 }
	 canHave.push_back(aValue);
	 return true;
  }
  
  public :bool removeCanHave(int aValue) {
	if ((1 == xPos) && (5 == yPos)) {
		int ibreak = 1;
	}
	 for(int v : canHave) {
	   if (aValue == v) {
	     canHave.remove(aValue);
	     return true;
	   };
	 }
	 return false;
  }
  
  public :bool checkCanHave(int aValue) {
	 for(int v : canHave) {
	   if (aValue == v) {
	     return true;
	   };
	 }
	 return false;
  }
    
  public :void resetValue()
  {
    value = 0;
	filled = false;
  }
  
};

}