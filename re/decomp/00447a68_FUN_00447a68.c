// FUN_00447a68 @ 00447a68 size=163 sig=undefined FUN_00447a68() cc=unknown
// callers: FUN_00447b54,FUN_00447b30,FUN_00447b0c,FUN_00447b9c,FUN_00447bc0,FUN_00447be4,FUN_00447c08,FUN_00447b78
// callees: memset

void FUN_00447a68(int param_1,int param_2)

{
  int *piVar1;
  int local_c;
  int local_8;
  
  memset(param_2,0,0x4c);
  *(int *)(param_2 + 4) = (int)*(char *)(param_1 + 6);
  *(undefined1 *)(param_2 + 0x1e) = *(undefined1 *)(param_1 + 8);
  *(undefined1 *)(param_2 + 8) = *(undefined1 *)(param_1 + 8);
  local_8 = (int)*(short *)(param_1 + 0x28);
  local_c = 1000;
  if (*(short *)(param_1 + 0x28) < 0x3e9) {
    piVar1 = &local_8;
  }
  else {
    piVar1 = &local_c;
  }
  *(short *)(param_2 + 10) = (short)*piVar1;
  *(undefined1 *)(param_2 + 9) = *(undefined1 *)(param_1 + 0x24);
  *(undefined4 *)(param_2 + 0x3c) = 0;
  if ((((&DAT_0059f169)[*(char *)(param_1 + 8) * 0x2d8] & 1) == 0) &&
     (((&DAT_0059f169)[*(char *)(param_1 + 8) * 0x2d8] & 2) == 0)) {
    *(undefined1 *)(param_2 + 0x1c) = 0;
  }
  else {
    *(undefined1 *)(param_2 + 0x1c) = 0xff;
  }
  return;
}

