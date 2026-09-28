// FUN_004a335b @ 004a335b size=84 sig=undefined FUN_004a335b() cc=unknown
// callers: FUN_004a33f3,FUN_004a39f7
// callees: FUN_0049d4aa,FUN_0048e5f8
// strings: \"Unknown opcode in SMenu item list\"

int * FUN_004a335b(int *param_1)

{
  switch(*param_1) {
  default:
    FUN_0048e5f8(s_Unknown_opcode_in_SMenu_item_lis_0051e439);
    break;
  case 1:
  case 3:
  case 4:
  case 5:
  case 6:
  case 7:
  case 8:
  case 9:
  case 10:
  case 0xb:
  case 0xc:
  case 0xd:
  case 0xe:
  case 0xf:
  case 0x11:
  case 0x12:
  case 0x13:
  case 0x14:
  case 0x15:
  case 0x16:
  case 0x1b:
  case 0x1c:
  case 0x1d:
  case 0x1e:
  case 0x1f:
  case 0x20:
  case 0x21:
  case 0x26:
  case 0x27:
  case 0x28:
    param_1 = param_1 + 2;
    break;
  case 2:
  case 0x2a:
    param_1 = param_1 + 5;
    break;
  case 0x17:
    param_1 = (int *)FUN_0049d4aa(param_1);
    break;
  case 0x22:
  case 0x23:
  case 0x24:
  case 0x25:
    param_1 = param_1 + 1 + param_1[1] + 1;
    break;
  case -1:
    param_1 = param_1 + 1;
  }
  return param_1;
}

