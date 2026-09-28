// FUN_00432014 @ 00432014 size=248 sig=undefined FUN_00432014() cc=unknown
// callers: FUN_0043242c
// callees: FUN_0049eb44,sprintf,FUN_004382d0
// strings: \"%s %d\"

void FUN_00432014(void)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  undefined1 local_74 [80];
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  local_24 = 0;
  local_20 = 0x31304c55;
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  piVar2 = &DAT_00558cd4;
  for (iVar3 = 0; iVar3 < DAT_00558e64; iVar3 = iVar3 + 1) {
    sprintf(local_74,s__s__d_004c45ab,
            (&PTR_s_No_Unit_004faf7c)[*(int *)(&DAT_004c42f8 + *piVar2 * 0xe) * 9],piVar2[1]);
    iVar1 = FUN_0049eb44(DAT_004c42e0,0xe,1,0x26,0xffffffff,local_74);
    if (iVar1 != 0) {
      FUN_004382d0(&local_24,(int)(char)*PTR_DAT_004d5988,
                   *(undefined4 *)(&DAT_004c42f8 + *piVar2 * 0xe));
      FUN_0049eb44(DAT_004c42e0,0xe,1,0x24,iVar1 + -1,&local_24);
    }
    piVar2 = piVar2 + 2;
  }
  DAT_004c4508 = 0;
  FUN_0049eb44(DAT_004c42e0,0xe,1,0x1b,0,0);
  return;
}

