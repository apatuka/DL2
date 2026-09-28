// FUN_00410558 @ 00410558 size=141 sig=undefined FUN_00410558() cc=unknown
// callers: FUN_00405b38,FUN_0041026c
// callees: FUN_004b0a30,FUN_004b0b44,memset,FUN_004058e0,FUN_004056fc

undefined4 *
FUN_00410558(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6,int param_7)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int *piVar3;
  
  puVar1 = (undefined4 *)FUN_004b0b44(0x44);
  memset(puVar1,0,0x44);
  *puVar1 = 6;
  puVar1[1] = param_2;
  puVar1[2] = param_3;
  puVar1[3] = 0;
  puVar1[7] = param_4;
  puVar1[8] = param_5;
  puVar1[9] = param_6;
  puVar2 = (undefined4 *)FUN_004058e0(param_1,puVar1);
  if (puVar2 == (undefined4 *)0x0) {
    FUN_004056fc(param_1,puVar1);
  }
  else {
    if (param_7 != 0) {
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

