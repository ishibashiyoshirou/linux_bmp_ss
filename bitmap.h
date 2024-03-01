typedef struct tagBITMAPFILEHEADER{ //ビットマップファイルヘッダ 14バイト
	unsigned short	bfType; //識別子0x4d42('B', 'M')
	unsigned long	bfSize; //ファイルサイズ
	unsigned short	bfReserved1;
	unsigned short	bfReserved2;
	unsigned long	bfOffBits; //ファイル内の画像データ開始位置
} __attribute__((packed)) BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER{ //ビットマップ情報ヘッダ 40バイト
	unsigned long	biSize; //情報ヘッダサイズ
	long		biWidth; //画像の幅
	long		biHeight; //画像の高さ
	unsigned short	biPlanes; //プレーン数(1に固定)
	unsigned short	biBitCount; //1ピクセルあたりのビット数
	unsigned long	biCompression; //圧縮タイプ
	unsigned long	biSizeImage; //画像データサイズ
	long		biXPixPerMeter; //横1mあたりのピクセル数
	long		biYPixPerMeter; //縦1mあたりのピクセル数
	unsigned long	biClrUsed; //パレット数
	unsigned long	biClrImporant; //重要パレット数
} __attribute__((packed)) BITMAPINFOHEADER;

/*プロトタイプ宣言*/
int bmp2RGB565(FILE * fpbmp, unsigned short *pfb, int max_x, int max_y);
int load_bmp(char *filename, unsigned short *pfb, int max_x, int max_y);
