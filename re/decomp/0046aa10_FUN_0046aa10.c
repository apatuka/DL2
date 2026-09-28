// FUN_0046aa10 @ 0046aa10 size=261 sig=undefined FUN_0046aa10() cc=unknown
// callers: FUN_0046ab18
// callees: FUN_0044de9c,FUN_0044df30,FUN_00471cc0

void FUN_0046aa10(int param_1)

{
  short sVar1;
  short *psVar2;
  int *piVar3;
  int iVar4;
  undefined1 local_48 [8];
  short local_40 [22];
  short *local_14;
  int *local_10;
  int local_c;
  int local_8;
  
  local_c = 0;
  local_10 = (int *)(param_1 + 0x154);
  do {
    local_8 = *local_10;
    if (((local_8 != 0) && ((*(ushort *)(local_8 + 2) & 2) == 0)) &&
       ((*(ushort *)(local_8 + 2) & 4) != 0)) {
      if (*(char *)(local_8 + 4) == '%') {
        FUN_0044df30(local_8,local_48);
      }
      else {
        FUN_0044de9c(&DAT_0059f160 + *(char *)(param_1 + 0x20) * 0x2d8,(int)*(char *)(local_8 + 4),
                     (int)*(char *)(param_1 + 0x21),local_48);
      }
      iVar4 = 1;
      psVar2 = local_40;
      local_14 = (short *)(local_8 + 0x42);
      piVar3 = (int *)(param_1 + 0xa82);
      do {
        if (iVar4 == 4) {
          sVar1 = FUN_00471cc0(local_8 + 0x3e);
          *piVar3 = *piVar3 + (int)(short)(*psVar2 - sVar1);
        }
        else {
          *piVar3 = *piVar3 + (int)(short)(*psVar2 - *local_14);
        }
        iVar4 = iVar4 + 1;
        local_14 = local_14 + 2;
        piVar3 = piVar3 + 1;
        psVar2 = psVar2 + 2;
      } while (iVar4 < 0xb);
    }
    local_c = local_c + 1;
    local_10 = local_10 + 0xd;
  } while (local_c < 0x24);
  return;
}

