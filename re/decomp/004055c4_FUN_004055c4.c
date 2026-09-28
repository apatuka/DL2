// FUN_004055c4 @ 004055c4 size=51 sig=undefined FUN_004055c4() cc=unknown
// callers: FUN_0040cda0,FUN_004055f8
// callees: FUN_0040552c

int FUN_004055c4(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  
  iVar3 = 0;
  puVar2 = &DAT_00521bb4;
  do {
    iVar1 = FUN_0040552c(*puVar2,param_1,param_2);
    iVar3 = iVar3 + iVar1;
    puVar2 = (undefined4 *)puVar2[1];
  } while (puVar2 != &DAT_00521bb4);
  return iVar3;
}

