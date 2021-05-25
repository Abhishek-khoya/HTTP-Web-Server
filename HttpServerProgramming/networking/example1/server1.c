#include<windows.h>
#include<stdio.h>
#include<string.h>
int main()
{
    char response[5000];
    char request[5000];
    WORD ver;
    WSADATA wsaData;
    int serverSocketDescriptor;
    int clientSocketDescriptor;
    struct sockaddr_in serverSocketInformation;
    struct sockaddr_in clientSocketInformation;
    int successCode;
    int len;
    ver=MAKEWORD(1,1);
    WSAStartup(ver,&wsaData); //socket libary initialized
    serverSocketDescriptor=socket(AF_INET,SOCK_STREAM,0);
    if(serverSocketDescriptor<0)
    {
        printf("unable to create socket \n");
        return 0;
    }
    serverSocketInformation.sin_family=AF_INET;
    serverSocketInformation.sin_port=htons(5050);
    serverSocketInformation.sin_addr.s_addr=htonl(INADDR_ANY);
    successCode=bind(serverSocketDescriptor,(struct sockaddr *)&serverSocketInformation,sizeof(serverSocketInformation));
    if(successCode<0)
    {
        printf("Unable to bind socket to port 5050\n");
        WSACleanup();
        return 0;
    }
    listen(serverSocketDescriptor,10);
    printf("AKServer is ready to accept request on port 5050 \n");
    len=sizeof(clientSocketInformation);
    clientSocketDescriptor=accept(serverSocketDescriptor,(struct sockaddr *)&clientSocketInformation,&len);
    if(clientSocketDescriptor<0)
    {
        printf("unable to accept client connection \n");
        closesocket(serverSocketDescriptor);
        WSACleanup();
        return 0;
    }
    successCode=recv(clientSocketDescriptor,request,sizeof(request),0);
    if(successCode>0)
    {
        printf("request arrived\n");
        printf("%s\n",request);
    }
    strcpy(response,"Welcome to AKServer");
    successCode=send(clientSocketDescriptor,response,strlen(response)+1,0);
    if(successCode>0)
    {
        printf("Response sent\n");
    }
    else
    {
        printf("unable to send response\n");
    }
    closesocket(clientSocketDescriptor);
    closesocket(serverSocketDescriptor);
    WSACleanup();
    return 0;
}