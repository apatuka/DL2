// FUN_004838fc @ 004838fc size=80 sig=undefined FUN_004838fc() cc=unknown
// callers: FUN_0043cc5c,FUN_004839e4
// callees: FUN_004b0b44,FUN_004838d4

undefined4 FUN_004838fc(int *param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int iVar4;
  
  iVar1 = FUN_004838d4(*param_1,param_2);
  if (iVar1 == 0) {
    puVar3 = (undefined4 *)FUN_004b0b44(8);
    *puVar3 = param_2;
    puVar3[1] = 0;
    iVar1 = *param_1;
    if (*param_1 == 0) {
      *param_1 = (int)puVar3;
    }
    else {
      do {
        iVar4 = iVar1;
        iVar1 = *(int *)(iVar4 + 4);
      } while (iVar1 != 0);
      *(undefined4 **)(iVar4 + 4) = puVar3;
    }
    uVar2 = 1;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

