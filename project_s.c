//kadai2 38 kaito yuuki
#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<netdb.h>
#include<signal.h>

void InterruptSignalHandler(int ssock)
{
  printf("\nInterrupt Received. Exiting program.\n");
  close(ssock);
  exit(1);
}

int main()
{
 int ssock = 0;
 int b;
 struct sigaction handler;
 struct sockaddr_in saddr;
 int flag = 1;

 memset(&saddr,0,sizeof(saddr));
 saddr.sin_family =  AF_INET;
 saddr.sin_addr.s_addr = htonl(INADDR_ANY);
 saddr.sin_port = htons(10085);

 ssock = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
 setsockopt(ssock, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag));
 handler.sa_handler = InterruptSignalHandler;
 handler.sa_flags = 0;
 if(sigaction(SIGINT,&handler,0)<0)
   {
     printf("signal error\n");
     close(ssock);
     exit(1);
   }
 b=bind(ssock,(struct sockaddr*)&saddr, sizeof(saddr));

 if(b==-1){
   printf("bind error\n");
   close(ssock);
   exit(0);}

 listen(ssock,10);

 while(1){
  int csock;
  struct sockaddr_in caddr;
  int caddr_len = sizeof(caddr);
  int read_size;
  char moji[140];
  char buf[16];
  char buf2[140];
  int i = 0;

    csock = accept(ssock, (struct sockaddr*)&caddr,&caddr_len);
    if(csock==-1){
      printf("accept error\n");
      close(ssock);
      close(csock);
      exit(0);}

  if((strncmp(buf2,"WRITE / HTTP/1.0",140))==0){

    send(csock,"A",strlen("A"),0);
  }
  while(1)
    {
      for(i=0;i<139;i++)
	{
	  buf2[i]='\0';
	}
      
      read_size = recv(csock,buf2,140,0);
      buf2[read_size] = 0;
      printf("[recv text]\n");
      puts(buf2);
     
    }
  if((strncmp(buf2,"GET / HTTP/1.1",14))==0)
    
    {
      send(csock,moji ,strlen(moji), 0);
    }
  else
    {
      send(csock,"no text\n" ,strlen("no text\n"), 0);
    }
  close(csock);
 }
 
 close(ssock);
 exit(EXIT_SUCCESS);
}
