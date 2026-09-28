// FUN_004b3400 @ 004b3400 size=60 sig=undefined FUN_004b3400() cc=unknown
// callers: FUN_004b3304,FUN_004b335c,FUN_004b3208,FUN_004b343c
// callees: FUN_004a9090

int FUN_004b3400(int param_1)

{
  int iVar1;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_28;
  
  FUN_004a9090();
  iVar1 = ((((param_1 - DAT_005217ec) + DAT_005217f0) - 1) / DAT_005217f0) * DAT_005217f0 +
          DAT_005217ec;
  *unaff_FS_OFFSET = local_28;
  return iVar1;
}

