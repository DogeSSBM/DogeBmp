#include "Includes.h"
// dots per line
#define DPL_DEFAULT		384
// bits per line: 8 data bits plus 1 clock bit
#define BPL_DEFAULT		9
// dots per bit
#define DPB_DEFAULT		(DPL_DEFAULT/BPL_DEFAULT)

typedef struct Printer{
	// dots per line
	uint dpl;
	// bits per line: 8 data bits plus 1 clock bit
	uint bpl;
	// dots per bit
	uint dpb;
}Printer;


int main(int argc, char const *argv[])
{
	Printer printer;
	switch(argc){
	case 3:
		printer.dpl = DPL_DEFAULT;
		printer.bpl = BPL_DEFAULT;
		printer.dpb = DPB_DEFAULT;
		break;
	case 5:
		printer.dpl = strToInt(argv[3]);
		//printer.bpl = strToInt(argv[4]); To complex for now
		printer.bpl = BPL_DEFAULT;
		printer.dpb = printer.dpl/printer.bpl;
		break;
	default:
		printf("Usage\n");
		printf("\tDogeBmp <input_file> <output_file>\n");
		printf("\tDogeBmp <input_file> <output_file> [<dots per line><bits per line>]\n");
		exit(-1);
	}

	File *inputFile = fopen(argv[1], "r");
	if(!inputFile){
		perror("Could not open input file");
		exit(1);
	}

	//Open file and get file length
	fseek(inputFile, 0, SEEK_END);
	int len = ftell(inputFile);
	fseek(inputFile, 0, SEEK_SET);
	int bmpHeight = len * printer.dpb;

	//Copy input file into input buffer and close file
	char *inputBuffer = malloc(len);
	fread(inputBuffer, sizeof(char), len, inputFile);
	fclose(inputFile);

	//Create monochrome bitmap surface
	SDL_Surface *bitmap = SDL_CreateRGBSurface(SDL_SWSURFACE, 
			printer.dpl, bmpHeight, 8, 0, 0, 0, 0);
	SDL_SetSurfacePalette(bitmap, &BANDW);

	//Do the draw
	bool clockBit = false;
	SDL_Rect bitRect = {0, 0, printer.dpb, printer.dpb};
	for(int x = 0; x < len; x++)
	{
		if(clockBit) SDL_FillRect(bitmap, &bitRect, 0xFFFFFFFF);
		clockBit = !clockBit;
		bitRect.x += printer.dpb;
		for(int y = (printer.bpl - 2); y >= 0 ;y--)
		{
			if((inputBuffer[x] >> y) & 1) 
				SDL_FillRect(bitmap, &bitRect, 0xFFFFFFFF);
			bitRect.x += printer.dpb;
		}
		bitRect.y += printer.dpb;
		bitRect.x = 0;
	}
	SDL_SaveBMP(bitmap, argv[2]);

	free(inputBuffer);
	return 0;
}
