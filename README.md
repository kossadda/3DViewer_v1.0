# 3DViewer v1.0

Implementation 3DViewer v1.0.

The Russian version of the README can be found in the repository.

## Contents
1. [Appearance](#appearance)
2. [Project description](#project-description)
3. [Building project](#building-project)
4. [Testing](#testing)
5. [Feedback](#feedback)

<br>

## [Appearance](#3dviewer-v10)

![Viewer](./misc/images/3d_viewer.gif) <br>

## [Project description](#3dviewer-v10)

The goal of this project is to implement a program in the C programming language for viewing 3D models in wireframe form (3D Viewer). The models themselves are loaded from .obj files, making it possible to view them on the screen with the ability to rotate, scale and move.

- The program was developed in the C language of the `C11` standard using the `gcc` compiler. Additional libraries and modules `QT` are used;
- The program code is located in the `src` folder;
- The program build must be configured using `Makefile` with a standard set of targets for GNU programs: `all`, `install`, `uninstall`, `clean`, `dvi`, `dist`, `tests`, `gcov_report` . Installation is carried out in the `bin` folder in the root of the repository;
- The program is developed in accordance with the principles of structured programming;
- The code is written in accordance with `Google Style`;
- Provided unit test coverage of modules related to loading models and affine transformations;
- At one time the program displays only one model on the screen;
- The program provides the opportunity to:
- Load a wireframe model from an obj file (supports only a list of vertices and surfaces);
    - Move the model a specified distance relative to the `X`, `Y`, `Z` axes;
    - Rotate the model at a given angle relative to its `X`, `Y`, `Z` axes;
    - Scale the model by a given value;
    - Perform affine transformations using a video card (using OpenGL library methods);
    - Set the projection type (parallel and central);
    - Customize the type (none, solid, dotted), color and thickness of edges, display method (absent, circle, square), color and size of vertices;
    - Select background color;
    - Save the received (“rendered”) images to a file in bmp and jpeg formats;
    - Record small “screencasts” - current custom affine transformations of the loaded object into gif animation (640x480, 10fps, 5s);
- The program implements a graphical user interface based on GUI libraries `QT` with `API` for `C11`.
- Graphical user interface contains:
    - A button for selecting a file with a model and a field for input/output of its name;
    - Button for switching the affine transformation method (processor/video card);
    - Projection settings button;
    - Buttons for selecting the type, color and thickness of ribs;
    - Buttons for selecting the type, color and size of vertices;
    - Background selection button;
    - Buttons for saving images and screencasts;
    - Frame model visualization area;
    - Slider and input fields for moving the model;
    - Slider and input fields for rotating the model;
    - Slider and input fields for scaling the model;
    - Information about the loaded model - file name, number of vertices and edges.
- Settings are saved between program restarts;
- The program correctly processes and allows the user to view models with details up to 100, 1000, 10,000, 100,000, 1,000,000 vertices without freezing (that is, without interface inactivity for more than 0.5 seconds).

## [Building project](#3dviewer-v10)

The following main goals for working with the project have been added to the `Makefile`:

| #  | Target             | Description of the target                                                 |
|----| ------------------ | ------------------------------------------------------------------------- |
| 1  | `all`              | Builds the project and launches the game                                  |
| 2  | `install`          | Builds the project                                                        |
| 3  | `uninstall`        | Uninstalls the project                                                    |
| 4  | `3d_viewer`        | Builds modules into a static library                                      |
| 5  | `test`             | Performs module testing                                                   |
| 6  | `gcov_report`      | Tests modules and generates a coverage report in `html` format            |
| 7  | `dvi`              | Generates documentation in `html` and manual format for the functionality |
| 8  | `dist`             | Compresses the project into a tar archive                                 |
| 9  | `clean`            | Cleans the repository of generated files                                  |
| 10 | `rebuild`          | Rebuilds the project                                                      |
| 11 | `clang_check`      | Testing modules for compliance with `Google style`                        |
| 12 | `cppcheck`         | Testing modules using the `cppcheck` code analyzer                        |
| 13 | `valgrind`         | Testing modules for working with memory via `Valgrind`                    |
| 14 | `docker_build`     | Builds the project via `Docker`                                           |
| 15 | `dependencies`     | Installs the necessary dependencies for building and testing the project  |
| 16 | `run`              | Launch the game                                                           |

<br>

The project can be built using the main goal `install`, which builds the project using `cmake`. There is a variation of installing using `Docker` via the `docker_build` target.

> To build the project on any operating system, you need cmake and qtbase starting from version 6.

## [Testing](#3dviewer-v10)

Also the code written was:

- tested by unit tests using the `check` library;
- tested for code coverage by tests with output to `html` report using `gcovr`;
- testing for errors/leaks via `valgrind`.

## [Feedback](#3dviewer-v10)

If you have any questions regarding the features or other aspects of the project that interest you, please contact <br>

|          |                       |
| ---------| --------------------- |
| mail     | gabilov1997@gmail.com |
| telegram | @kossadda             |
| vk       | vk.com/kossadda       |

Thank you for your attention. I hope you enjoy this project and find it useful.

<br>

[К оглавлению](#3dviewer-v10)
