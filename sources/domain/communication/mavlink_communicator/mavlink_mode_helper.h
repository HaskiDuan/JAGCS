#ifndef MAVLINK_MODE_HELPER_H
#define MAVLINK_MODE_HELPER_H

// MAVLink
#include <mavlink.h>

// Qt
#include <QString>

namespace domain
{
    QString decodeApmMode(uint8_t type, uint32_t mode)
    {
        switch (type)
        {
        case MAV_TYPE_FIXED_WING:
            if (mode == 0) return QT_TRANSLATE_NOOP("MAVLINK", "MANUAL");
            if (mode == 1) return QT_TRANSLATE_NOOP("MAVLINK", "CIRCLE");
            if (mode == 2) return QT_TRANSLATE_NOOP("MAVLINK", "STABILIZE");
            if (mode == 3) return QT_TRANSLATE_NOOP("MAVLINK", "TRAINING");
            if (mode == 4) return QT_TRANSLATE_NOOP("MAVLINK", "ACRO");
            if (mode == 5) return QT_TRANSLATE_NOOP("MAVLINK", "FBWA");
            if (mode == 6) return QT_TRANSLATE_NOOP("MAVLINK", "FBWB");
            if (mode == 7) return QT_TRANSLATE_NOOP("MAVLINK", "CRUISE");
            if (mode == 8) return QT_TRANSLATE_NOOP("MAVLINK", "AUTOTUNE");
            if (mode == 10) return QT_TRANSLATE_NOOP("MAVLINK", "AUTO");
            if (mode == 11) return QT_TRANSLATE_NOOP("MAVLINK", "RETURN");
            if (mode == 12) return QT_TRANSLATE_NOOP("MAVLINK", "LOITER");
            if (mode == 14) return QT_TRANSLATE_NOOP("MAVLINK", "AVOID ADSB");
            if (mode == 15) return QT_TRANSLATE_NOOP("MAVLINK", "GUIDED");
            if (mode == 16) return QT_TRANSLATE_NOOP("MAVLINK", "INITIALISING");
            if (mode == 17) return QT_TRANSLATE_NOOP("MAVLINK", "QSTABILIZE");
            if (mode == 18) return QT_TRANSLATE_NOOP("MAVLINK", "QHOVER");
            if (mode == 19) return QT_TRANSLATE_NOOP("MAVLINK", "QLOITER");
            if (mode == 20) return QT_TRANSLATE_NOOP("MAVLINK", "QLAND");
            if (mode == 21) return QT_TRANSLATE_NOOP("MAVLINK", "QRTL");
            return QT_TRANSLATE_NOOP("MAVLINK", "APM PLANE NONE");
        case MAV_TYPE_TRICOPTER:
        case MAV_TYPE_QUADROTOR:
        case MAV_TYPE_HEXAROTOR:
        case MAV_TYPE_OCTOROTOR:
        case MAV_TYPE_COAXIAL:
        case MAV_TYPE_HELICOPTER:
            if (mode == 0) return QT_TRANSLATE_NOOP("MAVLINK", "STABILIZE");
            if (mode == 1) return QT_TRANSLATE_NOOP("MAVLINK", "ACRO");
            if (mode == 2) return QT_TRANSLATE_NOOP("MAVLINK", "ALT HOLD");
            if (mode == 3) return QT_TRANSLATE_NOOP("MAVLINK", "AUTO");
            if (mode == 4) return QT_TRANSLATE_NOOP("MAVLINK", "GUIDED");
            if (mode == 5) return QT_TRANSLATE_NOOP("MAVLINK", "LOITER");
            if (mode == 6) return QT_TRANSLATE_NOOP("MAVLINK", "RETURN");
            if (mode == 7) return QT_TRANSLATE_NOOP("MAVLINK", "CIRCLE");
            if (mode == 9) return QT_TRANSLATE_NOOP("MAVLINK", "LAND");
            if (mode == 11) return QT_TRANSLATE_NOOP("MAVLINK", "DRIFT");
            if (mode == 13) return QT_TRANSLATE_NOOP("MAVLINK", "SPORT");
            if (mode == 14) return QT_TRANSLATE_NOOP("MAVLINK", "FLIP");
            if (mode == 15) return QT_TRANSLATE_NOOP("MAVLINK", "AUTOTUNE");
            if (mode == 16) return QT_TRANSLATE_NOOP("MAVLINK", "POS HOLD");
            if (mode == 17) return QT_TRANSLATE_NOOP("MAVLINK", "BRAKE");
            if (mode == 18) return QT_TRANSLATE_NOOP("MAVLINK", "THROW");
            if (mode == 19) return QT_TRANSLATE_NOOP("MAVLINK", "AVOID ADSB");
            if (mode == 20) return QT_TRANSLATE_NOOP("MAVLINK", "GUIDED NO SNS");
        default:
            break;
        }

        return QT_TRANSLATE_NOOP("MAVLINK", "APM NONE");
    }

    QString decodeCustomMode(uint8_t ap, uint8_t type, uint32_t mode)
    {
        switch (ap)
        {
        case MAV_AUTOPILOT_ARDUPILOTMEGA:
            return decodeApmMode(type, mode);
            break;
        default:
            break;
        }

        return QT_TRANSLATE_NOOP("MAVLINK", "NONE");
    }
}

#endif // MAVLINK_MODE_HELPER_H
