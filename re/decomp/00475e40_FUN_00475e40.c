// FUN_00475e40 @ 00475e40 size=145 sig=undefined FUN_00475e40() cc=unknown
// callers: 
// callees: FUN_004779c0,FUN_00474d90,FUN_0044c9a0

void FUN_00475e40(int param_1,uint param_2,ushort *param_3,int param_4,int param_5)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  if (param_4 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = 0x4000;
  }
  if (param_5 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = 0x8000;
  }
  if (param_3 == (ushort *)0x0) {
    uVar3 = 0xffffffff;
  }
  else {
    uVar3 = (uint)*param_3;
  }
  if (DAT_0058f1fc == 0) {
    FUN_0044c9a0(param_1,param_2,param_3,param_4,param_5);
  }
  else {
    FUN_004779c0((int)*(char *)(param_1 + 0x20),0x21,(int)*(short *)(param_1 + 0x1a),uVar3,
                 param_2 & 0xff | uVar1 | uVar2,0,0);
    FUN_00474d90(0x21,(int)*(char *)(param_1 + 0x20));
  }
  return;
}

