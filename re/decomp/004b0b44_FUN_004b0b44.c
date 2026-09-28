// FUN_004b0b44 @ 004b0b44 size=766 sig=undefined FUN_004b0b44() cc=unknown
// callers: FUN_004ac7ec,FUN_0040cffc,FUN_004838fc,FUN_004ab648,FUN_0040cdfc,FUN_004b1b38,FUN_004100e0,FUN_004a748b,FUN_0041287c,FUN_00452594,FUN_004b1010,FUN_004b26cc,FUN_004ac974,FUN_0040d1a4,FUN_004b0248,FUN_004101d4,FUN_004114f0,FUN_0045ff94,FUN_00410558,FUN_004b1e64,FUN_004b02a8,FUN_004b3698,FUN_00412358,FUN_004b343c,FUN_004b2380,FUN_0045fae4,FUN_004a9b5c,FUN_00408b58,FUN_00408f58,FUN_00407d60,FUN_004b3208,FUN_004b3e08,FUN_00408288,FUN_004b1f50,FUN_004b1fb4,FUN_0040d338,FUN_004ac718,FUN_004b0b44,FUN_0041140c,FUN_004107ec
// callees: FUN_004b0418,FUN_004b0654,FUN_004b0408,FUN_004b0b44

/* WARNING: Restarted to delay deadcode elimination for space: ram */

uint * FUN_004b0b44(uint param_1)

{
  undefined *puVar1;
  uint *puVar2;
  int iVar3;
  int iVar4;
  uint *puVar5;
  int *piVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  
  if (param_1 == 0) {
    puVar2 = (uint *)0x0;
  }
  else {
    FUN_004b0408();
    if (param_1 < 0xc) {
      uVar7 = 0xc;
    }
    else {
      uVar7 = param_1 + 3 & 0xfffffffc;
    }
    if (DAT_005211f4 == 0) {
      FUN_004b0654(1);
    }
    puVar1 = PTR_DAT_00521204;
    puVar5 = (uint *)PTR_DAT_00521204;
    if (uVar7 < DAT_005211e0) {
      iVar3 = uVar7 * 2 + DAT_005211f4;
      puVar2 = *(uint **)(iVar3 + -8);
      if ((uint *)(iVar3 + -0xc) != puVar2) {
        *puVar2 = *puVar2 & 0xfffffffe;
        puVar5 = (uint *)((int)puVar2 + (*puVar2 & 0xfffffffc) + 4);
        *puVar5 = *puVar5 & 0xfffffffd;
        uVar7 = puVar2[1];
        *(uint *)(uVar7 + 8) = puVar2[2];
        *(uint *)(puVar2[2] + 4) = uVar7;
        FUN_004b0418();
        return puVar2 + 1;
      }
      if ((undefined4 *)PTR_DAT_00521204 == &DAT_005211f8) {
        puVar5 = (uint *)PTR_DAT_005211fc;
      }
      if ((undefined4 *)PTR_DAT_005211fc == &DAT_005211f8) {
        for (iVar3 = uVar7 * 2 + DAT_005211f4 + -4;
            (((iVar4 = iVar3, iVar3 == *(int *)(iVar3 + 4) &&
              (iVar4 = iVar3 + 8, iVar4 == *(int *)(iVar3 + 0xc))) &&
             ((iVar4 = iVar3 + 0x10, iVar4 == *(int *)(iVar3 + 0x14) &&
              ((((iVar4 = iVar3 + 0x18, iVar4 == *(int *)(iVar3 + 0x1c) &&
                 (iVar4 = iVar3 + 0x20, iVar4 == *(int *)(iVar3 + 0x24))) &&
                (iVar4 = iVar3 + 0x28, iVar4 == *(int *)(iVar3 + 0x2c))) &&
               ((iVar4 = iVar3 + 0x30, iVar4 == *(int *)(iVar3 + 0x34) &&
                (iVar4 = iVar3 + 0x38, iVar4 == *(int *)(iVar3 + 0x3c))))))))) &&
            (((iVar4 = iVar3 + 0x40, iVar4 == *(int *)(iVar3 + 0x44) &&
              ((iVar4 = iVar3 + 0x48, iVar4 == *(int *)(iVar3 + 0x4c) &&
               (iVar4 = iVar3 + 0x50, iVar4 == *(int *)(iVar3 + 0x54))))) &&
             (((iVar4 = iVar3 + 0x58, iVar4 == *(int *)(iVar3 + 0x5c) &&
               (((iVar4 = iVar3 + 0x60, iVar4 == *(int *)(iVar3 + 100) &&
                 (iVar4 = iVar3 + 0x68, iVar4 == *(int *)(iVar3 + 0x6c))) &&
                (iVar4 = iVar3 + 0x70, iVar4 == *(int *)(iVar3 + 0x74))))) &&
              (iVar4 = iVar3 + 0x78, iVar4 == *(int *)(iVar3 + 0x7c))))))); iVar3 = iVar3 + 0x80) {
        }
        puVar5 = (uint *)PTR_DAT_00521204;
        if (*(uint **)(iVar4 + 4) != (uint *)0x0) {
          puVar5 = *(uint **)(iVar4 + 4);
        }
      }
    }
    else {
      uVar9 = *(uint *)PTR_DAT_00521204;
      if (uVar9 < uVar7) {
        *(undefined4 *)PTR_DAT_00521204 = 0xfffffffd;
        puVar5 = *(uint **)(puVar1 + 4);
        while ((((((*puVar5 < uVar7 && (puVar5 = (uint *)puVar5[1], *puVar5 < uVar7)) &&
                  (puVar5 = (uint *)puVar5[1], *puVar5 < uVar7)) &&
                 (((puVar5 = (uint *)puVar5[1], *puVar5 < uVar7 &&
                   (puVar5 = (uint *)puVar5[1], *puVar5 < uVar7)) &&
                  ((puVar5 = (uint *)puVar5[1], *puVar5 < uVar7 &&
                   ((puVar5 = (uint *)puVar5[1], *puVar5 < uVar7 &&
                    (puVar5 = (uint *)puVar5[1], *puVar5 < uVar7)))))))) &&
                ((puVar5 = (uint *)puVar5[1], *puVar5 < uVar7 &&
                 (((puVar5 = (uint *)puVar5[1], *puVar5 < uVar7 &&
                   (puVar5 = (uint *)puVar5[1], *puVar5 < uVar7)) &&
                  (puVar5 = (uint *)puVar5[1], *puVar5 < uVar7)))))) &&
               (((puVar5 = (uint *)puVar5[1], *puVar5 < uVar7 &&
                 (puVar5 = (uint *)puVar5[1], *puVar5 < uVar7)) &&
                ((puVar5 = (uint *)puVar5[1], *puVar5 < uVar7 &&
                 (puVar5 = (uint *)puVar5[1], *puVar5 < uVar7))))))) {
          puVar5 = (uint *)puVar5[1];
        }
        *(uint *)PTR_DAT_00521204 = uVar9;
        if (puVar5 == (uint *)PTR_DAT_00521204) {
          puVar5 = &DAT_005211f8;
        }
      }
    }
    if (puVar5 == &DAT_005211f8) {
      iVar3 = FUN_004b0654(param_1 + 0x40);
      if (iVar3 == 0) {
        FUN_004b0418();
        puVar2 = (uint *)FUN_004b0b44(param_1);
      }
      else {
        FUN_004b0418();
        puVar2 = (uint *)0x0;
      }
    }
    else {
      uVar9 = *puVar5;
      uVar8 = (uVar9 & 0xfffffffc) - uVar7;
      if (uVar8 < 0x10) {
        *puVar5 = *puVar5 & 0xfffffffe;
        puVar2 = (uint *)((int)puVar5 + (*puVar5 & 0xfffffffc) + 4);
        *puVar2 = *puVar2 & 0xfffffffd;
        if (DAT_005211e0 <= (uVar9 & 0xfffffffc)) {
          PTR_DAT_00521204 = (undefined *)puVar5[1];
        }
        uVar7 = puVar5[1];
        puVar2 = puVar5 + 1;
        *(uint *)(uVar7 + 8) = puVar5[2];
        *(uint *)(puVar5[2] + 4) = uVar7;
        FUN_004b0418();
      }
      else {
        uVar9 = uVar8 - 4;
        *puVar5 = uVar7;
        piVar6 = (int *)((int)puVar5 + uVar7 + 4);
        *piVar6 = uVar8 - 3;
        *(uint *)((int)piVar6 + uVar9) = uVar8;
        if (uVar9 < DAT_005211e0) {
          iVar3 = uVar9 * 2 + DAT_005211f4;
          *(undefined4 *)((int)puVar5 + uVar7 + 8) = *(undefined4 *)(iVar3 + -8);
          *(int *)((int)puVar5 + uVar7 + 0xc) = iVar3 + -0xc;
          *(int **)(*(int *)((int)puVar5 + uVar7 + 8) + 8) = piVar6;
          *(int **)(iVar3 + -8) = piVar6;
          if (puVar5 == (uint *)PTR_DAT_00521204) {
            PTR_DAT_00521204 = (undefined *)puVar5[1];
          }
          uVar7 = puVar5[1];
          *(uint *)(uVar7 + 8) = puVar5[2];
          *(uint *)(puVar5[2] + 4) = uVar7;
        }
        else {
          uVar9 = puVar5[2];
          *(int **)(uVar9 + 4) = piVar6;
          *(uint *)((int)puVar5 + uVar7 + 0xc) = uVar9;
          uVar9 = puVar5[1];
          *(int **)(uVar9 + 8) = piVar6;
          *(uint *)((int)puVar5 + uVar7 + 8) = uVar9;
          PTR_DAT_00521204 = (undefined *)piVar6;
        }
        puVar2 = puVar5 + 1;
        FUN_004b0418();
      }
    }
  }
  return puVar2;
}

