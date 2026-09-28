// FUN_0045b304 @ 0045b304 size=323 sig=undefined FUN_0045b304() cc=unknown
// callers: FUN_0043baf4,FUN_0043be98
// callees: FUN_00458ed8,GetCursorPos,FUN_00482f94,FUN_00475a60,sprintf,FUN_0046e6b8,FUN_00449f5c,FUN_004590f0,MapWindowPoints,FUN_0042836c,FUN_00449dec
// strings: \"Demolish all buildings in territory %s?\"|\"Oolan's Advice\"|\"Sorry.  You cannot demolish buildings in territories you do not own.  Nice try, though.\"

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0045b304(void)

{
  int iVar1;
  int iVar2;
  undefined *puVar3;
  int *piVar4;
  tagPOINT local_dc;
  undefined1 local_d4 [200];
  
  GetCursorPos(&local_dc);
  MapWindowPoints((HWND)0x0,DAT_004d5974,&local_dc,1);
  iVar1 = DAT_004c5b50;
  puVar3 = &DAT_005a43d0 + DAT_004c5b50 * 0xadc;
  if ((DAT_004d5aa0 == '\0') && ((&DAT_005a4436)[DAT_0058f1f4 + DAT_004c5b50 * 0xadc] != '\x04')) {
    FUN_0042836c(PTR_s_Oolan_s_Advice_00508fa4,PTR_s_Sorry__You_cannot_demolish_build_00509698,4,0,9
                );
  }
  else if (DAT_004d59b4 == 0) {
    sprintf(local_d4,PTR_s_Demolish_all_buildings_in_territ_00509770,puVar3);
    iVar2 = FUN_0042836c(PTR_s_Oolan_s_Advice_00508fa4,local_d4,0x18,0,4);
    if (iVar2 == 1) {
      iVar2 = 0;
      piVar4 = &DAT_005a4524 + iVar1 * 0x2b7;
      do {
        if ((*piVar4 != 0) && (*(char *)(*piVar4 + 5) != '\v')) {
          FUN_00475a60(puVar3,iVar2,0);
        }
        iVar2 = iVar2 + 1;
        piVar4 = piVar4 + 0xd;
      } while (iVar2 < 0x24);
    }
    FUN_00482f94(PTR_DAT_004d5988);
    if (DAT_004d5aa0 != '\0') {
      FUN_0046e6b8(puVar3);
    }
    FUN_00449dec();
    FUN_00449f5c();
  }
  else {
    DAT_004d1c7c = 1;
    FUN_004590f0(DAT_004d5974,*(undefined4 *)(PTR_DAT_004d0360 + 8),local_dc.x,local_dc.y,
                 (int)*(short *)(PTR_DAT_004d0360 + 4),(int)*(short *)(PTR_DAT_004d0360 + 6),0,
                 FUN_0045b094);
    FUN_00458ed8();
    _DAT_004c5b6c = 1;
  }
  return;
}

