/**
 * @author Ali Mirmohammad
 * @file directorylisting.h
 * @credits Remco123
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
#ifndef __Novanix__SYSTEM__LISTINGS__DIRECTORYLISTING_H
#define __Novanix__SYSTEM__LISTINGS__DIRECTORYLISTING_H

#include <system/listings/listingcontroller.h>

namespace Novanix
{
    namespace system
    {
        // A class that is responsable for processes which request a directory list
        class DirectoryListing : public ListingController
        {
        public:
            /**
            Create new instance of DirectoryListing
            */
            DirectoryListing();

            /**
            Begin processing a new directorylist request
            Returns amount of items in directory
            */
            int BeginListing(Thread* thread, uint32_t pathPtr) override;
            /**
            Get an item from the current request.
            Returns characters in file/dirname
            */
            int GetEntry(Thread* thread, int entry, uint32_t bufPtr) override;
            /**
            End the current listing
            */
            void EndListing(Thread* thread) override;
        };
    }
}

#endif