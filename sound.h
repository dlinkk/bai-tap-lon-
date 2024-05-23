#pragma once // Đảm bảo rằng file header này chỉ được include một lần trong quá trình biên dịch.

#include <SDL_mixer.h> // Bao gồm thư viện SDL_mixer để xử lý âm thanh.
#include <string> // Bao gồm thư viện chuẩn C++ cho xử lý chuỗi.
#include "lib.h" // Bao gồm các định nghĩa và khai báo chung từ thư viện tự định nghĩa.

using namespace std; // Sử dụng không gian tên std để truy cập các tính năng chuẩn C++ dễ dàng hơn.

class sound : LTexture // Lớp sound kế thừa từ lớp LTexture.
{
public:
    bool init(); // Hàm khởi tạo các tài nguyên âm thanh.

    void Free(); // Hàm giải phóng các tài nguyên âm thanh.

    void playBreath(); // Hàm phát âm thanh hơi thở.

    void playHit(); // Hàm phát âm thanh va chạm.

    void renderSound(); // Hàm hiển thị biểu tượng âm thanh (bật/tắt).

    bool checkSound(); // Hàm kiểm tra tương tác người dùng với biểu tượng âm thanh và đổi trạng thái.

private:
    const short int POS_X = 107; // Vị trí x mặc định của biểu tượng âm thanh trên màn hình.
    const short int POS_Y = 267; // Vị trí y mặc định của biểu tượng âm thanh trên màn hình.
    bool isPlay = 0; // Biến trạng thái âm thanh: 0 là tắt, 1 là bật.
    Mix_Chunk* breath = NULL; // Con trỏ đến âm thanh hơi thở.
    Mix_Chunk* hit = NULL; // Con trỏ đến âm thanh va chạm.
    Mix_Chunk* drop = NULL; // Con trỏ đến âm thanh rơi (không được sử dụng trong chú thích).
    SDL_Rect Mute; // Định nghĩa khu vực hiển thị cho trạng thái âm thanh tắt.
    SDL_Rect Active; // Định nghĩa khu vực hiển thị cho trạng thái âm thanh bật.
};
