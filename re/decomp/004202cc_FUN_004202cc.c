// FUN_004202cc @ 004202cc size=1128 sig=undefined FUN_004202cc() cc=unknown
// callers: FUN_00420aac
// callees: sprintf,FUN_0041ff98,FUN_0041fd38,FUN_0049eb44,FUN_0041ffd4
// strings: \"Iron -> Steel\"|\"%s \\n %d / %d   %d\"

void FUN_004202cc(void)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  bool bVar4;
  int iVar5;
  uint *puVar6;
  undefined4 *local_124;
  int local_120;
  int local_11c;
  int local_118;
  int local_114;
  undefined1 local_110 [256];
  
  iVar5 = 0;
  puVar6 = &DAT_004b7a20;
  bVar4 = false;
  local_124 = &DAT_004c5650;
  do {
    iVar1 = iVar5 + 0x10;
    uVar3 = *puVar6;
    iVar2 = iVar5 * 2;
    if (*(int *)(&DAT_00564220 + uVar3 * 0x18) == 0) {
      FUN_0049eb44(DAT_004b7a14,iVar5 * 2 + 0xd,1,0x3c,0,1);
      FUN_0049eb44(DAT_004b7a14,iVar5 * 2 + 0xe,1,0x3c,0,1);
      *local_124 = 0;
    }
    else if ((int)uVar3 < 0xc) {
      if (((uVar3 != 0xb) && (1 < uVar3)) && (uVar3 - 2 < 9)) {
LAB_00420340:
        if (!bVar4) {
          DAT_0053b8c4 = 0;
          FUN_0049eb44(DAT_004b7a14,6,1,0x3c,0,1);
          FUN_0049eb44(DAT_004b7a14,7,1,0x3c,0,1);
          FUN_0049eb44(DAT_004b7a14,8,1,0x3c,0,1);
          FUN_0049eb44(DAT_004b7a14,9,1,0x3c,0,1);
          FUN_0049eb44(DAT_004b7a14,0xb,1,0x3c,0,1);
          FUN_0049eb44(DAT_004b7a14,0xc,1,0x3c,0,1);
          bVar4 = true;
          FUN_0049eb44(DAT_004b7a14,iVar2 + 0xd,1,0xb,1,0);
          FUN_0041fd38(uVar3,0);
        }
        sprintf(local_110,s__s__d____d__d_004b7abe,(&PTR_s__00509178)[uVar3],
                (&DAT_00564224)[uVar3 * 6],
                (&DAT_00564224)[uVar3 * 6] + *(int *)(&DAT_00564228 + uVar3 * 0x18) +
                *(int *)(&DAT_0056422c + uVar3 * 0x18),*(undefined4 *)(&DAT_00564230 + uVar3 * 0x18)
               );
        iVar2 = iVar2 + 0xe;
        FUN_0049eb44(DAT_004b7a14,iVar2,1,0xf,0,local_110);
        FUN_0049eb44(DAT_004b7a14,iVar2,1,1,0,&local_120);
        iVar1 = iVar5 + 0x10;
        (&DAT_004c5458)[iVar1 * 8] = local_120;
        (&DAT_004c545c)[iVar1 * 8] = local_11c;
        (&DAT_004c5460)[iVar1 * 8] = local_118 - local_120;
        (&DAT_004c5464)[iVar1 * 8] = local_114 - local_11c;
        (&DAT_004c5450)[iVar1 * 8] = 1;
        FUN_0049eb44(DAT_004b7a14,iVar2,1,0x42,0,(char)PTR_DAT_004d5988[2] + 0x3ea);
      }
    }
    else {
      if (uVar3 - 0xc < 10) goto LAB_00420340;
      if (uVar3 - 0x17 < 5) {
        if (!bVar4) {
          bVar4 = true;
          DAT_0053b8c4 = 1;
          FUN_0049eb44(DAT_004b7a14,6,1,0x3c,1,1);
          FUN_0049eb44(DAT_004b7a14,7,1,0x3c,1,1);
          FUN_0049eb44(DAT_004b7a14,8,1,0x3c,1,1);
          FUN_0049eb44(DAT_004b7a14,9,1,0x3c,1,1);
          FUN_0049eb44(DAT_004b7a14,0xb,1,0x3c,1,1);
          FUN_0049eb44(DAT_004b7a14,0xc,1,0x3c,1,1);
          if ((1 << ((char)DAT_0053b8ac - 0x16U & 0x1f) & (int)*(char *)(DAT_0053b8b8 + 0x9ae)) == 0
             ) {
            FUN_0049eb44(DAT_004b7a14,7,1,0xb,0,0);
          }
          else {
            FUN_0049eb44(DAT_004b7a14,7,1,0xb,1,0);
          }
          FUN_0049eb44(DAT_004b7a14,iVar2 + 0xd,1,0xb,1,0);
          FUN_0041fd38(uVar3,0);
          FUN_0041ff98();
          FUN_0041ffd4();
        }
        sprintf(local_110,s__s__d____d__d_004b7abe,(&PTR_s__00509178)[uVar3],
                (&DAT_00564224)[uVar3 * 6],
                (&DAT_00564224)[uVar3 * 6] + *(int *)(&DAT_00564228 + uVar3 * 0x18) +
                *(int *)(&DAT_0056422c + uVar3 * 0x18),*(undefined4 *)(&DAT_00564230 + uVar3 * 0x18)
               );
        iVar2 = iVar2 + 0xe;
        FUN_0049eb44(DAT_004b7a14,iVar2,1,0xf,0,local_110);
        FUN_0049eb44(DAT_004b7a14,iVar2,1,1,0,&local_120);
        (&DAT_004c5458)[iVar1 * 8] = local_120;
        (&DAT_004c545c)[iVar1 * 8] = local_11c;
        (&DAT_004c5460)[iVar1 * 8] = local_118 - local_120;
        (&DAT_004c5464)[iVar1 * 8] = local_114 - local_11c;
        (&DAT_004c5450)[iVar1 * 8] = 1;
        FUN_0049eb44(DAT_004b7a14,iVar2,1,0x42,0,(char)PTR_DAT_004d5988[2] + 0x3f1);
      }
    }
    local_124 = local_124 + 8;
    iVar5 = iVar5 + 1;
    puVar6 = puVar6 + 1;
    if (0x17 < iVar5) {
      return;
    }
  } while( true );
}

