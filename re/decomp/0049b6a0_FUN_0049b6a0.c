// FUN_0049b6a0 @ 0049b6a0 size=336 sig=undefined FUN_0049b6a0() cc=unknown
// callers: 
// callees: FUN_00498b98,GlobalLock,GlobalUnlock,FUN_004989cf,FUN_0048fbbf,FUN_0048f8e8,FUN_0048f992,FUN_00498ba9

HGLOBAL FUN_0049b6a0(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  LPVOID pvVar4;
  uint uVar5;
  int iVar6;
  HGLOBAL unaff_EDI;
  undefined1 local_14 [2];
  ushort local_12;
  int local_c [2];
  
  iVar6 = 0;
  iVar1 = FUN_0048f8e8(param_1,param_2);
  if (iVar1 == 0) {
    unaff_EDI = (HGLOBAL)0x0;
  }
  else {
    iVar2 = FUN_0048f992(iVar1,local_c,8);
    if (((((iVar2 == 8) && (local_c[0] == 0x52494646)) &&
         (iVar2 = FUN_0048f992(iVar1,local_c,4), iVar2 == 4)) &&
        ((local_c[0] == 0x50414c20 && (iVar2 = FUN_0048f992(iVar1,local_c,8), iVar2 == 8)))) &&
       (iVar2 = FUN_0048f992(iVar1,local_14,4), iVar2 == 4)) {
      iVar2 = (uint)local_12 << 2;
      iVar6 = FUN_00498ba9(iVar2);
      if (((iVar6 != 0) && (iVar3 = FUN_0048f992(iVar1,iVar6,iVar2), iVar3 == iVar2)) &&
         (unaff_EDI = (HGLOBAL)FUN_00498b98((uint)local_12 * 4 + 8), unaff_EDI != (HGLOBAL)0x0)) {
        pvVar4 = GlobalLock(unaff_EDI);
        *(ushort *)((int)pvVar4 + 2) = local_12;
        *(undefined2 *)((int)pvVar4 + 4) = 0;
        *(undefined2 *)((int)pvVar4 + 6) = 0;
        for (uVar5 = 0; uVar5 < local_12; uVar5 = uVar5 + 1) {
          *(undefined1 *)((int)pvVar4 + uVar5 * 4 + 8) = *(undefined1 *)(iVar6 + uVar5 * 4);
          *(undefined1 *)((int)pvVar4 + uVar5 * 4 + 9) = *(undefined1 *)(iVar6 + 1 + uVar5 * 4);
          *(undefined1 *)((int)pvVar4 + uVar5 * 4 + 10) = *(undefined1 *)(iVar6 + 2 + uVar5 * 4);
          *(undefined1 *)((int)pvVar4 + uVar5 * 4 + 0xb) = 0;
        }
        GlobalUnlock(unaff_EDI);
      }
    }
    FUN_0048fbbf(iVar1,0);
    if (iVar6 != 0) {
      FUN_004989cf(iVar6);
    }
  }
  return unaff_EDI;
}

