#include <gui/draw_screen/DrawView.hpp>
#include <cmath>
#include <touchgfx/hal/HAL.hpp>

DrawView::DrawView()
    : patternLength(0),
      currentLineIndex(0),
      successVisible(false),
      tickCounter(0)
{
}

void DrawView::setupScreen()
{
    DrawViewBase::setupScreen();
    // Khi vào màn hình, reset hoàn toàn state
    resetPattern();
    resetLines();
}

void DrawView::tearDownScreen()
{
    DrawViewBase::tearDownScreen();
}

// Xóa dữ liệu pattern
void DrawView::resetPattern()
{
    patternLength = 0;
    for (int i = 0; i < 9; i++)
    {
        pointUsed[i] = false;
    }
}

// Ẩn tất cả các đường vẽ
void DrawView::resetLines()
{
    for (int i = 0; i < 10; i++)
    {
        lineBoxList[i].setVisible(false);
        lineBoxList[i].invalidate();
    }
    currentLineIndex = 0;
}

void DrawView::addPointToPattern(uint8_t index)
{
    if (!pointUsed[index] && patternLength < 9) {
        patternBuffer[patternLength++] = index + 1; // lưu từ 1–9
        pointUsed[index] = true;
        drawLineBetweenLastTwoDots();
    }
}
// Vẽ line nối giữa 2 nút
void DrawView::drawLineBetweenLastTwoDots()
{
    if (patternLength < 2 || currentLineIndex >= 10) return;

    int fromIdx = patternBuffer[patternLength - 2] - 1;
    int toIdx   = patternBuffer[patternLength - 1] - 1;

    int x1 = dotX[fromIdx] + 15;
    int y1 = dotY[fromIdx] + 15;
    int x2 = dotX[toIdx] + 15;
    int y2 = dotY[toIdx] + 15;

    // Cập nhật vị trí và style
    lineBoxList[currentLineIndex].setLine(x1, y1, x2, y2);
    lineBoxList[currentLineIndex].setLineWidth(4);
    lineBoxList[currentLineIndex].setColor(0x0000); // RGB565 xanh

    // Hiển thị dòng
    lineBoxList[currentLineIndex].setVisible(true);
    remove(lineBoxList[currentLineIndex]);
    add(lineBoxList[currentLineIndex]);
    lineBoxList[currentLineIndex].invalidate();

    currentLineIndex++;
}

void DrawView::handleDragEvent(const touchgfx::DragEvent& evt)
{
    int x = evt.getNewX();
    int y = evt.getNewY();
    for (int i = 0; i < 9; i++) {
        int dx = x - (dotX[i] + 15);
        int dy = y - (dotY[i] + 15);
        if (dx*dx + dy*dy < 225) {
            addPointToPattern(i);
        }
    }
}

void DrawView::handleClickEvent(const touchgfx::ClickEvent& evt)
{
    if (evt.getType() == touchgfx::ClickEvent::RELEASED)
    {
    	// Đang fix cứng là >= 3 nút là đúng, thay bằng hàm check pattern đúng chưa nhé

        if (patternLength <= 3) // Nếu sai (thay hàm check vào chỗ này) => hiển thị cảnh báo sai
        {
            textAreaWrong.setVisible(true);
            textAreaWrong.invalidate();
            textAreaStart.setVisible(false);
            textAreaStart.invalidate();

            resetPattern();
            resetLines();
        }
        else // patternLength >= 4  => coi là đúng, hiển thị “True” trong 5s
        {
            // Ẩn thông báo Wrong , và ẩn hướng dẫn Start
            textAreaWrong.setVisible(false);
            textAreaWrong.invalidate();
            textAreaStart.setVisible(false);
            textAreaStart.invalidate();
            resetLines();
            // Ẩn 9 dots
            dot1.setVisible(false); dot1.invalidate();
            dot2.setVisible(false); dot2.invalidate();
            dot3.setVisible(false); dot3.invalidate();
            dot4.setVisible(false); dot4.invalidate();
            dot5.setVisible(false); dot5.invalidate();
            dot6.setVisible(false); dot6.invalidate();
            dot7.setVisible(false); dot7.invalidate();
            dot8.setVisible(false); dot8.invalidate();
            dot9.setVisible(false); dot9.invalidate();

            // Hiển thị hộp “True”
            boxWithBorderTrue.setVisible(true);
            boxWithBorderTrue.invalidate();
            textAreaTrue.setVisible(true);
            textAreaTrue.invalidate();

            // Bật cờ successVisible kết quả thành công và reset bộ đếm tick
            successVisible = true;
            tickCounter = 0;
        }
    }
}

void DrawView::handleTickEvent()
{
    // Chỉ quan tâm khi đang hiển thị kết quả thành công
    if (successVisible)
    {
        tickCounter++;
        if (tickCounter >= 300)
        {
            // 5 giây đã trôi qua, reset giao diện về màn pattern nhập
            successVisible = false;
            tickCounter = 0;

            // Ẩn True
            boxWithBorderTrue.setVisible(false);
            boxWithBorderTrue.invalidate();
            textAreaTrue.setVisible(false);
            textAreaTrue.invalidate();

            // Hiển thị lại 9 dots
            dot1.setVisible(true);  dot1.invalidate();
            dot2.setVisible(true);  dot2.invalidate();
            dot3.setVisible(true);  dot3.invalidate();
            dot4.setVisible(true);  dot4.invalidate();
            dot5.setVisible(true);  dot5.invalidate();
            dot6.setVisible(true);  dot6.invalidate();
            dot7.setVisible(true);  dot7.invalidate();
            dot8.setVisible(true);  dot8.invalidate();
            dot9.setVisible(true);  dot9.invalidate();

            // Hiển thị hướng dẫn start
            textAreaStart.setVisible(true);
            textAreaStart.invalidate();

            // Reset dữ liệu pattern và ẩn tất cả đường vẽ
            resetPattern();
            resetLines();
        }
    }

    // Cuối cùng gọi base để TouchGFX tiếp tục phần xử lý tick mặc định
    DrawViewBase::handleTickEvent();
}

void DrawView::enterRegisterMode()
{
	isRegistering = true;
	resetPattern();
	resetLines();

	hideAllNotifications();
	setAllDotsVisible(false);
}

void DrawView::hideAllNotifications()
{
    // Tắt tất cả text area
    textAreaWrong.setVisible(false);
    textAreaWrong.invalidate();

    textAreaStart.setVisible(false);
    textAreaStart.invalidate();

    textAreaTrue.setVisible(false);
    textAreaTrue.invalidate();

    // Tắt các hộp viền
    boxWithBorderTrue.setVisible(false);
    boxWithBorderTrue.invalidate();
}


void DrawView::setAllDotsVisible(bool visible)
{
    dot1.setVisible(visible);  dot1.invalidate();
    dot2.setVisible(visible);  dot2.invalidate();
    dot3.setVisible(visible);  dot3.invalidate();
    dot4.setVisible(visible);  dot4.invalidate();
    dot5.setVisible(visible);  dot5.invalidate();
    dot6.setVisible(visible);  dot6.invalidate();
    dot7.setVisible(visible);  dot7.invalidate();
    dot8.setVisible(visible);  dot8.invalidate();
    dot9.setVisible(visible);  dot9.invalidate();
}
