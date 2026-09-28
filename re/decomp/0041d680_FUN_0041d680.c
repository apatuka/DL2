// FUN_0041d680 @ 0041d680 size=141 sig=undefined FUN_0041d680() cc=unknown
// callers: CheckBuilding,FUN_0041d414
// callees: FUN_00476238,FUN_0049eb44

void FUN_0041d680(void)

{
  *(byte *)(DAT_0053b84c + 0x9ae) =
       *(byte *)(DAT_0053b84c + 0x9ae) ^
       '\x01' << ((byte)*(undefined4 *)(&DAT_004f9de6 + *(char *)(DAT_0053b850 + 4) * 0x32) & 0x1f);
  if ((1 << ((byte)*(undefined4 *)(&DAT_004f9de6 + *(char *)(DAT_0053b850 + 4) * 0x32) & 0x1f) &
      (int)*(char *)(DAT_0053b84c + 0x9ae)) == 0) {
    FUN_0049eb44(DAT_004b7758,0x1b,1,0xb,0,0);
  }
  else {
    FUN_0049eb44(DAT_004b7758,0x1b,1,0xb,1,0);
  }
  FUN_00476238(DAT_0053b84c);
  return;
}

