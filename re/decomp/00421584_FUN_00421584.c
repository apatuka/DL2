// FUN_00421584 @ 00421584 size=431 sig=undefined FUN_00421584() cc=unknown
// callers: FUN_0044ae10
// callees: FUN_0041ff24,FUN_004590f0,FUN_00448878,FUN_0049eb44

void FUN_00421584(undefined4 param_1,undefined4 param_2)

{
  undefined *puVar1;
  uint uVar2;
  int iVar3;
  char cVar4;
  int iVar5;
  uint *puVar6;
  undefined4 local_c;
  
  puVar1 = (&PTR_DAT_004d078c)[(char)PTR_DAT_004d5988[2] * 3];
  if ((DAT_0053b8bc < 0x10) || (0x27 < DAT_0053b8bc)) {
    local_c = DAT_0053b8ac;
  }
  else {
    local_c = *(undefined4 *)(&DAT_004b79e0 + DAT_0053b8bc * 4);
  }
  iVar5 = 0;
  puVar6 = &DAT_004b7a20;
  do {
    uVar2 = *puVar6;
    iVar3 = iVar5 * 2;
    if (*(int *)(&DAT_00564220 + uVar2 * 0x18) != 0) {
      if ((int)uVar2 < 0xc) {
        if (((uVar2 != 0xb) && (1 < uVar2)) && (uVar2 - 2 < 9)) {
LAB_0042161e:
          cVar4 = FUN_00448878(DAT_0053b8b8,local_c,uVar2);
          if (cVar4 == '\0') {
            FUN_0049eb44(DAT_004b7a14,iVar3 + 0xe,1,0x42,0,(char)PTR_DAT_004d5988[2] + 0x3ea);
          }
          else {
            FUN_0049eb44(DAT_004b7a14,iVar3 + 0xe,1,0x42,0,(char)PTR_DAT_004d5988[2] + 0x1771);
          }
        }
      }
      else {
        if (uVar2 - 0xc < 10) goto LAB_0042161e;
        if (uVar2 - 0x17 < 5) {
          cVar4 = FUN_00448878(DAT_0053b8b8,local_c,uVar2);
          if (cVar4 == '\0') {
            FUN_0049eb44(DAT_004b7a14,iVar3 + 0xe,1,0x42,0,(char)PTR_DAT_004d5988[2] + 0x3f1);
          }
          else {
            FUN_0049eb44(DAT_004b7a14,iVar3 + 0xe,1,0x42,0,(char)PTR_DAT_004d5988[2] + 0x1b59);
          }
        }
      }
    }
    iVar5 = iVar5 + 1;
    puVar6 = puVar6 + 1;
    if (0x17 < iVar5) {
      FUN_0041ff24();
      FUN_004590f0(DAT_004d5974,*(undefined4 *)(puVar1 + 8),param_1,param_2,
                   (int)*(short *)(puVar1 + 4),(int)*(short *)(puVar1 + 6),0,FUN_00421178);
      return;
    }
  } while( true );
}

