// FUN_004a5699 @ 004a5699 size=245 sig=undefined FUN_004a5699() cc=unknown
// callers: FUN_004a578e
// callees: FUN_004989de,FUN_00498adf,FUN_00498af3,GlobalLock,GlobalUnlock,FUN_0048e5f8,FUN_00498b98,FUN_004906e3
// strings: \"Requested tile out of range, wanted %d, max %d\"

HGLOBAL FUN_004a5699(HGLOBAL param_1,int param_2)

{
  int iVar1;
  HGLOBAL pvVar2;
  short *psVar3;
  undefined4 uVar4;
  LPVOID pvVar5;
  int iVar6;
  
  if (param_1 == (HGLOBAL)0x0) {
    pvVar2 = (HGLOBAL)0x0;
  }
  else {
    psVar3 = GlobalLock(param_1);
    if (param_2 < *psVar3) {
      pvVar2 = *(HGLOBAL *)(psVar3 + param_2 * 4 + 8);
      if (pvVar2 == (HGLOBAL)0x0) {
        uVar4 = FUN_00498adf(param_1);
        FUN_00498af3(param_1,0);
        iVar6 = *(int *)(psVar3 + param_2 * 4 + 10);
        iVar1 = *(int *)(psVar3 + param_2 * 4 + 6);
        pvVar2 = (HGLOBAL)FUN_00498b98(iVar6 - iVar1);
        if (pvVar2 != (HGLOBAL)0x0) {
          pvVar5 = GlobalLock(pvVar2);
          iVar6 = FUN_004906e3(*(undefined4 *)(psVar3 + 2),*(undefined4 *)(psVar3 + param_2 * 4 + 6)
                               ,iVar6 - iVar1,pvVar5);
          if (iVar6 == 0) {
            *(HGLOBAL *)(psVar3 + param_2 * 4 + 8) = pvVar2;
            GlobalUnlock(pvVar2);
            GlobalUnlock(param_1);
            FUN_00498af3(param_1,uVar4);
            return pvVar2;
          }
          GlobalUnlock(pvVar2);
          GlobalUnlock(param_1);
          FUN_004989de(pvVar2);
        }
        FUN_00498af3(param_1,uVar4);
        pvVar2 = (HGLOBAL)0x0;
      }
      else {
        GlobalUnlock(param_1);
      }
    }
    else {
      FUN_0048e5f8(s_Requested_tile_out_of_range__wan_0051e4e8,param_2,(int)*psVar3);
      GlobalUnlock(param_1);
      pvVar2 = (HGLOBAL)0x0;
    }
  }
  return pvVar2;
}

