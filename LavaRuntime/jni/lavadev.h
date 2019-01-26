extern  void emu_drawText(char *str,int x,int y,int r,int g,int b,int size);
extern void emu_drawRGB(int r,int g,int b);
extern int decompress_one_file(char *infilename, char *outfilename);
extern int compress_one_file(char *infilename, char *outfilename);
extern int emu_startTimer(int id,void* data,long delay,long period);
extern int emu_createTimer(char *bstr);
extern void emu_toast(char* str);
extern void emu_refs(int x,int y,int w,int h);
extern int emu_loadImageForPak(char *bstr);

extern void emu_drawImage(int imgid,int x,int y);

extern void unzipfile(char *src,char *destfile);

extern void emu_deleteTimer(int id);

extern void emu_destroyImage(int id);
