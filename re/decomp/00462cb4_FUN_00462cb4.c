// FUN_00462cb4 @ 00462cb4 size=186 sig=undefined FUN_00462cb4() cc=unknown
// callers: 
// callees: FUN_004ae5d8

undefined4 FUN_00462cb4(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined2 uVar4;
  char *pcVar5;
  undefined2 local_f0 [112];
  undefined2 *local_10;
  undefined *local_c;
  int local_8;
  
  local_8 = 0;
  local_10 = local_f0;
  local_c = &DAT_005a43d0 + param_1 * 0xadc;
  pcVar5 = &DAT_005a4f2a;
  for (iVar2 = 1; iVar1 = local_8, iVar2 <= DAT_004d5b18; iVar2 = iVar2 + 1) {
    if (((param_1 != iVar2) && (*pcVar5 != '\0')) &&
       ((1 << ((byte)iVar2 & 0xf) & *(ushort *)(local_c + (iVar2 >> 4) * 2 + 0x890)) != 0)) {
      *local_10 = (short)iVar2;
      local_8 = local_8 + 1;
      local_10 = local_10 + 1;
    }
    pcVar5 = pcVar5 + 0xadc;
  }
  if (local_8 == 0) {
    uVar3 = 0xffffffff;
  }
  else {
    if (local_8 == 0) {
      iVar2 = 0;
      uVar4 = 0;
    }
    else {
      iVar2 = FUN_004ae5d8();
      uVar4 = (undefined2)((uint)(iVar2 / iVar1) >> 0x10);
      iVar2 = iVar2 % iVar1;
    }
    uVar3 = CONCAT22(uVar4,local_f0[iVar2]);
  }
  return uVar3;
}

