#include "main.h"

CONTENT prog;

int main()
{
	while (true)
	{
		// On / Off
		prog.Video_Mosaic = 1;
		if (prog.Video_Mosaic == 1)
			Mosaic_Video();
	}
}
