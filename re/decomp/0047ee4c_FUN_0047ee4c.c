// FUN_0047ee4c @ 0047ee4c size=77 sig=undefined FUN_0047ee4c() cc=unknown
// callers: FUN_0047eed8,FUN_0047ee9c
// callees: 

void FUN_0047ee4c(uint param_1,int param_2,int *param_3,int *param_4)

{
  int iVar1;
  
  iVar1 = (int)param_1 >> 1;
  if (iVar1 < 0) {
    iVar1 = iVar1 + (uint)((param_1 & 1) != 0);
  }
  *param_3 = (iVar1 + param_2 + 1000) / 0x32 + -0x14;
  *param_4 = ((param_2 + 1000) - iVar1) / 0x32 + -0x14;
  return;
}

