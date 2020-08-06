# AMT102

### Arduino で AMT102 エンコーダーを使用するためのライブラリです

## メンバ関数

- ### AMT102::AMT102(uint8_t dipSwitch, int aInterruptNumber, int bInterruptNumber)
  - #### 意味
    コンストラクタ
  - #### 引数
    - ##### uint8_t dipSwitch
        AMT102 の背面に付属している４連スイッチの状態を二進数の４桁の数字で渡してください（上が１、下が０です）  
        よくわからない場合はデータシートを見てください。記載してあるはずです  
        例）AMT102 の背面のスイッチの状態が右から 1110 の場合、渡す数字は '0b1110' となります  
    - ##### int aInterruptNumber
        AMT102 の a 層の信号を処理するために使用する割り込みの番号です  
        この番号は Arduino の attachInterrupt() 関数に与える割り込み番号に準拠しています  
    - ##### int bInterruptNumber
        AMT102 の b 層の信号を処理するために使用する割り込みの番号です  
        この番号は Arduino の attachInterrupt() 関数に与える割り込み番号に準拠しています  

- ### void AMT102::setup()
  - #### 意味
    AMT102 エンコーダを使用する際に必要な準備をします  
    プログラムで使用する際には必ず一回呼び出してください  
  - #### 引数
    なし
  - #### 戻り値
    なし

- ### double AMT102::getRevolution()
  - #### 意味
    AMT102 エンコーダで計測した回転数を degree 単位で返します  
    なお、計測した回転数はインクリメントもしくはデクリメントされ続け、保持されます  
  - #### 引数
    なし
  - #### 戻り値
    double 型のエンコーダで計測した回転数（単位は degree ）

---

## コード例

```
#include <Arduino.h>
#include "AMT102.h"

AMT102 encoder(0b0000, 0, 1);

void setup() {
  Serial.begin(9600);
  encoder.setup();
}

void loop() {
  Serial.println(encoder.getRevolution());
}
```
出力例（１ループごとに半回転させた場合）： 
```
0.0
180.0
360.0
540.0
720.0
...
```

---

Version: 1.00  
Created: 2020/1/26  
Author: Yuki Yoshida
