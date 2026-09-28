// FUN_004068f8 @ 004068f8 size=266 sig=undefined FUN_004068f8() cc=unknown
// callers: FUN_004105e8
// callees: FUN_0044eeb4,FUN_0040668c,FUN_0044c8ac,FUN_004023dc,FUN_0044ba40,FUN_00406424,FUN_0044c718,FUN_004067b4,FUN_0044ba18

undefined4 FUN_004068f8(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  FUN_004067b4();
  do {
    do {
      iVar1 = FUN_0040668c(param_1,0xb,param_2);
      if (iVar1 == 0) {
        return 0;
      }
    } while (*(int *)(&DAT_004f9de6 + *(char *)(iVar1 + 4) * 0x32) != param_3);
    uVar2 = FUN_004023dc(iVar1,0xb);
    iVar3 = FUN_0044c8ac(param_2,iVar1,uVar2);
  } while (iVar3 == 0);
  iVar3 = FUN_004023dc(iVar1,0x15);
  if (iVar3 != -1) {
    iVar4 = FUN_0044ba18(iVar1);
    iVar5 = FUN_0044ba40(iVar1);
    if (iVar4 < iVar5) {
      iVar4 = FUN_0044eeb4(&DAT_0059f160 + param_1 * 0x2d8,
                           &DAT_005a43d0 + *(short *)(iVar1 + 8) * 0xadc,(int)*(char *)(iVar1 + 7),
                           iVar3,*(undefined4 *)(iVar1 + 0x18 + iVar3 * 4));
      iVar5 = FUN_0044c718(iVar1);
      if ((*(short *)(iVar1 + 0x16) + iVar4 < iVar5) &&
         (iVar4 = FUN_00406424(param_1,&DAT_005a43d0 + *(short *)(iVar1 + 8) * 0xadc), iVar4 != 0))
      {
        FUN_0044c8ac(&DAT_005a43d0 + *(short *)(iVar1 + 8) * 0xadc,iVar1,iVar3);
      }
    }
  }
  return 1;
}

