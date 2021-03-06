#pragma once

#include "AbstractApp.h"
#include <LilyGoWatch.h>

namespace app
{
    class WifiSettingsApp : public AbstractApp
    {
    public:
        static const char ID[];
        static WifiSettingsApp *instance();

        WifiSettingsApp();
        virtual void setupApp() override;
        virtual const char *loopApp() override;
        virtual ~WifiSettingsApp();

    private:
        static WifiSettingsApp *s_instance;

        static void _internalEventHandler(lv_obj_t *obj, lv_event_t event)
        {
            if(s_instance == nullptr)
            {
                Log::error("Instance already destroyed but events are coming in");
                return;
            }
            instance()->buttonEventHandler(obj, event);
        }

        void buttonEventHandler(lv_obj_t *obj, lv_event_t event);
        void createKeyboard();
        void scanWifi();

        lv_obj_t *m_btnScan;
        lv_obj_t *m_btnConnect;
        lv_obj_t *m_rollerWifiSSID;
        lv_obj_t *m_textPassword;
        lv_obj_t *m_keyboard;
        lv_obj_t *m_labelPassword;
    };
}