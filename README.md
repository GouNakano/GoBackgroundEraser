# 対話形式で画像から背景を除去する　GoBackgroundEraser

## 概要

GoBackgroundEraserから簡単な操作で背景を除去するアプリです。  
画像を読み込んだ後、範囲指定をして更新で初回の背景除去をした後、  
背景指定や前景指定をして更新をするサイクルを繰り返して、  
目的の背景を除去した画像を保存します。  
保存した画像はpng形式で、背景は透明となります。

## 開発環境
1. OS
  Windows10,11
2. コンパイラ及びIDE
 C++Builder 10.3 Comminuty Edition  
3. 使用Staticライブラリ
   Openv 3.2.0
   C++Builder付属のVCL
4. 使用動的ライブラリ(.dll,.ocxなど)
   GoBackgroundEraserのための固有のものは無し  
   (単独で動作可能
6. 使用言語
   C++(17)
   一部にC++Builder独自のC++拡張部分を含む
   
## 実行環境
1. OS  
  Windows10,11
2. 他に必要なソフト
   無し
   
## 操作方法

1. ダウンロード  
   git cloneやzip形式で本リポジトリをダウンロード出来ます。
   zip形式でダウンロードした場合は全て展開して下さい。
   実行に必要な部分だけ必要な場合は、
   GoBackgroundEraserのGoBackgroundEraserフォルダだけを  
   ダウンロード後に別の場所にコピーして下さい。
2. 起動  
   GoBackgroundEraser.exe をダブルクリックして起動してください。
   起動すると以下の様な画面が表示されます。
   
   ![bge01](https://github.com/GouNakano/GoBackgroundEraser/assets/56259253/2e69011c-02e9-4d81-89da-ae4bc3bf3812)
   
4. 画像の読込
   画像読込ボタンクリックか、メニューの「ファイル(<ins>F</ins>)-画像読込(<ins>O</ins>)」を選択します。
   開くダイアログで目的の画像のある場所に移動して、bmpかjpegかpngのファイルを指定します。
   この場の説明では、sampleフォルダにあるlena.jpgを指定します。

   ![bge02](https://github.com/GouNakano/GoBackgroundEraser/assets/56259253/dc2dc9c3-90bf-4bb5-8766-8e0212e9f6e1)

   開くボタンをクリックすると、画像ファイル(lena.jpg)読み込まれて、
   GoBackgroundEraserの表示は以下の様になります。
   
   

 

　

