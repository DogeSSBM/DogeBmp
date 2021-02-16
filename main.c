#include "Includes.h"
// dots per line
#define DPL_DEFAULT		384
// bits per line: 8 data bits plus 1 clock bit
#define BPL_DEFAULT		9
// dots per bit
#define DPB_DEFAULT		(DPL/BPL)

struct{
	// dots per line
	uint dpl;
	// bits per line: 8 data bits plus 1 clock bit
	uint bpl;
	// dots per bit
	uint dpb;
}printer;


int main(int argc, char const *argv[])
{
	switch(argc){
	case 3:
		printer.dpl = DPL_DEFAULT;
		printer.bpl = BPL_DEFAULT;
		printer.dpb = DPB_DEFAULT;
		break;
	case 5:
		printer.dpl = strToInt(argv[3]);
		printer.bpl = strToInt(argv[4]);
		printer.dpb = printer.dpl/printer.bpl;
		break;
	default:
		printf("Usage\n");
		printf("\tDogeBmp <input_file> <output_file>\n");
		printf("\tDogeBmp <input_file> <output_file> [<dots per line><bits per line>]\n");
		exit(-1);
	}

	File * = fopen(argv[1], "r");
	if(!inputFile){
		perror("Could not open input file");
		exit(1);
	}

	//Open file and get file length
	fseek(inputFile, 0, SEEK_END);
	int len = ftell(inputFile);
	fseek(inputFile, 0, SEEK_SET);
	int bmpHeight = len * DPB;

	//Copy input file into input buffer and close file
	char *inputBuffer = malloc(len);
	fread(inputBuffer, sizeof(char), len, inputFile);
	fclose(inputFile);

	bool bitNine = false;
	for(int i = 0; i < len; i++)
	{

	}

	return 0;
}
