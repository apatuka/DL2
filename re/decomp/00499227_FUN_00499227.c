// FUN_00499227 @ 00499227 size=307 sig=undefined FUN_00499227() cc=unknown
// callers: 
// callees: FUN_0048fade,GlobalLock,FUN_00498e00,FUN_0048fbf8,GlobalUnlock,FUN_0048fd38,FUN_0048fbbf,FUN_0048f8e8,FUN_0048d76a

HGLOBAL FUN_00499227(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  undefined1 uVar2;
  int iVar3;
  int iVar4;
  LPVOID pvVar5;
  ushort uVar6;
  HGLOBAL unaff_EDI;
  undefined1 auStack_384 [768];
  char local_84;
  char local_83;
  
  iVar3 = FUN_0048f8e8(param_1,param_2);
  if (iVar3 == 0) {
    unaff_EDI = (HGLOBAL)0x0;
  }
  else {
    iVar4 = FUN_00498e00(&local_84,iVar3);
    if (iVar4 == 0) {
      iVar4 = FUN_0048fbf8(iVar3);
      if (iVar4 == 0) {
        if (local_84 == '\n') {
          if (local_83 == '\x05') {
            FUN_0048fade(iVar3,0xfffffcff,2);
            cVar1 = FUN_0048fd38(iVar3);
            if (cVar1 == '\f') {
              uVar6 = 0;
              do {
                uVar2 = FUN_0048fd38(iVar3);
                auStack_384[uVar6] = uVar2;
                uVar6 = uVar6 + 1;
              } while (uVar6 < 0x300);
              unaff_EDI = (HGLOBAL)FUN_0048d76a(0x100,0);
              if (unaff_EDI != (HGLOBAL)0x0) {
                pvVar5 = GlobalLock(unaff_EDI);
                for (uVar6 = 0; (int)(uint)uVar6 < (int)*(short *)((int)pvVar5 + 2);
                    uVar6 = uVar6 + 1) {
                  *(undefined1 *)((int)pvVar5 + (uint)uVar6 * 4 + 8) = auStack_384[(uint)uVar6 * 3];
                  *(undefined1 *)((int)pvVar5 + (uint)uVar6 * 4 + 9) =
                       auStack_384[(uint)uVar6 * 3 + 1];
                  *(undefined1 *)((int)pvVar5 + (uint)uVar6 * 4 + 10) =
                       auStack_384[(uint)uVar6 * 3 + 2];
                  *(undefined1 *)((int)pvVar5 + (uint)uVar6 * 4 + 0xb) = 0;
                }
                GlobalUnlock(unaff_EDI);
              }
            }
          }
          FUN_0048fbbf(iVar3,0);
        }
        else {
          FUN_0048fbbf(iVar3,0);
          unaff_EDI = (HGLOBAL)0x0;
        }
      }
      else {
        FUN_0048fbbf(iVar3,0);
        unaff_EDI = (HGLOBAL)0x0;
      }
    }
    else {
      FUN_0048fbbf(iVar3,0);
      unaff_EDI = (HGLOBAL)0x0;
    }
  }
  return unaff_EDI;
}

