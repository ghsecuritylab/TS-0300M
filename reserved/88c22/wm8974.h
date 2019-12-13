#ifndef __WM8974_H_
#define __WM8974_H_


void Wm8974RegisterInit(void);
void Wm8974SetDacDbVolume(s8 n_db);
void Wm8974SetDacHexVolume(u8 data);
void Wm8974SetAdcDbVolume(s8 n_db);
void Wm8974SetSpkVolCtrl(u8 flag);
void Wm8974SetMonoVolCtrl(u8 flag);
void Wm8974SetInpgaVolume(s8 n_db);
void Wm8974SetFilter(u8 enable);
void Wm8974SetEQValue(u8 band, u8 data);
void SetMicSen2WM8974(u8 sen);
void Wm8974SpecialParmInit(void);
void Wm8974ReadStatus(void);
#endif

