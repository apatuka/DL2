// FUN_00444fd4 @ 00444fd4 size=108 sig=undefined FUN_00444fd4() cc=unknown
// callers: FUN_00453350,FUN_00444fd4,FUN_0045539c,FUN_00445270,FUN_00444e88
// callees: FUN_00444ae4,FUN_00445074,FUN_00444fd4,FUN_00444abc

void FUN_00444fd4(int param_1)

{
  byte *pbVar1;
  byte *pbVar2;
  int iVar3;
  
  iVar3 = FUN_00444abc(param_1);
  if (iVar3 != 0) {
    FUN_00445074((int)*(short *)(param_1 + 0xe),(int)*(short *)(param_1 + 0x10),
                 (int)*(short *)(param_1 + 0x12),(int)*(short *)(param_1 + 0x14));
    iVar3 = param_1 + -0x561a34;
    if (iVar3 < 0) {
      iVar3 = param_1 + -0x5619f5;
    }
    FUN_00444ae4(param_1);
    pbVar1 = DAT_00561a30;
    while (pbVar2 = pbVar1, pbVar2 != (byte *)0x0) {
      pbVar1 = *(byte **)(pbVar2 + 0x38);
      if (((*pbVar2 & 0x10) != 0) && ((short)(iVar3 >> 6) == *(short *)(pbVar2 + 0x32))) {
        FUN_00444fd4(pbVar2);
      }
    }
  }
  return;
}

