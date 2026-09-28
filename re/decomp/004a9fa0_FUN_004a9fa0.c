// FUN_004a9fa0 @ 004a9fa0 size=166 sig=undefined FUN_004a9fa0() cc=unknown
// callers: fopen
// callees: fclose,FUN_004a9ec4,FUN_004acfa4,FUN_004ab3c8

int FUN_004a9fa0(int param_1,undefined4 param_2,undefined4 param_3,uint param_4)

{
  char cVar1;
  short sVar2;
  int iVar3;
  undefined4 local_c;
  uint local_8;
  
  sVar2 = FUN_004a9ec4(param_3,&local_8,&local_c);
  *(short *)(param_1 + 0x12) = sVar2;
  if (sVar2 == 0) {
LAB_004a9feb:
    *(undefined1 *)(param_1 + 0x16) = 0xff;
    *(undefined2 *)(param_1 + 0x12) = 0;
    param_1 = 0;
  }
  else {
    if (*(char *)(param_1 + 0x16) < '\0') {
      cVar1 = FUN_004acfa4(param_2,local_8 | param_4,local_c);
      *(char *)(param_1 + 0x16) = cVar1;
      if (cVar1 < '\0') goto LAB_004a9feb;
    }
    if ((*(byte *)((int)&DAT_00520198 + *(char *)(param_1 + 0x16) * 4 + 1) & 0x20) != 0) {
      *(ushort *)(param_1 + 0x12) = *(ushort *)(param_1 + 0x12) | 0x200;
    }
    iVar3 = FUN_004ab3c8(param_1,0,(*(byte *)(param_1 + 0x13) & 2) != 0,0x200);
    if (iVar3 == 0) {
      *(undefined2 *)(param_1 + 0x10) = 0;
    }
    else {
      fclose(param_1);
      param_1 = 0;
    }
  }
  return param_1;
}

