/**
 * @author Ali Mirmohammad
 * @file ipc.h
 * @credits remco123
 ** This file is part of Novanix.

**Novanix is free software: you can redistribute it and/or modify
**it under the terms of the GNU Affero General Public License as published by
**the Free Software Foundation, either version 3 of the License, or
**(at your option) any later version.

**Novanix is distributed in the hope that it will be useful,
**but WITHOUT ANY WARRANTY; without even the implied warranty of
**MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
**GNU Affero General Public License for more details.

**You should have received a copy of the GNU Affero General Public License
**along with Novanix. If not, see <https://www.gnu.org/licenses/>.
*/
#ifndef __Novanix__IPC_H
#define __Novanix__IPC_H

namespace Novanix
{
    enum IPCMessageType : int
    {
        None = 0,
        GUIRequest = 1,
        GUIEvent = 2
    };

    struct IPCMessage
    {
        int source; // Who has sended this message?
        int dest;   // Who is it for
        
        int type; // What type of message is it?

        // Arguments
        unsigned int arg1;
        unsigned int arg2;
        unsigned int arg3;
        unsigned int arg4;
        unsigned int arg5;
        unsigned int arg6;
    };

    /**
     * Send a message to a other process
    */
    int IPCSend(int dest, int type = IPCMessageType::None, unsigned int arg1 = 0, unsigned int arg2 = 0, unsigned int arg3 = 0, unsigned int arg4 = 0, unsigned int arg5 = 0, unsigned int arg6 = 0);
    /**
     * Send a message to a other process
    */
    int IPCSend(IPCMessage message);

    /**
     * How many messages are ready for receiving?
    */
    int IPCAvailable();

    /**
     * Receive a single IPCMessage, blocks if none availible
     * FromID: Only receive a message from specified process
    */
    IPCMessage ICPReceive(int fromID = -1, int* errOut = 0, int type = -1);
}

#endif