// FUN_00407248 @ 00407248 size=71 sig=undefined FUN_00407248() cc=unknown
// callers: NetBreakPact
// callees: FUN_0040526c

void FUN_00407248(undefined4 param_1,undefined4 param_2,uint param_3,int param_4)

{
  int iVar1;
  
  iVar1 = 0;
  if ((param_3 & 2) != 0) {
    iVar1 = -0x14;
  }
  if ((param_3 & 8) != 0) {
    iVar1 = iVar1 + -8;
  }
  if ((param_3 & 4) != 0) {
    iVar1 = iVar1 + -8;
  }
  if ((param_3 & 0x10) != 0) {
    iVar1 = iVar1 + -0x14;
  }
  if (param_4 != 0) {
    iVar1 = iVar1 * 2;
  }
  FUN_0040526c(param_1,param_2,iVar1);
  return;
}

