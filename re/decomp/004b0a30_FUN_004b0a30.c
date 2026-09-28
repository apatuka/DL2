// FUN_004b0a30 @ 004b0a30 size=273 sig=undefined FUN_004b0a30() cc=unknown
// callers: FUN_0040cffc,FUN_0040cdfc,FUN_004100e0,FUN_004a74d5,FUN_004839bc,FUN_00452594,FUN_004b2380,FUN_004ac940,FUN_004b1010,FUN_004b1c4c,FUN_004b343c,FUN_004b0568,FUN_0040d1a4,FUN_00412584,FUN_004ac718,FUN_004101d4,FUN_00411534,fclose,FUN_0041161c,FUN_00410558,FUN_004526b0,free,FUN_004ab6ec,FUN_004b3698,FUN_00405760,FUN_0045fae4,FUN_004a9b5c,FUN_00408b58,FUN_00408f58,FUN_00407d60,FUN_0048394c,FUN_00408288,FUN_0040d338,FUN_004b1fb4,FUN_0041140c,FUN_004b32c0,FUN_004107ec
// callees: FUN_004b0408,FUN_004b092c,FUN_004b0418

void FUN_004b0a30(int param_1)

{
  int iVar1;
  uint *puVar2;
  uint uVar3;
  uint *puVar4;
  uint uVar5;
  
  if (param_1 != 0) {
    FUN_004b0408();
    puVar2 = (uint *)(param_1 + -4);
    uVar3 = *puVar2;
    if ((uVar3 & 2) == 0) {
      *puVar2 = *puVar2 | 1;
    }
    else {
      puVar2 = (uint *)((int)puVar2 - *(int *)(param_1 + -8));
      *puVar2 = *puVar2 + (uVar3 & 0xfffffffc) + 4;
      if (puVar2 == (uint *)PTR_DAT_00521204) {
        PTR_DAT_00521204 = *(undefined **)(PTR_DAT_00521204 + 4);
      }
      uVar3 = puVar2[1];
      *(uint *)(uVar3 + 8) = puVar2[2];
      *(uint *)(puVar2[2] + 4) = uVar3;
    }
    uVar3 = *puVar2 & 0xfffffffc;
    puVar4 = (uint *)((int)puVar2 + uVar3 + 4);
    if ((*puVar4 & 1) != 0) {
      *puVar2 = *puVar2 + (*puVar4 & 0xfffffffc) + 4;
      if (puVar4 == (uint *)PTR_DAT_00521204) {
        PTR_DAT_00521204 = *(undefined **)((int)puVar2 + uVar3 + 8);
      }
      iVar1 = *(int *)((int)puVar2 + uVar3 + 8);
      *(undefined4 *)(iVar1 + 8) = *(undefined4 *)((int)puVar2 + uVar3 + 0xc);
      *(int *)(*(int *)((int)puVar2 + uVar3 + 0xc) + 4) = iVar1;
    }
    puVar4 = (uint *)((int)puVar2 + (*puVar2 & 0xfffffffc) + 4);
    *puVar4 = *puVar4 | 2;
    uVar3 = *puVar2 & 0xfffffffc;
    if (uVar3 < DAT_005211e0) {
      uVar5 = (uVar3 * 2 + DAT_005211f4) - 0xc;
    }
    else {
      uVar5 = *(uint *)(PTR_DAT_00521204 + 4);
    }
    puVar2[1] = *(uint *)(uVar5 + 4);
    puVar2[2] = uVar5;
    *(uint **)(puVar2[1] + 8) = puVar2;
    *(uint **)(uVar5 + 4) = puVar2;
    *(uint *)((int)puVar2 + uVar3) = uVar3 + 4;
    if (*(int *)((int)puVar2 + (*puVar2 & 0xfffffffc) + 4) == 2) {
      uVar3 = DAT_005211e8;
      if (DAT_0052120c < DAT_00521208) {
        uVar3 = DAT_005211e4;
      }
      if (uVar3 < *puVar2) {
        FUN_004b092c(puVar2);
      }
    }
    FUN_004b0418();
  }
  return;
}

