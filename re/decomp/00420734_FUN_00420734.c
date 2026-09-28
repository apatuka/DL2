// FUN_00420734 @ 00420734 size=543 sig=undefined FUN_00420734() cc=unknown
// callers: CheckColonyAssistant,FUN_00421178,FUN_00421828
// callees: sprintf,FUN_0041ff98,FUN_0049eb44,FUN_0041ffd4
// strings: \"%s \\n %d / %d   %d\"

uint FUN_00420734(void)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  bool bVar6;
  uint *local_114;
  undefined1 local_110 [256];
  
  iVar4 = 0;
  puVar5 = &DAT_004c5650;
  local_114 = &DAT_004b7a20;
  do {
    uVar1 = *local_114;
    iVar2 = iVar4 * 2;
    if (*(int *)(&DAT_00564220 + uVar1 * 0x18) == 0) {
      FUN_0049eb44(DAT_004b7a14,iVar2 + 0xd,1,0x3c,0,1);
      uVar3 = FUN_0049eb44(DAT_004b7a14,iVar2 + 0xe,1,0x3c,0,1);
      *puVar5 = 0;
    }
    else {
      FUN_0049eb44(DAT_004b7a14,iVar2 + 0xd,1,0x3c,1,1);
      FUN_0049eb44(DAT_004b7a14,iVar2 + 0xe,1,0x3c,1,1);
      *puVar5 = 1;
      if ((int)uVar1 < 0xc) {
        uVar3 = uVar1;
        if (((uVar1 != 0xb) && (uVar3 = uVar1 - 2, 1 < uVar1)) &&
           (bVar6 = uVar3 < 9, uVar3 = uVar1 - 0xb, bVar6)) {
LAB_004207d3:
          sprintf(local_110,s__s__d____d__d_004b7abe,(&PTR_s__00509178)[uVar1],
                  (&DAT_00564224)[uVar1 * 6],
                  (&DAT_00564224)[uVar1 * 6] + *(int *)(&DAT_00564228 + uVar1 * 0x18) +
                  *(int *)(&DAT_0056422c + uVar1 * 0x18),
                  *(undefined4 *)(&DAT_00564230 + uVar1 * 0x18));
          FUN_0049eb44(DAT_004b7a14,iVar2 + 0xe,1,0xf,0,local_110);
          uVar3 = FUN_0049eb44(DAT_004b7a14,iVar2 + 0xe,1,0x42,0,(char)PTR_DAT_004d5988[2] + 0x3ea);
        }
      }
      else {
        if (uVar1 - 0xc < 10) goto LAB_004207d3;
        uVar3 = uVar1 - 0x1c;
        if (uVar1 - 0x17 < 5) {
          sprintf(local_110,s__s__d____d__d_004b7abe,(&PTR_s__00509178)[uVar1],
                  (&DAT_00564224)[uVar1 * 6],
                  (&DAT_00564224)[uVar1 * 6] + *(int *)(&DAT_00564228 + uVar1 * 0x18) +
                  *(int *)(&DAT_0056422c + uVar1 * 0x18),
                  *(undefined4 *)(&DAT_00564230 + uVar1 * 0x18));
          FUN_0049eb44(DAT_004b7a14,iVar2 + 0xe,1,0xf,0,local_110);
          if ((0x16 < DAT_0053b8ac) && (DAT_0053b8ac < 0x1c)) {
            FUN_0041ff98();
            FUN_0041ffd4();
          }
          uVar3 = FUN_0049eb44(DAT_004b7a14,iVar2 + 0xe,1,0x42,0,(char)PTR_DAT_004d5988[2] + 0x3f1);
        }
      }
    }
    iVar4 = iVar4 + 1;
    puVar5 = puVar5 + 8;
    local_114 = local_114 + 1;
    if (0x17 < iVar4) {
      return uVar3;
    }
  } while( true );
}

