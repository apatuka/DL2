// FUN_00421efc @ 00421efc size=183 sig=undefined FUN_00421efc() cc=unknown
// callers: FUN_00422bd8,FUN_00423104,FUN_00421fb4
// callees: FUN_00456d00

undefined4 FUN_00421efc(void)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined *puVar4;
  
  uVar2 = 0;
  iVar3 = 0;
  puVar4 = &DAT_005a43d0;
  do {
    if (DAT_004d5b18 < iVar3) {
      return uVar2;
    }
    *(uint *)(puVar4 + 0x1c) = *(uint *)(puVar4 + 0x1c) | 4;
    iVar1 = FUN_00456d00((int)*(short *)(puVar4 + 0x1a),(int)(char)*PTR_DAT_004d5988);
    if (iVar1 == 0) {
      if (DAT_00583c20 != 0) {
        iVar1 = FUN_00456d00((int)*(short *)(puVar4 + 0x1a),1);
        if (iVar1 == 0) {
          iVar1 = FUN_00456d00((int)*(short *)(puVar4 + 0x1a),2);
          if (iVar1 == 0) {
            iVar1 = FUN_00456d00((int)*(short *)(puVar4 + 0x1a),3);
            if (iVar1 == 0) {
              iVar1 = FUN_00456d00((int)*(short *)(puVar4 + 0x1a),4);
              if (iVar1 == 0) {
                iVar1 = FUN_00456d00((int)*(short *)(puVar4 + 0x1a),5);
                if (iVar1 == 0) {
                  iVar1 = FUN_00456d00((int)*(short *)(puVar4 + 0x1a),6);
                  if (iVar1 == 0) goto LAB_00421f97;
                }
              }
            }
          }
        }
        goto LAB_00421f91;
      }
    }
    else {
LAB_00421f91:
      *(uint *)(puVar4 + 0x1c) = *(uint *)(puVar4 + 0x1c) & 0xfffffffb;
      uVar2 = 1;
    }
LAB_00421f97:
    iVar3 = iVar3 + 1;
    puVar4 = puVar4 + 0xadc;
  } while( true );
}

