// FUN_00465e7c @ 00465e7c size=66 sig=undefined FUN_00465e7c() cc=unknown
// callers: FUN_00466218,FUN_00466128
// callees: FUN_0046237c

void FUN_00465e7c(int param_1)

{
  int iVar1;
  undefined1 uVar2;
  int *piVar3;
  int iVar4;
  
  piVar3 = (int *)(param_1 + 0x80);
  for (iVar4 = 0; iVar4 < *(char *)(param_1 + 0x7e); iVar4 = iVar4 + 1) {
    uVar2 = FUN_0046237c((int)*(char *)*piVar3,(int)*(char *)(*piVar3 + 1),
                         (int)*(short *)(param_1 + 0x1a));
    iVar1 = *piVar3;
    piVar3 = piVar3 + 1;
    *(undefined1 *)(iVar1 + 4) = uVar2;
  }
  return;
}

