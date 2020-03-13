#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
	FILE *fp;
	char set_value[4];

	/*********** set direction **************/
	if((fp = fopen("/sys/class/gpio/gpio67/direction", "w+")) < 0)
	{
		perror("led.c");
		exit(-1);
	}
	strcpy(set_value, "out");
	fwrite(&set_value, sizeof(char), 4, fp);
	fclose(fp);
	printf("direction finished\n");

	/*********** blink led **************/
	if((fp = fopen("/sys/class/gpio/gpio67/value", "w+")) < 0)
	{
		perror("led.c");
		exit(-1);
	}

	for(int i = 0; i<3; i++)
	{
		strcpy(set_value, "1");
		fwrite(&set_value, sizeof(char), 2, fp);
		sleep(1);

		strcpy(set_value, "0");
		fwrite(&set_value, sizeof(char), 2, fp);
		sleep(1);
	}
	fclose(fp);
	printf("blink finished\n");

	return 0;
}
