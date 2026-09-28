// FUN_0046a39c @ 0046a39c size=490 sig=undefined FUN_0046a39c() cc=unknown
// callers: FUN_0046a844
// callees: 

void FUN_0046a39c(void)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  short *psVar6;
  int local_28;
  int local_24;
  short local_20;
  int local_18;
  int local_14;
  
  for (local_28 = 0; local_28 <= DAT_004d5b18; local_28 = local_28 + 1) {
    iVar1 = local_28 * 0xadc;
    if (((&DAT_005a43f1)[iVar1] != '\0') && ((&DAT_005a4444)[iVar1] != -1)) {
      iVar5 = ((char *)(&DAT_005a4450)[local_28 * 0x2b7 + (int)(char)(&DAT_005a4444)[iVar1]])[1] *
              0x20;
      iVar1 = *(char *)(&DAT_005a4450)[local_28 * 0x2b7 + (int)(char)(&DAT_005a4444)[iVar1]] * 0x20;
      local_24 = (int)*(short *)((iVar5 * DAT_0058f140 + iVar1) * 2 + DAT_0058f138 + 0x20 +
                                DAT_0058f140 * 0x20);
      if (local_24 < 2) {
        local_24 = 2;
      }
      for (iVar4 = iVar5 + -10; iVar4 < iVar5 + 0x2a; iVar4 = iVar4 + 1) {
        for (iVar2 = iVar1 + -10; iVar2 < iVar1 + 0x2a; iVar2 = iVar2 + 1) {
          if ((((-1 < iVar2) && (-1 < iVar4)) && (iVar2 < DAT_0058f140)) && (iVar4 < DAT_0058f13c))
          {
            psVar6 = (short *)((iVar4 * DAT_0058f140 + iVar2) * 2 + DAT_0058f138);
            if (((iVar2 < iVar1) || (iVar1 + 0x20 < iVar2)) ||
               ((iVar4 < iVar5 || (iVar5 + 0x20 < iVar4)))) {
              if (0 < *psVar6) {
                local_18 = 0;
                local_14 = 0;
                if (iVar2 < iVar1) {
                  local_18 = (iVar1 - iVar2) * 10;
                }
                if (iVar1 + 0x20 < iVar2) {
                  local_18 = (iVar2 - (iVar1 + 0x20)) * 10;
                }
                if (iVar4 < iVar5) {
                  local_14 = (iVar5 - iVar4) * 10;
                }
                if (iVar5 + 0x20 < iVar4) {
                  local_14 = (iVar4 - (iVar5 + 0x20)) * 10;
                }
                if (local_14 < local_18) {
                  piVar3 = &local_18;
                }
                else {
                  piVar3 = &local_14;
                }
                local_20 = (short)(((100 - *piVar3) * (local_24 - *psVar6)) / 100);
                *psVar6 = *psVar6 + local_20;
              }
            }
            else if (0 < *psVar6) {
              *psVar6 = (short)local_24;
            }
          }
        }
      }
    }
  }
  return;
}

