// FUN_00498cab @ 00498cab size=32 sig=undefined FUN_00498cab() cc=unknown
// callers: 
// callees: 

undefined4 FUN_00498cab(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = DAT_0065ee18;
  DAT_0065ee18 = param_1;
  *(undefined4 *)(DAT_0051e1d8 + 0x14) = param_1;
  return uVar1;
}

