// FUN_00486964 @ 00486964 size=528 sig=undefined FUN_00486964() cc=unknown
// callers: WinMain,ChCht,FUN_004618e8,FUN_0044f3f0,FUN_00486e34
// callees: memset,FUN_004237d0,FUN_0044d1a4,FUN_0044d1e4,FUN_004412d4

void FUN_00486964(void)

{
  int iVar1;
  int iVar2;
  undefined *puVar3;
  int iVar4;
  char *pcVar5;
  int *local_14;
  
  memset(&DAT_0065e3cc,0,0x1c);
  memset(&DAT_0065e3b0,0,0x1c);
  memset(&DAT_0065e3e8,0,0x1c);
  DAT_0065e420 = 0;
  for (puVar3 = &DAT_005a43d0; puVar3 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
      puVar3 = puVar3 + 0xadc) {
    if ((puVar3[0x7e] != '\0') && ((puVar3[0x1d] & 1) == 0)) {
      if ((char)puVar3[0x20] != -1) {
        (&DAT_0065e3b0)[(char)puVar3[0x20]] = (&DAT_0065e3b0)[(char)puVar3[0x20]] + 1;
        iVar1 = FUN_0044d1e4(puVar3,9,0);
        if (iVar1 != -1) {
          (&DAT_0065e3cc)[(char)puVar3[0x20]] = (&DAT_0065e3cc)[(char)puVar3[0x20]] + 1;
        }
      }
      iVar1 = -1;
      while( true ) {
        iVar1 = FUN_0044d1e4(puVar3,0xb,iVar1 + 1);
        if (iVar1 == -1) break;
        if ((puVar3[0x20] != 0xff) &&
           ((1 << (puVar3[0x20] & 0x1f) & *(uint *)(puVar3 + 0x8b0)) != 0)) {
          iVar4 = 0;
          local_14 = &DAT_0065e3e8;
          pcVar5 = &DAT_0059f161;
          do {
            if ((iVar4 != (char)puVar3[0x20]) && (*pcVar5 != '\0')) {
              iVar2 = FUN_004412d4(iVar4,(int)(char)puVar3[0x20],0x10);
              if (iVar2 == 0) {
                if (((1 << ((byte)iVar4 & 0x1f) & *(uint *)(puVar3 + 0x8b0)) == 0) &&
                   (DAT_004d5b00 == '\x02')) {
                  FUN_004237d0(iVar4,0x4e,
                               (&PTR_s_ChCh_t_00509038)
                               [(char)(&DAT_0059f162)[(char)puVar3[0x20] * 0x2d8]],puVar3,0,0,
                               (int)(char)puVar3[0x20],0);
                }
              }
              else {
                *local_14 = *local_14 + 1;
                if (((1 << ((byte)iVar4 & 0x1f) & *(uint *)(puVar3 + 0x8b0)) == 0) &&
                   (DAT_004d5b00 == '\x02')) {
                  FUN_004237d0(iVar4,0x4d,
                               (&PTR_s_ChCh_t_00509038)
                               [(char)(&DAT_0059f162)[(char)puVar3[0x20] * 0x2d8]],puVar3,0,0,
                               (int)(char)puVar3[0x20],0);
                }
              }
            }
            iVar4 = iVar4 + 1;
            local_14 = local_14 + 1;
            pcVar5 = pcVar5 + 0x2d8;
          } while (iVar4 < 7);
          (&DAT_0065e3e8)[(char)puVar3[0x20]] = (&DAT_0065e3e8)[(char)puVar3[0x20]] + 1;
          *(undefined4 *)(puVar3 + 0x8b0) = 0xff;
        }
      }
      iVar1 = -1;
      while( true ) {
        iVar1 = FUN_0044d1a4(puVar3,0xb,iVar1 + 1);
        if (iVar1 == -1) break;
        DAT_0065e420 = DAT_0065e420 + 1;
      }
    }
  }
  return;
}

