#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include "bitmap.h"

/*LCDを使用するための準備*/
#define DEVFB "/dev/fb0"
#define SCREENWIDTH	480
#define SCREENHEIGHT	272
#define SCREENSIZE	(SCREENWIDTH * SCREENHEIGHT * 2)

/*bmpファイル*/
char *bmpfile[]={	"01.bmp",
			"02.bmp",
			"03.bmp",
			"04.bmp",
			"05.bmp",
			NULL};

int main(int argc,char *argv[])
{
	int fd;
	int ret;
	unsigned short *pfb;
	char buf[256];
	int bmp_n=0;

	/*LCDデバイスファイルを開く*/
	fd=open(DEVFB,O_RDWR);
	if (fd<0) {
		perror("open(fb)");
		return 1;
	}
	
	/*LCD画面サイズ分メモリマッピング*/
	pfb = mmap(0, SCREENSIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	if (pfb == MAP_FAILED){
		perror("mmap"); 
		close(fd);
		return 1;
	}
	
	/*LCD画面を黒に*/
	memset(pfb, 0, SCREENSIZE);

	/*画像を5秒毎に切り替えてLCDに出力*/
	while(1){
		load_bmp(bmpfile[bmp_n],pfb,SCREENWIDTH,SCREENHEIGHT);
		bmp_n++;
		if(bmpfile[bmp_n]==NULL)bmp_n=0;
		sleep(5);
	}
	close(fd);
	return 0;
}

