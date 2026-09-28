// FUN_00409964 @ 00409964 size=432 sig=undefined FUN_00409964() cc=unknown
// callers: FUN_00409b58
// callees: FUN_00402cc0,FUN_00401558,FUN_00407d60

void FUN_00409964(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  piVar3 = &DAT_00521bb4;
  do {
    iVar1 = *piVar3;
    iVar2 = FUN_00401558(iVar1);
    if (iVar2 * 100 < (int)*(short *)(iVar1 + 0x30)) {
      switch(*(undefined1 *)(iVar1 + 0x21)) {
      case 0:
        iVar2 = FUN_00402cc0(param_1,0x2a,(int)*(short *)(iVar1 + 0x1a),0xf);
        if (iVar2 != 0) {
          FUN_00407d60(param_1,3,0xfffffc18,0x2a,(int)*(short *)(iVar1 + 0x1a),0xf,0);
        }
        iVar2 = FUN_00402cc0(param_1,0x29,(int)*(short *)(iVar1 + 0x1a),0xc);
        if (iVar2 != 0) {
          FUN_00407d60(param_1,3,0xfffffc18,0x29,(int)*(short *)(iVar1 + 0x1a),0xc,0);
        }
        break;
      case 1:
        iVar2 = FUN_00402cc0(param_1,5,(int)*(short *)(iVar1 + 0x1a),0xc);
        if (iVar2 != 0) {
          FUN_00407d60(param_1,3,0xfffffc18,5,(int)*(short *)(iVar1 + 0x1a),0xc,0);
        }
        break;
      case 2:
        iVar2 = FUN_00402cc0(param_1,5,(int)*(short *)(iVar1 + 0x1a),0xd);
        if (iVar2 != 0) {
          FUN_00407d60(param_1,3,0xfffffc18,5,(int)*(short *)(iVar1 + 0x1a),0xd,0);
        }
        iVar2 = FUN_00402cc0(param_1,8,(int)*(short *)(iVar1 + 0x1a),4);
        if ((iVar2 != 0) && ((1 << ((byte)param_1 & 0x1f) & (int)DAT_004fbf94) != 0)) {
          FUN_00407d60(param_1,3,0xfffffc18,8,(int)*(short *)(iVar1 + 0x1a),4,0);
        }
        break;
      case 3:
        iVar2 = FUN_00402cc0(param_1,0xb,(int)*(short *)(iVar1 + 0x1a),0xf);
        if (iVar2 != 0) {
          FUN_00407d60(param_1,3,0xfffffc18,0xb,(int)*(short *)(iVar1 + 0x1a),0xf,0);
        }
        break;
      case 4:
        iVar2 = FUN_00402cc0(param_1,8,(int)*(short *)(iVar1 + 0x1a),3);
        if (iVar2 != 0) {
          FUN_00407d60(param_1,3,0xfffffc18,8,(int)*(short *)(iVar1 + 0x1a),3,0);
        }
      }
    }
    piVar3 = (int *)piVar3[1];
  } while (piVar3 != &DAT_00521bb4);
  return;
}

