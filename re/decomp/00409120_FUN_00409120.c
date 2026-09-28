// FUN_00409120 @ 00409120 size=89 sig=undefined FUN_00409120() cc=unknown
// callers: FUN_004059bc
// callees: FUN_004067d0,FUN_00408fdc

void FUN_00409120(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_2 + 0x1c);
  if (iVar2 == 4) {
    FUN_00408fdc(param_1,param_2);
  }
  uVar1 = *(undefined4 *)(&DAT_004b6444 + iVar2 * 4);
  iVar2 = FUN_004067d0(param_1,0,uVar1,1,1,0);
  if (iVar2 == 0) {
    iVar2 = FUN_004067d0(param_1,0,uVar1,1,1,10000);
  }
  if (iVar2 == 0) {
    *(undefined4 *)(param_2 + 0xc) = 1;
  }
  return;
}

