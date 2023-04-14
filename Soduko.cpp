#include <stdio.h>
#include <list>
#include <iostream>
#include <algorithm>
#include <string>
#include "BoxItem.cpp"
using namespace std;
using namespace mySodukoLib;

namespace mySodukoLib {

class Soduko {

  private:
    list<BoxItem> items;
    int magicTable[100];
	int printCnt = 0;
	string lastSavedSolution = "";
  
  public :Soduko() { 
    //magicTable = new List<int>();
	for(int i = 0; i < 100; i++) {
	  magicTable[i] = 0;
	}
    //items = new List<BoxItem>();
    for(int y = 1; y<=9; y++) {
	  for(int x = 1; x<=9; x++) {
	    BoxItem* aItem = new BoxItem(x, y);
		items.push_back(*aItem);
        int aPos = items.size(); 		
		magicTable[x*10+y] = aPos - 1;
	  }
	}
  }

  public :~Soduko() {
	//Free list<BoxItem>
	items.clear();
  }
  
  public :void Setup(int x, int y, int aValue) {
    //for (BoxItem item : items) {
	//  if ((x==item.getX()) && (y==item.getY())) {
	//    item.setValue(aValue);
	//	int test = item.getValue();
	//	break;
	//  }
	//}
    for (list<BoxItem>::iterator pItem = items.begin(),
         end = items.end();
         pItem != end;
         ++pItem) {
        //BoxItem *item = (*iter);
	    if ((x==pItem->getX()) && (y==pItem->getY())) {
	      pItem->setValue(aValue);  
		  int test = pItem->getValue();
		  break;
	    }
	}
  }

  public :void testValuesInItems() {
    for (BoxItem item : items) {
	  int test = item.getValue(); 
	}
  }
  
  public :void setupRow(int y, string numbers) {
    int x = 1;
	string szNumbers = numbers;
	if (szNumbers.length() != 9) {
	  if (szNumbers.length() > 9) {
        szNumbers = szNumbers.substr(0, 9);
	  } else {
		for (int i = szNumbers.length(); i < 9; i++) {
		  szNumbers = szNumbers + "0";	
		}
	    printf("Error length input string");	
	  }
	}
    for (char & c : szNumbers) {
      int value = c - '0';  
	  if ((value > 9) || (value < 0)) {
		printf("Error value in setup row (\'%c\')", c);
		value = 0;
	  }  
      Setup(x, y, value); 
      x++;
    }
  }
  
  public :bool setValueForPos(int x, int y, int aValue) {  
	//test brytpunkt
    int pos = magicTable[x*10+y];
	//Item item = items[pos];
    list<BoxItem>::iterator pItem = items.begin();
    advance(pItem, pos);
    //BoxItem item = *pItem;
	if (pItem->getFilled()) {
	  return false;
	} else {
	  pItem->setValue(aValue);
	  return true;
	}
  }

  public :void resetValueForPos(int x, int y) {  
	//test brytpunkt
    int pos = magicTable[x*10+y];
	//Item item = items[pos];
    list<BoxItem>::iterator pItem = items.begin();
    advance(pItem, pos);
    //BoxItem item = *pItem;
    pItem->setValue(0);
  }

  public :BoxItem GetBoxItemAtPos(int x, int y){
    int pos = magicTable[x*10+y];
	list<BoxItem>::iterator it = items.begin();
    advance(it, pos);
    BoxItem item = *it;
	return item;
  }

  private :int GetValueFromIntAtPos(list<int> &values, int pos) {
	int i = 0;
	int res = 0;
	for (int v : values) {
	  if (i == pos)	{
        res = v;
		break;
	  }
	  i++;	
	}
	return res;
  }

  public :int GetValueForItemAtPos(int x, int y){
    int pos = magicTable[x*10+y];
	
	//BoxItem item = items[pos];
	//BoxItem item;
    list<BoxItem>::iterator it = items.begin();
    advance(it, pos);
    BoxItem item = *it;

	if (item.getFilled()) {	
	  return item.getValue();
    } else {
	  return 0;
    }	
  }

  public :bool setMissingValueInSquare(int  square, int missingValue) {
	bool res = false;
	SquareInfo squareInfo;
	mySquare sqr = squareInfo.GetPosForSquare(square);
	for (int x = sqr.xMin; x <= sqr.xMax; x++) {
	  for (int y = sqr.yMin; y <= sqr.xMax; y++) {
		BoxItem item = GetBoxItemAtPos(x, y);
		if (!item.getFilled()) {
	      res = setValueForPos(x, y, missingValue);
		  break;
		}
	  }
	  if (res) {
		break;
	  }
	} 
	return res;

  }

  public :list<BoxItem> GetBoxItemsForCol(int x, int ymin, int ymax) {
    list<BoxItem> res; // = new List<int>();
	for (int y = 1; y<=9; y++) {
	  if (((ymin == -1) && (ymax == -1)) || ((y<ymin) || (y>ymax))) {
        BoxItem aValue = GetBoxItemAtPos(x, y);
        res.push_back(aValue);
	  }
	}
	return res;
  }

  public :list<BoxItem> GetBoxItemsForRow(int y, int xmin, int xmax) {
    list<BoxItem> res; 
	for (int x = 1; x<=9; x++) {
	  if (((xmin == -1) && (xmax == -1)) || ((x<xmin) || (x>xmax))) {
        BoxItem aValue = GetBoxItemAtPos(x, y);
        res.push_back(aValue);
	  }
	}
	return res;
  }

  public :list<int> GetValuesForRow(int y, int xmin, int xmax) {
    list<int> res; // = new List<int>();
	for (int x = 1; x<=9; x++) {
	  if (((xmin == -1) && (xmax == -1)) || ((x<xmin) || (x>xmax))) {
        int aValue = GetValueForItemAtPos(x, y);
   	    if (aValue > 0) {
		  res.push_back(aValue);
	    }
	  }
	}
	return res;
  }
  
  public :list<int> GetValuesForCol(int x, int ymin, int ymax) { 
    list<int> res; // = new List<int>();
	for (int y = 1; y<=9; y++) {
	  if (((ymin == -1) && (ymax == -1)) || ((y<ymin) || (y>ymax))) {
        int aValue = GetValueForItemAtPos(x, y);
	    if (aValue > 0) {
		  res.push_back(aValue);
	    }
	  }
	}
	return res;
  }
  
  public :list<int> GetValuesForSquare(int square) {
    list<int> res; // = new List<int>();
    SquareInfo squareInfo;
    mySquare mSq = squareInfo.GetPosForSquare(square);
	for (int x = mSq.xMin; x <= mSq.xMax; x++) {
  	  for (int y = mSq.yMin; y <= mSq.yMax; y++) {
	    int aValue = GetValueForItemAtPos(x, y);
		if (aValue > 0) {
		  res.push_back(aValue);
		}
	  }
	}
	return res;
  }
  
  private :bool CheckIfValueIn(int aValue, list<int> values) {
	bool res = false;
	for (int value : values) {
		if (value == aValue) {
		  res = true;
		  break;	
		}
	}
	return res;
  }

  private :bool checkIfPosFilled(int x, int y) {
	bool res = false;
	BoxItem item = GetBoxItemAtPos(x, y);
	res = item.getFilled();
	return res;
  }

  private :bool checkIfValueAlreadyInSquare(int value, int sqr) {
	bool res = false;
	SquareInfo squareInfo;
	mySquare sqrPos = squareInfo.GetPosForSquare(sqr);
	for (int x = sqrPos.xMin; x <= sqrPos.xMax ; x++) {
	  for (int y = sqrPos.yMin; y <= sqrPos.yMax ; y++) {
		int tmp = GetValueForItemAtPos(x, y);
		res = value == tmp;
		if (res) {
		  break;	
		}
	  }	
	}
	return res;
  }

  private: bool checkIfPosCanHaveValueForCol(int x, int y, int value){
    list<int> values = GetValuesForCol(x, -1, -1);
    bool found = false;
	for (int avalue : values) {
		if (avalue == value) {
			found = true;
			break;
		}
	}
	return !found;
  }

  private: bool checkIfPosCanHaveValueForRow(int x, int y, int value){
    list<int> values = GetValuesForRow(y, -1, -1);
    bool found = false;
	for (int avalue : values) {
		if (avalue == value) {
			found = true;
			break;
		}
	}
	return !found;

  }

  private :bool checkIfPosCanHaveValue(int x, int y, int value){
	//Check Row
	list<int> row = GetValuesForRow(y, -1, -1);
	for (int i : row){
	  if (value == i) {
		return false;
	  }
	}

	//Check Col
	list<int> col = GetValuesForCol(x, -1, -1);
	for (int i : col){
	  if (value == i) {
		return false;
	  }
	}

	//Check Square
	SquareInfo squareInfo;
	int sqr = squareInfo.GetRutaForPos(x, y);
	list<int> sqrValues = GetValuesForSquare(sqr);
	for (int i : sqrValues){
	  if (value == i) {
		return false;
	  }
	}

	return true;

  }

  private :bool checkIfPosCanHaveValue(int x, int y, int value, 
                                       int x1, int x2, int y1, int y2,
                                       list<int> colValues1, list<int> colValues2, 
									   list<int> rowValues1, list<int> rowValues2, 
									   list<int> sqrValues ) {
	bool res = false;
	bool colTest = false;
	bool rowTest = false;									
    if ( (CheckIfValueIn(value, colValues1) ) &&
	     (CheckIfValueIn(value, colValues2) ) ) {
	  colTest = true;		
      if ( (checkIfPosFilled(x, y1)) && (checkIfPosFilled(x, y2))){
        res = true;
	  }
	}
	if (!res) {
 	  if ( (CheckIfValueIn(value, rowValues1)) &&
		   (CheckIfValueIn(value, rowValues2)) ) {
		rowTest = true;	
        if ( (checkIfPosFilled(x1, y)) && (checkIfPosFilled(x2, y))) {
          res = true; 
	    }
	  }
	}
	if (!res) {
	  res = rowTest && colTest;
	}
	if (res) {
	  res = false;	 	 
	  if (!CheckIfValueIn(value, sqrValues)) {
        res = true;
	  }		
	}
	if (!res) {
	  if (colTest) {
		if (CheckIfValueIn(value, rowValues1)) {
		  res = checkIfPosFilled(x, y2);
		} else if (CheckIfValueIn(value, rowValues2)) {
          res = checkIfPosFilled(x, y1);
		} 
      } else if (rowTest) {
		if (CheckIfValueIn(value, colValues1)) {
		  res = checkIfPosFilled(x2, y);
		} else if (CheckIfValueIn(value, colValues2)) {
          res = checkIfPosFilled(x1, y);
		} 
	  }	  
	}	
    return res;
  }

  public :void analyzeSquaresAround(int x, int y, int &tmpValue) {
	SquareInfo squareInfo;
	int sqr = squareInfo.GetRutaForPos(x, y);
	mySquare sqrpos = squareInfo.GetPosForSquare(sqr);
	int x1 = -1;
	int x2 = -1;
	int y1 = -1;
	int y2 = -1;
	for (int xP = sqrpos.xMin; xP <= sqrpos.xMax; xP++) {
	  if ((-1 == x1) && (xP != x)) {
		x1 = xP;
	  }
	  else if ((-1 == x2) && (xP != x)) {
		x2 = xP;
	  }
	}
	for (int yP = sqrpos.yMin; yP <= sqrpos.yMax; yP++) {
	  if ((-1 == y1) && (yP != y)) {
		y1 = yP;
	  }
	  else if ((-1 == y2) && (yP != y)) {
		y2 = yP;
	  }
	}
	if ((1 == x) && (5 == y)) {
		int ibreak = 1;
	}
    BoxItem item = GetBoxItemAtPos(x, y);
	list<int>colValues1 = GetValuesForCol(x1, sqrpos.yMin, sqrpos.yMax);
	list<int>colValues2 = GetValuesForCol(x2, sqrpos.yMin, sqrpos.yMax);
	list<int>rowValues1 = GetValuesForRow(y1, sqrpos.xMin, sqrpos.xMax);
	list<int>rowValues2 = GetValuesForRow(y2, sqrpos.xMin, sqrpos.xMax);
	list<int>sqrValues = GetValuesForSquare(sqr);
	bool found = false;
	int setValue = 0;
	list<int> canhaveValues = item.getCanHave();
	for (int value : canhaveValues) {
	  found = false;	
	  found = checkIfPosCanHaveValue(x, y, value, x1, x2, y1, y2, colValues1, colValues2, rowValues1, rowValues2, sqrValues );
	  if (found) {
	    setValue = value;
		break;
	  }
      //}
	  //}
	}
		//}
		//if (found) {
		//  break;
		//}
	  //}
	if (found && (0 != setValue)) {
	  setValueForPos(x, y, setValue);
	}
	
  }

  public :bool analyzeRows(){
	bool res = false;
    list<int> missingValues;
	list<int> emptyXs;
	int xPos = 0;
	int yPos = 0;
	int setValue = 0;
	for (int y = 1; y <= 9; y++) {
	  list<int> rowValues = GetValuesForRow(y, -1, -1);
	  for (int v = 1; v <= 9; v++) {
		if (!CheckIfValueIn(v, rowValues)) {
			missingValues.push_back(v);
		}
	  }
	  for (int x = 1; x <= 9; x++) {
		if (!GetBoxItemAtPos(x, y).getFilled()) {
          emptyXs.push_back(x);
		}
	  }
	  int cnt = 0;
	  for (int missValue : missingValues) {
        for(int x : emptyXs) {
		  list<int> yValues = GetValuesForCol(x, -1, -1);
		  if (!CheckIfValueIn(missValue, yValues)) {
			cnt++;
			xPos = x;
			yPos = y;
			setValue = missValue;
			if (cnt>2) {			 	
			  break;
			}
		  }
	    }
	  }
	  if (1 == cnt ) {
		res = setValueForPos(xPos, yPos, setValue);
	  }
	  emptyXs.clear();
	  missingValues.clear();
	}
    return res;
  }

  public :bool analyzeCols() {
	bool res = false;
    list<int> missingValues;
	list<int> emptyYs;
	int xPos = 0;
	int yPos = 0;
	int setValue = 0;
	for (int x = 1; x <= 9; x++) {
	  list<int> colValues = GetValuesForCol(x, -1, -1);
	  for (int v = 1; v <= 9; v++) {
		if (!CheckIfValueIn(v, colValues)) {
			missingValues.push_back(v);
		}
	  }
	  for (int y = 1; y <= 9; y++) {
		if (!GetBoxItemAtPos(x, y).getFilled()) {
          emptyYs.push_back(y);
		}
	  }
	  int cnt = 0;
	  for (int missValue : missingValues) {
        for(int y : emptyYs) {
		  list<int> xValues = GetValuesForRow(y, -1, -1);
		  if (!CheckIfValueIn(missValue, xValues)) {
			cnt++;
			xPos = x;
			yPos = y;
			setValue = missValue;
			if (cnt > 1) {			 	
			  break;
			}
		  }
	    }
		if (1 == cnt ) {
			break;
	    }
	  }
      if (1 == cnt ) {
	    res = setValueForPos(xPos, yPos, setValue);
	  }
	  emptyYs.clear();
	  missingValues.clear();
	}
    return res;
  }

  private :int GetSquareForValueInItems(int value, list<BoxItem>items){
	int res = 0;
	for (BoxItem item: items) {
	  if (item.getFilled()) {
		if (item.getValue() == value) {
	  	  res = item.getRuta();
		  break;
		}
	  }
	}
	if (0 == res) {
	  int tmpSquare = 0;	
	  bool tmpFound = false;
      for (BoxItem item: items) {
		if (!item.getFilled()) {
		  list<int> canHave = item.getCanHave();
		  for (int tmpV: canHave) {
            if (tmpV == value) {
			  
			  if (0 == tmpSquare) {
				tmpFound = true;
			    tmpSquare = item.getRuta();
			  } else { 
				if (item.getRuta() != tmpSquare) {
					tmpFound = false;
				}
			  }
			  break;
			}
		  }
		}
	  }
	  if (tmpFound) {
	    res = tmpSquare;
	  }		
	}
    return res;
  }

  private :bool checkIfValueInItems(int value, list<BoxItem> items) {
    bool res = false;
	for (BoxItem item: items) {
	  if (item.getFilled()) {
		if (item.getValue() == value) {
	  	  res = true;
		  break;
		}
	  }
	}
	if (!res) {
	  	
	  bool found = true;
	  list<int> squares;
      for (BoxItem item: items) {
		if (!item.getFilled()) {
		  int tmpS = item.getRuta();
		  list<int> canHave = item.getCanHave();
		  bool tmpFound = false;
		  for (int tmpV: canHave) {
            if (tmpV == value) {
			  tmpFound = true;
			  if (!CheckIfValueIn(tmpS, squares)) {
				squares.push_back(tmpS);
			  }
			  break;
			}
		  }
		  found = tmpFound;
		  if (!found) {
			break;
		  }
		}
	  }
	  res = found && (squares.size() == 1);		
	}
	return res;
  }

  private :bool checkThatValueOnlyCanBeAtRow(int value, int sqr, int yCheck){
    SquareInfo squareInfo;
	bool shouldHave = false;
	bool shouldNotHave = true;
	mySquare sqrPos = squareInfo.GetPosForSquare(sqr);
	for (int y = sqrPos.xMin; y <= sqrPos.xMax; y++) {
	  if (yCheck == y) {
		//Should have
		for (int x = sqrPos.xMin; x <= sqrPos.xMax; x++) {
		  if (checkIfPosFilled(x, y)) {
            if (value == GetValueForItemAtPos(x, y)) {
				shouldHave = true;
				break;
			}
		  } else {
            BoxItem item = GetBoxItemAtPos(x, y);
			list<int> canHave = item.getCanHave();
			if (CheckIfValueIn(value, canHave)){
			  shouldHave = true;
			} 
		  }
		}
	  } else {
        //Should not have

		for (int x = sqrPos.xMin; x <= sqrPos.xMax; x++) {
		  if (checkIfPosFilled(x, y)) {
            if (value == GetValueForItemAtPos(x, y)) {
				shouldNotHave = false;
				break;
			}
		  } else {
            BoxItem item = GetBoxItemAtPos(x, y);
			list<int> canHave = item.getCanHave();
			if (CheckIfValueIn(value, canHave)){
			  shouldNotHave = false;
			} 
		  }
		}
	  }
	}
	return shouldHave && shouldNotHave;
  }

  private :bool checkThatValueOnlyCanBeAtCol(int value, int sqr, int xCheck){
    SquareInfo squareInfo;
	bool shouldHave = false;
	bool shouldNotHave = true;
	mySquare sqrPos = squareInfo.GetPosForSquare(sqr);
	for (int x = sqrPos.xMin; x <= sqrPos.xMax; x++) {
	  if (xCheck == x) {
		//Should have
		for (int y = sqrPos.yMin; y <= sqrPos.yMax; y++) {
		  if (checkIfPosFilled(x, y)) {
            if (value == GetValueForItemAtPos(x, y)) {
				shouldHave = true;
				break;
			}
		  } else {
            BoxItem item = GetBoxItemAtPos(x, y);
			list<int> canHave = item.getCanHave();
			if (CheckIfValueIn(value, canHave)){
			  shouldHave = true;
			} 
		  }
		}
	  }
	}   
	for (int x = sqrPos.xMin; x <= sqrPos.xMax; x++) {
	  if (xCheck != x) {
        //Should not have
		for (int y = sqrPos.yMin; y <= sqrPos.yMax; y++) {
		  if (checkIfPosFilled(x, y)) {
            if (value == GetValueForItemAtPos(x, y)) {
				shouldNotHave = false;
				break;
			}
		  } else {
            BoxItem item = GetBoxItemAtPos(x, y);
			list<int> canHave = item.getCanHave();
			if (CheckIfValueIn(value, canHave)){
			  shouldNotHave = false;
			} 
		  }
		}
	  }
	}
	return shouldHave && shouldNotHave;
  }

  private :bool checkThatRowOk(int value, int x, int y) {
	list<int> values = GetValuesForRow(y, -1, -1);
	bool res = !CheckIfValueIn(value, values); 
	if (res) {
      list<BoxItem> items = GetBoxItemsForRow(y, -1, -1);
	  for (BoxItem item : items) {
		if (item.getX() != x) {
			list<int> canHave = item.getCanHave(); 
			res = !CheckIfValueIn(value, canHave);
			if (!res) {
			  break;
			}
		}
	  }
	}
	return res;
  }

  private :bool checkThatColOk(int value, int x, int y) {
	list<int> values = GetValuesForCol(x, -1, -1);
	bool res = !CheckIfValueIn(value, values); 
	if (res) {
      list<BoxItem> items = GetBoxItemsForCol(x, -1, -1);
	  for (BoxItem item : items) {
		if (item.getX() != x) {
			list<int> canHave = item.getCanHave(); 
			res = !CheckIfValueIn(value, canHave);
			if (!res) {
			  break;
			}
		}
	  }
	}
	return res;
  }

  private :bool analyzeRowAgainst(int y, int y1, int y2, int xMin, int xMax, int sqr, int sqr1, int sqr2) {
	bool res = false;
	int cntFilled = 0;
	int xPos = 0;
	for (int x = xMin; x <= xMax; x++) {
	  if (checkIfPosFilled(x, y)) {
		cntFilled++;
	  } else {
        xPos = x;
	  }
	}
	int x1Min = 0; int x1Max = 0; int x2Min = 0;int x2Max = 0;
	switch (xMin) {
	  case 1:
		x1Min = 4; x1Max = 6; x2Min = 7; x2Max = 9;
		break;
	  case 4:
		x1Min = 1; x1Max = 3; x2Min = 7; x2Max = 9;
		break;
	  case 7:
		x1Min = 1; x1Max = 3; x2Min = 4; x2Max = 6;
		break;
	  default:
		break;
	}
	if (2 == cntFilled) {
	  BoxItem item = GetBoxItemAtPos(xPos, y);
	  list<int> canHave = item.getCanHave();
	  for (int value : canHave) {
        //Check sqr1 //Only one column should have value
		bool sqr1Ok = checkThatValueOnlyCanBeAtRow(value, sqr1, y1);
		//Check sqr2 //Only one column should have value but not same as sqr1
		bool sqr2Ok = checkThatValueOnlyCanBeAtRow(value, sqr2, y2);
		if (sqr1Ok && sqr2Ok) {
		  if (checkThatColOk(value, xPos, y)){	
		    res = setValueForPos(xPos, y, value);
		    break;
		  }
		}
		sqr1Ok = checkThatValueOnlyCanBeAtRow(value, sqr1, y2);
		//Check sqr2 //Only one column should have value but not same as sqr1
		sqr2Ok = checkThatValueOnlyCanBeAtRow(value, sqr2, y1);
		if (sqr1Ok && sqr2Ok) {
		  if (checkThatColOk(value, xPos, y)){	
		    res = setValueForPos(xPos, y, value);
		    break;
		  }
		}
	  }
	}
    return res;
  }

  private :bool analyzeColAgainst(int x, int x1, int x2, int yMin, int yMax, int sqr, int sqr1, int sqr2) {
	bool res = false;
	int cntFilled = 0;
	int yPos = 0;
	for (int y = yMin; y <= yMax; y++) {
	  if (checkIfPosFilled(x, y)) {
		cntFilled++;
	  } else {
        yPos = y;
	  }
	}
	//Ex x=9 x1=7 x2=8 yMin=7 YMax=9 sqr=9 sqr1=3 sqr2=6 

	if ((9 == x) && (9 == sqr)) {
		int iBreak = 1;
	}
	if (2 == cntFilled) {
	  BoxItem item = GetBoxItemAtPos(x, yPos);
	  list<int> canHave = item.getCanHave();
	  for (int value : canHave) {
        //Check sqr1 //Only one column should have value
		bool sqr1Ok = checkThatValueOnlyCanBeAtCol(value, sqr1, x1);
		//Check sqr2 //Only one column should have value but not same as sqr1
		bool sqr2Ok = checkThatValueOnlyCanBeAtCol(value, sqr2, x2);
		if (sqr1Ok && sqr2Ok) {
		  if (checkThatRowOk(value, x, yPos)){	
		    res = setValueForPos(x, yPos, value);
		    break;
		  }
		}
		sqr1Ok = checkThatValueOnlyCanBeAtCol(value, sqr1, x2);
		//Check sqr2 //Only one column should have value but not same as sqr1
		sqr2Ok = checkThatValueOnlyCanBeAtCol(value, sqr2, x1);
		if (sqr1Ok && sqr2Ok) {
		  if (checkThatRowOk(value, x, yPos)){	
		    res = setValueForPos(x, yPos, value);
		    break;
		  }
		}
	  }
	}
    return res;
  }

  private :bool analyzeRowSquareExtendedPlus(int sqr) {
	SquareInfo squareInfo;
    mySquare sqrPos = squareInfo.GetPosForSquare(sqr);
	int sqr1; int sqr2;
	squareInfo.getSquaresInRow(sqr, sqr1, sqr2);
	int y = sqrPos.xMin;
	int y1 = sqrPos.xMin + 1;
	int y2 = sqrPos.xMax;
	bool res = analyzeRowAgainst(y, y1, y2, sqrPos.xMin, sqrPos.xMax, sqr, sqr1, sqr2);
	if (!res) {
	  res = analyzeRowAgainst(y1, y, y2, sqrPos.xMin, sqrPos.xMax, sqr, sqr1, sqr2);
	}
	if (!res) {
	  res = analyzeRowAgainst(y2, y, y1, sqrPos.xMin, sqrPos.xMax, sqr, sqr1, sqr2);
	}

    return res;
  }

  private :bool analyzeColSquareExtendedPlus(int sqr) {
	SquareInfo squareInfo;
    mySquare sqrPos = squareInfo.GetPosForSquare(sqr);
	int sqr1; int sqr2;
	squareInfo.getSquaresInCol(sqr, sqr1, sqr2);
	int x = sqrPos.xMin;
	int x1 = sqrPos.xMin + 1;
	int x2 = sqrPos.xMax;
	bool res = analyzeColAgainst(x, x1, x2, sqrPos.yMin, sqrPos.yMax, sqr, sqr1, sqr2);
	if (!res) {
	  res = analyzeColAgainst(x1, x, x2, sqrPos.yMin, sqrPos.yMax, sqr, sqr1, sqr2);
	}
	if (!res) {
	  res = analyzeColAgainst(x2, x, x1, sqrPos.yMin, sqrPos.yMax, sqr, sqr1, sqr2);
	}
    return res;
  }

  public :bool analyzeExtendedPlus() {
	bool res = false;
	for (int sqr = 1; sqr <= 9; sqr++) {
	  res = analyzeColSquareExtendedPlus(sqr);
	}
	for (int sqr = 1; sqr <= 9; sqr++) {
	  res = analyzeRowSquareExtendedPlus(sqr);
	}
	return res;
  }

  public :bool analyzeRowsExtended() {
	bool res = false;
	list<int> missingValues;
	for ( int y = 1; y <= 9; y++) {
	  int xPos = 0;
	  int yPos = 0;
	  int setValue = 0;
	  int cnt = 0;
      list<int> tmpValues = GetValuesForRow(y, -1, -1);
	  for (int value = 1; value <= 9; value++) {
		if (!CheckIfValueIn(value, tmpValues)) {
			missingValues.push_back(value);
		}		
	  }
	  for (int value : missingValues) {
		cnt = 0;
		for (int x = 1; x <= 9; x++) {
		  if (!checkIfPosFilled(x, y)) {	
		    BoxItem item = GetBoxItemAtPos(x, y);
		    list<int> canhave = item.getCanHave();
		    if (CheckIfValueIn(value, canhave)) {
			  cnt++;
			  if (1 == cnt) {
			    xPos = x;
			    yPos = y;
			    setValue = value;
			  }
			  if (cnt > 1) {
				break;
			  }
		    }
		  }
		}
		if (1 == cnt) {
		  res = setValueForPos(xPos, yPos, setValue);
		  missingValues.clear();
		  return res;
		}
	  }
	  missingValues.clear();
	}
	return res;
  }
  
  public :bool analyzeColsExtended() {
	bool res = false;
	list<int> missingValues;
	for ( int x = 1; x <= 9; x++) {
	  int xPos = 0;
	  int yPos = 0;
	  int setValue = 0;
	  int cnt = 0;
      list<int> tmpValues = GetValuesForCol(x, -1, -1);
	  for (int value = 1; value <= 9; value++) {
		if (!CheckIfValueIn(value, tmpValues)) {
			missingValues.push_back(value);
		}		
	  }
	  for (int value : missingValues) {
		cnt = 0;
		for (int y = 1; y <= 9; y++) {
		  if (!checkIfPosFilled(x, y)) {	
		    BoxItem item = GetBoxItemAtPos(x, y);
		    list<int> canhave = item.getCanHave();
		    if (CheckIfValueIn(value, canhave)) {
			  cnt++;
			  if (1 == cnt) {
			    xPos = x;
			    yPos = y;
			    setValue = value;
			  }
			  if (cnt > 1) {
				break;
			  }
		    }
		  }
		}
		if (1 == cnt) {
		  res =setValueForPos(xPos, yPos, setValue);
  		  missingValues.clear();
		  return res;
		}
	  }
	  missingValues.clear();
	}
	return res;
  }

  public :bool analyzeSquaresExtended() {
	bool res = false;
    list<int> missingValues;	
	//int xPos = 0;
	//int yPos = 0;
	//int setValue = 0;
 	for(int asquare = 1; asquare <= 9; asquare++) {
   	  int xPos = 0;
	  int yPos = 0;
	  int setValue = 0;
	  //int missingValue = 0;
	  list<int> sqrValues = GetValuesForSquare(asquare);
	  for (int v = 1; v <= 9; v++) {
		if (!CheckIfValueIn(v, sqrValues)) {
			missingValues.push_back(v);
		}
	  }
	  SquareInfo squareInfo;
	  mySquare sqrPos = squareInfo.GetPosForSquare(asquare);
	  
	  int cnt = 0;
	  for (int value : missingValues) {
		cnt = 0;
	    for (int x = sqrPos.xMin; x <= sqrPos.xMax; x++) {
		  for (int y = sqrPos.yMin; y <= sqrPos.yMax; y++) {
		    if (!checkIfPosFilled(x, y)) {
			  BoxItem item = GetBoxItemAtPos(x, y);
			  list<int> canHave = item.getCanHave();
			  if (4 == value) {
			    if ((3 == x) && (5 == y)) {
				  int ibreak = 1;
			    }
			    if ((1 == x) && (5 == y)) {
				  int ibreak = 1;
			    }
			  }
			  if (CheckIfValueIn(value, canHave)) {
				cnt++;
				if (1 == cnt) {
					xPos = x;
					yPos = y;
					setValue = value;
				}
				if (cnt > 1) {
				  break;	
				}

			  }
		    } 
		  }
	      if (cnt > 1) {
		    break;	
		  }
        }
		if (1 == cnt) { 
		  break;
		}
	  }
	  if (1 == cnt) {
		res = setValueForPos(xPos, yPos, setValue);
		if (res) {
			missingValues.clear();
			break;
		}
	  }
      missingValues.clear();
	}
    return res;
  }

  public :bool analyzeSquares() {
	bool res = false;
	for(int asquare = 1; asquare <= 9; asquare++) {
 	    int missingValue = 0;
		list<int> sqrValues = GetValuesForSquare(asquare);
		if (sqrValues.size() == 8) {
          for (int i = 1; i <= 9; i++) {
			bool found = false;
			for(int value : sqrValues) {
				if (value == i) {
                  found = true;
				}
			}
			if (!found) {
			  missingValue = i;
			  break;
			}
		  }
		  if (missingValue != 0) {
            res = setMissingValueInSquare(asquare, missingValue);
			if (res) {
			  break;
			}
		  }
		}
		if (res) {
		  break;
		}
	}
	return res;
  }

  private :bool detectSameCanHaveCol(int x, int yMin, int yMax) {
	//Count get filled
	if ((3 == x) && (4 == yMin) && (6 == yMax)) {
      int ibreak = 1;
	}
	int cntFilled = 0;
    for (int y = yMin; y <= yMax; y++) {
      if (checkIfPosFilled(x, y)) {
		cntFilled++;
	  }
	}
	if (cntFilled >= 2) {
	  return false;	
	}
	int cntUnfilled = 3 - cntFilled;
	bool res = true;
	list<int> firstCanHave;
	bool first = true;
    for (int y = yMin; y <= yMax; y++) {
      if (!checkIfPosFilled(x, y)) {
		if (first) {
		  first = false;
		  BoxItem item = GetBoxItemAtPos(x, y);
		  firstCanHave = item.getCanHave();
		  if (firstCanHave.size() != cntUnfilled) {
			res = false;
			break;
		  }
		  firstCanHave.sort();
		} else {
		  BoxItem item = GetBoxItemAtPos(x, y);
		  list<int> canhave = item.getCanHave();
		  if (canhave.size() != cntUnfilled) {
			res = false;
			break;
		  } else {
			canhave.sort();
			for (int i = 0; i < cntUnfilled; i++) {
              int iFirst = GetValueFromIntAtPos(firstCanHave, i);		
			  int iCanHave = GetValueFromIntAtPos(canhave, i);		
			  if (iFirst != iCanHave) {
                res = false;
			    break;
			  }
			}
			if (!res) {
			  break;	
			}
		  }

		}
	  }
	}
    return res;
  }

  private :bool CheckIfRowIsFilled(int y) {
    for (int x = 1; x <= 9; x++) {
      if (!checkIfPosFilled(x, y)) {
		return false;
	  }
	}
	return true;
  }

  private :bool CheckIfColIsFilled(int x) {
    for (int y = 1; y <= 9; y++) {
      if (!checkIfPosFilled(x, y)) {
		return false;
	  }
	}
	return true;
  }

  private :bool CheckIfSqrIsFilled(int sqr) {
    SquareInfo squareInfo;
    mySquare mySqr = squareInfo.GetPosForSquare(sqr);
    for (int x = mySqr.xMin; x <= mySqr.xMax; x++) {
      for (int y = mySqr.yMin; y <= mySqr.yMax; y++) {
        if (!checkIfPosFilled(x, y)) {
	  	  return false;
	    }  
	  }
	}
	return true;
  }

  private :bool specialCheckIfOnlyOneLeftinSqrRow(int sqr, int &xOne, int &yOne) {
    SquareInfo squareInfo;
    mySquare mySqr = squareInfo.GetPosForSquare(sqr);
    for (int y = mySqr.yMin; y <= mySqr.yMax; y++) {
	  int cnt = 0;	
      for (int x = mySqr.xMin; x <= mySqr.xMax; x++) {
        if (checkIfPosFilled(x, y)) {
          cnt++;
	    } else {
			xOne = x;
			yOne = y;
		}
	  }
	  if (2 == cnt) {
		return true;
	  }
	}
	return false;
  }

  private :bool specialCheckIfOnlyOneLeftinSqrCol(int sqr, int &xOne, int &yOne) {
    SquareInfo squareInfo;
    mySquare mySqr = squareInfo.GetPosForSquare(sqr);
    for (int x = mySqr.xMin; x <= mySqr.xMax; x++) {
	  int cnt = 0;	
      for (int y = mySqr.yMin; y <= mySqr.yMax; y++) {
        if (checkIfPosFilled(x, y)) {
          cnt++;
	    } else {
			xOne = x;
			yOne = y;
		}
	  }
	  if (2 == cnt) {
		return true;
	  }
	}
	return false;
  }

  private :int getMissingSquare(int sqr, int sqr1, int sqr2, int sqrFilled, int sqrOne) {
	int sqrRes = 0;
	if (!((sqr2 == sqrFilled) || (sqr2 == sqrOne))) {
		sqrRes = sqr2;
	}
	if (!((sqr1 == sqrFilled) || (sqr1 == sqrOne))) {
		sqrRes = sqr1;
	}
	if (!((sqr == sqrFilled) || (sqr == sqrOne))) {
		sqrRes = sqr;
	}
	return sqrRes;
  }

  private :bool analyzeExtendedSquareCanNotHaveRows() {
	for (int sqr = 1; sqr <=7; sqr = sqr + 3){
	  //Get squares for "squares in row"
      SquareInfo squareInfo;
	  int sqr1; int sqr2;
	  squareInfo.getSquaresInRow(sqr, sqr1, sqr2);
	  mySquare mySqr = squareInfo.GetPosForSquare(sqr);
	  mySquare mySqr1 = squareInfo.GetPosForSquare(sqr1);
	  mySquare mySqr2 = squareInfo.GetPosForSquare(sqr2);

	  //Check if one row is filled
	  int yFilled = 0;
	  int sqrFilled = 0;
	  int cnt = 0;
	  for (int y = mySqr.yMin; y <= mySqr.yMax; y++) {
		if (CheckIfRowIsFilled(y)) {
		  yFilled = y;
		  cnt ++;
		}
	  }
	  if (cnt != 1) {
		continue;
	  }
	  //Check if one sqr is filled
	  cnt = 0;
	  if (CheckIfSqrIsFilled(sqr)) {
	    sqrFilled = sqr;
	    cnt++;
	  }
	  if (CheckIfSqrIsFilled(sqr1)) {
	    sqrFilled = sqr1;
	    cnt++;
	  }
	  if (CheckIfSqrIsFilled(sqr2)) {
	    sqrFilled = sqr2;
	    cnt++;
	  }
	  if (cnt != 1) {
		continue;
	  }

	  //Check if only one left in a row in a sqr
	  int xOne; int yOne; int sqrOne; list<int> canhaveValues;
	  cnt = 0;
	  if (sqr != sqrFilled) {
	    if (specialCheckIfOnlyOneLeftinSqrRow(sqr, xOne, yOne)) {
		  sqrOne = sqr;
		  BoxItem item = GetBoxItemAtPos(xOne, yOne);
		  canhaveValues = item.getCanHave();
		  cnt++;
	    }
	  }
	  if ((0 == cnt) && (sqr1 != sqrFilled)) {
	    if (specialCheckIfOnlyOneLeftinSqrRow(sqr1, xOne, yOne)) {
		  sqrOne = sqr1;
		  BoxItem item = GetBoxItemAtPos(xOne, yOne);
		  canhaveValues = item.getCanHave();
		  cnt++;
	    }
	  }
	  if ((0 == cnt) && (sqr2 != sqrFilled)) {
	    if (specialCheckIfOnlyOneLeftinSqrRow(sqr2, xOne, yOne)) {
		  sqrOne = sqr2;
		  BoxItem item = GetBoxItemAtPos(xOne, yOne);
		  canhaveValues = item.getCanHave();
		  cnt++;
	    }
	  }
	  if (1 == cnt) {
		if (2 != canhaveValues.size()) {
		  continue;
		}
		// Get row which is not filled and the one withoute xOne!!
		int ySearch = 0;
  	    for (int y = mySqr.yMin; y <= mySqr.yMax; y++) {
		  if ((y != yFilled) && (y != yOne)) {
			ySearch = y;
		  }
		}
		//Get square which not have pos xOne, yOne anf are not filled!
		int sqrSearch = getMissingSquare(sqr, sqr1, sqr2, sqrFilled, sqrOne);
		mySquare mySqrSearch = squareInfo.GetPosForSquare(sqrSearch);
		list<int> canhaveSrh;
		int tmpCnt = 0;
		for (int x = mySqrSearch.xMin; x <= mySqrSearch.xMax; x++) {
		  BoxItem item = GetBoxItemAtPos(x, ySearch);
		  canhaveSrh = item.getCanHave();	
		  if (2 == canhaveSrh.size()) {
		    tmpCnt++;
		  }
		}
		if (1 == tmpCnt) {
		  int theValue = 0;
		  int lCnt = 0;
		  for (int value : canhaveValues) {
            for (int serchValue : canhaveSrh) {
			  if (value == serchValue) {
				lCnt++;
				theValue = value;
			  }
			}
		  }
		  if (1 == lCnt) {
			setValueForPos(xOne, yOne, theValue);
			return true;
		  }
		}
	  }

	}
	return false;
  }

  private :bool analyzeExtendedSquareCanNotHavecols() {
	for (int sqr = 1; sqr <=3; sqr++){
	  //Get squares for "squares in row"
      SquareInfo squareInfo;
	  int sqr1; int sqr2;
	  squareInfo.getSquaresInCol(sqr, sqr1, sqr2);
	  mySquare mySqr = squareInfo.GetPosForSquare(sqr);
	  mySquare mySqr1 = squareInfo.GetPosForSquare(sqr1);
	  mySquare mySqr2 = squareInfo.GetPosForSquare(sqr2);

	  //Check if one row is filled
	  int xFilled = 0;
	  int sqrFilled = 0;
	  int cnt = 0;
	  for (int x = mySqr.xMin; x <= mySqr.xMax; x++) {
		if (CheckIfColIsFilled(x)) {
		  xFilled = x;
		  cnt ++;
		}
	  }
	  if (cnt != 1) {
		continue;
	  }
	  //Check if one sqr is filled
	  cnt = 0;
	  if (CheckIfSqrIsFilled(sqr)) {
	    sqrFilled = sqr;
	    cnt++;
	  }
	  if (CheckIfSqrIsFilled(sqr1)) {
	    sqrFilled = sqr1;
	    cnt++;
	  }
	  if (CheckIfSqrIsFilled(sqr2)) {
	    sqrFilled = sqr2;
	    cnt++;
	  }
	  if (cnt != 1) {
		continue;
	  }

	  //Check if only one left in a row in a sqr
	  int xOne; int yOne; int sqrOne; list<int> canhaveValues;
	  cnt = 0;
	  if (sqr != sqrFilled) {
	    if (specialCheckIfOnlyOneLeftinSqrCol(sqr, xOne, yOne)) {
		  sqrOne = sqr;
		  BoxItem item = GetBoxItemAtPos(xOne, yOne);
		  canhaveValues = item.getCanHave();
		  cnt++;
	    }
	  }
	  if ((0 == cnt) && (sqr1 != sqrFilled)) {
	    if (specialCheckIfOnlyOneLeftinSqrCol(sqr1, xOne, yOne)) {
		  sqrOne = sqr1;
		  BoxItem item = GetBoxItemAtPos(xOne, yOne);
		  canhaveValues = item.getCanHave();
		  cnt++;
	    }
	  }
	  if ((0 == cnt) && (sqr2 != sqrFilled)) {
	    if (specialCheckIfOnlyOneLeftinSqrCol(sqr2, xOne, yOne)) {
		  sqrOne = sqr2;
		  BoxItem item = GetBoxItemAtPos(xOne, yOne);
		  canhaveValues = item.getCanHave();
		  cnt++;
	    }
	  }
	  if (1 == cnt) {
		if (2 != canhaveValues.size()) {
		  continue;
		}
		// Get row which is not filled and the one withoute xOne!!
		int xSearch = 0;
  	    for (int x = mySqr.xMin; x <= mySqr.yMax; x++) {
		  if ((x != xFilled) && (x != xOne)) {
			xSearch = x;
		  }
		}
		//Get square which not have pos xOne, yOne anf are not filled!
		int sqrSearch = getMissingSquare(sqr, sqr1, sqr2, sqrFilled, sqrOne);
		mySquare mySqrSearch = squareInfo.GetPosForSquare(sqrSearch);
		list<int> canhaveSrh;
		int tmpCnt = 0;
		for (int y = mySqrSearch.yMin; y <= mySqrSearch.yMax; y++) {
		  BoxItem item = GetBoxItemAtPos(xSearch, y);
		  canhaveSrh = item.getCanHave();	
		  if (2 == canhaveSrh.size()) {
		    tmpCnt++;
		  }
		}
		if (1 == tmpCnt) {
		  int theValue = 0;
		  int lCnt = 0;
		  for (int value : canhaveValues) {
            for (int serchValue : canhaveSrh) {
			  if (value == serchValue) {
				lCnt++;
				theValue = value;
			  }
			}
		  }
		  if (1 == lCnt) {
			setValueForPos(xOne, yOne, theValue);
			return true;
		  }
		}
	  }

	}
	return false;
  }

  public :bool analyzeExtendedSquareCanNotHave(){
	if (!analyzeExtendedSquareCanNotHaveRows()) {
	  return analyzeExtendedSquareCanNotHavecols();
	}
	return true;
  }

  private :bool detectSameCanHaveRow(int y, int xMin, int xMax) {
	//Count get filled
	int cntFilled = 0;
    for (int x = xMin; x <= xMax; x++) {
      if (checkIfPosFilled(x, y)) {
		cntFilled++;
	  }
	}
	if (cntFilled >= 2) {
	  return false;	
	}
	int cntUnfilled = 3 - cntFilled;
	bool res = true;
	list<int> firstCanHave;
	bool first = true;
    for (int x = xMin; x <= xMax; x++) {
      if (!checkIfPosFilled(x, y)) {
		if (first) {
		  first = false;
		  BoxItem item = GetBoxItemAtPos(x, y);
		  firstCanHave = item.getCanHave();
		  if (firstCanHave.size() != cntUnfilled) {
			res = false;
			break;
		  }
		  firstCanHave.sort();
		} else {
		  BoxItem item = GetBoxItemAtPos(x, y);
		  list<int> canhave = item.getCanHave();
		  if (canhave.size() != cntUnfilled) {
			res = false;
			break;
		  } else {
			canhave.sort();
			for (int i = 0; i < cntUnfilled; i++) {
			  if (GetValueFromIntAtPos(firstCanHave, i) != GetValueFromIntAtPos(canhave, i)) {
                res = false;
			    break;
			  }
			}
			if (!res) {
			  break;
			}
		  }

		}
	  }
	}
    return res;
  }

  private :void detectMissingValuesFriendsInSquareCol(int sqr) {
    SquareInfo squareInfo;
	mySquare sqrpos = squareInfo.GetPosForSquare(sqr);
	if (4 == sqr) {
		int ibreak = 1;
	}
	int xPos = 0;
	for (int x = sqrpos.xMin; x <= sqrpos.xMax; x++) {
	  if (detectSameCanHaveCol(x, sqrpos.yMin, sqrpos.yMax)) {
        xPos = x;
		break;
	  }	
	}
	if (3 == xPos) {
		int ibreak = 1;
	}
	if (xPos > 0 ) {
	  //remove can haves in other cols
	  // get can have from yPos col!
	  list <int> canHave;
	  for (int y = sqrpos.yMin; y <= sqrpos.yMax; y++) {
		if (!checkIfPosFilled(xPos, y)) {
		  canHave = GetBoxItemAtPos(xPos, y).getCanHave();
		  break;
		}		
	  }
	  //Remove can haves
   	  for (int x = sqrpos.xMin; x <= sqrpos.xMax; x++) {
		if (x != xPos) {
		  for (int y = sqrpos.yMin; y <= sqrpos.yMax; y++) {
			if ((5==x) && (1==y)) {
				int ibreak = 1;
			}	
			if ((5==x) && (3==y)) {
				int ibreak = 1;
			}	
            int pos = magicTable[x*10+y];
            list<BoxItem>::iterator pItem = items.begin();
            advance(pItem, pos);
  	        if (!pItem->getFilled()) {
			  for (int v : canHave) {
                pItem->removeCanHave(v);
			  }	
		    }
		  }
	    }
	  }
    }
  }

  private :void detectMissingValuesFriendsInSquareRow(int sqr) {
    SquareInfo squareInfo;
	if (7 == sqr) {
		int ibreak = 1;
	}
	mySquare sqrpos = squareInfo.GetPosForSquare(sqr);
	int yPos = 0;
	for (int y = sqrpos.yMin; y <= sqrpos.yMax; y++) {
	  if (detectSameCanHaveRow(y, sqrpos.xMin, sqrpos.xMax)) {
        yPos = y;
		break;
	  }	
	}
	if (yPos > 0 ) {
	  //remove can haves in other rows
	  // get can have from xPos row!
	  list <int> canHave;
	  for (int x = sqrpos.xMin; x <= sqrpos.xMax; x++) {
		if (!checkIfPosFilled(x, yPos)) {
		  canHave = GetBoxItemAtPos(x, yPos).getCanHave();
		  break;
		}		
	  }
	  //Remove can haves
   	  for (int y = sqrpos.yMin; y <= sqrpos.yMax; y++) {
		if (y != yPos) {
		  for (int x = sqrpos.xMin; x <= sqrpos.xMax; x++) {
			if ((5 == y) && (1 == x)) {
			  int ibreak = 1;	
			}	
			if ((5==x) && (3 == y)) {
				int ibreak = 1;
			}	
            int pos = magicTable[x*10+y];
            list<BoxItem>::iterator pItem = items.begin();
            advance(pItem, pos);
  	        if (!pItem->getFilled()) {
			  for (int v : canHave) {
                pItem->removeCanHave(v);
			  }	
		    }
		  }
	    }
	  }
    }
  }

  public :void detectMissingValuesFriends() {
    for (int sqr = 1; sqr <= 9; sqr++) {
	  detectMissingValuesFriendsInSquareRow(sqr);	
	}
    for (int sqr = 1; sqr <= 9; sqr++) {
  	  detectMissingValuesFriendsInSquareCol(sqr);
	}
  }

  public :bool checkMissingValuesAtPos(int x, int y) {
    int pos = magicTable[x*10+y];
	//Item item = items[pos];
    list<BoxItem>::iterator pItem = items.begin();
    advance(pItem, pos);
    //BoxItem item = *pItem;
	if (pItem->getFilled()) {
	  return true;
	} else {
	  list<int> rowValues = GetValuesForRow(y, -1, -1);
	  list<int> colValues = GetValuesForCol(x, -1, -1);
	  SquareInfo squareInfo;
	  int sqr = squareInfo.GetRutaForPos(x, y);
	  if (sqr == 0) {
	      printf("Error 001");
	  }
	  list<int> sqrValues = GetValuesForSquare(sqr);
	  list<int> values;
	  for(int value : rowValues) {
	    values.push_back(value);
	  }
	  for(int value : colValues) {
	    //if (!values.contains(value)) {
	    list<int>::iterator it;
	    it = std::find(values.begin(), values.end(), value);
	    bool found = it != values.end();
	    if (!found) {
	      values.push_back(value);
		}
	  }
	  for(int value : sqrValues) {
	    //if (!values.contains(value)) {
	    list<int>::iterator it;
	    it = find(values.begin(), values.end(), value);
	    bool found = it != values.end();
	    if (!found) {
	      values.push_back(value);
		}
	  }
	  values.sort();
	  if ((1 == x) && (5 ==  y)) {
		int ibreak = 1;
	  }
	  for (int i=1; i <= 9; i++) {
	    pItem->addCanHave(i);
	  }
	  for (int v : values) {
	    pItem->removeCanHave(v);
	  }
	  bool res = false;
	  int tmpValue = 0;
	  if (pItem->validateCanHave(tmpValue)) {
		pItem->setValue(tmpValue);
		res = true;
	  }
	  if (!res) {
		int tmpValue = 0;
		analyzeSquaresAround(x, y, tmpValue);
	  }
	  return res;
  	}
  }
  
  public :bool CheckIfFilled() {
    bool filled = true;
	for (BoxItem item : items) {
 	  if (!item.getFilled()) {
	    filled = false;
		break;
	  }
	}
	return filled;
  }

  private :bool validateSquare(int sqr) {
	SquareInfo squareInfo;
	mySquare pos = squareInfo.GetPosForSquare(sqr);
	list<int> values = GetValuesForSquare(sqr);
	bool res = true;
	for (int value = 1; value <= 9; value++) {
	  res = CheckIfValueIn(value, values);
	  if (!res) {
		break;
	  }
	}
	return res;
  }

  private :bool validateSquares() {
	bool res = true;
	for (int sqr = 1; sqr <= 9; sqr++) {
	  res = validateSquare(sqr);
  	  if (!res) {
		break;
	  }
	}
	return res;
  }

  private :bool validateRow(int y) {
	list<int> values = GetValuesForRow(y, -1, -1);
	bool res = true;
	for (int value = 1; value <= 9; value++) {
	  res = CheckIfValueIn(value, values);
	  if (!res) {
		break;
	  }
	}
	return res;
  }

  private :bool validateRows() {
	bool res = true;
	for (int y = 1; y <= 9; y++) {
	  res = validateRow(y);
	  if (!res) {
		break;
	  }
	}
	return res;
  }

  private :bool validateCol(int x) {
	list<int> values = GetValuesForCol(x, -1, -1);
	bool res = true;
	for (int value = 1; value <= 9; value++) {
	  res = CheckIfValueIn(value, values);
	  if (!res) {
		break;
	  }
	}
	return res;
  }

  private :bool validateCols() {
	bool res = true;
	for (int x = 1; x <= 9; x++) {
	  res = validateCol(x);
	  if (!res) {
		break;
	  }
	}
	return res;
  }

  public :bool validate() {
	bool res = validateSquares();
	if (res) {
	  res = validateRows();	
	}
	if (res) {
	  res = validateCols();	
	}
	return res;
  }
  
  public :void printfunction() {
    int cnt = 0;
	int rowCnt = 0;
    printf("PRINT: %d\n", printCnt);
	printCnt++;
    string szTmp = "";
    for(BoxItem item : items) {
      cnt++;
      int value = item.getValue();
      szTmp = szTmp + to_string(value);
	  if ((cnt % 3) == 0) {
		szTmp = szTmp + " ";
	  }
      if ((cnt % 9) == 0) {
        printf("%s", szTmp.c_str());
        printf("\n");
        szTmp = "";
		rowCnt++;
		if ((rowCnt % 3) == 0) {
		  printf("\n");
		}
      }
    }
	printf("\n");
  }

  private :bool trySetCheatingValueAtSquare(int sqr, int &cheatValue, int &xCheat, int &yCheat, bool tryFirst) {
	//TBD
	bool res = false;
	list<int> values = GetValuesForSquare(sqr);
	if (values.size() == 7) {
	  SquareInfo squareInfo;
	  mySquare pos = squareInfo.GetPosForSquare(sqr);
	  for (int x = pos.xMin; x <= pos.xMax; x++) {
		for (int y = pos.yMin; y <= pos.yMax; y++) {
		  BoxItem item = GetBoxItemAtPos(x, y);
		  if (!item.getFilled()) {
		    list<int> canHave = item.getCanHave();	
		    if (canHave.size() == 2) {
			  res = true;
			  xCheat = item.getX();
			  yCheat = item.getY();
			  for (int value : canHave) {
				if (tryFirst) {
			      cheatValue = value;	
			      break;
				}
 		        cheatValue = value;	
			  }
			  break;
		    }
		  }		
		}
		if (res) {
		  break;
		}
	  }
	}
	return res;
  }
  private :bool setCheatingValue(int &cheatValue, int &xCheat, int &yCheat, int &square, bool tryFirst, int notSqr) {
	bool res = false;
	for (int sqr = 1; sqr <= 9; sqr++) {
	  if (sqr != notSqr) {
	    if (trySetCheatingValueAtSquare(sqr, cheatValue, xCheat, yCheat, tryFirst)) {
		  square = sqr;
		  res = true;
		  break;
	  }
	  }
	}
	return res;
  }


  private :bool equalToLast() {
	string tmpLast = lastSavedSolution;
	save(false);
	return tmpLast.compare(lastSavedSolution) == 0;
  }

  public :string save(bool toFile) {
    int cnt = 0;
    string szTmp = "";
    for(BoxItem item : items) {
      cnt++;
      int value = item.getValue();
      szTmp = szTmp + to_string(value);
  	  if (toFile) {
	    if ((cnt % 3) == 0) {
		  szTmp = szTmp + " ";
	    }
	  }
  	  if (toFile) {
        if ((cnt % 9) == 0) {
          szTmp = szTmp +  "\n";
	    }
	  }
	}
	lastSavedSolution = szTmp;
	return lastSavedSolution;
  }

  private :void restore(string solutionBeforeCheat) {
	int pos = 0;
    for (char & c : solutionBeforeCheat) {
      list<BoxItem>::iterator pItem = items.begin();
      advance(pItem, pos);
      //BoxItem item = *pItem;
      int value = c - '0';  
	  if (value <= 9) {
	    pItem->setValue(value);
	  }
	  pos++;	
	}
  }

  private :bool findEmptyCell(int &x, int &y) {
	for (x = 1; x <= 9; x++) {
	  for (y = 1; y <= 9; y++) {
		if (!checkIfPosFilled(x,  y)) {
          return true;
		}
	  }
	}
    return false;
  }

  private :bool solveSudoku() //int grid[SIZE][SIZE]) 
  { 
    int x, y; 
    if (!findEmptyCell(x, y)) 
    { 
      printfunction(); // printGrid(grid); 
	  return true; 
	  // Grid is solved 
    } 
    for (int num = 1; num <= 9; num++) 
    { 
      if (checkIfPosCanHaveValue(x, y, num)) 
	  { 
	    setValueForPos(x, y, num);
	    if (solveSudoku()) 
	    { 
	      printfunction(); //printGrid(grid); 
		  return true; 
	    } 
	    resetValueForPos(x, y);//grid[row][col] = 0; // backtrack 
	  } 
    } 
    return false; // No solution exists
  }

  private :bool tryTrialAndError() {
	return solveSudoku();
  }

  private :bool tryTrialAndErrorDoesNotWork() {
    printfunction();
    string solutionBeforeCheat = save(false);
	for (int value = 1; value <= 9; value++) {
	  bool first = true;	
	  for (int x = 1; x <= 9; x++) {		
		for (int y = 1; y <= 9; y++) {
    	  if (!checkIfPosFilled(x, y)) {
			int start = 1;
			if (first) {
			  start = value;
			  first = false;	
			}
     	    for (int nvalue = start; nvalue <= 9; nvalue++) {
     	      if (checkIfPosCanHaveValue(x, y, nvalue)) {
				setValueForPos(x, y, nvalue);
				continue;
			  }
		    }
		  }
		}
		printfunction();
	  }
	  //Check if solved
 	  bool isFilled = CheckIfFilled();
	  bool isValid = validate();
      if (isFilled && isValid) {
		return true;
	  }
	  //else
	  restore(solutionBeforeCheat);
	}
    return false;
  }

  public :void Solution() {
	string solutionBeforeCheat;
	string solutionBeforeCheat2;
	bool cheating = false; 
	bool cheatOk = false;
	bool tryFirst = true;
	int notSqr = 0;
	int cheatValue; int xCheat; int yCheat; int cheatSqr;
	int zeroCount = 0;
    bool isValid = false;
	bool isFilled = false;
	while (not isValid) {
	  for (int x=1; x<=9; x++) {
	    for (int y=1; y<=9; y++) {
		  checkMissingValuesAtPos(x,y);
	    }
	  }
	  detectMissingValuesFriends();
	  analyzeSquares();
	  analyzeRows();
	  analyzeCols();
	  analyzeSquaresExtended();
	  if (!analyzeRowsExtended()) {
	    analyzeColsExtended();
	  }
	  analyzeExtendedPlus();

	  analyzeExtendedSquareCanNotHave();

	  isFilled = CheckIfFilled();
	  isValid = validate();
      printfunction();
	  if ((equalToLast())) {
		if (!tryTrialAndError()) {
		  if (cheating) {
		    tryFirst = !tryFirst;
		    restore(solutionBeforeCheat);
		  }
		  printf("equal\n");
		  if (!isValid) {
		    if (!cheating) {
		      solutionBeforeCheat = save(false);
		    }           
		    cheating = setCheatingValue(cheatValue, xCheat, yCheat, cheatSqr, tryFirst, notSqr);
		    if (cheating) {
			  setValueForPos(xCheat, yCheat, cheatValue);
			  if (!tryFirst) {
			    notSqr = cheatSqr;
   		        solutionBeforeCheat2 = save(false);
			  }
		    }
		    printfunction();
		  }
		  if (!cheating) {
		    //Set a cheating value
		    int value = 0; int x = 0; int y = 0;
            cout << "Please enter an integer value:  (Zero = NOT!!)";
            cin >> value;
		    if ((value >= 1) && (value <= 9)) {
              cout << "For row: ";
              cin >> y;
              cout << "For col: ";
              cin >> x;
   		      if ((x >= 1) && (x <= 9)) {
			    if ((y >= 1) && (y <= 9)) {
				  setValueForPos(x, y, value);
				  zeroCount = 0;
			    } 
		      }
		    } else {
		      zeroCount++;
		    }
		  }
		}
	  }
	  save(false);
	  if (3 <= printCnt) {
		int stop = 1;
	  }
	  if (zeroCount > 1) {
		return;
	  }

	} 
	string szExit = "Y";
    //cout << "Please press enter key to exit!";
	cout << "Ary you happy with the solution [Y or N]?";
    cin >> szExit;
	return;
  }

};

};
