# SCLM-P105

![名称未設定 3](https://user-images.githubusercontent.com/79851969/109542467-6fc3f480-7b08-11eb-8076-a7e40d74efdf.jpg)

デジットで20円で販売されている「RGBバックライト搭載 8色カラー 10桁＋固定マーク表示 7セグ液晶モジュール」のArduino用ライブラリー。

詳しい使用方法はサンプルスケッチをご覧下さい。

関数一覧

・SCLMP105(BUSY, CLK, CS, DB0, DB1, DB2, DB3, DB4, DB5, DB6, DB7)

・setDigit(桁の位置[0-9], 数値[0-25], (色番号[0-7]))

・setNumber(行の位置[0-1], 数値[0-9999], (色番号[0-7]))

・setMark(マーク番号[0-16], (色番号[0-7]))

・clearDisplay()

・update()


[色番号] 0:黒, 1:白, 2:黄, 3:紫, 4:赤, 5:水色, 6:緑, 7:青
