#include <stdio.h>
#include <sys/socket.h>
#include <errno.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <unistd.h>

int main(int argc , char **argv)
{
	struct hostent *host;
	int err, i , sock ,start , end;
	char hostname[100];
	struct sockaddr_in sa;
	
	//Get the hostname to scan
	printf("Hostname OR IP: ");
	gets(hostname);
	//Get start port number
	printf("\nStart port number: ");
	scanf("%d" , &start);
	
	//Get end port number
	printf("End Port number: ");
	scanf("%d" , &end);

	//sa Structure
	strncpy((char*)&sa , "" , sizeof sa);
	sa.sin_family = AF_INET;
	
	//Check if is it a IP
	if(isdigit(hostname[0]))
	{
		sa.sin_addr.s_addr = inet_addr(hostname);
	}
	//Resolve 
	else if( (host = gethostbyname(hostname)) != 0)
	{
		strncpy((char*)&sa.sin_addr , (char*)host->h_addr , sizeof sa.sin_addr);
	}
	else
	{
		herror(hostname);
		exit(2);
	}
	
	//Start the port scan loop
	printf("Starting Port Scan...: \n");
	for( i = start ; i <= end ; i++) 
	{
		//Fill in the port number
		sa.sin_port = htons(i);
		//Create a socket of type internet
		sock = socket(AF_INET , SOCK_STREAM , 0);
		
		//Check whether socket created fine or not
		if(sock < 0) 
		{
			perror("\nSocket");
			exit(1);
		}
		//Connect using that socket and sockaddr structure
		err = connect(sock , (struct sockaddr*)&sa , sizeof sa);
		
		//not connected
		if( err < 0 )
		{
			//printf("%s %-5d %s\r" , hostname , i, strerror(errno));
			fflush(stdout);
		}
		//connected
		else
		{
			printf("%-5d open\n",  i);
		}
		close(sock);
	}
	
	printf("\r");
	fflush(stdout);
	return(0);
}
