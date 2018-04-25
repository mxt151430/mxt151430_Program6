/*
 * File: cdkexample.cc
 * When made by makefile will output to program6
 * Author: Michael Teeple 
 * Email:  mxt151430@utdallas.edu
 */

#include <cstdint>
#include <fstream>
#include <ios>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include "cdk.h"

//Setting the box dimension
#define BOX_WIDTH 25
#define MATRIX_HEIGHT 5
#define MATRIX_NAME_STRING "Binary File Contents"
#define MATRIX_WIDTH 3
#define MAX_RECORD_STRING_LENGTH 25

using namespace std;

//Information provided to us by Homework
class BinaryFileHeader {
public:
  uint32_t magicNumber;
  uint32_t versionNumber;
  uint64_t numRecords;
};

class BinaryFileRecord{
public:
  uint8_t strLength;
  char stringBuffer[MAX_RECORD_STRING_LENGTH];
};

int main()
{

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  //setting the rows and columns area
  const char 		*rowTitles[MATRIX_HEIGHT+1]={" R0", "R1", "R2", "R3", "R4", "R5"};
  const char 		*columnTitles[MATRIX_WIDTH+1] = {"C0", "C1", "C2", "C3" };
  int		boxWidths[MATRIX_WIDTH+1] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[MATRIX_HEIGHT+1] = {vMIXED, vMIXED, vMIXED, vMIXED};


  // Initialize the Cdk screen.
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  // Create the matrix. Manually casting (const char**) to (char **)
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }
  
  //  Binary File Stream
  ifstream binInfile("cs3377.bin", ios::in | ios::binary);

  // Displaying the Header
  BinaryFileHeader *myHeader = new BinaryFileHeader();
  binInfile.read((char*) myHeader, sizeof(BinaryFileHeader));

  stringstream magicNumber;
  magicNumber << "Magic: " << "0x" << hex << myHeader->magicNumber;
  stringstream versionNumber;
  versionNumber << "Version: " << dec << myHeader->versionNumber;
  stringstream numRecords;
  numRecords << "NumRecords: " << myHeader->numRecords;
  //Setting the matrix cells
  setCDKMatrixCell(myMatrix, 1, 1, magicNumber.str().c_str());
  setCDKMatrixCell(myMatrix, 1, 2, versionNumber.str().c_str());
  setCDKMatrixCell(myMatrix, 1, 3, numRecords.str().c_str());

  // Displaying Records 
  
  for (int i = 2; i <= 5 && i <= (int) myHeader->numRecords+1; i++) {
    BinaryFileRecord *myRecord = new BinaryFileRecord();
    binInfile.read((char*) myRecord, sizeof(BinaryFileRecord));

    char str[2];
    sprintf(str, "%d", myRecord->strLength);
    stringstream strLength;
    strLength << "strlen: " << str;
    //setting matrix cells
    setCDKMatrixCell(myMatrix, i, 1, strLength.str().c_str());
    setCDKMatrixCell(myMatrix, i, 2, myRecord->stringBuffer);
  }
  
  // Display a message
  drawCDKMatrix(myMatrix, true);
  
  // Sleep for 15 seconds to show result
  sleep(15);

  // Clean Exit
  endCDK();

  return 0;
}
