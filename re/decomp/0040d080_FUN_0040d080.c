// FUN_0040d080 @ 0040d080 size=285 sig=undefined FUN_0040d080() cc=unknown
// callers: FUN_004059bc
// callees: FUN_0040cdfc,FUN_0040552c,FUN_0046b0e4,FUN_004067d0,FUN_0044d1a4,FUN_00407d60

void FUN_0040d080(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined *puVar4;
  
  iVar1 = *(int *)(param_2 + 0x1c);
  if (iVar1 == -1) {
    *(undefined4 *)(param_2 + 0x10) = 1;
  }
  else {
    puVar4 = &DAT_005a43d0 + iVar1 * 0xadc;
    if (((puVar4 == (undefined *)0x0) || ((&DAT_005a4400)[iVar1 * 0x56e] == 0)) ||
       (param_1 != (char)(&DAT_005a43f0)[iVar1 * 0xadc])) {
      *(undefined4 *)(param_2 + 0x10) = 1;
    }
    else {
      iVar2 = FUN_0040552c(puVar4,0x11,0);
      iVar3 = FUN_0046b0e4(puVar4);
      if ((short)(&DAT_005a4400)[iVar1 * 0x56e] + iVar2 < iVar3) {
        iVar2 = FUN_004067d0(param_1,puVar4,0x11,1,1,0);
        if (iVar2 == 0) {
          iVar2 = FUN_004067d0(param_1,puVar4,0x11,1,1,10000);
        }
        if (iVar2 == 0) {
          if ((1 << ((byte)param_1 & 0x1f) & (int)DAT_004fbd6e) == 0) {
            *(undefined4 *)(param_2 + 0xc) = 1;
            FUN_0040cdfc(param_1,*(undefined4 *)(param_2 + 4),*(undefined4 *)(param_2 + 8),9,1);
          }
          else {
            iVar2 = FUN_0044d1a4(puVar4,0xd,0);
            if (iVar2 == -1) {
              *(undefined4 *)(param_2 + 0xc) = 1;
              FUN_00407d60(param_1,*(undefined4 *)(param_2 + 4),*(undefined4 *)(param_2 + 8),4,iVar1
                           ,0x11,1);
            }
            else {
              *(undefined4 *)(param_2 + 0xc) = 1;
            }
          }
        }
      }
      else {
        *(undefined4 *)(param_2 + 0x10) = 1;
      }
    }
  }
  return;
}

