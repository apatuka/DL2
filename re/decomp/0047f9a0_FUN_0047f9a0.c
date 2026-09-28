// FUN_0047f9a0 @ 0047f9a0 size=584 sig=undefined FUN_0047f9a0() cc=unknown
// callers: FUN_00480150
// callees: BlitSprite8

void FUN_0047f9a0(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  byte bVar1;
  uint in_EAX;
  uint uVar2;
  short *psVar3;
  int iVar4;
  uint uVar5;
  int unaff_ESI;
  
  uVar5 = *(short *)(DAT_00657de0 + 0x1a) + param_5;
  iVar4 = -1;
  if (3 < param_3) {
    if (param_3 != 4) {
      if (param_3 == 5) {
        iVar4 = 0x73;
        switch(*(undefined1 *)(DAT_00657de0 + 0x21)) {
        case 0:
        case 4:
        case 5:
          unaff_ESI = 0;
          break;
        case 1:
          unaff_ESI = 1;
          break;
        case 2:
          unaff_ESI = 3;
          break;
        case 3:
          unaff_ESI = 2;
        }
        in_EAX = ((int)uVar5 % 7 + (char)(&DAT_004dcdc0)[unaff_ESI + DAT_004d5b1c * 4] * 7) - 7;
      }
      goto LAB_0047fbd2;
    }
    goto LAB_0047fac9;
  }
  if (param_3 != 3) {
    if (param_3 == 0) goto LAB_0047fbd2;
    if (param_3 == 1) {
      bVar1 = *(byte *)(DAT_00657de0 + 0x21);
      if (bVar1 < 2) {
LAB_0047fa92:
        uVar2 = uVar5 & 0x80000001;
        if ((int)uVar2 < 0) {
          uVar2 = (uVar2 - 1 | 0xfffffffe) + 1;
        }
        in_EAX = uVar2 + 2;
      }
      else if (bVar1 == 2) {
        uVar2 = uVar5 & 0x80000001;
        if ((int)uVar2 < 0) {
          uVar2 = (uVar2 - 1 | 0xfffffffe) + 1;
        }
        in_EAX = uVar2 + 4;
      }
      else if (bVar1 == 3) {
        uVar2 = uVar5 & 0x80000001;
        if ((int)uVar2 < 0) {
          uVar2 = (uVar2 - 1 | 0xfffffffe) + 1;
        }
        in_EAX = uVar2 + 6;
      }
      else if (bVar1 == 4) goto LAB_0047fa92;
LAB_0047fac9:
      switch(DAT_004d5b1c) {
      case '\0':
        iVar4 = 0x78;
        break;
      case '\x01':
        iVar4 = 0x7e;
        break;
      case '\x02':
        iVar4 = 0x7c;
        break;
      case '\x03':
        iVar4 = 0x7a;
        break;
      case '\x04':
        iVar4 = 0x76;
        break;
      case '\x05':
        iVar4 = 0x80;
        break;
      case '\x06':
        iVar4 = 0x74;
      }
      if (param_3 == 4) {
        uVar5 = uVar5 & 0x80000003;
        if ((int)uVar5 < 0) {
          uVar5 = (uVar5 - 1 | 0xfffffffc) + 1;
        }
        in_EAX = uVar5 + 8;
      }
      goto LAB_0047fbd2;
    }
    if (param_3 != 2) goto LAB_0047fbd2;
    in_EAX = uVar5 & 0x80000001;
    if ((int)in_EAX < 0) {
      in_EAX = (in_EAX - 1 | 0xfffffffe) + 1;
    }
  }
  switch(DAT_004d5b1c) {
  case '\0':
    iVar4 = 0x79;
    break;
  case '\x01':
    iVar4 = 0x7f;
    break;
  case '\x02':
    iVar4 = 0x7d;
    break;
  case '\x03':
    iVar4 = 0x7b;
    break;
  case '\x04':
    iVar4 = 0x77;
    break;
  case '\x05':
    iVar4 = 0x81;
    break;
  case '\x06':
    iVar4 = 0x75;
  }
  if (param_3 == 3) {
    uVar5 = uVar5 & 0x80000001;
    if ((int)uVar5 < 0) {
      uVar5 = (uVar5 - 1 | 0xfffffffe) + 1;
    }
    in_EAX = uVar5 + 4;
  }
  if (param_4 == 0) {
    in_EAX = in_EAX + 2;
  }
LAB_0047fbd2:
  if (iVar4 != -1) {
    psVar3 = (short *)((int)(&PTR_DAT_004d02f4)[iVar4 * 3] + in_EAX * 8 * 2);
    if (*(int *)(psVar3 + 4) == 0) {
      psVar3 = (short *)(&PTR_DAT_004d02f4)[iVar4 * 3];
    }
    BlitSprite8(*(undefined4 *)(psVar3 + 4),*psVar3 + param_1 + 0x32,psVar3[1] + param_2 + 0x32,
                (int)psVar3[2],(int)psVar3[3],(int)psVar3[2],0);
  }
  return;
}

