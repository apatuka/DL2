// FUN_004995ab @ 004995ab size=177 sig=undefined FUN_004995ab() cc=unknown
// callers: 
// callees: GlobalLock,GlobalUnlock,FUN_0048fbbf,FUN_0048f8e8,FUN_0048f992,FUN_0048d76a

HGLOBAL FUN_004995ab(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  LPVOID pvVar3;
  undefined1 *puVar4;
  undefined1 local_308 [768];
  HGLOBAL local_8;
  
  iVar1 = FUN_0048f8e8(param_1,param_2);
  if (iVar1 == 0) {
    local_8 = (HGLOBAL)0x0;
  }
  else {
    iVar2 = FUN_0048f992(iVar1,local_308,0x300);
    if (iVar2 == 0x300) {
      local_8 = (HGLOBAL)FUN_0048d76a(0x100,0);
      if (local_8 != (HGLOBAL)0x0) {
        pvVar3 = GlobalLock(local_8);
        *(undefined2 *)((int)pvVar3 + 2) = 0x100;
        *(undefined2 *)((int)pvVar3 + 4) = 0;
        *(undefined2 *)((int)pvVar3 + 6) = 0;
        puVar4 = local_308;
        iVar2 = 0;
        do {
          *(undefined1 *)((int)pvVar3 + iVar2 * 4 + 8) = *puVar4;
          *(undefined1 *)((int)pvVar3 + iVar2 * 4 + 9) = puVar4[1];
          *(undefined1 *)((int)pvVar3 + iVar2 * 4 + 10) = puVar4[2];
          puVar4 = puVar4 + 3;
          *(undefined1 *)((int)pvVar3 + iVar2 * 4 + 0xb) = 0;
          iVar2 = iVar2 + 1;
        } while (iVar2 < 0x100);
        GlobalUnlock(local_8);
      }
    }
    FUN_0048fbbf(iVar1,0);
  }
  return local_8;
}

