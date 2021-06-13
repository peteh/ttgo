#include "AbstractApp.h"
#include "MainMenuApp.h"
#include <Log.h>
namespace app
{
    volatile bool AbstractApp::s_powerInterrupt = false;

    void AbstractApp::setup()
    {
        getWatch()->motor_begin();

        // add interrupt to handle button presses
        pinMode(AXP202_INT, INPUT_PULLUP);
        attachInterrupt(
            AXP202_INT, []
            { s_powerInterrupt = true; },
            FALLING);

        //!Clear IRQ unprocessed  first
        getWatch()->power->enableIRQ(AXP202_PEK_SHORTPRESS_IRQ | AXP202_VBUS_REMOVED_IRQ | AXP202_VBUS_CONNECT_IRQ | AXP202_CHARGING_IRQ, true);
        getWatch()->power->clearIRQ();
        setupApp();
    }



    const char *AbstractApp::loop()
    {
        m_buttonWasPressed = false;

        if (s_powerInterrupt)
        {
            s_powerInterrupt = false;
            getWatch()->power->readIRQ();
            if (getWatch()->power->isVbusPlugInIRQ())
            {
                Log::debug("Power plugged in");
            }
            if (getWatch()->power->isVbusRemoveIRQ())
            {
                Log::debug("Removed power");
            }
            if (getWatch()->power->isPEKShortPressIRQ())
            {
                Log::debug("Button pressed");
                m_buttonWasPressed = true;
            }
            getWatch()->power->clearIRQ();
        }

        if(m_buttonWasPressed)
        {
            return MainMenuApp::ID;
        }

        // TODO: try to handle gestures here
        // TODO: handle exit of app here too
        return loopApp();
    }

    void AbstractApp::tearDown()
    {
        tearDownApp();
    }
}