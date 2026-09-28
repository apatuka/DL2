// FUN_00441590 @ 00441590 size=61 sig=undefined FUN_00441590() cc=unknown
// callers: NetBreakPact_6a70
// callees: 

bool FUN_00441590(int param_1,int param_2,uint param_3)

{
  bool bVar1;
  
  bVar1 = DAT_004d5af4 != 0;
  if (bVar1) {
    (&DAT_0059f3da)[param_1 * 0xb6 + param_2] = (&DAT_0059f3da)[param_1 * 0xb6 + param_2] & ~param_3
    ;
  }
  return bVar1;
}

