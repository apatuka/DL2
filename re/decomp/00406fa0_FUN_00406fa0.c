// FUN_00406fa0 @ 00406fa0 size=141 sig=undefined FUN_00406fa0() cc=unknown
// callers: FUN_00408a88
// callees: FUN_00406dd8

uint FUN_00406fa0(int param_1)

{
  uint uVar1;
  int iVar2;
  char *pcVar3;
  int *piVar4;
  uint local_8;
  
  if (DAT_004d5af4 == 0) {
    local_8 = 0;
  }
  else {
    iVar2 = 0;
    local_8 = 0;
    pcVar3 = &DAT_0059f161;
    piVar4 = (int *)(&DAT_005220a4 + param_1 * 0x1c);
    do {
      if ((((*pcVar3 != '\0') && (iVar2 != param_1)) && (-1 < *piVar4)) &&
         ((1 << ((byte)iVar2 & 0x1f) & *(uint *)(&DAT_0052222c + param_1 * 4)) == 0)) {
        uVar1 = FUN_00406dd8(param_1,iVar2);
        local_8 = local_8 | uVar1;
      }
      iVar2 = iVar2 + 1;
      piVar4 = piVar4 + 1;
      pcVar3 = pcVar3 + 0x2d8;
    } while (iVar2 < 7);
  }
  return local_8;
}

