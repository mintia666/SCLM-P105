#ifndef SCLMP105_h
#define SCLMP105_h
#include <Arduino.h>

class SCLMP105 {
  public:
    SCLMP105(int busy, int clk, int cs, int db0, int db1, int db2, int db3, int db4, int db5, int db6, int db7);
    void clearDisplay();
    void setDigit(int digit, unsigned int value, int col = 1);
    void setNumber(int row, unsigned int value, int col = 1);
    void setMark(int mark, int col = 1);
    void update();
  private :
    unsigned int data[27];
    void cmdtx(unsigned int data[]);
    int BUSY, CLK, CS;
    int DB0, DB1, DB2, DB3, DB4, DB5, DB6, DB7;
};

#endif	//SCLMP1055.h
