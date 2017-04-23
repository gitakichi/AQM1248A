秋月電子で販売されているAQM1248AをNucleo F303K8で動かすためのMBED用のソースコードになります。
変換基板を用いています。LED1とSCLはピンを共有しているため、データ送信時に点灯します。また、SPIの速度設定をすると動作しませんでした。
初のgithubですので、ミスなどがございましたらご連絡下さい。

配線になります。
(Nucleo F303K8) --  (akiduki's AQM1248A)
3V3 --  VDD
GND --  CS
NC  --  RES
A1  --  RS
D13 --  SCL
D11 --  SDI
GND --  GND
