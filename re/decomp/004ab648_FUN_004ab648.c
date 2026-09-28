// FUN_004ab648 @ 004ab648 size=164 sig=undefined FUN_004ab648() cc=unknown
// callers: FUN_004aa518,FUN_004ac65c,FUN_004aa380,FUN_004aa948,FUN_004aa418,FUN_004aa0a8,fread,FUN_004ab3c8,FUN_004ac634,FUN_004ab744,FUN_004aa994,FUN_004aa48c,FUN_004a9d10,FUN_004a9c80,fclose
// callees: FUN_004b38b0,FUN_004b382c,FUN_004ab628,memset,FUN_004b0b44,FUN_004b3890,FUN_004ab638
// strings: \"allocating stream lock table\"|\"creating stream lock\"

void FUN_004ab648(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = (param_1 + -0x51fce4) / 0x18;
  if ((DAT_0069f560 == 0) || (*(int *)(DAT_0069f560 + iVar1 * 4) == 0)) {
    FUN_004ab628();
    if (DAT_0069f560 == 0) {
      iVar2 = DAT_00520194 << 2;
      DAT_0069f560 = FUN_004b0b44(iVar2);
      if (DAT_0069f560 == 0) {
        FUN_004b38b0(s_allocating_stream_lock_table_00520790);
      }
      memset(DAT_0069f560,0,iVar2);
    }
    if (*(int *)(DAT_0069f560 + iVar1 * 4) == 0) {
      FUN_004b382c(iVar1 * 4 + DAT_0069f560,s_creating_stream_lock_005207ad);
    }
    FUN_004ab638();
  }
  FUN_004b3890(*(undefined4 *)(DAT_0069f560 + iVar1 * 4));
  return;
}

