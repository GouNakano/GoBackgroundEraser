# 対話形式で画像から背景を除去する　GoBackgroundEraser

## 概要

GoBackgroundEraserは簡単な操作で画像の背景を除去するアプリです。  
画像を読み込んで範囲指定をして更新で初回の背景除去をした後、  
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
   
   ![bge01](https://github.com/GouNakano/GoBackgroundEraser/assets/56259253/8a856dd4-99f5-47a3-8ce7-833ac26ff509)

3. 画像の読込  
   画像読込ボタンクリックか、メニューの「ファイル(<ins>F</ins>)-画像読込(<ins>O</ins>)」を選択します。  
   開くダイアログで目的の画像のある場所に移動して、bmpかjpegかpngのファイルを指定します。  
   この場の説明では、sampleフォルダにあるlena.jpgを指定します。  

   ![bge02](https://github.com/GouNakano/GoBackgroundEraser/assets/56259253/249dd183-108f-43f8-b59b-6750649ac4a4)

   開くボタンをクリックすると、画像ファイル(lena.jpg)読み込まれて、 
   GoBackgroundEraserの表示は以下の様になります。  

   ![bge03](https://github.com/GouNakano/GoBackgroundEraser/assets/56259253/185917e3-6ffd-40dd-82cc-c9d48d813eed)
   
4. 範囲指定  
   表示されている画像の部分の背景除去処理の対象範囲の左上にマウスポインタを移動します。  
   そこでマウスの左ボタンを押下したまま右下に移動します。  
   対象範囲の右下に達しましたらマウスの左ボタンを解放します。  
   GoBackgroundEraserの表示は以下の様になります。  

   ![bge04](https://github.com/GouNakano/GoBackgroundEraser/assets/56259253/b449fadf-41e3-4630-a47a-fd0b18749e9f)

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

   ![bge05](https://github.com/GouNakano/GoBackgroundEraser/assets/56259253/7d17ac19-ff8f-4b2e-90e5-aa081d268703)

 6. 修正の操作  
    上記の更新では、帽子の左上の部分が欠けているのが分かります。  
    どの部分が問題があるかを知るには、元画像の表示ボタンをクリックして、  
    見比べて見る方法になります。  
    帽子の左上の部分の修正では、前景指定モードボタンをクリックして、  
    補正する所に白点(線)をマウスで設定します。  

    ![bge06](https://github.com/GouNakano/GoBackgroundEraser/assets/56259253/30a98e27-f571-44dd-8ee9-e892ff78e7ee)

    修正の設定が終わりましたら、更新ボタンをクリックします。  
    更新後の画像は以下の様になります。  

    ![bge07](https://github.com/GouNakano/GoBackgroundEraser/assets/56259253/734fd85e-2265-4385-906f-c7592d1181fb)

    更新の結果が想いと異なる場合は、元に戻すかCTRL+Zキー押下で、 
    更新前の状態に戻す事が出来ます。  

    次に肩の高さの左側に、背景となるべき所が映り込んでいますので、  
    背景指定モードボタンをクリックして、
    補正する所に黒点(線)をマウスで設定します。
    ※赤丸は位置を強調するために後で追加したもので、実際には描画されません。

    ![bge08](https://github.com/GouNakano/GoBackgroundEraser/assets/56259253/9dfdea09-0b9e-4365-be9d-eb4796f0cb2b)

    修正の設定が終わりましたら、更新ボタンをクリックします。  
    更新後の画像は以下の様になります。

    ![bge09](https://github.com/GouNakano/GoBackgroundEraser/assets/56259253/01503748-34a5-4bee-b494-3e98a6ea8745)

    この様に修正操作を繰り返してマスクを更新して行き、
    完成を目指す事になります。
    
7. 画像の保存
   修正が終わりましたら、画像保存ボタンクリックかメニューの「ファイル(<ins>F</ins>)-画像保存(<ins>S</ins>)」を選択か、  
   CTRL+Sキー押下で名前を付けて保存ダイアログを表示します。

   ![bge10](https://github.com/GouNakano/GoBackgroundEraser/assets/56259253/9ebe94eb-9a3f-4e3d-999a-87f03e4399a2)

   保存後のファイルをエクスプローラで表示すると、
   背景として指定した領域が透明のpngファイルが作成されているのが分かります。

   ![bge11](https://github.com/GouNakano/GoBackgroundEraser/assets/56259253/c0754c48-b94a-48c6-bc0d-ee1fe0b90a96)
   
    

    

　

