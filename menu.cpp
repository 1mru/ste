#include "menu.h"
#include <windows.h>

HMENU createMenuBar() {
  HMENU hFileMenu = CreateMenu();

  AppendMenuW(
    hFileMenu,
    MF_STRING,
    IDM_NEW,
    L"新規作成(&N)\tCtrl+N"
  );

  AppendMenuW(
    hFileMenu,
    MF_STRING,
    IDM_OPEN,
    L"開く(&O)...\tCtrl+O"
  );

  AppendMenuW(
    hFileMenu,
    MF_STRING,
    IDM_SAVE,
    L"保存(&S)\tCtrl+S"
  );

  AppendMenuW(
    hFileMenu,
    MF_STRING,
    IDM_SAVEAS,
    L"名前を付けて保存(&A)\tCtrl+Shift+S"
  );

  AppendMenuW(
    hFileMenu,
    MF_STRING,
    IDM_CLOSE,
    L"閉じる(&C)\tCtrl+W"
  );

  AppendMenuW(
    hFileMenu,
    MF_STRING,
    IDM_CLOSEALL,
    L"すべて閉じる(&E)\tCtrl+Shift+W"
  );

  AppendMenuW(
    hFileMenu,
    MF_SEPARATOR,
    0,
    0
  );

  AppendMenuW(
    hFileMenu,
    MF_STRING,
    IDM_QUIT,
    L"終了(&X)\tCtrl+Q"
  );

  HMENU hEditMenu = CreateMenu();
  AppendMenuW(
    hEditMenu,
    MF_STRING,
    IDM_UNDO,
    L"元に戻す(&U)\tCtrl+Z"
  );

  AppendMenuW(
    hEditMenu,
    MF_STRING,
    IDM_REDO,
    L"やり直し(&R)\tCtrl+R"
  );

  AppendMenuW(
    hEditMenu,
    MF_SEPARATOR,
    0,
    0
  );

  AppendMenuW(
    hEditMenu,
    MF_STRING,
    IDM_CUT,
    L"切り取り(&T)\tCtrl+X"
  );

  AppendMenuW(
    hEditMenu,
    MF_STRING,
    IDM_COPY,
    L"コピー(&C)\tCtrl+C"
  );

  AppendMenuW(
    hEditMenu,
    MF_STRING,
    IDM_PASTE,
    L"貼り付け(&P)\tCtrl+V"
  );

  AppendMenuW(
    hEditMenu,
    MF_STRING,
    IDM_DELETE,
    L"削除(&D)\tDel"
  );

  AppendMenuW(
    hEditMenu,
    MF_STRING,
    IDM_SELECTALL,
    L"すべて選択(&A)\tCtrl+A"
  );

  HMENU hHelpMenu = CreateMenu();

  AppendMenuW(
    hHelpMenu,
    MF_STRING,
    IDM_ABOUT,
    L"バージョン情報(&A)..."
  );

  HMENU hMainMenu = CreateMenu();
  AppendMenuW(
    hMainMenu,
    MF_POPUP,
    reinterpret_cast<UINT_PTR>(hFileMenu), L"ファイル(&F)"
  );

  AppendMenuW(
    hMainMenu,
    MF_POPUP,
    reinterpret_cast<UINT_PTR>(hEditMenu), L"編集(&E)"
  );

  AppendMenuW(
    hMainMenu,
    MF_POPUP,
    reinterpret_cast<UINT_PTR>(hHelpMenu),
    L"ヘルプ(&H)"
  );

  return hMainMenu;
}
