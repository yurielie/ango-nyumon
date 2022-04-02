# ango-nyumon
『暗号技術入門 第3版』のC++での再現ソース


## ビルド

```bash
make ango
```

## 実行

```bash
.\ango.exe <平文> Args...
```

### Caesar Cipher
シーザー暗号。何文字ずらすか指定

```bash
.\ango.exe caesar <平文> <鍵(整数)>
```

### Simple Substitution Cipher
換字式暗号。アルファベット52文字([a-zA-Z])をランダムに換字。実行のたびに換字表を表示

```bash
.\ango.exe simpleSubstitution <平文>
```
