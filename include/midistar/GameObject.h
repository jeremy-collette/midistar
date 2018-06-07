/*
 * midistar
 * Copyright (C) 2018 Jeremy Collette.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MIDISTAR_GAMEOBJECT_H_
#define MIDISTAR_GAMEOBJECT_H_

#include <vector>

#include "midistar/Component.h"

namespace midistar {
class Game;

/**
 * The GameObject class is used to represent on-screen game objects. Each
 * GameObject owns derived instances of Component, which dictate the
 * GameObject's behaviour and functionality.
 *
 * A GameObject may own one Component of each ComponentType at any given time.
 * Components are added or removed dynamically, which changes the GameObject's
 * behaviour during runtime.
 */
class GameObject {
 public:
    /**
     * Constructor.
     *
     * \param x_pos The X on-screen position of the GameObject
     * \param y_pos The Y on-screen position of the GameObject
     */
    GameObject(double x_pos, double y_pos);

    /**
     * Removes and deletes the Component with the specified ComponentType from
     * the GameObject. This deletes the Component, so be careful if the deleted
     * component is shared among other GameObjects.
     *
     * \param type Specifies the type of the Component to remove and delete.
     */
    void DeleteComponent(ComponentType type);

    /**
     * Gets the Component with the specified ComponentType.
     *
     * \tparam T The derived Component class.
     * \param type The ComponentType of the derived Component class.
     *
     * \return A pointer to the Component with the specified ComponentType.
     */
    template <typename T> T* GetComponent(ComponentType type) {
        return static_cast<T*>(components_[type]);
    }

    /**
     * Gets the position of the GameObject.
     *
     * \param[out] x Stores the X position.
     * \param[out] y Stores the Y position.
     */
    void GetPosition(double* x, double* y);

    /**
     * Gets the request deletion status.
     *
     * \return True if the GameObject has requested deletion. False otherwise.
     */
    bool GetRequestDelete();

    /**
     * Determines whether or not the GameObject has a Component with the
     * ComponentType type.
     *
     * \param type Checks if the GameObject has a Component with this type.
     *
     * \return True if the GameObject has a Component with the specified type.
     * False otherwise.
     */
    bool HasComponent(ComponentType type);

    /**
     * Sets the Component in slot determined by the ComponentType.
     *
     * \param c The Component to set.
     */
    void SetComponent(Component* c);

    /**
     * Sets the position of the GameObject.
     *
     * \param x The new X position.
     * \param y The new Y position.
     */
    void SetPosition(double x, double y);

    /**
     * Sets the request deletion status.
     *
     * \param del The request deletion status. Setting this to true will delete
     * the GameObject (and all its Components) at the end of this tick.
     */
    void SetRequestDelete(bool del);

    /**
     * Updates the GameObject by updating each of its Components.
     *
     * \param g A reference to the current Game instance.
     * \param delta The time in milliseconds since the end of last tick.
     */
    void Update(Game* g, int delta);

 private:
    Component* components_[Component::NUM_COMPONENTS];  //!< Holds components
    bool request_delete_;  //!< Holds deletion request status
    std::vector<Component*> to_delete_;  //!< Holds components to delete
    double x_pos_;  //!< Holds X position
    double y_pos_;  //!< Holds Y position
};

}   // End namespace midistar

#endif  // MIDISTAR_GAMEOBJECT_H_
