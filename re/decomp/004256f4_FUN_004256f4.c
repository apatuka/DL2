// FUN_004256f4 @ 004256f4 size=249 sig=undefined FUN_004256f4() cc=unknown
// callers: FUN_0042623c,FUN_00425f58,FUN_00425bc4
// callees: FUN_00425ef8,FUN_004a19b4,FUN_00425f04

void FUN_004256f4(int param_1)

{
  char *pcVar1;
  
  if (*(int *)(param_1 + 0x1a) == 0) {
    DAT_00557558 = 0xffffffff;
  }
  else {
    pcVar1 = *(char **)(*(int *)(param_1 + 0x1a) + 8);
    if (pcVar1 == (char *)0x0) {
      DAT_00557558 = 0xffffffff;
    }
    else {
      FUN_004a19b4(DAT_004b7ce4,10,1,0xc,
                   (int)pcVar1[3] << 0x18 | (int)pcVar1[2] << 0x10 | (int)pcVar1[1] << 8 |
                   (int)*pcVar1);
      FUN_004a19b4(DAT_004b7ce4,10,1,0xd,*(undefined4 *)(*(int *)(param_1 + 0x1a) + 0xc));
      DAT_00557558 = *(undefined4 *)(*(int *)(param_1 + 0x1a) + 0x10);
    }
  }
  pcVar1 = *(char **)(param_1 + 8);
  if (pcVar1 == (char *)0x0) {
    DAT_0055755c = 0xffffffff;
  }
  else {
    FUN_004a19b4(DAT_004b7ce4,0xb,1,0xc,
                 (int)pcVar1[3] << 0x18 | (int)pcVar1[2] << 0x10 | (int)pcVar1[1] << 8 |
                 (int)*pcVar1);
    FUN_004a19b4(DAT_004b7ce4,0xb,1,0xd,*(undefined4 *)(param_1 + 0xc));
    DAT_0055755c = *(undefined4 *)(param_1 + 0x10);
  }
  FUN_00425f04();
  FUN_00425ef8();
  return;
}

