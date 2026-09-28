// FUN_0043addc @ 0043addc size=154 sig=undefined FUN_0043addc() cc=unknown
// callers: 
// callees: FUN_0049eb44,FUN_004a43da

void FUN_0043addc(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  if (param_2 == 3) {
    if (DAT_004d5aa0 != '\0') {
      if ((&DAT_0059f161)[DAT_0058f1f4 * 0x2d8] == '\0') {
        FUN_0049eb44(DAT_004c48a0,0x22,1,0x42,0,0x1780);
      }
      else {
        FUN_0049eb44(DAT_004c48a0,0x22,1,0x42,0,(char)(&DAT_0059f162)[DAT_0058f1f4 * 0x2d8] + 0x1779
                    );
      }
    }
    FUN_004a43da(param_1,3,param_3,param_4);
  }
  else {
    FUN_004a43da(param_1,param_2,param_3,param_4);
  }
  return;
}

