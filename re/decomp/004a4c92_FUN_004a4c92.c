// FUN_004a4c92 @ 004a4c92 size=508 sig=undefined FUN_004a4c92() cc=unknown
// callers: FUN_004a4ffe
// callees: FUN_00498ba9,FUN_0048f774,FUN_0048fd38,FUN_0048fcc3,FUN_0048fade,FUN_004a4c60

undefined4 FUN_004a4c92(byte *param_1,undefined4 param_2)

{
  ushort uVar1;
  byte bVar2;
  char cVar3;
  undefined1 uVar4;
  undefined2 uVar5;
  int iVar6;
  undefined4 uVar7;
  uint uVar8;
  undefined1 *puVar9;
  
  FUN_0048f774(param_1,0xa3b,0);
  bVar2 = FUN_0048fd38(param_2);
  *param_1 = bVar2;
  bVar2 = FUN_0048fd38(param_2);
  param_1[1] = bVar2;
  bVar2 = FUN_0048fd38(param_2);
  param_1[2] = bVar2;
  uVar5 = FUN_0048fcc3(param_2);
  *(undefined2 *)(param_1 + 3) = uVar5;
  uVar5 = FUN_0048fcc3(param_2);
  *(undefined2 *)(param_1 + 5) = uVar5;
  bVar2 = FUN_0048fd38(param_2);
  param_1[7] = bVar2;
  uVar5 = FUN_0048fcc3(param_2);
  *(undefined2 *)(param_1 + 8) = uVar5;
  uVar5 = FUN_0048fcc3(param_2);
  *(undefined2 *)(param_1 + 10) = uVar5;
  uVar5 = FUN_0048fcc3(param_2);
  *(undefined2 *)(param_1 + 0xc) = uVar5;
  uVar5 = FUN_0048fcc3(param_2);
  *(undefined2 *)(param_1 + 0xe) = uVar5;
  bVar2 = FUN_0048fd38(param_2);
  param_1[0x10] = bVar2;
  bVar2 = FUN_0048fd38(param_2);
  param_1[0x11] = bVar2;
  if (*param_1 != 0) {
    iVar6 = FUN_00498ba9(*param_1);
    *(int *)(param_1 + 0x12) = iVar6;
    if (iVar6 == 0) {
      FUN_004a4c60(param_1);
      return 0xffffffff;
    }
    for (uVar1 = 0; uVar1 < *param_1; uVar1 = uVar1 + 1) {
      uVar4 = FUN_0048fd38(param_2);
      *(undefined1 *)(*(int *)(param_1 + 0x12) + (uint)uVar1) = uVar4;
    }
  }
  if (param_1[1] != 0) {
    iVar6 = FUN_00498ba9((uint)*(ushort *)(param_1 + 5) * 3);
    *(int *)(param_1 + 0x16) = iVar6;
    if (iVar6 == 0) {
      FUN_004a4c60(param_1);
      return 0xffffffff;
    }
    puVar9 = *(undefined1 **)(param_1 + 0x16);
    bVar2 = param_1[7];
    if ((byte)(bVar2 - 0xf) < 2) {
      for (uVar1 = 0; uVar1 < *(ushort *)(param_1 + 5); uVar1 = uVar1 + 1) {
        cVar3 = FUN_0048fd38(param_2);
        uVar8 = (uint)cVar3;
        cVar3 = FUN_0048fd38(param_2);
        uVar8 = uVar8 | (int)cVar3 << 8;
        *puVar9 = (char)(uVar8 << 3);
        puVar9[1] = (byte)(uVar8 >> 2) & 0xf8;
        puVar9[2] = (byte)(uVar8 >> 7) & 0xf8;
        puVar9 = puVar9 + 3;
      }
    }
    else if (bVar2 == 0x18) {
      for (uVar1 = 0; uVar1 < *(ushort *)(param_1 + 5); uVar1 = uVar1 + 1) {
        uVar4 = FUN_0048fd38(param_2);
        *puVar9 = uVar4;
        uVar4 = FUN_0048fd38(param_2);
        puVar9[1] = uVar4;
        uVar4 = FUN_0048fd38(param_2);
        puVar9[2] = uVar4;
        puVar9 = puVar9 + 3;
      }
    }
    else if (bVar2 == 0x20) {
      for (uVar1 = 0; uVar1 < *(ushort *)(param_1 + 5); uVar1 = uVar1 + 1) {
        uVar4 = FUN_0048fd38(param_2);
        *puVar9 = uVar4;
        uVar4 = FUN_0048fd38(param_2);
        puVar9[1] = uVar4;
        uVar4 = FUN_0048fd38(param_2);
        puVar9[2] = uVar4;
        puVar9 = puVar9 + 3;
        FUN_0048fd38(param_2);
      }
    }
    param_1[7] = 0x18;
  }
  uVar7 = FUN_0048fade(param_2,0,1);
  *(undefined4 *)(param_1 + 0xa37) = uVar7;
  return 0;
}

