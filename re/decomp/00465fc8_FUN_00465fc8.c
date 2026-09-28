// FUN_00465fc8 @ 00465fc8 size=75 sig=undefined FUN_00465fc8() cc=unknown
// callers: FUN_00466218,FUN_00466128
// callees: FUN_00465f84

undefined4 FUN_00465fc8(int param_1)

{
  char *pcVar1;
  undefined1 uVar2;
  
  if ((*(byte *)(param_1 + 0x1d) & 1) == 0) {
    pcVar1 = *(char **)(param_1 + 0x80 + *(char *)(param_1 + 0x75) * 4);
    uVar2 = FUN_00465f84(param_1,*pcVar1 + 1,pcVar1[1] + 2);
    *(undefined1 *)(param_1 + 0x74) = uVar2;
    if (*(char *)(param_1 + 0x74) == -1) {
      return 0;
    }
  }
  return 1;
}

