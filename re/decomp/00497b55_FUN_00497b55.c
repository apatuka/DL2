// FUN_00497b55 @ 00497b55 size=149 sig=undefined FUN_00497b55() cc=unknown
// callers: FUN_00497d40
// callees: FUN_0048f992

void FUN_00497b55(undefined4 param_1,undefined1 *param_2,short param_3)

{
  char cVar1;
  bool bVar2;
  undefined4 uVar3;
  undefined4 in_ECX;
  short sVar4;
  undefined4 uStack_8;
  
  sVar4 = 0;
  uStack_8 = in_ECX;
  if (0 < param_3) {
    do {
      FUN_0048f992(param_1,(int)&uStack_8 + 2,1);
      if ((char)uStack_8._2_1_ < '\x01') {
        if ((char)uStack_8._2_1_ < -0x7f) {
          FUN_0048f992(param_1,(int)&uStack_8 + 3,1);
        }
        else {
          uStack_8._0_3_ = CONCAT12(~uStack_8._2_1_ + 2,(undefined2)uStack_8);
          FUN_0048f992(param_1,(int)&uStack_8 + 3,1);
          uVar3 = uStack_8;
          while (bVar2 = uStack_8._2_1_ != '\0', uStack_8 = uVar3, bVar2) {
            uStack_8._3_1_ = (undefined1)((uint)uVar3 >> 0x18);
            *param_2 = uStack_8._3_1_;
            param_2 = param_2 + 1;
            sVar4 = sVar4 + 1;
            uStack_8._2_1_ = (byte)((uint)uVar3 >> 0x10);
            uStack_8._2_1_ = uStack_8._2_1_ + -1;
            uStack_8._0_2_ = (undefined2)uVar3;
            uVar3 = uStack_8;
          }
        }
      }
      else {
        cVar1 = uStack_8._2_1_ + 1;
        uStack_8._0_3_ = CONCAT12(cVar1,(undefined2)uStack_8);
        while (cVar1 != '\0') {
          FUN_0048f992(param_1,param_2,1);
          param_2 = param_2 + 1;
          sVar4 = sVar4 + 1;
          cVar1 = uStack_8._2_1_ + -1;
          uStack_8._0_3_ = CONCAT12(cVar1,(undefined2)uStack_8);
        }
      }
    } while (sVar4 < param_3);
  }
  return;
}

