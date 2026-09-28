// FUN_0046bc28 @ 0046bc28 size=187 sig=undefined FUN_0046bc28() cc=unknown
// callers: FUN_0046c7d4
// callees: FUN_0046b910,FUN_004237d0

void FUN_0046bc28(void)

{
  int iVar1;
  int *piVar2;
  undefined *puVar3;
  int local_14;
  int local_10 [2];
  
  for (puVar3 = &DAT_005a43d0; puVar3 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
      puVar3 = puVar3 + 0xadc) {
    local_14 = FUN_0046b910(puVar3);
    piVar2 = (int *)(puVar3 + 0x42);
    if (local_14 <= *(int *)(puVar3 + 0x42)) {
      piVar2 = &local_14;
    }
    iVar1 = *piVar2;
    *(int *)(puVar3 + 0x42) = *(int *)(puVar3 + 0x42) - (int)(short)iVar1;
    if (iVar1 < local_14) {
      local_10[0] = (iVar1 * 100) / local_14;
      local_10[1] = 0x32;
      if (local_10[0] < 0x32) {
        piVar2 = local_10 + 1;
      }
      else {
        piVar2 = local_10;
      }
      iVar1 = *piVar2;
      puVar3[0x35] = (char)iVar1;
      FUN_004237d0((int)(char)puVar3[0x20],0x33,puVar3,100 - (char)iVar1,0,0,
                   (int)*(short *)(puVar3 + 0x1a),0);
    }
    else {
      puVar3[0x35] = 100;
    }
  }
  return;
}

