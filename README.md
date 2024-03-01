## 実習環境  
＜開発マシン＞  
メインPC : windows11  
仮想化ソフト : VMWare  
Linux : Debian7.6  
コンパイラ : gcc    
コードエディター : VScode  
ターミナル : TeraTerm
  
<ターゲットボード>  
実習ボード : アットマークテクノ製「Armadillo-460」   
組込みLinux : アットマークテクノ製「Atmark-dist」を改変

## 動作
ターゲットボードのLCD画面に5秒ごとに表示画像を切り替える  
画像ファイル形式:bmp

## 実行  
1.開発マシンで「make」コマンド  
2.開発マシンで「make install」コマンド  
3.LCD画面に表示したいbmpファイル(01.bmp,02.bmp,03.bmp, 04.bmp, 05.bmp)をターゲットボードのLinuxにコピー  
※bmpファイルは画像サイズ480×272以下、非圧縮、1ピクセルあたり24bit  
4.ターゲットボードで「./bmptest」コマンド 
