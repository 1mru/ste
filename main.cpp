#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  switch (uMsg) {
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
    // 後ほどRichTextEdit/Scintillaを追加するのでWM_PAINTは不要
  }
  return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow) {
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

  ShowWindow(hwnd, nCmdShow);

  BOOL bRet;
  MSG msg = {};
  while ( (bRet = GetMessageW(&msg, NULL, 0, 0)) != 0) {
    if (bRet == -1) return 0;
    TranslateMessage(&msg);
    DispatchMessageW(&msg);
  }

  return 0;
}
