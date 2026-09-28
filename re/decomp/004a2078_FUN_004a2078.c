// FUN_004a2078 @ 004a2078 size=448 sig=undefined FUN_004a2078() cc=unknown
// callers: FUN_004a421e,FUN_0043acd4,FUN_004a3329,FUN_004a322d,FUN_004a5ad9,FUN_00422344,FUN_0043e22c
// callees: FUN_004989de,FUN_0049a93f,GlobalUnlock,FUN_0049a8ed,FUN_0049f22b,FUN_0048e670,FUN_004a0f18,FUN_00498aab,FUN_0048c434,FUN_00499840,GlobalLock,FUN_004a10b3,FUN_0049aa64,FUN_0049551a,FUN_00491d38

void FUN_004a2078(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined1 local_1c [16];
  undefined4 local_c;
  undefined4 local_8;
  
  local_c = 0;
  if ((param_1 != 0) && (iVar2 = FUN_0049551a(DAT_0051e384,param_1), iVar2 != -1)) {
    FUN_0049a8ed();
    FUN_0049f22b(param_1,local_1c);
    iVar2 = FUN_0049aa64(local_1c);
    if (iVar2 != 0) {
      if (*(int *)(param_1 + 0x3c) != 0) {
        local_c = DAT_0051bddc;
        FUN_0048c434(*(undefined4 *)(param_1 + 0x3c));
      }
      if (*(int *)(param_1 + 0x50) != 0) {
        uVar3 = FUN_00498aab(*(undefined4 *)(param_1 + 0x50),1);
        local_8 = FUN_00491d38(uVar3);
      }
      if (((param_1 != 0) && (*(int *)(param_1 + 300) != 0)) && (**(int **)(param_1 + 300) != 0)) {
        for (puVar1 = *(undefined4 **)(*(int *)(param_1 + 300) + 4); puVar1 != (undefined4 *)0x0;
            puVar1 = (undefined4 *)*puVar1) {
          if (((*(byte *)(puVar1 + 10) & 0x10) == 0) && (puVar1[0x19] != 0)) {
            puVar4 = GlobalLock((HGLOBAL)puVar1[0x19]);
            FUN_00499840(*puVar4,puVar4[1]);
            FUN_0048e670(puVar4 + 4,puVar4[2],puVar4[3],0,DAT_0051c3c4,DAT_0051c3c0);
            GlobalUnlock((HGLOBAL)puVar1[0x19]);
            FUN_004989de(puVar1[0x19]);
            puVar1[0x19] = 0;
          }
        }
      }
      if (*(int *)(param_1 + 0x5c) == 0) {
        FUN_004a10b3(param_1,0);
      }
      else {
        iVar2 = (**(code **)(param_1 + 0x5c))(param_1,0,3,0);
        if (iVar2 == 0) {
          FUN_004a10b3(param_1,0);
        }
      }
      if (((param_1 != 0) && (*(int *)(param_1 + 300) != 0)) && (**(int **)(param_1 + 300) != 0)) {
        for (iVar2 = **(int **)(param_1 + 300); iVar2 != 0; iVar2 = *(int *)(iVar2 + 4)) {
          if ((*(byte *)(iVar2 + 0x28) & 0x10) == 0) {
            FUN_004a0f18(iVar2);
          }
        }
      }
      if (((param_1 != 0) && (*(int *)(param_1 + 300) != 0)) && (**(int **)(param_1 + 300) != 0)) {
        for (iVar2 = **(int **)(param_1 + 300); iVar2 != 0; iVar2 = *(int *)(iVar2 + 4)) {
          if ((*(byte *)(iVar2 + 0x28) & 0x10) != 0) {
            FUN_004a0f18(iVar2);
          }
        }
      }
      if (*(int *)(param_1 + 0x50) != 0) {
        FUN_00498aab(*(undefined4 *)(param_1 + 0x50),0);
        FUN_00491d38(local_8);
      }
      if (*(int *)(param_1 + 0x3c) != 0) {
        FUN_0048c434(local_c);
      }
    }
    FUN_0049a93f();
  }
  return;
}

