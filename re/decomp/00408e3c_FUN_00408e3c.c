// FUN_00408e3c @ 00408e3c size=279 sig=undefined FUN_00408e3c() cc=unknown
// callers: FUN_004059bc
// callees: FUN_0046ac44,FUN_004067d0,FUN_00408bf4,FUN_004054d8,FUN_00407d60,FUN_0040cdfc

void FUN_00408e3c(undefined4 param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined1 local_84 [32];
  int aiStack_64 [11];
  int aiStack_38 [11];
  int local_c;
  int local_8;
  
  iVar2 = *(int *)(param_2 + 0x1c);
  local_8 = *(int *)(param_2 + 0x20);
  if (iVar2 == 4) {
    FUN_00408bf4(param_1,param_2);
  }
  else {
    FUN_0046ac44(local_84,param_1);
    if (aiStack_64[iVar2] + aiStack_38[iVar2] < local_8) {
      local_c = *(int *)(&DAT_004b6444 + iVar2 * 4);
      iVar1 = FUN_004067d0(param_1,0,local_c,1,1,0);
      if (iVar1 == 0) {
        iVar1 = FUN_004067d0(param_1,0,local_c,1,1,10000);
      }
      if (iVar1 == 0) {
        iVar2 = *(int *)(&DAT_004b64f4 + iVar2 * 4);
        if ((iVar2 == 0) ||
           ((1 << ((byte)param_1 & 0x1f) & (int)(short)(&DAT_004fbbac)[iVar2 * 0x19]) != 0)) {
          iVar2 = FUN_004054d8(local_c,0);
          if (iVar2 == 0) {
            *(undefined4 *)(param_2 + 0xc) = 1;
          }
          else {
            *(undefined4 *)(param_2 + 0xc) = 1;
            FUN_00407d60(param_1,*(undefined4 *)(param_2 + 4),*(undefined4 *)(param_2 + 8),
                         *(undefined4 *)(&DAT_004b649c + local_c * 4),0xffffffff,local_c,1);
          }
        }
        else {
          *(undefined4 *)(param_2 + 0xc) = 1;
          FUN_0040cdfc(param_1,*(undefined4 *)(param_2 + 4),*(undefined4 *)(param_2 + 8),iVar2,1);
        }
      }
    }
    else {
      *(undefined4 *)(param_2 + 0xc) = 1;
    }
  }
  return;
}

