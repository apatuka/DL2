// FUN_0046686c @ 0046686c size=364 sig=undefined FUN_0046686c() cc=unknown
// callers: FUN_004669d8
// callees: FUN_004ae5d8,FUN_00466358,FUN_0046c9d8
// strings: \"SBld2\"

int FUN_0046686c(int param_1)

{
  char cVar1;
  char cVar2;
  char *pcVar3;
  int iVar4;
  char cVar5;
  int iVar6;
  int iVar7;
  int local_10;
  
  pcVar3 = *(char **)(param_1 + 0x80 + *(char *)(param_1 + 0x74) * 4);
  cVar1 = *pcVar3;
  cVar2 = pcVar3[1];
  iVar7 = 0;
  local_10 = 0;
  do {
    iVar6 = iVar7 * 0x34 + param_1;
    *(char *)(iVar6 + 0x140) = (char)(iVar7 % 6);
    cVar5 = (char)(iVar7 / 6);
    *(char *)(iVar6 + 0x141) = cVar5;
    iVar4 = FUN_00466358((int)cVar1 << 5,(int)cVar2 << 5,(int)*(char *)(iVar6 + 0x140),(int)cVar5);
    if (iVar4 < 0xb) {
      if (DAT_004d5a88 == 0) {
        if (*(char *)(param_1 + 0x21) == '\x05') {
          iVar4 = FUN_004ae5d8();
          if (iVar4 % 0x24 == 0) {
            iVar4 = FUN_0046c9d8(10,&DAT_004d5120);
            *(undefined2 *)(iVar6 + 0x142) =
                 *(undefined2 *)(&DAT_004d5080 + iVar4 * 2 + *(char *)(param_1 + 0x21) * 0x14);
          }
          else {
            *(undefined2 *)(iVar6 + 0x142) = 5;
          }
        }
        else {
          iVar4 = FUN_004ae5d8();
          if (iVar4 % 0x48 == 0) {
            *(undefined2 *)(iVar6 + 0x142) = 5;
          }
          else {
            iVar4 = FUN_0046c9d8(10,&DAT_004d5120);
            *(undefined2 *)(iVar6 + 0x142) =
                 *(undefined2 *)(&DAT_004d5080 + iVar4 * 2 + *(char *)(param_1 + 0x21) * 0x14);
          }
        }
      }
      local_10 = local_10 + 1;
    }
    else {
      *(undefined2 *)(iVar6 + 0x142) = 0xff;
    }
    if (DAT_004d5a88 == 0) {
      if ((*(short *)(iVar6 + 0x142) != 0xff) && (*(short *)(iVar6 + 0x142) != 5)) {
        iVar4 = FUN_0046c9d8(0x10,s_SBld2_004d5125);
        if (iVar4 == 0) {
          *(undefined1 *)(iVar6 + 0x144) = *(undefined1 *)(*(short *)(iVar6 + 0x142) * 4 + 0x4d5020)
          ;
          goto LAB_004669c2;
        }
      }
      *(undefined1 *)(iVar6 + 0x144) = 0;
    }
LAB_004669c2:
    iVar7 = iVar7 + 1;
    if (0x23 < iVar7) {
      return local_10;
    }
  } while( true );
}

