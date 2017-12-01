#include "ui_sfx.h"

/*
	Default values
*/
pongUISFX::pongUISFX()
{
	
}


/*
	Play requested sound
*/
void pongUISFX::playSound(int sound_id)
{
	switch (sound_id)
	{
		case 0:
		{
			PlaySound(TEXT("Resources_Temp\\BEEP_005.wav"), NULL, SND_ASYNC);
		}
		case 1:
		{
			PlaySound(TEXT("Resources_Temp\\BEEP_009.wav"), NULL, SND_ASYNC);
		}
		case 2:
		{
			PlaySound(TEXT("Resources_Temp\\BEEP_011.wav"), NULL, SND_ASYNC);
		}
		case 3:
		{
			PlaySound(TEXT("Resources_Temp\\BEEP_016.wav"), NULL, SND_ASYNC);
		}
		case 4:
		{
			PlaySound(TEXT("Resources_Temp\\BEEP_018.wav"), NULL, SND_ASYNC);
		}
		case 5:
		{
			PlaySound(TEXT("Resources_Temp\\BEEP_021.wav"), NULL, SND_ASYNC | SND_NOSTOP);
		}
		case 6:
		{
			PlaySound(TEXT("Resources_Temp\\Interactive_Terminal_Startup_SHORTENED.wav"), NULL, SND_ASYNC);
		}
		case 7:
		{
			PlaySound(TEXT("Resources_Temp\\Interactive_Terminal_Telem_02.wav"), NULL, SND_ASYNC);
		}
		case 8:
		{
			PlaySound(TEXT("Resources_Temp\\Interactive_Terminal_Telem_04.wav"), NULL, SND_ASYNC);
		}
		case 9:
		{
			PlaySound(TEXT("Resources_Temp\\Interactive_Terminal_Telem_06.wav"), NULL, SND_ASYNC);
		}
		case 10:
		{
			PlaySound(TEXT("Resources_Temp\\Interactive_Terminal_Telem_07.wav"), NULL, SND_ASYNC);
		}
	}
}