#include <windows.h>
#include <richedit.h>
#include <shellscalingapi.h>

// ファイル
#define IDM_NEW         101
#define IDM_OPEN        102
#define IDM_SAVE        103
#define IDM_SAVEAS      104
#define IDM_CLOSE       105
#define IDM_CLOSEALL    106 
#define IDM_QUIT        107

// 編集
#define IDM_UNDO        201
#define IDM_REDO        202
#define IDM_CUT         203
#define IDM_COPY        204
#define IDM_PASTE       205
#define IDM_DELETE      206
#define IDM_SELECTALL   207

// ヘルプ
#define IDM_ABOUT       301

HWND hwndEdit = NULL;

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  switch (uMsg) {
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
    case WM_SETFOCUS:
      SetFocus(hwndEdit);
      return 0;
    case WM_SIZE: {
      UINT width = LOWORD(lParam);
      UINT height = HIWORD(lParam);
      MoveWindow(hwndEdit, 0, 0, width, height, TRUE);
      return 0;
    }
  }
  return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow) {
  SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);
  const wchar_t CLASS_NAME[] = L"ste";

  WNDCLASS wc = {};
  wc.lpfnWndProc = WndProc;
  wc.hInstance = hInstance;
  wc.lpszClassName = CLASS_NAME;

  RegisterClass(&wc);


  HMENU hFileMenu = CreateMenu();
  AppendMenuW(hFileMenu, MF_STRING, IDM_NEW, L"新規作成(&N)\tCtrl+N");
  AppendMenuW(hFileMenu, MF_STRING, IDM_OPEN, L"開く(&O)...\tCtrl+O");
  AppendMenuW(hFileMenu, MF_STRING, IDM_SAVE, L"保存(&S)\tCtrl+S");
  AppendMenuW(hFileMenu, MF_STRING, IDM_SAVEAS, L"名前を付けて保存(&A)\tCtrl+Shift+S");
  AppendMenuW(hFileMenu, MF_STRING, IDM_CLOSE, L"閉じる(&C)\tCtrl+W");
  AppendMenuW(hFileMenu, MF_STRING, IDM_CLOSEALL, L"すべて閉じる(&E)\tCtrl+Shift+W");
  AppendMenuW(hFileMenu, MF_SEPARATOR, 0, 0);
  AppendMenuW(hFileMenu, MF_STRING, IDM_QUIT, L"終了(&X)\tCtrl+Q");

  HMENU hEditMenu = CreateMenu();
  AppendMenuW(hEditMenu, MF_STRING, IDM_UNDO, L"元に戻す(&U)\tCtrl+Z");
  AppendMenuW(hEditMenu, MF_STRING, IDM_REDO, L"やり直し(&R)\tCtrl+R");
  AppendMenuW(hEditMenu, MF_SEPARATOR, 0, 0);
  AppendMenuW(hEditMenu, MF_STRING, IDM_CUT, L"切り取り(&T)\tCtrl+X");
  AppendMenuW(hEditMenu, MF_STRING, IDM_COPY, L"コピー(&C)\tCtrl+C");
  AppendMenuW(hEditMenu, MF_STRING, IDM_PASTE, L"貼り付け(&P)\tCtrl+V");
  AppendMenuW(hEditMenu, MF_STRING, IDM_DELETE, L"削除(&D)\tDel");
  AppendMenuW(hEditMenu, MF_STRING, IDM_SELECTALL, L"すべて選択(&A)\tCtrl+A");

  HMENU hHelpMenu = CreateMenu();
  AppendMenuW(hHelpMenu, MF_STRING, IDM_ABOUT, L"バージョン情報(&A)...");

  HMENU hMainMenu = CreateMenu();
  AppendMenuW(hMainMenu, MF_POPUP, reinterpret_cast<UINT_PTR>(hFileMenu), L"ファイル(&F)");
  AppendMenuW(hMainMenu, MF_POPUP, reinterpret_cast<UINT_PTR>(hEditMenu), L"編集(&E)");
  AppendMenuW(hMainMenu, MF_POPUP, reinterpret_cast<UINT_PTR>(hHelpMenu), L"ヘルプ(&H)");

  HWND hwnd = CreateWindowExW(
    0,                            // 追加スタイル
    CLASS_NAME,                   // ウィンドウクラス
    L"ste",                       // ウィンドウテキスト
    WS_OVERLAPPEDWINDOW,          // 基本スタイル
    CW_USEDEFAULT, CW_USEDEFAULT, // 大きさ
    CW_USEDEFAULT, CW_USEDEFAULT, // 位置
    NULL,                         // 親
    hMainMenu,                    // メニュー
    hInstance,                    // インスタンス
    NULL                          // 追加データ
  );

  if (hwnd == NULL) return 0;

  HMODULE hRichEdit = LoadLibrary(TEXT("Msftedit.dll"));
  if (hRichEdit == NULL) return 0;

  hwndEdit = CreateWindowExW(
    WS_EX_CLIENTEDGE, // 追加スタイル
    MSFTEDIT_CLASS,   // ウィンドウクラス
    L"",              // ウィンドウテキスト
    ES_MULTILINE |
    ES_LEFT |
    ES_AUTOVSCROLL |
    ES_AUTOHSCROLL |
    WS_VISIBLE |
    WS_CHILD |
    WS_HSCROLL |
    WS_VSCROLL |
    WS_TABSTOP,
    0, 0,             // 大きさ
    0, 0,             // 位置
    hwnd,             // 親
    NULL,             // メニュー
    hInstance,        // インスタンス
    NULL              // 追加データ
  );

  // 文書を画面端で折り返さない
  SendMessageW(hwndEdit, EM_SETTARGETDEVICE, 0, 1);

  // フォント設定
  CHARFORMAT2 cf = {};
  cf.cbSize = sizeof(cf);
  cf.dwMask = CFM_FACE | CFM_SIZE | CFM_COLOR;
  cf.yHeight= 12 * 20; // 12pt
  cf.crTextColor = RGB(0, 0, 0);
  wcscpy_s(cf.szFaceName, L"Consolas");
  SendMessageW(hwndEdit, EM_SETCHARFORMAT, SCF_ALL, reinterpret_cast<LPARAM>(&cf));

  ShowWindow(hwnd, nCmdShow);
  SetFocus(hwndEdit);

  BOOL bRet;
  MSG msg = {};
  while ( (bRet = GetMessageW(&msg, NULL, 0, 0)) != 0) {
    if (bRet == -1) return 0;
    TranslateMessage(&msg);
    DispatchMessageW(&msg);
  }

  return 0;
}
