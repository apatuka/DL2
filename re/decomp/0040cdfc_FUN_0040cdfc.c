// FUN_0040cdfc @ 0040cdfc size=165 sig=undefined FUN_0040cdfc() cc=unknown
// callers: FUN_0040a14c,FUN_00408e3c,FUN_0041026c,FUN_00407e78,FUN_0040d080,FUN_00408310,FUN_0040a420,FUN_00410870,FUN_0040d228,FUN_0040cea4,FUN_0040854c
// callees: FUN_00450150,FUN_004b0a30,FUN_004b0b44,memset,FUN_004058e0,FUN_004056fc

undefined4 *
FUN_0040cdfc(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,int param_5)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int *piVar4;
  
  iVar1 = FUN_00450150((int)(char)(&DAT_0059f162)[param_1 * 0x2d8],param_4);
  if (iVar1 == 0) {
    puVar2 = (undefined4 *)0x0;
  }
  else {
    puVar2 = (undefined4 *)FUN_004b0b44(0x44);
    memset(puVar2,0,0x44);
    *puVar2 = 7;
    puVar2[1] = param_2;
    puVar2[2] = param_3;
    puVar2[3] = 0;
    puVar2[7] = param_4;
    puVar3 = (undefined4 *)FUN_004058e0(param_1,puVar2);
    if (puVar3 == (undefined4 *)0x0) {
      FUN_004056fc(param_1,puVar2);
    }
    else {
      if (param_5 != 0) {
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
  return puVar2;
}

