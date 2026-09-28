// FUN_004b3168 @ 004b3168 size=157 sig=undefined FUN_004b3168() cc=unknown
// callers: 
// callees: FUN_004b2e50,FUN_004a9090,FUN_004a7b5d,FUN_004b2fd4,FUN_004a6e64
// strings: \"String reference out of range\"

void FUN_004b3168(int param_1,uint param_2)

{
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_30 [4];
  undefined2 local_20;
  int local_14;
  undefined1 local_c [4];
  undefined1 local_8 [4];
  
  FUN_004a9090();
  if (*(uint *)(param_1 + 8) <= param_2) {
    local_20 = 8;
    FUN_004b2e50(local_8,s_String_reference_out_of_range_00521854,0,FUN_004b2f97,1,0,0,0,local_30);
    local_14 = local_14 + 1;
    FUN_004a6e64(local_c,local_8);
    local_20 = 0x14;
    FUN_004b2fd4(local_8,2);
    local_20 = 8;
    local_14 = local_14 + 2;
    FUN_004a7b5d(&DAT_004b2d7a,local_c);
  }
  *unaff_FS_OFFSET = local_30[0];
  return;
}

