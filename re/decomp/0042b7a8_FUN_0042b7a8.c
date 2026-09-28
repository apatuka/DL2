// FUN_0042b7a8 @ 0042b7a8 size=198 sig=undefined FUN_0042b7a8() cc=unknown
// callers: FUN_0042b870
// callees: FUN_0042baa4,FUN_0049eb44

void FUN_0042b7a8(int param_1,int param_2)

{
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  if ((param_1 != DAT_004bda74) || (param_2 != DAT_004bda70)) {
    local_14 = 10000;
    local_10 = 10000;
    local_c = 0x28a0;
    local_8 = 0x28a0;
    FUN_0049eb44(DAT_004bda5c,
                 *(undefined4 *)(&DAT_004bda78 + DAT_004bda74 * 4 + DAT_004bda70 * 0x10),1,0xd,0,
                 &local_14);
    local_14 = 0x35;
    local_10 = 0x71;
    local_c = 0xc6;
    local_8 = 0x102;
    FUN_0049eb44(DAT_004bda5c,*(undefined4 *)(&DAT_004bda78 + param_1 * 4 + param_2 * 0x10),1,0xd,0,
                 &local_14);
    DAT_004bda74 = param_1;
    DAT_004bda70 = param_2;
    FUN_0042baa4();
  }
  return;
}

