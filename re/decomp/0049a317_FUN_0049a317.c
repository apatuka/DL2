// FUN_0049a317 @ 0049a317 size=911 sig=undefined FUN_0049a317() cc=unknown
// callers: FUN_0049a6bb
// callees: FUN_004ae068,FUN_00499fd7,FUN_0049a13b

void FUN_0049a317(void)

{
  int iVar1;
  int iVar2;
  ushort uVar3;
  int iVar4;
  ushort *puVar5;
  ushort *puVar6;
  undefined1 local_40 [8];
  undefined1 local_38 [8];
  undefined1 local_30 [8];
  undefined1 local_28 [8];
  undefined1 local_20 [8];
  undefined1 local_18 [8];
  int local_10;
  int local_c;
  int local_8;
  
  puVar6 = &DAT_0065ee30;
  puVar5 = &DAT_0067ee30;
  if (DAT_0065e5a8 == 0x10) {
    if (DAT_0065e5ac == 2) {
      PTR_LAB_0051e264 = &LAB_0048eea4;
      local_8 = 0;
      do {
        local_c = 0;
        do {
          iVar4 = 0;
          do {
            FUN_00499fd7((double)((float)(local_8 << 3) * 0.00390625),
                         (double)((float)(local_c << 3) * 0.00390625),
                         (double)((float)(iVar4 << 3) * 0.00390625),local_30,local_38,local_40);
            iVar1 = FUN_004ae068();
            uVar3 = (ushort)((iVar1 >> 3) << 0xb);
            iVar1 = FUN_004ae068();
            uVar3 = uVar3 | (ushort)((iVar1 >> 3) << 6);
            iVar1 = FUN_004ae068();
            *puVar5 = uVar3 | (ushort)(iVar1 >> 2);
            puVar5 = puVar5 + 1;
            iVar4 = iVar4 + 1;
          } while (iVar4 < 0x20);
          local_c = local_c + 1;
        } while (local_c < 0x20);
        local_8 = local_8 + 1;
      } while (local_8 < 0x20);
      local_10 = 0;
      do {
        iVar4 = 0;
        do {
          iVar1 = 0;
          do {
            FUN_0049a13b((double)((float)(local_10 << 3) * 360.0 * 0.00390625),
                         (double)((float)(iVar4 << 3) * 0.00390625),
                         (double)((float)(iVar1 << 2) * 0.00390625),local_18,local_20,local_28);
            iVar2 = FUN_004ae068();
            uVar3 = (ushort)((iVar2 >> 3) << 10);
            iVar2 = FUN_004ae068();
            uVar3 = uVar3 | (ushort)((iVar2 >> 3) << 5);
            iVar2 = FUN_004ae068();
            *puVar6 = uVar3 | (ushort)(iVar2 >> 3);
            puVar6 = puVar6 + 1;
            iVar1 = iVar1 + 1;
          } while (iVar1 < 0x40);
          iVar4 = iVar4 + 1;
        } while (iVar4 < 0x20);
        local_10 = local_10 + 1;
      } while (local_10 < 0x20);
    }
    else {
      PTR_LAB_0051e264 = &LAB_0048f00d;
      local_8 = 0;
      do {
        local_c = 0;
        do {
          iVar4 = 0;
          do {
            FUN_00499fd7((double)((float)(local_8 << 3) * 0.00390625),
                         (double)((float)(local_c << 2) * 0.00390625),
                         (double)((float)(iVar4 << 3) * 0.00390625),local_30,local_38,local_40);
            iVar1 = FUN_004ae068();
            uVar3 = (ushort)((iVar1 >> 3) << 0xb);
            iVar1 = FUN_004ae068();
            uVar3 = uVar3 | (ushort)((iVar1 >> 3) << 6);
            iVar1 = FUN_004ae068();
            *puVar5 = uVar3 | (ushort)(iVar1 >> 2);
            puVar5 = puVar5 + 1;
            iVar4 = iVar4 + 1;
          } while (iVar4 < 0x20);
          local_c = local_c + 1;
        } while (local_c < 0x40);
        local_8 = local_8 + 1;
      } while (local_8 < 0x20);
      local_10 = 0;
      do {
        iVar4 = 0;
        do {
          iVar1 = 0;
          do {
            FUN_0049a13b((double)((float)(local_10 << 3) * 360.0 * 0.00390625),
                         (double)((float)(iVar4 << 3) * 0.00390625),
                         (double)((float)(iVar1 << 2) * 0.00390625),local_18,local_20,local_28);
            iVar2 = FUN_004ae068();
            uVar3 = (ushort)((iVar2 >> 3) << 0xb);
            iVar2 = FUN_004ae068();
            uVar3 = uVar3 | (ushort)((iVar2 >> 2) << 5);
            iVar2 = FUN_004ae068();
            *puVar6 = uVar3 | (ushort)(iVar2 >> 3);
            puVar6 = puVar6 + 1;
            iVar1 = iVar1 + 1;
          } while (iVar1 < 0x40);
          iVar4 = iVar4 + 1;
        } while (iVar4 < 0x20);
        local_10 = local_10 + 1;
      } while (local_10 < 0x20);
    }
  }
  return;
}

