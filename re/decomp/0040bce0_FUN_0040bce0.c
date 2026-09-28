// FUN_0040bce0 @ 0040bce0 size=290 sig=undefined FUN_0040bce0() cc=unknown
// callers: 
// callees: 

void FUN_0040bce0(int param_1)

{
  bool bVar1;
  short *psVar2;
  short *psVar3;
  undefined4 *puVar4;
  int iVar5;
  int iVar6;
  int local_c;
  
  for (psVar2 = &DAT_00645370; psVar2 < &DAT_00651cb0; psVar2 = psVar2 + 0x2e) {
    if (((char)psVar2[3] != '\0') && ((char)psVar2[4] == param_1)) {
      if (psVar2[0x1b] == 0) {
        iVar5 = 0;
        do {
          iVar6 = 0;
          psVar3 = &DAT_005225a8 + iVar5 * 0x62 + param_1 * 0x1324;
          puVar4 = &DAT_005225c8 + iVar5 * 0x31 + param_1 * 0x992;
          do {
            if ((psVar2 == (short *)*puVar4) || (*psVar3 == *psVar2)) {
              *puVar4 = 0;
              *psVar3 = 0;
            }
            iVar6 = iVar6 + 1;
            psVar3 = psVar3 + 1;
            puVar4 = puVar4 + 1;
          } while (iVar6 < 0x10);
          iVar5 = iVar5 + 1;
        } while (iVar5 < 0x32);
      }
      else {
        bVar1 = false;
        local_c = 0;
        do {
          iVar5 = 0;
          psVar3 = &DAT_005225a8 + local_c * 0x62 + param_1 * 0x1324;
          puVar4 = &DAT_005225c8 + local_c * 0x31 + param_1 * 0x992;
          do {
            if ((psVar2 == (short *)*puVar4) || (*psVar3 == *psVar2)) {
              if (((int)psVar2[0x1b] != local_c + 1) || (bVar1)) {
                *puVar4 = 0;
                *psVar3 = 0;
              }
              else {
                bVar1 = true;
              }
            }
            iVar5 = iVar5 + 1;
            psVar3 = psVar3 + 1;
            puVar4 = puVar4 + 1;
          } while (iVar5 < 0x10);
          local_c = local_c + 1;
        } while (local_c < 0x32);
        if (!bVar1) {
          psVar2[0x1b] = 0;
        }
      }
    }
  }
  return;
}

