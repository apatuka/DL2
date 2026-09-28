// FUN_0043cfb0 @ 0043cfb0 size=81 sig=undefined FUN_0043cfb0() cc=unknown
// callers: FUN_0044a328
// callees: FUN_0043c6c4,FUN_0043cf64

int FUN_0043cfb0(int param_1,int param_2)

{
  int iVar1;
  int in_EAX;
  
  iVar1 = DAT_00559dac;
  if (param_1 == 0) {
    in_EAX = DAT_00559dac + param_2 * -0x28;
  }
  else if (param_1 == 1) {
    in_EAX = param_2 * 0x28 + DAT_00559dac;
  }
  FUN_0043cf64(in_EAX);
  if (iVar1 != DAT_00559dac) {
    FUN_0043c6c4();
  }
  return DAT_00559dac;
}

