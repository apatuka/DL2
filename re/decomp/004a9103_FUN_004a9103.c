// FUN_004a9103 @ 004a9103 size=219 sig=undefined FUN_004a9103() cc=unknown
// callers: FUN_004a95c1,FUN_004a94c7,FUN_004a7df4,FUN_004a91de,FUN_004a9335,FUN_004a9956,FUN_004a9828
// callees: __assertfail
// strings: \"XXTYPE.CPP\"|\"tp1->tpName\"|\"tp2->tpName\"

undefined4 FUN_004a9103(int *param_1,int *param_2)

{
  char cVar1;
  char cVar2;
  undefined4 uVar3;
  char *pcVar4;
  char *pcVar5;
  
  if (param_1 == (int *)0x0) {
    __assertfail(&DAT_0051f9e3,s_XXTYPE_CPP_0051f9e7,0x104);
  }
  if (param_2 == (int *)0x0) {
    __assertfail(&DAT_0051f9f2,s_XXTYPE_CPP_0051f9f6,0x105);
  }
  if (param_2 == param_1) {
    uVar3 = 1;
  }
  else if (((short)param_1[1] == (short)param_2[1]) && (*param_1 == *param_2)) {
    if (((*(ushort *)(param_1 + 1) | *(ushort *)(param_2 + 1)) & 0x80) == 0) {
      pcVar5 = (char *)((uint)*(ushort *)((int)param_1 + 6) + (int)param_1);
      if (*(short *)((int)param_1 + 6) == 0) {
        __assertfail(s_tp1_>tpName_0051fa01,s_XXTYPE_CPP_0051fa0d,0x11d);
      }
      pcVar4 = (char *)((uint)*(ushort *)((int)param_2 + 6) + (int)param_2);
      if (*(short *)((int)param_2 + 6) == 0) {
        __assertfail(s_tp2_>tpName_0051fa18,s_XXTYPE_CPP_0051fa24,0x11e);
      }
      do {
        cVar1 = *pcVar5;
        cVar2 = *pcVar4;
        pcVar4 = pcVar4 + 1;
        pcVar5 = pcVar5 + 1;
        if (cVar2 != cVar1) {
          return 0;
        }
      } while (cVar1 != '\0');
      uVar3 = 1;
    }
    else {
      uVar3 = 0;
    }
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}

