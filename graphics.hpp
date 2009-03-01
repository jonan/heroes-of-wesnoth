/*
This file is part of Heroes of Wesnoth.
Copyright (C) 2007, 2008, 2009 Jon Ander Peñalba <jonan88@gmail.com>

Heroes of Wesnoth is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License version 3 as
published by the Free Software Foundation.

Heroes of Wesnoth is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>
*/

/// @file
/// The Graphics class and global graphics variables.
/// @author Jonan

#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <SDL/SDL.h>

#include "macros.hpp"

/// All functions that operate directly with the video.
namespace video_engine {

// @{
/// Alpha values
const int OPAQUE = 255;
const int TRANSPARENT = 0;
// @}

/// Mirror
enum {NONE, X, Y};

/// Type of effects
enum {HORIZONTAL, VERTICAL, NUMBER_OF_EFFECTS, RANDOM};

/// Sides to face
enum {RIGHT, LEFT};

/// Complete screen control.
/// This class gives you all the control you need over the screen.
/// The game is played in one screen so there should
/// only be one object of this type.
class Graphics {
  public:
    static Graphics* getInstance(void); // Singleton pattern constructor
    ~Graphics(void); // Destructor

    /// Creates the surface that will be drawn directly to the screen.
    /// @param[in] fullscreen Indicates if it's supposed to run on fullscreen.
    /// @param[in] width Screen's width.
    /// @param[in] height Screen's height.
    void createWindow(const bool fullscreen, int width, int height);

    /// Loads an image for further use.
    /// @param[in] image_name The image's name, without the "img/" or the ".png".
    /// @param[in] alpha Alpha value of the image (0 transparent - 255 opaque).
    /// @param[in] mirror Indicates if the image is a mirror of the original.
    /// @param[in] angle Number of degrees the image is rotated.
    void newImage(const char *image_name, const int alpha = OPAQUE,
                  const int mirror = NONE, const int angle = 0);
    /// Returns the surface of an image.
    /// Looks for the image in the list of loaded
    /// ones, if it's not there it loads it.
    /// @param[in] image_name The image's name, without the "img/" or the ".png".
    /// @param[in] alpha Alpha value of the image (0 transparent - 255 opaque).
    /// @param[in] mirror Indicates if the image is a mirror of the original.
    /// @param[in] angle Number of degrees the image is rotated.
    /// @return Surface of the image.
    SDL_Surface* getImage(const char *image_name, const int alpha = OPAQUE,
                          const int mirror = NONE, const int angle = 0);
    /// Makes an image face the given side.
    /// @param[in] side Side to face (RIGHT or LEFT)
    /// @param[in] image_surface Original image.
    /// @return The same image facing the given side.
    SDL_Surface* face(const int side, SDL_Surface *image_surface);

    /// Changes the size of the actual screen.
    /// This function should only be called inside the
    /// Events class after a SDL_VIDEORESIZE event.
    /// @param[in] width New screen width.
    /// @param[in] height New screen height.
    void resize(const int width, const int height);
    /// Returns the actual screen's size.
    /// @param[out] width The screen's width.
    /// @param[out] height The screen's height.
    void getScreenSize(int &width, int &height);

    /// Draws an image to the indicated position.
    /// Before drawing looks for the image in the list
    /// of loaded ones, if it's not there it loads it.
    /// @param[in] image_name The image's name, without the "img/" or the ".png".
    /// @param[in] position Position where the image will be drawn.
    void draw(const char *image_name, SDL_Rect &position);
    /// Draws a surface to the indicated position.
    /// @param[in] img The images's surface.
    /// @param[in] position Position where the image will be drawn.
    void draw(SDL_Surface *img, SDL_Rect &position);

    /// Writes text in the screen.
    /// @param[in] text Text to be writen.
    /// @param[in] x The x coordinate of the top left corner of the text.
    /// @param[in] y The y coordinate of the top left corner of the text.
    void write(const char *text,  const int x, const int y);
    /// Writes text in the screen.
    /// The text is centered in between the given positions.
    /// @param[in] text A string with the text to write.
    /// @param[in] left_x The x coordinate of the left margen of the text.
    /// @param[in] right_x The x coordinate of the right margen of the text.
    /// @param[in] top_y The y coordinate of the top margen of the text.
    /// @param[in] bottom_y The y coordinate of the bottom margen of the text.
    void writeCentered(const char *text,
                       const int left_x, const int right_x,
                       const int top_y, const int bottom_y);

    /// Puts the screen black.
    void erase(void);
    /// Refreshes the screen.
    void update(void);

    /// Refreshes the screen with an especial effect.
    /// @param[in] effect Type of effect to use.
    void transitionEffect(int effect);

  private:
    class Image;
    class ImageList;
    class Ttf;

    Graphics(void); // Constructor

    // Initializes SDL and SDL_ttf.
    void init(void);

    Uint32 SDL_flags; // SDL flags of the actual screen
    SDL_Surface *screen; // The surface that represents the screen
    int width, height, bpp; // The screen's witdh, height and bpp
    ImageList *images; // List with all the images used
    Ttf *text; // Used to write text into the screen

    DISALLOW_COPY_AND_ASSIGN(Graphics);
};

extern Graphics *screen;

} // namespace video_engine

#endif // GRAPHICS_HPP
