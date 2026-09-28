// FUN_004969f8 @ 004969f8 size=46 sig=undefined FUN_004969f8() cc=unknown
// callers: 
// callees: FUN_0049698a

int FUN_004969f8(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined1 local_8 [4];
  
  iVar1 = 0;
  do {
    iVar3 = iVar1;
    iVar2 = FUN_0049698a(param_1,param_2,iVar3,local_8);
    iVar1 = iVar3 + 1;
  } while (iVar2 != 0);
  return iVar3;
}

