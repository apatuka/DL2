// FUN_0044d890 @ 0044d890 size=428 sig=undefined FUN_0044d890() cc=unknown
// callers: FUN_0044db50,FUN_0044dcf4
// callees: memset,GetBuildingTasks,FUN_0044de48

void FUN_0044d890(int param_1,int param_2,int param_3,undefined1 param_4,undefined2 param_5)

{
  char cVar1;
  
  *(char *)(param_2 + 4) = (char)param_3;
  *(undefined *)(param_2 + 5) = (&DAT_004f9dc3)[param_3 * 0x32];
  *(undefined2 *)(param_2 + 2) = 4;
  *(undefined1 *)(param_2 + 7) = param_4;
  *(undefined2 *)(param_2 + 8) = *(undefined2 *)(param_1 + 0x1a);
  *(undefined2 *)(param_2 + 10) = 0;
  if (DAT_004d5aa0 == '\0') {
    *(undefined2 *)(param_2 + 0x14) = param_5;
  }
  else {
    *(undefined2 *)(param_2 + 0x14) = 0;
    if ((&DAT_004f9dc3)[*(char *)(param_2 + 4) * 0x32] == '\v') {
      *(uint *)(param_1 + 0x1c) = *(uint *)(param_1 + 0x1c) | 0x10;
    }
  }
  if ((param_3 == 0x25) && (*(char *)(param_1 + 0x20) != -1)) {
    cVar1 = FUN_0044de48((int)*(char *)(param_1 + 0x20));
    *(short *)(param_2 + 0xc) = (short)(char)(cVar1 + -1);
  }
  else {
    *(undefined2 *)(param_2 + 0xc) = 0;
  }
  *(undefined2 *)(param_2 + 0x10) = 0;
  *(undefined2 *)(param_2 + 0x12) = 0;
  *(undefined2 *)(param_2 + 0x16) = 0;
  memset(param_2 + 0x18,0,0x14);
  memset(param_2 + 0x2c,0,5);
  memset(param_2 + 0x31,0,4);
  memset(param_2 + 0x36,0,8);
  memset(param_2 + 0x3e,0,0x2c);
  memset(param_2 + 0x6a,0,0xb0);
  if (*(char *)(param_1 + 0x20) != -1) {
    GetBuildingTasks(&DAT_0059f160 + *(char *)(param_1 + 0x20) * 0x2d8,param_2);
  }
  if (((((param_3 == 1) || (param_3 == 2)) || (param_3 == 3)) ||
      ((param_3 == 0x27 || (param_3 == 0x25)))) || (param_3 == 0x17)) {
    if ((DAT_004d5aa0 == '\0') || (*(char *)(param_1 + 0x20) != -1)) {
      *(undefined1 *)(param_2 + 6) = (&DAT_0059f162)[*(char *)(param_1 + 0x20) * 0x2d8];
    }
    else {
      *(undefined1 *)(param_2 + 6) = (&DAT_0059f162)[DAT_0058f1f4 * 0x2d8];
    }
  }
  else {
    *(undefined1 *)(param_2 + 6) = 0;
  }
  return;
}

