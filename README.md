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

   ![bge03](https://github.com/GouNakano/GoBackgroundEraser/assets/56259253/d1deef63-7aea-4621-a269-4595fb6ff243)
   
5. 範囲指定  
   表示されている画像の部分の背景除去処理の対象範囲の左上にマウスポインタを移動します。  
   そこでマウスの左ボタンを押下したまま右下に移動します。  
   対象範囲の右下に達しましたらマウスの左ボタンを解放します。  
   GoBackgroundEraserの表示は以下の様になります。  

   ![bge04](https://github.com/GouNakano/GoBackgroundEraser/assets/56259253/e4e6c2d2-d508-466b-b0f0-9dd21a854d97)

   この時の選択範囲は、なるべく目的の前景部分の範囲に絞って設定します。  
   理由は、選択範囲の外側は全て背景として扱われ、  
   選択範囲の内側は選択範囲の外側の背景と連続的な部分を、  
   背景と認識する可能性が高くなるからです。  
   
5. 初回の更新  
   範囲選択後更新ボタンをクリックまたはエンターキー押下で初回の更新を行います。  
   初回の更新では、背景削除用のマスクの作成を行います。  
   背景除去は読み込んだ元画像に対してマスクを作用させることで、  
   マスクが白(255)の場合は、元画像の色をそのまま引き継ぎ、  
   マスクが黒(0)の場合は、透明度を0にして完全透過にします。
   そのため、出力画像はアルファチャンネルを含む４チャンネルのpng画像になります。  
   上記のlena.jpgの場合の初回更新画像は以下の様になります。  

   ![bge05](https://github.com/GouNakano/GoBackgroundEraser/assets/56259253/df37ff44-19d4-418e-ba3d-172493b1d139)

 6. 修正の操作  
    上記の更新では、帽子の左上の部分が欠けているのが分かります。  
    どの部分が問題があるかを知るには、元画像の表示ボタンをクリックして、  
    見比べて見る方法になります。  
    帽子の左上の部分の修正では、前景指定モードボタンをクリックして、  
    補正する所に白点(線)をマウスで設定します。  

    ![bge06](https://github.com/GouNakano/GoBackgroundEraser/assets/56259253/b219de4e-6b58-4e52-ac10-55d102fdd838)

    修正の設定が終わりましたら、更新ボタンをクリックします。
    更新後の画像は以下の様になります。

    

　

