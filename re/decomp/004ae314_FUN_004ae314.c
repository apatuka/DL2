// FUN_004ae314 @ 004ae314 size=253 sig=undefined FUN_004ae314() cc=unknown
// callers: FUN_004af598,FUN_004af0b4
// callees: FUN_004adff4,FUN_004b12c4

float10 FUN_004ae314(int param_1,undefined4 param_2,undefined4 param_3,ushort param_4,
                    undefined4 param_5,undefined4 param_6)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  ushort uVar3;
  ushort uVar4;
  ushort uVar5;
  float10 fVar6;
  undefined8 local_14;
  
  if (param_1 == 0) {
    uVar3 = 0x407e;
    uVar5 = 0x3f6a;
  }
  else {
    uVar3 = 0x43fe;
    uVar5 = 0x3bcd;
  }
  uVar4 = param_4 & 0x7fff;
  if (uVar4 == 0x7fff) {
    return (float10)CONCAT28(param_4,CONCAT26(param_3._2_2_,CONCAT24((short)param_3,param_2)));
  }
  if (uVar3 < uVar4) {
    local_14 = (double)CONCAT44(param_6,param_5);
  }
  else {
    if (uVar3 == uVar4) {
      uVar1 = FUN_004adff4(0,0);
      FUN_004adff4(0xc00,0xc00);
      FUN_004adff4(uVar1,0xc00);
      return (float10)(float)(float10)CONCAT28(param_4,CONCAT26(param_3._2_2_,
                                                                CONCAT24((short)param_3,param_2)));
    }
    if (((((short)param_2 == 0 && uVar4 == 0) && param_2._2_2_ == 0) && (short)param_3 == 0) &&
        param_3._2_2_ == 0) {
      return (float10)CONCAT28(param_4,CONCAT26(param_3._2_2_,CONCAT24((short)param_3,param_2)));
    }
    if (uVar5 <= uVar4) {
      return (float10)CONCAT28(param_4,CONCAT26(param_3._2_2_,CONCAT24((short)param_3,param_2)));
    }
    local_14 = 0.0;
  }
  puVar2 = (undefined4 *)FUN_004b12c4();
  *puVar2 = 0x22;
  if ((param_4 & 0x8000) == 0) {
    fVar6 = (float10)local_14;
  }
  else {
    fVar6 = -(float10)local_14;
  }
  return fVar6;
}

