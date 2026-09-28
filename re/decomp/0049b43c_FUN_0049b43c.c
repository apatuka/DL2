// FUN_0049b43c @ 0049b43c size=67 sig=undefined FUN_0049b43c() cc=unknown
// callers: 
// callees: FUN_00499a4f

uint FUN_0049b43c(uint param_1,int param_2)

{
  byte bVar1;
  
  if (((param_1 & 0x80000000) != 0) && (param_2 != 0)) {
    bVar1 = FUN_00499a4f(param_1 >> 0x10,param_1 >> 8,param_1,param_2);
    param_1 = (uint)bVar1;
  }
  return param_1;
}

