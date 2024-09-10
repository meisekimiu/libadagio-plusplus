#ifndef GL_ADAGIO_MESSAGEINBOX_H
#define GL_ADAGIO_MESSAGEINBOX_H

#include "../../../event/MessageCollection.h"

struct MessageInbox {
    static constexpr auto in_place_delete = true; // Ensure pointer stability in EnTT
    Adagio::MessageCollection messages;
};

#endif //GL_ADAGIO_MESSAGEINBOX_H
