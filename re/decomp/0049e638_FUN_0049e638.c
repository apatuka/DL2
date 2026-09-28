// FUN_0049e638 @ 0049e638 size=825 sig=undefined FUN_0049e638() cc=unknown
// callers: FUN_004a2004
// callees: FUN_00498aab,FUN_00499a4f,FUN_0049b339

void FUN_0049e638(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  int iVar8;
  
  if (param_2 != 0) {
    iVar6 = DAT_0051bddc;
    if (*(int *)(param_1 + 0x3c) != 0) {
      iVar6 = *(int *)(param_1 + 0x3c);
    }
    if (iVar6 != 0) {
      iVar1 = FUN_00498aab(param_2,1);
      uVar7 = 1;
      if (*(short *)(iVar6 + 0x26) != 2) {
        uVar7 = 2;
      }
      if (*(int *)(iVar6 + 0xc) == 8) {
        if (*(int *)(iVar6 + 0x3c) != 0) {
          iVar2 = FUN_00498aab(*(undefined4 *)(iVar6 + 0x3c),1);
          *(byte *)(iVar2 + 0x407) = *(byte *)(iVar2 + 0x407) | 1;
          iVar5 = 0;
          do {
            iVar8 = (iVar5 + 0x10) * 4 + iVar1;
            uVar3 = FUN_00499a4f(*(undefined1 *)(iVar8 + 8),*(undefined1 *)(iVar8 + 9),
                                 *(undefined1 *)(iVar8 + 10),iVar2);
            *(uint *)(param_1 + 0x9c + iVar5 * 4) = uVar3 & 0xff;
            iVar8 = (iVar5 + 0x13) * 4 + iVar1;
            uVar3 = FUN_00499a4f(*(undefined1 *)(iVar8 + 8),*(undefined1 *)(iVar8 + 9),
                                 *(undefined1 *)(iVar8 + 10),iVar2);
            *(uint *)(param_1 + 0xa8 + iVar5 * 4) = uVar3 & 0xff;
            iVar8 = (iVar5 + 0x16) * 4 + iVar1;
            uVar3 = FUN_00499a4f(*(undefined1 *)(iVar8 + 8),*(undefined1 *)(iVar8 + 9),
                                 *(undefined1 *)(iVar8 + 10),iVar2);
            *(uint *)(param_1 + 0xb4 + iVar5 * 4) = uVar3 & 0xff;
            iVar8 = (iVar5 + 0x20) * 4 + iVar1;
            uVar3 = FUN_00499a4f(*(undefined1 *)(iVar8 + 8),*(undefined1 *)(iVar8 + 9),
                                 *(undefined1 *)(iVar8 + 10),iVar2);
            *(uint *)(param_1 + 0xf0 + iVar5 * 4) = uVar3 & 0xff;
            iVar8 = (iVar5 + 0x23) * 4 + iVar1;
            uVar3 = FUN_00499a4f(*(undefined1 *)(iVar8 + 8),*(undefined1 *)(iVar8 + 9),
                                 *(undefined1 *)(iVar8 + 10),iVar2);
            *(uint *)(param_1 + 0xfc + iVar5 * 4) = uVar3 & 0xff;
            iVar8 = (iVar5 + 0x26) * 4 + iVar1;
            uVar3 = FUN_00499a4f(*(undefined1 *)(iVar8 + 8),*(undefined1 *)(iVar8 + 9),
                                 *(undefined1 *)(iVar8 + 10),iVar2);
            *(uint *)(param_1 + 0x108 + iVar5 * 4) = uVar3 & 0xff;
            iVar8 = (iVar5 + 0x30) * 4 + iVar1;
            uVar3 = FUN_00499a4f(*(undefined1 *)(iVar8 + 8),*(undefined1 *)(iVar8 + 9),
                                 *(undefined1 *)(iVar8 + 10),iVar2);
            *(uint *)(param_1 + 0xc0 + iVar5 * 4) = uVar3 & 0xff;
            iVar8 = (iVar5 + 0x33) * 4 + iVar1;
            uVar3 = FUN_00499a4f(*(undefined1 *)(iVar8 + 8),*(undefined1 *)(iVar8 + 9),
                                 *(undefined1 *)(iVar8 + 10),iVar2);
            *(uint *)(param_1 + 0xcc + iVar5 * 4) = uVar3 & 0xff;
            iVar8 = (iVar5 + 0x36) * 4 + iVar1;
            uVar3 = FUN_00499a4f(*(undefined1 *)(iVar8 + 8),*(undefined1 *)(iVar8 + 9),
                                 *(undefined1 *)(iVar8 + 10),iVar2);
            *(uint *)(param_1 + 0xd8 + iVar5 * 4) = uVar3 & 0xff;
            uVar7 = *(undefined4 *)(param_1 + 0x9c + iVar5 * 4);
            *(undefined4 *)(param_1 + 0xe4 + iVar5 * 4) = uVar7;
            iVar8 = (iVar5 + 0x40) * 4 + iVar1;
            uVar3 = FUN_00499a4f(*(undefined1 *)(iVar8 + 8),
                                 CONCAT31((int3)((uint)uVar7 >> 8),*(undefined1 *)(iVar8 + 9)),
                                 *(undefined1 *)(iVar8 + 10),iVar2);
            *(uint *)(param_1 + 0x114 + iVar5 * 4) = uVar3 & 0xff;
            iVar5 = iVar5 + 1;
          } while (iVar5 < 3);
          FUN_00498aab(*(undefined4 *)(iVar6 + 0x3c),0);
        }
      }
      else {
        iVar6 = 0;
        do {
          uVar4 = FUN_0049b339(iVar1,uVar7,iVar6 + 0x10);
          *(undefined4 *)(param_1 + 0x9c + iVar6 * 4) = uVar4;
          uVar4 = FUN_0049b339(iVar1,uVar7,iVar6 + 0x13);
          *(undefined4 *)(param_1 + 0xa8 + iVar6 * 4) = uVar4;
          uVar4 = FUN_0049b339(iVar1,uVar7,iVar6 + 0x16);
          *(undefined4 *)(param_1 + 0xb4 + iVar6 * 4) = uVar4;
          uVar4 = FUN_0049b339(iVar1,uVar7,iVar6 + 0x20);
          *(undefined4 *)(param_1 + 0xf0 + iVar6 * 4) = uVar4;
          uVar4 = FUN_0049b339(iVar1,uVar7,iVar6 + 0x23);
          *(undefined4 *)(param_1 + 0xfc + iVar6 * 4) = uVar4;
          uVar4 = FUN_0049b339(iVar1,uVar7,iVar6 + 0x26);
          *(undefined4 *)(param_1 + 0x108 + iVar6 * 4) = uVar4;
          uVar4 = FUN_0049b339(iVar1,uVar7,iVar6 + 0x40);
          *(undefined4 *)(param_1 + 0x114 + iVar6 * 4) = uVar4;
          *(int *)(param_1 + 0xc0 + iVar6 * 4) = iVar6 + 0x30;
          *(int *)(param_1 + 0xcc + iVar6 * 4) = iVar6 + 0x33;
          *(int *)(param_1 + 0xd8 + iVar6 * 4) = iVar6 + 0x36;
          *(int *)(param_1 + 0xc0 + iVar6 * 4) = iVar6 + 0x30;
          *(int *)(param_1 + 0xe4 + iVar6 * 4) = iVar6 + 0x10;
          iVar6 = iVar6 + 1;
        } while (iVar6 < 3);
      }
      FUN_00498aab(param_2,0);
    }
  }
  return;
}

