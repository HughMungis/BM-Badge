# todo:

## Game Engine:
- [x] Add tile flipping to render function
- [x] Entities
	- [x] Determine which entity should be player character on map load
- [x] Handle player input
- [x] Add entity render ordering by coordinate of bottom edge
- [x] Add support for entity animation timing
	- [x] Make an array of uint16s that just hold the current frame for entities; it doesn't need to be hackable, just stateful
	- [x] Reset
- [x] Port over the sdl_toy_0 button & LED state emulation
	- [x] Start rendering the background graphic
	- [x] Collect the Button coordinates
	- [x] Render the Buttons
	- [x] Collect the LED coordinates
	- [x] Render the LEDs
	- [x] Handle all inputs for the buttons
	- [x] Toggle the button renderable states when buttons are down
	- [x] Toggle the LED/Boolean values when the buttons are pressed
- [x] Generate a bunch of different WAV files of different sample rates for Dovid
- [x] Port over the Hex Editor
	- [x] Build Monaco 9 as an AdaGFXFont because we need a good monospace font
	- [x] Start rendering the text for the byte grid
	- [x] Render byte selection cursor behind the text
	- [x] Arrows navigate cursor on byte grid when hex editor is open
	- [x] Pass states of currently selected byte to the LEDs
	- [x] Build the entity RAM <-> uint8_t array mapper/typecasting?
	- [x] Build hex ops handler functions
	- [x] Trigger swap of hex ops enum
	- [x] Build hex bit handler functions
	- [x] Trigger hex bit handler to change value of bits on selected byte
	- [x] Build MEM button handler functions
	- [x] Add ability to offset visible page of RAM by pages
	- [x] Render something on screen to see which RAM PAGE you're on
	- [x] Add PAGE handler; Hold page + arrows to jump pages of bytes?
	- [x] Start adding error handling for when indexing outside of supported types ROM data
- [x] Move functions for reading from the ROM into `mage_rom.cpp`
- [x] Create some `get_*_by_index` functions for validating hackable datas
	- [x] getValidEntityId
	- [x] getValidMapId
	- [x] getValidPrimaryIdType
	- [x] getValidTilesetId
	- [x] getValidTileId
	- [x] getValidAnimationId
	- [x] getValidAnimationFrame
	- [x] getValidEntityTypeId
	- [x] getValidEntityTypeAnimationId
	- [x] getValidEntityTypeDirection
- [x] In the ROM header, add a timestamp so we know if the game.dat should be replaced with SD card versions.
- [x] Make a list of some C functions we want scripts to be able to call
- [x] Decide on a common script function signature
- [x] Define an encoding format for scripts
- [ ] Adjust entity animation system to allow for multiple actions that can be called from scripts
- [x] Make it so that maps denote a player entity by ID in the game.dat file, and only has ONE or ZERO players per map.
- [x] Change map reset keybind to be XOR+MEM3 and make it work even in dialogs and the hex editor
- [ ] Script system
	- [x] Binary Encoder parts
	- [x] Scripts
		- [x] What is a script?
			- [x] It's a length + sequence of Actions
			- [x] Scripts shouldn't be able to be called when the player has opened the hex editor, but scripts should be able to open the hex editor when called from elsewhere.
			- [x] We'll need entity-based state variables to track pathing and other transient values between ticks.
		- [x] Map
			- [x] onMapLoad(uint16_t scriptId); //called once when the map loads
			- [x] onMapTick(uint16_t scriptId); //called every tick, used for doors, other static events when moving around map.
		- [x] Entity
			- [x] onEntityTick(uint16_t scriptId, uint8_t entityId); //called every tick, entityId is the entity calling that script.
			- [x] onEntityInteract(uint16_t scriptId); //called when the player interacts with the entity
	- [ ] Actions (see mage_defines.h for structs detailing arguments for each action type below:)
		- [x] NULL_ACTION
		- [x] CHECK_ENTITY_NAME
		- [x] CHECK_ENTITY_X
		- [x] CHECK_ENTITY_Y
		- [x] CHECK_ENTITY_INTERACT_SCRIPT
		- [x] CHECK_ENTITY_TICK_SCRIPT
		- [x] CHECK_ENTITY_TYPE
		- [x] CHECK_ENTITY_PRIMARY_ID
		- [x] CHECK_ENTITY_SECONDARY_ID
		- [x] CHECK_ENTITY_PRIMARY_ID_TYPE
		- [x] CHECK_ENTITY_CURRENT_ANIMATION
		- [x] CHECK_ENTITY_CURRENT_FRAME
		- [ ] CHECK_ENTITY_DIRECTION
		- [ ] CHECK_ENTITY_HACKABLE_STATE_A
		- [ ] CHECK_ENTITY_HACKABLE_STATE_B
		- [ ] CHECK_ENTITY_HACKABLE_STATE_C
		- [ ] CHECK_ENTITY_HACKABLE_STATE_D
		- [ ] CHECK_ENTITY_HACKABLE_STATE_A_U2
		- [ ] CHECK_ENTITY_HACKABLE_STATE_C_U2
		- [ ] CHECK_ENTITY_HACKABLE_STATE_A_U4
		- [ ] CHECK_ENTITY_PATH (specific hackable state check by name)
		- [/] CHECK_SAVE_FLAG (needs ROM/DESKTOP reads)
		- [x] CHECK_IF_ENTITY_IS_IN_GEOMETRY
		- [x] CHECK_FOR_BUTTON_PRESS
		- [x] CHECK_FOR_BUTTON_STATE
		- [x] CHECK_WARP_STATE
		- [x] RUN_SCRIPT
		- [x] BLOCKING_DELAY
		- [x] NON_BLOCKING_DELAY
		- [ ] PAUSE_GAME
		- [ ] PAUSE_ENTITY_SCRIPT
		- [x] SET_ENTITY_NAME
		- [x] SET_ENTITY_X
		- [x] SET_ENTITY_Y
		- [x] SET_ENTITY_INTERACT_SCRIPT
		- [x] SET_ENTITY_TICK_SCRIPT
		- [x] SET_ENTITY_TYPE
		- [x] SET_ENTITY_PRIMARY_ID
		- [x] SET_ENTITY_SECONDARY_ID
		- [x] SET_ENTITY_PRIMARY_ID_TYPE
		- [x] SET_ENTITY_CURRENT_ANIMATION - Encoder needs to lookup animation NAME, not index
		- [x] SET_ENTITY_CURRENT_FRAME
		- [x] SET_ENTITY_DIRECTION
		- [x] SET_ENTITY_DIRECTION_RELATIVE
		- [x] SET_ENTITY_DIRECTION_TARGET_ENTITY
		- [x] SET_ENTITY_DIRECTION_TARGET_GEOMETRY
		- [ ] SET_ENTITY_HACKABLE_STATE_A
		- [ ] SET_ENTITY_HACKABLE_STATE_B
		- [ ] SET_ENTITY_HACKABLE_STATE_C
		- [ ] SET_ENTITY_HACKABLE_STATE_D
		- [ ] SET_ENTITY_HACKABLE_STATE_A_U2
		- [ ] SET_ENTITY_HACKABLE_STATE_C_U2
		- [ ] SET_ENTITY_HACKABLE_STATE_A_U4
		- [ ] SET_ENTITY_PATH (specific hackable state check by name)
		- [/] SET_SAVE_FLAG (needs ROM/DESKTOP writes)
		- [x] SET_PLAYER_CONTROL
		- [ ] SET_MAP_TICK_SCRIPT
		- [ ] SET_HEX_CURSOR_LOCATION
		- [ ] SET_HEX_BITS
		- [x] SET_WARP_STATE
		- [ ] UNLOCK_HAX_CELL
		- [ ] LOCK_HAX_CELL
		- [x] SET_HEX_EDITOR_STATE
		- [x] SET_HEX_EDITOR_DIALOG_MODE
		- [x] LOAD_MAP
		- [x] SHOW_DIALOG
		- [ ] PLAY_ENTITY_ANIMATION
		- [x] TELEPORT_ENTITY_TO_GEOMETRY
		- [x] WALK_ENTITY_TO_GEOMETRY
		- [x] WALK_ENTITY_ALONG_GEOMETRY
		- [x] LOOP_ENTITY_ALONG_GEOMETRY
		- [ ] SET_CAMERA_TO_FOLLOW_ENTITY
		- [ ] TELEPORT_CAMERA_TO_GEOMETRY
		- [ ] PAN_CAMERA_TO_ENTITY
		- [ ] PAN_CAMERA_TO_GEOMETRY
		- [ ] PAN_CAMERA_ALONG_GEOMETRY
		- [ ] LOOP_CAMERA_ALONG_GEOMETRY
		- [ ] SET_SCREEN_SHAKE
		- [x] SCREEN_FADE_OUT
		- [x] SCREEN_FADE_IN
		- [ ] PLAY_SOUND_CONTINUOUS
		- [ ] PLAY_SOUND_INTERRUPT
- [x] Geometry
	- [x] polygon(uint8_t count, x points[count])
	- [x] polyline(uint8_t count, x points[count])
	- [x] point(uint16_t x, uint16_t y)
	- [x] Geometry::inside_poly(point) collision detection function
	- [x] draw() renders geometry to screen
- [ ] Collision System
	- [ ] For Tiles
	- [ ] For Entities
- [ ] Dialog Data Type Implementation:
	- [ ] Display Name - either stringId, or entityId
	- [x] The actual text to display, probably with line breaks hard coded in to keep things simple.
	- [x] byte to encode position (i.e. is the text on the top or bottom of the screen, is the portrait on the left or right side of the screen, should we display a portrait at all?, etc.).
		- [x] flags for position encoding byte:
			- [x] Top or Bottom
			- [x] Portrait on or off
			- [x] portrait left or right
	- [x] tilesetId and tileId for the portrait picture.
	- [ ] display font
	- [ ] voice sound Id
	- [ ] Dialog Responses:
		- [ ] response TypeId:
			- [ ] NO_RESPONSE = 0
			- [ ] SELECT_FROM_SHORT_LIST = 1
			- [ ] SELECT_FROM_LONG_LIST = 2
			- [ ] ENTER_NUMBER = 2
			- [ ] ENTER_ALPHANUMERIC = 3
			- [ ] etc...
		- [ ] Player responses to dialog may be desired:
			- [ ] Assuming pop-up happens while dialog is still active:
				- [ ] select from a list of options
				- [ ] enter a numerical code
				- [ ] enter an alphanumeric code (put on-screen keyboard over dialog? Cycle through all letter options like arcade name entry?)
			- [ ] new script and/or dialog to call depending on player response
		- [ ] Show bouncing arrow at bottom of dialog to indicate that the player should press button to continue
- [x] Strings
	- [x] uint16_t Length
	- [x] char array with null termination Length bytes long
- [ ] Save system with flags
	- [ ] Player Name (12 bytes, like all other entities)
	- [ ] On map init, replace player name into PlayerEntity
	- [ ] Use bit flags in a specific region of the ROM chip to encode SAVE data automatically as events transpire.
- [ ] Allow upload of game.dat to ROM chip using nrfjprog
	- [ ] Convert game.daty into a game.hex file that writes data to address 0x12000000 and up on the ROM chip.
	- [ ] Use qcustominit.ini file added with this commit and the following command to upload:
		- `nrfjprog -f nrf52 --qspiini qcustominit.ini --program <filename>`
		- More info on nrfjprog: https://infocenter.nordicsemi.com/index.jsp?topic=%2Fug_nrf_cltools%2FUG%2Fcltools%2Fnrf_nrfjprogexe_reference.html

## Encoder TODO:
- [x] Throw error when > 1 entities have `is_player`
- [ ] Build a test map with no entities and make sure it does not crash
- [x] Fix bug where empty string for script on map or entity does not encode as null_script
- [ ] Action Argument Getters:
	- [ ] color
	- [ ] button_id (need enum lookup)
	- [ ] entity hex cells
	- [ ] sound id lookup for scripts and dialogs
- [ ] Music/SFX encoding in the binary asset encoder
- [ ] Consider adding lookup encoding for setting primary ID, secondary ID, and primary ID type. The numbers seem to be unreliable when you change things in a map (i.e. a mage entity primary id is 3, then after changing something unrelated and re-encoding it jumped to 13), so being able to do a lookup to make sure an entity gets their type set to a specific thing would be useful.

## Hardware TODO:

- [x] Get keyboard chip working and reliably updating button states
- [x] Get LED control chip working and update LED control functions
- [x] Update FrameBuffer.h to work with the new larger screen
- [x] Use SD card for testing game until ROM chip is functional
- [ ] Get ROM chip read/write working reliably
- [ ] Verify function of all desktop testing build features are working correctly on badge hardware
- [ ] Fix audio driver and initialize communication with audio chip

# MAJOR GAMEPLAY AND QUEST SPOILERS BELOW!

## Assets we need
- [ ] More villagers
	- [ ] One of the children's actions should be a sneeze
- [ ] The other mystical artifacts, which do _not_ pick the mage
- [ ] Ring Zero, spinning
- [ ] Chicken
- [ ] Sparkles that could be overlayed on anything to draw attention
- [ ] Character Portraits for the Dialog system
	- [ ] Mouth open, closed
- [x] The Quest Board tiles
- [X] The 9-slice image for "Quest List" screen
- [X] The 9-slice image for dialog borders
- [ ] Tiles for the inside of village houses
- [ ] Set Dressing
	- [ ] Bed
	- [ ] Flower Pots
	- [ ] Windows
	- [ ] Kitchen table
	- [ ] Kitchen chairs at table
	- [ ] Pots
	- [ ] Interior Doors for all 4 walls
	- [ ] Fireplace
	- [ ] Shelves with things on them
	- [ ] Fruits on table
	- [ ] Fence Posts to paint, so we need 2 states
	- [ ] Dancy Flowers
	- [ ] A rake, for the lake
- [ ] A knob that has never turned, but must be turned to get the fountain to turn on again
- [ ] A well, for Timmy to get stuck in
- [ ] Tiles for village elder's basement/dungeon
- [X] Bender + shiny metal ass