#include "SCLMP105.h"

//color table: 0:black, 1:white, 2:yellow, 3:violet, 4:red, 5:light blue, 6:green, 7:blue
const static unsigned int color_table[8] = {0xE0, 0x00, 0x20, 0x40, 0x60, 0x80, 0xA0, 0xC0};

SCLMP105::SCLMP105(int busy, int clk, int cs, int db0, int db1, int db2, int db3, int db4, int db5, int db6, int db7) {
  BUSY = busy;  CLK = clk;  CS = cs;
  DB0 = db0;  DB1 = db1;  DB2 = db2;  DB3 = db3;
  DB4 = db4;  DB5 = db5;  DB6 = db6;  DB7 = db7;
  pinMode(BUSY, INPUT); pinMode(CLK, OUTPUT); pinMode(CS, OUTPUT);
  pinMode(DB0, OUTPUT); pinMode(DB1, OUTPUT); pinMode(DB2, OUTPUT); pinMode(DB3, OUTPUT);
  pinMode(DB4, OUTPUT); pinMode(DB5, OUTPUT); pinMode(DB6, OUTPUT); pinMode(DB7, OUTPUT);
  digitalWrite(CS, HIGH);  digitalWrite(CLK, LOW);
  digitalWrite(DB0, LOW); digitalWrite(DB1, LOW); digitalWrite(DB2, LOW); digitalWrite(DB3, LOW);
  digitalWrite(DB4, LOW); digitalWrite(DB5, LOW); digitalWrite(DB6, LOW); digitalWrite(DB7, LOW);
  delayMicroseconds(6);
}

void SCLMP105::cmdtx(unsigned int data[]) {
  //start of data
  do {} while (digitalRead(BUSY));
  do {} while (digitalRead(BUSY)); //need a double check?
  digitalWrite(CS, LOW);
  delayMicroseconds(6);
  //data transfer
  for (int i = 0; i < 27; i++) {
    digitalWrite(CLK, HIGH);
    digitalWrite(DB0, (data[i] & 1) && 1); digitalWrite(DB1, (data[i] & 2) && 2); digitalWrite(DB2, (data[i] & 4) && 4); digitalWrite(DB3, (data[i] & 8) && 8);
    digitalWrite(DB4, (data[i] & 16) && 16); digitalWrite(DB5, (data[i] & 32) && 32); digitalWrite(DB6, (data[i] & 64) && 64); digitalWrite(DB7, (data[i] & 128) && 128);
    delayMicroseconds(6);
    do {} while (digitalRead(BUSY));
    digitalWrite(CLK, LOW);
    delayMicroseconds(6);
  }
  //end of data
  delayMicroseconds(4);
  digitalWrite(CS, HIGH);
}

void SCLMP105::clearDisplay() {
  for (int i = 0; i < 27; i++)   // all blacks
    data[i] = color_table[0];
  cmdtx(data);
}

void SCLMP105::setDigit(int digit, unsigned int value, int col = 1) {
  if (digit < 0 || digit > 9 || value < 0 || value > 63 || col < 0 || col > 7) return;
  data[digit + 17] =  color_table[col] + value;
}

void SCLMP105::setNumber(int row, unsigned int value, int col = 1) {
  if (row < 0 || row > 1 || value < 0 || value > 9999 || col < 0 || col > 7) return;
  int _value = value;
  if (_value > 999) data[17 + (row * 5)] = color_table[col] + value / 1000;
  else data[17 + (row * 5)   ] =   color_table[0];
  value = value % 1000;
  if (_value > 99) data[18 + (row * 5)] = color_table[col] + value / 100;
  else  data[18 + (row * 5)] = color_table[0];
  value = value % 100;
  if (_value > 9) data[19 + (row * 5)] = color_table[col] + value / 10;
  else data[19 + (row * 5)] = color_table[0];
  value = value % 10;
  data[20 + (row * 5)] = color_table[col] + value;
}

void SCLMP105::setMark(int mark, int col = 1) {
  if (mark < 0 || mark > 16 || col < 0 || col > 7) return;
  data[mark] =  color_table[col];
}

void SCLMP105::update() {
  cmdtx(data);
}
