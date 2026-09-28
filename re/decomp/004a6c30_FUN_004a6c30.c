// FUN_004a6c30 @ 004a6c30 size=24 sig=undefined FUN_004a6c30() cc=unknown
// callers: FUN_004a6c48,FUN_004adbec
// callees: 

int FUN_004a6c30(short *param_1)

{
  int iVar1;
  
  iVar1 = 0;
  for (; *param_1 != 0; param_1 = param_1 + 1) {
    iVar1 = iVar1 + 1;
  }
  return iVar1;
}

