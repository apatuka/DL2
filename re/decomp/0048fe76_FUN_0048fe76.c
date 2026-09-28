// FUN_0048fe76 @ 0048fe76 size=25 sig=undefined FUN_0048fe76() cc=unknown
// callers: CalculateGameCRC
// callees: FUN_0048fd54

uint FUN_0048fe76(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  
  uVar1 = FUN_0048fd54(param_2,0xffffffff,param_1);
  return uVar1 ^ 0xffffffff;
}

