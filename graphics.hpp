/*
Heroes of Wesnoth - http://heroesofwesnoth.sf.net
Copyright (C) 2007-2008 Jon Ander Peñalba <jonan88@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License version 3 as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
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
///
/// -no detailed description-
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
///
/// This class gives you all the control you need over the screen.
/// The game is played in one screen so there should
/// only be one object of this type.
class Graphics {
  public:
    /// @param[in] fullscreen Indicates if it's supposed to run on fullscreen.
    /// @param[in] width Screen's width.
    /// @param[in] height Screen's height.
    static Graphics* instance(const bool fullscreen, int width, int height); // Singleton pattern constructor
    ~Graphics(void); // Destructor

    /// Returns the surface of an image.
    ///
    /// Looks for the image in the list of loaded
    /// ones, if it's not there it loads it.
    ///
    /// @param[in] image_name The image's name, without the "img/" or the ".png".
    /// @param[in] alpha Alpha value of the image (0 transparent - 255 opaque).
    /// @param[in] mirror Indicates if the image is a mirror of the original.
    /// @param[in] angle Number of degrees the image is rotated.
    /// @return Surface of the image.
    SDL_Surface* getImage(const char *image_name, const int alpha,
                          const int mirror, const int angle);

    /// Returns the actual screen's size.
    ///
    ///  -no detailed description-
    ///
    /// @param[out] width The screen's width.
    /// @param[out] height The screen's height.
    void getScreenSize(int &width, int &height);

    /// Changes the size of the actual screen.
    ///
    /// This function should only be called inside the
    /// Events class after a SDL_VIDEORESIZE event.
    ///
    /// @param[in] width New screen width.
    /// @param[in] height New screen height.
    void resize(const int width, const int height);

    /// Makes an image face the given side.
    ///
    ///  -no detailed description-
    ///
    /// @param[in] side Side to face.
    /// @param[in] image_surface Original image.
    /// @return The same image facing the given side.
    SDL_Surface* face(const int side, SDL_Surface *image_surface);

    /// Loads an image for further use.
    ///
    /// Adds a new image to the list
    ///
    /// @param[in] image_name The image's name, without the "img/" or the ".png".
    /// @param[in] alpha Alpha value of the image (0 transparent - 255 opaque).
    /// @param[in] mirror Indicates if the image is a mirror of the original.
    /// @param[in] angle Number of degrees the image is rotated.
    void newImage(const char *image_name, const int alpha,
                  const int mirror, const int angle);

    /// Draws an image to the indicated position.
    ///
    /// Before drawing looks for the image in the list
    /// of loaded ones, if it's not there it loads it.
    ///
    /// @param[in] image_name The image's name, without the "img/" or the ".png".
    /// @param[in] position Position where the image will be drawn.
    void draw(const char *image_name, SDL_Rect &position);
    /// Draws a surface to the indicated position.
    ///
    /// -no detailed description-
    ///
    /// @param[in] img The images's surface.
    /// @param[in] position Position where the image will be drawn.
    void draw(SDL_Surface *img, SDL_Rect &position);
    /// Writes text in the screen.
    ///
    /// -no detailed description-
    ///
    /// @param[in] text Text to be writen.
    /// @param[in] x The x coordinate of the top left corner of the text.
    /// @param[in] y The y coordinate of the top left corner of the text.
    void write(const char *text,  const int x, const int y);
    /// Writes text in the screen.
    ///
    /// The text is centered in between the given positions.
    ///
    /// @param[in] text A string with the text to write.
    /// @param[in] left_x The x coordinate of the left margen of the text.
    /// @param[in] right_x The x coordinate of the right margen of the text.
    /// @param[in] top_y The y coordinate of the top margen of the text.
    /// @param[in] bottom_y The y coordinate of the bottom margen of the text.
    void writeCentered(const char *text,
                       const int left_x, const int right_x,
                       const int top_y, const int bottom_y);

    /// Puts the screen black.
    ///
    /// -no detailed description-
    void erase(void);
    /// Refreshes the screen.
    ///
    /// -no detailed description-
    void update(void);

    /// Refreshes the screen with an especial effect.
    ///
    /// -no detailed description-
    ///
    /// @param[in] effect Type of effect to use.
    void transitionEffect(int effect);

    /// Stops the program a number of milisecons.
    ///
    /// -no detailed description-
    ///
    /// @param[in] ms Milisecons to wait.
    void wait(const int ms) {SDL_Delay(ms);}

  private:
    Graphics(const bool fullscreen, int width, int height); // Constructor

    // Initializes SDL, SDL_ttf and SDL_mixer.
    void init(void);
    // Creates the surface that will be drawn directly to the screen.
    void createWindow(const bool fullscreen, int width, int height);

    // Declaration of nested classes
    class Image;
    class ImageList;
    class Ttf;

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
