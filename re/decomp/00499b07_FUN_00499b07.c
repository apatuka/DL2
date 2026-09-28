// FUN_00499b07 @ 00499b07 size=152 sig=undefined FUN_00499b07() cc=unknown
// callers: 
// callees: FUN_00499a4f

undefined1
FUN_00499b07(byte param_1,byte param_2,byte param_3,byte param_4,byte param_5,byte param_6,
            short param_7,undefined4 param_8)

{
  undefined1 uVar1;
  
  uVar1 = FUN_00499a4f(((int)(((uint)param_4 - (uint)param_1) * (int)param_7) / 100 & 0xffU) +
                       (uint)param_1,
                       ((int)(((uint)param_5 - (uint)param_2) * (int)param_7) / 100 & 0xffU) +
                       (uint)param_2,
                       ((int)(((uint)param_6 - (uint)param_3) * (int)param_7) / 100 & 0xffU) +
                       (uint)param_3,param_8);
  return uVar1;
}

