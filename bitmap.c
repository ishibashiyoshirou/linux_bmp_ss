#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bitmap.h"

/*RGB565への変換*/
int bmp2RGB565(FILE * fpbmp, unsigned short *pfb, int max_x, int max_y) {
	int fd_in;
	int datasize;
	int x0, x1 ,y0 ,y1 ,xx, yy;
	int padding;
	int c = 0;
	unsigned char *bmpdata;
	unsigned char r, g, b;

	/*ヘッダ情報構造体*/
	struct bmpheader_t{
		BITMAPFILEHEADER fh;
		BITMAPINFOHEADER ih;
	} bmp;

	/*ヘッダ情報を変数に格納*/
	if (fread(&bmp, sizeof(bmp), 1, fpbmp) != 1){
		perror("fread(file)");
		return -1;
	}

	/*BMPファイルか？色は24bitか？非圧縮か？高さは0以上か？*/
	if (bmp.fh.bfType != 0x4d42 || bmp.ih.biBitCount != 24
		|| bmp.ih.biCompression != 0 || bmp.ih.biHeight < 0){
		fprintf(stderr, "unsupported bitmap format\n");
		return -1;
	}

	/*幅と高さはLCDのサイズ以下か?*/
	if (bmp.ih.biWidth > max_x || bmp.ih.biHeight > max_y){
		fprintf(stderr, "image size too big\n");
		return -1;
	}
	/*画像データのサイズ計測*/
	datasize = bmp.fh.bfSize - sizeof(bmp);
	
	/*画像データサイズ分のメモリ確保*/
	if (!(bmpdata = malloc(datasize))){
		perror("malloc");
		return -1;
	}
	/*画像データをmallocで確保したメモリに格納
	　※freadは連続で使用するとファイルの途中から読み込む*/
	if (fread(bmpdata, datasize, 1, fpbmp) != 1){
		perror("fread(file)");
		free(bmpdata);
		return -1;
	}

	/*LCD画面を黒に*/
	memset(pfb, 0, max_x * max_y * 2);

	/*画像を中央揃えで出力*/
	/*左上の座標*/
	x0 = (max_x - bmp.ih.biWidth) / 2;
	y0 = (max_y - bmp.ih.biHeight) / 2;
	/*右下の座標*/
	x1 = x0 + bmp.ih.biWidth;
	y1 = y0 + bmp.ih.biHeight;
	padding = bmp.ih.biWidth % 4; //1ライン毎に読み飛ばすバイト数

	
	/*画像データをRGB565に変換しmmapで取得したpfb配列に格納
	 ※bmpファイルは上下反転しているので左下よりスタート*/
	for(yy = y1 - 1; yy >= y0; yy--){
		for(xx = x0; xx < x1; xx++){
			b = bmpdata[c++];
			g = bmpdata[c++];
			r = bmpdata[c++];
			pfb[yy * max_x + xx] = 
			((r & 0xf8) << 8 | (g & 0xfc) << 3 | (b & 0xf8) >> 3);
		}
		c += padding; //読み飛ばし
	}
	free(bmpdata); //mallocで確保したメモリを解放
	return 0;
}

/*bmpファイルを開いてRGB565変換関数を呼び出す*/
int load_bmp(char *filename, unsigned short *pfb, int max_x, int max_y){
	FILE * fpbmp;

	if ((fpbmp=fopen(filename, "rb")) == NULL) {
		perror("fopen(file)");
		return -1;
	}
	bmp2RGB565(fpbmp, pfb, max_x, max_y);
	fclose(fpbmp);
	return 0;
}
