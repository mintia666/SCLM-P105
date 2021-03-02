//SCLM-P105 for Arduino

#include "SCLMP105.h"

/*ArduinoとSCLM-P105のピン割当 (BUSY, CLK, CS, DB0, DB1, DB2, DB3, DB4, DB5, DB6, DB7)*/
SCLMP105 sclm = SCLMP105(2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12);

void setup() {}

void loop() {

  //全画面消去
  sclm.clearDisplay();

  //7セグ表示
  sclm.setDigit(0, 1); //setDigit(桁の位置[0-9], 数値[0-25], (色番号[0-7]))
  sclm.update();        //データ転送、ディスプレイ更新
  delay(3000);
  /*  [桁の位置] 0:左上 … 9:右下
       [数値] 0-9:数字、10-25:英記号
       [色番号] 0:黒, 1:白, 2:黄, 3:紫, 4:赤, 5:水色, 6:緑, 7:青    （色番号は省略可。省略時は白色）*/

  //マーク表示
  sclm.setMark(13);  //setMark(マーク番号[0-16], (色番号[0-7]))
  sclm.update();
  delay(3000);
  /*  [マーク番号] 0:なし, 1:コロン, 2:dp(上), 3:dp(下), 4:システム, 5:なし, 6:時:分, 7:ml, 8:ml/h, 9:注入量,
                          10:積算, 11:早送り, 12:予定, 13:終了, 14:閉塞, 15:押子 16:電池
        [色番号] 0:黒, 1:白, 2:黄, 3:紫, 4:赤, 5:水色, 6:緑, 7:青    （色番号は省略可。省略時は白色）*/


  ///  demos  ///

  sclm.clearDisplay();

  //color digits
  //0 1 2 3 4
  //5 6 7 8 9
  sclm.setDigit(0, 0, 1);  sclm.setDigit(1, 1, 2);  sclm.setDigit(2, 2, 3);  sclm.setDigit(3, 3, 4);  sclm.setDigit(4, 4, 5);
  sclm.setDigit(5, 5, 6);  sclm.setDigit(6, 6, 7);  sclm.setDigit(7, 7, 1);  sclm.setDigit(8, 8, 2);  sclm.setDigit(9, 9, 3);
  sclm.update();
  delay(3000);
  sclm.clearDisplay();

  //temperatures 1
  //24
  //9
  sclm.setDigit(0, 2, 4);  sclm.setDigit(1, 4, 4);
  sclm.setDigit(5, 0, 0);  sclm.setDigit(6, 9, 7);
  sclm.update();
  delay(4000);
  sclm.clearDisplay();

  //temperatures 2
  //32.5
  //16.1
  sclm.setDigit(2, 3, 4); sclm.setDigit(3, 2, 4); sclm.setDigit(4, 5, 4);  sclm.setMark(2, 4);
  sclm.setDigit(7, 1, 7); sclm.setDigit(8, 6, 7); sclm.setDigit(9, 1, 7);  sclm.setMark(3, 7);
  sclm.update();
  delay(4000);
  sclm.clearDisplay();

  //VU meter
  int r;
  int meter[6] = {0, 13, 14, 15, 16, 4};  int mc[6] = {0, 7, 6, 6, 2, 4};
  for (int i = 0; i < 600; i++) {
    for (int n = 0; n < 6; n++) {
      sclm.setMark(meter[n], 0);
    }
    r += random(-1, 2);
    if (r < 0)r = 1; if (r > 6)r = 6;
    for (int j = 0; j < r; j++) {
      sclm.setMark(meter[j], mc[j]);
    }
    sclm.update();
    delay(10);
  }
  sclm.clearDisplay();

  //counter
  for (int i = 0; i < 9999; i++) {
    sclm.setNumber(0, i);              //setNumber(行の位置[0-1], 数値[0-9999], (色番号[0-7]))
    sclm.setNumber(1, 9999 - i);
    sclm.update();
    delay(10);
    if (i > 1200)break;
  }
  /*  [行の位置] 0:上段, 1:下段
       [数値] 0-9999
       [色番号] 0:黒, 1:白, 2:黄, 3:紫, 4:赤, 5:水色, 6:緑, 7:青    （色番号は省略可。省略時は白色）*/

  sclm.clearDisplay();

  delay(2000);
}
