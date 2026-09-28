// FUN_00450b4c @ 00450b4c size=235 sig=undefined FUN_00450b4c() cc=unknown
// callers: RunAITurns
// callees: FUN_004419c8,FUN_0048796c,FUN_00450670,FUN_004590d4,FUN_00450528,FUN_004505d0

void FUN_00450b4c(void)

{
  undefined *puVar1;
  int iVar2;
  
  if (DAT_004cacd0 == 0) {
    iVar2 = FUN_004590d4();
    if (iVar2 == 0) {
      iVar2 = FUN_0048796c();
      puVar1 = PTR_DAT_004cacc8;
      if ((iVar2 == 0) && (PTR_DAT_004cacc8 != PTR_DAT_004caccc)) {
        DAT_004cacd0 = 1;
        if ((&DAT_0059f161)[*(int *)PTR_DAT_004cacc8 * 0x2d8] != '\0') {
          if (*(int *)(PTR_DAT_004cacc8 + 8) == -2) {
            if (*(int *)(PTR_DAT_004cacc8 + 0xc) != 0) {
              FUN_004505d0(*(int *)PTR_DAT_004cacc8,*(undefined4 *)(PTR_DAT_004cacc8 + 4),
                           *(undefined4 *)(PTR_DAT_004cacc8 + 0xc));
              FUN_004419c8(*(undefined4 *)(puVar1 + 0xc));
            }
          }
          else if (*(int *)(PTR_DAT_004cacc8 + 8) == -1) {
            FUN_00450670(*(undefined4 *)PTR_DAT_004cacc8,*(undefined4 *)(PTR_DAT_004cacc8 + 4),
                         *(undefined4 *)(PTR_DAT_004cacc8 + 0xc),
                         *(undefined4 *)(PTR_DAT_004cacc8 + 0x10),
                         *(undefined4 *)(PTR_DAT_004cacc8 + 0x14));
          }
          else {
            FUN_00450528(*(undefined4 *)PTR_DAT_004cacc8,*(undefined4 *)(PTR_DAT_004cacc8 + 4),
                         *(undefined4 *)(PTR_DAT_004cacc8 + 8),
                         *(undefined4 *)(PTR_DAT_004cacc8 + 0xc));
          }
        }
        PTR_DAT_004cacc8 = PTR_DAT_004cacc8 + 0x1c;
        if ((undefined *)0x5649c7 < PTR_DAT_004cacc8) {
          PTR_DAT_004cacc8 = (undefined *)&DAT_00564530;
        }
        DAT_004cacd0 = 0;
      }
    }
  }
  return;
}

