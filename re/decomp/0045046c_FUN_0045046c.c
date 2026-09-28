// FUN_0045046c @ 0045046c size=54 sig=undefined FUN_0045046c() cc=unknown
// callers: FUN_004237d0
// callees: 

undefined4 FUN_0045046c(int param_1,int param_2)

{
  undefined4 uVar1;
  
  if ((((param_2 == 7) || (param_2 == 8)) || (param_1 == 7)) || (param_1 == 8)) {
    uVar1 = 0;
  }
  else {
    uVar1 = *(undefined4 *)(&DAT_004cac00 + param_2 * 4 + param_1 * 0x1c);
  }
  return uVar1;
}

