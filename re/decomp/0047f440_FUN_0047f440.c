// FUN_0047f440 @ 0047f440 size=170 sig=undefined FUN_0047f440() cc=unknown
// callers: FUN_0047f4ec,FUN_00451de4,FUN_00480d78
// callees: FUN_0044de9c

char FUN_0047f440(int param_1)

{
  char cVar1;
  int local_38 [13];
  
  FUN_0044de9c(&DAT_0059f160 + *(char *)(DAT_00657de0 + 0x20) * 0x2d8,(int)*(char *)(param_1 + 4),
               (int)*(char *)(DAT_00657de0 + 0x21),local_38);
  local_38[0] = ((local_38[0] - *(short *)(param_1 + 0x14)) * 100) / local_38[0];
  if ((*(byte *)(param_1 + 2) & 2) == 0) {
    cVar1 = ((&DAT_004f9dc5)[*(char *)(param_1 + 4) * 0x32] == '\x02') + 'o';
  }
  else {
    if (local_38[0] < 0x1e) {
      cVar1 = 'i';
    }
    else if (local_38[0] < 0x3c) {
      cVar1 = 'j';
    }
    else {
      cVar1 = 'k';
    }
    if ((&DAT_004f9dc5)[*(char *)(param_1 + 4) * 0x32] == '\x02') {
      cVar1 = cVar1 + '\x03';
    }
  }
  return cVar1;
}

