// FUN_0045093c @ 0045093c size=484 sig=undefined FUN_0045093c() cc=unknown
// callers: FUN_00404cec,FUN_00403408,FUN_004046e8,FUN_0040350c,FUN_00403350,FUN_00407290,FUN_004755b4,FUN_004073e4,FUN_00475660,FUN_00450cf8,FUN_00477684,FUN_0041edd8,FUN_00450cb8,FUN_00404b68
// callees: FUN_004756c8,FUN_004776b8,FUN_00475624,strlen,FUN_004418ec
// strings: \"Custom Chat\"

void FUN_0045093c(int param_1,uint param_2,int param_3,char *param_4,undefined4 param_5,
                 undefined4 param_6,undefined4 param_7)

{
  char cVar1;
  bool bVar2;
  bool bVar3;
  undefined *puVar4;
  undefined4 *puVar5;
  char *pcVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  undefined4 *puVar10;
  char *pcVar11;
  char *pcVar12;
  
  puVar4 = PTR_DAT_004caccc;
  bVar3 = false;
  puVar5 = (undefined4 *)PTR_DAT_004caccc;
  if ((((DAT_0058f1fc == 0) || (DAT_0058f1f4 == DAT_004d5a58)) ||
      ((char)(&DAT_0059f161)[param_1 * 0x2d8] < '\x03')) || (DAT_004d8268 != 0)) {
    if ('\x02' < (char)(&DAT_0059f161)[param_1 * 0x2d8]) {
      bVar2 = false;
      iVar9 = 0;
      pcVar6 = &DAT_0059f161;
      do {
        if ((((1 << ((byte)iVar9 & 0x1f) & param_2) != 0) && (*pcVar6 != '\0')) &&
           (*pcVar6 < '\x03')) {
          bVar2 = true;
        }
        iVar9 = iVar9 + 1;
        pcVar6 = pcVar6 + 0x2d8;
      } while (iVar9 < 7);
      if (!bVar2) {
        return;
      }
    }
    puVar10 = (undefined4 *)(PTR_DAT_004caccc + 0x1c);
    if ((undefined4 *)0x5649c7 < puVar10) {
      puVar10 = &DAT_00564530;
    }
    if (puVar10 != (undefined4 *)PTR_DAT_004cacc8) {
      *(int *)PTR_DAT_004caccc = param_1;
      *(uint *)(puVar4 + 4) = param_2;
      *(int *)(puVar4 + 8) = param_3;
      *(char **)(puVar4 + 0xc) = param_4;
      *(undefined4 *)(puVar4 + 0x10) = param_5;
      *(undefined4 *)(puVar4 + 0x14) = param_6;
      *(undefined4 *)(puVar4 + 0x18) = param_7;
      if ((param_1 == DAT_0058f1f4) ||
         ((DAT_0058f1f4 == DAT_004d5a58 && ('\x02' < (char)(&DAT_0059f161)[param_1 * 0x2d8])))) {
        bVar3 = true;
      }
      puVar5 = puVar10;
      if ((bVar3) && (param_3 == -1)) {
        FUN_004776b8(param_1,param_2,param_4,param_5,param_6);
      }
      else if (param_3 == -2) {
        iVar9 = strlen(param_4);
        pcVar6 = (char *)FUN_004418ec(s_Custom_Chat_004ce842,iVar9 + 1);
        if (pcVar6 != (char *)0x0) {
          uVar7 = 0xffffffff;
          do {
            pcVar11 = param_4;
            if (uVar7 == 0) break;
            uVar7 = uVar7 - 1;
            pcVar11 = param_4 + 1;
            cVar1 = *param_4;
            param_4 = pcVar11;
          } while (cVar1 != '\0');
          uVar7 = ~uVar7;
          pcVar11 = pcVar11 + -uVar7;
          pcVar12 = pcVar6;
          for (uVar8 = uVar7 >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
            *(undefined4 *)pcVar12 = *(undefined4 *)pcVar11;
            pcVar11 = pcVar11 + 4;
            pcVar12 = pcVar12 + 4;
          }
          for (uVar7 = uVar7 & 3; uVar7 != 0; uVar7 = uVar7 - 1) {
            *pcVar12 = *pcVar11;
            pcVar11 = pcVar11 + 1;
            pcVar12 = pcVar12 + 1;
          }
          if (bVar3) {
            FUN_004756c8(param_1,param_2,pcVar6);
          }
        }
        *(char **)(PTR_DAT_004caccc + 0xc) = pcVar6;
      }
      else if (bVar3) {
        FUN_00475624(param_1,param_2,param_3,param_4);
      }
    }
  }
  PTR_DAT_004caccc = (undefined *)puVar5;
  return;
}

