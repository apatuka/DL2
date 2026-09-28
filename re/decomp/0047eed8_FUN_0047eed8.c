// FUN_0047eed8 @ 0047eed8 size=672 sig=undefined FUN_0047eed8() cc=unknown
// callers: FUN_004810cc
// callees: FUN_0049b3c9,FUN_0047e0e8,FUN_0047e054,FUN_0047ee4c,FUN_0047e394,FUN_0047e85c,FUN_0047e450,FUN_004935fc,FUN_0047e0bc,FUN_0047edbc

void FUN_0047eed8(void)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int local_328;
  int local_324;
  int local_320;
  int local_31c;
  int local_318;
  int local_314;
  int local_310;
  int local_30c;
  int local_308;
  int local_304;
  int local_300;
  undefined1 local_2fc [400];
  undefined1 local_16c [100];
  undefined1 local_108 [52];
  undefined1 local_d4 [196];
  
  iVar1 = DAT_004d5ab4;
  if (DAT_004dcc1c != 0) {
    if (DAT_004d5ab4 == 0) {
      if (*(int *)(DAT_0051bddc + 0xc) == 8) {
        FUN_004935fc(0,0,*(undefined4 *)(DAT_0051bddc + 4),*(undefined4 *)(DAT_0051bddc + 8),
                     *(uint *)(&DAT_004dce08 + *(char *)(DAT_00657de0 + 0x21) * 4) | 3);
      }
      else {
        uVar2 = FUN_0049b3c9(DAT_0058df44,
                             *(uint *)(&DAT_004dce08 + *(char *)(DAT_00657de0 + 0x21) * 4) | 3);
        FUN_004935fc(0,0,*(undefined4 *)(DAT_0051bddc + 4),*(undefined4 *)(DAT_0051bddc + 8),uVar2);
      }
    }
    else {
      FUN_004935fc(0,0,*(undefined4 *)(DAT_0051bddc + 4),*(undefined4 *)(DAT_0051bddc + 8),0);
      FUN_0047e054(DAT_00657ddc);
      FUN_0047e0bc();
      FUN_0047ee4c(-DAT_00657dd0,DAT_00657ddc - DAT_00657dd4,&local_320,&local_31c);
      FUN_0047edbc(local_320,local_31c,&local_328,&local_324);
      local_328 = local_328 + 0x32;
      local_310 = DAT_004dcc14 << 5;
      local_30c = DAT_004dcc18 << 5;
      for (; -0x32 < local_324; local_324 = local_324 + -0x19) {
        local_308 = local_320 * 5 + local_310 + -1;
        local_318 = local_328;
        local_314 = local_324;
        for (local_304 = local_31c * 5 + local_30c + -1;
            ((local_318 <= DAT_00657dd8 + 0x32 && (local_308 < DAT_0058f140 + -3)) &&
            (-1 < local_304)); local_304 = local_304 + -5) {
          if ((-2 < local_308) && (local_304 < DAT_0058f13c + -3)) {
            FUN_0047e394(local_308,local_304,local_108,local_d4);
            iVar5 = 4;
            do {
              iVar3 = 4;
              do {
                iVar4 = (iVar3 - iVar5) * 10 + local_318;
                local_300 = (iVar5 + iVar3) * 5 + local_314;
                FUN_0047e450(iVar3 + 1,iVar5 + 1,local_d4,local_2fc,iVar1);
                FUN_0047e85c(iVar3 + 1,iVar5 + 1,local_108,local_16c,iVar1);
                FUN_0047e0e8(iVar4,local_300,local_16c,local_2fc,10);
                iVar3 = iVar3 + -1;
              } while (-1 < iVar3);
              iVar5 = iVar5 + -1;
            } while (-1 < iVar5);
          }
          local_318 = local_318 + 100;
          local_308 = local_308 + 5;
        }
        if (local_328 < -0x32) {
          local_31c = local_31c + -1;
          local_328 = local_328 + 0x32;
        }
        else {
          local_320 = local_320 + -1;
          local_328 = local_328 + -0x32;
        }
      }
    }
  }
  return;
}

