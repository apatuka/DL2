// FUN_00408b58 @ 00408b58 size=153 sig=undefined FUN_00408b58() cc=unknown
// callers: FUN_0040aaa4,FUN_00408310,FUN_0041026c,FUN_00407e78,FUN_00409b58,FUN_0040a098
// callees: FUN_004058e0,memset,FUN_004056fc,FUN_004b0b44,FUN_004b0a30

undefined4 *
FUN_00408b58(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,int param_5
            ,int param_6)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int *piVar3;
  
  puVar1 = (undefined4 *)FUN_004b0b44(0x44);
  memset(puVar1,0,0x44);
  *puVar1 = 8;
  puVar1[1] = param_2;
  puVar1[2] = param_3;
  puVar1[3] = 0;
  puVar1[7] = param_4;
  puVar1[8] = 0xffffffff;
  puVar2 = (undefined4 *)FUN_004058e0(param_1,puVar1);
  if (puVar2 == (undefined4 *)0x0) {
    puVar1[8] = param_5;
    FUN_004056fc(param_1,puVar1);
  }
  else {
    puVar2[3] = 0;
    puVar2[8] = puVar2[8] + param_5;
    if (param_6 != 0) {
      piVar3 = puVar2 + 2;
      if ((int)puVar2[2] <= (int)puVar1[2]) {
        piVar3 = puVar1 + 2;
      }
      puVar2[2] = *piVar3;
    }
    FUN_004b0a30(puVar1);
    puVar1 = puVar2;
  }
  return puVar1;
}

