#include "sound.h" // Bao gồm tệp tiêu đề cho lớp sound.
#include <stdio.h> // Bao gồm thư viện chuẩn C cho việc nhập xuất.
#include <iostream> // Bao gồm thư viện C++ cho việc nhập xuất.
#include <string> // Bao gồm thư viện chuẩn C++ cho xử lý chuỗi.

bool sound::init() // Hàm khởi tạo cho lớp sound.
{
    string breath_path = "res/sound/flap.mp3"; // Đường dẫn tệp âm thanh cho tiếng thở.
    string hit_path = "res/sound/death.wav"; // Đường dẫn tệp âm thanh cho tiếng va chạm.
    string sound_path = "res/image/sound.png"; // Đường dẫn tệp hình ảnh cho biểu tượng âm thanh.

    bool success = true; // Biến để kiểm tra quá trình khởi tạo có thành công không.

    if (SDL_Init(SDL_INIT_AUDIO) < 0) // Khởi tạo SDL cho âm thanh.
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() ); // In lỗi nếu SDL không khởi tạo được.
        success = false; // Đặt thành công là false.
    }
    else
    {
        if( Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048) < 0 ) // Mở âm thanh với các thông số nhất định.
        {
            printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() ); // In lỗi nếu SDL_mixer không khởi tạo được.
            success = false; // Đặt thành công là false.
        }

        breath = Mix_LoadWAV( breath_path.c_str() ); // Tải âm thanh tiếng thở.
        if ( breath == NULL )
        {
            printf( "Failed to load sound! SDL_mixer Error: %s\n", Mix_GetError() ); // In lỗi nếu tải âm thanh thất bại.
            success = false; // Đặt thành công là false.
        }

        hit = Mix_LoadWAV( hit_path.c_str() ); // Tải âm thanh tiếng va chạm.
        if (hit == NULL)
        {
            printf( "Failed to load chord! SDL_mixer Error: %s\n", Mix_GetError() ); // In lỗi nếu tải âm thanh thất bại.
            success = false; // Đặt thành công là false.
        }

        if (!Load(sound_path)) // Tải hình ảnh biểu tượng âm thanh.
        {
            return false; // Trả về false nếu tải hình ảnh thất bại.
        }

        Active.x = 0; Active.y = 0; Active.w = getWidth(); Active.h = getHeight() / 2; // Thiết lập vùng hiển thị âm thanh đang bật.
        Mute.x = 0; Mute.y = getHeight() / 2; Mute.w = getWidth(); Mute.h = getHeight() / 2; // Thiết lập vùng hiển thị âm thanh đã tắt.
        isPlay = true; // Đặt trạng thái phát âm thanh là true.
    }
    return success; // Trả về kết quả của quá trình khởi tạo.
}

void sound::Free() // Hàm giải phóng tài nguyên âm thanh.
{
    free(); // Gọi hàm giải phóng tài nguyên.

    Mix_FreeChunk(breath); // Giải phóng chunk âm thanh tiếng thở.
    breath = NULL; // Đặt breath là NULL.
    Mix_FreeChunk(hit); // Giải phóng chunk âm thanh tiếng va chạm.
    hit = NULL; // Đặt hit là NULL.

    Mix_Quit(); // Dừng và giải phóng thư viện SDL_mixer.
}

void sound::playBreath() // Hàm phát âm thanh tiếng thở.
{
    if (isPlay) // Kiểm tra nếu âm thanh đang được phát.
    {
        Mix_PlayChannel( -1, breath, 0 ); // Phát âm thanh tiếng thở trên kênh nào đó.
    }
}

void sound::playHit() // Hàm phát âm thanh tiếng va chạm.
{
    if (isPlay) // Kiểm tra nếu âm thanh đang được phát.
    {
        Mix_PlayChannel(-1, hit, 0); // Phát âm thanh tiếng va chạm trên kênh nào đó.
    }
}

void sound::renderSound() // Hàm hiển thị biểu tượng âm thanh tùy vào trạng thái âm thanh đang bật hay tắt.
{
    if (isPlay) // Nếu âm thanh đang bật.
    {
        Render(POS_X, POS_Y, 0, &Active); // Hiển thị biểu tượng âm thanh bật.
    }
    else
    {
        Render(POS_X, POS_Y, 0, &Mute); // Hiển thị biểu tượng âm thanh tắt.
    }
}

bool sound::checkSound() // Hàm kiểm tra xem người dùng có bấm vào biểu tượng âm thanh không và thay đổi trạng thái.
{
    int x, y;
    SDL_GetMouseState(&x, &y); // Lấy vị trí chuột hiện tại.
    if (x > POS_X && x < POS_X + getWidth() &&
        y > POS_Y && y < POS_Y + getHeight()) // Kiểm tra vị trí chuột có nằm trong khu vực biểu tượng âm thanh không.
    {
        isPlay = !isPlay; // Đảo trạng thái âm thanh.
        return true; // Trả về true nếu có thay đổi.
    }
    return false; // Trả về false nếu không có thay đổi.
}
