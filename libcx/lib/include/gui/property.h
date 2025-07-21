/**
 * @author Ali Mirmohammad
 * @file property.h
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
#ifndef __Novanix__GUI__PROPERTY_H
#define __Novanix__GUI__PROPERTY_H

#include <types.h>

namespace Novanix
{
    class Control;

    template <typename>
    class EventHandlerList;

    // Function to force a control to update its GUI
    // We need this because if we place it in the template we get a lot of warnings
    // This a nice way to fix it
    void UpdateGUIPropertyTargetGUI(Control* target);

    // Property that is used to declare a gui specific variable
    // When this property changes the gui needs to be repainted
    template <typename T>
    class GUIProperty
    {
    friend class Control;
    protected:
        // Value of this property
        T value;

        // Which control is the owner of this property
        Control* parent = 0;
    public:
        // Called when value of this property is changed
        // Make sure this does not create an infinite loop!
        EventHandlerList<T> onChanged;
    public:
        // Create new property with default value and pointer to parent control
        GUIProperty(Control* p, T def) { this->parent = p; this->value = def; }

        // Deconstructor
        ~GUIProperty() { }

        
        // Assignment operator
        GUIProperty& operator=(T newVal)
        {
            this->value = newVal;
            this->onChanged.Invoke(this, this->value);
            UpdateGUIPropertyTargetGUI(this->parent);
            return *this;
        }

        // Increase operator
        GUIProperty& operator+=(T newVal)
        {
            this->value += newVal;
            this->onChanged.Invoke(this, this->value);
            UpdateGUIPropertyTargetGUI(this->parent);
            return *this;
        }

        // Decrease operator
        GUIProperty& operator-=(T newVal)
        {
            this->value -= newVal;
            this->onChanged.Invoke(this, this->value);
            UpdateGUIPropertyTargetGUI(this->parent);
            return *this;
        }

        // Get operator, used for value feedback
        operator T() const
        {
            return this->value;
        }
    };        
}

#endif