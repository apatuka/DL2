// FUN_00417c00 @ 00417c00 size=321 sig=undefined FUN_00417c00() cc=unknown
// callers: CheckArmy
// callees: FUN_0049eb44

void FUN_00417c00(void)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  bool bVar5;
  undefined1 local_10;
  
  local_10 = 0xff;
  iVar1 = FUN_0049eb44(DAT_004b76b4,8,1,0xc,0,0);
  if (iVar1 == 0) {
    iVar1 = FUN_0049eb44(DAT_004b76b4,9,1,0xc,0,0);
    if (iVar1 == 0) {
      iVar1 = FUN_0049eb44(DAT_004b76b4,10,1,0xc,0,0);
      if (iVar1 == 0) {
        iVar1 = FUN_0049eb44(DAT_004b76b4,0xb,1,0xc,0,0);
        if (iVar1 == 0) {
          iVar1 = FUN_0049eb44(DAT_004b76b4,0xc,1,0xc,0,0);
          bVar5 = iVar1 != 0;
          if (bVar5) {
            local_10 = 100;
          }
        }
        else {
          local_10 = 0x4b;
          bVar5 = true;
        }
      }
      else {
        local_10 = 0x32;
        bVar5 = true;
      }
    }
    else {
      local_10 = 0x19;
      bVar5 = true;
    }
  }
  else {
    local_10 = 0;
    bVar5 = true;
  }
  if (bVar5) {
    DAT_0053b258 = local_10;
    if (DAT_004b76b8 == '\0') {
      *(undefined1 *)(DAT_004b76bc + 0x26) = local_10;
    }
    else {
      iVar1 = 0;
      piVar4 = &DAT_005332d8;
      do {
        iVar3 = 0;
        piVar2 = piVar4;
        do {
          if (*piVar2 == 1) {
            *(undefined1 *)(piVar2[1] + 0x26) = DAT_0053b258;
          }
          iVar3 = iVar3 + 1;
          piVar2 = piVar2 + 8;
        } while (iVar3 < 10);
        iVar1 = iVar1 + 1;
        piVar4 = (int *)((int)piVar4 + 0x146);
      } while (iVar1 < 100);
    }
  }
  return;
}

