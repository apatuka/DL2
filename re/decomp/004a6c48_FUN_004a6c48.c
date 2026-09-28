// FUN_004a6c48 @ 004a6c48 size=63 sig=undefined FUN_004a6c48() cc=unknown
// callers: FUN_004ae974
// callees: FUN_004a6c30

undefined2 * FUN_004a6c48(undefined2 *param_1,undefined2 *param_2)

{
  uint uVar1;
  uint uVar2;
  undefined2 *puVar3;
  
  uVar1 = FUN_004a6c30(param_2);
  uVar2 = 0;
  puVar3 = param_1;
  if (uVar1 != 0) {
    do {
      *puVar3 = *param_2;
      uVar2 = uVar2 + 1;
      puVar3 = puVar3 + 1;
      param_2 = param_2 + 1;
    } while (uVar2 < uVar1);
  }
  param_1[uVar1] = 0;
  return param_1;
}

