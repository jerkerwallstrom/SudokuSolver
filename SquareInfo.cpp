#include <stdio.h>
#include <list>
#include <iostream>
#include <stdlib.h>
using namespace std;

namespace mySodukoLib {

  //namespace mySqureStruct {    
    struct mySquare {             // Structure declaration
      int xMin;         // Member (int variable)
      int xMax;   // Member (string variable)
      int yMin;         // Member (int variable)
      int yMax;   // Member (string variable)
    };
  //};

class SquareInfo {

  public :
  int GetRutaForPos(int x, int y) {
    switch(x) {
	  case 1: case 2: case 3:
	    switch(y) {
		  case 1: case 2: case 3:
		    return 1;
			break;
		  case 4: case 5: case 6:
		    return 4;
			break;
		  case 7: case 8: case 9:
		    return 7;
			break;
		  default:  	
		    break;
        }
		break;
	  case 4: case 5: case 6:
	    switch(y) {
		  case 1: case 2: case 3:
		    return 2;
			break;
		  case 4: case 5: case 6:
		    return 5;
			break;
		  case 7: case 8: case 9:
		    return 8;
			break;
		  default:
		    break;
        }
		break;
	  case 7: case 8: case 9:
	    switch(y) {
		  case 1: case 2: case 3:
		    return 3;
			break;
		  case 4: case 5: case 6:
		    return 6;
			break;
		  case 7: case 8: case 9:
		    return 9;
			break;
		  default:
		    break;
        }
    	break;
      default:
        break;
    }
    return 0;
  }	 
	
  void GetPosForSquare(int asquare, mySquare& res) {
    //mySquare res;
    res.xMin = (((asquare-1) % 3) * 3) + 1;
	res.xMax = (((asquare-1) % 3) * 3) + 3;
	res.yMin = (((asquare-1) / 3) * 3) + 1;
	res.yMax = (((asquare-1) / 3) * 3) + 3;
	//return (res);
  }
  
  mySquare GetPosForSquare(int asquare) {
    mySquare res;
    res.xMin = (((asquare-1) % 3) * 3) + 1;
	res.xMax = (((asquare-1) % 3) * 3) + 3;
	res.yMin = (((asquare-1) / 3) * 3) + 1;
	res.yMax = (((asquare-1) / 3) * 3) + 3;
	return (res);
  }
  void getSquareFriends(int v, int &v1, int &v2)
  {
      switch (v) {
	    case 1:
	      v1 = 2; v2 = 3; break;	
	    case 2:
	      v1 = 1; v2 = 3; break;	
	    case 3:
	      v1 = 1; v2 = 2; break;	
	    case 4:
	      v1 = 5; v2 = 6; break;	
	    case 5:
	      v1 = 4; v2 = 6; break;	
	    case 6:
	      v1 = 4; v2 = 5; break;	
	    case 7:
	      v1 = 8; v2 = 9; break;	
	    case 8:
	      v1 = 7; v2 = 9; break;	
	    case 9:
	      v1 = 7; v2 = 8; break;	
	  }
	
  }

  void getSquaresInRow(int sqr, int &sqr1, int &sqr2) {
    switch (sqr) {
	    case 1:
	      sqr1 = 2; sqr2 = 3; break;	
	    case 2:
	      sqr1 = 1; sqr2 = 3; break;	
	    case 3:
	      sqr1 = 1; sqr2 = 2; break;	
	    case 4:
	      sqr1 = 5; sqr2 = 6; break;	
	    case 5:
	      sqr1 = 4; sqr2 = 6; break;	
	    case 6:
	      sqr1 = 4; sqr2 = 5; break;	
	    case 7:
	      sqr1 = 8; sqr2 = 9; break;	
	    case 8:
	      sqr1 = 7; sqr2 = 9; break;	
	    case 9:
	      sqr1 = 7; sqr2 = 8; break;	
	  }
  }
  
  void getSquaresInCol(int sqr, int &sqr1, int &sqr2) {
    switch (sqr) {
	    case 1:
	      sqr1 = 4; sqr2 = 7; break;	
	    case 2:
	      sqr1 = 5; sqr2 = 8; break;	
	    case 3:
	      sqr1 = 6; sqr2 = 9; break;	
	    case 4:
	      sqr1 = 1; sqr2 = 7; break;	
	    case 5:
	      sqr1 = 2; sqr2 = 8; break;	
	    case 6:
	      sqr1 = 3; sqr2 = 9; break;	
	    case 7:
	      sqr1 = 1; sqr2 = 4; break;	
	    case 8:
	      sqr1 = 2; sqr2 = 5; break;	
	    case 9:
	      sqr1 = 3; sqr2 = 6; break;	
	  }
  }

};
    
};
