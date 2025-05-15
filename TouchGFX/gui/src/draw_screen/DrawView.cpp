#include <gui/draw_screen/DrawView.hpp>
#include <cmath>
#include <touchgfx/hal/HAL.hpp>
#include "stm32f4xx_hal.h"
#include "string.h"
#include "PatternStorage.hpp"


DrawView::DrawView()
    : patternLength(0),
      currentLineIndex(0),
      successVisible(false),
      tickCounter(0),
	  isRegistering(false),
	  patternTempLength(0),
	  registerStage(0),
	  successRegister(false),
	  failRegister(false),
      failedAttempts(0),
      isLockoutActive(false),
      countdownSeconds(30),
      lockoutTickCounter(0)

{
	memset(patternTemp, 0, sizeof(patternTemp));
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
    if (isLockoutActive || successVisible || successRegister || failRegister)
    {
        return;
    }

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
		if (isLockoutActive || successVisible || successRegister || failRegister)
		{
			return;
		}

        if (isRegistering)
            {
        		processRegisterPattern();
            }

        else
        {

        	if (!findPatternMatch(patternBuffer, patternLength)) // sai
        	{
	            hideAllNotifications();

        	    textAreaWrong.setVisible(true);
        	    textAreaWrong.invalidate();

        	    failedAttempts++;

    			if (failedAttempts >= 5)
    			{
    			    isLockoutActive    = true;
    			    countdownSeconds   = 30;
    			    lockoutTickCounter = 0;

    	            hideAllNotifications();
    			    resetLines();
            	    resetPattern();
    	            setAllDotsVisible(false);


    			    // Chỉ hiển thị TextAreaTryAgain
    			    Unicode::snprintf(textAreaTryAgainBuffer, TEXTAREATRYAGAIN_SIZE,
    			                      "Try again in %u seconds", countdownSeconds);
    			    textAreaTryAgain.setVisible(true);
    			    textAreaTryAgain.invalidate();

    			}


        	    resetPattern();
        	    resetLines();
        	}
        	else // đúng
        	{
        		failedAttempts = 0;

	            hideAllNotifications();
        	    resetLines();
        	    resetPattern();

        	    // ẩn 9 dots
        	    setAllDotsVisible(false);

        	    // Hiển thị hộp "True"
        	    boxWithBorderTrue.setVisible(true);
        	    boxWithBorderTrue.invalidate();
        	    textAreaTrue.setVisible(true);
        	    textAreaTrue.invalidate();

        	    successVisible = true;
        	    tickCounter = 0;
        	}

        }
    }
}

void DrawView::processRegisterPattern()
{

    if (registerStage == 0)
    {
        // Lần nhập đầu tiên: lưu tạm pattern
    	memcpy(patternTemp, patternBuffer, patternLength);
    	patternTempLength = patternLength;
    	registerStage = 1;

        hideAllNotifications();
        setAllDotsVisible(true);

        // Hiển thị yêu cầu nhập lại
        textAreaConfirm.setVisible(true);
        textAreaConfirm.invalidate();

        resetPattern();
        resetLines();
    }
    else if (registerStage == 1)
    {
        // Lần nhập xác nhận: so sánh với patternTemp
    	if (patternLength == patternTempLength &&
    		memcmp(patternBuffer, patternTemp, patternLength) == 0)
    	{
            // Pattern trùng, lưu vào flash
        	savePatternToFlash(patternBuffer, patternLength);


            hideAllNotifications();
            resetLines();
            resetPattern();
            setAllDotsVisible(false);

            // Hiển thị thông báo thành công
            textAreaConfirmSuccess.setVisible(true);
            textAreaConfirmSuccess.invalidate();
            boxWithBorderTrue.setVisible(true);
            boxWithBorderTrue.invalidate();

            isRegistering = false;
            registerStage = 0;


            // Bật cờ successVisible kết quả thành công và reset bộ đếm tick
             successRegister = true;
             tickCounter = 0;
        }
        else
        {
            hideAllNotifications();
            resetLines();
            resetPattern();
            setAllDotsVisible(false);

            // Sai pattern, yêu cầu nhập lại
            textAreaConfirmFail.setVisible(true);
            textAreaConfirmFail.invalidate();
            boxWithBorderTrue.setVisible(true);
            boxWithBorderTrue.invalidate();

            // Báo lỗi và quay lại stage đầu tiên
            failRegister = true;
            registerStage = 0;
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
    if (isLockoutActive)
    {
        // Chạy tick (mỗi tick ~1/60 giây)
        lockoutTickCounter++;
        if (lockoutTickCounter >= 60) // 60 ticks = ~1 giây
        {
            lockoutTickCounter = 0;
            if (countdownSeconds > 0)
            {
                countdownSeconds--;
                Unicode::snprintf(textAreaTryAgainBuffer, TEXTAREATRYAGAIN_SIZE,
                                  "Try again in %u seconds", countdownSeconds);
			    textAreaTryAgain.setVisible(true);
                textAreaTryAgain.invalidate();
            }
            else
            {
                // Hết thời gian, mở khóa
                isLockoutActive  = false;
                failedAttempts   = 0;
                countdownSeconds = 30;

                hideAllNotifications();

                // Reset tất cả về trạng thái ban đầu
                resetPattern();
                resetLines();

                setAllDotsVisible(true);

                textAreaStart.setVisible(true);
                textAreaStart.invalidate();
            }
        }
    }

    if (successRegister)
    {
        tickCounter++;
        if (tickCounter >= 150)
        {
            // 2,5 giây đã trôi qua, reset giao diện về màn pattern nhập
        	successRegister = false;
            tickCounter = 0;

            hideAllNotifications();
            setAllDotsVisible(true);
            textAreaStart.setVisible(true);
            textAreaStart.invalidate();

            // Reset dữ liệu pattern và ẩn tất cả đường vẽ
            resetPattern();
            resetLines();
        }
    }

    if (failRegister)
    {
        tickCounter++;
        if (tickCounter >= 150)
        {
            // 2,5 giây đã trôi qua, reset giao diện về màn pattern nhập
        	failRegister = false;
            tickCounter = 0;
            hideAllNotifications();
            setAllDotsVisible(true);
            textAreaRegister.setVisible(true);
            textAreaRegister.invalidate();
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
	successVisible = false;
	isLockoutActive = false;
	successRegister = false;
	failRegister = false;

	isRegistering = true;
	registerStage = 0;  // reset trạng thái đăng ký
    resetPattern();
    resetLines();

	memset(patternTemp, 0, sizeof(patternTemp));
	hideAllNotifications();
	setAllDotsVisible(true);

    textAreaRegister.setVisible(true);
    textAreaRegister.invalidate();
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

    textAreaRegister.setVisible(false);
    textAreaRegister.invalidate();

    textAreaConfirm.setVisible(false);
    textAreaConfirm.invalidate();

    textAreaConfirmSuccess.setVisible(false);
    textAreaConfirmSuccess.invalidate();

    textAreaConfirmFail.setVisible(false);
    textAreaConfirmFail.invalidate();

    textAreaTryAgain.setVisible(false);
    textAreaTryAgain.invalidate();

    textAreaDeleteAll.setVisible(false);
    textAreaDeleteAll.invalidate();

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


