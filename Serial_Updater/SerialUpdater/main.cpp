#include "serial.h"

#pragma warning (disable:4996)

int main(int argc, char *argv[])
{
	char com_port[50];
	int baud_rate, cmd;
	char cmds[7][50] = { MOVE,STEP,STEP_R,STEP_S,PWM_FR,PWM_FA,STEPIN };

	if (argc != 5)
	{
		printf("Error! Not enough params\nUsage:\tCOM_PORT BAUD_RATE CMD PARAM");
		return 0;
	}

	sprintf(com_port,"\\\\.\\%s",argv[1]);
	CSyncSerialComm serial(com_port);
	serial.Open();
	baud_rate = atoi(argv[2]);
	serial.ConfigPort(baud_rate, 5);
	serial.Flush();
	cmd = atoi(argv[3]);
	SEND_CMD(cmds[cmd], argv[4]);
	serial.Close();

	return 0;
}
