/**
 * @author Ali Mirmohammad
 * @file help.hpp
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

#ifndef __NOVANIX_KERNEL_HELP_H
#define __NOVANIX_KERNEL_HELP_H


#define HELP_MENU " \n help : Show this help message and exit\n shutdown-now : Shut down the system \n initfile [filename] Make a new file\n time: get the current time of the system\n clear : clean the terminal \n pwd : Show the current directory \n time: Show the current time for system. \n halt : halt and stop the system. \n version: Show the latest kernel version. \n tasks-show: Show the running tasks. \n cowsay : An interesting command. \n cal : show the calendar. \n hawk : Nova OS file editor. \n mkdir : Make a new directory. \n motd: Get the message of the day. \n pci : Show the pci devices. \n" 
#define SUDO_HELP_MENU "\nset-password : Set and change sudo password\n sudo-su : Gain super user access\n sudo-reset : Reset the SUDO access. \n"

#endif /*__NOVANIX_KERNEL_HELP_H*/