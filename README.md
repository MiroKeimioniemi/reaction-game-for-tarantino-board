# Reaction game for the [Tarantino board](https://gitlab.fabcloud.org/pub/programmers/tarantino)

A simple reaction time game for the [XIAO RP2040](https://wiki.seeedstudio.com/XIAO-RP2040/) powered [Tarantino board](https://gitlab.fabcloud.org/pub/programmers/tarantino) using an RGB LED and two unicolor LEDs. Made for the [embedded programming week](https://digital-fabrication-portfolio-miro-keimioniemi-a2f2c11a6e705b8f.gitlab.io/p/embedded-programming/) of the [Digital Fabrication](https://www.aalto.fi/en/minors/digital-fabrication-minor) overlay course for [Fab Academy](https://fabacademy.org/) held at [Aalto FabLab](https://studios.aalto.fi/fablab/). To read more about the project or my digital fabrication journey, visit my documentation website [here](https://digital-fabrication-portfolio-miro-keimioniemi-a2f2c11a6e705b8f.gitlab.io/). The GitLab repository can be found [here](https://gitlab.com/miro.keimioniemi/digital-fabrication-portfolio/-/tree/main) and all the material produced each week can be found under [content/post](https://gitlab.com/miro.keimioniemi/digital-fabrication-portfolio/-/tree/main/content/post).

The idea for the game is to improve the player's reflexes by forcing them to overcome their previous best reaction time for, in this case, five times in a row. The game is entirely configurable, however, meaning that this, along with many other features, can be changed by altering the single WIN_COUNT variable.

In order to win the game, the player must beat their previous reaction time for five times by being consistently faster. When started, the game gives a visual countdown with the RGB LED and starts soon after it flashes green. It then flashes either the target LED or a decoy LED at random intervals ranging from 0.5 to 5 seconds.

The player has to react to the target LED flashing by quickly pressing the button. If they did this in under MAX_DELAY and faster than their previous best (or ULONG_MAX denoting a very large long number in the case of the first press), they get a point, which is indicated by the RGB LED flashing green and a message in the Serial terminal with the new best time. If they fail to press the button faster, the RGB LED will flash yellow and neither positive nor negative points are given.

If, however, the player presses the button when they are not supposed to, i.e. when either the decoy LED is on or no LED is on, they get a strike, 5 of which lead to failure in the current configuration. A failure is indicated by the on-board LEDs turning semi-permanently red and victory is indicated similarly but with green. In order to start a new game, just press the reset button on the lower left corner of the XIAO board, denoted by “R”.

A demo video can be found [here](https://digital-fabrication-portfolio-miro-keimioniemi-a2f2c11a6e705b8f.gitlab.io/p/embedded-programming/#micropython) by clicking the link and scrolling upwards a little bit until the 57s long video.

The game can be found in the `src` folder. `other` contains code for testing the LEDs on the board. 

