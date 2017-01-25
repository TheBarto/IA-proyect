#include "Datos.h"
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc,char* argv[]) {

	int fd = open("README.md",O_RDONLY,S_IRUSR);
	char* buffer = (char *)malloc(512*sizeof(char));
	memset(buffer, 0, 512);


	rline(&fd, buffer,NULL);
	printf("La primera linea --> %s\n",buffer);
	rline(&fd, buffer,NULL);
	printf("La segunda linea --> %s\n",buffer);

	free(buffer);
}