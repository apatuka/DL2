// FUN_00484114 @ 00484114 size=309 sig=undefined FUN_00484114() cc=unknown
// callers: FUN_0046c7d4
// callees: FUN_00483d58,FUN_00483c3c,FUN_0040526c,FUN_00484080,FUN_004237d0,FUN_004412d4

void FUN_00484114(byte *param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined2 *puVar5;
  
  iVar4 = (int)(char)param_1[0x3e];
  puVar5 = &DAT_004fbbac + iVar4 * 0x19;
  (&DAT_004fbbb2)[iVar4 * 0x19 + (int)(char)*param_1] =
       (&DAT_004fbbb2)[iVar4 * 0x19 + (int)(char)*param_1] + (short)param_2;
  if ((param_2 != 0) || (param_1[0x3e] != 0)) {
    iVar2 = FUN_00483c3c(param_1,puVar5);
    if (iVar2 <= (short)(&DAT_004fbbb2)[iVar4 * 0x19 + (int)(char)*param_1]) {
      if ((1 << (*param_1 & 0x1f) & (int)DAT_004fbc74) != 0) {
        iVar2 = FUN_00483c3c(param_1,puVar5);
        FUN_00484080((int)(char)*param_1,8,
                     ((short)(&DAT_004fbbb2)[iVar4 * 0x19 + (int)(char)*param_1] - iVar2) / 5);
      }
      bVar1 = param_1[0x3e];
      if ((bVar1 != 0) &&
         ((1 << (*param_1 & 0x1f) & (int)(short)(&DAT_004fbbac)[(char)bVar1 * 0x19]) == 0)) {
        FUN_004237d0((int)(char)*param_1,0x36,
                     *(undefined4 *)((int)&PTR_s_Nothing_004fbbc0 + iVar4 * 0x32),0,0,0,
                     (int)(char)bVar1,0);
        iVar2 = 0;
        do {
          if (iVar2 != (char)*param_1) {
            iVar3 = FUN_004412d4((int)(char)*param_1,iVar2,8);
            if (iVar3 != 0) {
              FUN_004237d0(iVar2,0x38,*(undefined4 *)((int)&PTR_s_Nothing_004fbbc0 + iVar4 * 0x32),0
                           ,0,0,(int)(char)*param_1,0);
              FUN_00483d58(iVar2,puVar5);
              if ('\x02' < (char)param_1[1]) {
                FUN_0040526c((int)(char)*param_1,iVar2,0xfffffffc);
              }
            }
          }
          iVar2 = iVar2 + 1;
        } while (iVar2 < 7);
      }
      if (param_1[0x3e] != 0) {
        FUN_00483d58((int)(char)*param_1,puVar5);
      }
    }
  }
  return;
}

