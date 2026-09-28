// FUN_004a43da @ 004a43da size=1896 sig=undefined FUN_004a43da() cc=unknown
// callers: FUN_00438134,FUN_0041f7f0,FUN_00420954,FUN_00425d68,FUN_0041e4d0,FUN_0041c258,FUN_0041b330,FUN_0043b50c,FUN_00424e28,FUN_0043aed0,FUN_0043b1ac,FUN_00427198,FUN_0042f224,FUN_00431258,FUN_0041b608,FUN_00418f3c,FUN_0042b99c,FUN_00438f58,FUN_0041f2c8,FUN_004316d8,FUN_00418efc,FUN_00418d4c,FUN_00413428,FUN_0041f024,FUN_00421fc4,FUN_0043ae78,FUN_0042a25c,FUN_00414dd4,FUN_0042cfbc,FUN_0043c78c,FUN_0049eb44,FUN_0043addc,FUN_0042de68,FUN_00438dbc,FUN_0043b040,FUN_0043b2c4,FUN_0043b8b0,FUN_00414b10,FUN_004209c0,FUN_00422f7c,FUN_00425bc4,FUN_00418c8c,FUN_00414bd8,FUN_0041ab54,FUN_0041be6c,FUN_00432824,FUN_00431dfc
// callees: FUN_0049ee8f,FUN_0049f947,FUN_0049d7f4,FUN_0049edb2,FUN_004a42f0,FUN_0049e971,FUN_004a228a,FUN_004a18a9,FUN_004a412b,FUN_0049eef7,FUN_0049ea99,FUN_004a1555,FUN_0049d58b,FUN_0049e9e8,FUN_004a3e49,FUN_0049d5c5,FUN_0049cb2f,FUN_0049d06a,FUN_0049b7f0,FUN_004a4156,FUN_0049d5dd,FUN_0049f7c9,FUN_0049d54f,FUN_0049ee46,FUN_004a1150,FUN_0049e2d5,FUN_0049ef88,FUN_004a2307,FUN_004a120c,FUN_004a196e,strlen,FUN_0049d7cc,FUN_0049ef47,FUN_004a6964,FUN_0049ebfb,FUN_0049eb44,FUN_0049b90a,FUN_0049cf41,FUN_004a3ea0,FUN_004a0e79,FUN_004a18c5,FUN_004a1715

undefined4 FUN_004a43da(int param_1,undefined4 param_2,uint param_3,undefined4 *param_4)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  
  switch(param_2) {
  default:
    goto switchD_004a43ef_caseD_0;
  case 1:
    if ((param_1 == 0) || (param_4 == (undefined4 *)0x0)) {
      uVar2 = 0;
    }
    else {
      param_4[1] = *(undefined4 *)(param_1 + 0x10);
      *param_4 = *(undefined4 *)(param_1 + 0xc);
      param_4[3] = *(int *)(param_1 + 0x10) + *(int *)(param_1 + 0x14);
      param_4[2] = *(int *)(param_1 + 0xc) + *(int *)(param_1 + 0x18);
      uVar2 = 1;
    }
    break;
  case 2:
    uVar2 = FUN_0049ea99(param_1);
    FUN_004a3ea0(uVar2,param_1);
    uVar2 = 1;
    break;
  case 3:
    uVar2 = FUN_0049ea99(param_1);
    FUN_004a0e79(uVar2,param_1);
    uVar2 = 1;
    break;
  case 7:
    *(undefined4 **)(param_1 + 0x40) = param_4;
    uVar2 = 1;
    break;
  case 8:
    FUN_0049f7c9(param_1);
    uVar2 = 1;
    break;
  case 9:
    uVar2 = FUN_0049ea99(param_1);
    FUN_004a228a(uVar2,param_1,param_4,param_3);
    uVar2 = 1;
    break;
  case 10:
    uVar2 = FUN_0049ea99(param_1);
    FUN_004a2307(uVar2,param_1,param_3);
    uVar2 = 1;
    break;
  case 0xb:
    FUN_0049f947(param_1,param_3);
    uVar2 = 1;
    break;
  case 0xc:
    if ((param_1 == 0) || ((*(byte *)(param_1 + 0x28) & 1) == 0)) {
      uVar2 = 0;
    }
    else {
      uVar2 = 1;
    }
    break;
  case 0xd:
    if ((param_1 == 0) || (param_4 == (undefined4 *)0x0)) {
      uVar2 = 0;
    }
    else {
      uVar2 = FUN_0049ea99(param_1);
      uVar2 = FUN_004a120c(uVar2,param_1,param_4);
    }
    break;
  case 0xe:
    if (*(int *)(param_1 + 0x34) != 0) {
      if (param_4 == (undefined4 *)0x0) {
        uVar2 = strlen(*(undefined4 *)(param_1 + 0x34));
        return uVar2;
      }
      iVar1 = strlen(*(undefined4 *)(param_1 + 0x34));
      if (iVar1 < (int)param_3) {
        FUN_004a6964(param_4,*(undefined4 *)(param_1 + 0x34));
        return 1;
      }
    }
    uVar2 = 0;
    break;
  case 0xf:
    FUN_004a18a9(param_1 + 0x34);
    if (param_4 != (undefined4 *)0x0) {
      uVar2 = FUN_004a18c5(param_4,0);
      *(undefined4 *)(param_1 + 0x34) = uVar2;
    }
    uVar7 = 0;
    uVar6 = 3;
    uVar5 = 0x1c;
    uVar4 = 2;
    iVar1 = param_1;
    uVar2 = FUN_0049ea99(param_1);
    FUN_0049eb44(uVar2,iVar1,uVar4,uVar5,uVar6,uVar7);
    uVar7 = 0;
    uVar6 = 0;
    uVar5 = 8;
    uVar4 = 2;
    uVar2 = FUN_0049ea99(param_1);
    FUN_0049eb44(uVar2,param_1,uVar4,uVar5,uVar6,uVar7);
    uVar2 = 1;
    break;
  case 0x10:
    if (param_4 == (undefined4 *)0x0) {
      uVar2 = 0;
    }
    else {
      *param_4 = *(undefined4 *)(param_1 + 0x3c);
      uVar2 = 1;
    }
    break;
  case 0x11:
    uVar2 = FUN_004a1715(param_1,param_3);
    break;
  case 0x12:
    uVar2 = FUN_0049e971(param_1,param_3,param_4);
    break;
  case 0x13:
    uVar2 = FUN_0049e9e8(param_1,param_3,param_4);
    break;
  case 0x15:
    uVar2 = *(undefined4 *)(param_1 + 0x44);
    break;
  case 0x16:
    *(uint *)(param_1 + 0x44) = param_3;
    uVar2 = 1;
    break;
  case 0x17:
    uVar2 = FUN_0049ea99(param_1);
    uVar2 = FUN_0049d58b(uVar2,param_1);
    break;
  case 0x18:
    uVar2 = FUN_0049ea99(param_1);
    uVar2 = FUN_0049d7cc(uVar2,param_1);
    break;
  case 0x19:
    uVar2 = FUN_0049ea99(param_1);
    uVar2 = FUN_0049d7f4(uVar2,param_1,param_3,param_4);
    break;
  case 0x1a:
    uVar2 = FUN_0049ea99(param_1);
    uVar2 = FUN_0049d5c5(uVar2,param_1);
    break;
  case 0x1b:
  case 0x1c:
    uVar2 = FUN_0049edb2(param_1,param_2,param_3,param_4);
    break;
  case 0x1d:
    uVar2 = FUN_0049ebfb(param_1,param_3,param_4);
    break;
  case 0x1e:
    uVar2 = FUN_0049ea99(param_1);
    uVar2 = FUN_0049d5dd(uVar2,param_1);
    break;
  case 0x1f:
    uVar2 = FUN_0049ea99(param_1);
    uVar2 = FUN_0049ee46(uVar2,param_1,param_3);
    break;
  case 0x21:
    uVar2 = FUN_0049ea99(param_1);
    uVar2 = FUN_0049cf41(uVar2,param_1,param_4,param_3);
    break;
  case 0x22:
    uVar2 = FUN_0049ea99(param_1);
    uVar2 = FUN_0049d54f(uVar2,param_1,param_3);
    break;
  case 0x23:
    uVar4 = 0;
    uVar2 = FUN_0049ea99(param_1);
    uVar2 = FUN_0049ef47(uVar2,param_1,param_3,uVar4,param_4);
    break;
  case 0x24:
    uVar4 = 1;
    uVar2 = FUN_0049ea99(param_1);
    uVar2 = FUN_0049ef47(uVar2,param_1,param_3,uVar4,param_4);
    break;
  case 0x25:
    uVar4 = 2;
    uVar2 = FUN_0049ea99(param_1);
    uVar2 = FUN_0049ef47(uVar2,param_1,param_3,uVar4,param_4);
    break;
  case 0x26:
    uVar2 = FUN_0049ea99(param_1);
    uVar2 = FUN_0049ee8f(uVar2,param_1,param_3,param_4);
    break;
  case 0x27:
    uVar2 = FUN_0049ea99(param_1);
    uVar2 = FUN_0049eef7(uVar2,param_1,param_3);
    break;
  case 0x28:
    uVar2 = FUN_0049ea99(param_1);
    uVar2 = FUN_0049b90a(uVar2,param_1,param_4);
    break;
  case 0x29:
    uVar2 = FUN_0049ea99(param_1);
    uVar2 = FUN_0049b7f0(uVar2,param_1,param_4);
    break;
  case 0x2a:
  case 0x2b:
  case 0x2c:
  case 0x2d:
  case 0x2e:
    uVar2 = FUN_0049cb2f(param_1,param_2,param_3,param_4);
    break;
  case 0x30:
    uVar2 = FUN_004a412b(param_1,param_2,param_3,param_4);
    break;
  case 0x31:
    if (*(int *)(param_1 + 0xfc) != 0) {
      *(undefined4 *)(*(int *)(param_1 + 0xfc) + 0xfc) = 0;
    }
    uVar2 = FUN_0049ea99(param_1);
    iVar1 = FUN_004a1150(uVar2,param_3,param_4);
    *(int *)(param_1 + 0xfc) = iVar1;
    if (iVar1 != 0) {
      *(int *)(*(int *)(param_1 + 0xfc) + 0xfc) = param_1;
    }
    uVar7 = 0;
    uVar6 = 1;
    uVar5 = 0x32;
    uVar4 = 2;
    uVar2 = FUN_0049ea99(param_1);
    FUN_0049eb44(uVar2,param_1,uVar4,uVar5,uVar6,uVar7);
    uVar2 = 1;
    break;
  case 0x32:
    uVar2 = FUN_004a4156(param_1,param_3);
    break;
  case 0x33:
    uVar2 = FUN_0049ea99(param_1);
    uVar2 = FUN_0049d06a(uVar2,param_1,param_3);
    break;
  case 0x34:
    uVar7 = 0;
    uVar6 = 0;
    uVar5 = 8;
    uVar4 = 2;
    iVar1 = param_1;
    uVar2 = FUN_0049ea99(param_1);
    FUN_0049eb44(uVar2,iVar1,uVar4,uVar5,uVar6,uVar7);
    uVar3 = 0x800000;
    if (param_3 == 0) {
      uVar3 = 0;
    }
    *(uint *)(param_1 + 0x28) = *(uint *)(param_1 + 0x28) & 0xff7fffff | uVar3;
    if (*(int *)(param_1 + 0x1c) == 5) {
      FUN_0049e2d5(param_1,param_3 != 0);
    }
    uVar7 = 0;
    uVar6 = 0;
    uVar5 = 8;
    uVar4 = 2;
    uVar2 = FUN_0049ea99(param_1);
    FUN_0049eb44(uVar2,param_1,uVar4,uVar5,uVar6,uVar7);
    goto switchD_004a43ef_caseD_0;
  case 0x35:
    uVar4 = 0;
    uVar2 = FUN_0049ea99(param_1);
    uVar2 = FUN_0049ef88(uVar2,param_1,param_3,uVar4,param_4);
    break;
  case 0x36:
    uVar4 = 1;
    uVar2 = FUN_0049ea99(param_1);
    uVar2 = FUN_0049ef88(uVar2,param_1,param_3,uVar4,param_4);
    break;
  case 0x37:
    uVar4 = 2;
    uVar2 = FUN_0049ea99(param_1);
    uVar2 = FUN_0049ef88(uVar2,param_1,param_3,uVar4,param_4);
    break;
  case 0x38:
    if (((*(int *)(param_1 + 0x100) == 0) || (param_4 == (undefined4 *)0x0)) ||
       (iVar1 = strlen(*(undefined4 *)(param_1 + 0x100)), (int)param_3 <= iVar1)) {
      uVar2 = 0;
    }
    else {
      FUN_004a6964(param_4,*(undefined4 *)(param_1 + 0x100));
      uVar2 = 1;
    }
    break;
  case 0x39:
    FUN_004a18a9(param_1 + 0x100);
    if (param_4 != (undefined4 *)0x0) {
      uVar2 = FUN_004a18c5(param_4,0);
      *(undefined4 *)(param_1 + 0x100) = uVar2;
    }
    uVar7 = 0;
    uVar6 = 0;
    uVar5 = 8;
    uVar4 = 2;
    uVar2 = FUN_0049ea99(param_1);
    FUN_0049eb44(uVar2,param_1,uVar4,uVar5,uVar6,uVar7);
    uVar2 = 1;
    break;
  case 0x3a:
    uVar2 = 1;
    break;
  case 0x3b:
    uVar2 = 1;
    break;
  case 0x3c:
    if (param_4 == (undefined4 *)0x0) {
      if (param_3 == 0) {
        *(int *)(param_1 + 0x104) = *(int *)(param_1 + 0x104) + -1;
      }
      else {
        *(int *)(param_1 + 0x104) = *(int *)(param_1 + 0x104) + 1;
      }
    }
    else if (param_3 == 0) {
      if (*(int *)(param_1 + 0x104) != 0) {
        *(int *)(param_1 + 0x104) = *(int *)(param_1 + 0x104) + -1;
      }
    }
    else if (*(int *)(param_1 + 0x104) == 0) {
      *(int *)(param_1 + 0x104) = *(int *)(param_1 + 0x104) + 1;
    }
    if ((*(int *)(param_1 + 0x104) == 1) || (*(int *)(param_1 + 0x104) == 0)) {
      uVar6 = 0;
      uVar3 = (uint)(*(int *)(param_1 + 0x104) == 0);
      uVar5 = 10;
      uVar4 = 2;
      iVar1 = param_1;
      uVar2 = FUN_0049ea99(param_1);
      FUN_0049eb44(uVar2,iVar1,uVar4,uVar5,uVar3,uVar6);
      FUN_0049f7c9(param_1);
    }
    uVar2 = *(undefined4 *)(param_1 + 0x104);
    break;
  case 0x3d:
    uVar2 = FUN_0049ea99(param_1);
    FUN_004a1555(uVar2,param_1,param_3,param_4);
    uVar2 = 1;
    break;
  case 0x3e:
    if ((-1 < (int)param_3) && ((int)param_3 < 3)) {
      *(undefined4 **)(param_1 + 0x10c + param_3 * 4) = param_4;
    }
switchD_004a43ef_caseD_0:
    uVar2 = 0;
    break;
  case 0x3f:
    if (param_4 == (undefined4 *)0x0) {
      uVar2 = 0;
    }
    else {
      *param_4 = *(undefined4 *)(param_1 + 0x11c);
      uVar2 = 1;
    }
    break;
  case 0x40:
    uVar2 = FUN_0049ea99(param_1);
    uVar2 = FUN_004a196e(uVar2,param_1,param_4);
    break;
  case 0x41:
    if (param_4 == (undefined4 *)0x0) {
      uVar2 = 0;
    }
    else {
      *param_4 = *(undefined4 *)(param_1 + 0x54);
      uVar2 = 1;
    }
    break;
  case 0x42:
    uVar7 = 0;
    uVar6 = 0;
    uVar5 = 8;
    uVar4 = 2;
    iVar1 = param_1;
    uVar2 = FUN_0049ea99(param_1);
    FUN_0049eb44(uVar2,iVar1,uVar4,uVar5,uVar6,uVar7);
    *(undefined4 **)(param_1 + 0x54) = param_4;
    uVar7 = 0;
    uVar6 = 0;
    uVar5 = 8;
    uVar4 = 2;
    uVar2 = FUN_0049ea99(param_1);
    FUN_0049eb44(uVar2,param_1,uVar4,uVar5,uVar6,uVar7);
    uVar2 = 1;
    break;
  case 0x43:
    if (param_4 == (undefined4 *)0x0) {
      uVar2 = 0;
    }
    else {
      *param_4 = *(undefined4 *)(param_1 + 0x24);
      uVar2 = 1;
    }
    break;
  case 0x44:
    if ((*(uint *)(param_1 + 0x24) & 0x1f) != (param_3 & 0x1f)) {
      uVar7 = 0;
      uVar6 = 0;
      uVar5 = 8;
      uVar4 = 2;
      iVar1 = param_1;
      uVar2 = FUN_0049ea99(param_1);
      FUN_0049eb44(uVar2,iVar1,uVar4,uVar5,uVar6,uVar7);
      iVar1 = param_1;
      uVar2 = FUN_0049ea99(param_1);
      FUN_004a3e49(uVar2,iVar1);
      *(uint *)(param_1 + 0x24) = *(uint *)(param_1 + 0x24) & 0xffffffe0 | param_3 & 0x1f;
    }
    uVar2 = 1;
    break;
  case 0x46:
    FUN_004a42f0(param_1,param_3,param_4);
    uVar2 = 1;
  }
  return uVar2;
}

