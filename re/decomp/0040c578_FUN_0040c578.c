// FUN_0040c578 @ 0040c578 size=82 sig=undefined FUN_0040c578() cc=unknown
// callers: FUN_0040ef18
// callees: FUN_00401440

int FUN_0040c578(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int local_8;
  
  local_8 = -1000000;
  iVar4 = 0;
  piVar3 = &DAT_00521bb4;
  do {
    iVar1 = *piVar3;
    iVar2 = FUN_00401440(param_1,iVar1,0);
    if ((iVar2 != 0) && (iVar2 = *(int *)(iVar1 + 0xa0a) - *(int *)(iVar1 + 0xa60), local_8 < iVar2)
       ) {
      iVar4 = iVar1;
      local_8 = iVar2;
    }
    piVar3 = (int *)piVar3[1];
  } while (piVar3 != &DAT_00521bb4);
  return iVar4;
}

