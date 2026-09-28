// FUN_00408288 @ 00408288 size=135 sig=undefined FUN_00408288() cc=unknown
// callers: FUN_00405b38,FUN_00407e78
// callees: FUN_004058e0,memset,FUN_004056fc,FUN_004b0b44,FUN_004b0a30

undefined4 *
FUN_00408288(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,int param_6)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int *piVar3;
  
  puVar1 = (undefined4 *)FUN_004b0b44(0x44);
  memset(puVar1,0,0x44);
  *puVar1 = 3;
  puVar1[1] = param_2;
  puVar1[2] = param_3;
  puVar1[3] = 0;
  puVar1[7] = param_4;
  puVar1[8] = param_5;
  puVar2 = (undefined4 *)FUN_004058e0(param_1,puVar1);
  if (puVar2 == (undefined4 *)0x0) {
    FUN_004056fc(param_1,puVar1);
  }
  else {
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

