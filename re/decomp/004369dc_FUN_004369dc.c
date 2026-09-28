// FUN_004369dc @ 004369dc size=103 sig=undefined FUN_004369dc() cc=unknown
// callers: FUN_00436a44
// callees: FUN_0049eb44,FUN_0049b416,FUN_004989cf

void FUN_004369dc(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4,
                 undefined4 param_5)

{
  int iVar1;
  
  iVar1 = FUN_0049b416(3);
  if (iVar1 != 0) {
    *(undefined4 *)(iVar1 + 4) = param_5;
    *(undefined4 *)(iVar1 + 8) = param_5;
    *(undefined4 *)(iVar1 + 0xc) = 0x32;
  }
  if ((param_4 != 0) && (iVar1 != 0)) {
    FUN_0049eb44(param_1,param_2,1,0x13,2,iVar1);
  }
  FUN_0049eb44(param_1,param_2,1,0xf,0,param_3);
  if (iVar1 != 0) {
    FUN_004989cf(iVar1);
  }
  return;
}

