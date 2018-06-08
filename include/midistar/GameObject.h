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

#include <SFML/Graphics.hpp>
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
     * \param shape Underlying shape.
     * \param x_pos The X on-screen position of the GameObject.
     * \param y_pos The Y on-screen position of the GameObject.
     * \param width The width of the GameObject.
     * \param height The height of the GameObject.
     */
    GameObject(
            sf::Shape* shape
            , double x_pos
            , double y_pos
            , double width
            , double height);

    /**
     * Destructor.
     */
    ~GameObject();

    /**
     * Removes and deletes the Component with the specified ComponentType from
     * the GameObject. This deletes the Component, so be careful if the deleted
     * component is shared among other GameObjects.
     *
     * \param type Specifies the type of the Component to remove and delete.
     */
    void DeleteComponent(ComponentType type);

    /**
     * Draws the GameObject.
     *
     * \param window The window to draw the GameObject in.
     */
    void Draw(sf::RenderWindow& window);

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
     * Gets the drawable component of the GameObject.
     *
     * \return Drawable component.
     */
    sf::Drawable& GetDrawable();
    
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
     * Gets the underlying shape if it exists.
     *
     * \return Underlying shape if it exists. Otherwise nullptr.
     */
    sf::Shape* GetShape();

    /**
     * Gets the size of the GameObject.
     *
     * \param[out] w Stores the width.
     * \param[out[ h Stores the height.
     */
    void GetSize(double* w, double* h);

    /**
     * Gets the underlying sprite if it exists.
     *
     * \return Underlying sprite if it exists. Otherwise nullptr.
     */
    sf::Sprite* GetSprite();

    /**
     * Gets the underlying text if it exists.
     *
     * \return Underlying text if it exists. Otherwise nullptr.
     */
    sf::Text* GetText();

    /**
     * Gets the transformable component of the GameObject.
     *
     * \return Transformable component.
     */
    sf::Transformable& GetTransformable();

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
     * Sets the size of the GameObject.
     *
     * \param w The new width.
     * \param h The new height.
     */
    void SetSize(double w, double h);

    /**
     * Updates the GameObject by updating each of its Components.
     *
     * \param g A reference to the current Game instance.
     * \param delta The time in milliseconds since the end of last tick.
     */
    void Update(Game* g, int delta);

 private:
    GameObject(sf::Drawable* drawable, sf::Transformable* transformable, double 
            x_pos, double y_pos, double width, double height);  //!< Private
                                                             //!< constructor. 

    Component* components_[Component::NUM_COMPONENTS];  //!< Holds components
    sf::Drawable& drawable_;  //!< Holds reference to drawable part of object
    double original_height_;  //!< Height at creation
    double original_width_;  //!< Width at creation
    bool request_delete_;  //!< Holds deletion request status
    sf::Shape* shape_;  //!< Holds underlying shape (if it exists)
    sf::Sprite* sprite_;  //!< Holds underlying sprite (if it exists)
    sf::Text* text_;  //!< Holds underlying text (if it exists)
    std::vector<Component*> to_delete_;  //!< Holds components to delete
    sf::Transformable& transformable_;  //!< Holds transformable part of object
    double x_pos_;  //!< Holds X position
    double y_pos_;  //!< Holds Y position
};

}   // End namespace midistar

#endif  // MIDISTAR_GAMEOBJECT_H_
