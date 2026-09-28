// FUN_0049028e @ 0049028e size=246 sig=undefined FUN_0049028e() cc=unknown
// callers: FUN_00490bca
// callees: FUN_004950bc,FUN_00498b98,FUN_00491101,FUN_00498b4c,GlobalUnlock,FUN_00498aa4,FUN_00490261,FUN_004989de,GlobalLock,FUN_00488ba3,FUN_0048fea9,FUN_00498aab

HGLOBAL FUN_0049028e(undefined4 param_1)

{
  HGLOBAL pvVar1;
  LPVOID pvVar2;
  int iVar3;
  int iVar4;
  
  pvVar1 = (HGLOBAL)FUN_00498b98(0x14);
  if (pvVar1 != (HGLOBAL)0x0) {
    pvVar2 = GlobalLock(pvVar1);
    iVar3 = FUN_00488ba3(param_1,pvVar2,0x14);
    if (iVar3 == 0x14) {
      iVar3 = FUN_00490261(pvVar2);
      if (iVar3 != 0) {
        iVar4 = *(int *)((int)pvVar2 + 0xc) * 8 + *(int *)((int)pvVar2 + 0x10);
        GlobalUnlock(pvVar1);
        iVar3 = FUN_00498b4c(pvVar1,iVar4 + 0x14);
        if (iVar3 == 0) {
          pvVar2 = GlobalLock(pvVar1);
          iVar3 = FUN_00488ba3(param_1,(int)pvVar2 + 0x14,iVar4);
          if (iVar3 == iVar4) {
            GlobalUnlock(pvVar1);
            pvVar1 = (HGLOBAL)FUN_00491101(pvVar1);
            if (pvVar1 == (HGLOBAL)0x0) {
              return (HGLOBAL)0x0;
            }
            pvVar2 = GlobalLock(pvVar1);
            FUN_0048fea9(pvVar2);
            GlobalUnlock(pvVar1);
            if (DAT_0051dafc == 0) {
              return pvVar1;
            }
            FUN_00498aa4(pvVar1);
            FUN_00498aab(pvVar1,1);
            return pvVar1;
          }
          if (-1 < iVar3) {
            iVar3 = 0x2000000a;
          }
          FUN_004950bc(iVar3);
        }
      }
    }
    else {
      if (-1 < iVar3) {
        iVar3 = 0x2000000a;
      }
      FUN_004950bc(iVar3);
    }
    FUN_004989de(pvVar1);
  }
  return (HGLOBAL)0x0;
}

