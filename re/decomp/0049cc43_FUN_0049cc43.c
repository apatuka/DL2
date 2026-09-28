// FUN_0049cc43 @ 0049cc43 size=106 sig=undefined FUN_0049cc43() cc=unknown
// callers: FUN_004a2847
// callees: FUN_0049eb44,FUN_0049ea99

void FUN_0049cc43(undefined4 param_1,int param_2,uint param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  if (param_2 == 1) {
    uVar2 = 0x2a;
    param_3 = param_3 & 0x20;
  }
  else if (param_2 == 2) {
    uVar2 = 0x2b;
    param_3 = param_3 & 0x20;
  }
  else if (param_2 == 5) {
    uVar2 = 0x2c;
    param_3 = param_3 & 0x20;
  }
  else if (param_2 == 6) {
    uVar2 = 0x2d;
    param_3 = param_3 & 0x20;
  }
  else {
    uVar2 = 0x2f;
  }
  uVar3 = 2;
  uVar1 = FUN_0049ea99(param_1);
  FUN_0049eb44(uVar1,param_1,uVar3,uVar2,param_2,param_3);
  return;
}

