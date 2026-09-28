// FUN_004067d0 @ 004067d0 size=293 sig=undefined FUN_004067d0() cc=unknown
// callers: FUN_00408bf4,FUN_00408fdc,FUN_00410870,FUN_0040d228,FUN_00409120,FUN_0040cea4,FUN_0040d080,FUN_00408e3c,FUN_0040d3bc,FUN_00406a08
// callees: FUN_0044eeb4,FUN_0040668c,FUN_0044c8ac,FUN_004023dc,FUN_0044ba40,FUN_00406538,FUN_00406424,FUN_0044c718,FUN_004067b4,FUN_0044ba18

int FUN_004067d0(int param_1,undefined4 param_2,undefined4 param_3,int param_4,int param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int local_8;
  
  local_8 = 0;
  FUN_004067b4();
  while ((0 < param_4 && (0 < param_5))) {
    iVar1 = FUN_0040668c(param_1,param_3,param_2);
    if (iVar1 == 0) {
      return local_8;
    }
    iVar2 = FUN_00406538(iVar1,param_3,param_4,&param_5,&stack0x00000018);
    iVar3 = FUN_004023dc(iVar1,0x15);
    if (iVar3 != -1) {
      iVar4 = FUN_0044ba18(iVar1);
      iVar5 = FUN_0044ba40(iVar1);
      if (iVar4 < iVar5) {
        iVar4 = FUN_0044eeb4(&DAT_0059f160 + param_1 * 0x2d8,
                             &DAT_005a43d0 + *(short *)(iVar1 + 8) * 0xadc,(int)*(char *)(iVar1 + 7)
                             ,iVar3,*(undefined4 *)(iVar1 + 0x18 + iVar3 * 4));
        iVar5 = FUN_0044c718(iVar1);
        if ((*(short *)(iVar1 + 0x16) + iVar4 < iVar5) &&
           (iVar4 = FUN_00406424(param_1,&DAT_005a43d0 + *(short *)(iVar1 + 8) * 0xadc), iVar4 != 0)
           ) {
          FUN_0044c8ac(&DAT_005a43d0 + *(short *)(iVar1 + 8) * 0xadc,iVar1,iVar3);
        }
      }
    }
    local_8 = local_8 + iVar2;
    param_4 = param_4 - iVar2;
  }
  return local_8;
}

