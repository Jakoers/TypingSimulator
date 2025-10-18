#ifndef U8UTILS_A3DCCD5C_C3F6_4D64_ADE3_5E2CF3825EC2
#define U8UTILS_A3DCCD5C_C3F6_4D64_ADE3_5E2CF3825EC2

#include <windows.h>

#include <string>

/**
 * @brief 发送一个 UTF-16 code unit
 *
 * @param cu 要发送的 UTF-16 code unit
 */
void SendUtf16CodeUnit(wchar_t cu)
{
    INPUT inp[2] = {};
    // key down
    inp[0].type       = INPUT_KEYBOARD;
    inp[0].ki.wScan   = cu;
    inp[0].ki.dwFlags = KEYEVENTF_UNICODE;
    // key up
    inp[1].type       = INPUT_KEYBOARD;
    inp[1].ki.wScan   = cu;
    inp[1].ki.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;
    SendInput(2, inp, sizeof(INPUT));
}

void SendEnterKey()
{
    INPUT inp[2] = {};

    // key down
    inp[0].type       = INPUT_KEYBOARD;
    inp[0].ki.wVk     = VK_RETURN; // 虚拟键码
    inp[0].ki.dwFlags = 0;

    // key up
    inp[1].type       = INPUT_KEYBOARD;
    inp[1].ki.wVk     = VK_RETURN;
    inp[1].ki.dwFlags = KEYEVENTF_KEYUP;

    SendInput(2, inp, sizeof(INPUT));
}

std::wstring Utf8ToUtf16(std::string const &utf8)
{
    if (utf8.empty()) return {};
    int wlen =
        MultiByteToWideChar(CP_UTF8, 0, utf8.data(), utf8.size(), nullptr, 0);
    if (wlen == 0) return {};
    std::wstring w;
    w.resize(wlen);
    MultiByteToWideChar(CP_UTF8, 0, utf8.data(), (int) utf8.size(), &w[0],
        wlen);
    return w;
}

/**
 * @brief 将 uft-8 字符串中的每个字符按照 code unit 逐个发送到焦点窗口中
 *
 * @param utf8 要发送的 UTF-8 字符串
 * @param delayMilliseconds 每个code unit之间的等待时间，单位：毫秒
 */
void SendUtf8StringAsUnicodeInput(std::string const &utf8,
    DWORD                                            delayMilliseconds = 0)
{
    std::wstring w = Utf8ToUtf16(utf8);
    if (w.empty()) return;
    for (auto c : w)
    {
        SendUtf16CodeUnit(c);
        Sleep(delayMilliseconds);
    }
}

#endif /* U8UTILS_A3DCCD5C_C3F6_4D64_ADE3_5E2CF3825EC2 */
