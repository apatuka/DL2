// FUN_00441388 @ 00441388 size=118 sig=undefined FUN_00441388() cc=unknown
// callers: FUN_0040350c,FUN_0042c934,FUN_00485034,FUN_004418ac,FUN_0046bd3c,FUN_00406d10,FUN_00429a04,FUN_00441868,FUN_004073e4,FUN_00406dd8
// callees: 

bool FUN_00441388(int param_1,int param_2,uint param_3)

{
  bool bVar1;
  
  if (DAT_004d5af4 == 0) {
    bVar1 = false;
  }
  else if ((param_1 < 0) || (DAT_004d5aec <= param_1)) {
    bVar1 = false;
  }
  else if ((param_2 < 0) || (DAT_004d5aec <= param_2)) {
    bVar1 = false;
  }
  else if (((&DAT_0059f3f6)[param_1 * 0xb6 + param_2] & 0x10) == 0) {
    bVar1 = param_3 == ((&DAT_0059f3f6)[param_1 * 0xb6 + param_2] & param_3);
  }
  else {
    bVar1 = param_3 == (param_3 & 0x1e);
  }
  return bVar1;
}

