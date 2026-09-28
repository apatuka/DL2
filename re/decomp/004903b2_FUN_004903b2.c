// FUN_004903b2 @ 004903b2 size=36 sig=undefined FUN_004903b2() cc=unknown
// callers: 
// callees: 

bool FUN_004903b2(int param_1,int param_2,undefined4 *param_3)

{
  bool bVar1;
  
  bVar1 = param_2 < *(int *)(param_1 + 0xc);
  if (bVar1) {
    *param_3 = *(undefined4 *)(param_1 + 0x14 + param_2 * 8);
  }
  return bVar1;
}

