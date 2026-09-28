// FUN_00498196 @ 00498196 size=358 sig=undefined FUN_00498196() cc=unknown
// callers: 
// callees: FUN_0048fade,FUN_00497eea,FUN_00497bea,FUN_0048f877,GlobalLock,FUN_004989cf,GlobalUnlock,FUN_0048fbbf,FUN_0048f8e8,FUN_00498ba9,FUN_0048f992,FUN_0048d76a

HGLOBAL FUN_00498196(undefined4 param_1,undefined4 param_2)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  LPVOID pvVar4;
  HGLOBAL hMem;
  undefined1 local_350 [768];
  undefined1 local_50 [64];
  uint local_10;
  undefined4 local_c;
  int local_8;
  
  local_c = 0;
  hMem = (HGLOBAL)0x0;
  piVar1 = (int *)FUN_00498ba9(0x1000);
  if (piVar1 == (int *)0x0) {
    hMem = (HGLOBAL)0x0;
  }
  else {
    iVar2 = FUN_0048f8e8(param_1,param_2);
    if (iVar2 == 0) {
      hMem = (HGLOBAL)0x0;
    }
    else {
      iVar3 = FUN_0048f992(iVar2,piVar1,0xc);
      if ((iVar3 == 0xc) && (*piVar1 == 0x4d524f46)) {
        local_8 = 0;
        if ((piVar1[2] == 0x4d424c49) || (piVar1[2] == 0x204d4250)) {
          while ((local_8 == 0 && (iVar3 = FUN_0048f992(iVar2,piVar1,8), iVar3 == 8))) {
            if (*piVar1 == 0x474e5243) {
              FUN_00497eea(piVar1,iVar2,local_50,&local_c);
            }
            else if (*piVar1 == 0x50414d43) {
              FUN_00497bea(piVar1,iVar2,local_350);
              local_8 = 1;
            }
            else {
              local_10 = piVar1[1];
              local_10 = FUN_0048f877(local_10);
              if ((local_10 & 1) != 0) {
                local_10 = local_10 + 1;
              }
              FUN_0048fade(iVar2,local_10,1);
            }
          }
        }
      }
      FUN_004989cf(piVar1);
      FUN_0048fbbf(iVar2,0);
      if ((local_8 == 1) && (hMem = (HGLOBAL)FUN_0048d76a(0x100,0), hMem != (HGLOBAL)0x0)) {
        pvVar4 = GlobalLock(hMem);
        for (iVar2 = 0; iVar2 < *(short *)((int)pvVar4 + 2); iVar2 = iVar2 + 1) {
          *(undefined1 *)((int)pvVar4 + iVar2 * 4 + 8) = local_350[iVar2 * 3];
          *(undefined1 *)((int)pvVar4 + iVar2 * 4 + 9) = local_350[iVar2 * 3 + 1];
          *(undefined1 *)((int)pvVar4 + iVar2 * 4 + 10) = local_350[iVar2 * 3 + 2];
          *(undefined1 *)((int)pvVar4 + iVar2 * 4 + 0xb) = 0;
        }
        GlobalUnlock(hMem);
      }
    }
  }
  return hMem;
}

