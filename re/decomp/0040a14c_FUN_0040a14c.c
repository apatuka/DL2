// FUN_0040a14c @ 0040a14c size=116 sig=undefined FUN_0040a14c() cc=unknown
// callers: FUN_00409914,FUN_0040a420,FUN_0040aaa4,FUN_00409b58,FUN_0040a098
// callees: FUN_0040cdfc

void FUN_0040a14c(int param_1,int param_2,int *param_3)

{
  int iVar1;
  
  iVar1 = *param_3;
  while( true ) {
    if (iVar1 == 0) {
      return;
    }
    if ((1 << ((byte)param_1 & 0x1f) & (int)(short)(&DAT_004fbbac)[iVar1 * 0x19]) == 0) break;
    param_3 = param_3 + 1;
    iVar1 = *param_3;
  }
  FUN_0040cdfc(param_1,param_2,(int)(char)(&DAT_0059f1bf)[param_2 * 0x5a + param_1 * 0x2d8],iVar1,0)
  ;
  return;
}

