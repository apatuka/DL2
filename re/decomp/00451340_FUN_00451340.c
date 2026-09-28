// FUN_00451340 @ 00451340 size=32 sig=undefined FUN_00451340() cc=unknown
// callers: FUN_0045209c
// callees: 

void FUN_00451340(int param_1,int param_2,char param_3)

{
  (&DAT_0057cf4d)[param_1 + param_2 * 0x24] =
       (&DAT_0057cf4d)[param_1 + param_2 * 0x24] | param_3 << 4;
  return;
}

