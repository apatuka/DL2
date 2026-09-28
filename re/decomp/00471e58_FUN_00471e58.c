// FUN_00471e58 @ 00471e58 size=258 sig=undefined FUN_00471e58() cc=unknown
// callers: FUN_004722e0,FUN_004383a4,FUN_00471f5c
// callees: FUN_00471cc0,FUN_00472ca0,FUN_00471cec

uint FUN_00471e58(byte *param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  
  uVar4 = 0;
  if (DAT_004d5aa0 == '\0') {
    iVar1 = FUN_00472ca0(param_2,param_3 + 4);
    if (((iVar1 == -1) || (*(int *)(param_1 + 0xc) < iVar1)) ||
       ((*(int *)(param_1 + 0xc) < *(int *)(param_3 + 4) + iVar1 &&
        (*(int *)(param_3 + 4) < *(int *)(param_1 + 0xc))))) {
      uVar4 = 0x2000;
    }
    if ((*(int *)(param_3 + 0x30) != 0) &&
       (((int)(short)(&DAT_004fbbac)[*(int *)(param_3 + 0x30) * 0x19] & 1 << (*param_1 & 0x1f)) == 0
       )) {
      uVar4 = uVar4 | 0x1000;
    }
    if (*(int *)(param_1 + 0xc) < iVar1 + *(int *)(param_3 + 4)) {
      uVar4 = uVar4 | 1;
    }
    if ((uVar4 & 0x2000) != 0) {
      iVar1 = 1;
      piVar3 = (int *)(param_3 + 8);
      do {
        if (0 < *piVar3) {
          if (iVar1 == 4) {
            iVar2 = FUN_00471cc0(DAT_00657de0 + 0x3a);
          }
          else {
            iVar2 = *(int *)(DAT_00657de0 + 0x3a + iVar1 * 4);
          }
          if ((iVar2 < *piVar3) &&
             (iVar2 = FUN_00471cec((int)*(char *)(DAT_00657de0 + 0x20),iVar1,*piVar3), iVar2 == 0))
          {
            uVar4 = uVar4 | 1 << ((byte)iVar1 & 0x1f);
          }
        }
        iVar1 = iVar1 + 1;
        piVar3 = piVar3 + 1;
      } while (iVar1 < 0xb);
    }
  }
  else {
    uVar4 = 0;
  }
  return uVar4;
}

