// FUN_0049002d @ 0049002d size=206 sig=undefined FUN_0049002d() cc=unknown
// callers: 
// callees: FUN_0048fe90,FUN_00498b98,FUN_00498a5c,FUN_004989ed,GlobalUnlock,FUN_004989de,FUN_004906e3,GlobalLock

int FUN_0049002d(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4,int param_5)

{
  undefined4 uVar1;
  int iVar2;
  HGLOBAL hMem;
  undefined2 *puVar3;
  int iVar4;
  
  iVar4 = 1;
  if (param_5 == 2) {
    if ((*(int *)(param_4 + 0x1c) != 0) &&
       (iVar2 = FUN_004989ed(*(undefined4 *)(param_4 + 0x1c)), iVar2 == 0)) {
      FUN_0048fe90(param_4);
    }
  }
  else if (param_5 == 3) {
    iVar2 = *(int *)(param_4 + 0x18);
    uVar1 = *(undefined4 *)(param_4 + 0x14);
    hMem = (HGLOBAL)FUN_00498b98(iVar2 + 2);
    if (hMem != (HGLOBAL)0x0) {
      puVar3 = GlobalLock(hMem);
      *puVar3 = 0;
      iVar4 = FUN_004906e3(param_1,uVar1,iVar2,puVar3 + 1);
      if (iVar4 == 0) {
        GlobalUnlock(hMem);
        FUN_0048fe90(param_4);
        *(HGLOBAL *)(param_4 + 0x1c) = hMem;
        iVar4 = param_4;
      }
      else {
        GlobalUnlock(hMem);
        FUN_004989de(hMem);
        iVar4 = 0;
      }
    }
  }
  else if (param_5 == 4) {
    if (*(int *)(param_4 + 0x1c) != 0) {
      FUN_00498a5c(*(undefined4 *)(param_4 + 0x1c));
    }
    iVar4 = 1;
  }
  else {
    iVar4 = 0;
  }
  return iVar4;
}

