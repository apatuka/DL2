// FUN_004101d4 @ 004101d4 size=149 sig=undefined FUN_004101d4() cc=unknown
// callers: FUN_0040febc
// callees: FUN_0044ff28,FUN_004b0a30,FUN_004b0b44,memset,FUN_004058e0,FUN_004056fc

undefined4 *
FUN_004101d4(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,int param_6)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int *piVar4;
  
  iVar1 = FUN_0044ff28(param_4);
  if (iVar1 == 0) {
    puVar2 = (undefined4 *)FUN_004b0b44(0x44);
    memset(puVar2,0,0x44);
    *puVar2 = 5;
    puVar2[1] = param_2;
    puVar2[2] = param_3;
    puVar2[3] = 0;
    puVar2[7] = param_4;
    puVar2[8] = param_5;
    puVar3 = (undefined4 *)FUN_004058e0(param_1,puVar2);
    if (puVar3 == (undefined4 *)0x0) {
      FUN_004056fc(param_1,puVar2);
    }
    else {
      if (param_6 != 0) {
        piVar4 = puVar3 + 2;
        if ((int)puVar3[2] <= (int)puVar2[2]) {
          piVar4 = puVar2 + 2;
        }
        puVar3[2] = *piVar4;
      }
      FUN_004b0a30(puVar2);
      puVar2 = puVar3;
    }
  }
  else {
    puVar2 = (undefined4 *)0x0;
  }
  return puVar2;
}

