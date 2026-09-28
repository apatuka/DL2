// FUN_004589b0 @ 004589b0 size=106 sig=undefined FUN_004589b0() cc=unknown
// callers: FUN_00458a5c,LoadSmacker
// callees: sprintf,GetVersionExA
// strings: \"Windows 3.1 and Win32s\"|\"Windows 95?\"|\"Windows NT\"|\"%s version %d.%d build %d\\n%s\"

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined * FUN_004589b0(void)

{
  char *unaff_EBX;
  
  _DAT_00583b88 = 0x94;
  GetVersionExA((LPOSVERSIONINFOA)&DAT_00583b88);
  if (DAT_00583b98 == 0) {
    unaff_EBX = s_Windows_3_1_and_Win32s_004d196e;
  }
  if (DAT_00583b98 == 1) {
    unaff_EBX = s_Windows_95__004d1985;
  }
  if (DAT_00583b98 == 2) {
    unaff_EBX = s_Windows_NT_004d1991;
  }
  sprintf(&DAT_00583c2c,s__s_version__d__d_build__d__s_004d199c,unaff_EBX,DAT_00583b8c,DAT_00583b90,
          DAT_00583b94,&DAT_00583b9c);
  return &DAT_00583c2c;
}

