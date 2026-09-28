// FUN_00409c5c @ 00409c5c size=215 sig=undefined FUN_00409c5c() cc=unknown
// callers: FUN_00409d38
// callees: FUN_00402cc0,FUN_0044d034,FUN_00407d60,FUN_0044d1a4

void FUN_00409c5c(int param_1)

{
  int iVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  
  bVar2 = false;
  piVar5 = &DAT_00521bb4;
  do {
    iVar1 = *piVar5;
    iVar3 = FUN_0044d1a4(iVar1,9,0);
    if (iVar3 == -1) {
      iVar3 = FUN_0044d034(iVar1,4);
      iVar4 = FUN_0044d034(iVar1,7);
      iVar3 = iVar3 + iVar4;
      iVar4 = FUN_0044d034(iVar1,8);
      if ((2 < iVar4 + iVar3) ||
         (*(int *)(&DAT_0055a838 + param_1 * 4 + *(char *)(iVar1 + 0x22) * 0x1a2) == 6)) {
        iVar3 = FUN_00402cc0(param_1,0x25,(int)*(short *)(iVar1 + 0x1a),0xe);
        if (iVar3 != 0) {
          FUN_00407d60(param_1,2,0xfffffc18,0x25,(int)*(short *)(iVar1 + 0x1a),0xb,0);
        }
      }
    }
    else {
      bVar2 = true;
    }
    piVar5 = (int *)piVar5[1];
  } while (piVar5 != &DAT_00521bb4);
  if ((!bVar2) || (DAT_004d5b00 == '\0')) {
    FUN_00407d60(param_1,2,0x1389,0x25,0xffffffff,0xb,1);
  }
  return;
}

