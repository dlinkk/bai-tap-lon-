#include "bird.h" // Bao gồm tệp tiêu đề 'meo.h' vào chương trình.
#include <stdio.h> // Bao gồm thư viện chuẩn của C cho việc nhập xuất.
#include <iostream> // Bao gồm thư viện C++ cho việc nhập xuất.

// Định nghĩa hàm khởi tạo cho lớp bird
bool bird::init(bool isDark)
{
    string character_path = "res/image/cangu.png"; // Đường dẫn mặc định cho hình ảnh.
    if (isDark) character_path = "res/image/canigga.png"; // Đổi đường dẫn nếu là chế độ tối.
    if (saved_path == character_path) // Kiểm tra nếu đường dẫn đã được lưu trước đó.
    {
        posBird.getPos(75, SCREEN_HEIGHT / 2 - 10); // Lấy vị trí ban đầu cho mèo.
        ahead = 0; // Đặt chỉ số ống tiếp theo là 0.
        angle = 0; // Đặt góc xoay ban đầu là 0.
    }
    if (isNULL() || saved_path != character_path) // Kiểm tra nếu đường dẫn chưa được lưu hoặc đã thay đổi.
    {
        saved_path = character_path; // Lưu đường dẫn mới.
        if ( Load(character_path.c_str() , 1) ) // Tải hình ảnh từ đường dẫn.
        {
            return true; // Trả về true nếu tải thành công.
        }
        else
        {
            return false; // Trả về false nếu tải không thành công.
        }

    }
    return false; // Trả về false nếu không có thay đổi nào cần thiết.
}

void bird::Free() // Hàm giải phóng tài nguyên.
{
    free(); // Gọi hàm free để giải phóng.
}

void bird::render() // Hàm để vẽ mèo lên màn hình.
{
    Render(posBird.x, posBird.y, angle); // Vẽ mèo tại vị trí và góc được chỉ định.
}

void bird::fall() // Hàm mô tả hành vi rơi của chim.
{
    if (die && posBird.y < SCREEN_HEIGHT - LAND_HEIGHT - CHARACTER_HEIGHT - 5) // Kiểm tra nếu chim đã chết và vẫn chưa chạm đất.
    {
        if (time == 0) // Nếu là lần đầu tiên rơi.
        {
            x0 = posBird.y; // Lưu vị trí y ban đầu.
            angle = -25; // Đặt góc nghiêng ban đầu.
        }
        else if (angle < 70 && time > 30) // Điều kiện để tăng góc nghiêng.
        {
            angle += 3; // Tăng góc nghiêng.
        }

        if (time >= 0) // Nếu thời gian vẫn còn.
        {
            posBird.y = x0 + time * time * 0.18 - 7.3 * time; // Tính vị trí y mới theo thời gian.
            time++; // Tăng thời gian.
        }
    }
    else return; // Trả về nếu không có điều kiện nào được thỏa mãn.
}

void bird::update(short int pipeWidth, short int pipeHeight) // Hàm cập nhật trạng thái và vị trí của chim.
{
    if (!die) // Kiểm tra nếu chim chưa chết.
    {
        if (time == 0) // Nếu là lần đầu tiên cập nhật.
        {
            x0 = posBird.y; // Lưu vị trí y ban đầu.
            angle = -25; // Đặt góc nghiêng ban đầu.
        }
        else if (angle < 70 && time > 30) // Điều kiện để tăng góc nghiêng.
        {
            angle += 3; // Tăng góc nghiêng.
        }

        if (time >= 0) // Nếu thời gian vẫn còn.
        {
            posBird.y = x0 + time * time * 0.18 - 7.3 * time; // Tính vị trí y mới theo thời gian.
            time++; // Tăng thời gian.
        }

        if ( (posBird.x + getWidth() > posPipe[ahead].x + 5) && (posBird.x + 5 < posPipe[ahead].x + pipeWidth) &&
             (posBird.y + 5 < posPipe[ahead].y + pipeHeight || posBird.y  + getHeight() > posPipe[ahead].y + pipeHeight + PIPE_SPACE + 5) )
        {
            die = true; // Đánh dấu chim đã chết nếu chạm vào ống.
        }
        else if (posBird.x > posPipe[ahead].x + pipeWidth )
        {
            ahead = ( ahead + 1 ) % TOTAL_PIPE; // Chuyển sang ống tiếp theo.
            score++; // Tăng điểm.
        }

        if (posBird.y > SCREEN_HEIGHT - LAND_HEIGHT -  CHARACTER_HEIGHT - 5 || posBird.y < - 10 )
        {
            die = true; // Đánh dấu chim đã chết nếu rơi ra khỏi màn hình hoặc chạm đất.
        }
    }
}
