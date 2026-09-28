// FUN_00480d78 @ 00480d78 size=799 sig=undefined FUN_00480d78() cc=unknown
// callers: FUN_004812f4,FUN_00481098,FUN_00449dec
// callees: FUN_00480be0,FUN_00445270,FUN_0047ee04,FUN_0044d1a4,FUN_00486798,FUN_00486860,FUN_00444f20,FUN_00444b74,FUN_0047f440,FUN_0046c3fc,FUN_0047e2fc,FUN_00444e88,FUN_0046dc5c

void FUN_00480d78(void)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined1 *puVar7;
  int iVar8;
  int local_160;
  int local_15c;
  undefined1 local_158 [4];
  int local_154;
  int local_150;
  int local_14c;
  int local_148;
  int local_144;
  int local_140;
  int local_13c;
  int *local_138;
  undefined1 local_134 [2];
  undefined2 local_132;
  char local_130;
  undefined1 local_12f;
  undefined1 local_12e;
  undefined2 local_12c;
  short local_120;
  undefined4 local_11c [67];
  
  local_150 = DAT_00657de0;
  if ((*(char *)(DAT_00657de0 + 0x66 + DAT_0058f1f4) == '\x04') || (DAT_004d5aa0 != '\0')) {
    local_14c = 1;
  }
  else {
    local_14c = 0;
  }
  FUN_00444e88();
  DAT_0065e028 = 0;
  if (local_14c == 0) {
    local_154 = (int)*(char *)(local_150 + 0x36);
  }
  else {
    FUN_0046c3fc(local_150,local_158,&local_154);
  }
  local_148 = 0;
  local_138 = &DAT_004dcd00;
  do {
    iVar2 = *local_138;
    iVar8 = iVar2 * 0x34 + local_150;
    local_144 = *(int *)(&DAT_004dcc2c + iVar2 * 4) * 100;
    puVar7 = *(undefined1 **)(iVar8 + 0x154);
    if (puVar7 == (undefined1 *)0x0) {
LAB_00480e54:
      FUN_0047ee04(iVar2 % 6,iVar2 / 6,&local_160,&local_15c);
      if (local_14c == 0) {
        cVar1 = *(char *)(iVar8 + 0x15a);
        if (cVar1 == '\0') {
          puVar7 = (undefined1 *)0x0;
        }
        else {
          local_132 = 2;
          local_130 = cVar1;
          local_12f = (&DAT_004f9dc3)[cVar1 * 0x32];
          local_12e = *(undefined1 *)(iVar8 + 0x159);
          puVar4 = (undefined4 *)(iVar8 + 0x15e);
          local_12c = *(undefined2 *)(local_150 + 0x1a);
          local_120 = (short)*(char *)(iVar8 + 0x15b);
          iVar3 = 0;
          puVar6 = local_11c;
          do {
            *puVar6 = *puVar4;
            iVar3 = iVar3 + 1;
            puVar6 = puVar6 + 1;
            puVar4 = puVar4 + 1;
          } while (iVar3 < 5);
          puVar7 = local_134;
          if ((&DAT_004f9dc5)[cVar1 * 0x32] == '\x02') {
            local_160 = local_160 + -100;
          }
        }
      }
      if ((puVar7 != (undefined1 *)0x0) && (puVar7[4] != '\0')) {
        if ((&DAT_004f9dc5)[(char)puVar7[4] * 0x32] == '\x02') {
          local_144 = local_144 + 100;
        }
        if ((DAT_004dccbc == 0) && ((puVar7[2] & 4) != 0)) {
          if (*(short *)(puVar7 + 0x14) == 0) {
            iVar3 = (int)(short)(&DAT_004f9dc0)[(char)puVar7[4] * 0x19] + (int)(char)puVar7[6];
          }
          else {
            iVar3 = FUN_0047f440(puVar7);
          }
          local_140 = 0;
          local_13c = 0;
          if ((*(ushort *)(iVar8 + 0x142) & 0xf00) == 0x200) {
            iVar5 = FUN_0044d1a4(local_150,0x14,0);
            FUN_0047e2fc(&local_140,&local_13c,iVar5 - iVar2);
          }
          iVar3 = FUN_00444f20(iVar3,local_160 + local_140 + 0x32,local_15c + local_13c + 0x32,0);
          if (iVar3 != 0) {
            FUN_00444b74(iVar3,local_144 + 0x4c);
          }
        }
        if ((local_154 == 0) || (puVar7[5] != '\x11')) {
          FUN_00480be0(puVar7,local_144 + 99,local_160 + 0x32,local_15c + 0x2e,0);
        }
        else {
          iVar3 = FUN_00480be0(puVar7,local_144 + 99,local_160 + 0x32,local_15c + 0x2e,local_154);
          local_154 = local_154 - iVar3;
        }
      }
      if (((*(char *)(iVar8 + 0x150) != '\0') && (local_14c != 0)) &&
         (*(short *)(local_150 + 0x30) != 0)) {
        FUN_00486798(iVar2);
      }
    }
    else {
      iVar3 = FUN_0046dc5c(local_150);
      if ((iVar3 != 0) || ((puVar7[4] != '.' && (puVar7[4] != '/')))) goto LAB_00480e54;
    }
    local_148 = local_148 + 1;
    local_138 = local_138 + 1;
    if (0x23 < local_148) {
      if (local_14c != 0) {
        FUN_00486860();
      }
      FUN_00445270(1);
      return;
    }
  } while( true );
}

