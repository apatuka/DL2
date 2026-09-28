// FUN_00407d60 @ 00407d60 size=155 sig=undefined FUN_00407d60() cc=unknown
// callers: FUN_0040b5cc,FUN_00407e78,FUN_00409f6c,FUN_004094d8,FUN_004105e8,FUN_004096a8,FUN_0040a2a4,FUN_0041026c,FUN_00409c5c,FUN_0040a5a4,FUN_00408bf4,FUN_00409d9c,FUN_00409ef0,FUN_0040d228,FUN_00409964,FUN_0040cea4,FUN_0040d080,FUN_0040ef18,FUN_00408e3c,FUN_0040d3bc
// callees: FUN_004058e0,FUN_004056fc,memset,FUN_004b0a30,FUN_004b0b44,FUN_0044feec

undefined4 *
FUN_00407d60(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6,int param_7)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int *piVar4;
  
  iVar1 = FUN_0044feec(param_4);
  if (iVar1 == 0) {
    puVar2 = (undefined4 *)FUN_004b0b44(0x44);
    memset(puVar2,0,0x44);
    *puVar2 = 2;
    puVar2[1] = param_2;
    puVar2[2] = param_3;
    puVar2[3] = 0;
    puVar2[7] = param_4;
    puVar2[8] = param_5;
    puVar2[9] = param_6;
    puVar3 = (undefined4 *)FUN_004058e0(param_1,puVar2);
    if (puVar3 == (undefined4 *)0x0) {
      FUN_004056fc(param_1,puVar2);
    }
    else {
      if (param_7 != 0) {
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

