/*
This class contains all the code related to the hex editor hacking interface.
*/
#ifndef _MAGE_SCRIPT_CONTROL_H
#define _MAGE_SCRIPT_CONTROL_H

#include "mage_defines.h"
#include "mage.h"
#include "mage_game_control.h"
#include "mage_hex.h"

//this is a class designed to handle all the scripting for the MAGE() game
//it is designed to work in tandem with a MageGameControl object and a
//MageHex object to effect that state of the game.

class MageScriptControl
{
	private:
		//the jumpScript variable is used by some actions to indicate that a script should
		//end and immediately begin running a new script.
		//it should be set to MAGE_NULL_SCRIPT unless a new script should be run immediately.
		uint16_t jumpScript;

		//variables for tracking suspended script states:
		MageScriptState mapLoadResumeState;
		MageScriptState mapTickResumeState;
		MageScriptState entityTickResumeStates[MAX_ENTITIES_PER_MAP];
		MageScriptState entityInteractResumeStates[MAX_ENTITIES_PER_MAP];

		//typedef for the array of function pointers to script action functions:
		typedef void(MageScriptControl::*ActionFunctionPointer)(uint8_t * args);

		//the actual array of action functions:
		ActionFunctionPointer actionFunctions[MageScriptActionTypeId::NUM_ACTIONS];
	public:
		MageScriptControl();

		uint32_t size() const;

		//this is used to call a script by script Id
		void runScript(uint16_t scriptId);

		//this will run through the actions in a script.
		//if a jumpScript is called by an action, it will return 
		//without processing any further actions.
		void processActionQueue(uint16_t scriptId);

		//this will get action arguments from ROM memory and call
		//a function based on the ActionTypeId 
		void runAction(uint32_t argumentMemoryAddress);

		//the functions below here are the action functions. These are going to be
		//called directly by scripts, and preform their actions based on arguments read from ROM
		void nullAction(uint8_t * args);
		void checkEntityByte(uint8_t * args);
		void checkSaveFlag(uint8_t * args);
		void checkIfEntityIsInGeometry(uint8_t * args);
		void checkForButtonPress(uint8_t * args);
		void checkForButtonState(uint8_t * args);
		void runScript(uint8_t * args);
		void compareEntityName(uint8_t * args);
		void blockingDelay(uint8_t * args);
		void nonBlockingDelay(uint8_t * args);
		void setPauseState(uint8_t * args);
		void setEntityByte(uint8_t * args);
		void setSaveFlag(uint8_t * args);
		void setPlayerControl(uint8_t * args);
		void setEntityInteractScript(uint8_t * args);
		void setEntityTickScript(uint8_t * args);
		void setMapTickScript(uint8_t * args);
		void setEntityType(uint8_t * args);
		void setHexCursorLocation(uint8_t * args);
		void setHexBit(uint8_t * args);
		void unlockHaxCell(uint8_t * args);
		void lockHaxCell(uint8_t * args);
		void loadMap(uint8_t * args);
		void screenShake(uint8_t * args);
		void screenFadeOut(uint8_t * args);
		void screenFadeIn(uint8_t * args);
		void showDialog(uint8_t * args);
		void setRenderableFont(uint8_t * args);
		void moveEntityToGeometry(uint8_t * args);
		void moveEntityAlongGeometry(uint8_t * args);
		void loopEntityAlongGeometry(uint8_t * args);
		void moveCameratoGeometry(uint8_t * args);
		void moveCameraAlongGeometry(uint8_t * args);
		void loopCameraAlongGeometry(uint8_t * args);
		void setEntityDirection(uint8_t * args);
		void setHexEditorState(uint8_t * args);
		void setHexEditorDialogMode(uint8_t * args);
}; //MageScriptControl

#endif //_MAGE_SCRIPT_CONTROL_H