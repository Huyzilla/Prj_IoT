#ifndef DRAWVIEW_HPP
#define DRAWVIEW_HPP

#include <gui_generated/draw_screen/DrawViewBase.hpp>
#include <gui/draw_screen/DrawPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/events/DragEvent.hpp>
#include <touchgfx/events/ClickEvent.hpp>
#include "gui/draw_screen/LineWidget.hpp" // widget này tự viết thêm để vẽ line, không có sẵn

class DrawView : public DrawViewBase
{
public:
    DrawView();
    virtual ~DrawView() {}

    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void handleDragEvent(const touchgfx::DragEvent& evt);
    virtual void handleClickEvent(const touchgfx::ClickEvent& evt) override;
    virtual void handleTickEvent() override;

    void enterRegisterMode();


protected:
    void addPointToPattern(uint8_t dotIndex);
    void drawLineBetweenLastTwoDots();
    void resetPattern();
    void resetLines();
    void setAllDotsVisible(bool visible);
    void hideAllNotifications();
    void processRegisterPattern();

    uint8_t patternBuffer[9];
    bool pointUsed[9];
    uint8_t patternLength;

    // Tọa độ các Dot
    int dotX[9] = {27, 105, 182, 27, 105, 182, 27, 105, 182};
    int dotY[9] = {136, 136, 136, 194, 194, 194, 254, 254, 254};

    // Line bằng LineWidget
    LineWidget lineBoxList[10];
    uint8_t currentLineIndex;

    // Các biến mới để quản lý thời gian hiển thị thông báo thành công
    bool successVisible;        // = true khi đang hiển thị hộp 'True'
    uint16_t tickCounter;       // Đếm số tick

    bool isRegistering ; // kiểm tra trạng thái đăng ký
    uint8_t patternTemp[9];  // lưu pattern đăng ký lần đầu
    uint8_t patternTempLength;
    int registerStage;       // trạng thái đăng ký: 0 - chưa nhập, 1 - đã nhập lần 1
    bool successRegister;
    bool failRegister;

    // Số lần nhập sai liên tiếp
    uint8_t failedAttempts;
    // Đang ở trạng thái khóa (đếm ngược)
    bool isLockoutActive;
    // Số giây còn lại trong đếm ngược
    uint16_t countdownSeconds;
    // Đếm tick để quy đổi sang giây
    uint16_t lockoutTickCounter;


};

#endif // DRAWVIEW_HPP
