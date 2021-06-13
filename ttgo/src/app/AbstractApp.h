#pragma once
#include "App.h"
#include "../config.h"
#include <LilyGoWatch.h>

namespace app
{
    class AbstractApp : public IApp
    {
    protected:
        AbstractApp()
            : m_watch(TTGOClass::getWatch())
        {
        }

        void vibrateHaptic()
        {
            getWatch()->motor->onec(30);
        }

        virtual TTGOClass *getWatch()
        {
            return m_watch;
        }

        virtual void setup();
        
        virtual const char* loop();

        virtual void tearDown();

        // may be implemented by app
        virtual void setupApp()
        {
            
        }

        // must be implemented by app
        virtual const char* loopApp() = 0;

        // may be implemented by app
        virtual void tearDownApp()
        {

        }

        virtual ~AbstractApp()
        {
            
        }

    private:
        static volatile bool s_powerInterrupt;
        TTGOClass *m_watch;


        bool m_buttonWasPressed;
    };
}