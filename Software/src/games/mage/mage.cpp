#include "mage.h"

#include "common.h"
#include "mage_defines.h"

#include "EngineROM.h"
#include "EnginePanic.h"

#ifdef DC801_DESKTOP
#include "EngineWindowFrame.h"
#endif

#include "mage_hex.h"
#include "mage_script_control.h"

std::unique_ptr<MageGameControl> MageGame;
std::unique_ptr<MageHexEditor> MageHex;
std::unique_ptr<MageScriptControl> MageScript;
MageEntity *hackableDataAddress;
FrameBuffer *mage_canvas;

uint32_t lastTime;
uint32_t now;
uint32_t deltaTime;
uint32_t lastLoopTime;

Point cameraPosition = {
	.x = 0,
	.y = 0,
};

void GameUpdate()
{
	//check to see if player input is allowed:
	if(MageGame->playerHasControl)
	{
		//apply inputs that work all the time
		MageGame->applyUniversalInputs();

		//either do hax inputs:
		if (MageHex->getHexEditorState())
		{
			MageHex->applyHexModeInputs();
		}

		//or be boring and normal:
		else
		{
			//this handles buttons and state updates based on button presses in game mode:
			MageGame->applyGameModeInputs();
			
			//Call the map's onTick script:
			MageScript->handleMapOnTickScript();
			//then handle all entity onTick scripts:
			for(uint8_t i = 0; i < MageGame->Map().EntityCount(); i++)
			{
				//handle Entity onTick scripts for the local entity at Id 'i':
				MageScript->handleEntityOnTickScript(i);
			}

			//update the entities based on the current state of their (hackable) data array.
			MageGame->UpdateEntities(deltaTime);

			//run interact script on button press before drawing everything:
			if(EngineInput_Activated.rjoy_right)
			{ 
				//need a function to call interact scripts if player is interacting with things -Tim
			}
		}
	}
}

void GameRender()
{
	//make hax do
	if (MageHex->getHexEditorState())
	{
		//run hex editor if appropriate
		mage_canvas->clearScreen(RGB(0,0,0));
		MageHex->renderHexEditor();
	}
	//otherwise be boring and normal
	else
	{
		//otherwise run mage game:
		mage_canvas->clearScreen(RGB(0,0,255));

		//then draw the map and entities:
		uint8_t layerCount = MageGame->Map().LayerCount();

		if (layerCount > 1)
		{
			for (
				uint8_t layerIndex = 0;
				layerIndex < (layerCount - 1);
				layerIndex++
			)
			{
				//draw all map layers except the last one before drawing entities.
				MageGame->DrawMap(layerIndex, cameraPosition.x, cameraPosition.y);
			}
		}
		else
		{
			//if there is only one map layer, it will always be drawn before the entities.
			MageGame->DrawMap(0, cameraPosition.x, cameraPosition.y);
		}

		//now that the entities are updated, draw them to the screen.
		MageGame->DrawEntities(cameraPosition.x, cameraPosition.y);

		if (layerCount > 1)
		{	
			//draw the final layer above the entities.
			MageGame->DrawMap(layerCount - 1, cameraPosition.x, cameraPosition.y);
		}
	}

	//update the state of the LEDs
	MageHex->updateHexLights();

	//update the screen
	mage_canvas->blt();
}

void MAGE()
{
#ifdef DC801_DESKTOP
	EngineWindowFrameInit();
#endif

	// Initialize ROM and drivers
	EngineROM_Init();

	// Verify magic
	if (EngineROM_Magic((const uint8_t*)"MAGEGAME", 8) != true)
	{
		ENGINE_PANIC("Failed to match Game Magic");
	}
	
	// Construct MageGameControl object, loading all headers
	MageGame = std::make_unique<MageGameControl>();
	
	//construct MageHexEditor object, set hex editor defaults
	MageHex = std::make_unique<MageHexEditor>();

	//construct MageScriptControl object to handle scripts for the game
	MageScript = std::make_unique<MageScriptControl>();

	//load in the pointer to the array of MageEntities for use in hex editor mode:
	hackableDataAddress = MageGame->entities.get();

	//initialize the canvas object for the screen buffer.
	mage_canvas = p_canvas();

	//note the time the first loop is running
	lastTime = millis();
	lastLoopTime = lastTime;

	//set a default hacking option.
	MageHex->setHexOp(HEX_OPS_XOR);

	#ifdef DC801_DESKTOP
		fprintf(stderr, "MageGameControl RAM use:   %8d bytes.\r\n", MageGame->Size());
		fprintf(stderr, "MageScriptControl RAM use: %8d bytes.\r\n", MageScript->size());
		fprintf(stderr, "MageHexControl RAM use:    %8d bytes.\r\n", MageHex->size());
		fprintf(stderr, "FrameBuffer RAM use:       %8d bytes.\r\n", FRAMEBUFFER_SIZE * sizeof(uint16_t));
		fprintf(stderr, "-------------------------------------------\r\n");
		fprintf(stderr, "Minimum RAM overhead use:  %8d bytes.\r\n", 
			(MageGame->Size() + MageScript->size() + MageHex->size() + (FRAMEBUFFER_SIZE * sizeof(uint16_t))));
	#endif

	MageGame->LoadMap(DEFAULT_MAP);

	//main game loop:
	while (EngineIsRunning())
	{
		//update timing information at the start of every game loop
		now = millis();
		deltaTime = now - lastTime;
		lastTime = now;

		//frame limiter code to keep game running at a specific FPS:
		//only do this on the real hardware:
		#ifndef DC801_DESKTOP
		if( now < (lastLoopTime + MAGE_MIN_MILLIS_BETWEEN_FRAMES) )
		{ continue; }

		//code below here will only be run if enough ms have passed since the last frame:
		lastLoopTime = now;
		#endif

		//handles hardware inputs and makes their state available
		EngineHandleInput();

		//updates the state of all the things before rendering:
		GameUpdate();

		//This renders the game to the screen based on the loop's updated state.
		GameRender();
	}

	// Close rom and any open files
	EngineROM_Deinit();

	#ifdef DC801_DESKTOP
		// Clean up
		EngineWindowFrameDestroy();
	#endif

	return;
}