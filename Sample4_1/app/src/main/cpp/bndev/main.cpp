#include <jni.h>
#include <errno.h>
#include <vulkan/vulkan.h>
#include <GLES/gl.h>
#include <EGL/egl.h>
#include <android_native_app_glue.h>
#include "help.h"
#include "MyVulkanManager.h"


extern "C"
{

static int32_t engine_handle_input(struct android_app *app, AInputEvent *event) {//事件处理回调方法
    if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION) {        //如果是MOTION事件
        if (AInputEvent_getSource(event) == AINPUT_SOURCE_TOUCHSCREEN) {//如果是触屏
            int x = AMotionEvent_getRawX(event, 0);                        //获取触控点x坐标
            int y = AMotionEvent_getRawY(event, 0);                        //获取触控点y坐标
            int32_t id = AMotionEvent_getAction(event);                    //获取事件类型编号
            switch (id) {
                case AMOTION_EVENT_ACTION_DOWN:                    //触控点按下
                    MyVulkanManager::vpCenterX = x;            //设置vpCenterX为触控点x坐标
                    MyVulkanManager::vpCenterY = y;            //设置vpCenterY为触控点y坐标
                    if (x > MyVulkanManager::screenWidth / 4 * 3)        //判断触控点x坐标是否大于允许的最大值
                        MyVulkanManager::vpCenterX = MyVulkanManager::screenWidth / 4 * 3;
                    if (x < MyVulkanManager::screenWidth / 4)        //判断触控点x坐标是否小于允许的最小值
                        MyVulkanManager::vpCenterX = MyVulkanManager::screenWidth / 4;
                    if (y > MyVulkanManager::screenHeight / 4 * 3)        //判断触控点y坐标是否大于允许的最大值
                        MyVulkanManager::vpCenterY = MyVulkanManager::screenHeight / 4 * 3;
                    if (y < MyVulkanManager::screenHeight / 4)        //判断触控点y坐标是否小于允许的最小值
                        MyVulkanManager::vpCenterY = MyVulkanManager::screenHeight / 4;
                    break;
                case AMOTION_EVENT_ACTION_MOVE:
                    break;    //触控点移动
                case AMOTION_EVENT_ACTION_UP:
                    break;        //触控点抬起
            }
        }
        return true;
    }
    return false;
}


static void engine_handle_cmd(struct android_app *app, int32_t cmd) {

    switch (cmd) {
        case APP_CMD_SAVE_STATE:
            LOGI("APP_CMD_SAVE_STATE");
            break;
        case APP_CMD_INIT_WINDOW:
            MyVulkanManager::doVulkan();
            LOGI("APP_CMD_INIT_WINDOW");
            break;
        case APP_CMD_TERM_WINDOW:
            LOGI("APP_CMD_TERM_WINDOW");
            break;
        case APP_CMD_GAINED_FOCUS:
            LOGI("APP_CMD_GAINED_FOCUS");
            break;
        case APP_CMD_LOST_FOCUS:
            MyVulkanManager::loopDrawFlag = false;
            LOGI("APP_CMD_LOST_FOCUS");
            break;
    }
}

void android_main(struct android_app *app) {

    app_dummy();
    MyVulkanManager::Android_application = app;
    MyData md;

    app->userData = &md;

    app->onAppCmd = engine_handle_cmd;

    app->onInputEvent = engine_handle_input;

    md.app = app;

    bool beginFlag = false;
    while (true) {
        int events;
        struct android_poll_source *source;


        while ((ALooper_pollAll((beginFlag ? 0 : -1), NULL, &events, (void **) &source)) >= 0) {
            beginFlag = true;

            if (source != NULL) {
                source->process(app, source);
            }
        }
    }
}


}
