// FUN_004957b5 @ 004957b5 size=92 sig=undefined FUN_004957b5() cc=unknown
// callers: FUN_0049585a
// callees: FUN_004975a1,FUN_004974aa,FUN_004ae26c

bool FUN_004957b5(int *param_1,undefined4 *param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 local_104 [256];
  
  iVar1 = FUN_004974aa(*param_1,&DAT_0051e088);
  *param_1 = iVar1;
  if (iVar1 == 0) {
    *param_2 = 0;
  }
  else {
    iVar2 = FUN_004975a1(*param_1,local_104,&DAT_0051e08a);
    *param_1 = iVar2;
    uVar3 = FUN_004ae26c(local_104);
    *param_2 = uVar3;
  }
  return iVar1 != 0;
}

