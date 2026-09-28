// FUN_004436cc @ 004436cc size=246 sig=undefined FUN_004436cc() cc=unknown
// callers: FUN_004437c4
// callees: FUN_0044d0ac,DetectsShrine,FUN_0044d1a4

void FUN_004436cc(int param_1)

{
  int iVar1;
  int iVar2;
  byte bVar3;
  undefined4 *puVar4;
  int iVar5;
  
  puVar4 = &DAT_005a4eac;
  do {
    if (&DAT_005a43d0 + DAT_004d5b18 * 0xadc < puVar4) {
      iVar5 = 0;
      do {
        iVar2 = iVar5 * 0x5c;
        if (((iVar2 != -0x645370) && ((&DAT_00645376)[iVar2] != '\0')) &&
           (param_1 == (char)(&DAT_00645378)[iVar2])) {
          iVar1 = (&DAT_006453a8)[iVar5 * 0x17];
          iVar2 = DetectsShrine(iVar1,(int)(char)(&DAT_00645376)[iVar2]);
          if (iVar2 == 100) {
            iVar2 = FUN_0044d1a4(iVar1,0xb,0);
            if (iVar2 == -1) {
              *(undefined4 *)(iVar1 + 0x978 + param_1 * 4) = 0;
            }
          }
        }
        iVar5 = iVar5 + 1;
      } while (iVar5 < 0x230);
      return;
    }
    bVar3 = (byte)param_1;
    if ((1 << (bVar3 & 0x1f) & puVar4[0x22c]) == 0) {
      iVar5 = FUN_0044d0ac(puVar4,0x2d);
      if ((iVar5 != 0) &&
         ((1 << (bVar3 & 0x1f) & (int)*(char *)((int)puVar4 + param_1 + 0x66)) != 0))
      goto LAB_0044370d;
    }
    else {
LAB_0044370d:
      puVar4[param_1 + 0x25e] = 1;
    }
    if (((*(char *)((int)puVar4 + 0x21) != '\0') && (*(char *)(puVar4 + 8) != -1)) &&
       ((1 << (bVar3 & 0x1f) & puVar4[0x22c]) == 0)) {
      puVar4[param_1 + 0x25e] = 0;
    }
    puVar4 = puVar4 + 0x2b7;
  } while( true );
}

