
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<X11/Xlib.h>
#include<X11/Xutil.h>
#include<ppm.h>
#include<math.h>


void error();
pixel nearest(double Px,double Py, pixel **input, int x_max, int y_max);
pixel bi_linear(double Px,double Py,pixel **input,int cols,int rows);
void interpolation(int out_cols,int out_rows,double x_min,double y_min,pixel **input,pixel **output,double ad,double bd,double cd,double dd,double ed,double fd,int mode,int cols,int lows,gray maxval);
void calclation(double x,double y,double *u,double *v,double ***mat);
void shear(pixel **input,int in_cols,int in_rows,gray maxval,int mode);
void magnication(pixel **input,int in_cols,int in_rows,gray maxval,int mode);
void rotation(pixel **input,int in_cols,int in_rows,gray maxval,int mode);
void parallel(pixel **input, int in_cols, int in_rows, gray maxval, int mode);
void scare(double ***matrix);
int bit_count(unsigned int x);
double setpivot(double **a,double **b,int n);
void inverse_calc(double ***matrix,double *a,double *b,double *c,double *d,double *e,double *f);
void color_view(pixel **ppm_trans, int x, int y, int maxval);
void output(pixel **output,int cols,int rows,gray maxval);
void menu(pixel **input, int cols, int rows, gray maxval, int mode_1);

//エラー
void error()
{
  printf("不正な値が入力されました。プログラムを終了します。\n");
  exit(1);
}

//最近隣内挿法
pixel nearest(double Px,double Py, pixel **input, int cols, int rows)
{
  int Pk,Pl,l,k;
  pixel data;
  Pk=(int)(Px+0.5);
  Pl=(int)(Py+0.5);

  if((0>Pk)||(Pk>=cols)||(0>Pl)||(Pl>=rows)){
    data.r = 255;
    data.g = 255;
    data.b = 255;
     }
    else data=input[Pl][Pk];

  return data;

}

//共一次内挿法
pixel bi_linear(double Px,double Py,pixel **input,int cols,int rows){
  pixel data,P[2][2];
  int Pk,Pl,l,k;
  double fact[2][2];

  Pk = (int)Px;
  Pl = (int)Py;

  fact[0][0]=(Pk+1-Px)*(Pl+1-Py);
  fact[0][1]=(Px-Pk)*(Pl+1-Py);
  fact[1][0]=(Pk+1-Px)*(Py-Pl);
  fact[1][1]=(Px-Pk)*(Py-Pl);

  for(k=0;k<=1;k++){
    for(l=0;l<=1;l++){
      if((0>Pk+k)||(Pk+k>=cols)||(0>Pl+l)||(Pl+l>=rows)){
      P[l][k].r = 255;
      P[l][k].g = 255;
      P[l][k].b = 255;
      }
      else P[l][k]=input[Pl+l][Pk+k];
    }
  }


  data.r = fact[0][0]*P[0][0].r+fact[0][1]*P[0][1].r+fact[1][0]*P[1][0].r+fact[1][1]*P[1][1].r;
  data.g = fact[0][0]*P[0][0].g+fact[0][1]*P[0][1].g+fact[1][0]*P[1][0].g+fact[1][1]*P[1][1].g;
  data.b = fact[0][0]*P[0][0].b+fact[0][1]*P[0][1].b+fact[1][0]*P[1][0].b+fact[1][1]*P[1][1].b;

  return data;
 
  } 

//内挿法
void interpolation(int out_cols,int out_rows,double x_min,double y_min,pixel **input,pixel **out,double ad,double bd,double cd,double dd,double ed,double fd,int mode,int cols,int rows,gray maxval){
  int x,y;
  double Px,Py;
  pixel Pdata;

  for(y=0;y<out_rows;y++){
    for(x=0;x<out_cols;x++){

      Px=(x_min+x)*(ad)+(y_min+y)*(bd)+ed;
      Py=(x_min+x)*(cd)+(y_min+y)*(dd)+fd;

      switch(mode){
      case 1 : Pdata = nearest(Px,Py,input,cols,rows);
	break; 
      case 2 : Pdata = bi_linear(Px,Py,input,cols,rows);
	break;
      default : exit(1);
      }
     out[y][x] = Pdata;
    }
  }
  menu(out,out_cols,out_rows,maxval,mode);
}

void calclation(double x,double y,double *u,double *v,double ***mat){

  *u=((*mat)[0][0])*x+((*mat)[0][1])*y+((*mat)[0][2])*1.0;
  *v=((*mat)[1][0])*x+((*mat)[1][1])*y+((*mat)[1][2])*1.0;

}

//拡大、縮小
void magnication(pixel **input,int in_cols,int in_rows,gray maxval,int mode)
{
  int i,out_rows,out_cols;
  double **matrix,x[4],y[4],ad,bd,cd,dd,ed,fd,mag_x,mag_y;
  char mag[256];
  char *endptr;
  double x_max=0,y_max=0,x_min=0,y_min=0;
  pixel **output;
  scare(&matrix);
  printf("画像の拡大・縮小の変換処理を実行します。x軸方向の倍率を実数で入力してください。\n");
  printf(">");
  scanf("%s",mag);
  mag_x = strtod(mag,&endptr);
  if(*endptr!='\0')
    {error();}
  printf("画像の拡大・縮小の変換処理を実行します。y軸方向の倍率を実数で入力してください。\n");
  printf(">");
  scanf("%s",mag);
  mag_y = strtod(mag,&endptr);
  if(*endptr!='\0')
    {error();}
  matrix[0][0]=mag_x;
  matrix[0][1]=0;
  matrix[0][2]=0;
  matrix[1][0]=0;
  matrix[1][1]=mag_y;
  matrix[1][2]=0;
  matrix[2][0]=0;
  matrix[2][1]=0;
  matrix[2][2]=1;
  calclation(0,0,&x[0],&y[0],&matrix);
  calclation(in_cols,0,&x[1],&y[1],&matrix);
  calclation(0,in_rows,&x[2],&y[2],&matrix);
  calclation(in_cols,in_rows,&x[3],&y[3],&matrix);

  x_max=x_min=x[0];
  y_max=y_min=y[0];
 
  for(i=1;i<4;i++){if(x[i]>=x_max)x_max = x[i];}
  for(i=1;i<4;i++){if(x[i]<=x_min)x_min = x[i];}
  for(i=1;i<4;i++){if(y[i]>=y_max)y_max = y[i];}
  for(i=1;i<4;i++){if(y[i]<=y_min)y_min = y[i];}

  out_cols=(int)x_max-(int)x_min;
  out_rows=(int)y_max-(int)y_min;

  output = ppm_allocarray(out_cols,out_rows);//逆

  inverse_calc(&matrix,&ad,&bd,&cd,&dd,&ed,&fd); 
interpolation(out_cols,out_rows,x_min,y_min,input,output,ad,bd,cd,dd,ed,fd,mode,in_cols,in_rows,maxval);
}

//線断
void shear(pixel **input,int in_cols,int in_rows,gray maxval,int mode)
{
  int i,out_rows,out_cols;
  double **matrix,x[4],y[4],ad,bd,cd,dd,ed,fd,move_x,move_y,kx,ky;
  char move[256];
  char *endptr;
  double x_max=0,y_max=0,x_min=0,y_min=0;
  pixel **output;
  scare(&matrix);

  printf("画像のせん断の変換処理を実行します。x軸方向の移動量を実数で入力してください。\n");
  printf(">");
  scanf("%s",move);
  move_x = strtod(move,&endptr);
  if(*endptr!='\0')
    {error();}
  printf("画像のせん断の変換処理を実行します。y軸方向の移動量を実数で入力してください。\n");
  printf(">");
  scanf("%s",move);
  move_y = strtod(move,&endptr);
  if(*endptr!='\0')
    {error();}

  kx=(move_x)/(in_rows);
  ky=(move_y)/(in_cols);
  matrix[0][0]=1;
  matrix[0][1]=kx;
  matrix[0][2]=0;
  matrix[1][0]=ky;
  matrix[1][1]=1;
  matrix[1][2]=0;
  matrix[2][0]=0;
  matrix[2][1]=0;
  matrix[2][2]=1;
 
  calclation(0,0,&x[0],&y[0],&matrix);
  calclation(in_cols,0,&x[1],&y[1],&matrix);
  calclation(0,in_rows,&x[2],&y[2],&matrix);
  calclation(in_cols,in_rows,&x[3],&y[3],&matrix);

  x_max=x_min=x[0];
  y_max=y_min=y[0];
 
  for(i=1;i<4;i++){if(x[i]>=x_max)x_max = x[i];}
  //printf("xmax=%lf",x_max);
  for(i=1;i<4;i++){if(x[i]<=x_min)x_min = x[i];}
  //printf("xmin=%lf",x_min);
  for(i=1;i<4;i++){if(y[i]>=y_max)y_max = y[i];}
  //printf("ymax=%lf",y_max);
  for(i=1;i<4;i++){if(y[i]<=y_min)y_min = y[i];}
  //printf("ymin=%lf",y_min);

  out_cols=(int)x_max-(int)x_min;
  //printf("outrows=%d",out_cols);
  out_rows=(int)y_max-(int)y_min;
  //printf("outcols=%d",out_rows);

  output = ppm_allocarray(out_cols,out_rows);

  inverse_calc(&matrix,&ad,&bd,&cd,&dd,&ed,&fd); 
interpolation(out_cols,out_rows,x_min,y_min,input,output,ad,bd,cd,dd,ed,fd,mode,in_cols,in_rows,maxval);
}

 //回転
void rotation(pixel **input,int in_cols,int in_rows,gray maxval,int mode){

  pixel **output;
  int i,out_cols,out_rows;
  char in_angle[256],*endptr;
  double angle,rad,**matrix,x[4],y[4],x_max=0,x_min=0,y_max=0,y_min=0,
    ad,bd,cd,dd,ed,fd;

  printf("画像の変換処理を実行します。回転させる角度を実数で入力してください。\n");
  scanf("%s",in_angle);
  angle = strtod(in_angle,&endptr);
  if(*endptr!='\0')
    {error();}
  rad = (angle/180)*M_PI;
  //printf("%lf",rad);
  scare(&matrix);

  (matrix)[0][0]=cos(rad);
  (matrix)[0][1]=sin(rad);
  (matrix)[0][2]=0;
  (matrix)[1][0]=(-sin(rad));
  (matrix)[1][1]=cos(rad);
  (matrix)[1][2]=0;
  (matrix)[2][0]=0;
  (matrix)[2][1]=0;
  (matrix)[2][2]=1;

 
  calclation(0,0,&x[0],&y[0],&matrix);
  calclation(in_cols,0,&x[1],&y[1],&matrix);
  calclation(0,in_rows,&x[2],&y[2],&matrix);
  calclation(in_cols,in_rows,&x[3],&y[3],&matrix);

  for(i=0;i<4;i++){if(x[i]>=x_max)x_max = x[i];}
  for(i=0;i<4;i++){if(x[i]<=x_min)x_min = x[i];}
  for(i=0;i<4;i++){if(y[i]>=y_max)y_max = y[i];}
  for(i=0;i<4;i++){if(y[i]<=y_min)y_min = y[i];}
  

  out_cols = (int)x_max - (int)x_min;
  out_rows = (int)y_max - (int)y_min;
  

  output = ppm_allocarray(out_cols,out_rows); 

  inverse_calc(&matrix,&ad,&bd,&cd,&dd,&ed,&fd); 

  interpolation(out_cols,out_rows,x_min,y_min,input,output,ad,bd,cd,dd,ed,fd,mode,in_cols,in_rows,maxval);

}

//平行移動
void parallel(pixel **input, int in_cols, int in_rows, gray maxval, int mode)
{
  double **matrix,dis_x,dis_y,x[4],y[4],a,b,c,d,e,f,x_max,x_min,y_max,y_min;
  pixel **output;
  int i,value,out_cols,out_rows;
  char mag_c[256],*endptr;
  char dis[256];
  x_max=0;
  y_max=0;
  x_min=0;
  y_min=0;
  printf("変換処理を実行します。移動したい座標を実数で指定してください\n");
  printf("x軸>");
  scanf("%s",dis);
  dis_x = strtod(dis,&endptr);
  if(*endptr!='\0')
    {error();}
  printf("y軸>");
  scanf("%s",dis);
  dis_y = strtod(dis,&endptr);
  if(*endptr!='\0')
    {error();}
  scare(&matrix);
  matrix[0][0]=1;
  matrix[0][1]=0;
  matrix[0][2]=dis_x;
  matrix[1][0]=0;
  matrix[1][1]=1;
  matrix[1][2]=dis_y;
  matrix[2][0]=0;
  matrix[2][1]=0;
  matrix[2][2]=1;

  calclation(0,0,&x[0],&y[0],&matrix);
  calclation(in_cols,0,&x[1],&y[1],&matrix);
  calclation(0,in_rows,&x[2],&y[2],&matrix);
  calclation(in_cols,in_rows,&x[3],&y[3],&matrix);
 

  x_max=x_min=x[0];
  y_max=y_min=y[0];



  for(i=1;i<4;i++){if(x[i]>=x_max)x_max = x[i];}
  for(i=1;i<4;i++){if(x[i]<=x_min)x_min = x[i];}
  for(i=1;i<4;i++){if(y[i]>=y_max)y_max = y[i];}
  for(i=1;i<4;i++){if(y[i]<=y_min)y_min = y[i];}

  
  out_cols=(int)x_max-(int)x_min;
  out_rows=(int)y_max-(int)y_min;


 output = ppm_allocarray(out_cols,out_rows); 
  
 inverse_calc(&matrix,&a,&b,&c,&d,&e,&f);
 
 x_min=y_min=0;
  interpolation(out_cols,out_rows,x_min,y_min,input,output,a,b,c,d,e,f,mode,in_cols,in_rows,maxval);

}

//二次元配列の動的確保
void scare(double ***matrix){
  int i;
  *matrix = (double**)malloc(sizeof(double*)*3);
  for(i=0;i<3;i++)(*matrix)[i] = (double*)malloc(sizeof(double)*3);
}


int bit_count(unsigned int x) {
  x=x-((x>>1)&0x55555555);
  x=(x&0x33333333)+((x>>2)&0x33333333);
  x=(x+(x>>4))&0x0f0f0f0f;
  x=x+(x>>8);
  x=x+(x>>16);

  return x & 0x0000003f;
}

//逆行列の軸
double setpivot(double **a,double **b,int n)
{ 
  double pivot,temp;
  int i=n;
  int j,k;
  while(fabs(a[i][n])<1e-10)
    {i++;
      if(i==3)
        { for(k=0;k<3;k++){
	    for(j=0;j<3;j++)printf("%lf\n",a[k][j]);
	  }
	  printf("逆行列が存在しません。\n");
	  printf("プログラムを終了します。\n");
	  exit(1);}}
  pivot=a[i][n];
  if(i!=n){
    for(j=0;j<3;j++)
      {temp=a[n][j];
        a[n][j]=a[i][j];
        a[i][j]=temp;
        temp=b[n][j];
        b[n][j]=b[i][j];
        b[i][j]=temp;}}
  return pivot;
}

//逆行列
void inverse_calc(double ***matrix,double *a,double *b,double *c,double *d,double *e,double *f)
{
  int i,j,n;
  static double **inv_A;
  double pivot,temp;
  double **A;

  A=(double **)malloc(sizeof(double*)*3);
  inv_A=(double **)malloc(sizeof(double*)*3);
  for(i=0;i<3;++i)
    {
      A[i]=(double *)malloc(sizeof(double)*3);
      inv_A[i]=(double *)malloc(sizeof(double)*3);
    }

  A[0][0]=(*matrix)[0][0];
  A[0][1]=(*matrix)[0][1];
  A[0][2]=(*matrix)[0][2];
  A[1][0]=(*matrix)[1][0];
  A[1][1]=(*matrix)[1][1];
  A[1][2]=(*matrix)[1][2];
  A[2][0]=(*matrix)[2][0];
  A[2][1]=(*matrix)[2][1];
  A[2][2]=(*matrix)[2][2];
  

  for(i=0;i<3;++i)
    {
      for(j=0;j<3;++j){
	if(i==j)
	  {inv_A[i][j]=1;}
	else{
	  inv_A[i][j]=0;}
      }
    }
 
  for(n=0;n<3;++n){
    pivot=setpivot(A,inv_A,n);
      for(j=0;j<3;++j)
        {A[n][j]=(A[n][j])/pivot;
	  inv_A[n][j]=(inv_A[n][j])/pivot;}
  
  for(i=0;i<3;++i)
    {temp=A[i][n];
      if(i!=n)
        for(j=0;j<3;++j)
          {A[i][j]-=temp*A[n][j];
            inv_A[i][j]-=temp*inv_A[n][j];}
      
    }
}
  
  *a=inv_A[0][0];
  *b=inv_A[0][1];
  *e=inv_A[0][2];
  *c=inv_A[1][0];
  *d=inv_A[1][1];
  *f=inv_A[1][2];
}

void color_view(pixel **ppm_trans, int x, int y, int maxval) {
  Display *disp;
  Window win;
  GC gc;
  Colormap cmap;
  XImage *im;
  XSetWindowAttributes at;
  XEvent ev;
  unsigned long *data;
  Visual *visual;
  int depth;

  data=(unsigned long *)malloc((size_t)x*y*sizeof(unsigned long));

  disp=XOpenDisplay(NULL);
  win=XCreateSimpleWindow(disp,DefaultRootWindow(disp),0,0,x,y,0,
			  BlackPixel(disp,0),WhitePixel(disp,0));
  at.override_redirect = False;
  at.save_under=True;
  at.backing_store=Always;
  XChangeWindowAttributes(disp,win,
			  CWOverrideRedirect|CWSaveUnder|CWBackingStore,&at);
  XSelectInput(disp,win,ExposureMask|ButtonReleaseMask);
  XMapWindow(disp,win);

  gc=XCreateGC(disp,win,0,0);
  cmap=DefaultColormap(disp,0);

  visual=DefaultVisual(disp,0);
  depth=DefaultDepth(disp,0);

  im=XCreateImage(disp,visual,depth,ZPixmap,0,0,0,0,32,0);
  im->byte_order=LSBFirst;
  im->bitmap_unit=32;
  im->bitmap_pad=32;
  im->bytes_per_line=x*sizeof(unsigned long);
  im->bits_per_pixel=8*sizeof(unsigned long);
  im->width=x;
  im->height=y;
  im->data=(char *)data;

  int i,j;

  int r_bit,g_bit,b_bit;

  r_bit=bit_count(visual->red_mask);
  g_bit=bit_count(visual->green_mask);
  b_bit=bit_count(visual->blue_mask);


  for(i=0;i<y;i++) {
    for(j=0;j<x;j++) {
      data[i*x+j]=((ppm_trans[i][j].r>>(8-r_bit))<<(g_bit+b_bit)
		   |((ppm_trans[i][j].g>>(8-g_bit))<<b_bit)
		   |(ppm_trans[i][j].b>>(8-b_bit)));
    }
  }

  XPutImage(disp,win,gc,im,0,0,0,0,x,y);
  XFlush(disp);

  do {
    XNextEvent(disp,&ev);

    if(ev.type == Expose) {
      XPutImage(disp,win,gc,im,0,0,0,0,x,y);
      XFlush(disp);
    }

  } while(ev.type != ButtonRelease);

  XDestroyWindow(disp,win);
  XCloseDisplay(disp);
}

//出力
void output(pixel **output,int cols,int rows,gray maxval){
  FILE *outfile;
  char filename[256];
  int mode;
  printf("出力形式を選択してください\n");
  printf("1.画面を保存\n");
  printf("2.ディスプレイに出力\n");
  printf(">");
  scanf("%d",&mode);
  if(mode!=1&&mode!=2)
    {error();}
  switch(mode){
	case 1 :
	  scanf("%s",filename);
	  printf("ファイルに保存されました。\n");
	  outfile=fopen(filename,"w");
	  ppm_writeppm(outfile,output,cols,rows,maxval,0);
	  fclose(outfile);
	  break;
	case 2 :
	  printf("画像を表示します。\n");
	  color_view(output,cols,rows,maxval);
	  break;
	default :exit(1);	
  }
}

//変換方法の選択
void menu(pixel **input, int cols, int rows, gray maxval, int mode_1)
{
  int mode_2;
  printf("次の4種類の変換から実行したい変換処理を数字で選択してください。\n");
  printf("1. 拡大・縮小\n");
  printf("2. 回転\n");
  printf("3. 平行移動\n");
  printf("4. 線断\n");
  printf("5. 終了\n");
  printf(">");
  scanf("%d",&mode_2);
  if(mode_2!=1&&mode_2!=2&&mode_2!=3&&mode_2!=4&&mode_2!=5)
    {error();}
  switch(mode_2){
  case 1:
    magnication(input,cols,rows,maxval,mode_1);
    break;
  case 2:
    rotation(input,cols,rows,maxval,mode_1);
    break;
  case 3:
    parallel(input,cols,rows,maxval,mode_1);
    break;
  case 4:
    shear(input,cols,rows,maxval,mode_1);
    break;
  case 5:
    output(input,cols,rows,maxval);
    break;
  }
}


int main(int argc,char *argv[]) {
  pixel **ppmdata;
  FILE *infile;
  int cols,rows,mode_1;
  gray maxval;

  infile=fopen(argv[1],"rb");
  if(infile==NULL)printf("画像ファイルが存在しないか、ファイル名が間違っています。\n");

  ppmdata=ppm_readppm(infile,&cols,&rows,&maxval);
   while(1){
  printf("次の2種類の内挿法から実行したい内挿法を数字で選択してください。\n");
  printf("1. 最近隣内挿法\n");
  printf("2. 共一次内挿法\n");
  printf(">");
  scanf("%d",&mode_1);

  if((mode_1!=1)||(mode_1!=2))
    {menu(ppmdata,cols,rows,maxval,mode_1);
      break;}
  else
    {error();}
  break;}
   //menu(ppmdata,cols,rows,maxval,mode_1);
  //magnication(ppmdata,cols,rows,maxval,1);
  //rotation(ppmdata,cols,rows,maxval,1);
  //parallel(ppmdata,cols,rows,maxval,1);
  //output(ppmdata,cols,rows,maxval);
  //color_view(ppmdata,cols,rows,maxval);

}
