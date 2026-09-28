// FUN_00484ee0 @ 00484ee0 size=23 sig=undefined FUN_00484ee0() cc=unknown
// callers: FUN_0044e0a8,SendTerritoryData,FUN_00405b38,FUN_0040f658,FUN_004607d8,FUN_0041d710,FUN_0041c418,FUN_0041ffd4,FUN_0040f6b0,FUN_00420d34,ProduceUnits
// callees: 

undefined1 FUN_00484ee0(int param_1)

{
  undefined1 uVar1;
  
  if (*(undefined1 **)(param_1 + 4) == (undefined1 *)0x0) {
    uVar1 = 0;
  }
  else {
    uVar1 = **(undefined1 **)(param_1 + 4);
  }
  return uVar1;
}

