// FUN_00481da0 @ 00481da0 size=1355 sig=undefined FUN_00481da0() cc=unknown
// callers: FUN_00421fc4,FUN_00443830,FUN_00413428,FUN_00432824,FUN_00482320,FUN_0042f224
// callees: sprintf,FUN_004847f8,FUN_0048180c,FUN_00456d00,FUN_0043edd8,FUN_0046411c,FUN_00481540,FUN_00481b80,FUN_00464444,FUN_0048c434,FUN_0048192c

void FUN_00481da0(int param_1,int param_2,int param_3,undefined4 param_4,int param_5)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined1 local_78 [16];
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  if (param_5 == 4) {
    local_8 = 0;
  }
  else {
    local_8 = param_4;
  }
  if (DAT_00583e04 != 0) {
    puVar2 = &DAT_005a4eac;
    for (iVar3 = 1; iVar3 <= DAT_004d5b18; iVar3 = iVar3 + 1) {
      switch(param_5) {
      case 0:
        if (*(char *)((int)puVar2 + DAT_0058f1f4 + 0x66) < '\x02') {
          FUN_0048180c(puVar2,param_1,param_2,param_3,0xfffffffe,0,local_8);
        }
        if (iVar3 == DAT_004c5b50) {
          FUN_00481540(puVar2,param_1,param_2,param_3,0xff,local_8);
        }
        else {
          FUN_00481540(puVar2,param_1,param_2,param_3,0xffffffff,local_8);
        }
      case 1:
        if (DAT_004d59b4 == 0) {
          if (DAT_004d5ad0 == 0) {
            FUN_00481b80(DAT_004c5b54,DAT_004c5b58,&local_10,&local_18,param_3,param_4);
            FUN_00481b80(DAT_004c5b54 + DAT_005644c4,DAT_004c5b58 + DAT_005644c8,&local_14,&local_1c
                         ,param_3,param_4);
            if ((DAT_005644c4 < DAT_004d5b1a) || (DAT_005644c8 < DAT_004d5b1b)) {
              FUN_0046411c(local_10,local_18,local_14 - local_10,local_1c - local_18,0xda,0);
            }
          }
          else {
            local_60 = DAT_004c5460;
            local_64 = DAT_004c5464;
            FUN_0043edd8(0,0,&local_20,&local_30);
            FUN_0043edd8(0,local_64,&local_24,&local_34);
            FUN_0043edd8(local_60,0,&local_28,&local_38);
            FUN_0043edd8(local_60,local_64,&local_2c,&local_3c);
            FUN_00481b80(local_20,local_30,&local_40,&local_50,param_3,param_4);
            FUN_00481b80(local_24,local_34,&local_44,&local_54,param_3,param_4);
            FUN_00481b80(local_28,local_38,&local_48,&local_58,param_3,param_4);
            FUN_00481b80(local_2c,local_3c,&local_4c,&local_5c,param_3,param_4);
            local_68 = DAT_0051bddc;
            iVar1 = FUN_0048c434(*(undefined4 *)(&DAT_0058de34 + DAT_00583e18 * 0x1c));
            if (iVar1 != 0) {
              FUN_00464444(local_44,local_54,local_40,local_50,0xda);
              FUN_00464444(local_44,local_54,local_4c,local_5c,0xda);
              FUN_00464444(local_40,local_50,local_48,local_58,0xda);
              FUN_00464444(local_4c,local_5c,local_48,local_58,0xda);
              FUN_0048c434(local_68);
            }
          }
        }
        break;
      case 2:
      case 3:
        if ((*(byte *)(puVar2 + 7) & 2) == 0) {
          if ((*(byte *)(puVar2 + 7) & 4) == 0) {
            FUN_00481540(puVar2,param_1,param_2,param_3,0xffffffff,local_8);
          }
          else {
            FUN_0048180c(puVar2,param_1,param_2,param_3,0xfffffffd,0,local_8);
            FUN_00481540(puVar2,param_1,param_2,param_3,0,local_8);
          }
        }
        else {
          FUN_0048180c(puVar2,param_1,param_2,param_3,3,0,local_8);
          FUN_00481540(puVar2,param_1,param_2,param_3,0xff,local_8);
        }
        break;
      case 4:
        if (((*(ushort *)(puVar2 + 9) != 0) &&
            (FUN_0048180c(puVar2,param_1,param_2,param_3,*(ushort *)(puVar2 + 9) & 0xff,1,local_8),
            *(char *)((int)puVar2 + 0x7e) != '\0')) && (*(char *)(puVar2 + 0x1d) != -1)) {
          sprintf(local_78,&DAT_004dce2d,(int)*(short *)(puVar2 + 9));
          FUN_004847f8(*(char *)puVar2[*(char *)(puVar2 + 0x1d) + 0x20] * param_3 + param_1,
                       (((char *)puVar2[*(char *)(puVar2 + 0x1d) + 0x20])[1] + -1) * param_3 +
                       param_2,local_78,0xff);
        }
        FUN_00481540(puVar2,param_1,param_2,param_3,0,local_8);
        break;
      case 6:
        if (DAT_004d5aa0 != '\0') {
          switch(*(undefined1 *)((int)puVar2 + 0x21)) {
          case 0:
            local_c = 0x800000ad;
            break;
          case 1:
            local_c = 0x80bd944a;
            break;
          case 2:
            local_c = 0x804a947b;
            break;
          case 3:
            local_c = 0x80634a21;
            break;
          case 4:
            local_c = 0x80bdbdbd;
            break;
          case 5:
            local_c = 0x80000000;
          }
          FUN_0048180c(puVar2,param_1,param_2,param_3,local_c,1,local_8);
          FUN_00481540(puVar2,param_1,param_2,param_3,0xf,local_8);
        }
      }
      puVar2 = puVar2 + 0x2b7;
    }
    if (((param_5 == 3) || (param_5 == 0)) || (param_5 == 2)) {
      puVar2 = &DAT_005a4eac;
      for (iVar3 = 1; iVar3 <= DAT_004d5b18; iVar3 = iVar3 + 1) {
        if ((((param_5 != 2) && (*(char *)(puVar2 + 8) != -1)) &&
            ((DAT_0059f154 == 0 || ('\0' < *(char *)((int)puVar2 + DAT_0058f1f4 + 0x66))))) ||
           ((param_5 == 2 &&
            (iVar1 = FUN_00456d00((int)*(short *)((int)puVar2 + 0x1a),DAT_0058f1f4), iVar1 != 0))))
        {
          FUN_0048192c(puVar2,param_1,param_2,param_3,param_5,local_8);
        }
        puVar2 = puVar2 + 0x2b7;
      }
    }
  }
  return;
}

