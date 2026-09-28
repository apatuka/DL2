// FUN_00436000 @ 00436000 size=100 sig=undefined FUN_00436000() cc=unknown
// callers: FUN_00476c80,FUN_00476cc0
// callees: FUN_00430b94,FUN_00449dec,FUN_00430b1c,FUN_0047d3d8

void FUN_00436000(char *param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  
  if (param_3 < 0) {
    iVar1 = FUN_00430b1c(param_2);
  }
  else {
    iVar1 = FUN_00430b94(param_2);
  }
  *(int *)(&DAT_005a440a + param_2 * 4 + param_4 * 0xadc) =
       *(int *)(&DAT_005a440a + param_2 * 4 + param_4 * 0xadc) + param_3;
  *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) - iVar1 * param_3;
  FUN_0047d3d8((int)*param_1,(int)*(short *)(param_1 + 6),1,iVar1 * param_3);
  FUN_00449dec();
  return;
}

