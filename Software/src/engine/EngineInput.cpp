#include "EngineInput.h"
#include "FrameBuffer.h"
#include "fonts/Monaco9.h"

#ifdef __cplusplus
extern "C" {
#endif

bool running = true;

ButtonStates EngineInput_Buttons = {};
ButtonStates EngineInput_Activated = {};
bool *buttonBoolPointerArray[] = {
	&EngineInput_Buttons.mem0,
	&EngineInput_Buttons.mem1,
	&EngineInput_Buttons.mem2,
	&EngineInput_Buttons.mem3,
	&EngineInput_Buttons.bit_128,
	&EngineInput_Buttons.bit_64,
	&EngineInput_Buttons.bit_32,
	&EngineInput_Buttons.bit_16,
	&EngineInput_Buttons.bit_8,
	&EngineInput_Buttons.bit_4,
	&EngineInput_Buttons.bit_2,
	&EngineInput_Buttons.bit_1,
	&EngineInput_Buttons.op_xor,
	&EngineInput_Buttons.op_add,
	&EngineInput_Buttons.op_sub,
	&EngineInput_Buttons.op_page,
	&EngineInput_Buttons.ljoy_center,
	&EngineInput_Buttons.ljoy_left,
	&EngineInput_Buttons.ljoy_down,
	&EngineInput_Buttons.ljoy_up,
	&EngineInput_Buttons.ljoy_right,
	&EngineInput_Buttons.rjoy_center,
	&EngineInput_Buttons.rjoy_left,
	&EngineInput_Buttons.rjoy_down,
	&EngineInput_Buttons.rjoy_up,
	&EngineInput_Buttons.rjoy_right,
	&EngineInput_Buttons.hax,
};

#ifdef DC801_DESKTOP

void EngineGetDesktopInputState(uint32_t *keyboardBitmask)
{
	if (application_quit != 0)
	{
		running = false;
		return;
	}

	SDL_PumpEvents();

	const uint8_t *keys = SDL_GetKeyboardState(nullptr);
	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			running = false;
			return;
		}

		if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_ESCAPE)
			{
				running = false;
				return;
			}
		}
	}

	uint32_t newValue = 0x00000000;

	//primary bindings:
	newValue ^= (uint32_t) keys[SDL_SCANCODE_F5] << KEYBOARD_KEY_MEM0;
	newValue ^= (uint32_t) keys[SDL_SCANCODE_F6] << KEYBOARD_KEY_MEM1;
	newValue ^= (uint32_t) keys[SDL_SCANCODE_F7] << KEYBOARD_KEY_MEM2;
	newValue ^= (uint32_t) keys[SDL_SCANCODE_F8] << KEYBOARD_KEY_MEM3;
	newValue ^= (uint32_t) keys[SDL_SCANCODE_1] << KEYBOARD_KEY_BIT128;
	newValue ^= (uint32_t) keys[SDL_SCANCODE_2] << KEYBOARD_KEY_BIT64;
	newValue ^= (uint32_t) keys[SDL_SCANCODE_3] << KEYBOARD_KEY_BIT32;
	newValue ^= (uint32_t) keys[SDL_SCANCODE_4] << KEYBOARD_KEY_BIT16;
	newValue ^= (uint32_t) keys[SDL_SCANCODE_5] << KEYBOARD_KEY_BIT8;
	newValue ^= (uint32_t) keys[SDL_SCANCODE_6] << KEYBOARD_KEY_BIT4;
	newValue ^= (uint32_t) keys[SDL_SCANCODE_7] << KEYBOARD_KEY_BIT2;
	newValue ^= (uint32_t) keys[SDL_SCANCODE_8] << KEYBOARD_KEY_BIT1;
	newValue ^= (uint32_t) keys[SDL_SCANCODE_F1] << KEYBOARD_KEY_XOR;
	newValue ^= (uint32_t) keys[SDL_SCANCODE_F2] << KEYBOARD_KEY_ADD;
	newValue ^= (uint32_t) keys[SDL_SCANCODE_F3] << KEYBOARD_KEY_SUB;
	newValue ^= (uint32_t) keys[SDL_SCANCODE_F4] << KEYBOARD_KEY_PAGE;
	newValue ^= (uint32_t) keys[SDL_SCANCODE_E] << KEYBOARD_KEY_LJOY_CENTER;
	newValue ^= (uint32_t) keys[SDL_SCANCODE_W] << KEYBOARD_KEY_LJOY_UP;
	newValue ^= (uint32_t) keys[SDL_SCANCODE_S] << KEYBOARD_KEY_LJOY_DOWN;
	newValue ^= (uint32_t) keys[SDL_SCANCODE_A] << KEYBOARD_KEY_LJOY_LEFT;
	newValue ^= (uint32_t) keys[SDL_SCANCODE_D] << KEYBOARD_KEY_LJOY_RIGHT;
	newValue ^= (uint32_t) keys[SDL_SCANCODE_KP_5] << KEYBOARD_KEY_RJOY_CENTER;
	newValue ^= (uint32_t) keys[SDL_SCANCODE_KP_8] << KEYBOARD_KEY_RJOY_UP;
	newValue ^= (uint32_t) keys[SDL_SCANCODE_KP_2] << KEYBOARD_KEY_RJOY_DOWN;
	newValue ^= (uint32_t) keys[SDL_SCANCODE_KP_4] << KEYBOARD_KEY_RJOY_LEFT;
	newValue ^= (uint32_t) keys[SDL_SCANCODE_KP_6] << KEYBOARD_KEY_RJOY_RIGHT;
	newValue ^= (uint32_t) keys[SDL_SCANCODE_TAB] << KEYBOARD_KEY_HAX;
	//secondary bindings that duplicate values above:
	newValue ^= (uint32_t) keys[SDL_SCANCODE_LSHIFT] << KEYBOARD_KEY_RJOY_DOWN;
	newValue ^= (uint32_t) keys[SDL_SCANCODE_LCTRL] << KEYBOARD_KEY_PAGE;
	newValue ^= (uint32_t) keys[SDL_SCANCODE_UP] << KEYBOARD_KEY_LJOY_UP;
	newValue ^= (uint32_t) keys[SDL_SCANCODE_DOWN] << KEYBOARD_KEY_LJOY_DOWN;
	newValue ^= (uint32_t) keys[SDL_SCANCODE_LEFT] << KEYBOARD_KEY_LJOY_LEFT;
	newValue ^= (uint32_t) keys[SDL_SCANCODE_RIGHT] << KEYBOARD_KEY_LJOY_RIGHT;
	newValue ^= (uint32_t) keys[SDL_SCANCODE_O] << KEYBOARD_KEY_RJOY_CENTER;
	newValue ^= (uint32_t) keys[SDL_SCANCODE_I] << KEYBOARD_KEY_RJOY_UP;
	newValue ^= (uint32_t) keys[SDL_SCANCODE_K] << KEYBOARD_KEY_RJOY_DOWN;
	newValue ^= (uint32_t) keys[SDL_SCANCODE_J] << KEYBOARD_KEY_RJOY_LEFT;
	newValue ^= (uint32_t) keys[SDL_SCANCODE_L] << KEYBOARD_KEY_RJOY_RIGHT;

	*keyboardBitmask = newValue;
	// debug_print("EngineGetDesktopInputState keyboardBitmask: %" PRIu32 "\n", *keyboardBitmask);
}

#endif

void EngineSetHardwareBitmaskToButtonStates (uint32_t keyboardBitmask)
{
	uint32_t oneBit = 0x00000001;

	memcpy(&EngineInput_Activated, &EngineInput_Buttons, sizeof(ButtonStates));

	EngineInput_Buttons.mem0 = (oneBit << KEYBOARD_KEY_MEM0) & keyboardBitmask;
	EngineInput_Buttons.mem1 = (oneBit << KEYBOARD_KEY_MEM1) & keyboardBitmask;
	EngineInput_Buttons.mem2 = (oneBit << KEYBOARD_KEY_MEM2) & keyboardBitmask;
	EngineInput_Buttons.mem3 = (oneBit << KEYBOARD_KEY_MEM3) & keyboardBitmask;
	EngineInput_Buttons.bit_128 = (oneBit << KEYBOARD_KEY_BIT128) & keyboardBitmask;
	EngineInput_Buttons.bit_64 = (oneBit << KEYBOARD_KEY_BIT64) & keyboardBitmask;
	EngineInput_Buttons.bit_32 = (oneBit << KEYBOARD_KEY_BIT32) & keyboardBitmask;
	EngineInput_Buttons.bit_16 = (oneBit << KEYBOARD_KEY_BIT16) & keyboardBitmask;
	EngineInput_Buttons.bit_8 = (oneBit << KEYBOARD_KEY_BIT8) & keyboardBitmask;
	EngineInput_Buttons.bit_4 = (oneBit << KEYBOARD_KEY_BIT4) & keyboardBitmask;
	EngineInput_Buttons.bit_2 = (oneBit << KEYBOARD_KEY_BIT2) & keyboardBitmask;
	EngineInput_Buttons.bit_1 = (oneBit << KEYBOARD_KEY_BIT1) & keyboardBitmask;
	EngineInput_Buttons.op_xor = (oneBit << KEYBOARD_KEY_XOR) & keyboardBitmask;
	EngineInput_Buttons.op_add = (oneBit << KEYBOARD_KEY_ADD) & keyboardBitmask;
	EngineInput_Buttons.op_sub = (oneBit << KEYBOARD_KEY_SUB) & keyboardBitmask;
	EngineInput_Buttons.op_page = (oneBit << KEYBOARD_KEY_PAGE) & keyboardBitmask;
	EngineInput_Buttons.ljoy_center = (oneBit << KEYBOARD_KEY_LJOY_CENTER) & keyboardBitmask;
	EngineInput_Buttons.ljoy_up = (oneBit << KEYBOARD_KEY_LJOY_UP) & keyboardBitmask;
	EngineInput_Buttons.ljoy_down = (oneBit << KEYBOARD_KEY_LJOY_DOWN) & keyboardBitmask;
	EngineInput_Buttons.ljoy_left = (oneBit << KEYBOARD_KEY_LJOY_LEFT) & keyboardBitmask;
	EngineInput_Buttons.ljoy_right = (oneBit << KEYBOARD_KEY_LJOY_RIGHT) & keyboardBitmask;
	EngineInput_Buttons.rjoy_center = (oneBit << KEYBOARD_KEY_RJOY_CENTER) & keyboardBitmask;
	EngineInput_Buttons.rjoy_up = (oneBit << KEYBOARD_KEY_RJOY_UP) & keyboardBitmask;
	EngineInput_Buttons.rjoy_down = (oneBit << KEYBOARD_KEY_RJOY_DOWN) & keyboardBitmask;
	EngineInput_Buttons.rjoy_left = (oneBit << KEYBOARD_KEY_RJOY_LEFT) & keyboardBitmask;
	EngineInput_Buttons.rjoy_right = (oneBit << KEYBOARD_KEY_RJOY_RIGHT) & keyboardBitmask;
	EngineInput_Buttons.hax = (oneBit << KEYBOARD_KEY_HAX) & keyboardBitmask;

	EngineInput_Activated.mem0 = !EngineInput_Activated.mem0 && EngineInput_Buttons.mem0;
	EngineInput_Activated.mem1 = !EngineInput_Activated.mem1 && EngineInput_Buttons.mem1;
	EngineInput_Activated.mem2 = !EngineInput_Activated.mem2 && EngineInput_Buttons.mem2;
	EngineInput_Activated.mem3 = !EngineInput_Activated.mem3 && EngineInput_Buttons.mem3;
	EngineInput_Activated.bit_128 = !EngineInput_Activated.bit_128 && EngineInput_Buttons.bit_128;
	EngineInput_Activated.bit_64 = !EngineInput_Activated.bit_64 && EngineInput_Buttons.bit_64;
	EngineInput_Activated.bit_32 = !EngineInput_Activated.bit_32 && EngineInput_Buttons.bit_32;
	EngineInput_Activated.bit_16 = !EngineInput_Activated.bit_16 && EngineInput_Buttons.bit_16;
	EngineInput_Activated.bit_8 = !EngineInput_Activated.bit_8 && EngineInput_Buttons.bit_8;
	EngineInput_Activated.bit_4 = !EngineInput_Activated.bit_4 && EngineInput_Buttons.bit_4;
	EngineInput_Activated.bit_2 = !EngineInput_Activated.bit_2 && EngineInput_Buttons.bit_2;
	EngineInput_Activated.bit_1 = !EngineInput_Activated.bit_1 && EngineInput_Buttons.bit_1;
	EngineInput_Activated.op_xor = !EngineInput_Activated.op_xor && EngineInput_Buttons.op_xor;
	EngineInput_Activated.op_add = !EngineInput_Activated.op_add && EngineInput_Buttons.op_add;
	EngineInput_Activated.op_sub = !EngineInput_Activated.op_sub && EngineInput_Buttons.op_sub;
	EngineInput_Activated.op_page = !EngineInput_Activated.op_page && EngineInput_Buttons.op_page;
	EngineInput_Activated.ljoy_center = !EngineInput_Activated.ljoy_center && EngineInput_Buttons.ljoy_center;
	EngineInput_Activated.ljoy_up = !EngineInput_Activated.ljoy_up && EngineInput_Buttons.ljoy_up;
	EngineInput_Activated.ljoy_down = !EngineInput_Activated.ljoy_down && EngineInput_Buttons.ljoy_down;
	EngineInput_Activated.ljoy_left = !EngineInput_Activated.ljoy_left && EngineInput_Buttons.ljoy_left;
	EngineInput_Activated.ljoy_right = !EngineInput_Activated.ljoy_right && EngineInput_Buttons.ljoy_right;
	EngineInput_Activated.rjoy_center = !EngineInput_Activated.rjoy_center && EngineInput_Buttons.rjoy_center;
	EngineInput_Activated.rjoy_up = !EngineInput_Activated.rjoy_up && EngineInput_Buttons.rjoy_up;
	EngineInput_Activated.rjoy_down = !EngineInput_Activated.rjoy_down && EngineInput_Buttons.rjoy_down;
	EngineInput_Activated.rjoy_left = !EngineInput_Activated.rjoy_left && EngineInput_Buttons.rjoy_left;
	EngineInput_Activated.rjoy_right = !EngineInput_Activated.rjoy_right && EngineInput_Buttons.rjoy_right;
	EngineInput_Activated.hax = !EngineInput_Activated.hax && EngineInput_Buttons.hax;
}

void EngineHandleInput ()
{
	static uint32_t keyboardBitmask = 0x00000000;

#ifdef DC801_DESKTOP
	EngineGetDesktopInputState(&keyboardBitmask);
#endif

#ifdef DC801_EMBEDDED
	app_usbd_event_queue_process();
	keyboardBitmask = get_keyboard_mask();
#endif
	EngineSetHardwareBitmaskToButtonStates(keyboardBitmask);

	/*
	//screen logging, prints button states to screen:
	char mask_string[128];
	uint8_t length = 0;
	for(int k=0; k<KEYBOARD_NUM_KEYS; k++){
		length += sprintf(mask_string+length, "%d", *buttonBoolPointerArray[k]);
	}
	p_canvas()->clearScreen(COLOR_DARKBLUE);
	p_canvas()->printMessage(
		mask_string,
		Monaco9,
		COLOR_WHITE,
		32,
		32
	);
	//p_canvas()->blt();

	//nrf_delay_ms(500);

	//screen logging:
	length = 0;
	for(int k=0; k<KEYBOARD_NUM_KEYS; k++){
		length += sprintf(mask_string+length, "%d", *buttonBoolPointerArray[k]);
	}
	//p_canvas()->clearScreen(COLOR_RED);
	p_canvas()->printMessage(
		mask_string,
		Monaco9,
		COLOR_RED,
		32,
		32
	);
	p_canvas()->blt();

	nrf_delay_ms(500);
	*/
}

bool EngineIsRunning()
{
	return running;
}

#ifdef __cplusplus
}
#endif
