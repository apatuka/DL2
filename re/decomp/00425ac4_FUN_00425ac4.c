// FUN_00425ac4 @ 00425ac4 size=253 sig=undefined FUN_00425ac4() cc=unknown
// callers: FUN_0042623c,FUN_00425f58,FUN_00425bc4
// callees: FUN_00425620,FUN_00425ef8,UpdateWindow,FUN_0042540c,LoadStringA,FUN_0048db5d,FUN_004503f4,FUN_0049eb44
// strings: \"NNOPENA\"

void FUN_00425ac4(int param_1)

{
  char *pcVar1;
  char *pcVar2;
  CHAR *pCVar3;
  int iVar4;
  char *pcVar5;
  bool bVar6;
  CHAR local_404;
  char local_403 [1023];
  
  FUN_0049eb44(DAT_004b7ce4,3,1,0x3c,0,2);
  LoadStringA(DAT_0058f19c,(int)*(short *)(param_1 + 6),&local_404,0x3ff);
  if (&stack0x00000000 == (undefined1 *)0x404) {
    FUN_0049eb44(DAT_004b7ce4,3,1,0x3c,1,2);
  }
  else {
    pcVar2 = &local_404;
    pcVar5 = s_NNOPENA_004b7d15;
    do {
      if (*pcVar2 != *pcVar5) goto LAB_00425b49;
      bVar6 = true;
      if (*pcVar2 == '\0') break;
      pcVar1 = pcVar2 + 1;
      if (*pcVar1 != pcVar5[1]) goto LAB_00425b49;
      pcVar2 = pcVar2 + 2;
      pcVar5 = pcVar5 + 2;
      bVar6 = *pcVar1 == '\0';
    } while (!bVar6);
    if (bVar6) {
      pCVar3 = (CHAR *)FUN_004503f4(8,0,0xffffffff);
    }
    else {
LAB_00425b49:
      pCVar3 = &local_404;
    }
    iVar4 = FUN_0042540c(pCVar3);
    if (iVar4 != 0) {
      FUN_00425ef8();
      if (DAT_004d5978 == (HWND)0x0) {
        UpdateWindow(DAT_004d5974);
      }
      else {
        UpdateWindow(DAT_004d5978);
      }
      DAT_004d59a4 = 1;
      FUN_0048db5d(0);
      DAT_004d59a4 = 0;
      FUN_00425620();
      DAT_004b7d0c = 1;
    }
  }
  return;
}

