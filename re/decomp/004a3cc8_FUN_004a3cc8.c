// FUN_004a3cc8 @ 004a3cc8 size=94 sig=undefined FUN_004a3cc8() cc=unknown
// callers: 
// callees: FUN_004a3533,FUN_00490ab3,FUN_00498aab,FUN_004a1fc4,FUN_00490796,FUN_004a3bd0

bool FUN_004a3cc8(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_00490ab3(param_1,0x554e4d53,param_3,0,0);
  if (iVar1 != 0) {
    uVar2 = FUN_00498aab(iVar1,1);
    FUN_004a3533(param_2,0,uVar2);
    FUN_00498aab(iVar1,0);
    FUN_00490796(iVar1,0);
    FUN_004a1fc4(param_2);
    FUN_004a3bd0(param_2);
  }
  return iVar1 != 0;
}

