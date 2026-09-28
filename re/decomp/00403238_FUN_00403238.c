// FUN_00403238 @ 00403238 size=169 sig=undefined FUN_00403238() cc=unknown
// callers: FUN_00408a88
// callees: 

void FUN_00403238(int param_1)

{
  undefined2 *puVar1;
  
  puVar1 = &DAT_005f0410;
  do {
    if ((undefined2 *)0x64536f < puVar1) {
      return;
    }
    if (((*(char *)(puVar1 + 2) != '\0') &&
        (param_1 == (char)(&DAT_005a43f0)[(short)puVar1[4] * 0xadc])) &&
       (*(char *)(puVar1 + 7) == '\0')) {
      switch(*(undefined1 *)((int)puVar1 + 5)) {
      case 1:
      case 2:
      case 3:
        *(undefined1 *)(puVar1 + 7) = 3;
        break;
      case 4:
      case 7:
      case 8:
      case 9:
      case 10:
      case 0xc:
      case 0xf:
        *(undefined1 *)(puVar1 + 7) = 1;
        break;
      case 5:
        *(undefined1 *)(puVar1 + 7) = 4;
      case 0xb:
        if (*(char *)(puVar1 + 2) == '/') {
          *(undefined1 *)(puVar1 + 7) = 3;
        }
        else {
          *(undefined1 *)(puVar1 + 7) = 4;
        }
        break;
      case 6:
      case 0xd:
      case 0xe:
      case 0x11:
        *(undefined1 *)(puVar1 + 7) = 5;
      }
      if (*(char *)(puVar1 + 2) == '%') {
        *(undefined1 *)(puVar1 + 7) = 1;
      }
    }
    puVar1 = puVar1 + 0x91;
  } while( true );
}

