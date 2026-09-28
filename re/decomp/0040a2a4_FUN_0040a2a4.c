// FUN_0040a2a4 @ 0040a2a4 size=145 sig=undefined FUN_0040a2a4() cc=unknown
// callers: FUN_0040a420
// callees: FUN_00402cc0,FUN_00401558,FUN_00407d60

void FUN_0040a2a4(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  piVar3 = &DAT_00521bb4;
  do {
    iVar1 = *piVar3;
    iVar2 = FUN_00401558(iVar1);
    if (iVar2 * 100 < (int)*(short *)(iVar1 + 0x30)) {
      iVar2 = FUN_00402cc0(param_1,0x12,(int)*(short *)(iVar1 + 0x1a),0xe);
      if (iVar2 == 0) {
        iVar2 = FUN_00402cc0(param_1,0x13,(int)*(short *)(iVar1 + 0x1a),0xe);
        if (iVar2 != 0) {
          FUN_00407d60(param_1,4,0xfffffe0c,0x13,(int)*(short *)(iVar1 + 0x1a),0xe,0);
        }
      }
      else {
        FUN_00407d60(param_1,4,0xfffffe0c,0x12,(int)*(short *)(iVar1 + 0x1a),0xe,0);
      }
    }
    piVar3 = (int *)piVar3[1];
  } while (piVar3 != &DAT_00521bb4);
  return;
}

