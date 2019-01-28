#include "client.h"
#include "server.h"
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(){
	int pid = fork();
	if( pid == 0 ){
		simple_server();
	}else{
		printf("input c: ");
		char option = ' ';
		scanf("%c", &option);
		if( option == 'c' ){
			simple_client();
		}
	}
	return 0;
}