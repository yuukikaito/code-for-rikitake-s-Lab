//4I 38 結城海斗
#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<netdb.h>

unsigned long ResolveName(char name[])
{
  struct hostent *host;

  //URLチェック
  if ((host = gethostbyname(name)) == NULL)
    {
      printf("\n");
      fprintf(stderr, "gethostbyname() failed\n");
      printf("\n");
      exit(1);
    }
  return *((unsigned long *)host ->h_addr_list[0]);
}

//URL解析
void check(char *IP,char *host,char *path)
{
  int i=-1,g=0,y,v;
  while(i++,i<100)
    {
      if(IP[i]=='/')
	{
	  g+=1;
	  if(g>=2) break;
	}
    }
  y=i+1;
  while(i++,i<100-1)
    {
      if(IP[i]=='/')
	break;
      else 
	host[i-y]=IP[i];
    }
  host[i-y]='\0';
  v=i+1;
  while(i++,i<100-1)
    {
      if(IP[i]=='\0')
	break;
      else
	path[i-v]=IP[i];
    }
  path[i-v]='\0';
}


int main()
{
  char moji[140];
  int  sock,b;
  char addres;
  char IP[100],host[100],path[100];
  int  data;
  char buf2[140];

  printf("[IPの指定]\n");
  scanf("%s",IP);
  check(IP,host,path);
  
  sock = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
  
  struct sockaddr_in addr;
  
  memset(&addr,0,sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = ResolveName(host);
  //addr.sin_addr.s_addr = inet_addr("10.64.130.125");
  addr.sin_port = htons(10085);
  
  b=connect(sock,(struct sockaddr*)&addr,sizeof(addr));
  
  //コネクトチェック
  if(b==-1){
    printf("\n");
    printf("not connect");
    printf("\n");
    exit(1);
  }
  
  
  sprintf(IP,"GET /%s HTTP/1.1\r\n\r\n",path);
  
  while(1)
    {
      printf("[いまどうしてる？]\n");	
      scanf("%s",moji);
      send(sock,moji,strlen(moji),0);
    }		
  
  while(recv(sock,buf2,140,0)>0)
    {
      fwrite(buf2,sizeof(char),strlen(buf2),stdout);
    }
  
  
    
	close(sock);
}
    
    
