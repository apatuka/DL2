// FUN_0042d304 @ 0042d304 size=213 sig=undefined FUN_0042d304() cc=unknown
// callers: FUN_0042d3dc
// callees: FUN_00412d38,FUN_0048db5d,FUN_004a2cb5,FUN_00412f10,free,FUN_0042d04c

longlong FUN_0042d304(void)

{
  int iVar1;
  uint local_4;
  
  if (((DAT_00557c48 != 0) && (*(char *)(DAT_00557c48 + 0x3c) == '\0')) && (DAT_004bf910 == 0)) {
    DAT_004c5b78 = 0;
    DAT_004c5b70 = 0;
    DAT_004c5b7c = 0;
    DAT_004c5b74 = 0;
    FUN_00412f10(DAT_00557c48);
    FUN_00412d38(DAT_00557c48,*(undefined4 *)(DAT_004bf8fc + 0x3c));
    if (DAT_00557c4c != 0) {
      free(DAT_00557c4c);
      DAT_00557c4c = 0;
    }
  }
  DAT_004d59a4 = 1;
  DAT_0051b824 = 1;
  FUN_0048db5d(0);
  FUN_0042d04c();
  iVar1 = FUN_004a2cb5(DAT_004bf8fc,&local_4);
  if (((iVar1 == 0) && (local_4 != 0)) &&
     ((*(int *)(DAT_004bf8fc + 100) == 0 && (local_4 - 0x25 < 2)))) {
    DAT_004d59a4 = 0;
    return CONCAT44(local_4,local_4);
  }
  DAT_004d59a4 = 0;
  return (ulonglong)local_4 << 0x20;
}

