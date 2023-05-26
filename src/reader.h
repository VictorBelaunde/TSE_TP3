#define FIFO_NAME "myfifo"
#define BUFFER_SIZE 300
#define CABECERA_SIGN "SIGN"
#define CABECERA_DATA "DATA"
char inputBuffer[BUFFER_SIZE];
char mensaje_original[BUFFER_SIZE];
int32_t bytesRead, returnCode, fd;

int parser_cadena(char cadena[], char delimitador[]);