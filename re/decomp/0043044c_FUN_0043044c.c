// FUN_0043044c @ 0043044c size=1473 sig=undefined FUN_0043044c() cc=unknown
// callers: FUN_00430abc
// callees: FUN_004302e8,FUN_004302f4,FUN_0049eb44,FUN_00441128,FUN_004669d8,FUN_0042f950,FUN_0048db5d,FUN_004a2cb5,FUN_004ae26c,FUN_00426594

int FUN_0043044c(void)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  int *piVar5;
  int local_9c [5];
  undefined1 local_88 [128];
  
  DAT_004d59a4 = 1;
  DAT_0051b824 = 1;
  FUN_0048db5d(0);
  FUN_004302e8();
  iVar1 = FUN_004a2cb5(DAT_004c4294,local_9c);
  if (((iVar1 == 0) && (local_9c[0] != 0)) && (*(int *)(DAT_004c4294 + 100) == 0)) {
    switch(local_9c[0]) {
    case 3:
      DAT_004d5aec = 2;
      break;
    case 4:
      DAT_004d5aec = 3;
      break;
    case 5:
      DAT_004d5aec = 4;
      break;
    case 6:
      DAT_004d5aec = 5;
      break;
    case 7:
      DAT_004d5aec = 6;
      break;
    case 8:
      DAT_004d5aec = 7;
      break;
    case 9:
      DAT_004d5b00 = 0;
      FUN_0042f950();
      FUN_004302f4();
      break;
    case 10:
      DAT_004d5b00 = 1;
      FUN_0042f950();
      FUN_004302f4();
      break;
    case 0xb:
      DAT_004d5b00 = 2;
      FUN_0042f950();
      FUN_004302f4();
      break;
    case 0xc:
      DAT_004c428c = 0;
      DAT_004d5af8 = DAT_004c4274;
      break;
    case 0xd:
      DAT_004c428c = 1;
      DAT_004d5af8 = DAT_004c4278;
      break;
    case 0xe:
      DAT_004c428c = 2;
      DAT_004d5af8 = DAT_004c427c;
      break;
    case 0xf:
      DAT_004c4290 = 0;
      DAT_004d5afc = DAT_004c4280;
      break;
    case 0x10:
      DAT_004c4290 = 1;
      DAT_004d5afc = DAT_004c4284;
      break;
    case 0x11:
      DAT_004c4290 = 2;
      DAT_004d5afc = DAT_004c4288;
      break;
    case 0x12:
      DAT_004c4258 = 0;
      DAT_004d5af0 = DAT_004c425c;
      break;
    case 0x13:
      DAT_004c4258 = 1;
      DAT_004d5af0 = DAT_004c4260;
      break;
    case 0x14:
      DAT_004c4258 = 2;
      DAT_004d5af0 = DAT_004c4264;
      break;
    case 0x15:
      DAT_004c4258 = 3;
      DAT_004d5af0 = DAT_004c4268;
      break;
    case 0x16:
      DAT_004c4258 = 4;
      DAT_004d5af0 = DAT_004c426c;
      break;
    case 0x17:
      DAT_004d5b0c = 0;
      break;
    case 0x18:
      DAT_004d5b0c = 1;
      break;
    case 0x19:
      DAT_004d5b0c = 2;
      break;
    case 0x1a:
      DAT_004d5b0c = 3;
      break;
    case 0x1b:
      DAT_004d5b0c = 4;
      break;
    case 0x1c:
      DAT_004d5b04 = DAT_004d5b04 ^ 1;
      break;
    case 0x1d:
      DAT_004d5af4 = DAT_004d5af4 ^ 1;
      if ((DAT_004d5aa0 != '\0') && (DAT_004d5af4 == 0)) {
        iVar1 = 0;
        puVar3 = &DAT_0059f3da;
        do {
          iVar4 = 0;
          puVar2 = puVar3;
          do {
            iVar4 = iVar4 + 1;
            *puVar2 = 0;
            puVar2 = puVar2 + 1;
          } while (iVar4 < 7);
          iVar1 = iVar1 + 1;
          puVar3 = puVar3 + 0xb6;
        } while (iVar1 < 7);
      }
      break;
    case 0x1e:
      DAT_004d5b08 = DAT_004d5b08 ^ 1;
      break;
    case 0x1f:
      DAT_004d5a90 = DAT_004d5a90 ^ 1;
      break;
    case 0x20:
      DAT_004d5b34 = DAT_004d5b34 ^ 1;
      if (DAT_004d5b34 != 0) {
        DAT_004d5b2c = 0;
        FUN_0049eb44(DAT_004c4294,0x22,1,0xb,0,0);
        FUN_004302f4();
      }
      break;
    case 0x22:
      DAT_004d5b2c = DAT_004d5b2c ^ 1;
      if (DAT_004d5b2c != 0) {
        DAT_004d5b34 = 0;
        FUN_0049eb44(DAT_004c4294,0x20,1,0xb,0,0);
        FUN_004302f4();
      }
      break;
    case 0x28:
      DAT_004d5b3c = 0;
      break;
    case 0x29:
      DAT_004d5b3c = 1;
      break;
    case 0x2a:
      DAT_004d5b3c = 2;
      break;
    case 0x2b:
      FUN_00426594(&DAT_004d4d64);
      break;
    case 0x2c:
      if ((DAT_004d5aa0 != '\0') && (FUN_00441128(), DAT_00558c80 != DAT_004d5a90)) {
        FUN_004669d8(0);
      }
      FUN_0049eb44(DAT_004c4294,0x25,1,0xe,0x80,local_88);
      iVar1 = FUN_004ae26c(local_88);
      local_9c[1] = 0x3c0;
      if (iVar1 < 0x3c0) {
        piVar5 = &DAT_004d5b38;
      }
      else {
        piVar5 = local_9c + 1;
      }
      local_9c[2] = 3;
      if (*piVar5 < 4) {
        piVar5 = local_9c + 2;
      }
      else {
        piVar5 = &DAT_004d5b38;
      }
      DAT_004d5b38 = *piVar5;
      FUN_0049eb44(DAT_004c4294,0x27,1,0xe,0x80,local_88);
      iVar1 = FUN_004ae26c(local_88);
      local_9c[3] = 0x3c0;
      if (iVar1 < 0x3c0) {
        piVar5 = &DAT_004d5b30;
      }
      else {
        piVar5 = local_9c + 3;
      }
      local_9c[4] = 3;
      if (*piVar5 < 4) {
        piVar5 = local_9c + 4;
      }
      else {
        piVar5 = &DAT_004d5b30;
      }
      DAT_004d59a4 = 0;
      DAT_004d5b30 = *piVar5;
      return local_9c[0];
    case 0x2d:
      DAT_004d59a4 = 0;
      DAT_004d5a90 = DAT_00558c80;
      DAT_004d5aec = DAT_00558c88;
      DAT_004d5af0 = DAT_00558c94;
      DAT_004d5af4 = DAT_00558ca0;
      DAT_004d5af8 = DAT_00558c8c;
      DAT_004d5afc = DAT_00558c90;
      DAT_004d5b00 = DAT_00558c84;
      DAT_004d5b04 = DAT_00558c9c;
      DAT_004d5b08 = DAT_00558ca4;
      DAT_004d5b0c = DAT_00558c98;
      DAT_004d5b2c = DAT_00558ca8;
      DAT_004d5b30 = DAT_00558cb8;
      DAT_004d5b34 = DAT_00558cac;
      DAT_004d5b38 = DAT_00558cb4;
      DAT_004d5b3c = DAT_00558cb0;
      return local_9c[0];
    }
  }
  DAT_004d59a4 = 0;
  return 0;
}

