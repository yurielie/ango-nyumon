# ango-nyumon
『暗号技術入門 第3版』のC++での再現ソース


## ビルド

```bash
make ango
```

## 実行

```bash
./ango --algo <暗号アルゴリズム> --text <平文> <追加の引数>...
```

### Caesar Cipher
シーザー暗号。何文字ずらすか指定


```bash
./ango --algo caesar --text <平文> <鍵(整数)>
```

### Simple Substitution Cipher
換字式暗号。ASCII印字可能文字(95種類)の範囲でランダムに換字。実行のたびに換字表を表示

```
./ango --algo simpleSubstitution --text <平文>
```
