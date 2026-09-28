// FUN_0041f198 @ 0041f198 size=301 sig=undefined FUN_0041f198() cc=unknown
// callers: FUN_0041f544,FUN_0041f384
// callees: FUN_004504e8,FUN_0041244c,FUN_00450508,free,FUN_0049eb44

void FUN_0041f198(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  undefined1 local_c [4];
  int local_8;
  
  iVar1 = FUN_0049eb44(DAT_004b7974,0x1e,1,0x18,0,0);
  iVar4 = 0;
  if (0 < iVar1) {
    do {
      FUN_0049eb44(DAT_004b7974,0x1e,1,0x27,0,0);
      iVar4 = iVar4 + 1;
    } while (iVar4 < iVar1);
  }
  if (param_1 != 0x24) {
    puVar2 = (undefined4 *)FUN_004504e8((int)(char)(&DAT_0059f162)[DAT_0058f1f4 * 0x2d8],param_1);
    local_8 = FUN_00450508((int)(char)(&DAT_0059f162)[DAT_0058f1f4 * 0x2d8],param_1);
    iVar1 = 0;
    if (0 < local_8) {
      do {
        iVar4 = FUN_0041244c(DAT_004d5a5c,*puVar2,local_c);
        if (iVar4 != 0) {
          iVar3 = FUN_0049eb44(DAT_004b7974,0x1e,1,0x26,0xffffffff,iVar4);
          FUN_0049eb44(DAT_004b7974,0x1e,1,0x25,iVar3 + -1,iVar1);
          free(iVar4);
        }
        iVar1 = iVar1 + 1;
        puVar2 = puVar2 + 1;
      } while (iVar1 < local_8);
    }
    FUN_0049eb44(DAT_004b7974,0x1e,1,7,0,FUN_0041f024);
    FUN_0049eb44(DAT_004b7974,0x1f,1,0x31,0x1e,1);
  }
  return;
}

