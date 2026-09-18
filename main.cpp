#include <windows.h>
#include <richedit.h>
#include <shellscalingapi.h>

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

  HWND hwnd = CreateWindowExW(
    0,                            // 追加スタイル
    CLASS_NAME,                   // ウィンドウクラス
    L"ste",                       // ウィンドウテキスト
    WS_OVERLAPPEDWINDOW,          // 基本スタイル
    CW_USEDEFAULT, CW_USEDEFAULT, // 大きさ
    CW_USEDEFAULT, CW_USEDEFAULT, // 位置
    NULL,                         // 親
    NULL,                         // メニュー
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
