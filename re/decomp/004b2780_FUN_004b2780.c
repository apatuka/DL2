// FUN_004b2780 @ 004b2780 size=156 sig=undefined FUN_004b2780() cc=unknown
// callers: FUN_004b26a8,FUN_004b17d4
// callees: FUN_004b366c,FUN_004b2500,FUN_004b17c0,FUN_004b1874

undefined4 FUN_004b2780(int param_1)

{
  code *pcVar1;
  int iVar2;
  undefined4 uVar3;
  undefined *puVar4;
  
  if ((param_1 == 2) || (param_1 == 0x15)) {
    puVar4 = &DAT_00521438;
  }
  else {
    iVar2 = FUN_004b366c();
    if ((iVar2 == 0) || (puVar4 = *(undefined **)(iVar2 + 0x28), puVar4 == (undefined *)0x0)) {
      return 1;
    }
  }
  iVar2 = FUN_004b2500(param_1);
  if (iVar2 == -1) {
    uVar3 = 1;
  }
  else {
    pcVar1 = *(code **)(puVar4 + iVar2 * 4);
    if (pcVar1 != (code *)0x1) {
      if (pcVar1 == (code *)0x0) {
        if ((1 < param_1 - 0x10U) && (param_1 != 0x14)) {
          if (param_1 == 0x16) {
            FUN_004b17c0();
          }
          else {
            FUN_004b1874(3);
          }
        }
      }
      else {
        *(undefined4 *)(puVar4 + iVar2 * 4) = 0;
        if ((&DAT_00521488)[iVar2] == '\0') {
          (*pcVar1)(param_1);
        }
        else {
          (*pcVar1)(param_1,(&DAT_00521488)[iVar2]);
        }
      }
    }
    uVar3 = 0;
  }
  return uVar3;
}

